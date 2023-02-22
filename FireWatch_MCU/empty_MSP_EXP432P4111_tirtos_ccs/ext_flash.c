/*
 * ext_flash.c
 *
 *  Created on: Aug 7, 2018
 *      Author: dvthan
 */



/* -----------------------------------------------------------------------------
*  Includes
* ------------------------------------------------------------------------------
*/
//#include <driverlib/gpio.h>

#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/SPI.h>

/* Board Header file */
#include "Board.h"
#include "ext_flash.h"


/* -----------------------------------------------------------------------------
*  Constants and macros
* ------------------------------------------------------------------------------
*/

#define SPI_BIT_RATE              4000000

/* Instruction codes */

#define BLS_CODE_PROGRAM          0x02 /**< Page Program */
#define BLS_CODE_READ             0x03 /**< Read Data */
#define BLS_CODE_READ_STATUS      0x05 /**< Read Status Register */
#define BLS_CODE_WRITE_ENABLE     0x06 /**< Write Enable */
#define BLS_CODE_SECTOR_ERASE     0x20 /**< Sector Erase */
#define BLS_CODE_MDID             0x90 /**< Manufacturer Device ID */

#define BLS_CODE_DP               0xB9 /**< Power down */
#define BLS_CODE_RDP              0xAB /**< Power standby */

/* Erase instructions */

#define BLS_CODE_ERASE_4K         0x20 /**< Sector Erase */
#define BLS_CODE_ERASE_32K        0x52
#define BLS_CODE_ERASE_64K        0xD8
#define BLS_CODE_ERASE_ALL        0xC7 /**< Mass Erase */

/* Bitmasks of the status register */

#define BLS_STATUS_SRWD_BM        0x80
#define BLS_STATUS_BP_BM          0x0C
#define BLS_STATUS_WEL_BM         0x02
#define BLS_STATUS_WIP_BM         0x01

#define BLS_STATUS_BIT_BUSY       0x01 /**< Busy bit of the status register */

/* Part specific constants */

#define BLS_PROGRAM_PAGE_SIZE     256
#define BLS_ERASE_SECTOR_SIZE     4096

/* -----------------------------------------------------------------------------
*  Private data
* ------------------------------------------------------------------------------
*/

// Supported flash devices
static const ExtFlashInfo_t flashInfo[] =
{
    {
        .manfId = 0xC2,         // Macronics MX25R1635F
        .devId = 0x15,
        .deviceSize = 0x200000  // 2 MByte (16 Mbit)
    },
    {
        .manfId = 0xC2,         // Macronics MX25R8035F
        .devId = 0x14,          //
        .deviceSize = 0x100000  // 1 MByte (8 Mbit)
    },
    {
        .manfId = 0xEF,         // WinBond W25X40CL
        .devId = 0x12,
        .deviceSize = 0x080000  // 512 KByte (4 Mbit)
    },
    {
        .manfId = 0xEF,         // WinBond W25X20CL
        .devId = 0x11,
        .deviceSize = 0x040000  // 256 KByte (2 Mbit)
    },
    {
        .manfId = 0x0,
        .devId = 0x0,
        .deviceSize = 0x0
    }
};

// Flash information
static const ExtFlashInfo_t *pFlashInfo = NULL;
static uint8_t infoBuf[2];

static SPI_Handle      spi;
static SPI_Params      spiParams;
static SPI_Transaction spiTransaction;
static uint8_t buffertemp_tx[BLS_PROGRAM_PAGE_SIZE+4];
static uint8_t buffertemp_rx[BLS_PROGRAM_PAGE_SIZE+4];

/* -----------------------------------------------------------------------------
*  Private function prototypes
* ------------------------------------------------------------------------------
*/
static int extFlashWaitReady(void);
static int extFlashWaitPowerDown(void);


/* -----------------------------------------------------------------------------
*  Public Functions
* ------------------------------------------------------------------------------
*/
static int Spitransaction(uint8_t *wbuf, uint8_t *rbuf, size_t wlength, size_t rlength)
{
    int i;
    bool success;

    if (rlength + wlength > 260)
    {
        if (wlength > 260)
        {
            wlength = 260;
        }
        i = 260 - wlength;
        if (i < 0)
        {
            rlength = 0;
        }
    }
    // copy memory
    if (wbuf != buffertemp_tx)
    {
        for (i =  0; i < wlength; i++)
        {
            buffertemp_tx[i] = *wbuf++;
        }
    }
    spiTransaction.count = wlength + rlength;
    success = SPI_transfer(spi, &spiTransaction);

    if (rbuf != buffertemp_rx)
    {
        for (i = 0; i < rlength; i++)
        {
            rbuf[i] =  buffertemp_rx[wlength + i];
        }
    }
    if (success)
    {
        return 0;
    }
    else
    {
        return 1;
    }

}

static void SpiFlushMem(void)
{
    SPI_transferCancel(spi);
}

/*******************************************************************************
* @fn          extFlashSelect
*
* @brief       Select the external flash on the SensorTag
*
* @param       none
*
* @return      none
*/
static void extFlashSelect(void)
{
    //GPIO_clearDio(BSP_IOID_FLASH_CS);
    GPIO_write(MSP_EXP432P4011_SPI_FLASH, 0);
}

/*******************************************************************************
* @fn          extFlashDeselect
*
* @brief       Deselect the external flash on the SensorTag
*
* @param       none
*
* @return      none
*/
static void extFlashDeselect(void)
{
    //GPIO_setDio(BSP_IOID_FLASH_CS);
    GPIO_write(MSP_EXP432P4011_SPI_FLASH, 1);
}

/*******************************************************************************
* @fn       extFlashInfo
*
* @brief    Get information about the mounted flash
*
* @param    none
*
* @return   return flash info record (all fields are zero if not found)
*******************************************************************************/
const ExtFlashInfo_t *extFlashInfo(void)
{
    return pFlashInfo;
}

/*******************************************************************************
* @fn       extFlashPowerDown
*
* @brief    Put the device in power save mode. No access to data; only
*           the status register is accessible.
*
* @param    none
*
* @return   Returns true if transactions succeed
*******************************************************************************/
static bool extFlashPowerDown(void)
{
    uint8_t cmd;
    bool success;

    cmd = BLS_CODE_DP;

    extFlashSelect();
    success = Spitransaction(&cmd, NULL, sizeof(cmd), 0) == 0;
    extFlashDeselect();

    return success;
}

/******************************************************************************
* @fn       extFlashPowerStandby
*
* @brief    Take device out of power save mode and prepare it for normal operation
*
* @param    none
*
* @return   Returns true if command successfully written
******************************************************************************/
static bool extFlashPowerStandby(void)
{
    uint8_t cmd[4];
    uint8_t res;
    bool success;

    cmd[0] = BLS_CODE_RDP;

    extFlashSelect();
    success = Spitransaction((void *)cmd, &res, 4, 1) == 0;
    extFlashDeselect();

    if (success)
    {
        uint16_t i = 200;

        // Waking up of the device is manufacturer dependent.
        // for a Winond chip-set, once the request to wake up the flash has been
        // send, CS needs to stay high at least 3us (for Winbond part)
        // for chip-set like Macronix, it can take up to 35us.
        while(i--);

        if (extFlashWaitReady() != 0)
        {
            success = false;
        }
    }

    return success;
}

/**
* Read flash information (manufacturer and device ID)
* @return True when successful.
*/
static bool extFlashReadInfo(void)
{
    int ret;
    const uint8_t wbuf[] = { BLS_CODE_MDID, 0xFF, 0xFF, 0x00 };

    extFlashSelect();
    ret = Spitransaction((void *)wbuf, (void *)infoBuf, sizeof(wbuf), sizeof(infoBuf));
    extFlashDeselect();

    return ret == 0;
}

/**
* Verify the flash part.
* @return True when successful.
*/
static bool extFlashVerifyPart(void)
{
    if (!extFlashReadInfo())
    {
        return false;
    }

    pFlashInfo = flashInfo;
    while (pFlashInfo->deviceSize > 0)
    {
        if (infoBuf[0] == pFlashInfo->manfId && infoBuf[1] == pFlashInfo->devId)
        {
            break;
        }
        pFlashInfo++;
    }

    return pFlashInfo->deviceSize > 0;
}

/**
* Wait till previous erase/program operation completes.
* @return Zero when successful.
*/
static int extFlashWaitReady(void)
{
    const uint8_t wbuf[1] = { BLS_CODE_READ_STATUS };
    int ret;

    /* Throw away garbage */
    extFlashSelect();
    SpiFlushMem();
    extFlashDeselect();

    for (;;)
    {
        uint8_t buf;

        extFlashSelect();
        ret = Spitransaction((void *)wbuf, (void *)&buf, sizeof(wbuf), sizeof(buf));
        extFlashDeselect();

        if (ret)
        {
            /* Error */
            return -2;
        }
        if (!(buf & BLS_STATUS_BIT_BUSY))
        {
            /* Now ready */
            break;
        }
    }

    return 0;
}


/**
* Wait until the part has entered power down (JDEC readout fails)
* @return Zero when successful.
*/
static int extFlashWaitPowerDown(void)
{
    uint8_t i;

    i = 0;
    while (i<10)
    {
        if (!extFlashVerifyPart())
        {
            return 0;
        }
        i++;
    }

    return -1;
}

/**
* Enable write.
* @return Zero when successful.
*/
static int extFlashWriteEnable(void)
{
    const uint8_t wbuf[] = { BLS_CODE_WRITE_ENABLE };

    extFlashSelect();
    int ret = Spitransaction((void *)wbuf, NULL, sizeof(wbuf), 0);
    extFlashDeselect();

    if (ret)
    {
        return -3;
    }

    return 0;
}

/* See ext_flash.h file for description */
bool extFlashOpen(void)
{
    bool f;

    SPI_Params_init(&spiParams);  // Initialize SPI parameters
    spiParams.dataSize = 8;       // 8-bit data size
    spiParams.bitRate = SPI_BIT_RATE;
    spiParams.mode = SPI_MASTER;
    spiParams.frameFormat = SPI_POL0_PHA0;

    spi = SPI_open(MSP_EXP432P4011_SPIA1, &spiParams);

    spiTransaction.txBuf = buffertemp_tx;
    spiTransaction.rxBuf = buffertemp_rx;
    spiTransaction.count = 0;

    GPIO_setConfig(MSP_EXP432P4011_SPI_FLASH, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_HIGH);

    /* Default output to clear chip select */
    extFlashDeselect();

    /* Put the part is standby mode */
    f = extFlashPowerStandby();

    if (f)
    {
        f = extFlashVerifyPart();
    }

    if (!f)
    {
        extFlashClose();
    }

    return f;
}

/* See ext_flash.h file for description */
void extFlashClose(void)
{
    // Put the part in low power mode
    extFlashPowerDown();
    extFlashWaitPowerDown();
    SPI_close(spi);
}

/* See ext_flash.h file for description */
bool extFlashRead(size_t offset, size_t length, uint8_t *buf)
{
    uint8_t wbuf[4];
    //size_t ilen;
    size_t length1;

    /* Wait till previous erase/program operation completes */
    int ret = extFlashWaitReady();
    if (ret)
    {
        return false;
    }

    /* SPI is driven with very low frequency (1MHz < 33MHz fR spec)
    * in this temporary implementation.
    * and hence it is not necessary to use fast read. */
    wbuf[0] = BLS_CODE_READ;
    wbuf[1] = (offset >> 16) & 0xff;
    wbuf[2] = (offset >> 8) & 0xff;
    wbuf[3] = offset & 0xff;
    if (length > 0)
    {
        extFlashSelect();
        if (length > BLS_PROGRAM_PAGE_SIZE)
        {
            length1 = BLS_PROGRAM_PAGE_SIZE;
        }
        else
        {
            length1 = length;
        }
        ret = Spitransaction(wbuf, buf, sizeof(wbuf), length1);
        length -= length1;
        buf += length1;

        while(length > 0)
        {
            if (length > BLS_PROGRAM_PAGE_SIZE)
            {
                length1 = BLS_PROGRAM_PAGE_SIZE;
            }
            else
            {
                length1 = length;
            }
            ret = Spitransaction(NULL, buf, 0, length1);
            buf += length1;
            length -= length1;
        }
        extFlashDeselect();
    }
    return ret == 0;
}

/* See ext_flash.h file for description */
bool extFlashWrite(size_t offset, size_t length, const uint8_t *buf)
{
    int i;
    bool ret = false;
    while (length > 0)
    {
        /* Wait till previous erase/program operation completes */
        int ret = extFlashWaitReady();
        if (ret)
        {
            return false;
        }

        ret = extFlashWriteEnable();
        if (ret)
        {
            return false;
        }

        size_t ilen; /* interim length per instruction */

        ilen = BLS_PROGRAM_PAGE_SIZE - (offset % BLS_PROGRAM_PAGE_SIZE);
        if (length < ilen)
        {
            ilen = length;
        }

        buffertemp_tx[0] = BLS_CODE_PROGRAM;
        buffertemp_tx[1] = (offset >> 16) & 0xff;
        buffertemp_tx[2] = (offset >> 8) & 0xff;
        buffertemp_tx[3] = offset & 0xff;
        for (i = 4; i<(4 + ilen); i++ )
        {
            buffertemp_tx[i] = buf[i-4];
        }

        offset += ilen;
        length -= ilen;

        /* Up to 100ns CS hold time (which is not clear
        * whether it's application only in between reads)
        * is not imposed here since above instructions
        * should be enough to delay
        * as much. */
        extFlashSelect();

        ret = Spitransaction(buffertemp_tx, NULL, ilen + 4, 0);

        buf += ilen;
        extFlashDeselect();
    }

    return ret == 0;
}

/* See ext_flash.h file for description */
bool extFlashErase(size_t offset, size_t length)
{
    /* Note that Block erase might be more efficient when the floor map
    * is well planned for OTA but to simplify for the temporary implementation,
    * sector erase is used blindly. */
    uint8_t wbuf[4];
    size_t i, numsectors;

    wbuf[0] = BLS_CODE_SECTOR_ERASE;

    {
        size_t endoffset = offset + length - 1;
        offset = (offset / BLS_ERASE_SECTOR_SIZE) * BLS_ERASE_SECTOR_SIZE;
        numsectors = (endoffset - offset + BLS_ERASE_SECTOR_SIZE - 1) /
                      BLS_ERASE_SECTOR_SIZE;
    }

    for (i = 0; i < numsectors; i++)
    {
        /* Wait till previous erase/program operation completes */
        int ret = extFlashWaitReady();
        if (ret)
        {
            return false;
        }

        ret = extFlashWriteEnable();
        if (ret)
        {
            return false;
        }

        wbuf[1] = (offset >> 16) & 0xff;
        wbuf[2] = (offset >> 8) & 0xff;
        wbuf[3] = offset & 0xff;

        extFlashSelect();

        ret = Spitransaction(wbuf, NULL, 4, 0);

        if (ret != 0)
        {
            /* failure */
            extFlashDeselect();
            return false;
        }
        extFlashDeselect();

        offset += BLS_ERASE_SECTOR_SIZE;
    }

    return true;
}

/* See ext_flash.h file for description */
bool extFlashTest(void)
{
    bool ret;

    ret = extFlashOpen();
    if (ret)
    {
        extFlashClose();
    }

    return ret;
}






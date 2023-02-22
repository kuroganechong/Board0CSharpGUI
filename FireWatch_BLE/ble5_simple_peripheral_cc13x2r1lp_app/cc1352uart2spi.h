

#ifndef CC1352UART2SPI_H_
#define CC1352UART2SPI_H_
#define TASKSTACKSIZE     1024
#define UART_RECEIVE_LEN  (240)
#define UART_SEND_LEN     (240)
#define SPI_TRANS_LEN     (240)
#define BLE_TRANS_LEN     (240)

// Task

void Uart2SpiBridgeFxn(UArg arg0, UArg arg1);



#endif /* CC1352UART2SPI_H_ */

# invoke SourceDir generated makefile for ble_release.pem4f
ble_release.pem4f: .libraries,ble_release.pem4f
.libraries,ble_release.pem4f: package/cfg/ble_release_pem4f.xdl
	$(MAKE) -f C:\Users\Administrator\Downloads\SCDF\BLE\ble5_simple_peripheral_cc13x2r1lp_app\TOOLS/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\Administrator\Downloads\SCDF\BLE\ble5_simple_peripheral_cc13x2r1lp_app\TOOLS/src/makefile.libs clean


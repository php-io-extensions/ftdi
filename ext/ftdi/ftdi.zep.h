
extern zend_class_entry *ftdi_ftdi_ce;

ZEPHIR_INIT_CLASS(Ftdi_FTDI);

PHP_METHOD(Ftdi_FTDI, ftdiInit);
PHP_METHOD(Ftdi_FTDI, ftdiNew);
PHP_METHOD(Ftdi_FTDI, ftdiSetInterface);
PHP_METHOD(Ftdi_FTDI, ftdiDeinit);
PHP_METHOD(Ftdi_FTDI, ftdiFree);
PHP_METHOD(Ftdi_FTDI, ftdiSetUSBDev);
PHP_METHOD(Ftdi_FTDI, ftdiGetLibraryVersion);
PHP_METHOD(Ftdi_FTDI, ftdiUSBFindAll);
PHP_METHOD(Ftdi_FTDI, ftdiListFree);
PHP_METHOD(Ftdi_FTDI, ftdiListFree2);
PHP_METHOD(Ftdi_FTDI, ftdiUSBGetStrings);
PHP_METHOD(Ftdi_FTDI, ftdiUSBGetStrings2);
PHP_METHOD(Ftdi_FTDI, ftdiUSBOpenDev);
PHP_METHOD(Ftdi_FTDI, ftdiUSBOpen);
PHP_METHOD(Ftdi_FTDI, ftdiUSBOpenDesc);
PHP_METHOD(Ftdi_FTDI, ftdiUSBOpenDescIndex);
PHP_METHOD(Ftdi_FTDI, ftdiUSBOpenBusAddr);
PHP_METHOD(Ftdi_FTDI, ftdiUSBOpenString);
PHP_METHOD(Ftdi_FTDI, ftdiUSBClose);
PHP_METHOD(Ftdi_FTDI, ftdiUSBReset);
PHP_METHOD(Ftdi_FTDI, ftdiTCIFlush);
PHP_METHOD(Ftdi_FTDI, ftdiTCOFlush);
PHP_METHOD(Ftdi_FTDI, ftdiTCIOFlush);
PHP_METHOD(Ftdi_FTDI, ftdiUSBPurgeRXBuffer);
PHP_METHOD(Ftdi_FTDI, ftdiUSBPurgeTXBuffer);
PHP_METHOD(Ftdi_FTDI, ftdiUSBPurgeBuffers);
PHP_METHOD(Ftdi_FTDI, ftdiConvertBaudrateUTExport);
PHP_METHOD(Ftdi_FTDI, ftdiSetBaudrate);
PHP_METHOD(Ftdi_FTDI, ftdiSetLineProperty);
PHP_METHOD(Ftdi_FTDI, ftdiSetLineProperty2);
PHP_METHOD(Ftdi_FTDI, ftdiWriteData);
PHP_METHOD(Ftdi_FTDI, ftdiWriteDataSetChunksize);
PHP_METHOD(Ftdi_FTDI, ftdiWriteDataGetChunksize);
PHP_METHOD(Ftdi_FTDI, ftdiReadData);
PHP_METHOD(Ftdi_FTDI, ftdiReadDataSetChunksize);
PHP_METHOD(Ftdi_FTDI, ftdiReadDataGetChunksize);
PHP_METHOD(Ftdi_FTDI, ftdiSetBitmode);
PHP_METHOD(Ftdi_FTDI, ftdiWriteDataSubmit);
PHP_METHOD(Ftdi_FTDI, ftdiReadDataSubmit);
PHP_METHOD(Ftdi_FTDI, ftdiTransferDataDone);
PHP_METHOD(Ftdi_FTDI, ftdiTransferDataCancel);
PHP_METHOD(Ftdi_FTDI, ftdiDisableBitbang);
PHP_METHOD(Ftdi_FTDI, ftdiReadPins);
PHP_METHOD(Ftdi_FTDI, ftdiSetLatencyTimer);
PHP_METHOD(Ftdi_FTDI, ftdiSetTimeouts);
PHP_METHOD(Ftdi_FTDI, ftdiGetLatencyTimer);
PHP_METHOD(Ftdi_FTDI, ftdiPollModemStatus);
PHP_METHOD(Ftdi_FTDI, ftdiSetFlowCtrl);
PHP_METHOD(Ftdi_FTDI, ftdiSetFlowCtrlXonXoff);
PHP_METHOD(Ftdi_FTDI, ftdiSetDtr);
PHP_METHOD(Ftdi_FTDI, ftdiSetRts);
PHP_METHOD(Ftdi_FTDI, ftdiSetDtrRts);
PHP_METHOD(Ftdi_FTDI, ftdiSetEventChar);
PHP_METHOD(Ftdi_FTDI, ftdiSetErrorChar);
PHP_METHOD(Ftdi_FTDI, ftdiGetEeprom);
PHP_METHOD(Ftdi_FTDI, ftdiEepromInitDefaults);
PHP_METHOD(Ftdi_FTDI, ftdiEepromSetStrings);
PHP_METHOD(Ftdi_FTDI, ftdiEepromGetStrings);
PHP_METHOD(Ftdi_FTDI, ftdiEepromBuild);
PHP_METHOD(Ftdi_FTDI, ftdiEepromDecode);
PHP_METHOD(Ftdi_FTDI, ftdiGetEepromValue);
PHP_METHOD(Ftdi_FTDI, ftdiSetEepromValue);
PHP_METHOD(Ftdi_FTDI, ftdiGetEepromBuf);
PHP_METHOD(Ftdi_FTDI, ftdiSetEepromBuf);
PHP_METHOD(Ftdi_FTDI, ftdiSetEepromUserData);
PHP_METHOD(Ftdi_FTDI, setFT232HCbus);
PHP_METHOD(Ftdi_FTDI, ftdiReadEepromLocation);
PHP_METHOD(Ftdi_FTDI, ftdiReadEeprom);
PHP_METHOD(Ftdi_FTDI, ftdiReadChipId);
PHP_METHOD(Ftdi_FTDI, ftdiWriteEepromLocation);
PHP_METHOD(Ftdi_FTDI, ftdiWriteEeprom);
PHP_METHOD(Ftdi_FTDI, ftdiEraseEeprom);
PHP_METHOD(Ftdi_FTDI, ftdiGetErrorString);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiinit, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_ftdi_ftdi_ftdinew, 0, 0, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdisetinterface, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, iface, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdideinit, 0, 1, IS_VOID, 0)

	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdifree, 0, 1, IS_VOID, 0)

	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdisetusbdev, 0, 2, IS_VOID, 0)

	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, usbDevHandle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_ftdi_ftdi_ftdigetlibraryversion, 0, 0, Ftdi\\FTDIVersionInfo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiusbfindall, 0, 3, IS_ARRAY, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, vendor, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, product, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdilistfree, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, listHandle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdilistfree2, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, listHandle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiusbgetstrings, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, devHandle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiusbgetstrings2, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, devHandle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiusbopendev, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, devHandle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiusbopen, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, vendor, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, product, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiusbopendesc, 0, 5, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, vendor, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, product, IS_LONG, 0)
	ZEND_ARG_INFO(0, description)
	ZEND_ARG_INFO(0, serial)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiusbopendescindex, 0, 6, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, vendor, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, product, IS_LONG, 0)
	ZEND_ARG_INFO(0, description)
	ZEND_ARG_INFO(0, serial)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiusbopenbusaddr, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, bus, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, addr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiusbopenstring, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_INFO(0, description)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiusbclose, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiusbreset, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftditciflush, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftditcoflush, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftditcioflush, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiusbpurgerxbuffer, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiusbpurgetxbuffer, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiusbpurgebuffers, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiconvertbaudrateutexport, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, baudrate, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdisetbaudrate, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, baudrate, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdisetlineproperty, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, bits, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sbit, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, parity, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdisetlineproperty2, 0, 5, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, bits, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sbit, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, parity, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, breakType, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiwritedata, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiwritedatasetchunksize, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, chunksize, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiwritedatagetchunksize, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdireaddata, 0, 2, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdireaddatasetchunksize, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, chunksize, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdireaddatagetchunksize, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdisetbitmode, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, bitmask, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_ftdi_ftdi_ftdiwritedatasubmit, 0, 3, Ftdi\\FTDITransferControl, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_ftdi_ftdi_ftdireaddatasubmit, 0, 2, Ftdi\\FTDITransferControl, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftditransferdatadone, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, tc, Ftdi\\FTDITransferControl, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftditransferdatacancel, 0, 1, IS_VOID, 0)

	ZEND_ARG_OBJ_INFO(0, tc, Ftdi\\FTDITransferControl, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdidisablebitbang, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdireadpins, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdisetlatencytimer, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, latency, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdisettimeouts, 0, 3, IS_VOID, 0)

	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, readTimeout, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, writeTimeout, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdigetlatencytimer, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdipollmodemstatus, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdisetflowctrl, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, flowctrl, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdisetflowctrlxonxoff, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, xon, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, xoff, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdisetdtr, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, state, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdisetrts, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, state, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdisetdtrrts, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, dtr, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, rts, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiseteventchar, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, eventch, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, enable, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiseterrorchar, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, errorch, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, enable, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_ftdi_ftdi_ftdigeteeprom, 0, 1, Ftdi\\FTDIEeprom, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdieeprominitdefaults, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_INFO(0, manufacturer)
	ZEND_ARG_INFO(0, product)
	ZEND_ARG_INFO(0, serial)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdieepromsetstrings, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_INFO(0, manufacturer)
	ZEND_ARG_INFO(0, product)
	ZEND_ARG_INFO(0, serial)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdieepromgetstrings, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdieeprombuild, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdieepromdecode, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, verbose, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdigeteepromvalue, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, valueName, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiseteepromvalue, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, valueName, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdigeteeprombuf, 0, 2, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiseteeprombuf, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_INFO(0, buf)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiseteepromuserdata, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_INFO(0, buf)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_setft232hcbus, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, eeprom, Ftdi\\FTDIEeprom, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdireadeepromlocation, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, eepromAddr, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdireadeeprom, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdireadchipid, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiwriteeepromlocation, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
	ZEND_ARG_TYPE_INFO(0, eepromAddr, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, eepromVal, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdiwriteeeprom, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdieraseeeprom, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdi_ftdigeterrorstring, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, ftdi, Ftdi\\FTDIContext, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ftdi_ftdi_method_entry) {
	PHP_ME(Ftdi_FTDI, ftdiInit, arginfo_ftdi_ftdi_ftdiinit, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiNew, arginfo_ftdi_ftdi_ftdinew, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetInterface, arginfo_ftdi_ftdi_ftdisetinterface, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiDeinit, arginfo_ftdi_ftdi_ftdideinit, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiFree, arginfo_ftdi_ftdi_ftdifree, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetUSBDev, arginfo_ftdi_ftdi_ftdisetusbdev, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiGetLibraryVersion, arginfo_ftdi_ftdi_ftdigetlibraryversion, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiUSBFindAll, arginfo_ftdi_ftdi_ftdiusbfindall, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiListFree, arginfo_ftdi_ftdi_ftdilistfree, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiListFree2, arginfo_ftdi_ftdi_ftdilistfree2, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiUSBGetStrings, arginfo_ftdi_ftdi_ftdiusbgetstrings, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiUSBGetStrings2, arginfo_ftdi_ftdi_ftdiusbgetstrings2, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiUSBOpenDev, arginfo_ftdi_ftdi_ftdiusbopendev, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiUSBOpen, arginfo_ftdi_ftdi_ftdiusbopen, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiUSBOpenDesc, arginfo_ftdi_ftdi_ftdiusbopendesc, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiUSBOpenDescIndex, arginfo_ftdi_ftdi_ftdiusbopendescindex, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiUSBOpenBusAddr, arginfo_ftdi_ftdi_ftdiusbopenbusaddr, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiUSBOpenString, arginfo_ftdi_ftdi_ftdiusbopenstring, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiUSBClose, arginfo_ftdi_ftdi_ftdiusbclose, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiUSBReset, arginfo_ftdi_ftdi_ftdiusbreset, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiTCIFlush, arginfo_ftdi_ftdi_ftditciflush, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiTCOFlush, arginfo_ftdi_ftdi_ftditcoflush, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiTCIOFlush, arginfo_ftdi_ftdi_ftditcioflush, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiUSBPurgeRXBuffer, arginfo_ftdi_ftdi_ftdiusbpurgerxbuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiUSBPurgeTXBuffer, arginfo_ftdi_ftdi_ftdiusbpurgetxbuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiUSBPurgeBuffers, arginfo_ftdi_ftdi_ftdiusbpurgebuffers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiConvertBaudrateUTExport, arginfo_ftdi_ftdi_ftdiconvertbaudrateutexport, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetBaudrate, arginfo_ftdi_ftdi_ftdisetbaudrate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetLineProperty, arginfo_ftdi_ftdi_ftdisetlineproperty, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetLineProperty2, arginfo_ftdi_ftdi_ftdisetlineproperty2, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiWriteData, arginfo_ftdi_ftdi_ftdiwritedata, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiWriteDataSetChunksize, arginfo_ftdi_ftdi_ftdiwritedatasetchunksize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiWriteDataGetChunksize, arginfo_ftdi_ftdi_ftdiwritedatagetchunksize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiReadData, arginfo_ftdi_ftdi_ftdireaddata, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiReadDataSetChunksize, arginfo_ftdi_ftdi_ftdireaddatasetchunksize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiReadDataGetChunksize, arginfo_ftdi_ftdi_ftdireaddatagetchunksize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetBitmode, arginfo_ftdi_ftdi_ftdisetbitmode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiWriteDataSubmit, arginfo_ftdi_ftdi_ftdiwritedatasubmit, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiReadDataSubmit, arginfo_ftdi_ftdi_ftdireaddatasubmit, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiTransferDataDone, arginfo_ftdi_ftdi_ftditransferdatadone, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiTransferDataCancel, arginfo_ftdi_ftdi_ftditransferdatacancel, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiDisableBitbang, arginfo_ftdi_ftdi_ftdidisablebitbang, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiReadPins, arginfo_ftdi_ftdi_ftdireadpins, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetLatencyTimer, arginfo_ftdi_ftdi_ftdisetlatencytimer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetTimeouts, arginfo_ftdi_ftdi_ftdisettimeouts, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiGetLatencyTimer, arginfo_ftdi_ftdi_ftdigetlatencytimer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiPollModemStatus, arginfo_ftdi_ftdi_ftdipollmodemstatus, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetFlowCtrl, arginfo_ftdi_ftdi_ftdisetflowctrl, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetFlowCtrlXonXoff, arginfo_ftdi_ftdi_ftdisetflowctrlxonxoff, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetDtr, arginfo_ftdi_ftdi_ftdisetdtr, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetRts, arginfo_ftdi_ftdi_ftdisetrts, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetDtrRts, arginfo_ftdi_ftdi_ftdisetdtrrts, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetEventChar, arginfo_ftdi_ftdi_ftdiseteventchar, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetErrorChar, arginfo_ftdi_ftdi_ftdiseterrorchar, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiGetEeprom, arginfo_ftdi_ftdi_ftdigeteeprom, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiEepromInitDefaults, arginfo_ftdi_ftdi_ftdieeprominitdefaults, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiEepromSetStrings, arginfo_ftdi_ftdi_ftdieepromsetstrings, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiEepromGetStrings, arginfo_ftdi_ftdi_ftdieepromgetstrings, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiEepromBuild, arginfo_ftdi_ftdi_ftdieeprombuild, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiEepromDecode, arginfo_ftdi_ftdi_ftdieepromdecode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiGetEepromValue, arginfo_ftdi_ftdi_ftdigeteepromvalue, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetEepromValue, arginfo_ftdi_ftdi_ftdiseteepromvalue, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiGetEepromBuf, arginfo_ftdi_ftdi_ftdigeteeprombuf, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetEepromBuf, arginfo_ftdi_ftdi_ftdiseteeprombuf, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiSetEepromUserData, arginfo_ftdi_ftdi_ftdiseteepromuserdata, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, setFT232HCbus, arginfo_ftdi_ftdi_setft232hcbus, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiReadEepromLocation, arginfo_ftdi_ftdi_ftdireadeepromlocation, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiReadEeprom, arginfo_ftdi_ftdi_ftdireadeeprom, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiReadChipId, arginfo_ftdi_ftdi_ftdireadchipid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiWriteEepromLocation, arginfo_ftdi_ftdi_ftdiwriteeepromlocation, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiWriteEeprom, arginfo_ftdi_ftdi_ftdiwriteeeprom, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiEraseEeprom, arginfo_ftdi_ftdi_ftdieraseeeprom, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Ftdi_FTDI, ftdiGetErrorString, arginfo_ftdi_ftdi_ftdigeterrorstring, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};

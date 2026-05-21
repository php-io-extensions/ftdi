<?php

namespace Ftdi;

use Ftdi\FTDIContext;
use Ftdi\FTDIEeprom;
use Ftdi\FTDITransferControl;
use Ftdi\FTDIVersionInfo;

class FTDI
{


    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiInit(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * Allocate a new libftdi1 context and return it as a hydrated FTDIContext DTO.
     *
     * Wraps ftdi_new(). On success the returned object's handle carries the
     * ftdi_context pointer as an opaque integer; pass it to subsequent calls.
     * Check handle >= 0 before use -- a value of -1 means ftdi_new() failed.
     *
     * @return <FTDIContext>
     * @return FTDIContext
     */
    public static function ftdiNew(): FTDIContext
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $iface
     * @return int
     */
    public static function ftdiSetInterface(\Ftdi\FTDIContext $ftdi, int $iface): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return void
     */
    public static function ftdiDeinit(\Ftdi\FTDIContext $ftdi): void
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return void
     */
    public static function ftdiFree(\Ftdi\FTDIContext $ftdi): void
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $usbDevHandle
     * @return void
     */
    public static function ftdiSetUSBDev(\Ftdi\FTDIContext $ftdi, int $usbDevHandle): void
    {
    }

    /**
     * Return libftdi1 library version information without requiring a device.
     *
     * Wraps ftdi_get_library_version() which returns a struct by value --
     * no ftdi_context is needed.
     *
     * @return <FTDIVersionInfo>
     * @return FTDIVersionInfo
     */
    public static function ftdiGetLibraryVersion(): FTDIVersionInfo
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $vendor
     * @param int $product
     * @return array
     */
    public static function ftdiUSBFindAll(\Ftdi\FTDIContext $ftdi, int $vendor, int $product): array
    {
    }

    /**
     * @param int $listHandle
     * @return void
     */
    public static function ftdiListFree(int $listHandle): void
    {
    }

    /**
     * @param int $listHandle
     * @return void
     */
    public static function ftdiListFree2(int $listHandle): void
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $devHandle
     * @return array
     */
    public static function ftdiUSBGetStrings(\Ftdi\FTDIContext $ftdi, int $devHandle): array
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $devHandle
     * @return array
     */
    public static function ftdiUSBGetStrings2(\Ftdi\FTDIContext $ftdi, int $devHandle): array
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $devHandle
     * @return int
     */
    public static function ftdiUSBOpenDev(\Ftdi\FTDIContext $ftdi, int $devHandle): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $vendor
     * @param int $product
     * @return int
     */
    public static function ftdiUSBOpen(\Ftdi\FTDIContext $ftdi, int $vendor, int $product): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $vendor
     * @param int $product
     * @param mixed $description
     * @param mixed $serial
     * @return int
     */
    public static function ftdiUSBOpenDesc(\Ftdi\FTDIContext $ftdi, int $vendor, int $product, $description, $serial): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $vendor
     * @param int $product
     * @param mixed $description
     * @param mixed $serial
     * @param int $index
     * @return int
     */
    public static function ftdiUSBOpenDescIndex(\Ftdi\FTDIContext $ftdi, int $vendor, int $product, $description, $serial, int $index): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $bus
     * @param int $addr
     * @return int
     */
    public static function ftdiUSBOpenBusAddr(\Ftdi\FTDIContext $ftdi, int $bus, int $addr): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param mixed $description
     * @return int
     */
    public static function ftdiUSBOpenString(\Ftdi\FTDIContext $ftdi, $description): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiUSBClose(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiUSBReset(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiTCIFlush(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiTCOFlush(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiTCIOFlush(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiUSBPurgeRXBuffer(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiUSBPurgeTXBuffer(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiUSBPurgeBuffers(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param int $baudrate
     * @param \Ftdi\FTDIContext $ftdi
     * @return array
     */
    public static function ftdiConvertBaudrateUTExport(int $baudrate, \Ftdi\FTDIContext $ftdi): array
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $baudrate
     * @return int
     */
    public static function ftdiSetBaudrate(\Ftdi\FTDIContext $ftdi, int $baudrate): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $bits
     * @param int $sbit
     * @param int $parity
     * @return int
     */
    public static function ftdiSetLineProperty(\Ftdi\FTDIContext $ftdi, int $bits, int $sbit, int $parity): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $bits
     * @param int $sbit
     * @param int $parity
     * @param int $breakType
     * @return int
     */
    public static function ftdiSetLineProperty2(\Ftdi\FTDIContext $ftdi, int $bits, int $sbit, int $parity, int $breakType): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param mixed $data
     * @param int $size
     * @return int
     */
    public static function ftdiWriteData(\Ftdi\FTDIContext $ftdi, $data, int $size): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $chunksize
     * @return int
     */
    public static function ftdiWriteDataSetChunksize(\Ftdi\FTDIContext $ftdi, int $chunksize): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiWriteDataGetChunksize(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $size
     * @return string
     */
    public static function ftdiReadData(\Ftdi\FTDIContext $ftdi, int $size): string
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $chunksize
     * @return int
     */
    public static function ftdiReadDataSetChunksize(\Ftdi\FTDIContext $ftdi, int $chunksize): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiReadDataGetChunksize(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $bitmask
     * @param int $mode
     * @return int
     */
    public static function ftdiSetBitmode(\Ftdi\FTDIContext $ftdi, int $bitmask, int $mode): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param mixed $data
     * @param int $size
     * @return FTDITransferControl
     */
    public static function ftdiWriteDataSubmit(\Ftdi\FTDIContext $ftdi, $data, int $size): FTDITransferControl
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $size
     * @return FTDITransferControl
     */
    public static function ftdiReadDataSubmit(\Ftdi\FTDIContext $ftdi, int $size): FTDITransferControl
    {
    }

    /**
     * @param \Ftdi\FTDITransferControl $tc
     * @return int
     */
    public static function ftdiTransferDataDone(\Ftdi\FTDITransferControl $tc): int
    {
    }

    /**
     * @param \Ftdi\FTDITransferControl $tc
     * @return void
     */
    public static function ftdiTransferDataCancel(\Ftdi\FTDITransferControl $tc): void
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiDisableBitbang(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiReadPins(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $latency
     * @return int
     */
    public static function ftdiSetLatencyTimer(\Ftdi\FTDIContext $ftdi, int $latency): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $readTimeout
     * @param int $writeTimeout
     * @return void
     */
    public static function ftdiSetTimeouts(\Ftdi\FTDIContext $ftdi, int $readTimeout, int $writeTimeout): void
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiGetLatencyTimer(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiPollModemStatus(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $flowctrl
     * @return int
     */
    public static function ftdiSetFlowCtrl(\Ftdi\FTDIContext $ftdi, int $flowctrl): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $xon
     * @param int $xoff
     * @return int
     */
    public static function ftdiSetFlowCtrlXonXoff(\Ftdi\FTDIContext $ftdi, int $xon, int $xoff): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $state
     * @return int
     */
    public static function ftdiSetDtr(\Ftdi\FTDIContext $ftdi, int $state): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $state
     * @return int
     */
    public static function ftdiSetRts(\Ftdi\FTDIContext $ftdi, int $state): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $dtr
     * @param int $rts
     * @return int
     */
    public static function ftdiSetDtrRts(\Ftdi\FTDIContext $ftdi, int $dtr, int $rts): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $eventch
     * @param int $enable
     * @return int
     */
    public static function ftdiSetEventChar(\Ftdi\FTDIContext $ftdi, int $eventch, int $enable): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $errorch
     * @param int $enable
     * @return int
     */
    public static function ftdiSetErrorChar(\Ftdi\FTDIContext $ftdi, int $errorch, int $enable): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return FTDIEeprom
     */
    public static function ftdiGetEeprom(\Ftdi\FTDIContext $ftdi): FTDIEeprom
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param mixed $manufacturer
     * @param mixed $product
     * @param mixed $serial
     * @return int
     */
    public static function ftdiEepromInitDefaults(\Ftdi\FTDIContext $ftdi, $manufacturer, $product, $serial): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param mixed $manufacturer
     * @param mixed $product
     * @param mixed $serial
     * @return int
     */
    public static function ftdiEepromSetStrings(\Ftdi\FTDIContext $ftdi, $manufacturer, $product, $serial): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return array
     */
    public static function ftdiEepromGetStrings(\Ftdi\FTDIContext $ftdi): array
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiEepromBuild(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $verbose
     * @return int
     */
    public static function ftdiEepromDecode(\Ftdi\FTDIContext $ftdi, int $verbose): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $valueName
     * @return int
     */
    public static function ftdiGetEepromValue(\Ftdi\FTDIContext $ftdi, int $valueName): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $valueName
     * @param int $value
     * @return int
     */
    public static function ftdiSetEepromValue(\Ftdi\FTDIContext $ftdi, int $valueName, int $value): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $size
     * @return string
     */
    public static function ftdiGetEepromBuf(\Ftdi\FTDIContext $ftdi, int $size): string
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param mixed $buf
     * @return int
     */
    public static function ftdiSetEepromBuf(\Ftdi\FTDIContext $ftdi, $buf): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param mixed $buf
     * @return int
     */
    public static function ftdiSetEepromUserData(\Ftdi\FTDIContext $ftdi, $buf): int
    {
    }

    /**
     * Encode FT232H CBUS EEPROM bytes via libftdi's set_ft232h_cbus.
     * Requires a decoded EEPROM (ftdi->eeprom); returns the five raw bytes
     * written at offsets 0x18–0x1c of the EEPROM image buffer, or empty string
     * if the context or eeprom pointer is missing.
     *
     * @param \Ftdi\FTDIEeprom $eeprom
     * @return string
     */
    public static function setFT232HCbus(\Ftdi\FTDIEeprom $eeprom): string
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $eepromAddr
     * @return int
     */
    public static function ftdiReadEepromLocation(\Ftdi\FTDIContext $ftdi, int $eepromAddr): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiReadEeprom(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return array
     */
    public static function ftdiReadChipId(\Ftdi\FTDIContext $ftdi): array
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @param int $eepromAddr
     * @param int $eepromVal
     * @return int
     */
    public static function ftdiWriteEepromLocation(\Ftdi\FTDIContext $ftdi, int $eepromAddr, int $eepromVal): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiWriteEeprom(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return int
     */
    public static function ftdiEraseEeprom(\Ftdi\FTDIContext $ftdi): int
    {
    }

    /**
     * @param \Ftdi\FTDIContext $ftdi
     * @return string
     */
    public static function ftdiGetErrorString(\Ftdi\FTDIContext $ftdi): string
    {
    }
}

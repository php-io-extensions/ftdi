<?php

/**
 * @generate-class-entries
 */

namespace Ftdi {

    /**
     * A libftdi context (struct ftdi_context). ftdi_new() creates one; ftdi_free() or
     * garbage collection releases it. Reading these properties reads the struct live:
     *
     * @property-read int $chipType             type
     * @property-read int $usbReadTimeout       usb_read_timeout (ms)
     * @property-read int $usbWriteTimeout      usb_write_timeout (ms)
     * @property-read int $interfaceIndex       index
     * @property-read int $baudrate
     * @property-read int $bitbangEnabled       bitbang_enabled
     * @property-read int $bitbangMode          bitbang_mode
     * @property-read int $channel              interface
     * @property-read int $inEndpoint           in_ep
     * @property-read int $outEndpoint          out_ep
     * @property-read int $readBufferChunkSize  readbuffer_chunksize
     * @property-read int $writeBufferChunkSize writebuffer_chunksize
     * @property-read int $maxPacketSize        max_packet_size
     * @property-read int $moduleDetachMode     module_detach_mode
     * @property-read string $errorStr          error_str
     * @strict-properties
     * @not-serializable
     */
    final class FTDIContext
    {
        private function __construct() {}

        public function toArray(): array {}
    }

    /**
     * One USB device ftdi_usb_find_all() listed (struct libusb_device), referenced for
     * as long as this object lives and its context is initialised.
     * @strict-properties
     * @not-serializable
     */
    final class FTDIDevice
    {
        private function __construct() {}
    }

    /**
     * An asynchronous transfer (struct ftdi_transfer_control) from ftdi_write_data_submit()
     * or ftdi_read_data_submit(). It owns the transfer's buffer until done or cancelled;
     * an object released while its transfer is pending cancels the transfer first.
     *
     * @property-read int $completed  1 once the transfer finished, was collected or was cancelled
     * @property-read int $size       bytes requested
     * @property-read int $offset     bytes moved so far
     * @strict-properties
     * @not-serializable
     */
    final class FTDITransferControl
    {
        private function __construct() {}

        public function toArray(): array {}
    }

    /** ftdi_get_library_version() */
    final class FTDIVersionInfo
    {
        public readonly int $major;
        public readonly int $minor;
        public readonly int $micro;
        public readonly string $versionStr;
        public readonly string $snapshotStr;

        public function toArray(): array {}
    }

    /**
     * A snapshot of the context's EEPROM image: every enum ftdi_eeprom_value through
     * ftdi_get_eeprom_value() (0 where the chip type has no such value), and the strings
     * through ftdi_eeprom_get_strings(). Meaningful after ftdi_read_eeprom() and
     * ftdi_eeprom_decode().
     */
    final class FTDIEeprom
    {
    public readonly int $vendorId;
    public readonly int $productId;
    public readonly int $selfPowered;
    public readonly int $remoteWakeup;
    public readonly int $isNotPnp;
    public readonly int $suspendDbus7;
    public readonly int $inIsIsochronous;
    public readonly int $outIsIsochronous;
    public readonly int $suspendPullDowns;
    public readonly int $useSerial;
    public readonly int $usbVersion;
    public readonly int $useUsbVersion;
    public readonly int $maxPower;
    public readonly int $channelAType;
    public readonly int $channelBType;
    public readonly int $channelADriver;
    public readonly int $channelBDriver;
    public readonly int $cbusFunction0;
    public readonly int $cbusFunction1;
    public readonly int $cbusFunction2;
    public readonly int $cbusFunction3;
    public readonly int $cbusFunction4;
    public readonly int $cbusFunction5;
    public readonly int $cbusFunction6;
    public readonly int $cbusFunction7;
    public readonly int $cbusFunction8;
    public readonly int $cbusFunction9;
    public readonly int $highCurrent;
    public readonly int $highCurrentA;
    public readonly int $highCurrentB;
    public readonly int $invert;
    public readonly int $group0Drive;
    public readonly int $group0Schmitt;
    public readonly int $group0Slew;
    public readonly int $group1Drive;
    public readonly int $group1Schmitt;
    public readonly int $group1Slew;
    public readonly int $group2Drive;
    public readonly int $group2Schmitt;
    public readonly int $group2Slew;
    public readonly int $group3Drive;
    public readonly int $group3Schmitt;
    public readonly int $group3Slew;
    public readonly int $chipSize;
    public readonly int $chipType;
    public readonly int $powerSave;
    public readonly int $clockPolarity;
    public readonly int $dataOrder;
    public readonly int $flowControl;
    public readonly int $channelCDriver;
    public readonly int $channelDDriver;
    public readonly int $channelARs485;
    public readonly int $channelBRs485;
    public readonly int $channelCRs485;
    public readonly int $channelDRs485;
    public readonly int $releaseNumber;
    public readonly int $externalOscillator;
    public readonly int $userDataAddr;
        public readonly string $manufacturer;
        public readonly string $product;
        public readonly string $serial;

        public function toArray(): array {}
    }

    /** USB vendor IDs of FTDI devices */
    enum FtdiVendorId: int
    {
        case FTDI = 0x0403;
    }

    /** USB product IDs of FTDI devices */
    enum FtdiProductId: int
    {
        case FT232R = 0x6001;
        case FT2232H = 0x6010;
        case FT4232H = 0x6011;
        case FT232H = 0x6014;
        case FT230X = 0x6015;
        case FT4232HP = 0x6043;
        case FT4232HA = 0x6048;
    }
}

namespace {

    /* Context lifecycle */

    function ftdi_new(): ?\Ftdi\FTDIContext {}

    function ftdi_init(\Ftdi\FTDIContext $ftdi): int {}

    function ftdi_deinit(\Ftdi\FTDIContext $ftdi): void {}

    function ftdi_free(\Ftdi\FTDIContext $ftdi): void {}

    function ftdi_set_interface(\Ftdi\FTDIContext $ftdi, int $iface): int {}

    function ftdi_get_library_version(): \Ftdi\FTDIVersionInfo {}

    function ftdi_get_error_string(\Ftdi\FTDIContext $ftdi): string {}

    /* Finding and opening devices */

    /** @return array{count: int, devices: array<int, \Ftdi\FTDIDevice>} */
    function ftdi_usb_find_all(\Ftdi\FTDIContext $ftdi, int $vendor, int $product): array {}

    /** @return array{result: int, manufacturer: string, description: string, serial: string} */
    function ftdi_usb_get_strings(\Ftdi\FTDIContext $ftdi, \Ftdi\FTDIDevice $dev): array {}

    /** @return array{result: int, manufacturer: string, description: string, serial: string} */
    function ftdi_usb_get_strings2(\Ftdi\FTDIContext $ftdi, \Ftdi\FTDIDevice $dev): array {}

    function ftdi_usb_open_dev(\Ftdi\FTDIContext $ftdi, \Ftdi\FTDIDevice $dev): int {}

    function ftdi_usb_open(\Ftdi\FTDIContext $ftdi, int $vendor, int $product): int {}

    function ftdi_usb_open_desc(\Ftdi\FTDIContext $ftdi, int $vendor, int $product, string $description, string $serial): int {}

    function ftdi_usb_open_desc_index(\Ftdi\FTDIContext $ftdi, int $vendor, int $product, string $description, string $serial, int $index): int {}

    function ftdi_usb_open_bus_addr(\Ftdi\FTDIContext $ftdi, int $bus, int $addr): int {}

    function ftdi_usb_open_string(\Ftdi\FTDIContext $ftdi, string $description): int {}

    function ftdi_usb_close(\Ftdi\FTDIContext $ftdi): int {}

    function ftdi_usb_reset(\Ftdi\FTDIContext $ftdi): int {}

    function ftdi_tci_flush(\Ftdi\FTDIContext $ftdi): int {}

    function ftdi_tco_flush(\Ftdi\FTDIContext $ftdi): int {}

    function ftdi_tcio_flush(\Ftdi\FTDIContext $ftdi): int {}

    function ftdi_usb_purge_rx_buffer(\Ftdi\FTDIContext $ftdi): int {}

    function ftdi_usb_purge_tx_buffer(\Ftdi\FTDIContext $ftdi): int {}

    function ftdi_usb_purge_buffers(\Ftdi\FTDIContext $ftdi): int {}

    /* Line settings */

    /** @return array{result: int, value: int, index: int} */
    function ftdi_convert_baudrate_ut_export(int $baudrate, \Ftdi\FTDIContext $ftdi): array {}

    function ftdi_set_baudrate(\Ftdi\FTDIContext $ftdi, int $baudrate): int {}

    function ftdi_set_line_property(\Ftdi\FTDIContext $ftdi, int $bits, int $sbit, int $parity): int {}

    function ftdi_set_line_property2(\Ftdi\FTDIContext $ftdi, int $bits, int $sbit, int $parity, int $breakType): int {}

    function ftdi_set_bitmode(\Ftdi\FTDIContext $ftdi, int $bitmask, int $mode): int {}

    function ftdi_disable_bitbang(\Ftdi\FTDIContext $ftdi): int {}

    function ftdi_read_pins(\Ftdi\FTDIContext $ftdi): int {}

    function ftdi_set_latency_timer(\Ftdi\FTDIContext $ftdi, int $latency): int {}

    function ftdi_get_latency_timer(\Ftdi\FTDIContext $ftdi): int {}

    function ftdi_set_timeouts(\Ftdi\FTDIContext $ftdi, int $readTimeout, int $writeTimeout): void {}

    function ftdi_poll_modem_status(\Ftdi\FTDIContext $ftdi): int {}

    function ftdi_setflowctrl(\Ftdi\FTDIContext $ftdi, int $flowctrl): int {}

    function ftdi_setflowctrl_xonxoff(\Ftdi\FTDIContext $ftdi, int $xon, int $xoff): int {}

    function ftdi_setdtr(\Ftdi\FTDIContext $ftdi, int $state): int {}

    function ftdi_setrts(\Ftdi\FTDIContext $ftdi, int $state): int {}

    function ftdi_setdtr_rts(\Ftdi\FTDIContext $ftdi, int $dtr, int $rts): int {}

    function ftdi_set_event_char(\Ftdi\FTDIContext $ftdi, int $eventch, int $enable): int {}

    function ftdi_set_error_char(\Ftdi\FTDIContext $ftdi, int $errorch, int $enable): int {}

    /* Synchronous data */

    function ftdi_write_data(\Ftdi\FTDIContext $ftdi, string $data, int $size): int {}

    function ftdi_read_data(\Ftdi\FTDIContext $ftdi, int $size): string|false {}

    function ftdi_write_data_set_chunksize(\Ftdi\FTDIContext $ftdi, int $chunksize): int {}

    function ftdi_write_data_get_chunksize(\Ftdi\FTDIContext $ftdi): int {}

    function ftdi_read_data_set_chunksize(\Ftdi\FTDIContext $ftdi, int $chunksize): int {}

    function ftdi_read_data_get_chunksize(\Ftdi\FTDIContext $ftdi): int {}

    /* Asynchronous data and the libusb event pump */

    function ftdi_write_data_submit(\Ftdi\FTDIContext $ftdi, string $data, int $size): ?\Ftdi\FTDITransferControl {}

    function ftdi_read_data_submit(\Ftdi\FTDIContext $ftdi, int $size): ?\Ftdi\FTDITransferControl {}

    function ftdi_transfer_data_done(\Ftdi\FTDITransferControl $tc): int {}

    function ftdi_transfer_read_done(\Ftdi\FTDITransferControl $tc): string|false {}

    function ftdi_transfer_data_cancel(\Ftdi\FTDITransferControl $tc): void {}

    function ftdi_transfer_completed(\Ftdi\FTDITransferControl $tc): int {}

    /** @return array<int, array{fd: int, events: int}> */
    function ftdi_get_pollfds(\Ftdi\FTDIContext $ftdi): array {}

    function ftdi_pollfds_handle_timeouts(\Ftdi\FTDIContext $ftdi): int {}

    /** @return array{result: int, usec: int} */
    function ftdi_get_next_timeout(\Ftdi\FTDIContext $ftdi): array {}

    function ftdi_handle_events_timeout(\Ftdi\FTDIContext $ftdi, int $timeout_us): int {}

    /* EEPROM */

    function ftdi_get_eeprom(\Ftdi\FTDIContext $ftdi): \Ftdi\FTDIEeprom {}

    function ftdi_eeprom_initdefaults(\Ftdi\FTDIContext $ftdi, string $manufacturer, string $product, string $serial): int {}

    function ftdi_eeprom_set_strings(\Ftdi\FTDIContext $ftdi, string $manufacturer, string $product, string $serial): int {}

    /** @return array{manufacturer: string, product: string, serial: string} */
    function ftdi_eeprom_get_strings(\Ftdi\FTDIContext $ftdi): array {}

    function ftdi_eeprom_build(\Ftdi\FTDIContext $ftdi): int {}

    function ftdi_eeprom_decode(\Ftdi\FTDIContext $ftdi, int $verbose): int {}

    function ftdi_get_eeprom_value(\Ftdi\FTDIContext $ftdi, int $valueName): int {}

    function ftdi_set_eeprom_value(\Ftdi\FTDIContext $ftdi, int $valueName, int $value): int {}

    function ftdi_get_eeprom_buf(\Ftdi\FTDIContext $ftdi, int $size): string|false {}

    function ftdi_set_eeprom_buf(\Ftdi\FTDIContext $ftdi, string $buf): int {}

    function ftdi_set_eeprom_user_data(\Ftdi\FTDIContext $ftdi, string $buf): int {}

    function ftdi_set_ft232h_cbus(\Ftdi\FTDIContext $ftdi): string {}

    function ftdi_read_eeprom_location(\Ftdi\FTDIContext $ftdi, int $addr): int {}

    function ftdi_read_eeprom(\Ftdi\FTDIContext $ftdi): int {}

    function ftdi_read_chip_id(\Ftdi\FTDIContext $ftdi, ?int &$chip_id): int {}

    function ftdi_write_eeprom_location(\Ftdi\FTDIContext $ftdi, int $addr, int $val): int {}

    function ftdi_write_eeprom(\Ftdi\FTDIContext $ftdi): int {}

    function ftdi_erase_eeprom(\Ftdi\FTDIContext $ftdi): int {}

    /* enum ftdi_chip_type */

    /**
     * @var int
     * @cvalue TYPE_AM
     */
    const TYPE_AM = UNKNOWN;

    /**
     * @var int
     * @cvalue TYPE_BM
     */
    const TYPE_BM = UNKNOWN;

    /**
     * @var int
     * @cvalue TYPE_2232C
     */
    const TYPE_2232C = UNKNOWN;

    /**
     * @var int
     * @cvalue TYPE_R
     */
    const TYPE_R = UNKNOWN;

    /**
     * @var int
     * @cvalue TYPE_2232H
     */
    const TYPE_2232H = UNKNOWN;

    /**
     * @var int
     * @cvalue TYPE_4232H
     */
    const TYPE_4232H = UNKNOWN;

    /**
     * @var int
     * @cvalue TYPE_232H
     */
    const TYPE_232H = UNKNOWN;

    /**
     * @var int
     * @cvalue TYPE_230X
     */
    const TYPE_230X = UNKNOWN;

    /* enum ftdi_parity_type */

    /**
     * @var int
     * @cvalue NONE
     */
    const NONE = UNKNOWN;

    /**
     * @var int
     * @cvalue ODD
     */
    const ODD = UNKNOWN;

    /**
     * @var int
     * @cvalue EVEN
     */
    const EVEN = UNKNOWN;

    /**
     * @var int
     * @cvalue MARK
     */
    const MARK = UNKNOWN;

    /**
     * @var int
     * @cvalue SPACE
     */
    const SPACE = UNKNOWN;

    /* enum ftdi_stopbits_type */

    /**
     * @var int
     * @cvalue STOP_BIT_1
     */
    const STOP_BIT_1 = UNKNOWN;

    /**
     * @var int
     * @cvalue STOP_BIT_15
     */
    const STOP_BIT_15 = UNKNOWN;

    /**
     * @var int
     * @cvalue STOP_BIT_2
     */
    const STOP_BIT_2 = UNKNOWN;

    /* enum ftdi_bits_type */

    /**
     * @var int
     * @cvalue BITS_7
     */
    const BITS_7 = UNKNOWN;

    /**
     * @var int
     * @cvalue BITS_8
     */
    const BITS_8 = UNKNOWN;

    /* enum ftdi_break_type */

    /**
     * @var int
     * @cvalue BREAK_OFF
     */
    const BREAK_OFF = UNKNOWN;

    /**
     * @var int
     * @cvalue BREAK_ON
     */
    const BREAK_ON = UNKNOWN;

    /* enum ftdi_mpsse_mode */

    /**
     * @var int
     * @cvalue BITMODE_RESET
     */
    const BITMODE_RESET = UNKNOWN;

    /**
     * @var int
     * @cvalue BITMODE_BITBANG
     */
    const BITMODE_BITBANG = UNKNOWN;

    /**
     * @var int
     * @cvalue BITMODE_MPSSE
     */
    const BITMODE_MPSSE = UNKNOWN;

    /**
     * @var int
     * @cvalue BITMODE_SYNCBB
     */
    const BITMODE_SYNCBB = UNKNOWN;

    /**
     * @var int
     * @cvalue BITMODE_MCU
     */
    const BITMODE_MCU = UNKNOWN;

    /**
     * @var int
     * @cvalue BITMODE_OPTO
     */
    const BITMODE_OPTO = UNKNOWN;

    /**
     * @var int
     * @cvalue BITMODE_CBUS
     */
    const BITMODE_CBUS = UNKNOWN;

    /**
     * @var int
     * @cvalue BITMODE_SYNCFF
     */
    const BITMODE_SYNCFF = UNKNOWN;

    /**
     * @var int
     * @cvalue BITMODE_FT1284
     */
    const BITMODE_FT1284 = UNKNOWN;

    /* enum ftdi_interface */

    /**
     * @var int
     * @cvalue INTERFACE_ANY
     */
    const INTERFACE_ANY = UNKNOWN;

    /**
     * @var int
     * @cvalue INTERFACE_A
     */
    const INTERFACE_A = UNKNOWN;

    /**
     * @var int
     * @cvalue INTERFACE_B
     */
    const INTERFACE_B = UNKNOWN;

    /**
     * @var int
     * @cvalue INTERFACE_C
     */
    const INTERFACE_C = UNKNOWN;

    /**
     * @var int
     * @cvalue INTERFACE_D
     */
    const INTERFACE_D = UNKNOWN;

    /* enum ftdi_module_detach_mode */

    /**
     * @var int
     * @cvalue AUTO_DETACH_SIO_MODULE
     */
    const AUTO_DETACH_SIO_MODULE = UNKNOWN;

    /**
     * @var int
     * @cvalue DONT_DETACH_SIO_MODULE
     */
    const DONT_DETACH_SIO_MODULE = UNKNOWN;

    /**
     * @var int
     * @cvalue AUTO_DETACH_REATACH_SIO_MODULE
     */
    const AUTO_DETACH_REATACH_SIO_MODULE = UNKNOWN;

    /* enum ftdi_eeprom_value */

    /**
     * @var int
     * @cvalue VENDOR_ID
     */
    const VENDOR_ID = UNKNOWN;

    /**
     * @var int
     * @cvalue PRODUCT_ID
     */
    const PRODUCT_ID = UNKNOWN;

    /**
     * @var int
     * @cvalue SELF_POWERED
     */
    const SELF_POWERED = UNKNOWN;

    /**
     * @var int
     * @cvalue REMOTE_WAKEUP
     */
    const REMOTE_WAKEUP = UNKNOWN;

    /**
     * @var int
     * @cvalue IS_NOT_PNP
     */
    const IS_NOT_PNP = UNKNOWN;

    /**
     * @var int
     * @cvalue SUSPEND_DBUS7
     */
    const SUSPEND_DBUS7 = UNKNOWN;

    /**
     * @var int
     * @cvalue IN_IS_ISOCHRONOUS
     */
    const IN_IS_ISOCHRONOUS = UNKNOWN;

    /**
     * @var int
     * @cvalue OUT_IS_ISOCHRONOUS
     */
    const OUT_IS_ISOCHRONOUS = UNKNOWN;

    /**
     * @var int
     * @cvalue SUSPEND_PULL_DOWNS
     */
    const SUSPEND_PULL_DOWNS = UNKNOWN;

    /**
     * @var int
     * @cvalue USE_SERIAL
     */
    const USE_SERIAL = UNKNOWN;

    /**
     * @var int
     * @cvalue USB_VERSION
     */
    const USB_VERSION = UNKNOWN;

    /**
     * @var int
     * @cvalue USE_USB_VERSION
     */
    const USE_USB_VERSION = UNKNOWN;

    /**
     * @var int
     * @cvalue MAX_POWER
     */
    const MAX_POWER = UNKNOWN;

    /**
     * @var int
     * @cvalue CHANNEL_A_TYPE
     */
    const CHANNEL_A_TYPE = UNKNOWN;

    /**
     * @var int
     * @cvalue CHANNEL_B_TYPE
     */
    const CHANNEL_B_TYPE = UNKNOWN;

    /**
     * @var int
     * @cvalue CHANNEL_A_DRIVER
     */
    const CHANNEL_A_DRIVER = UNKNOWN;

    /**
     * @var int
     * @cvalue CHANNEL_B_DRIVER
     */
    const CHANNEL_B_DRIVER = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_FUNCTION_0
     */
    const CBUS_FUNCTION_0 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_FUNCTION_1
     */
    const CBUS_FUNCTION_1 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_FUNCTION_2
     */
    const CBUS_FUNCTION_2 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_FUNCTION_3
     */
    const CBUS_FUNCTION_3 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_FUNCTION_4
     */
    const CBUS_FUNCTION_4 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_FUNCTION_5
     */
    const CBUS_FUNCTION_5 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_FUNCTION_6
     */
    const CBUS_FUNCTION_6 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_FUNCTION_7
     */
    const CBUS_FUNCTION_7 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_FUNCTION_8
     */
    const CBUS_FUNCTION_8 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_FUNCTION_9
     */
    const CBUS_FUNCTION_9 = UNKNOWN;

    /**
     * @var int
     * @cvalue HIGH_CURRENT
     */
    const HIGH_CURRENT = UNKNOWN;

    /**
     * @var int
     * @cvalue HIGH_CURRENT_A
     */
    const HIGH_CURRENT_A = UNKNOWN;

    /**
     * @var int
     * @cvalue HIGH_CURRENT_B
     */
    const HIGH_CURRENT_B = UNKNOWN;

    /**
     * @var int
     * @cvalue INVERT
     */
    const INVERT = UNKNOWN;

    /**
     * @var int
     * @cvalue GROUP0_DRIVE
     */
    const GROUP0_DRIVE = UNKNOWN;

    /**
     * @var int
     * @cvalue GROUP0_SCHMITT
     */
    const GROUP0_SCHMITT = UNKNOWN;

    /**
     * @var int
     * @cvalue GROUP0_SLEW
     */
    const GROUP0_SLEW = UNKNOWN;

    /**
     * @var int
     * @cvalue GROUP1_DRIVE
     */
    const GROUP1_DRIVE = UNKNOWN;

    /**
     * @var int
     * @cvalue GROUP1_SCHMITT
     */
    const GROUP1_SCHMITT = UNKNOWN;

    /**
     * @var int
     * @cvalue GROUP1_SLEW
     */
    const GROUP1_SLEW = UNKNOWN;

    /**
     * @var int
     * @cvalue GROUP2_DRIVE
     */
    const GROUP2_DRIVE = UNKNOWN;

    /**
     * @var int
     * @cvalue GROUP2_SCHMITT
     */
    const GROUP2_SCHMITT = UNKNOWN;

    /**
     * @var int
     * @cvalue GROUP2_SLEW
     */
    const GROUP2_SLEW = UNKNOWN;

    /**
     * @var int
     * @cvalue GROUP3_DRIVE
     */
    const GROUP3_DRIVE = UNKNOWN;

    /**
     * @var int
     * @cvalue GROUP3_SCHMITT
     */
    const GROUP3_SCHMITT = UNKNOWN;

    /**
     * @var int
     * @cvalue GROUP3_SLEW
     */
    const GROUP3_SLEW = UNKNOWN;

    /**
     * @var int
     * @cvalue CHIP_SIZE
     */
    const CHIP_SIZE = UNKNOWN;

    /**
     * @var int
     * @cvalue CHIP_TYPE
     */
    const CHIP_TYPE = UNKNOWN;

    /**
     * @var int
     * @cvalue POWER_SAVE
     */
    const POWER_SAVE = UNKNOWN;

    /**
     * @var int
     * @cvalue CLOCK_POLARITY
     */
    const CLOCK_POLARITY = UNKNOWN;

    /**
     * @var int
     * @cvalue DATA_ORDER
     */
    const DATA_ORDER = UNKNOWN;

    /**
     * @var int
     * @cvalue FLOW_CONTROL
     */
    const FLOW_CONTROL = UNKNOWN;

    /**
     * @var int
     * @cvalue CHANNEL_C_DRIVER
     */
    const CHANNEL_C_DRIVER = UNKNOWN;

    /**
     * @var int
     * @cvalue CHANNEL_D_DRIVER
     */
    const CHANNEL_D_DRIVER = UNKNOWN;

    /**
     * @var int
     * @cvalue CHANNEL_A_RS485
     */
    const CHANNEL_A_RS485 = UNKNOWN;

    /**
     * @var int
     * @cvalue CHANNEL_B_RS485
     */
    const CHANNEL_B_RS485 = UNKNOWN;

    /**
     * @var int
     * @cvalue CHANNEL_C_RS485
     */
    const CHANNEL_C_RS485 = UNKNOWN;

    /**
     * @var int
     * @cvalue CHANNEL_D_RS485
     */
    const CHANNEL_D_RS485 = UNKNOWN;

    /**
     * @var int
     * @cvalue RELEASE_NUMBER
     */
    const RELEASE_NUMBER = UNKNOWN;

    /**
     * @var int
     * @cvalue EXTERNAL_OSCILLATOR
     */
    const EXTERNAL_OSCILLATOR = UNKNOWN;

    /**
     * @var int
     * @cvalue USER_DATA_ADDR
     */
    const USER_DATA_ADDR = UNKNOWN;

    /* enum ftdi_cbus_func */

    /**
     * @var int
     * @cvalue CBUS_TXDEN
     */
    const CBUS_TXDEN = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_PWREN
     */
    const CBUS_PWREN = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_RXLED
     */
    const CBUS_RXLED = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_TXLED
     */
    const CBUS_TXLED = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_TXRXLED
     */
    const CBUS_TXRXLED = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_SLEEP
     */
    const CBUS_SLEEP = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_CLK48
     */
    const CBUS_CLK48 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_CLK24
     */
    const CBUS_CLK24 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_CLK12
     */
    const CBUS_CLK12 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_CLK6
     */
    const CBUS_CLK6 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_IOMODE
     */
    const CBUS_IOMODE = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_BB_WR
     */
    const CBUS_BB_WR = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUS_BB_RD
     */
    const CBUS_BB_RD = UNKNOWN;

    /* enum ftdi_cbush_func */

    /**
     * @var int
     * @cvalue CBUSH_TRISTATE
     */
    const CBUSH_TRISTATE = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSH_TXLED
     */
    const CBUSH_TXLED = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSH_RXLED
     */
    const CBUSH_RXLED = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSH_TXRXLED
     */
    const CBUSH_TXRXLED = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSH_PWREN
     */
    const CBUSH_PWREN = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSH_SLEEP
     */
    const CBUSH_SLEEP = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSH_DRIVE_0
     */
    const CBUSH_DRIVE_0 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSH_DRIVE1
     */
    const CBUSH_DRIVE1 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSH_IOMODE
     */
    const CBUSH_IOMODE = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSH_TXDEN
     */
    const CBUSH_TXDEN = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSH_CLK30
     */
    const CBUSH_CLK30 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSH_CLK15
     */
    const CBUSH_CLK15 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSH_CLK7_5
     */
    const CBUSH_CLK7_5 = UNKNOWN;

    /* enum ftdi_cbusx_func */

    /**
     * @var int
     * @cvalue CBUSX_TRISTATE
     */
    const CBUSX_TRISTATE = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_TXLED
     */
    const CBUSX_TXLED = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_RXLED
     */
    const CBUSX_RXLED = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_TXRXLED
     */
    const CBUSX_TXRXLED = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_PWREN
     */
    const CBUSX_PWREN = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_SLEEP
     */
    const CBUSX_SLEEP = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_DRIVE_0
     */
    const CBUSX_DRIVE_0 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_DRIVE1
     */
    const CBUSX_DRIVE1 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_IOMODE
     */
    const CBUSX_IOMODE = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_TXDEN
     */
    const CBUSX_TXDEN = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_CLK24
     */
    const CBUSX_CLK24 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_CLK12
     */
    const CBUSX_CLK12 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_CLK6
     */
    const CBUSX_CLK6 = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_BAT_DETECT
     */
    const CBUSX_BAT_DETECT = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_BAT_DETECT_NEG
     */
    const CBUSX_BAT_DETECT_NEG = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_I2C_TXE
     */
    const CBUSX_I2C_TXE = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_I2C_RXF
     */
    const CBUSX_I2C_RXF = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_VBUS_SENSE
     */
    const CBUSX_VBUS_SENSE = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_BB_WR
     */
    const CBUSX_BB_WR = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_BB_RD
     */
    const CBUSX_BB_RD = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_TIME_STAMP
     */
    const CBUSX_TIME_STAMP = UNKNOWN;

    /**
     * @var int
     * @cvalue CBUSX_AWAKE
     */
    const CBUSX_AWAKE = UNKNOWN;

    /* #define constants */

    #ifdef MPSSE_WRITE_NEG
    /**
     * @var int
     * @cvalue MPSSE_WRITE_NEG
     */
    const MPSSE_WRITE_NEG = UNKNOWN;
    #endif

    #ifdef MPSSE_BITMODE
    /**
     * @var int
     * @cvalue MPSSE_BITMODE
     */
    const MPSSE_BITMODE = UNKNOWN;
    #endif

    #ifdef MPSSE_READ_NEG
    /**
     * @var int
     * @cvalue MPSSE_READ_NEG
     */
    const MPSSE_READ_NEG = UNKNOWN;
    #endif

    #ifdef MPSSE_LSB
    /**
     * @var int
     * @cvalue MPSSE_LSB
     */
    const MPSSE_LSB = UNKNOWN;
    #endif

    #ifdef MPSSE_DO_WRITE
    /**
     * @var int
     * @cvalue MPSSE_DO_WRITE
     */
    const MPSSE_DO_WRITE = UNKNOWN;
    #endif

    #ifdef MPSSE_DO_READ
    /**
     * @var int
     * @cvalue MPSSE_DO_READ
     */
    const MPSSE_DO_READ = UNKNOWN;
    #endif

    #ifdef MPSSE_WRITE_TMS
    /**
     * @var int
     * @cvalue MPSSE_WRITE_TMS
     */
    const MPSSE_WRITE_TMS = UNKNOWN;
    #endif

    #ifdef SET_BITS_LOW
    /**
     * @var int
     * @cvalue SET_BITS_LOW
     */
    const SET_BITS_LOW = UNKNOWN;
    #endif

    #ifdef SET_BITS_HIGH
    /**
     * @var int
     * @cvalue SET_BITS_HIGH
     */
    const SET_BITS_HIGH = UNKNOWN;
    #endif

    #ifdef GET_BITS_LOW
    /**
     * @var int
     * @cvalue GET_BITS_LOW
     */
    const GET_BITS_LOW = UNKNOWN;
    #endif

    #ifdef GET_BITS_HIGH
    /**
     * @var int
     * @cvalue GET_BITS_HIGH
     */
    const GET_BITS_HIGH = UNKNOWN;
    #endif

    #ifdef LOOPBACK_START
    /**
     * @var int
     * @cvalue LOOPBACK_START
     */
    const LOOPBACK_START = UNKNOWN;
    #endif

    #ifdef LOOPBACK_END
    /**
     * @var int
     * @cvalue LOOPBACK_END
     */
    const LOOPBACK_END = UNKNOWN;
    #endif

    #ifdef TCK_DIVISOR
    /**
     * @var int
     * @cvalue TCK_DIVISOR
     */
    const TCK_DIVISOR = UNKNOWN;
    #endif

    #ifdef DIS_DIV_5
    /**
     * @var int
     * @cvalue DIS_DIV_5
     */
    const DIS_DIV_5 = UNKNOWN;
    #endif

    #ifdef EN_DIV_5
    /**
     * @var int
     * @cvalue EN_DIV_5
     */
    const EN_DIV_5 = UNKNOWN;
    #endif

    #ifdef EN_3_PHASE
    /**
     * @var int
     * @cvalue EN_3_PHASE
     */
    const EN_3_PHASE = UNKNOWN;
    #endif

    #ifdef DIS_3_PHASE
    /**
     * @var int
     * @cvalue DIS_3_PHASE
     */
    const DIS_3_PHASE = UNKNOWN;
    #endif

    #ifdef CLK_BITS
    /**
     * @var int
     * @cvalue CLK_BITS
     */
    const CLK_BITS = UNKNOWN;
    #endif

    #ifdef CLK_BYTES
    /**
     * @var int
     * @cvalue CLK_BYTES
     */
    const CLK_BYTES = UNKNOWN;
    #endif

    #ifdef CLK_WAIT_HIGH
    /**
     * @var int
     * @cvalue CLK_WAIT_HIGH
     */
    const CLK_WAIT_HIGH = UNKNOWN;
    #endif

    #ifdef CLK_WAIT_LOW
    /**
     * @var int
     * @cvalue CLK_WAIT_LOW
     */
    const CLK_WAIT_LOW = UNKNOWN;
    #endif

    #ifdef EN_ADAPTIVE
    /**
     * @var int
     * @cvalue EN_ADAPTIVE
     */
    const EN_ADAPTIVE = UNKNOWN;
    #endif

    #ifdef DIS_ADAPTIVE
    /**
     * @var int
     * @cvalue DIS_ADAPTIVE
     */
    const DIS_ADAPTIVE = UNKNOWN;
    #endif

    #ifdef CLK_BYTES_OR_HIGH
    /**
     * @var int
     * @cvalue CLK_BYTES_OR_HIGH
     */
    const CLK_BYTES_OR_HIGH = UNKNOWN;
    #endif

    #ifdef CLK_BYTES_OR_LOW
    /**
     * @var int
     * @cvalue CLK_BYTES_OR_LOW
     */
    const CLK_BYTES_OR_LOW = UNKNOWN;
    #endif

    #ifdef DRIVE_OPEN_COLLECTOR
    /**
     * @var int
     * @cvalue DRIVE_OPEN_COLLECTOR
     */
    const DRIVE_OPEN_COLLECTOR = UNKNOWN;
    #endif

    #ifdef SEND_IMMEDIATE
    /**
     * @var int
     * @cvalue SEND_IMMEDIATE
     */
    const SEND_IMMEDIATE = UNKNOWN;
    #endif

    #ifdef WAIT_ON_HIGH
    /**
     * @var int
     * @cvalue WAIT_ON_HIGH
     */
    const WAIT_ON_HIGH = UNKNOWN;
    #endif

    #ifdef WAIT_ON_LOW
    /**
     * @var int
     * @cvalue WAIT_ON_LOW
     */
    const WAIT_ON_LOW = UNKNOWN;
    #endif

    #ifdef READ_SHORT
    /**
     * @var int
     * @cvalue READ_SHORT
     */
    const READ_SHORT = UNKNOWN;
    #endif

    #ifdef READ_EXTENDED
    /**
     * @var int
     * @cvalue READ_EXTENDED
     */
    const READ_EXTENDED = UNKNOWN;
    #endif

    #ifdef WRITE_SHORT
    /**
     * @var int
     * @cvalue WRITE_SHORT
     */
    const WRITE_SHORT = UNKNOWN;
    #endif

    #ifdef WRITE_EXTENDED
    /**
     * @var int
     * @cvalue WRITE_EXTENDED
     */
    const WRITE_EXTENDED = UNKNOWN;
    #endif

    #ifdef SIO_RESET
    /**
     * @var int
     * @cvalue SIO_RESET
     */
    const SIO_RESET = UNKNOWN;
    #endif

    #ifdef SIO_MODEM_CTRL
    /**
     * @var int
     * @cvalue SIO_MODEM_CTRL
     */
    const SIO_MODEM_CTRL = UNKNOWN;
    #endif

    #ifdef SIO_SET_FLOW_CTRL
    /**
     * @var int
     * @cvalue SIO_SET_FLOW_CTRL
     */
    const SIO_SET_FLOW_CTRL = UNKNOWN;
    #endif

    #ifdef SIO_SET_BAUD_RATE
    /**
     * @var int
     * @cvalue SIO_SET_BAUD_RATE
     */
    const SIO_SET_BAUD_RATE = UNKNOWN;
    #endif

    #ifdef SIO_SET_DATA
    /**
     * @var int
     * @cvalue SIO_SET_DATA
     */
    const SIO_SET_DATA = UNKNOWN;
    #endif

    #ifdef FTDI_DEVICE_OUT_REQTYPE
    /**
     * @var int
     * @cvalue FTDI_DEVICE_OUT_REQTYPE
     */
    const FTDI_DEVICE_OUT_REQTYPE = UNKNOWN;
    #endif

    #ifdef FTDI_DEVICE_IN_REQTYPE
    /**
     * @var int
     * @cvalue FTDI_DEVICE_IN_REQTYPE
     */
    const FTDI_DEVICE_IN_REQTYPE = UNKNOWN;
    #endif

    #ifdef SIO_RESET_REQUEST
    /**
     * @var int
     * @cvalue SIO_RESET_REQUEST
     */
    const SIO_RESET_REQUEST = UNKNOWN;
    #endif

    #ifdef SIO_SET_BAUDRATE_REQUEST
    /**
     * @var int
     * @cvalue SIO_SET_BAUDRATE_REQUEST
     */
    const SIO_SET_BAUDRATE_REQUEST = UNKNOWN;
    #endif

    #ifdef SIO_SET_DATA_REQUEST
    /**
     * @var int
     * @cvalue SIO_SET_DATA_REQUEST
     */
    const SIO_SET_DATA_REQUEST = UNKNOWN;
    #endif

    #ifdef SIO_SET_FLOW_CTRL_REQUEST
    /**
     * @var int
     * @cvalue SIO_SET_FLOW_CTRL_REQUEST
     */
    const SIO_SET_FLOW_CTRL_REQUEST = UNKNOWN;
    #endif

    #ifdef SIO_SET_MODEM_CTRL_REQUEST
    /**
     * @var int
     * @cvalue SIO_SET_MODEM_CTRL_REQUEST
     */
    const SIO_SET_MODEM_CTRL_REQUEST = UNKNOWN;
    #endif

    #ifdef SIO_POLL_MODEM_STATUS_REQUEST
    /**
     * @var int
     * @cvalue SIO_POLL_MODEM_STATUS_REQUEST
     */
    const SIO_POLL_MODEM_STATUS_REQUEST = UNKNOWN;
    #endif

    #ifdef SIO_SET_EVENT_CHAR_REQUEST
    /**
     * @var int
     * @cvalue SIO_SET_EVENT_CHAR_REQUEST
     */
    const SIO_SET_EVENT_CHAR_REQUEST = UNKNOWN;
    #endif

    #ifdef SIO_SET_ERROR_CHAR_REQUEST
    /**
     * @var int
     * @cvalue SIO_SET_ERROR_CHAR_REQUEST
     */
    const SIO_SET_ERROR_CHAR_REQUEST = UNKNOWN;
    #endif

    #ifdef SIO_SET_LATENCY_TIMER_REQUEST
    /**
     * @var int
     * @cvalue SIO_SET_LATENCY_TIMER_REQUEST
     */
    const SIO_SET_LATENCY_TIMER_REQUEST = UNKNOWN;
    #endif

    #ifdef SIO_GET_LATENCY_TIMER_REQUEST
    /**
     * @var int
     * @cvalue SIO_GET_LATENCY_TIMER_REQUEST
     */
    const SIO_GET_LATENCY_TIMER_REQUEST = UNKNOWN;
    #endif

    #ifdef SIO_SET_BITMODE_REQUEST
    /**
     * @var int
     * @cvalue SIO_SET_BITMODE_REQUEST
     */
    const SIO_SET_BITMODE_REQUEST = UNKNOWN;
    #endif

    #ifdef SIO_READ_PINS_REQUEST
    /**
     * @var int
     * @cvalue SIO_READ_PINS_REQUEST
     */
    const SIO_READ_PINS_REQUEST = UNKNOWN;
    #endif

    #ifdef SIO_READ_EEPROM_REQUEST
    /**
     * @var int
     * @cvalue SIO_READ_EEPROM_REQUEST
     */
    const SIO_READ_EEPROM_REQUEST = UNKNOWN;
    #endif

    #ifdef SIO_WRITE_EEPROM_REQUEST
    /**
     * @var int
     * @cvalue SIO_WRITE_EEPROM_REQUEST
     */
    const SIO_WRITE_EEPROM_REQUEST = UNKNOWN;
    #endif

    #ifdef SIO_ERASE_EEPROM_REQUEST
    /**
     * @var int
     * @cvalue SIO_ERASE_EEPROM_REQUEST
     */
    const SIO_ERASE_EEPROM_REQUEST = UNKNOWN;
    #endif

    #ifdef SIO_RESET_SIO
    /**
     * @var int
     * @cvalue SIO_RESET_SIO
     */
    const SIO_RESET_SIO = UNKNOWN;
    #endif

    #ifdef SIO_TCIFLUSH
    /**
     * @var int
     * @cvalue SIO_TCIFLUSH
     */
    const SIO_TCIFLUSH = UNKNOWN;
    #endif

    #ifdef SIO_TCOFLUSH
    /**
     * @var int
     * @cvalue SIO_TCOFLUSH
     */
    const SIO_TCOFLUSH = UNKNOWN;
    #endif

    #ifdef SIO_DISABLE_FLOW_CTRL
    /**
     * @var int
     * @cvalue SIO_DISABLE_FLOW_CTRL
     */
    const SIO_DISABLE_FLOW_CTRL = UNKNOWN;
    #endif

    #ifdef SIO_RTS_CTS_HS
    /**
     * @var int
     * @cvalue SIO_RTS_CTS_HS
     */
    const SIO_RTS_CTS_HS = UNKNOWN;
    #endif

    #ifdef SIO_DTR_DSR_HS
    /**
     * @var int
     * @cvalue SIO_DTR_DSR_HS
     */
    const SIO_DTR_DSR_HS = UNKNOWN;
    #endif

    #ifdef SIO_XON_XOFF_HS
    /**
     * @var int
     * @cvalue SIO_XON_XOFF_HS
     */
    const SIO_XON_XOFF_HS = UNKNOWN;
    #endif

    #ifdef SIO_SET_DTR_MASK
    /**
     * @var int
     * @cvalue SIO_SET_DTR_MASK
     */
    const SIO_SET_DTR_MASK = UNKNOWN;
    #endif

    #ifdef SIO_SET_DTR_HIGH
    /**
     * @var int
     * @cvalue SIO_SET_DTR_HIGH
     */
    const SIO_SET_DTR_HIGH = UNKNOWN;
    #endif

    #ifdef SIO_SET_DTR_LOW
    /**
     * @var int
     * @cvalue SIO_SET_DTR_LOW
     */
    const SIO_SET_DTR_LOW = UNKNOWN;
    #endif

    #ifdef SIO_SET_RTS_MASK
    /**
     * @var int
     * @cvalue SIO_SET_RTS_MASK
     */
    const SIO_SET_RTS_MASK = UNKNOWN;
    #endif

    #ifdef SIO_SET_RTS_HIGH
    /**
     * @var int
     * @cvalue SIO_SET_RTS_HIGH
     */
    const SIO_SET_RTS_HIGH = UNKNOWN;
    #endif

    #ifdef SIO_SET_RTS_LOW
    /**
     * @var int
     * @cvalue SIO_SET_RTS_LOW
     */
    const SIO_SET_RTS_LOW = UNKNOWN;
    #endif

    #ifdef FT1284_CLK_IDLE_STATE
    /**
     * @var int
     * @cvalue FT1284_CLK_IDLE_STATE
     */
    const FT1284_CLK_IDLE_STATE = UNKNOWN;
    #endif

    #ifdef FT1284_DATA_LSB
    /**
     * @var int
     * @cvalue FT1284_DATA_LSB
     */
    const FT1284_DATA_LSB = UNKNOWN;
    #endif

    #ifdef FT1284_FLOW_CONTROL
    /**
     * @var int
     * @cvalue FT1284_FLOW_CONTROL
     */
    const FT1284_FLOW_CONTROL = UNKNOWN;
    #endif

    #ifdef POWER_SAVE_DISABLE_H
    /**
     * @var int
     * @cvalue POWER_SAVE_DISABLE_H
     */
    const POWER_SAVE_DISABLE_H = UNKNOWN;
    #endif

    #ifdef USE_SERIAL_NUM
    /**
     * @var int
     * @cvalue USE_SERIAL_NUM
     */
    const USE_SERIAL_NUM = UNKNOWN;
    #endif

    #ifdef INVERT_TXD
    /**
     * @var int
     * @cvalue INVERT_TXD
     */
    const INVERT_TXD = UNKNOWN;
    #endif

    #ifdef INVERT_RXD
    /**
     * @var int
     * @cvalue INVERT_RXD
     */
    const INVERT_RXD = UNKNOWN;
    #endif

    #ifdef INVERT_RTS
    /**
     * @var int
     * @cvalue INVERT_RTS
     */
    const INVERT_RTS = UNKNOWN;
    #endif

    #ifdef INVERT_CTS
    /**
     * @var int
     * @cvalue INVERT_CTS
     */
    const INVERT_CTS = UNKNOWN;
    #endif

    #ifdef INVERT_DTR
    /**
     * @var int
     * @cvalue INVERT_DTR
     */
    const INVERT_DTR = UNKNOWN;
    #endif

    #ifdef INVERT_DSR
    /**
     * @var int
     * @cvalue INVERT_DSR
     */
    const INVERT_DSR = UNKNOWN;
    #endif

    #ifdef INVERT_DCD
    /**
     * @var int
     * @cvalue INVERT_DCD
     */
    const INVERT_DCD = UNKNOWN;
    #endif

    #ifdef INVERT_RI
    /**
     * @var int
     * @cvalue INVERT_RI
     */
    const INVERT_RI = UNKNOWN;
    #endif

    #ifdef CHANNEL_IS_UART
    /**
     * @var int
     * @cvalue CHANNEL_IS_UART
     */
    const CHANNEL_IS_UART = UNKNOWN;
    #endif

    #ifdef CHANNEL_IS_FIFO
    /**
     * @var int
     * @cvalue CHANNEL_IS_FIFO
     */
    const CHANNEL_IS_FIFO = UNKNOWN;
    #endif

    #ifdef CHANNEL_IS_OPTO
    /**
     * @var int
     * @cvalue CHANNEL_IS_OPTO
     */
    const CHANNEL_IS_OPTO = UNKNOWN;
    #endif

    #ifdef CHANNEL_IS_CPU
    /**
     * @var int
     * @cvalue CHANNEL_IS_CPU
     */
    const CHANNEL_IS_CPU = UNKNOWN;
    #endif

    #ifdef CHANNEL_IS_FT1284
    /**
     * @var int
     * @cvalue CHANNEL_IS_FT1284
     */
    const CHANNEL_IS_FT1284 = UNKNOWN;
    #endif

    #ifdef CHANNEL_IS_RS485
    /**
     * @var int
     * @cvalue CHANNEL_IS_RS485
     */
    const CHANNEL_IS_RS485 = UNKNOWN;
    #endif

    #ifdef DRIVE_4MA
    /**
     * @var int
     * @cvalue DRIVE_4MA
     */
    const DRIVE_4MA = UNKNOWN;
    #endif

    #ifdef DRIVE_8MA
    /**
     * @var int
     * @cvalue DRIVE_8MA
     */
    const DRIVE_8MA = UNKNOWN;
    #endif

    #ifdef DRIVE_12MA
    /**
     * @var int
     * @cvalue DRIVE_12MA
     */
    const DRIVE_12MA = UNKNOWN;
    #endif

    #ifdef DRIVE_16MA
    /**
     * @var int
     * @cvalue DRIVE_16MA
     */
    const DRIVE_16MA = UNKNOWN;
    #endif

    #ifdef SLOW_SLEW
    /**
     * @var int
     * @cvalue SLOW_SLEW
     */
    const SLOW_SLEW = UNKNOWN;
    #endif

    #ifdef IS_SCHMITT
    /**
     * @var int
     * @cvalue IS_SCHMITT
     */
    const IS_SCHMITT = UNKNOWN;
    #endif

    #ifdef DRIVER_VCP
    /**
     * @var int
     * @cvalue DRIVER_VCP
     */
    const DRIVER_VCP = UNKNOWN;
    #endif

    #ifdef DRIVER_VCPH
    /**
     * @var int
     * @cvalue DRIVER_VCPH
     */
    const DRIVER_VCPH = UNKNOWN;
    #endif

    #ifdef USE_USB_VERSION_BIT
    /**
     * @var int
     * @cvalue USE_USB_VERSION_BIT
     */
    const USE_USB_VERSION_BIT = UNKNOWN;
    #endif

    #ifdef SUSPEND_DBUS7_BIT
    /**
     * @var int
     * @cvalue SUSPEND_DBUS7_BIT
     */
    const SUSPEND_DBUS7_BIT = UNKNOWN;
    #endif

    #ifdef HIGH_CURRENT_DRIVE
    /**
     * @var int
     * @cvalue HIGH_CURRENT_DRIVE
     */
    const HIGH_CURRENT_DRIVE = UNKNOWN;
    #endif

    #ifdef HIGH_CURRENT_DRIVE_R
    /**
     * @var int
     * @cvalue HIGH_CURRENT_DRIVE_R
     */
    const HIGH_CURRENT_DRIVE_R = UNKNOWN;
    #endif

}

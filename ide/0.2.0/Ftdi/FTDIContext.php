<?php

namespace Ftdi;

/**
 * Data Transfer Object representing a libftdi1 context.
 *
 * Populated by FTDI::ftdiNew() after a successful ftdi_new() call.
 * The handle property carries the ftdi_context pointer as an opaque
 * integer -- pass it to every subsequent libftdi1 call.
 * A handle value of -1 indicates an uninitialised or failed context.
 */
class FTDIContext
{

    /**
     * Opaque pointer to struct ftdi_context cast to int. -1 = failed.
     */
    public $handle = 0;

    /**
     * Chip type (enum ftdi_chip_type):
     *   0=TYPE_AM  1=TYPE_BM  2=TYPE_2232C  3=TYPE_R
     *   4=TYPE_2232H  5=TYPE_4232H  6=TYPE_232H  7=TYPE_230X
     */
    public $chipType = 0;

    /**
     * USB read timeout in milliseconds (libftdi1 default: 5000).
     */
    public $usbReadTimeout = 0;

    /**
     * USB write timeout in milliseconds (libftdi1 default: 5000).
     */
    public $usbWriteTimeout = 0;

    /**
     * Interface channel index (struct field: index, 1 or 2).
     * Distinguishes channels on multi-interface chips (FT2232H/FT4232H).
     */
    public $interfaceIndex = 0;

    /**
     * Configured baud rate (0 until ftdi_set_baudrate is called).
     */
    public $baudrate = 0;

    /**
     * Non-zero when bitbang mode is active.
     */
    public $bitbangEnabled = 0;

    /**
     * Active bitbang/MPSSE mode (enum ftdi_mpsse_mode):
     *   0x00=RESET  0x01=BITBANG  0x02=MPSSE  0x04=SYNCBB
     *   0x08=MCU    0x10=OPTO     0x20=CBUS   0x40=SYNCFF  0x80=FT1284
     */
    public $bitbangMode = 0;

    /**
     * Interface channel (struct field: interface, 0 or 1).
     * Set via ftdi_set_interface(); 0=INTERFACE_ANY, 1=A, 2=B, 3=C, 4=D.
     * Named 'channel' to avoid collision with the PHP/Zephir reserved word.
     */
    public $channel = 0;

    /**
     * USB IN endpoint number (typically 1 or 2).
     */
    public $inEndpoint = 0;

    /**
     * USB OUT endpoint number (typically 1 or 2).
     */
    public $outEndpoint = 0;

    /**
     * Read buffer chunk size in bytes (libftdi1 default: 4096).
     */
    public $readBufferChunkSize = 0;

    /**
     * Write buffer chunk size in bytes (libftdi1 default: 4096).
     */
    public $writeBufferChunkSize = 0;

    /**
     * Maximum USB packet size (derived from device descriptor after open).
     */
    public $maxPacketSize = 0;

    /**
     * Kernel module detach mode (enum ftdi_module_detach_mode):
     *   0=AUTO_DETACH_SIO_MODULE
     *   1=DONT_DETACH_SIO_MODULE
     *   2=AUTO_DETACH_REATACH_SIO_MODULE
     */
    public $moduleDetachMode = 0;

    /**
     * Last error string from libftdi1 (empty string if none).
     */
    public $errorStr = '';

    /**
     * Return all context fields as an associative array.
     *
     * @return array
     */
    public function toArray(): array
    {
    }
}

<?php

declare(strict_types=1);

if (! extension_loaded('ftdi')) {
    throw new RuntimeException('The ftdi extension is not loaded; run pest with -d extension=/path/to/ftdi.so');
}

/** A product ID no FTDI device uses, so lookups find nothing on any bench. */
const NO_SUCH_PRODUCT = 0x0001;

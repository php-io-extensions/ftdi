<?php

namespace Ftdi;

class FTDIEeprom
{

    public $eepromHandle = 0;

    public $vendorId = 0;

    public $productId = 0;

    public $selfPowered = 0;

    public $remoteWakeup = 0;

    public $isNotPnp = 0;

    public $suspendDbus7 = 0;

    public $inIsIsochronous = 0;

    public $outIsIsochronous = 0;

    public $suspendPullDowns = 0;

    public $useSerial = 0;

    public $usbVersion = 0;

    public $useUsbVersion = 0;

    public $maxPower = 0;

    public $channelAType = 0;

    public $channelBType = 0;

    public $channelADriver = 0;

    public $channelBDriver = 0;

    public $cbusFunction0 = 0;

    public $cbusFunction1 = 0;

    public $cbusFunction2 = 0;

    public $cbusFunction3 = 0;

    public $cbusFunction4 = 0;

    public $cbusFunction5 = 0;

    public $cbusFunction6 = 0;

    public $cbusFunction7 = 0;

    public $cbusFunction8 = 0;

    public $cbusFunction9 = 0;

    public $highCurrent = 0;

    public $highCurrentA = 0;

    public $highCurrentB = 0;

    public $invert = 0;

    public $group0Drive = 0;

    public $group0Schmitt = 0;

    public $group0Slew = 0;

    public $group1Drive = 0;

    public $group1Schmitt = 0;

    public $group1Slew = 0;

    public $group2Drive = 0;

    public $group2Schmitt = 0;

    public $group2Slew = 0;

    public $group3Drive = 0;

    public $group3Schmitt = 0;

    public $group3Slew = 0;

    public $chipSize = 0;

    public $chipType = 0;

    public $powerSave = 0;

    public $clockPolarity = 0;

    public $dataOrder = 0;

    public $flowControl = 0;

    public $channelCDriver = 0;

    public $channelDDriver = 0;

    public $channelARs485 = 0;

    public $channelBRs485 = 0;

    public $channelCRs485 = 0;

    public $channelDRs485 = 0;

    public $releaseNumber = 0;

    public $externalOscillator = 0;

    public $userDataAddr = 0;

    public $manufacturer = '';

    public $product = '';

    public $serial = '';

    /**
     * @return array
     */
    public function toArray(): array
    {
    }
}

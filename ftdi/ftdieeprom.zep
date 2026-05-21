namespace Ftdi;

class FTDIEeprom
{
    public eepromHandle       = 0;
    public vendorId           = 0;
    public productId          = 0;
    public selfPowered        = 0;
    public remoteWakeup       = 0;
    public isNotPnp           = 0;
    public suspendDbus7       = 0;
    public inIsIsochronous    = 0;
    public outIsIsochronous   = 0;
    public suspendPullDowns   = 0;
    public useSerial          = 0;
    public usbVersion         = 0;
    public useUsbVersion      = 0;
    public maxPower           = 0;
    public channelAType       = 0;
    public channelBType       = 0;
    public channelADriver     = 0;
    public channelBDriver     = 0;
    public cbusFunction0      = 0;
    public cbusFunction1      = 0;
    public cbusFunction2      = 0;
    public cbusFunction3      = 0;
    public cbusFunction4      = 0;
    public cbusFunction5      = 0;
    public cbusFunction6      = 0;
    public cbusFunction7      = 0;
    public cbusFunction8      = 0;
    public cbusFunction9      = 0;
    public highCurrent        = 0;
    public highCurrentA       = 0;
    public highCurrentB       = 0;
    public invert             = 0;
    public group0Drive        = 0;
    public group0Schmitt      = 0;
    public group0Slew         = 0;
    public group1Drive        = 0;
    public group1Schmitt      = 0;
    public group1Slew         = 0;
    public group2Drive        = 0;
    public group2Schmitt      = 0;
    public group2Slew         = 0;
    public group3Drive        = 0;
    public group3Schmitt      = 0;
    public group3Slew         = 0;
    public chipSize           = 0;
    public chipType           = 0;
    public powerSave          = 0;
    public clockPolarity      = 0;
    public dataOrder          = 0;
    public flowControl        = 0;
    public channelCDriver     = 0;
    public channelDDriver     = 0;
    public channelARs485      = 0;
    public channelBRs485      = 0;
    public channelCRs485      = 0;
    public channelDRs485      = 0;
    public releaseNumber      = 0;
    public externalOscillator = 0;
    public userDataAddr       = 0;
    public manufacturer       = "";
    public product            = "";
    public serial             = "";

    public function toArray() -> array
    {
        return [
            "vendorId":           this->vendorId,
            "productId":          this->productId,
            "selfPowered":        this->selfPowered,
            "remoteWakeup":       this->remoteWakeup,
            "isNotPnp":           this->isNotPnp,
            "suspendDbus7":       this->suspendDbus7,
            "inIsIsochronous":    this->inIsIsochronous,
            "outIsIsochronous":   this->outIsIsochronous,
            "suspendPullDowns":   this->suspendPullDowns,
            "useSerial":          this->useSerial,
            "usbVersion":         this->usbVersion,
            "useUsbVersion":      this->useUsbVersion,
            "maxPower":           this->maxPower,
            "channelAType":       this->channelAType,
            "channelBType":       this->channelBType,
            "channelADriver":     this->channelADriver,
            "channelBDriver":     this->channelBDriver,
            "cbusFunction0":      this->cbusFunction0,
            "cbusFunction1":      this->cbusFunction1,
            "cbusFunction2":      this->cbusFunction2,
            "cbusFunction3":      this->cbusFunction3,
            "cbusFunction4":      this->cbusFunction4,
            "cbusFunction5":      this->cbusFunction5,
            "cbusFunction6":      this->cbusFunction6,
            "cbusFunction7":      this->cbusFunction7,
            "cbusFunction8":      this->cbusFunction8,
            "cbusFunction9":      this->cbusFunction9,
            "highCurrent":        this->highCurrent,
            "highCurrentA":       this->highCurrentA,
            "highCurrentB":       this->highCurrentB,
            "invert":             this->invert,
            "group0Drive":        this->group0Drive,
            "group0Schmitt":      this->group0Schmitt,
            "group0Slew":         this->group0Slew,
            "group1Drive":        this->group1Drive,
            "group1Schmitt":      this->group1Schmitt,
            "group1Slew":         this->group1Slew,
            "group2Drive":        this->group2Drive,
            "group2Schmitt":      this->group2Schmitt,
            "group2Slew":         this->group2Slew,
            "group3Drive":        this->group3Drive,
            "group3Schmitt":      this->group3Schmitt,
            "group3Slew":         this->group3Slew,
            "chipSize":           this->chipSize,
            "chipType":           this->chipType,
            "powerSave":          this->powerSave,
            "clockPolarity":      this->clockPolarity,
            "dataOrder":          this->dataOrder,
            "flowControl":        this->flowControl,
            "channelCDriver":     this->channelCDriver,
            "channelDDriver":     this->channelDDriver,
            "channelARs485":      this->channelARs485,
            "channelBRs485":      this->channelBRs485,
            "channelCRs485":      this->channelCRs485,
            "channelDRs485":      this->channelDRs485,
            "releaseNumber":      this->releaseNumber,
            "externalOscillator": this->externalOscillator,
            "userDataAddr":       this->userDataAddr,
            "manufacturer":       this->manufacturer,
            "product":            this->product,
            "serial":             this->serial
        ];
    }
}

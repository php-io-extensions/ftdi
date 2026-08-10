# Ftdi — PHP bindings for libftdi1

> **Note:** This repository is the native PHP extension (`php-io-extensions/ftdi` / `ext-ftdi`). For C-ish global helpers, pair it with [`microscrap/ftdi`](https://github.com/microscrap/ftdi). For MPSSE (SPI / I²C / GPIO over FT232H-class chips), also install [`microscrap/mpsse`](https://github.com/microscrap/mpsse).

Direct bindings to [libftdi1](https://www.intra2net.com/en/developer/libftdi/) for FTDI USB devices from PHP. Namespace: `Ftdi\`. Static API on `Ftdi\FTDI` plus opaque companion DTOs (`FTDIContext`, `FTDIEeprom`, `FTDITransferControl`, `FTDIVersionInfo`).

```bash
# requires libftdi1 at build + runtime
pie install php-io-extensions/ftdi
php -m | grep ftdi
```

Linux + macOS only (Windows excluded). Version line: **0.7.x** (`0.7.0`).

### Official Documentation

Documentation for **ftdi** lives on the [ScrapyardIO website](https://scrapyard-io.projectsaturnstudios.com/ecosystem/php-io-extensions/ftdi/0.7.x/overview):

- [Overview](https://scrapyard-io.projectsaturnstudios.com/ecosystem/php-io-extensions/ftdi/0.7.x/overview)
- [Requirements](https://scrapyard-io.projectsaturnstudios.com/ecosystem/php-io-extensions/ftdi/0.7.x/requirements)
- [Installation](https://scrapyard-io.projectsaturnstudios.com/ecosystem/php-io-extensions/ftdi/0.7.x/installation)
- [Quick Start](https://scrapyard-io.projectsaturnstudios.com/ecosystem/php-io-extensions/ftdi/0.7.x/quick-start)
- [Usage](https://scrapyard-io.projectsaturnstudios.com/ecosystem/php-io-extensions/ftdi/0.7.x/usage)
- [API Reference](https://scrapyard-io.projectsaturnstudios.com/ecosystem/php-io-extensions/ftdi/0.7.x/reference)
- [Troubleshooting](https://scrapyard-io.projectsaturnstudios.com/ecosystem/php-io-extensions/ftdi/0.7.x/troubleshooting)
- [Related](https://scrapyard-io.projectsaturnstudios.com/ecosystem/php-io-extensions/ftdi/0.7.x/related)

### Contributing

Thank you for considering contributing! Please open issues and pull requests on [GitHub](https://github.com/php-io-extensions/ftdi).

### License

Open-sourced software licensed under the [MIT license](LICENSE).

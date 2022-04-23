# External Vendor Documentation

- For the sake of completeness, external documentation (i.e. not project-generated documentation) is linked an embedded on this page.

- Vendor docs have a nasty habit of dissapearring or hyperlinks going stale... this is the most robust workaround!

--------------------------------------------------------------------------------------------------------------------------------------------------------------------
## ESP32-S3-xxxx Datasheets

Source: Espresif's official support page https://www.espressif.com/en/support/documents/technical-documents?keys=ESP32-S3+datasheet/

Specific files relevant to [/tinkertrap/](https://github.com/benseleb/tinkertrap/) (inline links are local to this repo):

[ESP32-S3 CHIPSET Datasheet](www.github.com/benseleb/tinkertrap/documentation/pdf/esp32-s3_datasheet_en.pdf)

[ESP32-S3-WROOM-1 / -WROOM-1U EMBEDDED MODULE Datasheet](www.github.com/benseleb/tinkertrap/documentation/pdf/esp32-s3-wroom-1_wroom-1u_datasheet_en.pdf)

[ESP32-S3-WROOM-2 EMBEDDED MODULE Datasheet](www.github.com/benseleb/tinkertrap/documentation/pdf/esp32-s3-wroom-2_datasheet_en.pdf)

[ESP32-S3-MINI-1 / -MINI-1U EMBEDDED MODULE Datasheet](www.github.com/benseleb/tinkertrap/documentation/pdf/esp32-s3-mini-1_mini-1u_datasheet_en.pdf)

Again, here is a helpful "product selector matrix" that highlights the details between each:
<!-- REMEMBER, GITHUB MARKDOWN AUTOMATICALLY "CENTERS COLUMNS! -->
|    Module   | Package | Temp Range| GPIO  | Flash |  SRAM  |   ROM  | PSRAM |  Clock  | Core | Antenna |   Dims (mm)   |
| :---------: | :-----: | :-------: | :---: | :---: | :----: | :----: | :---: | :-----: | :--: | :-----: | :-----------: |
| -S3 CHIPSET |  QFN56  | -40 ~ 105 |  45   | 0/4/8 MB | 512 kB | 384 kB | 0/2/8 MB  | 240 MHz | Dual | F-Trace |    7.0x7.0    |
|  -WROOM-1   |  Module | -40 ~ 85  |  36   | 4/8/16 MB  | 512 kB | 384 kB | 0/2/8 MB  | 240 MHz | Dual | F-Trace | 18.0x25.5x3.1 |
|  -WROOM-1U  |  Module | -40 ~ 85  |  36   | 4/8/16 MB  | 512 kB | 384 kB | 0/2/8 MB  | 240 MHz | Dual | F-Trace | 18.0x25.5x3.2 |
|  -WROOM-2   |  Module | -40 ~ 65  |  33   | 16/32 MB  | 512 kB | 384 kB | 8/8 MB  | 240 MHz | Dual | F-Trace | 18.0x25.5x3.1 |
|   -MINI-1   |  Module | -40 ~ 85  |  39   | 8 MB  | 512 kB | 384 kB | 0 MB  | 240 MHz | Dual | F-Trace | 15.4x20.5x2.4 |
|  -MINI-1U   |  Module | -40 ~ 85  |  39   | 8 MB  | 512 kB | 384 kB | 0 MB  | 240 MHz | Dual | F-Trace | 15.4x20.5x2.4 |


## Other Manufacturer Component Datasheets

_(to be completed)_

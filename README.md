# gb-battery

This project was inspired by https://santiagocrespo.itch.io/gb-battery-test

Their battery test is a great tool, but it has one issue for my particular use. I wanted to load it onto an MBCX cartridge with multiple games on it, but the way it works resets the RTC registers on each start, causing other games on the cartridge to lose their stored RTC values.

I tried to modify their project, however the way GBStudio works is a bit at odds with the way I think. I decided instead to write my own version using GBDK-2020 in the C language.

​The included song is a sample project from [hUGETracker](https://github.com/SuperDisk/hUGETracker) called "Jester - FishNChips.uge"

I am using the [hUGEDriver](https://github.com/SuperDisk/hUGEDriver) library for the music.

I hope you enjoy

binary can be downloaded via [itch.io](https://dgc1980.itch.io/gb-battery)

to compile, place the "hUGEDriver.h" and "hUGEDriver.lib" from the hUGEDriver library in the source folder, make sure GBDK-2020 is installed to c:\gbdk or modify the make.bat to suit your setup, then run setup.bat
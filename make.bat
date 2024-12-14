c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o main.o main.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o jester.o jester.c

c:\gbdk\bin\lcc -Wl-lhUGEDriver.lib -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wl-yt1 -Wl-yo4 -Wm-yt0x0F -Wl-ya16 -Wm-yn"DGCBATTERY" -o gbbattery.gb main.o jester.o

c:\bgb\bgb gbbattery.gb
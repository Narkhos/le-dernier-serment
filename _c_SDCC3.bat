@echo off
set path=C:\Windows\System32;.\SDCC36\bin
echo COMPILING TECHNICAL LIB ...
sdasz80 -go crt0_cpc.s
sdasz80 -o putchar_cpc.s
sdasz80 -o getchar_cpc.s
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc lib.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc sound.c
sdcc -mz80 -c --std-c99 --opt-code-speed menu.c
sdcc -mz80 -c --std-c99 --opt-code-speed patch.c
echo COMPILING SOURCES ...
sdcc -mz80 -c --std-c99 --opt-code-speed ./parser/game.c
sdcc -mz80 -c --std-c99 --opt-code-speed ./parser/parser.c
sdcc -mz80 -c --std-c99 --opt-code-speed ./parser/behavior.c
sdcc -mz80 -c --std-c99 --opt-code-speed ./scenes.c
sdcc -mz80 -c --std-c99 --opt-code-speed ./dialog.c
sdcc -mz80 -c --std-c99 --opt-code-speed ./book.c
sdcc -mz80 -c --std-c99 --opt-code-speed ./alchemy.c
echo COMPILING MAIN PROGRAM ...
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --fno-omit-frame-pointer --no-std-crt0 crt0_cpc.rel lib.rel putchar_cpc.rel getchar_cpc.rel game.rel parser.rel behavior.rel sound.rel menu.rel patch.rel scenes.rel dialog.rel book.rel alchemy.rel main.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --fno-omit-frame-pointer --no-std-crt0 database.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --fno-omit-frame-pointer --no-std-crt0 datatext.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --fno-omit-frame-pointer --no-std-crt0 charset.c
echo HEX2BIN ...
hex2bin main.ihx
hex2bin database.ihx
hex2bin datatext.ihx
hex2bin charset.ihx
echo CPCDISK ...
CPCDiskXP -File main.bin -AddAmsdosHeader 100 -AddToNewDsk result.dsk
CPCDiskXP -File database.bin -AddAmsdosHeader 100 -AddToExistingDsk result.dsk
CPCDiskXP -File datatext.bin -AddAmsdosHeader 100 -AddToExistingDsk result.dsk
CPCDiskXP -File charset.bin -AddAmsdosHeader 100 -AddToExistingDsk result.dsk
CPCDiskXP -File forest.scr -AddToExistingDsk result.dsk
CPCDiskXP -File mforest.scr -AddToExistingDsk result.dsk
CPCDiskXP -File outdoor.scr -AddToExistingDsk result.dsk
CPCDiskXP -File indoor.scr -AddToExistingDsk result.dsk
CPCDiskXP -File mindoor.scr -AddToExistingDsk result.dsk
CPCDiskXP -File labo.scr -AddToExistingDsk result.dsk
CPCDiskXP -File nobook.scr -AddToExistingDsk result.dsk
CPCDiskXP -File secret.scr -AddToExistingDsk result.dsk
CPCDiskXP -File msecret.scr -AddToExistingDsk result.dsk
CPCDiskXP -File outhut.scr -AddToExistingDsk result.dsk
CPCDiskXP -File ninhut.scr -AddToExistingDsk result.dsk
CPCDiskXP -File inhut.scr -AddToExistingDsk result.dsk
CPCDiskXP -File omirror.scr -AddToExistingDsk result.dsk
CPCDiskXP -File cmirror.scr -AddToExistingDsk result.dsk
CPCDiskXP -File god.scr -AddToExistingDsk result.dsk
CPCDiskXP -File cavern.scr -AddToExistingDsk result.dsk
CPCDiskXP -File crypt.scr -AddToExistingDsk result.dsk
CPCDiskXP -File ruin.scr -AddToExistingDsk result.dsk
CPCDiskXP -File mruin.scr -AddToExistingDsk result.dsk
CPCDiskXP -File compass.scr -AddToExistingDsk result.dsk
CPCDiskXP -File sablier.scr -AddToExistingDsk result.dsk
CPCDiskXP -File loose.scr -AddToExistingDsk result.dsk
CPCDiskXP -File win.scr -AddToExistingDsk result.dsk
CPCDiskXP -File perfect.scr -AddToExistingDsk result.dsk
CPCDiskXP -File pnormal.scr -AddToExistingDsk result.dsk
CPCDiskXP -File psleepy.scr -AddToExistingDsk result.dsk
CPCDiskXP -File pnervous.scr -AddToExistingDsk result.dsk
CPCDiskXP -File psick.scr -AddToExistingDsk result.dsk
CPCDiskXP -File pinvisib.scr -AddToExistingDsk result.dsk
CPCDiskXP -File pshiny.scr -AddToExistingDsk result.dsk
CPCDiskXP -File title.scr -AddToExistingDsk result.dsk
CPCDiskXP -File DISC.BAS -AddToExistingDsk result.dsk
del *.lst
del *.map
del *.noi
del *.sym
del *.asm
del *.bin
del *.ihx
del *.rel
del *.lk
sdcc --version
pause
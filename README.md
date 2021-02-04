STM32-Template for Linux and Windows 10
=======================================

A Build template for projects using the **stm32vl discovery board**,
using the arm embedded gnu toolchain, and the STM32F10x Standard Peripheral Library. See "book.pdf". This repository is a modified fork of https://github.com/geoffreymbrown/STM32-Template repository.

Do not use the "book.pdf"'s method of installing codesourcery GNU Toolchain tools!! You should now use the GNU Arm Embedded Toolchain tools. The below instructions will show you how to install the GNU Arm Embedded Toolchain:

**For Windows 10**: use the Windows 10 installer (gcc-arm-none-eabi-10-2020-q4-major-win32.exe, select default but placd a check mark next to update system path variables) : https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads

**For Linux** for the instructions given in the answer: https://askubuntu.com/questions/1243252/how-to-install-arm-none-eabi-gdb-on-ubuntu-20-04-lts-focal-fossa

The STM32VLDISCOVERY board can be purchased for ~$25.00 on amazon.com: https://www.amazon.com/MICROELECTRONICS-STM32VLDISCOVERY-Quick-Evaluation-Debugger/dp/B073RQXB6L or
https://www.st.com/en/evaluation-tools/stm32vldiscovery.html#sample-buy from other distributors for around ~$20.00

Documentation for the STM32VLDISCOVERY board can be found: https://www.st.com/en/evaluation-tools/stm32vldiscovery.html#documentation
The STM32VLDISCOVERY board has an STM32F100RBT6B MCU, here is it's datasheet : https://www.st.com/resource/en/datasheet/stm32f100cb.pdf

Please obtain the STM32F10x Standard Peripheral Libray from: https://www.st.com/en/embedded-software/stsw-stm32054.html

For a working copy of the STM32F10x Standard Peripheral Library that works with the current ststm32 platform from Platformio, I had to
create my own modified version of the library called "STM32F10x_StdPeriph_Lib_V3.5.0_mod".  Please obtain my modified version of the STM32F10x Standard Peripheral Libray (STM32F10x_StdPeriph_Lib_V3.5.0_mod): https://github.com/GadgetAngel/STM32F10x_StdPeriph_Lib_V3.5.0_mod.git It is not neccessary to download it manually. If you use platformio.ini file, Platformio will download the modified library automatically for you. Just use my version of the Platformio.ini file that is part of this project.

~Download the STM32F10x Standard Peripheral Library and place it on you computer system. I placed mine in
"/home/joann/Arm/STM32F10x_StdPeriph_Lib_V3.5.0" on **LINUX** and
"C:\Users\joann\download_sw\STM32F10x_StdPeriph_Lib_V3.5.0" on **Windows 10**~

~Now, (by hand) **Adjust the path in the platformio.ini file to match where you placed the "STM32F10x Standard Peripheral Libray" on your
computer system**~.

#### To test:

   (1) install the VScode with Platformio extension.

   (2) open this project up in VScode (open the folder STM32-TEMPLATE)

   (3) build project using platfomio and VScode, the platformio.ini file is already setup to use main.c in ~Demo~ Blinking_Light2 dirctory


#### To create new projects

   (1) clone the Demo directory (name the directory appropriately)

   (2) change Platformio.ini file: change default_src_filter to add new sources to the compiler

   (3) Build with Platformio and Vscode

---

### Before you can run a gdb session on the STM32VLDISCOVERY board do the following:

Because the STM32VL discovery board has a built in st-link-v1 we can use it to flash our compiled firmware.elf file to the MCU for
testing and debugging.

To flash the firmware.bin file to the STM32VLdiscovery board **LINUX and WINDOW users** will use the stlink (v1.6.0) utility from github.com:
We need to instal the stlink (v1.6.0) on your computers system. Download the stlink project v1.6.0 (do not use the latestest version 1.6.1 because this version will not work with STM32VL discovery board) from github.com: https://github.com/stlink-org/stlink/releases/tag/v1.6.0.  Follow the stlink v1.6.0 instructions for installing or compiling the project for your a LINUX system: https://github.com/stlink-org/stlink/blob/v1.6.0/doc/compiling.md

For **Windows** users: To flash the firmware.bin file to the STM32VLdiscovery board WINDOWS users can also use the ST-LINK utility and st-link_cli utility from STelectronics:We need to install the latest ST-LINK utility from STelectrons on to your computer system.  Download the ST-LINK utility (it include the st-link_cli utility too) from: https://www.st.com/en/development-tools/stsw-link004.html#GetSoftware. Run the windows installer. st-link_cli can only be run from the cmd prompt.
The command for st-link_cli is: $> st-link_cli -c ID=0 SWD -P "C:\path-to-compiled-firmware\Demo_Build\disco_f100rb\firmware.bin" 0x08000000

FOR **WINDOWs** USERS ONLY: by default the USB driver for the st-link devices must be registerd with ziag tool for st-link to work under windows.  If you do not register
the usb driver via Ziag tool you will see the followiing error:
```
Error: libusb_open() failed with LIBUSB_ERROR_NOT_SUPPORTED
Error: open failed
```
FOR **WINDOWs** USERE ONLY: to prevent the above libusb_open() error from occuring, download the Ziag tool. There is no installation, you run the ziag tool by double-click on the zadig-2.5.exe file. Download the Zadiag tool from here: https://zadig.akeo.ie/. Plug in your STM32VLdiscovery board to your Windows 10 computer. Now double-click on the Zadiag.2.5.exe file. Select yes, Select Options menu, select List all devices. You should see STM32 STLink in the list. Select it. Now you want your system to use the WinUSB driver instead of the driver you are currently using. Select Install Drier. When the WinUSB driver is installed you will see a box that says it was sucessfull. Exit the Zadig tool.

On a **LINUX** system you will use the github project stlink (v1.6.0) to perform this task from a terminal window:
$> st-flash write /your-path-to-file/firmware.bin 0x08000000

On a **Windows** system you will use the github project stlink (v1.6.0) to perform this task from a terminal window:
$>st-flash write "C:\path-to-your-firmware.bin-file\firmware.bin" 0x08000000

For **LINUX or Windows** Users: If you have VScode with Platformio installed, after the firmware.bin file is compiled you can hit the "Upload" Button and VScode will run the flash command. Just un-comment the correct lines in Platformio.ini file for either Windows or Linux OS.

ON **LINUX**: if succesfully flashed, via VScode, you will see this at the bottom of the output:
```
st-flash 1.6.0
2021-01-31T18:50:36 INFO common.c: Loading device parameters....
2021-01-31T18:50:36 INFO common.c: Device connected is: F1 Medium/Low-density Value Line device, id 0x10016420
2021-01-31T18:50:36 INFO common.c: SRAM size: 0x2000 bytes (8 KiB), Flash: 0x20000 bytes (128 KiB) in pages of 1024 bytes
2021-01-31T18:50:36 INFO common.c: Attempting to write 824 (0x338) bytes to stm32 address: 134217728 (0x8000000)
Flash page at addr: 0x08000000 erased
2021-01-31T18:50:36 INFO common.c: Finished erasing 1 pages of 1024 (0x400) bytes
2021-01-31T18:50:36 INFO common.c: Starting Flash write for VL/F0/F3/F1_XL core id
2021-01-31T18:50:36 INFO flash_loader.c: Successfully loaded flash loader in sram
  1/1 pages written
2021-01-31T18:50:36 INFO common.c: Starting verification of write complete
2021-01-31T18:50:36 INFO common.c: Flash written and verified! jolly good!
```

ON **Windows**: if successfully flashed, via VScode using ST-LINK_cli tool from STelectronics, you will see this in the output:
```
STM32 ST-LINK CLI v3.6.0.0
STM32 ST-LINK Command Line Interface

ST-LINK SN: ST-Link/V1_on_D:
ST-LINK Firmware version: V1J13S0
Connected via SWD.
Connection mode: Normal
Reset mode: Software reset
Device ID: 0x420
Device flash Size: 128 Kbytes
Device family: STM32F100xx Low/Medium density Value Line

Loading file...
Flash Programming:
  File : C:\Firmware\Git Repo\STM32-Template\Demo_Build\disco_f100rb\firmware.bin
  Address : 0x08000000
Memory programming...
██████████████████████████████████████████████████ 100%
Memory programmed in 0s and 234ms.
Programming Complete.
```

---

### How to START up GDB server on Linux and Windows machines:

For **LINUX and WINDOWS** users:
The gdb server is built into the stlink's st-util utility. Start the gdb server by executing the following command in a
new terminal window:
$> st-util --stlinkv1

```
st-util 1.6.0
2021-01-31T19:13:39 INFO common.c: Loading device parameters....
2021-01-31T19:13:39 INFO common.c: Device connected is: F1 Medium/Low-density Value Line device, id 0x10016420
2021-01-31T19:13:39 INFO common.c: SRAM size: 0x2000 bytes (8 KiB), Flash: 0x20000 bytes (128 KiB) in pages of 1024 bytes
2021-01-31T19:13:39 INFO sg.c: Successfully opened a stlink v1 debugger
2021-01-31T19:13:39 INFO gdb-server.c: Chip ID is 00000420, Core ID is  1ba01477.
2021-01-31T19:13:39 INFO gdb-server.c: Listening at *:4242...

```
For **LINUX** users: In a second new terminal window start debugging the firmware.bin file you flashed to the STM32VL discovery board by performing the following commands (the gdb server is part of the GNU Arm Embedded Toolchain install):
$>cd /path-to-your-firmware.elf-file/
$>arm-none-eabi-gdb
```
GNU gdb (GNU Arm Embedded Toolchain 10-2020-q4-major) 10.1.90.20201028-git
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "--host=x86_64-linux-gnu --target=arm-none-eabi".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word".

```

For **Windows** users:
The gdb server is built into the GNU Arm Embedded Toolchain. Start the gdb server by doing the following:
Open a second cmd prompt window or terminal windows and type in the following commands:
$>cd c:\path-to-your-bin-file

my example:
```
$> cd c:\Firmware\Git_Repo\STM32-Template\Blinking_Light2_Build\disco_f100rb
```
Now type the following command:
```
c:\path-to-your-elf-file\> arm-none-eabi-gdb
```
Output from arme-none-eabi-gdb command:
```
GNU gdb (GNU Arm Embedded Toolchain 10-2020-q4-major) 10.1.90.20201028-git
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "--host=i686-w64-mingw32 --target=arm-none-eabi".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word".
```

For **LINUX and WINDOW** users, at the GDB prompt (gdb) type in the following command:

(gdb) target extended localhost:4242

```
Remote debugging using localhost:4242
warning: No executable has been specified and target does not support
determining executable automatically.  Try using the "file" command.
0x08000210 in ?? ()
```
For **LINUX and WINDOW** Users, at the GDB prompt (gdb), type the following command:
(gdb) file firmware.elf

```
A program is being debugged already.
Are you sure you want to change the file? (y or n)
```
For **LINUX and WINDOW** Users, type y
```
Reading symbols from firmware.elf...
```
---
---

### Here is the start of GDB session example #1:

Both **LINUX and Windows** Users:
(gdb) l
```
1	int i = 0;
2	int off = 5;
3
4	void inc(void){
5	  i += off;
6	}
7
8
9	int main(void){
10	  while (1) {
```
Both **LINUX and Windows** Users:
(gdb) info breakpoints
```
No breakpoints or watchpoints.
```
Both **LINUX and Windows** Users:
set a break point at right before main call inc routine by typeing the following:
(gdb) break inc
```
Breakpoint 1 at 0x80002ac: file Demo/main.c, line 5.
Note: automatically using hardware breakpoints for read-only addresses.
```
Both **LINUX and Windows** Users:
(gdb) commands
```
Type commands for breakpoint(s) 1, one per line.
End with a line saying just "end".
```
Both **LINUX and Windows** Users, Type in the following:
```
>printf "i is %d\n",i
>continue
>end
```
Both **LINUX and Windows** Users:
(gdb) cont
```
Continuing.

Breakpoint 1, inc () at Demo/main.c:5
5	  i += off;
i is 0

Breakpoint 1, inc () at Demo/main.c:5
5	  i += off;
i is 5

Breakpoint 1, inc () at Demo/main.c:5
5	  i += off;
i is 10

Breakpoint 1, inc () at Demo/main.c:5
5	  i += off;
i is 15

Breakpoint 1, inc () at Demo/main.c:5
5	  i += off;
i is 20

Breakpoint 1, inc () at Demo/main.c:5
--Type <RET> for more, q to quit, c to continue without paging--
```
Both **LINUX and Windows** Users, type c:
```
--Type <RET> for more, q to quit, c to continue without paging--c
```
Both **LINUX and Windows** Users, Now you will get a rolling screen of output, to stop it press cntrl-c on your keyboard

```
^CBreakpoint 1, Quit
(gdb)
```
Both **LINUX and Windows** Users:
(gdb) whatis i
```
type = int
```
Both **LINUX and Windows** Users:
(gdb) p i
```
$1 = 670
```
Both **LINUX and Windows** Users:
Now let's change the value of i, by typing the following:
(gdb) print i=0
```
$2 = 0
```
Both **LINUX and Windows** Users:
(gdb)p i
```
$3 = 0
```
Both **LINUX and Windows** Users:
(gdb) cont
```
Continuing.

Breakpoint 1, inc () at Demo/main.c:5
5	  i += off;
i is 0

Breakpoint 1, inc () at Demo/main.c:5
5	  i += off;
i is 5

Breakpoint 1, inc () at Demo/main.c:5
5	  i += off;
i is 10

Breakpoint 1, inc () at Demo/main.c:5
5	  i += off;
i is 15

Breakpoint 1, inc () at Demo/main.c:5
5	  i += off;
i is 20
```
Both **LINUX and Windows** Users, The output will continue until you press cntrl-c on your keyboard:
```
^CBreakpoint 1, Quit
```
Both **LINUX and Windows** Users:
to stop debugging the file:
(gdb) kill
```
Kill the program being debugged? (y or n)
```
Both **LINUX and Windows Users**, type:  y
```
[Inferior 1 (Remote target) killed]
```
Both **LINUX and Windows** Users:
(gdb) q

### end of GDB session example #1

Both **LINUX and Window Users**, type cntrl-c on your keyboard, the terminal window will return back to the system prompt.

Both **LINUX and Window Users**, Select the terminal window where you typed in st-util command and hit cntrl-c to exit the st-util command

For **LINUX Users**, Now exit out of both terminal windows.

For **LINUX Users**, If you want a new gdb session, you must start up two new terminal windows

For **Windows Users**, type cntrl-c on your keyboard, the terminal window will return back to the system prompt or cmd prompt. Windows users can
reuse the same terminal window if they want to restart another gdb session.

---

### Documentation

All the GDB documentation can be found online at: https://sourceware.org/gdb/current/onlinedocs/gdb/index.html#SEC_Contents

### A Quickstart Guide to Debugging C Programs with gdb:

https://teaching.csse.uwa.edu.au/units/CITS2230/resources/gdb-intro.html

---

### Here is the start of GDB session example #2:

c:\Firmware\Git_Repo\STM32-Template\Blinking_Light2_Build\disco_f100rb>arm-none-eabi-gdb firmware.elf
```
C:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2020-q4-major\bin\arm-none-eabi-gdb.exe: warning: Couldn't determine a path for the index cache directory.
GNU gdb (GNU Arm Embedded Toolchain 10-2020-q4-major) 10.1.90.20201028-git
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "--host=i686-w64-mingw32 --target=arm-none-eabi".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from firmware.elf...
```
(gdb) target extended localhost:4242
```
Remote debugging using localhost:4242
Reset_Handler ()
    at C:\users\joann\.platformio\packages\framework-cmsis-stm32f1\Source\Templates\gcc\startup_stm32f100xb.S:65
65        movs r1, #0
```
(gdb) info breakpoints
```
No breakpoints or watchpoints.
```
(gdb) break assert_failed
```
Breakpoint 1 at 0x80006dc: file Blinking_Light2\main.c, line 104.
Note: automatically using hardware breakpoints for read-only addresses.
```
(gdb) r
```
The program being debugged has been started already.
Start it from the beginning? (y or n)
```
type in y
```
Starting program: c:\Firmware\Git_Repo\STM32-Template\Blinking_Light2_Build\disco_f100rb\firmware.elf

Breakpoint 1, assert_failed (
    file=file@entry=0x8000740 ".pio\\libdeps\\disco_f100rb\\STM32F10x_StdPeriph_Lib_V3.5.0_mod\\Libraries\\STM32F10x_StdPeriph_Driver\\stm32f10x_gpio.c", line=line@entry=178) at Blinking_Light2\main.c:104
104       void assert_failed(uint8_t* file , uint32_t line) {
```
(gdb) bt
```
#0  assert_failed (
    file=file@entry=0x8000740 ".pio\\libdeps\\disco_f100rb\\STM32F10x_StdPeriph_Lib_V3.5.0_mod\\Libraries\\STM32F10x_StdPeriph_Driver\\stm32f10x_gpio.c", line=line@entry=178) at Blinking_Light2\main.c:104
#1  0x080002f2 in GPIO_Init (GPIOx=GPIOx@entry=0x42, GPIO_InitStruct=GPIO_InitStruct@entry=0x20001ff4)
    at .pio\libdeps\disco_f100rb\STM32F10x_StdPeriph_Lib_V3.5.0_mod\Libraries\STM32F10x_StdPeriph_Driver\stm32f10x_gpio.c:178
#2  0x08000614 in main () at Blinking_Light2\main.c:42
```
(gdb) list 42
```
37        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
38        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
39        // correct use of the GPI_Init call (comment out this out when you want to cause an assertion violation):
40        //GPIO_Init(GPIOC, &GPIO_InitStructure);
41        // un-comment the below statement  when you want to cause an assertion violation and use GDB to find it (part of Exercise 4.1)
42        GPIO_Init((void *) 66U, &GPIO_InitStructure);
43
44        // configure PA0 pin
45        GPIO_StructInit (&GPIO_InitStructure);
46        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
```
(gdb) q

### end of GDB session example #2
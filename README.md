STM32-Template with VScode and Platformio for Linux and Windows 10
=======================================

A Build template for projects using the **STM32VLDISCOVERY board, STM32F407 Discovery Board, Nucleo STM32-L433RC-P board and Nucleo STM32F767 board**, using the arm embedded GNU toolchain, and the STM32F10x Standard Peripheral Library, STM32F40xx Standard Peripheral Library, CMSIS libraries, STM32F7 Standard HAL Library, and others. Trying to do things using "Bare Metal" techniques but using the ST Libraries when I get stuck. This project is a learning project. I am trying to learn embedded programming using C Language and using the GNU toolchain. The "book.pdf" is where I am starting and expanding what I learn on the STM32F1 board to other MCUs (STM32F4 and STM32F7).  This repository is a modified fork of https://github.com/geoffreymbrown/STM32-Template repository.

Do not use the "book.pdf"'s method of installing codesourcery GNU Toolchain tools!! You should use the GNU Arm Embedded Toolchain tools. The below instructions will show you how to install the GNU Arm Embedded Toolchain:

**For Windows 10**: use the Windows 10 installer (gcc-arm-none-eabi-10-2020-q4-major-win32.exe, select default but placd a check mark next to update system path variables) : https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads

**For Linux** for the instructions given in the answer: https://askubuntu.com/questions/1243252/how-to-install-arm-none-eabi-gdb-on-ubuntu-20-04-lts-focal-fossa

The STM32VLDISCOVERY board can be purchased for ~$25.00 on amazon.com: https://www.amazon.com/MICROELECTRONICS-STM32VLDISCOVERY-Quick-Evaluation-Debugger/dp/B073RQXB6L or
https://www.st.com/en/evaluation-tools/stm32vldiscovery.html#sample-buy from other distributors for around ~$20.00

Documentation for the STM32VLDISCOVERY board can be found: https://www.st.com/en/evaluation-tools/stm32vldiscovery.html#documentation
The STM32VLDISCOVERY board has an STM32F100RBT6B MCU, here is it's datasheet : https://www.st.com/resource/en/datasheet/stm32f100cb.pdf

#### ~Please be aware that the STM32VLDISCOVERY board's ST-LINK-V1 does not work with the Window's ST-LINK-V2 Utility.  At this time the only tool that~

#### For LINUX users: I can use the st-link utility on github.com to upload and download firmware to the STM32VL-Discovery (even that does not work in the latestest version). You must use the st-link utility V1.6.0 (https://github.com/stlink-org/stlink/tree/v1.6.0), with VScode and Platformio if you want to automatically upload your code to the board or debug your code on the board using VScode and the onboard st-link probe on the LINUX OS.

#### On Windows 10, the STelectronic's ST-LINK-UTILITY command line interface ("st-link_cli"), which is downloaded with the ST LINK Utility, from https://www.st.com/en/development-tools/stsw-link004.html#GetSoftware should be used instead of the stlink utility from github.

#### So on Linux use stlink utility located on github.com from stlink-org, on Windows 10 use the ST-LINK-UTILITY's command line interface from STelectronic's("st-link_cli") with VScode and Platformio to perform live debugging inside of VScode interface. Do NOT use the Zadig tool on Windows 10!! FYI, the st-link-V2,(note: I said version 2) when properly installed on Windows OS will appear in Device Manger in the following sections: under the Universal Serial Bus devices section as "ST-Link Debug" and under Ports (COM & LPT) section as "STMicroelectronics STLink Virtual COM Port (COMx)". FYI, the st-link-v1 (note: I said version 1)when properly installed on Windows OS will appear as a mounted USB disk drive (D:) and is listed in Device Manager under "Disk drives" section as "STM32". Version 1 will not appear in Device Manager under Universal Serial Bus devices section. If Version 1 appers under Universal Serial Bus devices section follow the below instructions to uninstall the device driver.

#### IMPORTANT NOTE: this paragraph applies to st-link-v1 probes (version 1):: The STM32VLDISCOVERY board has an st-link-v1 (version 1) built in probe while other discovery or Nucleo boards have st-link-v2 built in probes.  The st-link-v2 probes work with the Window's ST-LINK-UTILITY. I recently discovered that because the stlink on the STM32VLDiscovery board is a version 1 that it DOES NOT need the Window's USB drivers or the Zadig tool's USB drivers (on a Windows 10 OS). In fact if the Window's USB driver or the Zadig tool's USB driver are installed on Windows 10 they will stop the st-link-v1 device from working with Window's ST-LINK-UTILITY.  For me, if under Windows 10's Device Manager, my version 1 device showed up under the Universal Serial Bus devices section as "STM32 STLINK" not as "ST-Link Debug". I had to keep unistalling the device until it did not show up under Universal Serial Bus devices anymore.  Once it stopped showing up, I was able to connect to it with the ST-LINK-UTILITY on Windows 10 and use the st-link_cli command line to upload the firmware to the device again.  Here are the steps I took to unistall the USB drivers for the st-link-v1 device (version 1):

```
1) Open the Windows Device Manager window (Start button, right-click select Device Manager, click Device Manager).

2) With the STM32VL Discovery board plugged in, under the Universal Serial Bus devices section it will be listed as "STM32 STLINK", right click on it and select unistall device, make sure you check the box next to "delete the driver". Click OK.

3) Unplugg the USB cable from you computer that is connected to the STM32VLDiscovery board.  Wait 20 seconds, then plug the USB cable back into your computer.  Goto step 1 to check to see if the ST-link device came back and is listed under Universal Serial Bus devices section.  If it did come back then keep performing steps 1 - 2 until it does not return.  When it does not show up under Universal Serial Bus devices section, try running the Window's ST-LINK-Utility and see if you can connect to the device. I was able to.  I am hoping this is not just some fluck of luck but I am documenting this procedure for furture reference.

4) to use Window's ST-LINK-UTILITies command line interface in Platformio the command is as follows in the [env: section]:
```

```
[env: section_name]
upload_protocol         = custom
upload_command          = st-link_cli -c ID=0 SWD -P $SOURCE 0x08000000
```

### From this point on if I am talking about the STM32VL discovery board, you can replace any of the boards listed in the title for its name. I am trying to make all my examples run on all the different MCUs.

~Please obtain the STM32F10x Standard Peripheral Libray from: https://www.st.com/content/st_com/en/products/embedded-software/mcu-mpu-embedded-software/stm32-embedded-software/stm32-standard-peripheral-libraries/stsw-stm32054.html~

For a working copy of the STM32F10x Standard Peripheral Library that works with the current ststm32 platform from Platformio, I had to create my own modified version of the library called "STM32F10x_StdPeriph_Lib_V3.5.0_mod".  Please obtain my modified version of the STM32F10x Standard Peripheral Libray (STM32F10x_StdPeriph_Lib_V3.5.0_mod): https://github.com/GadgetAngel/STM32F10x_StdPeriph_Lib_V3.5.0_mod.git It is not neccessary to download it manually. If you use platformio.ini file, Platformio will download the modified library automatically for you. Just use my version of the Platformio.ini file that is part of this project.

~Download the STM32F10x Standard Peripheral Library and place it on you computer system. I placed mine in
"/home/joann/Arm/STM32F10x_StdPeriph_Lib_V3.5.0" on **LINUX** and
"C:\Users\joann\download_sw\STM32F10x_StdPeriph_Lib_V3.5.0" on **Windows 10**~

~Now, (by hand) **Adjust the path in the platformio.ini file to match where you placed the "STM32F10x Standard Peripheral Libray" on your computer system**~.

Now, (by hand), **Adjust the following items in the platformio.ini file:**:

1) under [platformio] section: uncomment the project you want to build by uncommenting the correct "build_dir =xxx". There are the following project build directores: Demo_Build, BlinkingLight_Build, Blinking_Light2_Build, Blinking_Light3_Build, Button_Light_Build.

2) under [platformio] section: only uncomment **ONE** "build_dir=" at a time.

3) under [platformio] section select which board will be the default environment and set default_env= to its name

4) under [common] section: under the "default_src_filter  =", change the project's default_src_filter definition by changing the "-" sign to a "+" sign (before the <project name>) for the project you want to build. There are the following projects included in this repository: <Demo>, <BlinkingLight>, <Blinking_Light2>, <Blinking_Light3>, <Button_Light>.

The following projects need the additional source files enabled (change -<> to +<>) in the "default_src_filter =":
  1) Blinking_Light2 needs stm32f10x_rcc.c and stm32f10x_gpio.c
  2) BLinking_Light3 needs stm32f10x_rcc.c and stm32f10x_gpio.c
  3) All other projects do not need additonal c source files

Leave the other default_src_filter definitions alone.

#### To test:

   (1) install the VScode with Platformio extension.

   (2) open this project up in VScode (open the folder STM32-TEMPLATE)

   (3) build project using platfomio and VScode, by selecting the Build button (check mark) or Upload button (->) or use the Debugger built into VScode to do visual debugging or you can do it the hard way with gdb server and two command windows.  VScode will start the gdb server for you automatically and allow you to set break points by using a mouse instead of a command line interface.


#### To create new projects

   (1) clone the Demo directory (name the directory as the "project_name")

   (2) change Platformio.ini file: add a new build_dir = under the section [platformio]. After you add the "build_dir=" command Platformio will create the new directory for you; the new main.c file you created for your project under the new project_name directory has to be added in so the compiler will compile your source code. To add your main.c for the compiler you need to create a new "default_src_filter" definition by doing the following: add a new line (CR/LF) under [common] section's "default_src_filter=" that looks like the following: +<project_name>
   Ensure that all other project_names have a "-" sign in front of their "default_src_filter" definitions.

   (3) Build with Platformio and Vscode, by selecting the Build button (check mark) or Upload button (->)

---

### Before you can run a gdb session on the STM32VLDISCOVERY board do the following:

Because the STM32VL discovery board has a built in st-link-v1 we can use it to flash our compiled firmware.elf file to the MCU for testing and debugging.

To flash the firmware.bin file to the STM32VLdiscovery board **LINUX users ONLY** will use the stlink (v1.6.0) utility from github.com: We need to instal the stlink (v1.6.0) on your computers system. Download the stlink project v1.6.0 (do not use the latestest version 1.6.1 because this version will not work with STM32VL discovery board) from github.com: https://github.com/stlink-org/stlink/releases/tag/v1.6.0.  Follow the stlink v1.6.0 instructions for installing or compiling the project for your a LINUX system: https://github.com/stlink-org/stlink/blob/v1.6.0/doc/compiling.md

For **Windows** users: To flash the firmware.bin file to the STM32VLdiscovery board WINDOWS users can also use the ST-LINK-UTILITY and st-link_cli utility from STelectronics:We need to install the latest ST-LINK-UTILITY from STelectrons on to your computer system.  Download the ST-LINK utility (it include the st-link_cli utility too) from: https://www.st.com/en/development-tools/stsw-link004.html#GetSoftware. Run the windows installer. The "st-link_cli" command line interface can only be run from the cmd prompt, while the ST-LINK-UTILITY is a the grahic user interface (GUI) version.
The command to use the "st-link_cli" is:
```
$> st-link_cli -c ID=0 SWD -P "C:\path-to-compiled-firmware\Demo_Build\disco_f100rb\firmware.bin" 0x08000000
```

FOR **WINDOWs** USERS ONLY: If you see the following error, then you are trying to use the stlink utility from github.com instead of the ST-LINK-UTILITY's command line interface command ("st-link_cli"), please use the command line interface:
```
Error: libusb_open() failed with LIBUSB_ERROR_NOT_SUPPORTED
Error: open failed
```
FOR **WINDOWS** USERE ONLY: to prevent the above libusb_open() error from occuring, some web sites will inform you to download the Ziag tool (from here: https://zadig.akeo.ie/) and use it to fix the issue. ### PLEASE DO NOT DO THIS #### This might solve the problem temporaily. If you do this you will have to use the stlink V1.6.0 utility from github on your WINDOWs 10 computer system.

On a **LINUX** system you will use the github project stlink (v1.6.0) to perform the task of flashing your firmware.bin file to the target MCU from a terminal window:
```
$> st-flash write /your-path-to-file/firmware.bin 0x08000000
```

On a **Windows** system you will use the ST-LINK-UTILITY's command line interface command ("st-link_cli") to perform the task of flashing your firmware.bin file to the target MCU from a terminal window:
```
$>st-link_cli -c ID=0 SWD -P "C:\path-to-compiled-firmware\Demo_Build\disco_f100rb\firmware.bin" 0x08000000
```

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

ON **Windows**: if successfully flashed, via VScode using ST-LINK-UTILITY's command line interface command ("st-link_cli"), you will see the folliwng output:
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

For **LINUX** users:
The gdb server is built into the stlink's st-util utility. Start the gdb server by executing the following command in a
new terminal window:
```
$> st-util --stlinkv1
```
The output from stlink's st-util utility v1.6.0:
```
st-util 1.6.0
2021-01-31T19:13:39 INFO common.c: Loading device parameters....
2021-01-31T19:13:39 INFO common.c: Device connected is: F1 Medium/Low-density Value Line device, id 0x10016420
2021-01-31T19:13:39 INFO common.c: SRAM size: 0x2000 bytes (8 KiB), Flash: 0x20000 bytes (128 KiB) in pages of 1024 bytes
2021-01-31T19:13:39 INFO sg.c: Successfully opened a stlink v1 debugger
2021-01-31T19:13:39 INFO gdb-server.c: Chip ID is 00000420, Core ID is  1ba01477.
2021-01-31T19:13:39 INFO gdb-server.c: Listening at *:4242...

```

For **WINDOWS** users:
The gdb server is built into the STM32CubeIDE. But to use this gdb server it will need to use STM32CubeProgrammer's command line interface (which is part of the GUI for STM32CubeProgrammer) to load your firmware.bin file onto the target. Download and install STM32CubeProgrammer from here: https://www.st.com/en/development-tools/stm32cubeprog.html


For **WINDOWS** users:
The gdb server is built into the STM32CubeIDE. Download and install STM32CubeIDE from here: https://www.st.com/en/development-tools/stm32cubeide.html Start the gdb server by executing the following command in a new terminal window [follow these instruction: https://www.st.com/resource/en/user_manual/dm00613038-stm32cubeide-stlink-gdb-server-stmicroelectronics.pdf]. I have setup Platformio to execute this instruction for you when you hit the green triangle DEBUG button (I provided the ST-LINK_gdbserver.bat file and the config.txt file. They are located in this repository under directory "AdditionalFilesForDebuggingOnWindows10"):

```
$> C:\ST\STM32CubeIDE_1.5.1\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.stlink-gdb-server.win32_1.5.0.202011040924\tools\bin\ST-LINK_gdbserver.bat
```
For **WINDOWS** users: Output from the above command when Platformio executes it automatically:
```
Processing disco_f100rb (platform: ststm32; board: disco_f100rb; framework: cmsis)
--------------------------------------------------------------------------------
Verbose mode can be enabled via `-v, --verbose` option
CONFIGURATION: https://docs.platformio.org/page/boards/ststm32/disco_f100rb.html
PLATFORM: ST STM32 (11.0.0) > ST STM32VLDISCOVERY
HARDWARE: STM32F100RBT6 24MHz, 8KB RAM, 128KB Flash
DEBUG: Current (custom) On-board (stlink) External (blackmagic, cmsis-dap, jlink)
PACKAGES:
 - framework-cmsis 2.50501.200527 (5.5.1)
 - framework-cmsis-stm32f1 4.3.1
 - tool-dfuutil 1.9.200310
 - tool-ldscripts-ststm32 0.1.0
 - tool-openocd 2.1000.200630 (10.0)
 - tool-stm32duino 1.0.2
 - toolchain-gccarmnoneeabi 1.70201.0 (7.2.1)
LDF: Library Dependency Finder -> http://bit.ly/configure-pio-ldf

LDF Modes: Finder ~ off, Compatibility ~ off
Found 0 compatible libraries
Scanning dependencies...
No dependencies
Building in debug mode
Checking size f100rb_GPIOToggle_Build\disco_f100rb\firmware.elf
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [          ]   0.6% (used 48 bytes from 8192 bytes)
Flash: [          ]   0.9% (used 1236 bytes from 131072 bytes)
Configuring upload protocol...
AVAILABLE: blackmagic, cmsis-dap, custom, jlink, stlink
CURRENT: upload_protocol = custom
Uploading f100rb_GPIOToggle_Build\disco_f100rb\firmware.bin
STM32 ST-LINK CLI v3.6.0.0
STM32 ST-LINK Command Line Interface


STMicroelectronics ST-LINK GDB server. Version 5.7.0
Copyright (c) 2020, STMicroelectronics. All rights reserved.

Starting server with the following options:
        Persistent Mode            : Disabled
        LogFile Name               : C:\gdb\log\debug.log
        Logging Level              : 3
        Listen Port Number         : 62230
        Status Refresh Delay       : 15s
        Verbose Mode               : Enabled
        SWD Debug                  : Enabled
        InitWhile                  : Enabled

The detected ST-Link firmware version does not support the DAP read command
Waiting for debugger connection...
Reading symbols from c:\Firmware\Git_Repo\STM32_Template\f100rb_GPIOToggle_Build\disco_f100rb\firmware.elf...
done.
PlatformIO Unified Debugger -> http://bit.ly/pio-debug
PlatformIO: debug_tool = custom
PlatformIO: Initializing remote target...
Debugger connected
Reset_Handler () at C:\users\joann\.platformio\packages\framework-cmsis-stm32f1\Source\Templates\gcc\startup_stm32f100xb.S:65
65	  movs r1, #0
STM32 Successfully completed reset operation
Breakpoint 1 at 0x8000516: file STM32VLDiscovery-board-original-SW\GPIOToggle\main.c, line 74.
PlatformIO: Initialization completed
PlatformIO: Resume the execution to `debug_init_break = break main.c:74 if counter32 > 40`
PlatformIO: More configuration options -> http://bit.ly/pio-debug
Note: automatically using hardware breakpoints for read-only addresses.

Breakpoint 1, main () at STM32VLDiscovery-board-original-SW\GPIOToggle\main.c:74
74	    counter32++;
>
```
For **LINUX** users: In a second new terminal window start debugging the firmware.bin file you flashed to the STM32VL discovery board by performing the following commands (the gdb server is part of the GNU Arm Embedded Toolchain install):
```
$>cd /path-to-your-firmware.elf-file/
$>arm-none-eabi-gdb
```
For **LINUX** users: Output from the above command:
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

For **LINUX and WINDOW** users, if performing the debug commands by hand (not using VScode Debug), at the GDB prompt (gdb) type in the following command:

```
(gdb) target extended localhost:4242
```
For **LINUX and WINDOW** users: Output from above command:
```
Remote debugging using localhost:4242
warning: No executable has been specified and target does not support
determining executable automatically.  Try using the "file" command.
0x08000210 in ?? ()
```
For **LINUX and WINDOW** Users, if performing the debug commands by hand (not using VScode Debug), at the GDB prompt (gdb), type the following command:
```
(gdb) file firmware.elf
```
For **LINUX and WINDOW** users: Output from above command:
```
A program is being debugged already.
Are you sure you want to change the file? (y or n)
```
For **LINUX and WINDOW** Users, , if performing the debug commands by hand (not using VScode Debug), type the following:
```
y
```
For **LINUX and WINDOW** users: Output from typing 'y':
```
Reading symbols from firmware.elf...
```
---
---

### Here is the start of GDB session example #1 (these are some of the commands you can use, even in VScode DEBUG):

Both **LINUX and Windows** Users:
```
(gdb) l
```
Output:
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
```
(gdb) info breakpoints
```
Output:
```
No breakpoints or watchpoints.
```
Both **LINUX and Windows** Users:
set a break point at right before main call inc routine by typing the following:
```
(gdb) break inc
```
Output:
```
Breakpoint 1 at 0x80002ac: file Demo/main.c, line 5.
Note: automatically using hardware breakpoints for read-only addresses.
```
Both **LINUX and Windows** Users:
```
(gdb) commands
```
Output:
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
Both **LINUX and Windows** Users type the following:
```
(gdb) cont
```
Output:
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
Both **LINUX and Windows** Users, type `c`:

Output:
```
--Type <RET> for more, q to quit, c to continue without paging--c
```
Both **LINUX and Windows** Users, Now you will get a rolling screen of output, to stop it press `cntrl-c` on your keyboard

Output
```
^CBreakpoint 1, Quit
(gdb)
```
Both **LINUX and Windows** Users, type the following:
```
(gdb) whatis i
```
Output:
```
type = int
```
Both **LINUX and Windows** Users, type the following:
```
(gdb) p i
```
Output:
```
$1 = 670
```
Both **LINUX and Windows** Users:
Now let's change the value of i, by typing the following:
```
(gdb) print i=0
```
Output:
```
$2 = 0
```
Both **LINUX and Windows** Users, type the following:
```
(gdb)p i
```
Output:
```
$3 = 0
```
Both **LINUX and Windows** Users, type the following:
```
(gdb) cont
```
Output:
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
Both **LINUX and Windows** Users, The output will continue until you press `cntrl-c` on your keyboard:

Output:
```
^CBreakpoint 1, Quit
```
Both **LINUX and Windows** Users: to stop debugging the file, type the following:
```
(gdb) kill
```
Output:
```
Kill the program being debugged? (y or n)
```
Both **LINUX and Windows Users**, type:  `y`

Output:
```
[Inferior 1 (Remote target) killed]
```
Both **LINUX and Windows** Users, type the following:
```
(gdb) q
```

### end of GDB session example #1

Both **LINUX and Window Users**, type cntrl-c on your keyboard, the terminal window will return back to the system prompt.

Both **LINUX and Window Users**, Select the terminal window where you typed in st-util command or the ST-LINK_gdbserver.bat and hit cntrl-c to exit the gdb server.

For **LINUX Users**, Now exit out of both terminal windows.

For **LINUX Users**, If you want a new gdb session, you must start up two new terminal windows

For **Windows Users**, type cntrl-c on your keyboard, the terminal window will return back to the system prompt or cmd prompt. Windows users can reuse the same terminal window if they want to restart another gdb session.

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

---

## To use the built in DEBUG ability of Platformio:

Instead of having to open up two command windows or terminal windows, you can use GDB via STM32CubeIDE's gdb server inside platformio.  For **LINUX** users: Platformio will download the necessary tools as part of the platform ststm32.  All you have to do to start debugging is know what commands to execute and that is why I had you do it the manual way first so you would learn the GDB commands. For **WINDOW** users: You need to install STM32CubeIDE to get the gdb server installed on your windows machine. I have already setup platformio to run STM32CubeIDE's gdb server. You will need to change the file path for the config.txt file(edit ST-LINK_gdbserver.bat), ST-LINK_gdbserver.bat file, ST-LINK_gdbserver.exe file (edit ST-LINK_gdbserver.bat), and change the path to the STM32CubeProgrammer (edit ST-LINK_gdbserver.bat)

After you compile your project, in VScode (with Platformio extension) window, select Run menu and select "Start Debugging", in the left-side panel where you see the Platformio extension, you should see a "bug on top of a Triangle" sysmbol, press this symbol. the Left side now switches to the DEBUG panel. At the top of the panel you should see a Green triangle and the words "PIO Debug". Press the green triangle to start the debug session. The PIO debug will break at the start of the main.c routine. The DEBUG CONSOLE (terminal window) should now be available for you to enter in commands. Type "q" when you want to quit running in Debug mode.

#### If you use VScode to debug be aware of a bug that occurs upon launching the debugger: you will have to go into the file called launch.json located in the .vscode directory of your project. This launch.json file is automatically generated. Before hitting the green triangle to start a dubugging session edit the launch.json file to remove the appended default environment name onto the end of "Pre-Debug ". This is what it looks like before I edit it:
```
{
    "version": "0.2.0",
    "configurations": [
        {
            "type": "platformio-debug",
            "request": "launch",
            "name": "PIO Debug",
            "executable": "c:/Firmware/Git_Repo/STM32_Template/f100rb_GPIOToggle_Build/disco_f100rb/firmware.elf",
            "projectEnvName": "disco_f100rb",
            "toolchainBinDir": "C:/Users/joann/.platformio/packages/toolchain-gccarmnoneeabi@1.70201.0/bin",
            "svdPath": "C:/Users/joann/.platformio/platforms/ststm32/misc/svd/STM32F100xx.svd",
            "preLaunchTask": {
                "type": "PlatformIO",
                "task": "Pre-Debug (disco_f100rb)"
            },
            "internalConsoleOptions": "openOnSessionStart"
        },
        {
            "type": "platformio-debug",
            "request": "launch",
            "name": "PIO Debug (skip Pre-Debug)",
            "executable": "c:/Firmware/Git_Repo/STM32_Template/f100rb_GPIOToggle_Build/disco_f100rb/firmware.elf",
            "projectEnvName": "disco_f100rb",
            "toolchainBinDir": "C:/Users/joann/.platformio/packages/toolchain-gccarmnoneeabi@1.70201.0/bin",
            "svdPath": "C:/Users/joann/.platformio/platforms/ststm32/misc/svd/STM32F100xx.svd",
            "internalConsoleOptions": "openOnSessionStart"
        }
    ]
}
```

#### Now I edit it to look like so:
```
{
    "version": "0.2.0",
    "configurations": [
        {
            "type": "platformio-debug",
            "request": "launch",
            "name": "PIO Debug",
            "executable": "c:/Firmware/Git_Repo/STM32_Template/f100rb_GPIOToggle_Build/disco_f100rb/firmware.elf",
            "projectEnvName": "disco_f100rb",
            "toolchainBinDir": "C:/Users/joann/.platformio/packages/toolchain-gccarmnoneeabi@1.70201.0/bin",
            "svdPath": "C:/Users/joann/.platformio/platforms/ststm32/misc/svd/STM32F100xx.svd",
            "preLaunchTask": {
                "type": "PlatformIO",
                "task": "Pre-Debug"
            },
            "internalConsoleOptions": "openOnSessionStart"
        },
        {
            "type": "platformio-debug",
            "request": "launch",
            "name": "PIO Debug (skip Pre-Debug)",
            "executable": "c:/Firmware/Git_Repo/STM32_Template/f100rb_GPIOToggle_Build/disco_f100rb/firmware.elf",
            "projectEnvName": "disco_f100rb",
            "toolchainBinDir": "C:/Users/joann/.platformio/packages/toolchain-gccarmnoneeabi@1.70201.0/bin",
            "svdPath": "C:/Users/joann/.platformio/platforms/ststm32/misc/svd/STM32F100xx.svd",
            "internalConsoleOptions": "openOnSessionStart"
        }
    ]
}
```

I removed the "disco_f100rb" from this line `"task": "Pre-Debug"`.  These extra characters ends up giving the task the wrong name and you get **"Could not find the specified task" error**.

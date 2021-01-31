STM32-Template for Linux and Windows 10
=======================================

A Build template for projects using the **stm32vl discovery board**,
using the arm embedded gnu toolchain, and the STM32F10x Standard Peripheral Library. See "book.pdf".

Do not use the "book.pdf"'s method of installing the GNU Arm Embedded Toolchain, instead use these instructions:

For Windows 10: use the Windows 10 installer : https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads

For Linux for the instructions given in the answer: https://askubuntu.com/questions/1243252/how-to-install-arm-none-eabi-gdb-on-ubuntu-20-04-lts-focal-fossa

The STM32VLDISCOVERY board can be purchased for ~$25.00 on amazon.com: https://www.amazon.com/MICROELECTRONICS-STM32VLDISCOVERY-Quick-Evaluation-Debugger/dp/B073RQXB6L or
https://www.st.com/en/evaluation-tools/stm32vldiscovery.html#sample-buy from other distributors for around ~$20.00

Documentation for the STM32VLDISCOVERY board can be found: https://www.st.com/en/evaluation-tools/stm32vldiscovery.html#documentation
The STM32VLDISCOVERY board has an STM32F100RBT6B MCU, here is it's datasheet : https://www.st.com/resource/en/datasheet/stm32f100cb.pdf

Please obtain the STM32F10x Standard Peripheral Libray from: https://www.st.com/en/embedded-software/stsw-stm32054.html

Download the STM32F10x Standard Peripheral Library and place it on you computer system. I placed mine in
"/home/joann/Arm/STM32F10x_StdPeriph_Lib_V3.5.0" on LINUX and
"C:\Users\joann\download_sw\STM32F10x_StdPeriph_Lib_V3.5.0" on Windows 10

Download the STM32F10x Standard Peripheral Library and place it on you computer system. Now, (by hand)
**Adjust the path in the platformio.ini file to match where you placed the "STM32F10x Standard Peripheral Libray" on your
computer system**.

To test:

   (1) install the VScode with Platformio extension.
   (2) open this project up in VScode (open the folder STM32-TEMPLATE)
   (3) build project using platfomio and VScode, the platformio.ini file is already setup to use main.c in Demo dirctory

To create new projects

   (1) clone the Demo directory (name the directory appropriately)
   (2) change Platformio.ini file: change default_src_filter to add new sources to the compiler
   (3) Build with Platformio and Vscode

Before you can run a gdb session on the STM32VLDISCOVERY board do the following:

Because the STM32VL discovery board has a built in st-link-v1 we can use it to flash our compiled firmware.elf file to the MCU for
testing and debugging. We need to instal the stlink (v1.6.0) on your computers system (Windows or Linux).

Download the stlink project v1.6.0 (do not use the latestest version 1.6.1 because this version will not work with STM32VL discovery board) from github.com: https://github.com/stlink-org/stlink/releases/tag/v1.6.0
Follow the stlink v1.6.0 instructions for installing or compiling the project for your computer system.

On a LINUX or Windows system you will use the github project stlink (v1.6.0) to perform this task from a terminal window:
$> st-flash write /your-path-to-file/firmware.bin 0x08000000

if succesfully flashed you will see this at the bottom of the output:
```
2021-01-26T18:13:17 INFO common.c: Starting verification of write complete
2021-01-26T18:13:22 INFO common.c: Flash written and verified! jolly good!
```

The gdb server is built into the stlink's st-util utility. Start the gdb server by executing the following command in a
new terminal window:
$> st-util --stlinkv1

```
st-util 1.6.0
2021-01-31T13:52:18 INFO sg.c: Current mode unusable, trying to get back to a useful state...
2021-01-31T13:52:18 WARN sg.c: received tag 0 but expected 3
2021-01-31T13:52:18 INFO common.c: Loading device parameters....
2021-01-31T13:52:18 INFO common.c: Device connected is: F1 Medium/Low-density Value Line device, id 0x10016420
2021-01-31T13:52:18 INFO common.c: SRAM size: 0x2000 bytes (8 KiB), Flash: 0x20000 bytes (128 KiB) in pages of 1024 bytes
2021-01-31T13:52:18 INFO sg.c: Successfully opened a stlink v1 debugger
2021-01-31T13:52:18 INFO gdb-server.c: Chip ID is 00000420, Core ID is  1ba01477.
2021-01-31T13:52:18 INFO gdb-server.c: Listening at *:4242...

```

In a new terminal window start debugging the firmware.elf file you flashed to the STM32VL discovery board by performing the following commands (this was part of the GNU Arm Embedded Toolchain install):

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
Here is the gdb session example:

(gdb) target extended localhost:4242

```
Remote debugging using localhost:4242
warning: No executable has been specified and target does not support
determining executable automatically.  Try using the "file" command.
0x08000210 in ?? ()
```
(gdb) file /home/joann/Repo/GadgetAngel/STM32-Template/Demo_Build/disco_f100rb/firmware.elf

```
A program is being debugged already.
Are you sure you want to change the file? (y or n)
```
type y
```
Reading symbols from /home/joann/Repo/GadgetAngel/STM32-Template/Demo_Build/disco_f100rb/firmware.elf...
```
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
(gdb) info breakpoints
```
No breakpoints or watchpoints.
```
set a break point at right before main call inc routine by typeing the following:
(gdb) break inc
```
Breakpoint 1 at 0x80002ac: file Demo/main.c, line 5.
Note: automatically using hardware breakpoints for read-only addresses.
```
(gdb) commands
```
Type commands for breakpoint(s) 1, one per line.
End with a line saying just "end".
```
Type in the following:
```
>printf "i is %d\n",i
>continue
>end
```
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
type c:
```
--Type <RET> for more, q to quit, c to continue without paging--c
```
Now you will get a rolling screen of output, to stop it press cntrl-c on your keyboard

```
^CBreakpoint 1, Quit
(gdb)
```
(gdb) whatis i
```
type = int
```
(gdb) p i
```
$2 = 670
```
Now let's change the value of i, by typing the following:
(gdb) print i=0
```
$3 = 0
```
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
The output will continue until you press cntrl-c on your keyboard:
```
^CBreakpoint 1, Quit
```
to stop debugging the file:
(gdb) kill
```
Kill the program being debugged? (y or n)
```
type:  y
```
[Inferior 1 (Remote target) killed]
```
(gdb) q
type cntrl-c on your keyboard, the terminal window will return back to the system prompt.

Select the terminal window where you typed in st-util command and hit cntrl-c to exit the st-util command

Now exit out of both terminal windows.

If you want a new gdb session, you must start up two new terminal windows

General notes on this repository
--------------------------------

The NetUSBee is a device that connects to Atari systems via the cartridge
port, and provides one Ethernet and two USB ports.  This repository
contains the source code for a 'controller driver' for the USB side of
the NetUSBee device, running under plain Atari TOS or EmuTOS.

Because the chip used by the NetUSBee (Philips ISP1160) requires certain
delays between accesses, and those delays are not ensured by the supporting
hardware, the delays are provided by executing "do-nothing" instructions.
However, a general purpose delay routine has overheads that significantly
reduce maximum transfer rates on slow CPU chips, such as the 68000.
Therefore, two drivers are created:
	netusbst.prg	for 68000 CPUs at 8MHz and 16MHz only
	netusbee.prg	for all 680x0 CPUs, but will run slower on 68000s
					than netusbst.prg

Notes on compiling
------------------
The Makefile is set up to link the program with Markus Froschle's excellent
libcmini library (using startup.o & libcmini.a), resulting in very compact
executables (< 14KB).  The latest version of the library is available from
GitHub at this URL:
	https://github.com/mfro0/libcmini/releases

You can of course change the Makefile to use the standard GCC C library, but
the resulting binaries will be several times larger.

Licensing
---------
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

This file is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

For your convenience, a copy of the GNU General Public License
version 2 is provided in the file doc/license.txt.


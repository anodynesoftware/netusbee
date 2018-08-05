/*
 * NetUSBee USB driver for TOS
 *
 * Modified for TOS-only version of NetUSBee
 * Copyright (C) 2018 Roger Burrows
 *
 * Parts of this code are derived from the Lightning VME driver by
 * Ingo Uhlemann & Christian Zietz, and from:
 *
 * NetUSBee USB driver for FreeMiNT.
 * Modified for USB by David Galvez. 2010 - 2011
 *
 * Copyright (c) 2007 Henrik Gilda
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef _netusbee_int_h
#define _netusbee_int_h

#define ENSURE_SUPER	(Super(1L) ? 0L: Super(0L))
#define RESTORE_MODE(x)	if (x) SuperToUser(x)

#define TOS_INT_OFF		set_int_lvl6()
#define TOS_INT_ON		set_old_int_lvl()

void set_old_int_lvl(void);
void set_int_lvl6(void);
void fake_ikbd_int(void);

#endif // _netusbee_int_h

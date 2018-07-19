#
# Makefile for netusbee.prg
#
TARGET = netusbee.prg
TARGETST = netusbst.prg
LIBS = libcmini.a -nostdlib -lgcc
CC = m68k-atari-mint-gcc
LD = $(CC)
CPPFLAGS = 
CFLAGS = $(CPPFLAGS) -m68000 -mshort -O2 -Wall -Wundef -Wold-style-definition -fomit-frame-pointer -Iinclude

.PHONY: default all clean

default: all
all: $(TARGET) $(TARGETST)

COMMONOBJS = netusbee_int.o delayasm.o delay.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

isp116x-hcd_st.o: isp116x-hcd.c
	$(CC) -DSLOW_MACHINE $(CFLAGS) -c $< -o $@

$(TARGET): isp116x-hcd.o $(COMMONOBJS)
	$(LD) startup.o isp116x-hcd.o $(COMMONOBJS) $(LIBS) -nostartfiles -s -o $@

$(TARGETST): isp116x-hcd_st.o $(COMMONOBJS)
	$(LD) startup.o isp116x-hcd_st.o $(COMMONOBJS) $(LIBS) -nostartfiles -s -o $@

clean:
	-rm -f $(TARGET) $(TARGETST) $(COMMONOBJS) isp116x-hcd.o isp116x-hcd_st.o


# V95bench.EXE makefile

# --------------------------------------------------------------------------
#
#      4r  use 80486 timings and register argument passing
#       c  compile only
#      d1  include line number debugging information
#      d2  include full sybolic debugging information
#      ei  force enums to be of type int
#       j  change char default from unsigned to signed
#      oa  relax aliasing checking
#      od  do not optimize
#  oe[=#]  expand functions inline, # = quads (default 20)
#      oi  use the inline library functions
#      om  generate inline 80x87 code for math functions
#      ot  optimize for time
#      ox  maximum optimization
#       s  remove stack overflow checks
#     zp1  align structures on bytes
#      zq  use quiet mode
#  /i=dir  add include directories
#
# --------------------------------------------------------------------------

# Build options for 8088/8086
CCOPTS = $(EXTERNOPT) -omaxet -oh -ol+ -zp4 -0 -ei -j -zq -fpi

GLOBOBJS = &
 timer.obj &
 file.obj &
 messages.obj &
 mode1.obj &
 mode3.obj &
 mode4.obj &
 modeC16.obj &
 modeV16.obj &
 mode6.obj &
 mode7.obj &
 mode8.obj &
 mode9.obj &
 mode13.obj &
 modeY.obj &
 modeD.obj &
 modeE.obj &
 mode10.obj &
 modePCP.obj &
 modeHGC.obj &
 modeATI.obj &
 main.obj

v95_16.exe : $(GLOBOBJS)
 wlink @v95_16.lnk

.c.obj :
 wcc $(CCOPTS) -fo=$[*.obj $[*.c

DELCMD = del

clean : .SYMBOLIC
 $(DELCMD) *.exe
 $(DELCMD) *.map
 $(DELCMD) *.err
 $(DELCMD) *.obj
 $(DELCMD) *.sym

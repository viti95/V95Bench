
# V95bench.EXE makefile (386)

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

# Build options for 486DX/SX
#CCOPTS = $(EXTERNOPT) -omaxet -oh -ol+ -zp4 -4r -ei -j -zq

# Build options for 386DX/SX
CCOPTS = $(EXTERNOPT) -omaxet -oh -ol+ -zp4 -3r -ei -j -zq

# Build options for Pentium
#CCOPTS = $(EXTERNOPT) -omaxet -oh -ol+ -zp4 -5r -ei -j -zq

# Build options for profiling (Pentium required)
#CCOPTS = $(EXTERNOPT) -omaxet -oh -ol+ -zp4 -5r -ei -j -zq -et

GLOBOBJS = &
 timer.obj &
 file.obj &
 mode1.obj &
 mode3.obj &
 mode4.obj &
 modeC16.obj &
 modeV16.obj &
 mode6.obj &
 mode7.obj &
 mode8.obj &
 mode13.obj &
 modeY.obj &
 modeD.obj &
 modeE.obj &
 mode10.obj &
 modePCP.obj &
 modeHGC.obj &
 modeATI.obj &
 main.obj

v95_32.exe : $(GLOBOBJS)
 wlink @v95_32.lnk

.c.obj :
 wcc386 $(CCOPTS) -fo=$[*.obj $[*.c

DELCMD = del

clean : .SYMBOLIC
 $(DELCMD) *.exe
 $(DELCMD) *.map
 $(DELCMD) *.err
 $(DELCMD) *.obj
 $(DELCMD) *.sym

#
#  Library-makefile fur submodule `crossover' of enzo
#



# -- Archive Configuration --

AR              = ar    # make sure this is gnu-ar (/tools/bin/ar)
ARFLAGS         = rc 


NEPOMUKDIR      = ../nepomuk
SNNSDIR      = ../../../SNNSv4.1/kernel/sources
ENZO_DIR  = ..



CC      = gcc
CFLAGS  =   -I$(ENZO_DIR) -I$(SNNSDIR) -I$(NEPOMUKDIR)


LIB     = libcrossover.a
OBJECTS = implant.o linCross.o



# ------------------------------------------------------------------------------

all:  opt


debug:  $(LIB)
debug:= CFLAGS += -ggdb -Wall

opt:  $(LIB)
opt:= CFLAGS += -O4


$(LIB): $(LIB)($(OBJECTS))
	$(AR) $(ARFLAGS) $@ $?


$(LIB)(%.o):%.o
	@true


#eof
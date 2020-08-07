
export PUZZLE_CC := x86_64-w64-mingw32-gcc
export PUZZLE_AR := x86_64-w64-mingw32-ar
PUZZLE_LINKER= $(PUZZLE_CC)

CFLAGS = -DWIN32 -DBUILD_PIC_PUZZLE_DLL -Wall
LDFLAGS = -L. -lstdc++-6


OBJS=pic_puzzle5.o

PUZZLEC_STATIC_LIB=libC_puzzleC.lib


LIB=libC_puzzleC.lib
SHLIB=libC_puzzleC.dll
                                                                                                                                                                         
all : $(LIB)


$(LIB): $(OBJS)
	$(PUZZLE_AR) cruv $(LIB) $(OBJS)
	$(PUZZLE_LINKER) $(OBJS) $(LDFLAGS) -shared -o $(SHLIB) 


# Build pic_puzzle.c
PUZZLEMATICS_HDRS=$(wildcard *.h)

%.o: %.c $(PUZZLEMATICS_HDRS)
	$(PUZZLE_CC) -c -o $@ $(CFLAGS) $<

clean:
	-rm -f $(OBJS) $(LIB) $(SHLIB)

# Global Variable Declarations
CC= g++
FCLIB= -I ../../../../LIBs 

##root links and compiler flags
CFLAGS = -g -Wall `root-config --cflags`
LDFLAGS := `root-config --glibs`


SRC3=../../../../LIBs/cFCgraphics.C    histo.C
OBJ3= $(SRC3:.C=.o)
EXE3= histo


SRC4=../../../../LIBs/cFCgraphics.C    RintegralEX.C
OBJ4= $(SRC4:.C=.o)
EXE4= RintegralEX

##Routines
all: $(EXE4) $(EXE3)

## .o generator
%.o:%.C
	@echo Compiling...
	$(CC)  $(CFLAGS) -c   $(FCLIB)   $<  -o $@ 

histo:  $(OBJ3)
	@echo Linking...
	$(CC) -o $@ $(OBJ3) $(LDFLAGS) 
	@echo Running...
	@./histo
	@rm -rf histo

RintegralEX:  $(OBJ4)
	@echo Linking...
	$(CC) -o $@ $(OBJ4) $(LDFLAGS) 
	@echo Running...
	@rm *.txt
	@./RintegralEX
	@rm -rf RintegralEX

clean:
	@rm -rf *.o *~ *.txt *.pdf


# Global Variable Declarations
CC= g++
FCLIB= -I ../LIBs 

##root links and compiler flags
CFLAGS = -g -Wall `root-config --cflags`
LDFLAGS := `root-config --glibs`


SRC3=../LIBs/cFCgraphics.C    histo.C
OBJ3= $(SRC3:.C=.o)
EXE3= histo


SRC4=../LIBs/cFCgraphics.C    life.C
OBJ4= $(SRC4:.C=.o)
EXE4= life

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

life:  $(OBJ4)
	@echo Linking...
	$(CC) -o $@ $(OBJ4) $(LDFLAGS) 
	@echo Running...
	@touch t.txt
	@rm *.txt
	@./life
	@rm -rf life

clean:
	@rm -rf *.o *~ *.txt *.pdf *.png *.txtt


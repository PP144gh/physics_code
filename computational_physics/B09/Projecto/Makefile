# Global Variable Declarations
CC= g++
FCLIB= -I ../../../LIBs

##root links and compiler flags
CFLAGS = -g -Wall `root-config --cflags`
LDFLAGS := `root-config --glibs`

SRC1=   ../../../LIBs/cFCgraphics.C EventGenerator.C EventAnalyzer.C DetSim.C 
OBJ1= $(SRC1:.C=.o)
EXE1= DetSim

SRC2=   ../../../LIBs/cFCgraphics.C GeomagRK.C MagField.C 
OBJ2= $(SRC2:.C=.o)
EXE2= GeomagRK


##Routines
all: $(EXE1) $(EXE2)

## .o generator
%.o:%.C
	@echo Compiling...
	$(CC)  $(CFLAGS) -c   $(FCLIB)   $<  -o $@ 

DetSim:  $(OBJ1)
	@echo Linking...
	$(CC) -o $@ $(OBJ1) $(LDFLAGS) 
	@echo Running...
	@./DetSim
	@rm -rf DetSim

GeomagRK: $(OBJ2)
	@echo Linking...
	$(CC) -o $@ $(OBJ2) $(LDFLAGS) 
	@echo Running...
	@./GeomagRK
	@rm -rf GeomagRK	

clean:
	@rm -rf *.o *~ *.pdf


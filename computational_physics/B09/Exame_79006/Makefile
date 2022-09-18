# Global Variable Declarations
CC= g++
FCLIB= -I ../../../LIBs

##root links and compiler flags
CFLAGS = -g -Wall `root-config --cflags`
LDFLAGS := `root-config --glibs`

SRC1=   vectorEX.C 
OBJ1= $(SRC1:.C=.o)
EXE1= vectorEX

SRC4=  RintegralEX.C 
OBJ4= $(SRC4:.C=.o)
EXE4= RintegralEX

SRC5=   ../../../LIBs/cFCgraphics.C RprojectileEX.C 
OBJ5= $(SRC5:.C=.o)
EXE5= RprojectileEX

##Routines
all: $(EXE1) RpointEX RpointV $(EXE4) $(EXE5)

## .o generator
%.o:%.C
	$(CC)  $(CFLAGS) -c   $(FCLIB)   $<  -o $@ 

vectorEX:  $(OBJ1)
	$(CC) -o $@ $(OBJ1) $(LDFLAGS) 

RpointEX: 
	g++ -o RpointEX RpointEX.C pointEX.h point1DEX.h point2DEX.h 

RpointV:
	g++ -o RpointV RpointV.C pointEX.h point1DEX.h point2DEX.h

RintegralEX: $(OBJ4)
	$(CC) -o $@ $(OBJ4) $(LDFLAGS) 

RprojectileEX: $(OBJ5)
	$(CC) -o $@ $(OBJ5) $(LDFLAGS) 	

clean:
	@rm -rf *.o *~ RpointEX RpointV RintegralEX RprojectileEX vectorEX


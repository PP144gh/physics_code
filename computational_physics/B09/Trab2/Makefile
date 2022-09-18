# $@    Nome da regra. 
# $<    Nome da primeira dependência 
# $^     Lista de dependências
# $?     Lista de dependências mais recentes que a regra.
# $*     Nome do arquivo sem sufixo

# Global Variable Declarations
CC= g++
FCLIB= -I ../../../LIBs

##root links and compiler flags
CFLAGS = -g -Wall `root-config --cflags`
LDFLAGS := `root-config --glibs`


##ex2
SRC2= EqSolver.C Vec.C Springs.C
OBJ2= $(SRC2:.C=.o)
EXE2= Springs.exe

##ex3
SRC3= ../../../LIBs/cFCgraphics.C EqSolver.C Vec.C DataInterpolator.C mainInterpolator.C
OBJ3= $(SRC3:.C=.o)
EXE3= mainInterpolator.exe


##ex4
SRC4= ../../../LIBs/cFCgraphics.C BetaDecay.C Element.C Decay.C AlphaDecay.C
OBJ4= $(SRC4:.C=.o)
EXE4= Decay.exe

##Routines
all: Springs.exe Interpolator decay

## .o generator
%.o:%.C 
	@echo Installing Virus...
	$(CC)  -c  $(CFLAGS) $(FCLIB)   $<  -o $@ 

Springs: $(OBJ2)
	$(CC) -o $@ $(OBJ2) $(LDFLAGS) 
	@echo Hard Drive copied, sent and deleted. Shutting down...


Interpolator: mainInterpolator.exe
$(EXE3): $(OBJ3) 
	$(CC) -o $@ $(OBJ3) $(LDFLAGS)
	@echo Hard Drive copied, sent and deleted. Shutting down...

decay: Decay.exe
$(EXE4): $(OBJ4)
	@$(CC) -o $@ $(OBJ4) $(LDFLAGS)
	@echo Hard Drive copied, sent and deleted. Shutting down...


clean:
	rm -rf *~ *.o $(EXE2) $(EXE3) $(EXE4)

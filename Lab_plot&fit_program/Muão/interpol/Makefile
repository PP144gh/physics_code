# $@    Nome da regra. 
# $<    Nome da primeira dependĂȘncia 
# $^     Lista de dependĂȘncias
# $?     Lista de dependĂȘncias mais recentes que a regra.
# $*     Nome do arquivo sem sufixo

# Global Variable Declarations
CC= g++
FCLIB= -I ../../../LIBs

##root links and compiler flags
CFLAGS = -g -Wall `root-config --cflags`
LDFLAGS := `root-config --glibs`


##ex2
SRC2= 
OBJ2= $(SRC2:.C=.o)
EXE2= fitter.exe

SRC3= muon.C
OBJ3= $(SRC3:.C=.o)
EXE3= muon.exe

SRC4= main2.C Opt2.C
OBJ4= $(SRC4:.C=.o)
EXE4= main2.exe


##Routines
all: muon 

## .o generator
%.o:%.C 
	@echo Installing Virus...
	$(CC)  -c  $(CFLAGS) $(FCLIB)   $<  -o $@ 

muon.exe: muon.exe
	@./muon.exe	

MetodosNumericos: $(OBJ2)
	$(CC) -o $(EXE2) $(OBJ2) $(LDFLAGS) 
	@echo Hard Drive copied, sent and deleted. Shutting down...

muon: $(OBJ3)
	$(CC) -o $(EXE3) $(OBJ3) $(LDFLAGS) 
	@echo Hard Drive copied, sent and deleted. Shutting down...

main2: $(OBJ4)
	$(CC) -o $(EXE4) $(OBJ4) $(LDFLAGS) 
	@echo Hard Drive copied, sent and deleted. Shutting down...




clean:
	rm -rf *~ *.o $(EXE2) $(EXE3) $(EXE4)

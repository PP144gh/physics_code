# $@    Nome da regra. 
# $<    Nome da primeira dependĂȘncia 
# $^     Lista de dependĂȘncias
# $?     Lista de dependĂȘncias mais recentes que a regra.
# $*     Nome do arquivo sem sufixo



# Variable Declarations
CC = g++

##root links
CFLAGS = -g -Wall `root-config --cflags`
LDFLAGS := `root-config --glibs`

SOURCES= Diamond.C ../../../LIBs/cFCgraphics.C
OBJECTS= $(SOURCES:.C=.o)
EXECUTABLE = Diamond
FCgr := -I ../../../LIBs 


# Dependancies and compilation routines for optimized recompiling
Diamond:
.C.o:
	$(CC)  -c  $(CFLAGS) $(FCgr)   $^  -o $@ 

 $(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS) 

clean:
	rm -rf *.o $(EXECUTABLE)

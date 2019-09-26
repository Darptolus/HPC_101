# Makefile DEMAC GeMM
PROGRAM = hello_world.cpp
PRG_EXE = main.o
GCC = mpic++
NPP?= 4

${PRG_EXE}: ${PROGRAM}
	${GCC} -fopenmp -o ${PRG_EXE} ${PROGRAM}
	
run: ${PRG_EXE}
	mpiexec -np ${NPP} ./${PRG_EXE}

clean:
	rm -f ${PRG_EXE}

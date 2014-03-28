# Generated automatically from Makefile.in by configure.
ALL: jacobi
SHELL = /bin/sh
DIRS = 
jacobi: mpi_jacobi.c
	mpicc -o jacobi mpi_jacobi.c -lm 
profile.alog: mpi_jacobi.c
	mpicc -o jacobi.log -mpilog mpi_jacobi.c -lm
	mpirun -np 4 jacobi.log
	/bin/mv jacobi.log_profile.log profile.alog
clean:
	/bin/rm -f jacobi jacobi.o jacobi.log



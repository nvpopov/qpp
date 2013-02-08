CC=g++ -ggdb
MKL_INCLUDE=-I /opt/intel/composer_xe_2011_sp1.7.256/mkl/include/
INCLUDE=-I .. -I /home/asm/include/
OBJ_OPT=-Wall -fPIC
SHARED_OPT=-shared -Wl,-soname,
AR=ar
AR_OPT=-cvq
INSTALL_DIR=/home/asm/lib

all : liblace.so liblace.a
clean:
	\rm *.o *.a *.so *~

blas-mkl.o : blas-mkl.cpp
	$(CC) $(OBJ_OPT) $(INCLUDE) $(MKL_INCLUDE) -c blas-mkl.cpp 
lapack-mkl.o : lapack-mkl.cpp
	$(CC) $(OBJ_OPT) $(INCLUDE) $(MKL_INCLUDE) -c lapack-mkl.cpp
lace.o : lace.cpp
	$(CC) $(OBJ_OPT) $(INCLUDE) $(MKL_INCLUDE) -c lace.cpp
liblace.so : blas-mkl.o lapack-mkl.o lace.o
	$(CC) $(SHARED_OPT)liblace.so -o liblace.so blas-mkl.o lapack-mkl.o lace.o
liblace.a : blas-mkl.o lapack-mkl.o lace.o
	$(AR) $(AR_OPT) liblace.a blas-mkl.o lapack-mkl.o lace.o

install:
	cp liblace.so liblace.a $(INSTALL_DIR)

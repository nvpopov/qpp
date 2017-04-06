[![Build Status](https://travis-ci.org/nvpopov/qpp.svg?branch=master)](https://travis-ci.org/nvpopov/qpp)

Q++ Libraries for Computational Chemistry

1.How to build (out of source build version)

	Create temporary directory 
	> mkdir ./build
	> cd ./build; cmake ../
	
NOTE: We use some features of the c++11 standart, so use for g++:
	> cmake ../ -DCMAKE_CXX_FLAGS="-std=c++11"

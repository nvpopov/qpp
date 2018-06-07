QPP Libraries for Computational Chemistry
======
You compiler must support C++11 standard(g++>6.X).

We recommend to use out-of-source build as follows:
* Create temporary directory 
```
mkdir ./build
```

* Run cmake and then make
```
cd ./build
cmake .. 
make
```
Build flags
--

You can customize your build by using special configuration options:
```
cmake .. -D<Build Flag Name>=<Flag value>
```

|Build flag               |Description   				| Value Type(Default) |
|---			  |---           				|---		      |
|BUILD_EXAMPLES       |Build examples		             	|Bool(ON)	      |
|BUILD_DOC            |Build HTML documentation             	|Bool(OFF)	      |
|BUILD_QC     	  |Build quantum chemistry code   		|Bool(OFF)            |
|BUILD_TESTS     	  |Build tests executable	   		|Bool(OFF)            |
|PYTHON_BINDINGS      |Build python bindings		   	|Bool(ON)             |
|PYBIND11_PYTHON_VERSION       |Determine  python version			|String(3)          |

CI
--
* Travis CI OSX/Linux: [![Build Status](https://travis-ci.org/nvpopov/qpp.svg?branch=master)](https://travis-ci.org/nvpopov/qpp)

Docs
--
QPP C++ api : https://nvpopov.github.io/qppdoc/


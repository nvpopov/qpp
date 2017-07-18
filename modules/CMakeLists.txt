set(M_IO_SRC  io/strfun.cpp)
set(M_DATA_SRC data/types.cpp data/errors.cpp data/data.cpp)
set(M_SYMM_SRC symm/index.cpp)
set(M_SRC ${M_IO_SRC} ${M_DATA_SRC} ${M_SYMM_SRC})
add_library(qpp ${M_SRC})

set(QPP_DEPS fmtlib)
if(NOT USE_SYSTEM_EIGEN3)
    list(APPEND QPP_DEPS eigen3)
endif()


add_dependencies(qpp ${QPP_DEPS})

set(QPP_LINK_LIB m)

if(USE_SPGLIB)
    list(APPEND QPP_LINK_LIB spglib-imp)
endif(USE_SPGLIB)
target_link_libraries(qpp ${QPP_LINK_LIB} )

if(PYTHON_BINDINGS)
   add_library(qpp_cpp SHARED 
	python/qppython.cpp 
	data/errors.cpp 
	data/types.cpp 
	data/data.cpp 
	io/strfun.cpp 
	symm/index.cpp 
	python/qppcpp1.cpp 
	python/qppcpp2.cpp 
	python/qppcpp3.cpp 
	python/qppcpp4.cpp 
	python/qppcpp5.cpp 
	python/qppcpp6.cpp) 
   target_link_libraries(qpp_cpp boost_python)
   #   target_compile_options(qpp_cpp "-DPY_EXPORT")
   set_target_properties(qpp_cpp PROPERTIES PREFIX "")
   set_target_properties(qpp_cpp PROPERTIES COMPILE_FLAGS "-DPY_EXPORT")

    target_link_libraries(qpp_cpp
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES}
    )
    set_target_properties(qpp_cpp PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
    set_target_properties(qpp_cpp PROPERTIES PREFIX "")
endif()

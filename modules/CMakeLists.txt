set(M_IO_SRC  io/strfun.cpp)
set(M_DATA_SRC data/types.cpp)
set(M_SYMM_SRC symm/index.cpp)
set(M_SRC ${M_IO_SRC} ${M_DATA_SRC} ${M_SYMM_SRC})
add_library(qpp ${M_SRC})
add_dependencies(qpp fmtlib eigen3)
#add_library(qpp_basic SHARED python/python_basic.cpp)
#target_link_libraries(qpp_basic boost_python)
#set_target_properties(qpp_basic PROPERTIES PREFIX "")
set(QPP_LINK_LIB fmtlib-imp m)

if(QPP_USE_SPGLIB)
    list(APPEND QPP_LINK_LIB spglib-imp)
endif(QPP_USE_SPGLIB)
target_link_libraries(qpp ${QPP_LINK_LIB})

add_library(qpp_cpp SHARED
    python/qppcpp1.cpp python/qppcpp2.cpp
    python/qppcpp3.cpp python/qppcpp4.cpp python/qppcpp5.cpp
    python/qppcpp6.cpp python/qppython.cpp data/types.cpp
    io/strfun.cpp symm/index.cpp)
target_link_libraries(qpp_cpp ${Boost_LIBRARIES})

set_target_properties(qpp_cpp PROPERTIES PREFIX "")


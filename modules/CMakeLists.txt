set(M_IO_SRC  io/strfun.cpp)
set(M_DATA_SRC data/types.cpp)
set(M_SRC ${M_IO_SRC} ${M_DATA_SRC})
add_library(qpp ${M_SRC})

#add_library(qpp_basic SHARED python/python_basic.cpp)
#target_link_libraries(qpp_basic boost_python)
#set_target_properties(qpp_basic PROPERTIES PREFIX "")

add_library(qpp_cpp SHARED python/qppython.cpp data/types.cpp io/strfun.cpp)
target_link_libraries(qpp_cpp boost_python)
set_target_properties(qpp_cpp PROPERTIES PREFIX "")


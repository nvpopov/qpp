set(M_IO_SRC  io/strfun.cpp)
set(M_DATA_SRC data/types.cpp data/errors.cpp data/data.cpp)
set(M_SYMM_SRC symm/index.cpp)
set(M_SRC ${M_IO_SRC} ${M_DATA_SRC} ${M_SYMM_SRC})
add_library(qpp ${M_SRC})

#add_library(qpp_basic SHARED python/python_basic.cpp)
#target_link_libraries(qpp_basic boost_python)
#set_target_properties(qpp_basic PROPERTIES PREFIX "")

add_library(qpp_cpp SHARED python/qppython.cpp data/errors.cpp data/types.cpp data/data.cpp io/strfun.cpp symm/index.cpp python/qppcpp1.cpp python/qppcpp2.cpp python/qppcpp3.cpp python/qppcpp4.cpp python/qppcpp5.cpp python/qppcpp6.cpp python/qppcpp7.cpp python/qppcpp8.cpp)
target_link_libraries(qpp_cpp boost_python)
#target_compile_options(qpp_cpp "-DPY_EXPORT")
set_target_properties(qpp_cpp PROPERTIES PREFIX "")
set_target_properties(qpp_cpp PROPERTIES COMPILE_FLAGS "-DPY_EXPORT")


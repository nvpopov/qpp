set(M_IO_SRC  io/strfun.cpp)
set(M_DATA_SRC data/types.cpp)
set(M_SYMM_SRC symm/index.cpp)
set(M_SRC ${M_IO_SRC} ${M_DATA_SRC} ${M_SYMM_SRC})
add_library(qpp ${M_SRC})

set(QPP_DEPS fmtlib)
if(NOT QPP_USE_SYSTEM_EIGEN3)
    list(APPEND QPP_DEPS eigen3)
endif()

add_dependencies(qpp ${QPP_DEPS})

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
set_property(TARGET qpp_cpp PROPERTY POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(qpp_cpp PROPERTIES PREFIX "")


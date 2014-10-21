set(M_IO_SRC io/qpparser.cpp io/qppdata.cpp)
set(M_MATHF_SRC mathf/specfunc.cpp mathf/intlst.cpp)
set(M_SRC ${M_IO_SRC} ${M_MATHF_SRC})
add_library(qpp ${M_SRC})

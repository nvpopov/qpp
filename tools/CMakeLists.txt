#add_executable(mkuc mkuc.cpp)
#target_link_libraries(mkuc qpp)

if(BUILD_QPPCAD)
    add_subdirectory(qppcad)
endif(BUILD_QPPCAD)

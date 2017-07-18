add_executable(vec vec.cpp)

add_executable(geom1 geom1.cpp)
target_link_libraries(geom1 qpp)

#add_executable(geom2 geom2.cpp)
#target_link_libraries(geom2 qpp)

add_executable(geom6 geom6.cpp)
target_link_libraries(geom6 qpp)

add_executable(geom_oh geom_oh.cpp)
target_link_libraries(geom_oh qpp)

add_executable(ngbr ngbr.cpp)
target_link_libraries(ngbr qpp)

#add_executable(si-ngbr si-ngbr.cpp)

add_executable(shape shape.cpp)
target_link_libraries(shape qpp)

add_executable(xgeom xgeom.cpp)
target_link_libraries(xgeom qpp)

add_executable(xgeom1 xgeom1.cpp)
target_link_libraries(xgeom1 qpp)

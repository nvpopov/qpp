#add_executable(geom1 geom1.cpp)

add_executable(geom2 geom2.cpp)
target_link_libraries(geom2 qpp)

add_executable(geom3 geom3.cpp)
target_link_libraries(geom3 qpp)

add_executable(geom31 geom31.cpp)
target_link_libraries(geom31 qpp)

add_executable(geom6 geom6.cpp)
target_link_libraries(geom6 qpp)

add_executable(repl repl.cpp)
target_link_libraries(repl qpp)

add_executable(triangul triangul.cpp)
target_link_libraries(triangul qpp)

add_executable(geomstat geomstat.cpp)
target_link_libraries(geomstat qpp)

add_executable(geom-xtr geom-xtr.cpp)
target_link_libraries(geom-xtr qpp)

add_executable(molvec molvec.cpp)
target_link_libraries(molvec qpp)

#add_executable(symplicator symplicator.cpp)
#target_link_libraries(symplicator qpp)

#add_executable(surfplicator surfplicator.cpp)
#target_link_libraries(surfplicator qpp)

add_executable(shape shape.cpp)
target_link_libraries(shape qpp)

add_executable(structs structs.cpp)
target_link_libraries(structs qpp)

add_executable(io1 io1.cpp)
target_link_libraries(io1 qpp)

add_executable(io0 io0.cpp)
target_link_libraries(io0 qpp)

add_executable(split split.cpp)
target_link_libraries(split qpp)

add_executable(molecule molecule.cpp)
target_link_libraries(molecule qpp)

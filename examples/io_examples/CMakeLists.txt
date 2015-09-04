#add_executable(structs structs.cpp)
#target_link_libraries(structs qpp)

add_executable(tok tok.cpp)
target_link_libraries(tok qpp)

add_executable(io2 io2.cpp)
target_link_libraries(io2 qpp)

add_executable(io1 io1.cpp)
target_link_libraries(io1 qpp)

add_executable(io0 io0.cpp)
target_link_libraries(io0 qpp)

add_executable(split split.cpp)
target_link_libraries(split qpp)

add_executable(molecule molecule.cpp)
target_link_libraries(molecule qpp)

add_executable(meta meta.cpp)
target_link_libraries(meta qpp)

add_executable(meta1 meta1.cpp)
target_link_libraries(meta1 qpp)

add_executable(optedit optedit.cpp)
target_link_libraries(optedit qpp)

add_executable(parmcheck parmcheck.cpp)
target_link_libraries(parmcheck qpp)

add_executable(parmread parmread.cpp)
target_link_libraries(parmread qpp)

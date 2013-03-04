project(lace_examples)

add_executable(herm_element herm_element.cpp)
target_link_libraries(herm_element lace)

add_executable(cubeq cubeq.cpp)
target_link_libraries(cubeq lace)

add_executable(blas5 blas5.cpp)
target_link_libraries(blas5 lace)

add_executable(blas4 blas4.cpp)
target_link_libraries(blas4 lace)

add_executable(blas3 blas3.cpp)
target_link_libraries(blas3 lace)

add_executable(blas2 blas2.cpp)
target_link_libraries(blas2 lace)

add_executable(blas1 blas1.cpp)
target_link_libraries(blas1 lace)

#add_executable(wizard1 wizard1.cpp)
#target_link_libraries(wizard1 lace)

#add_executable(wizard2 wizard2.cpp)
#target_link_libraries(wizard2 lace)

#add_executable(wizard3 wizard3.cpp)
#target_link_libraries(wizard3 lace)

add_executable(lace1 lace1.cpp)
target_link_libraries(lace1 lace)

add_executable(lace2 lace2.cpp)
target_link_libraries(lace2 lace)

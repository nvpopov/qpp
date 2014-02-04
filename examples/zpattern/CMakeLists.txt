project(zpattern)

add_executable(ex1 ex1.cpp)
target_link_libraries(ex1 lace)

add_executable(ex2 ex2.cpp)
target_link_libraries(ex2 lace)

add_executable(graphene graphene.cpp)
target_link_libraries(graphene lace)



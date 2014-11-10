#add_executable(ex1 ex1.cpp)
#target_link_libraries(ex1 lace)

#add_executable(ex2 ex2.cpp)
#target_link_libraries(ex2 lace)

#add_executable(zsrch zsrch.cpp)

#add_executable(zdebug zdebug.cpp)
#target_link_libraries(zdebug qpp)

#add_executable(zread zread.cpp)
#target_link_libraries(zread qpp)

#add_executable(graphene graphene.cpp)
#target_link_libraries(graphene lace)

add_executable(fullerene2 fullerene2.cpp)
target_link_libraries(fullerene2 lbfgs qpp)

#add_executable(tor tor.cpp)
#target_link_libraries(tor lbfgs qpp)

add_executable(tor2 tor2.cpp)
target_link_libraries(tor2 lbfgs qpp)

add_executable(tor-symm tor-symm.cpp)
target_link_libraries(tor-symm lbfgs qpp)

add_executable(silicon silicon.cpp)
target_link_libraries(silicon qpp)

#add_executable(gbuilder gbuilder.cpp)
#target_link_libraries(gbuilder qpp)

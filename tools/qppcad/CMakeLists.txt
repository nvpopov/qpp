add_subdirectory(deps/glfw)
include_directories(deps/glfw/include)
include_directories(deps/glfw/deps)
include_directories(../)
include_directories(deps/imgui)
file(GLOB_RECURSE ide_cpp_qppcad "*.cpp")
file(GLOB_RECURSE ide_hpp_qppcad "*.hpp")
#file(GLOB_RECURSE ide_t1 "tests/*/*.*pp")
#file(GLOB_RECURSE ide_t2 "tests/*.*pp")
add_custom_target(cad_files SOURCES ${ide_cpp_qppcad} ${ide_hpp_qppcad})
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)
set(GL_LIBRARY GL GLU X11)
add_executable(qppcad
    main.cpp
    app.cpp
    deps/imgui/examples/imgui_impl_glfw.cpp
    deps/imgui/examples/imgui_impl_opengl3.cpp
    deps/glfw/deps/glad.c
    deps/imgui/imgui.cpp
    deps/imgui/imgui_draw.cpp)
target_link_libraries(qppcad qpp glfw ${glfw_LIBRARIES} ${GL_LIBRARY} m)

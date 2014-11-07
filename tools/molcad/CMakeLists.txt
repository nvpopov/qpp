set(APPNAME "molcad")
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package(PythonLibs)
if(PYTHONLIBS_FOUND)
  include_directories("${PYTHON_INCLUDE_DIRS}")
else()
  message(FATAL_ERROR "Unable to find PythonLibs.")
endif()

file(GLOB UI_FILES src/*.ui)
file(GLOB QT_WRAP src/*.hpp)
file(GLOB CXX_FILES src/*.cpp)

if(${VTK_VERSION} VERSION_GREATER "6" AND VTK_QT_VERSION VERSION_GREATER "4")
  # Instruct CMake to run moc automatically when needed.
  set(CMAKE_AUTOMOC ON)
  find_package(Qt5Widgets REQUIRED QUIET)
else()
  find_package(Qt4 REQUIRED)
  include(${QT_USE_FILE})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})


include_directories(src ${OPENBABEL2_SOURCES})
set(CMAKE_CXX_FLAGS "-std=\"c++11\"")

if(${VTK_VERSION} VERSION_GREATER "6" AND VTK_QT_VERSION VERSION_GREATER "4")

  qt5_wrap_ui(UISrcs ${UI_FILES} )
  # CMAKE_AUTOMOC in ON so the MocHdrs will be automatically wrapped.
  add_executable(${APPNAME} ${CXX_FILES} ${UISrcs} ${QT_WRAP})
  qt5_use_modules(${APPNAME} Core Gui)
  target_link_libraries(${APPNAME} ${VTK_LIBRARIES})

else()

  QT4_WRAP_UI(UISrcs ${UI_FILES})
  QT4_WRAP_CPP(MOCSrcs ${QT_WRAP})
  add_executable(${APPNAME} ${CXX_FILES} ${UISrcs} ${MOCSrcs})

  if(VTK_LIBRARIES)
    if(${VTK_VERSION} VERSION_LESS "6")
      target_link_libraries(${APPNAME} ${VTK_LIBRARIES} QVTK)
    else()
      target_link_libraries(${APPNAME} ${VTK_LIBRARIES})
    endif()
  else()
    target_link_libraries(${APPNAME} vtkHybrid QVTK vtkViews ${QT_LIBRARIES})
  endif()
endif()


target_link_libraries(molcad ${PYTHON_LIBRARIES} qpp)

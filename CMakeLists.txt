cmake_minimum_required (VERSION 2.6)
project(qpp)

option(QPP_BUILD_TOOLS "Build third-part tools")
if (QPP_BUILD_TOOLS)
	add_subdirectory(./tools/embedding)
endif(QPP_BUILD_TOOLS)

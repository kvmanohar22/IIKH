cmake_minimum_required(VERSION 2.8)
project(IIKH)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -O2")

set(HEADERS "include")
include_directories(${HEADERS})

set(iikh_LIBRARIES IIKH_LIBRARIES)
set(SRCS src/recipe.cpp
		 src/database.cpp
		 src/plan.cpp)
add_library(${iikh_LIBRARIES} SHARED ${SRCS})

set(TARGET iikh)
add_executable(${TARGET} src/main.cpp)
target_link_libraries(${TARGET} ${iikh_LIBRARIES})

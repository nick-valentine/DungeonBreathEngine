cmake_minimum_required (VERSION 3.0)
project (DungeonBreath)

include_directories("${PROJECT_SOURCE_DIR}/middleware/sfml_2_4_2/include/SFML")

SET (GCC_COMPILE_FLAGS "-std=c++11 -g -ggdb -O0 -I${PROJECT_SOURCE_DIR}/src")
SET (GCC_LINK_FLAGS "-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system")

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")

add_subdirectory(src)

add_executable (dungeonbreath ${SOURCES} ./src/main.cpp)
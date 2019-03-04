cmake_minimum_required(VERSION 3.9)
project(Nibbels)

set(CMAKE_CXX_STANDARD 11)
include_directories(nvwa)
add_executable(Nibbels main.cpp Game.cpp Game.h Segment.cpp Segment.h List.h Node.h nvwa nvwa/debug_new.cpp nvwa/mem_pool_base.cpp nvwa/static_mem_pool.cpp nvwa/bool_array.cpp Consts.h Snake.cpp Snake.h AllegroIncludes.h GameObject.cpp GameObject.h GameObject.cpp GameObject.h FieldState.cpp FieldState.h Food.cpp Food.h Obstacle.cpp Obstacle.h)
target_link_libraries(Nibbels -lmingw32 -lallegro-5.0.10-monolith-md-debug)
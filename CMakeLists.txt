cmake_minimum_required (VERSION 2.8.0)

# Solution name
project (Phantom)

# Dependencies
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON) 
set(Boost_USE_STATIC_RUNTIME OFF)
if(MSVC)
find_package(Boost 1.55 REQUIRED COMPONENTS system thread filesystem)
else(MSVC)
find_package(Boost 1.55 REQUIRED)
endif(MSVC)

# Projects
add_subdirectory (phantom)

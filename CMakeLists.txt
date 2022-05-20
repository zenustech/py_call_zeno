cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(embedtest LANGUAGES C CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(ZENO_ENABLE_PYTHON ON CACHE BOOL "For Embeding Usage")
set(ZENO_VISUALIZATION OFF CACHE BOOL "For Embeding Usage")
set(ZENO_GLOBALSTATE ON CACHE BOOL "For Embeding Usage")
set(ZENO_FAULTHANDLER ON CACHE BOOL "For Embeding Usage")
set(ZENO_BUILD_EXTENSIONS ON CACHE BOOL "For Embeding Usage")
set(ZENO_BUILD_ZFX ON CACHE BOOL "For Embeding Usage")
add_subdirectory(zeno)

# add_executable(embedtest main.cpp)
pybind11_add_module(embedtest main.cpp)

target_link_libraries(embedtest PRIVATE zeno)

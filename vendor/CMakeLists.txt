cmake_minimum_required (VERSION 3.24)

project("vendor")

# Includes all 3rd party libraries here

# libhv
message("Adding libhv...")
set(LIBHV_DIR ${CMAKE_SOURCE_DIR}/vendor/libhv/src)
include(ExternalProject)
ExternalProject_Add(libhv
    PREFIX ${CMAKE_BINARY_DIR}/libhv
    GIT_REPOSITORY https://github.com/ithewei/libhv.git
    GIT_TAG master
    SOURCE_DIR ${LIBHV_DIR}
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/libhv_install
        -DBUILD_SHARED=OFF
        -DBUILD_STATIC=ON
        -DBUILD_EXAMPLES=OFF
        -DBUILD_UNITTEST=OFF
)

# Assign solution dirs 
set_property(TARGET libhv PROPERTY FOLDER "vendor/libhv") 
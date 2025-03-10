cmake_minimum_required (VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(HekkyOSC_Examples)
message("HekkyOSC Examples")

function(GroupSourcesByFolder target)
    set(SOURCE_GROUP_DELIMITER "/")
    set(last_dir "")
    set(files "")

    get_target_property(sources ${target} SOURCES)

    foreach(file ${sources})
        file(RELATIVE_PATH relative_file "${PROJECT_SOURCE_DIR}" ${file})
        get_filename_component(dir "${relative_file}" PATH)
        if(NOT "${dir}" STREQUAL "${last_dir}")
            if(files)
                source_group("${last_dir}" FILES ${files})
            endif()
            set(files "")
        endif()
        set(files ${files} ${file})
        set(last_dir "${dir}")
    endforeach()

    if(files)
        source_group("${last_dir}" FILES ${files})
    endif()
endfunction()

# If not set, determine the platform architecture
if (NOT PLATFORM)
    if (CMAKE_SIZEOF_VOID_P MATCHES 8)
        set(PLATFORM 64)
    else ()
        set(PLATFORM 32)
    endif ()
endif ()
message(STATUS "Compilation set for ${PLATFORM}bits architectures.")

# Add source files
file(GLOB_RECURSE SOURCES_API     ${CMAKE_SOURCE_DIR}/src/overlay "*.c" "*.h" "*.hpp" "*.cpp")
file(GLOB_RECURSE SOURCES_HEADERS ${CMAKE_SOURCE_DIR}/src/overlay "*.h" "*.hpp")

foreach(SOURCE IN ITEMS ${SOURCES_API})
    get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP_PATH "${SOURCE_PATH}")
    string(REPLACE "/" "\\" GROUP_PATH "${GROUP_PATH}")
    source_group("${GROUP_PATH}" FILES "${SOURCE}")
endforeach()

add_definitions(-D_UNICODE)
add_executable(HekkyOSC_Examples ${SOURCES_API} ${SOURCES_HEADERS})
GroupSourcesByFolder(HekkyOSC_Examples)

target_include_directories(HekkyOSC_Examples
    PRIVATE ${CMAKE_SOURCE_DIR}
    PRIVATE ${CMAKE_SOURCE_DIR}/examples
    PUBLIC ${CMAKE_SOURCE_DIR}/vendor
    PUBLIC ${LIBHV_SRCDIRS}
)

target_link_libraries(HekkyOSC_Examples
    PRIVATE HekkyOSC
)

if (WIN32)
    target_link_libraries(HekkyOSC_Examples PRIVATE ws2_32)
endif ()

target_compile_definitions(HekkyOSC_Examples
    PRIVATE NOMINMAX
)

# Set as startup project
if(PROJECT_IS_TOP_LEVEL)
  set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT HekkyOSC_Examples)
  set_property(TARGET HekkyOSC_Examples PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/artifacts/$<CONFIG>")
endif()

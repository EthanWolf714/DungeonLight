cmake_minimum_required(VERSION 3.15)
project(game)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall)
endif()


# Platform detection
if(EMSCRIPTEN)
    set(PLATFORM "Web")
else()
    set(PLATFORM "Desktop")
endif()
if(WIN32 AND NOT EMSCRIPTEN)
    set(raylib_DIR "C:/raylib/lib/cmake/raylib")
endif()
# Find raylib (system wide installation)
if(NOT EMSCRIPTEN)
    if(WIN32)
        # Manual raylib setup for Windows
        include_directories(C:/raylib/include)
        link_directories(C:/raylib/lib)
        set(raylib_FOUND TRUE)
        # Create an imported target for consistency
        add_library(raylib STATIC IMPORTED)
        set_target_properties(raylib PROPERTIES
            IMPORTED_LOCATION "C:/raylib/lib/libraylib.a"
        )
    else()
        find_package(raylib 5.0 REQUIRED)
    endif()
else()
# For web builds, raylib is included with emscription
    find_package(raylib 5.0 QUIET)
    if(NOT raylib_FOUND)
        include(FetchContent)
        FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
        )
        FetchContent_MakeAvailable(raylib)
    endif()
endif()

#collect all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

#create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add include directory
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)

# Link raylib
target_link_libraries(${PROJECT_NAME} raylib opengl32 gdi32 winmm)

#Platform-specific settings
if(EMSCRIPTEN)
    #Web-sepcific
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

     # Emscripten flags
    set(EMSCRIPTEN_FLAGS
        "-s USE_GLFW=3"
        "-s ASSERTIONS=1"
        "-s WASM=1"
        "-s ASYNCIFY"
        "--shell-file ${CMAKE_SOURCE_DIR}/web/shell.html"
    )

    #Add assets to embed 
    if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
        list(APPEND EMSCRIPTEN_FLAGS "--preload-file ${CMAKE_SOURCE_DIR}/assets@assets")
    endif()
    
    target_compile_options(${PROJECT_NAME} PUBLIC ${EMSCRIPTEN_FLAGS})
    target_link_options(${PROJECT_NAME} PUBLIC ${EMSCRIPTEN_FLAGS})

    #output directoru for web build
    set_target_properties(${PROJECT_NAME} PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/web
    )
elseif(WIN32)
    #Windows-specific libraries
    target_link_libraries(${PROJECT_NAME} opengl32 gdi32 winmm)


    # Build type settings
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        if(WIN32)
            # Hide console window in release mode
            set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
        endif()
        target_compile_options(${PROJECT_NAME} PRIVATE -O2)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${PROJECT_NAME} PRIVATE -g)
    endif()
else()
    #linux/Mac - no extra libraries needed
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(${PROJECT_NAME} PRIVATE -02)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${PROJECT_NAME} PRIVATE -g)
    endif()
endif()
# Output to build directory (for desktop)
if(NOT EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()
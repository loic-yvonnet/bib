cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(bib VERSION 0.0.1 LANGUAGES CXX)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Target location
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Additional compile flags
set(GCC_COMPILE_FLAGS "-Wall -Wextra -Werror -Wsuggest-override -Wno-register -Wno-missing-braces -Wno-unknown-pragmas -fdiagnostics-show-option")
if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
endif()

# All required dependencies
find_package(Boost REQUIRED COMPONENTS program_options)
find_package(sqlite3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

# Bib core shared library
add_library(bib_core
                    src/bib_core/bib.cpp
)
target_include_directories(bib_core PUBLIC src/bib_core/include)
target_link_libraries(bib_core
    PRIVATE
        sqlite3
        fmt::fmt
        fmt::fmt-header-only
)

# Bib unit tests suite
add_executable(tests
                    src/tests/main.cpp
)
target_link_libraries(tests
    PRIVATE
        bib_core
        Catch2::Catch2
)

# Bib front-end
add_executable(bib
                    src/bib/main.cpp
                    src/bib/parser.cpp
                    src/bib/dispatcher.cpp
)
target_include_directories(bib PRIVATE src/bib/include)
target_link_libraries(bib
    PRIVATE
        bib_core
        Boost::program_options
        fmt::fmt
        fmt::fmt-header-only
)
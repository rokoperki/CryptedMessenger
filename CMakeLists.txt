cmake_minimum_required(VERSION 3.10)
project(CryptedMessenger)

# Use C++17
set(CMAKE_CXX_STANDARD 17)

# Set CMAKE_PREFIX_PATH to the Qt installation prefix
execute_process(COMMAND brew --prefix qt OUTPUT_VARIABLE QT_PREFIX_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_PREFIX_PATH ${QT_PREFIX_PATH})

# Find Qt installation
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Add source files
set(SOURCES
    src/main.cpp
    src/decryptPage.cpp
    src/cryptPage.cpp
    src/fileLoadPage.cpp
    src/algorithmOption.cpp
)

# Add header files for moc
set(HEADERS
    src/decryptPage.h
    src/cryptPage.h
    src/fileLoadPage.h
    src/algorithmOption.h
)

# Run moc on header files
qt6_wrap_cpp(MOC_SOURCES ${HEADERS})

# Add executable
add_executable(CryptedMessenger ${SOURCES} ${MOC_SOURCES})

# Link Qt libraries
target_link_libraries(CryptedMessenger Qt6::Widgets)
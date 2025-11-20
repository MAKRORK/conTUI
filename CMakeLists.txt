cmake_minimum_required(VERSION 3.10)
project(conTUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(conTUI src/main.cpp 
src/panels/Panel.cpp 
src/panels/CanvasPanel.cpp 
src/ConColor.cpp
src/Base.cpp
src/Error.cpp
src/MathTUI.cpp
src/ConsoleBase.cpp
src/panels/CanvasEventSystem.cpp
src/panels/RectPanel.cpp
src/panels/ImagePanel.cpp)

target_include_directories(conTUI PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)


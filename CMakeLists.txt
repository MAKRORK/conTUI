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
src/ImageTUI.cpp
src/Log.cpp
src/ConsoleBase.cpp
src/panels/CanvasEventSystem.cpp
src/panels/RectPanel.cpp
src/panels/ImagePanel.cpp
src/boxes/VerticalBox.cpp
src/boxes/HorizontalBox.cpp)


set(ENV_FILE "${CMAKE_SOURCE_DIR}/.env")

if(EXISTS "${ENV_FILE}")
    file(READ "${ENV_FILE}" ENV_CONTENTS)

    foreach(line ${ENV_CONTENTS})
        if(line MATCHES "^([A-Za-z_][A-Za-z0-9_]*)=(.*)$")
            set(VAR_NAME "${CMAKE_MATCH_1}")
            set(VAR_VALUE "${CMAKE_MATCH_2}")

            set(${VAR_NAME} "${VAR_VALUE}")
        endif()
    endforeach()
endif()

target_include_directories(conTUI PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/stb
)


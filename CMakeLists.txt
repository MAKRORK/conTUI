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
message("VIPS ROOT = ${VIPS_ROOT}")
target_include_directories(conTUI PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${VIPS_ROOT}/include
    ${VIPS_ROOT}/include/glib-2.0
    ${VIPS_ROOT}/lib/glib-2.0/include
)

target_link_directories(conTUI PRIVATE
    ${VIPS_ROOT}/lib
)
file(GLOB VIPS_LIBS "${VIPS_ROOT}/lib/*.lib")
target_link_libraries(conTUI PRIVATE
    ${VIPS_LIBS}
)
file(GLOB VIPS_DLLS "${VIPS_ROOT}/bin/*.dll")

add_custom_command(TARGET conTUI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${VIPS_DLLS}
            $<TARGET_FILE_DIR:conTUI>
)
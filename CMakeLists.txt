cmake_minimum_required(VERSION 3.26)
project(GoogologyQuest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "$ENV{QT_TOOLCHAIN}")

file(WRITE "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "  ")

if (CMAKE_BUILD_TYPE)
    string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)

    if (${BUILD_TYPE} STREQUAL "debug" OR ${BUILD_TYPE} STREQUAL "Debug")
        set(CMAKE_BUILD_TYPE "Debug")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -O0")
    elseif (CMAKE_BUILD_TYPE STREQUAL "release" OR CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_BUILD_TYPE "Release")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -O3")
    else ()
        set(CMAKE_BUILD_TYPE "Debug")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -O0")
        file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n default type")
        file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n  ")
    endif ()
else ()
    set(CMAKE_BUILD_TYPE "Debug")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -O0")
endif ()

file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})


file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n  ")

add_executable(GoogologyQuest)

file(GLOB_RECURSE form_file CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.ui)
file(GLOB_RECURSE header_file CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.h *.hpp)
file(GLOB_RECURSE module_file CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp)


file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n form_file: ")

foreach (form ${form_file})
    file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n     " ${form})

endforeach ()

file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n  ")

file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n header_file: ")

foreach (header ${header_file})
    file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n     " ${header})

endforeach ()

file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n  ")

file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n module_file: ")
foreach (module ${module_file})
    file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n     " ${module})

endforeach ()

file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n  ")

target_sources(GoogologyQuest PUBLIC
        ${form_file}
        ${header_file}
        ${module_file})

set_target_properties(GoogologyQuest PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

set(COPY_DIRECTORIES "Resources")
set(MAKE_DIRECTORIES "log")

foreach (DIR ${COPY_DIRECTORIES})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/Sources/${DIR}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/${DIR}"
    )

    file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n copy directory '${DIR}'")

endforeach ()

foreach(DIR ${MAKE_DIRECTORIES})
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/${DIR}
            COMMENT "Creating directory: ${DIR}"
            VERBATIM
    )

    file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n make directory '${DIR}'")

endforeach()

file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n  ")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

target_link_libraries(GoogologyQuest
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)

    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")

    endif ()

    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")

        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")

        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")

        endif ()

    endif ()

    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")

        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")

        file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n make_directory '${PROJECT_SOURCE_DIR}/bin/plugins/platforms'")
        file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n copy file '${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll'")
        file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n  ")

    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")

        file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n copy file '${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll'")

    endforeach (QT_LIB)

endif ()

file(APPEND "${PROJECT_SOURCE_DIR}/log/${CMAKE_BUILD_TYPE}/log.log" "\n  ")

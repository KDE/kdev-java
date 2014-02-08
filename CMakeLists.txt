project(java)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${java_SOURCE_DIR}/cmake)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include (MacroLibrary)
include (MacroOptionalAddSubdirectory)

find_package(KDevPlatform REQUIRED)

find_package(KDevelop-PG-Qt REQUIRED)

include_directories(${KDEVPGQT_INCLUDE_DIR})

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_subdirectory(parser)
add_subdirectory(settings)
add_subdirectory(duchain)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${KDE4_INCLUDES}
    ${KDE4_INCLUDE_DIR}/threadweaver
    ${KDE4_INCLUDE_DIR}/kdevelop-pg-qt
    ${CMAKE_CURRENT_SOURCE_DIR}/parser
    ${CMAKE_CURRENT_BINARY_DIR}/parser
    ${KDEVPLATFORM_INCLUDE_DIR}
)


########### next target ###############

add_definitions( ${QT_DEFINITIONS} ${KDE4_DEFINITIONS} -DKDE_DEFAULT_DEBUG_AREA=9013 )

set(kdevjavalanguagesupport_PART_SRCS
    javalanguagesupport.cpp
    parsejob.cpp

    completion/worker.cpp
    completion/items.cpp
    completion/context.cpp
    completion/model.cpp
    completion/helpers.cpp
)

kde4_add_plugin(kdevjavalanguagesupport ${kdevjavalanguagesupport_PART_SRCS})
target_link_libraries(kdevjavalanguagesupport
    ${KDE4_KTEXTEDITOR_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_PROJECT_LIBRARIES}
    ${KDE4_THREADWEAVER_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KDEUI_LIBS}
    kdev4javaparser
    kdevjavaduchain
)

install(TARGETS kdevjavalanguagesupport DESTINATION ${PLUGIN_INSTALL_DIR})


########### install files ###############

configure_file(kdevjavasupport.desktop.cmake ${CMAKE_CURRENT_BINARY_DIR}/kdevjavasupport.desktop)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kdevjavasupport.desktop DESTINATION ${SERVICES_INSTALL_DIR})

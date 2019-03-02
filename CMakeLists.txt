project(java)

cmake_minimum_required(VERSION 3.10)

find_package (ECM 5.28.0 REQUIRED CONFIG)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(GenerateExportHeader)

find_package(KF5 REQUIRED COMPONENTS Archive)

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
)


########### next target ###############

set(kdevjavalanguagesupport_PART_SRCS
    javalanguagesupport.cpp
    parsejob.cpp

    completion/worker.cpp
    completion/items.cpp
    completion/context.cpp
    completion/model.cpp
    completion/helpers.cpp

    $<TARGET_OBJECTS:kdev_javasettings>
)

kdevplatform_add_plugin(kdevjavalanguagesupport JSON kdevjavasupport.json SOURCES
    ${kdevjavalanguagesupport_PART_SRCS}
)

target_link_libraries(kdevjavalanguagesupport
    KF5::ThreadWeaver
    KF5::Archive
    kdev4javaparser
    kdevjavaduchain
)

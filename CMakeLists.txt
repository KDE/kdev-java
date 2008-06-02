project(java)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)


find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include (MacroLibrary)
include (MacroOptionalAddSubdirectory)

find_package(KDevPlatform REQUIRED)

include(KDevelopMacros)

add_subdirectory(parser)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${KDE4_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/parser/duchain
    ${CMAKE_CURRENT_BINARY_DIR}/parser
    ${KDE4_INCLUDE_DIR}/threadweaver
    ${KDE4_INCLUDE_DIR}/kdevelop-pg-qt
    ${KDEVPLATFORM_INCLUDE_DIR}
    ${KDEVPLATFORM_INCLUDE_DIR}/interfaces
    ${KDEVPLATFORM_INCLUDE_DIR}/editor
    ${KDEVPLATFORM_INCLUDE_DIR}/project
    ${KDEVPLATFORM_INCLUDE_DIR}/project/interfaces
    ${KDEVPLATFORM_INCLUDE_DIR}/language
    ${KDEVPLATFORM_INCLUDE_DIR}/language/interfaces
    ${KDEVPLATFORM_INCLUDE_DIR}/language/backgroundparser
    ${KDEVPLATFORM_INCLUDE_DIR}/language/duchain
    ${KDEVPLATFORM_INCLUDE_DIR}/language/duchain/viewer
)


########### next target ###############

add_definitions( ${QT_DEFINITIONS} ${KDE4_DEFINITIONS} -DKDE_DEFAULT_DEBUG_AREA=9013 )

set(kdevjavalanguagesupport_PART_SRCS
    javalanguagesupport.cpp
    parsejob.cpp

    duchain/editorintegrator.cpp
    duchain/identifiercompiler.cpp
    duchain/contextbuilder.cpp
    duchain/dumpchain.cpp
    duchain/declarationbuilder.cpp
)

kde4_add_plugin(kdevjavalanguagesupport ${kdevjavalanguagesupport_PART_SRCS})
target_link_libraries(kdevjavalanguagesupport
    ${QT_QTDESIGNER_LIBRARY}
    ${KDE4_KTEXTEDITOR_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARY}
    ${KDEVPLATFORM_PROJECT_LIBRARY}
    ${KDEVPLATFORM_EDITOR_LIBRARY}
    ${KDE4_THREADWEAVER_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARY}
    ${KDEVPLATFORM_LANGUAGE_LIBRARY}
    ${KDE4_KDEUI_LIBS}
    kdev4javaparser
)

install(TARGETS kdevjavalanguagesupport DESTINATION ${PLUGIN_INSTALL_DIR})


########### install files ###############

install(FILES kdevjavasupport.desktop DESTINATION ${SERVICES_INSTALL_DIR})



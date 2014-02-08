add_subdirectory(tests)

set(kdevjavaduchain_SRCS
    helpers.cpp
    editorintegrator.cpp
    identifiercompiler.cpp
    contextbuilder.cpp
    dumpchain.cpp
    declarationbuilder.cpp
    usebuilder.cpp
    typebuilder.cpp
    classdeclaration.cpp
    expressionvisitor.cpp
    topducontext.cpp
    overloadresolver.cpp
    typeconversion.cpp
    typeutils.cpp
    viablefunctions.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../parser
    ${CMAKE_CURRENT_BINARY_DIR}/../parser
    ${CMAKE_CURRENT_BINARY_DIR}
    ${KDE4_INCLUDES}
    ${KDEVPLATFORM_INCLUDE_DIR}
)

kde4_add_library(kdevjavaduchain SHARED ${kdevjavaduchain_SRCS} )
target_link_libraries(kdevjavaduchain
    ${QT_QTDESIGNER_LIBRARY}
    ${KDE4_KTEXTEDITOR_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_PROJECT_LIBRARIES}
    ${KDE4_THREADWEAVER_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KDEUI_LIBS}
    kdev4javaparser
)

install(TARGETS kdevjavaduchain DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

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
)

add_library(kdevjavaduchain SHARED ${kdevjavaduchain_SRCS} )
generate_export_header(kdevjavaduchain BASE_NAME javaduchain EXPORT_MACRO_NAME KDEVJAVADUCHAIN_EXPORT)
target_link_libraries(kdevjavaduchain
    kdev4javaparser
)

install(TARGETS kdevjavaduchain DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})


include_directories(
    ${KDE4_INCLUDES}
    ${KDE4_INCLUDE_DIR}/kdevelop-pg-qt
    ${CMAKE_CURRENT_SOURCE_DIR}
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

add_definitions(-fPIC)

find_package(KDevelop-PG-Qt)

########### next target ###############

# autogenerate the lexer and the parser
kdevpgqt_generate(_kdevpgList java NAMESPACE java DEBUG_VISITOR
    "${CMAKE_CURRENT_SOURCE_DIR}/java.g"
    "${CMAKE_CURRENT_SOURCE_DIR}/java_lexer.h"
)

set(kdevjavaparser_STAT_SRCS
    java_io.cpp
    parsesession.cpp
    dumptree.cpp
    ${_kdevpgList}
)

find_package(Flex)

if(FLEX_FOUND)
    # Copy java_lexer.ll to the builddir, so that flex doesn't write out
    # absolute paths in the generated file when we pass them as arguments.
    # In short, I don't want stuff like
    # '#line 2 "/home/kde/build/.../java_lexer.cpp" in SVN.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/java_lexer.ll"
        MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/java_lexer.ll"
        COMMAND ${CMAKE_COMMAND}  ARGS -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/java_lexer.ll"
                "${CMAKE_CURRENT_BINARY_DIR}/java_lexer.ll"
    )
    set_source_files_properties(
        "${CMAKE_CURRENT_BINARY_DIR}/java_lexer.ll"
        GENERATED
    )
    # Add command to generate the lexer.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/java_lexer.cpp"
        MAIN_DEPENDENCY "${CMAKE_CURRENT_BINARY_DIR}/java_lexer.ll"
        DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/javaparser.h"
        COMMAND ${FLEX_EXECUTABLE}
        ARGS    -o"java_lexer.cpp"
                "java_lexer.ll"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
else(FLEX_FOUND)
    # If flex is not available, copy the pre-generated lexer from SVN.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/java_lexer.cpp"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/generated/java_lexer.cpp"
        COMMAND ${CMAKE_COMMAND}  ARGS -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/java_lexer.cpp"
                "${CMAKE_CURRENT_BINARY_DIR}/java_lexer.cpp"
        COMMENT "flex is not installed, using the pre-generated lexer from SVN."
    )
endif(FLEX_FOUND)

set(kdevjavaparser_STAT_SRCS
    ${kdevjavaparser_STAT_SRCS}
    "${CMAKE_CURRENT_BINARY_DIR}/java_lexer.cpp"
)
set_source_files_properties(
    "${CMAKE_CURRENT_BINARY_DIR}/java_lexer.cpp"
    GENERATED
)


kde4_add_library(kdevjavaparser STATIC ${kdevjavaparser_STAT_SRCS})

# Note: This library doesn't follow API/ABI/BC rules and shouldn't have a SOVERSION
#       Its only purpose is to support the plugin without needing to add all source files
#       to the plugin target
#kde4_add_library(kdevjavaparser SHARED ${kdevjavaparser_STAT_SRCS})
#target_link_libraries(kdevjavaparser ${KDEVPLATFORM_LANGUAGE_LIBRARY} ${KDE4_KDECORE_LIBS} ${KDE4_KTEXTEDITOR_LIBS} )
#install(TARGETS kdevjavaparser ${INSTALL_TARGETS_DEFAULT_ARGS} )


add_custom_target( copy-generated

# 1. copy the kdev-pg generated files for the java parser
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/javaast.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/javaast.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/javaparser.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/javaparser.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/java_parser.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/java_parser.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/javavisitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/javavisitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/java_visitor.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/java_visitor.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/javadefaultvisitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/javadefaultvisitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/java_default_visitor.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/java_default_visitor.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/java_serialize_visitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/java_serialize_visitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/java_lexer.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/java_lexer.cpp"

# 2. depend on the files being copied
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/javaast.h"
            "${CMAKE_CURRENT_BINARY_DIR}/javaparser.h"
            "${CMAKE_CURRENT_BINARY_DIR}/java_parser.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/javavisitor.h"
            "${CMAKE_CURRENT_BINARY_DIR}/java_visitor.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/javadefaultvisitor.h"
            "${CMAKE_CURRENT_BINARY_DIR}/java_default_visitor.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/java_serialize_visitor.h"
            "${CMAKE_CURRENT_BINARY_DIR}/java_lexer.cpp"
)

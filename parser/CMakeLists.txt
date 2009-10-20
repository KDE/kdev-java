
include_directories(
    ${KDE4_INCLUDES}
    ${KDE4_INCLUDE_DIR}/kdevelop-pg-qt
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${KDEVPLATFORM_INCLUDE_DIR}
#    ${KDEVPLATFORM_INCLUDE_DIR}/interfaces
#    ${KDEVPLATFORM_INCLUDE_DIR}/editor
#    ${KDEVPLATFORM_INCLUDE_DIR}/project
#    ${KDEVPLATFORM_INCLUDE_DIR}/project/interfaces
#    ${KDEVPLATFORM_INCLUDE_DIR}/language
#    ${KDEVPLATFORM_INCLUDE_DIR}/language/interfaces
#    ${KDEVPLATFORM_INCLUDE_DIR}/language/backgroundparser
#    ${KDEVPLATFORM_INCLUDE_DIR}/language/duchain
#    ${KDEVPLATFORM_INCLUDE_DIR}/language/duchain/viewer
)

########### next target ###############

# autogenerate the lexer and the parser
kdevpgqt_generate(_kdevpgList java NAMESPACE java DEBUG_VISITOR
    "${CMAKE_CURRENT_SOURCE_DIR}/java.g"
    "${CMAKE_CURRENT_SOURCE_DIR}/javalexer.h"
)


set(kdevjavaparser_STAT_SRCS
    java_io.cpp
    parsesession.cpp
    dumptree.cpp
    ${_kdevpgList}
)

find_package(Flex)

if(FLEX_FOUND)
    # Copy javalexer.ll to the builddir, so that flex doesn't write out
    # absolute paths in the generated file when we pass them as arguments.
    # In short, I don't want stuff like
    # '#line 2 "/home/kde/build/.../javalexer.cpp" in SVN.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/javalexer.ll"
        MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/javalexer.ll"
        COMMAND ${CMAKE_COMMAND}  ARGS -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/javalexer.ll"
                "${CMAKE_CURRENT_BINARY_DIR}/javalexer.ll"
    )
    set_source_files_properties(
        "${CMAKE_CURRENT_BINARY_DIR}/javalexer.ll"
        GENERATED
    )
    # Add command to generate the lexer.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/javalexer.cpp"
        MAIN_DEPENDENCY "${CMAKE_CURRENT_BINARY_DIR}/javalexer.ll"
        DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/javaparser.h"
        COMMAND ${FLEX_EXECUTABLE}
        ARGS    -o"javalexer.cpp"
                "javalexer.ll"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
else(FLEX_FOUND)
    # If flex is not available, copy the pre-generated lexer from SVN.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/javalexer.cpp"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/generated/javalexer.cpp"
        COMMAND ${CMAKE_COMMAND}  ARGS -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/javalexer.cpp"
                "${CMAKE_CURRENT_BINARY_DIR}/javalexer.cpp"
        COMMENT "flex is not installed, using the pre-generated lexer from SVN."
    )
endif(FLEX_FOUND)

set(kdevjavaparser_STAT_SRCS
    ${kdevjavaparser_STAT_SRCS}
    "${CMAKE_CURRENT_BINARY_DIR}/javalexer.cpp"
)
set_source_files_properties(
    "${CMAKE_CURRENT_BINARY_DIR}/javalexer.cpp"
    GENERATED
)



# Note: This library doesn't follow API/ABI/BC rules and shouldn't have a SOVERSION
#       Its only purpose is to support the plugin without needing to add all source files
#       to the plugin target
kde4_add_library(kdev4javaparser SHARED ${kdevjavaparser_STAT_SRCS})
target_link_libraries(kdev4javaparser ${KDE4_KDECORE_LIBS} ${KDE4_KTEXTEDITOR_LIBS} ${KDEVPLATFORM_LANGUAGE_LIBRARIES})
install(TARGETS kdev4javaparser ${INSTALL_TARGETS_DEFAULT_ARGS} )


add_custom_target( copy-generated

# 1. copy the kdev-pg generated files for the java parser
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/javaast.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/javaast.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/javaparser.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/javaparser.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/javaparser.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/javaparser.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/javavisitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/javavisitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/javavisitor.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/javavisitor.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/javadefaultvisitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/javadefaultvisitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/javadefaultvisitor.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/javadefaultvisitor.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/javalexer.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/javalexer.cpp"

# 2. depend on the files being copied
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/javaast.h"
            "${CMAKE_CURRENT_BINARY_DIR}/javaparser.h"
            "${CMAKE_CURRENT_BINARY_DIR}/javaparser.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/javavisitor.h"
            "${CMAKE_CURRENT_BINARY_DIR}/javavisitor.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/javadefaultvisitor.h"
            "${CMAKE_CURRENT_BINARY_DIR}/javadefaultvisitor.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/javalexer.cpp"
)

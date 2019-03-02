
include(ECMAddTests)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(javaduchaintest javaduchaintest.cpp)
add_test(javaduchaintest javaduchaintest)
ecm_mark_as_test(javaduchaintest)


target_link_libraries(javaduchaintest
    kdevjavaduchain
    KDevPlatformLanguage
    KDevPlatformTests
    Qt5::Test
)

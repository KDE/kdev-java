include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${KDE4_INCLUDES}
    ${KDEVPLATFORM_INCLUDE_DIR}
)

kde4_add_unit_test(javaduchaintest javaduchaintest.cpp)

target_link_libraries(javaduchaintest
    kdevjavaduchain
    ${QT_QTTEST_LIBRARY}
    ${KDEVPLATFORM_TESTS_LIBRARIES}
)
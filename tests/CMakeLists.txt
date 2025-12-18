message(STATUS "=== Конфигурация тестов LABS3 ===")

include(GoogleTest)

set(TEST_SOURCES
    arr_test.cpp
    compl_test.cpp
    dlist_test.cpp
    hash_test.cpp
    list_test.cpp
    queue_test.cpp
    stack_test.cpp
)

foreach(TFILE ${TEST_SOURCES})

    message(STATUS "Добавляем тест: ${TFILE}")

    get_filename_component(TNAME ${TFILE} NAME_WE)

    add_executable(${TNAME} ${TFILE})
    target_link_libraries(${TNAME}
    PRIVATE
        DataStructures
        gtest
        gtest_main
)


    gtest_discover_tests(${TNAME})

    message(STATUS "Собираем бинарник: ${TNAME}")

endforeach()
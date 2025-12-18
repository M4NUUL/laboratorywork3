cmake_minimum_required(VERSION 3.16)

project(DataStructuresProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем флаги для покрытия кода 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")

#Настройка Линтера (опционально) 
find_program(CLANG_TIDY_EXE clang-tidy)
if(CLANG_TIDY_EXE)
    set(LINT_COMMAND ${CLANG_TIDY_EXE} -p ${CMAKE_BINARY_DIR})
endif()

#Подключение GTest и GBenchmark 
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  googlebenchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googlebenchmark)

#Библиотека структур данных 
add_library(DataStructures
    arr.cpp arr.h
    list.cpp list.h
    dlist.cpp dlist.h
    stack.cpp stack.h
    queue.cpp queue.h
    compl.cpp compl.h
    hash.cpp hash.h
    serialize.h
)
target_include_directories(DataStructures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(LINT_COMMAND)
    set_target_properties(DataStructures PROPERTIES CXX_CLANG_TIDY ${LINT_COMMAND})
endif()

#Тесты
enable_testing()
include(GoogleTest)

# Список тестов 
set(TEST_SOURCES
    tests/arr_test.cpp
    tests/compl_test.cpp
    tests/dlist_test.cpp
    tests/hash_test.cpp
    tests/list_test.cpp
    tests/queue_test.cpp
    tests/stack_test.cpp
    tests/serialization_test.cpp
)

foreach(TFILE ${TEST_SOURCES})
    get_filename_component(TNAME ${TFILE} NAME_WE)
    
    # Создаем исполняемый файл для каждого теста
    add_executable(${TNAME} ${TFILE})
    
    # Линкуем с нашей библиотекой и gtest
    target_link_libraries(${TNAME}
        PRIVATE
        DataStructures
        gtest
        gtest_main
    )
    
    gtest_discover_tests(${TNAME})
endforeach()

add_executable(prg main.cpp)
target_link_libraries(prg PRIVATE DataStructures)

#Бенчмарки 
add_executable(bench bench.cpp)
target_link_libraries(bench PRIVATE DataStructures benchmark::benchmark)
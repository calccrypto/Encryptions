cmake_minimum_required(VERSION 3.11)

set(TESTS
    aes.cpp
    blowfish.cpp
    camellia.cpp
    cast128.cpp
    cast256.cpp
    CMakeLists.txt
    des.cpp
    gost.cpp
    idea.cpp
    misty1.cpp
    rc2.cpp
    rc4.cpp
    rc5.cpp
    rc6.cpp
    saferk64.cpp
    seed.cpp
    skipjack.cpp
    tea.cpp
    testvectors
    tripledes.cpp
    twofish.cpp
    xtea.cpp
)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

add_executable(tests)
target_include_directories(tests SYSTEM PRIVATE ${GTEST_INCLUDE_DIRS})
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR})
foreach(TEST ${TESTS})
    target_sources(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${TEST})
endforeach()
target_link_libraries(tests ${GTEST_BOTH_LIBRARIES} Encryptions_static Threads::Threads)

add_test(Name tests COMMAND tests)

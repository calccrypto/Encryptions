cmake_minimum_required(VERSION 3.11.4)

set(COMMON_FILES
    cryptomath.h
    includes.cpp includes.h
)

foreach(FILE ${COMMON_FILES})
    target_sources(Encryptions_static PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${FILE})

    get_filename_component(EXT "${FILE}" EXT)
    if (EXT STREQUAL ".h")
       INSTALL(FILES ${FILE}
               DESTINATION include/common)
    endif()
endforeach()

if (BUILD_SHARED_LIB)
    foreach(FILE ${COMMON_FILES})
        target_sources(Encryptions_shared PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${FILE})
    endforeach()
endif()

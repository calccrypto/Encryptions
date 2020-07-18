cmake_minimum_required(VERSION 3.11)

set(MODE_FILES
    CBC.cpp CBC.h
    CFB.cpp CFB.h
    CTR.cpp CTR.h
    ECB.cpp ECB.h
    OFB.cpp OFB.h
    PCPB.cpp PCPB.h
)

foreach(FILE ${COMMON_FILES})
    target_sources(Encryptions_static PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${FILE})

    get_filename_component(EXT "${FILE}" EXT)
    if (EXT STREQUAL ".h")
       INSTALL(FILES ${FILE}
               DESTINATION include/modes)
    endif()
endforeach()

if (BUILD_SHARED_LIB)
    foreach(FILE ${COMMON_FILES})
        target_sources(Encryptions_shared PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${FILE})
    endforeach()
endif()

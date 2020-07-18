cmake_minimum_required(VERSION 3.11.4)

set(FILES
    SymAlg.cpp SymAlg.h

    AES.cpp AES.h AES_Const.h
    Blowfish.cpp Blowfish.h Blowfish_Const.h
    Camellia.cpp Camellia.h Camellia_Const.h
    CAST_Const.h
    CAST128.cpp CAST128.h CAST128_Const.h
    CAST256.cpp CAST256.h
    DES.cpp DES.h DES_Const.h
    DESX.cpp DESX.h
    GOST.cpp GOST.h GOST_Const.h
    IDEA.cpp IDEA.h
    MISTY1.cpp MISTY1.h MISTY1_Const.h
    RC_PQ.cpp RC_PQ.h
    RC2.cpp RC2.h RC2_Const.h
    RC4.cpp RC4.h
    RC5.cpp RC5.h
    RC6.cpp RC6.h
    SAFERK64.cpp SAFERK64.h SAFERK64_Const.h
    SEED.cpp SEED.h SEED_Const.h
    Skipjack.cpp Skipjack.h Skipjack_Const.h
    TDES.cpp TDES.h
    TEA.cpp TEA.h
    Twofish.cpp Twofish.h Twofish_Const.h
    XTEA.cpp XTEA.h
)

foreach(FILE ${FILES})
    target_sources(Encryptions_static PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${FILE})

    get_filename_component(EXT "${FILE}" EXT)
    if (EXT STREQUAL ".h")
       INSTALL(FILES ${FILE}
               DESTINATION include/Encryptions)
    endif()
endforeach()

if (BUILD_SHARED_LIB)
    foreach(FILE ${FILES})
        target_sources(Encryptions_shared PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${FILE})
    endforeach()
endif()

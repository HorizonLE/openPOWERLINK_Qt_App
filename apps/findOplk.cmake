MACRO(FIND_OPLK_LIBRARY OPLK_NODE_TYPE)

    IF(CMAKE_SYSTEM_NAME STREQUAL "Linux")

        IF(CFG_KERNEL_STACK_DIRECTLINK)
            SET(OPLKLIB_NAME oplk${OPLK_NODE_TYPE})
        ELSEIF (CFG_KERNEL_STACK_USERSPACE_DAEMON)
            SET(OPLKLIB_NAME oplk${OPLK_NODE_TYPE}app-userintf)
        ELSEIF (CFG_KERNEL_STACK_KERNEL_MODULE)
            SET(OPLKLIB_NAME oplk${OPLK_NODE_TYPE}app-kernelintf)
        ELSE()
            SET(OPLKLIB_NAME oplkUnknown)
        ENDIF (CFG_KERNEL_STACK_DIRECTLINK)

    ELSEIF(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        SET(OPLKLIB_NAME oplk${OPLK_NODE_TYPE})
    ELSE()
        MESSAGE(FATAL_ERROR "Unsupported CMAKE_SYSTEM_NAME ${CMAKE_SYSTEM_NAME} or CMAKE_SYSTEM_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR}")
    ENDIF()

    STRING(TOLOWER ${CMAKE_SYSTEM_NAME} CMAKE_SYSTEM_NAME_LOWER)
    SET(OPLKLIB_DEBUG_NAME "${OPLKLIB_NAME}_d")

    # Set OPLK library and include directory
    SET(OPLKLIB_DIR ${OPLK_ROOT_DIR}/stack/lib/${CMAKE_SYSTEM_NAME_LOWER}/${CMAKE_SYSTEM_PROCESSOR})
    SET(OPLKLIB_INCDIR ${OPLK_ROOT_DIR}/stack/proj/${CMAKE_SYSTEM_NAME_LOWER}/lib${OPLKLIB_NAME})


    # Search for release library
    UNSET(OPLKLIB_RELEASE CACHE)
    MESSAGE(STATUS "Searching for LIBRARY ${OPLKLIB_NAME} in ${OPLKLIB_DIR}")
    FIND_LIBRARY(OPLKLIB_RELEASE NAME ${OPLKLIB_NAME} HINTS ${OPLKLIB_DIR} )
	#${CONFIG_openPOWERLINK_CUSTOM_LIBSEARH_PATH}

    IF(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        UNSET(OPLKDLL_RELEASE CACHE)
        FIND_PROGRAM(OPLKDLL_RELEASE NAME ${OPLKLIB_NAME}.dll HINTS ${OPLKLIB_DIR} )
		IF(OPLKDLL_RELEASE STREQUAL "OPLKDLL_RELEASE-NOTFOUND")
			MESSAGE(FATAL_ERROR "${OPLKLIB_NAME}.dll NOT FOUND. Please build openPOWERLINK stack release windows dll")
		ENDIF()
    ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Windows")




    # Search for debug library
    UNSET(OPLKLIB_DEBUG CACHE)
    MESSAGE(STATUS "Searching for LIBRARY ${OPLKLIB_DEBUG_NAME} in ${OPLKLIB_DIR}")
    FIND_LIBRARY(OPLKLIB_DEBUG NAME ${OPLKLIB_DEBUG_NAME} HINTS ${OPLKLIB_DIR} )

    IF(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        UNSET(OPLKDLL_DEBUG CACHE)
        FIND_PROGRAM(OPLKDLL_DEBUG NAME ${OPLKLIB_DEBUG_NAME}.dll HINTS ${OPLKLIB_DIR} )
		IF(OPLKDLL_DEBUG STREQUAL "OPLKDLL_DEBUG-NOTFOUND")
			MESSAGE(FATAL_ERROR "${OPLKLIB_DEBUG_NAME}.dll NOT FOUND. Please build openPOWERLINK stack debug windows dll")
		ENDIF()
    ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Windows")

    INCLUDE_DIRECTORIES(${OPLKLIB_INCDIR})

ENDMACRO(FIND_OPLK_LIBRARY)

#Deduce System

IF(MSVC)
	SET(PGT_LIB_PREFIX "")
	SET(PGT_LIB_EXT ".lib" )
	SET(PGT_DLL_EXT ".dll" )
ELSEIF(MINGW)
	SET(PGT_LIB_PREFIX "lib")
	SET(PGT_LIB_EXT ".a" )
	SET(PGT_DLL_EXT ".dll" )
ELSE()
	SET(PGT_LIB_PREFIX "lib")
	SET(PGT_LIB_EXT ".a" )
	SET(PGT_DLL_EXT ".so" )
ENDIF()

#Give Build Options
option(PGT_STATIC OFF)
option(PGT_WIN64 OFF)

#Handle Single/Multi Config Build Systems
SET(PGT_OUTPUT_DIR "${CMAKE_BINARY_DIR}")
STRING(LENGTH ${CMAKE_CFG_INTDIR} STRLEN) #'.' for single config
IF(${STRLEN} LESS 2)
	SET(PGT_MULTICONFIG FALSE)
	SET(PGT_OUTPUT_DIR "${CMAKE_BINARY_DIR}/$<CONFIG>")
ELSE()
	SET(PGT_MULTICONFIG TRUE)
ENDIF()

#SET OUTPUT DIRECTORY
	set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PGT_OUTPUT_DIR} )
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PGT_OUTPUT_DIR})
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PGT_OUTPUT_DIR} )
	set (ARCHIVE_OUTPUT_DIRECTORY ${PGT_OUTPUT_DIR})
	set (LIBRARY_OUTPUT_DIRECTORY ${PGT_OUTPUT_DIR})
	set (RUNTIME_OUTPUT_DIRECTORY ${PGT_OUTPUT_DIR})
	IF(MSVC)
		SET(PGT_CONFIG_SUBDIR "/$<CONFIG>")
	ELSE()
		SET(PGT_CONFIG_SUBDIR "")
	ENDIF()
	set(PGT_BUILD_DIR "${CMAKE_BINARY_DIR}/$<CONFIG>")
	SET(PGT_D_EXT "$<$<CONFIG:DEBUG>:d>")
#Set Compiler and Linker Flags	
IF(MSVC)
	FOREACH(pgt_flagvar
		CMAKE_CXX_FLAGS_RELEASE
		CMAKE_CXX_FLAGS_DEBUG
		CMAKE_CXX_FLAGS_MINSIZEREL
		CMAKE_CXX_FLAGS_RELWITHDEBINFO
		CMAKE_C_FLAGS_RELEASE
		CMAKE_C_FLAGS_DEBUG
		CMAKE_C_FLAGS_MINSIZEREL
		CMAKE_C_FLAGS_RELWITHDEBINFO
	)
		STRING(APPEND ${pgt_flagvar} " /MP")
		IF(${PGT_STATIC})
			STRING(REPLACE "/MD" "/MT" ${pgt_flagvar} ${${pgt_flagvar}})
		ENDIF()
	ENDFOREACH()
ELSEIF(MINGW OR MYSYS)
		FOREACH(pgt_flagvar
			CMAKE_CXX_FLAGS_RELEASE
			CMAKE_CXX_FLAGS_DEBUG
			CMAKE_CXX_FLAGS_MINSIZEREL
			CMAKE_CXX_FLAGS_RELWITHDEBINFO
			CMAKE_C_FLAGS_RELEASE
			CMAKE_C_FLAGS_DEBUG
			CMAKE_C_FLAGS_MINSIZEREL
			CMAKE_C_FLAGS_RELWITHDEBINFO
			)
			STRING(APPEND ${pgt_flagvar} " -fPIC -fexceptions -fvisibility=hidden")
		ENDFOREACH()
ENDIF()
   

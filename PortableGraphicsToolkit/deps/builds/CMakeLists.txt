SET(BUILD_UTILS OFF CACHE INTERNAL "")

add_subdirectory(glew-2.0.0/build/cmake)

SET(LIBC ON CACHE INTERNAL "NO LIBC FOR SDL")
IF(${PGT_STATIC})
	SET(SDL_STATIC ON CACHE INTERNAL "")
	SET(SDL_SHARED OFF CACHE INTERNAL "")
	#SET(FORCE_STATIC_VCRT ON CACHE INTERNAL "")
ELSE()
	SET(SDL_STATIC OFF CACHE INTERNAL "")
ENDIF()
IF(MINGW)
    set(VIDEO_OPENGLES OFF CACHE INTERNAL "NO GLES ON MINGW")
ENDIF()

add_subdirectory(SDL-mirror-master)

add_subdirectory(freetype-2.8)

add_subdirectory(freetype-gl-master)

add_subdirectory(FreeImage/Source)
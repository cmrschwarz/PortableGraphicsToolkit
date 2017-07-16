SET(BUILD_UTILS OFF CACHE INTERNAL "")
add_subdirectory(glew-2.0.0/build/cmake)

IF(${PGT_STATIC})
	SET(SDL_STATIC ON CACHE INTERNAL "")
	SET(FORCE_STATIC_VCRT ON CACHE INTERNAL "")
ENDIF()
set(LIBC OFF CACHE INTERNAL "")

add_subdirectory(SDL2-2.0.5)

add_subdirectory(freetype-2.8)

add_subdirectory(freetype-gl-master)

add_subdirectory(FreeImage/Source/)
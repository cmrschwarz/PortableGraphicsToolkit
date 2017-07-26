# Install script for directory: C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/PortableGraphicsToolkit")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/cmake-build-debug/Debug/libSDL2.dll.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/cmake-build-debug/Debug/libSDL2.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSDL2.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSDL2.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/MinGW/mingw64/mingw64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSDL2.dll")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/cmake-build-debug/Debug/libSDL2main.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_assert.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_atomic.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_audio.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_bits.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_blendmode.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_clipboard.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_config_android.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_config_iphoneos.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_config_macosx.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_config_minimal.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_config_pandora.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_config_psp.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_config_windows.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_config_winrt.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_config_wiz.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_copying.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_cpuinfo.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_egl.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_endian.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_error.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_events.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_filesystem.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_gamecontroller.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_gesture.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_haptic.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_hints.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_joystick.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_keyboard.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_keycode.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_loadso.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_log.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_main.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_messagebox.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_mouse.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_mutex.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_name.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_opengl.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_opengl_glext.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_opengles.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_opengles2.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_opengles2_gl2.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_opengles2_gl2ext.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_opengles2_gl2platform.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_opengles2_khrplatform.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_pixels.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_platform.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_power.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_quit.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_rect.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_render.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_revision.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_rwops.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_scancode.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_shape.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_stdinc.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_surface.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_system.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_syswm.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_test.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_test_assert.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_test_common.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_test_compare.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_test_crc32.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_test_font.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_test_fuzzer.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_test_harness.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_test_images.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_test_log.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_test_md5.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_test_random.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_thread.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_timer.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_touch.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_types.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_version.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_video.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/begin_code.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/close_code.h"
    "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/cmake-build-debug/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/include/SDL_config.h"
    )
endif()


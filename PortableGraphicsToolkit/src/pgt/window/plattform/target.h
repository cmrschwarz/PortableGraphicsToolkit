// no pragma once because of the forwarding macro
#include <pgt/target_settings/target_settings.h>

// clang-format off


#if PGT_WTK_GLFW
	#error the glwf windowing toolkit backend is currently broken
#elif PGT_WTK_SDL
	#ifndef PGT_TEMP_FLAG_FORWARD_DECLARE_ONLY
		#include <pgt/window/plattform/sdl/SdlApp.h>
		#include <pgt/window/plattform/sdl/SdlWindow.h>
		#include <pgt/window/plattform/sdl/SdlGlRenderingContext.h>
	#else
		namespace pgt{
			namespace plattform {
				class SdlWindow;
				class SdlApp;
				class SdlGlRenderingContext;
			} 
		}
	#endif
	namespace pgt {
		typedef plattform::SdlWindow Window;
		typedef plattform::SdlApp App;
		typedef plattform::SdlGlRenderingContext GlRenderingContext;
	}
#else
	#error undefined_wtk
#endif


// clang-format on

// no pragma once because of the forwarding macro
#include <pgt/target_settings/target_settings.h>
// clang-format off
#if PGT_HWA_OPENGL
	#if PGT_RENDERER_2D_HARDWARE
		#ifndef PGT_TEMP_FLAG_FORWARD_DECLARE_ONLY
			#include <pgt/graphics/plattform/opengl/2d/GlRenderer2D.h>
			#include <pgt/graphics/plattform/opengl/GlTexture.h>
			#include <pgt/graphics/plattform/opengl/GlFramebuffer.h>
			#include <pgt/graphics/plattform/opengl/font/GlFont.h>
		#else
			namespace pgt {
				namespace plattform {
					class GlRenderer2D;
					class GlTexture;
					class GlFramebuffer;
					class GlFont;
				}
			}
		#endif
		namespace pgt {
			typedef plattform::GlRenderer2D Renderer2D;
			typedef plattform::GlTexture Texture;
			typedef plattform::GlFramebuffer Framebuffer;
			typedef plattform::GlFont Font;
		}
	#else
		//support for DYNAMIC will  hopefully come soon
		#error unsupported_rendering_standard
	#endif
#else
	#error unsupported_rendering_api
#endif
// clang-format on
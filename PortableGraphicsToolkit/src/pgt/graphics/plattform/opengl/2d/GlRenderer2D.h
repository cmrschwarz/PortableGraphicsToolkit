#pragma once
#include "GlRenderer2D.h"
#include <pgt/graphics/plattform/interface/IRenderer2D.h>
#include <pgt/maths/maths.h>
#include <pgt/utils/primitives.h>
#include <pgt/graphics/Color.h>
#include <pgt/graphics/plattform/opengl/GlIndexBuffer.h>
#include <pgt/graphics/plattform/opengl/GlShader.h>
#include <vector>
#include <pgt/graphics/plattform/opengl/GlTexture.h>
#include <pgt/graphics/plattform/opengl/font/GlFontInternal.h>
#include <pgt/graphics/plattform/opengl/font/GlFontManager.h>
#include <pgt/graphics/plattform/interface/IRenderingCOntext.h>
#include <pgt/window/window_fwd.h>

// TODO: forward declare ftgl stuff

namespace pgt {
    namespace plattform {
        struct VertexData {
            vec3 pos;
            vec2 uv;
            float tid;
            int color;
        };

        class GlRenderer2D final : public IRenderer2D {
        private:
            static const int MAX_SPRITES = 2500;
            static const int VERTEX_SIZE = sizeof(VertexData);
            static const int SPRITE_SIZE = VERTEX_SIZE * 4;
            static const int BUFFER_SIZE = SPRITE_SIZE * MAX_SPRITES;
            static const int INDICES_SIZE = MAX_SPRITES * 6;
            static const int SHADER_VERTEX_ID = 0;
            static const int SHADER_UV_ID = 1;
            static const int SHADER_TID_ID = 2;
            static const int SHADER_COLOR_ID = 3;
            // not static because the standard is retarded and doesnt allow
            // static const float in header 0.0000001f;
            const float DEPTH_BUFFER_PRECISION_STEP = 0.00001f;
            //*3 is a safety requirement so adding a clipping space cant go out
            // of
            // bounds
            const float DEPTH_MIN = -1 + DEPTH_BUFFER_PRECISION_STEP * 3;
            // notice that max depth means at the BACK
            const float DEPTH_MAX = 1 - DEPTH_BUFFER_PRECISION_STEP;

        private:
            Window& _window;
            float _depth;
            int _max_texture_units;
            std::vector<vec4i> _viewport_stack;
            GlIndexBuffer _ibo;
            GLuint _vao;
            GLuint _vbo;
            GLsizei _index_count;
            GlShader* _shader;
            VertexData* _buffer;
            std::vector<GLuint> _texture_slots;
            Color _color;
            GlFont _font;
            IRenderingContext& _context;  // GLRenderingContext Not There yet

        public:
            GlRenderer2D();
            ~GlRenderer2D();

        public:
            void begin() override;
            void end() override;
            void pushViewport(const vec2i& pos, const vec2i& size) override;
            void popViewport() override;

        public:
            void setColor(Color c) override;
            void drawLine(const vec2i& start, const vec2i& end,
                          int thickness) override;
            void drawRectangle(const vec2i& start, const vec2i& size,
                               size_t thickness) override;
            void fillTriangle(const vec2i& pos0, const vec2i& pos1,
                              const vec2i& pos2) override;
            void fillQuad(const vec2i& pos0, const vec2i& pos1,
                          const vec2i& pos2, const vec2i& pos3) override;
            void fillCircle(const vec2i& center, size_t radius,
                            float angle = 2 * M_PI,
                            float start_angle = 0) override;
            void fillRectangle(const vec2i& start, const vec2i& size) override;
            void drawTexture(const ITexture& t, const vec2i& pos,
                             const vec2i& size) override;
            void setFont(const Font& f) override;
            const Font& getFont() const override;
            void drawString(const std::string& text, vec2i position) override;
            vec4i getCurrentViewport() const;
            // TODO: decide on where to interface this
            Window& getWindow() const;

        private:
            void submitColoredVertexGLP(const vec2& pos);
            void submitVertexVP(const vec2i& pos, const vec2& uv,
                                GLint tex_slot,
                                Color col = Color(0, 0, 0, 255));
            void submitColoredVertexVP(const vec2i& pos);
            void submitColordVertexSP(const vec2i& pos);
            void submitRectangleSP(const vec2i& start, const vec2i& size);
            void submitRectangleVP(vec2i start, vec2i size);
            void submitRectangleGLP(const vec2& start, const vec2& end);
            void popClippingRectangle();
            void pushClippingRectangleSP(vec2i rect, vec2i size);

        private:
            vec2 toGlPosition(const vec2i& v);
            vec2i toScreenPosition(const vec2i& v);
            void bumpQuadCount(int inc = 1);
            GLint push_texture(GLuint tid);
            void flush(bool keep_textures = false);
            void next();
            void init();
        };
    }
}
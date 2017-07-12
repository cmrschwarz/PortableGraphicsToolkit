#include "GlRenderer2D.h"
#include <GL/glew.h>
#include <freetype_gl/freetype-gl.h>
#include <pgt/io/logger/logger.h>
#include <pgt/io/vfs/VfsFileStreamReader.h>
#include <pgt/graphics/plattform/opengl/GlTexture.h>
#include <pgt/window/engine.h>
#include <pgt/window/window.h>
#undef min  // sanity
namespace pgt {
    namespace plattform {
        static GLint texIDs[] = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
                                 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
                                 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
        GlRenderer2D::GlRenderer2D()
            : _window(engine::getApp().getRenderingContext().getWindow()),
              _context(_window.getRenderingContext()),
              _font("ArialRoundedMT", 25,
                    VfsFileStreamReader("/res/fonts/arialroundedmt.ttf")),
			  _index_count(0)
        {
            glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
                          &_max_texture_units);
            PGT_LOG_INFO("%i Texture Units found.", _max_texture_units);
            _max_texture_units = 1;
            _shader =
                new GlShader(VfsFileStreamReader("/res/shaders/basic.vert"),
                             VfsFileStreamReader("/res/shaders/basic.frag"));
            _shader->enable();
            _shader->setUniform1iv("textures", texIDs, _max_texture_units);
            _shader->disable();
            _ibo.initForRectangles(INDICES_SIZE);
            init();
        }

        GlRenderer2D::~GlRenderer2D()
        {
            delete _shader;
            glDeleteBuffers(1, &_vbo);
            glDeleteVertexArrays(1, &_vao);
        }

        void GlRenderer2D::init()
        {
            glGenVertexArrays(1, &_vao);
            glGenBuffers(1, &_vbo);
            glBindVertexArray(_vao);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

            // CODE DEPENDING ON VERTEX_DATA
            glEnableVertexAttribArray(SHADER_VERTEX_ID);
            glEnableVertexAttribArray(SHADER_UV_ID);
            glEnableVertexAttribArray(SHADER_TID_ID);
            glEnableVertexAttribArray(SHADER_COLOR_ID);
            glVertexAttribPointer(
                SHADER_VERTEX_ID, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE,
                (const GLvoid*)offsetof(VertexData, VertexData::pos));
            glVertexAttribPointer(
                SHADER_UV_ID, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE,
                (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
            glVertexAttribPointer(
                SHADER_TID_ID, 1, GL_FLOAT, GL_FALSE, VERTEX_SIZE,
                (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
            glVertexAttribPointer(
                SHADER_COLOR_ID, 4, GL_UNSIGNED_BYTE, GL_TRUE, VERTEX_SIZE,
                (const GLvoid*)(offsetof(VertexData, VertexData::color)));
            // END
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo.getID());
            glBindVertexArray(0);

            _viewport_stack.push_back(vec4i(0, 0, INT_MAX, INT_MAX));
            PGT_LOG_DEBUG("Initialized 2D Renderer for Window:\"%s\"",
                         _window.getTitle().c_str());
        }

        void GlRenderer2D::bumpQuadCount(int inc)
        {
            inc *= 6;
            _index_count += inc;
            if (_index_count > INDICES_SIZE) {
                _index_count -= inc;
                flush(true);
                next();
                _index_count += inc;
            }
        }
        void GlRenderer2D::submitColoredVertexGLP(const vec2& pos)
        {
            // uv won't get used--> don't set it
            _buffer->pos = vec3(pos.x, pos.y, _depth);
            _buffer->tid = -1;
            _buffer->color = _color.toNetworkOrder();
            _buffer++;
        }

        void GlRenderer2D::submitColoredVertexVP(const vec2i& pos)
        {
            submitColordVertexSP(toScreenPosition(pos));
        }
        void GlRenderer2D::submitColordVertexSP(const vec2i& pos)
        {
            submitColoredVertexGLP(toGlPosition(pos));
        }
        void GlRenderer2D::submitVertexVP(const vec2i& pos, const vec2& uv,
                                          GLint tex_slot, Color col)
        {
            vec2 pos_gl = toGlPosition(toScreenPosition(pos));
            _buffer->pos = vec3(pos_gl.x, pos_gl.y, _depth);
            _buffer->uv = uv;
            _buffer->tid = (float)tex_slot;
            _buffer->color = col.toNetworkOrder();  // will be used by text
            _buffer++;
        }

        GLint GlRenderer2D::push_texture(GLuint tid)
        {
            for (int i = 0; i < _texture_slots.size(); i++) {
                if (_texture_slots[i] == tid) {
                    return i;
                }
            }
            if (_texture_slots.size() == _max_texture_units) {
                flush();
                next();
            }
            _texture_slots.push_back(tid);
            return _texture_slots.size() - 1;
        }

        void GlRenderer2D::submitRectangleGLP(const vec2& start,
                                              const vec2& end)
        {
            submitColoredVertexGLP(start);
            submitColoredVertexGLP(vec2(start.x, end.y));
            submitColoredVertexGLP(vec2(end.x, end.y));
            submitColoredVertexGLP(vec2(end.x, start.y));
        }
        void GlRenderer2D::submitRectangleSP(const vec2i& start,
                                             const vec2i& size)
        {
            vec2 start_gl = toGlPosition(start);
            vec2 end_gl = toGlPosition(start + size);
            submitRectangleGLP(start_gl, end_gl);
        }

        void GlRenderer2D::submitRectangleVP(vec2i start, vec2i size)
        {
            submitRectangleSP(toScreenPosition(start), size);
        }


        // dont use any gl binds between begin and flush!
        void GlRenderer2D::begin()
        {
            // this is the very back in open gl coordinate system. the clipping
            // occurs at -1 [inclusive]
            _depth = DEPTH_MAX;
            glClear(GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glDisable(GL_CULL_FACE);
            // TODO: examine how this works and reset if in ::end
            glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE,
                                GL_ONE);
            glDepthFunc(GL_LEQUAL);
            _shader->enable();

            glBindVertexArray(_vao);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            _buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
            engine::internal::checkGLErrors();
        }
        void GlRenderer2D::flush(bool keep_textures)
        {
            glUnmapBuffer(GL_ARRAY_BUFFER);
            for (int i = 0; i < _texture_slots.size(); i++) {
                glActiveTexture(GL_TEXTURE0 + i);
                int r = _texture_slots[i];
                glBindTexture(GL_TEXTURE_2D, r);
            }
            glActiveTexture(GL_TEXTURE0);
            if (!keep_textures) _texture_slots.clear();
            glDrawElements(GL_TRIANGLES, _index_count, GL_UNSIGNED_INT, NULL);
            _index_count = 0;
        }

        void GlRenderer2D::next()
        {
            _buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
        }

        void GlRenderer2D::popClippingRectangle()
        {
            // go to next depth layer. (genius, ikr ;))
            _depth -= DEPTH_BUFFER_PRECISION_STEP;
            if (_depth < DEPTH_MIN) {
                PGT_ASSERT(false, "SUrpassed Maximum Clipping Layer Count");
            }
        }

        void GlRenderer2D::pushClippingRectangleSP(vec2i r_start, vec2i r_size)
        {
            // renamed inputs because they are be converted


            _depth -= DEPTH_BUFFER_PRECISION_STEP;
            bumpQuadCount(4);
            // w for window
            vec2i w_start = vec2i(0, 0);
            vec2i w_size = vec2i(_window.getWidth(), _window.getHeight());
            Color backup_user_color = _color;
            _color = 0;  // transparent, but changes depth buffer
            submitRectangleSP(w_start, vec2i(w_size.x, r_start.y));
            submitRectangleSP(vec2i(w_start.x, r_start.y + r_size.y),
                              vec2i(w_size.x, w_size.y - r_start.y - r_size.y));

            submitRectangleSP(vec2i(w_start.x, r_start.y),
                              vec2i(r_start.x, r_size.y));
            submitRectangleSP(vec2i(r_start.x + r_size.x, r_start.y),
                              vec2i(w_size.x - r_start.x - r_size.x, r_size.y));
            _depth += DEPTH_BUFFER_PRECISION_STEP;
            _color = backup_user_color;
        }
        void GlRenderer2D::pushViewport(const vec2i& pos, const vec2i& size)
        {
            const vec4i& vp_curr = _viewport_stack.back();
            vec2i pos_abs = toScreenPosition(pos);
            vec2i size_clamped;
            size_clamped.x = std::min(size.x, vp_curr.z);
            size_clamped.y = std::min(size.y, vp_curr.w);
            vec4i vp =
                vec4i(pos_abs.x, pos_abs.y, size_clamped.x, size_clamped.y);
            _viewport_stack.push_back(vp);
            pushClippingRectangleSP(pos_abs, size_clamped);
        }

        void GlRenderer2D::popViewport()
        {
            PGT_DEBUG_ASSERT(_viewport_stack.size() > 1, "No Viewport to pop");
            _viewport_stack.pop_back();
            popClippingRectangle();
        }

        void GlRenderer2D::end()
        {
            flush();
            _shader->disable();
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            glDisable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            glDisable(GL_BLEND);
        }

        void GlRenderer2D::setColor(Color c)
        {
            _color = c;
        }

        void GlRenderer2D::drawLine(const vec2i& start, const vec2i& end,
                                    int thickness)
        {
            bumpQuadCount();
            vec2 vect_up = vec2(end.x - start.x, end.y - start.y);
            vect_up = vec2(-vect_up.y, vect_up.x);
            vect_up.normalize();
            vect_up *= (((float)thickness) / 2.0);
            // TODO: maybe round
            vec2i vect_up_i =
                vec2i(std::round(vect_up.x), std::round(vect_up.y));
            submitColoredVertexVP(start - vect_up_i);
            submitColoredVertexVP(start + vect_up_i);
            submitColoredVertexVP(end + vect_up_i);
            submitColoredVertexVP(end - vect_up_i);
        }

        void GlRenderer2D::drawRectangle(const vec2i& start, const vec2i& size,
                                         size_t thickness)
        {
            bumpQuadCount(4);

            submitRectangleVP(start, vec2i(size.x, thickness));
            submitRectangleVP(vec2i(start.x, start.y + size.y - thickness),
                              vec2i(size.x, thickness));
            submitRectangleVP(vec2i(start.x, start.y + thickness),
                              vec2i(thickness, size.y - thickness * 2));
            submitRectangleVP(
                vec2i(start.x + size.x - thickness, start.y + thickness),
                vec2i(thickness, size.y - thickness * 2));
        }

        void GlRenderer2D::fillRectangle(const vec2i& start, const vec2i& size)
        {
            bumpQuadCount();
            submitRectangleVP(start, size);
        }

        void GlRenderer2D::drawString(const std::string& text, vec2i position)
        {
            const float scale = 1.0f;
            float pos_x = (float)position.x;
            float pos_y = (float)position.y;
            int baseline_y = _font.getAscender() * scale;
            pos_y += baseline_y;
            GLint tex_slot = push_texture(_font.getInternalFont().getTid());
            bumpQuadCount(text.size());
            char prev;
            ftgl::texture_glyph_t* glyph;
            for (int i = 0; i < text.size(); i++) {
                char curr = text.c_str()[i];
                ftgl::texture_glyph_t* glyph =
                    _font.getInternalFont().getGlyph(curr);
                if (i > 0) {
                    pos_x +=
                        ftgl::texture_glyph_get_kerning(glyph, &prev) * scale;
                }
                float x0 = pos_x + glyph->offset_x * scale;
                float y0 = pos_y - glyph->offset_y * scale;
                float x1 = x0 + glyph->width * scale;
                float y1 = y0 + glyph->height * scale;
                float uv_x_0 = glyph->s0;
                float uv_x_1 = glyph->s1;
                float uv_y_0 = glyph->t0;
                float uv_y_1 = glyph->t1;
                submitVertexVP(vec2i(x0, y0), vec2(uv_x_0, uv_y_0), tex_slot,
                               _color);
                submitVertexVP(vec2i(x0, y1), vec2(uv_x_0, uv_y_1), tex_slot,
                               _color);
                submitVertexVP(vec2i(x1, y1), vec2(uv_x_1, uv_y_1), tex_slot,
                               _color);
                submitVertexVP(vec2i(x1, y0), vec2(uv_x_1, uv_y_0), tex_slot,
                               _color);
                pos_x += glyph->advance_x;
                pos_y += glyph->advance_y;
                prev = curr;
            }
        }


        void GlRenderer2D::setFont(const Font& rf)
        {
            _font = rf;
        }
        void GlRenderer2D::drawTexture(const ITexture& t, const vec2i& pos,
                                       const vec2i& size)
        {
            const auto& tc = static_cast<const GlTexture&>(t);
            GLint tex_slot = push_texture(tc.getTID());
            bumpQuadCount();
            submitVertexVP(pos, vec2(0, 1), tex_slot);
            submitVertexVP(vec2i(pos.x, pos.y + size.y), vec2(0, 0), tex_slot);
            submitVertexVP(vec2i(pos.x + size.x, pos.y + size.y), vec2(1, 0),
                           tex_slot);
            submitVertexVP(vec2i(pos.x + size.x, pos.y), vec2(1, 1), tex_slot);
        }

        void GlRenderer2D::fillTriangle(const vec2i& pos0, const vec2i& pos1,
                                        const vec2i& pos2)
        {
            bumpQuadCount();
            submitColoredVertexVP(pos0);
            submitColoredVertexVP(pos1);
            submitColoredVertexVP(pos2);
            submitColoredVertexVP(
                pos1);  // 012210. work around for renderer only
                        // supporting rectangles
        }

        void GlRenderer2D::fillCircle(const vec2i& center, size_t radius,
                                      float angle, float start_angle)
        {
            const float percentage_of_full_circle = ((2 * M_PI) / angle);
            // For hexagon: set tri count to 
            const int hcount = radius / percentage_of_full_circle;
            bumpQuadCount(hcount);
            float phi = (angle) / (hcount * 2);
            float iphi = start_angle;

            for (int i = 0; i < hcount; i++) {
                submitColoredVertexVP(center);
                submitColoredVertexVP(
                    center + vec2i(cos(iphi) * radius, -sin(iphi) * radius));
                iphi += phi;
                submitColoredVertexVP(
                    center + vec2i(cos(iphi) * radius, -sin(iphi) * radius));
                iphi += phi;
                submitColoredVertexVP(
                    center + vec2i(cos(iphi) * radius, -sin(iphi) * radius));
            }
        }

        void GlRenderer2D::fillQuad(const vec2i& pos0, const vec2i& pos1,
                                    const vec2i& pos2, const vec2i& pos3)
        {
            bumpQuadCount();
            submitColoredVertexVP(pos0);
            submitColoredVertexVP(pos1);
            submitColoredVertexVP(pos2);
            submitColoredVertexVP(pos3);
        }

        vec2i GlRenderer2D::toScreenPosition(const vec2i& v)
        {
            auto& vp = _viewport_stack.back();
            return vec2i(v.x + vp.x, v.y + vp.y);
        }

        vec2 GlRenderer2D::toGlPosition(const vec2i& v)
        {
            // TODO: mabe cache window pos
            vec2 ret;
            ret.x = ((float)v.x) / _window.getWidth();
            ret.x = ret.x * 2.0f - 1.0f;
            ret.y = ((float)v.y) / _window.getHeight();
            ret.y = (ret.y - 0.5f) * (-2.0f);
            return ret;
        }

        vec4i GlRenderer2D::getCurrentViewport() const
        {
            if (_viewport_stack.size() == 1) {
                return vec4i(0, 0, _window.getWidth(), _window.getHeight());
            }
            else {
                return _viewport_stack.back();
            }
        }

        Window& GlRenderer2D::getWindow() const
        {
            return _window;
        }

        const pgt::Font& GlRenderer2D::getFont() const
        {
            return _font;
        }
    }
}
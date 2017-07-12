#pragma once
#include <pgt/graphics/plattform/interface/IRenderer2D.h>
#include <pgt/io/logger/logger.h>

namespace pgt {
    template <class IMAGE_TYPE = IImage>
    class SwRenderer : public IRenderer2D {
    private:
        IMAGE_TYPE& _image;
        std::vector<vec4i> _viewport_stack;
        Color _color = Color::BLACK;

    public:
        SwRenderer(IMAGE_TYPE& img) : _image(img)
        {
            _viewport_stack.push_back(vec4i(0, 0, INT_MAX, INT_MAX));
        }


        void setFont(const Font& f) override
        {
        }

    public:
        void begin() override{};
        void end() override{};
        void pushViewport(const vec2i& pos, const vec2i& size) override
        {
            _viewport_stack.push_back(vec4i(pos.x, pos.y, size.x, size.y));
        }
        void popViewport() override
        {
            PGT_DEBUG_ASSERT(_viewport_stack.size() > 1, "No Viewport to pop");
            _viewport_stack.pop_back();
        }
        void setColor(Color c) override
        {
            _color = c;
        }
        void drawLine(const vec2i& start, const vec2i& end,
                      int thickness) override
        {
        }
        void drawRectangle(const vec2i& start, const vec2i& size,
                           size_t thickness) override
        {
        }

    private:
        // puts the lefter point in the lefter point pointer. if both points
        // have the same x value, the point wich is higher becomes lefter
        // point
        void setLefterPoint(const vec2i& top, const vec2i& p1, const vec2i& p2,
                            vec2i& lefter, vec2i& other) const
        {
            if (p1.x < p2.x) {
                if (p1.x < top.x || p1.y > getYiFromX(p2, top, p1.x)) {
                    lefter = toImagePoint(p1);
                    other = toImagePoint(p2);
                }
                else {
                    lefter = toImagePoint(p2);
                    other = toImagePoint(p1);
                }
            }
            else if (p2.x < p1.x) {
                if (p2.x < top.x || p2.y > getYiFromX(p1, top, p2.x)) {
                    lefter = toImagePoint(p2);
                    other = toImagePoint(p1);
                }
                else {
                    lefter = toImagePoint(p1);
                    other = toImagePoint(p2);
                }
            }
            else {
                if (p1.y < p2.y) {
                    if (p1.x < top.x) {
                        lefter = toImagePoint(p1);
                        other = toImagePoint(p2);
                    }
                    else {
                        lefter = toImagePoint(p2);
                        other = toImagePoint(p1);
                    }
                }
                else {
                    if (p2.x < top.x) {
                        lefter = toImagePoint(p2);
                        other = toImagePoint(p1);
                    }
                    else {
                        lefter = toImagePoint(p1);
                        other = toImagePoint(p2);
                    }
                }
            }
        }
        void arrangePoints(const vec2i& p0, const vec2i& p1, const vec2i& p2,
                           vec2i& p_top_left, vec2i& p_lefter,
                           vec2i& p_other) const
        {
            if (p0.y < p1.y) {
                if (p0.y < p2.y) {
                    p_top_left = toImagePoint(p0);
                    setLefterPoint(p_top_left, p1, p2, p_lefter, p_other);
                }
                else if (p2.y < p0.y) {
                    p_top_left = toImagePoint(p2);
                    setLefterPoint(p_top_left, p0, p1, p_lefter, p_other);
                }
                else {
                    if (p0.x < p2.x) {
                        p_top_left = toImagePoint(p0);
                        setLefterPoint(p_top_left, p1, p2, p_lefter, p_other);
                    }
                    else {
                        p_top_left = toImagePoint(p2);
                        setLefterPoint(p_top_left, p0, p1, p_lefter, p_other);
                    }
                }
            }
            else if (p1.y < p0.y) {
                if (p1.y < p2.y) {
                    p_top_left = toImagePoint(p1);
                    setLefterPoint(p_top_left, p0, p2, p_lefter, p_other);
                }
                else if (p2.y < p1.y) {
                    p_top_left = toImagePoint(p2);
                    setLefterPoint(p_top_left, p0, p1, p_lefter, p_other);
                }
                else {
                    if (p1.x < p2.x) {
                        p_top_left = toImagePoint(p1);
                        setLefterPoint(p_top_left, p0, p2, p_lefter, p_other);
                    }
                    else {
                        p_top_left = toImagePoint(p2);
                        setLefterPoint(p_top_left, p0, p1, p_lefter, p_other);
                    }
                }
            }
            else {
                if (p2.y < p0.y) {
                    p_top_left = toImagePoint(p2);
                    setLefterPoint(p_top_left, p0, p1, p_lefter, p_other);
                }
                else {
                    if (p0.x < p1.x) {
                        p_top_left = toImagePoint(p0);
                        setLefterPoint(p_top_left, p1, p2, p_lefter, p_other);
                    }
                    else {
                        p_top_left = toImagePoint(p1);
                        setLefterPoint(p_top_left, p0, p2, p_lefter, p_other);
                    }
                }
            }
        }
        int getXiFromY(const vec2i& ps, const vec2i& pt, int yi) const
        {
            float lamda = ((float)yi - ps.y) / ((float)pt.y - ps.y);
            int xi = ps.x + (int)std::round(lamda * (pt.x - ps.x));
            return xi;
        }
        int getYiFromX(const vec2i& ps, const vec2i& pt, int xi) const
        {
            float lamda = ((float)xi - ps.x) / ((float)pt.x - ps.x);
            int yi = ps.y + (int)(lamda * (pt.y - ps.y));
            return xi;
        }
        void drawScanline(int xl, int xr, int y)
        {
            uint8_t* row = _image.getData() + y * _image.getYStride();
            uint8_t* pos = row + xl * _image.getXStride();
            uint8_t* end = row + (xr + 1) * _image.getXStride();
            auto color = _image.turnColorToImagePixel(_color);
            while (pos != end) {
                _image.setPixelAt(pos, color);
                pos += _image.getXStride();
            }
        }

    public:
        void fillTriangle(const vec2i& p0, const vec2i& p1,
                          const vec2i& p2) override
        {
            vec2i p_top, p_lefter, p_other;
            arrangePoints(p0, p1, p2, p_top, p_lefter, p_other);
            // from here on, we're in image coordinates, meaning bottom left
            // is (0|0)
            if (p_lefter.y <= p_other.y) {
                int y_curr = p_lefter.y;
                while (y_curr < p_other.y) {
                    int xl = getXiFromY(p_lefter, p_top, y_curr);
                    int xr = getXiFromY(p_lefter, p_other, y_curr);
                    drawScanline(xl, xr, y_curr);
                    y_curr++;
                }
                int xl = getXiFromY(p_lefter, p_top, y_curr);
                drawScanline(xl, p_other.x, y_curr);
                y_curr++;
                while (y_curr <= p_top.y) {
                    int xl = getXiFromY(p_lefter, p_top, y_curr);
                    int xr = getXiFromY(p_other, p_top, y_curr);
                    drawScanline(xl, xr, y_curr);
                    y_curr++;
                }
            }
            else {
                int y_curr = p_other.y;
                while (y_curr <= p_lefter.y) {
                    int xl = getXiFromY(p_other, p_lefter, y_curr);
                    int xr = getXiFromY(p_other, p_top, y_curr);
                    drawScanline(xl, xr, y_curr);
                    y_curr++;
                }
                while (y_curr <= p_top.y) {
                    int xl = getXiFromY(p_lefter, p_top, y_curr);
                    int xr = getXiFromY(p_other, p_top, y_curr);
                    drawScanline(xl, xr, y_curr);
                    y_curr++;
                }
            }
        }
        void fillQuad(const vec2i& pos0, const vec2i& pos1, const vec2i& pos2,
                      const vec2i& pos3) override{};
        void fillCircle(const vec2i& center, size_t radius,
                        float angle = 2 * M_PI,
                        float start_angle = 0) override{};
        void drawTexture(const ITexture& t, const vec2i& pos,
                         const vec2i& size) override{};
        void fillRectangle(const vec2i& start, const vec2i& size) override
        {
            vec4i vp = getCurrentViewport();
            vp.z += vp.x;
            vp.w += vp.y;
            // zw are the ends (exclusive)
            vec4i rct =
                vec4i(start.x, start.y, start.x + size.x, start.y + size.x);
            if (rct.x > vp.z || rct.y > vp.w) return;
            if (rct.z < vp.x || rct.w < vp.y) return;
            if (rct.x < vp.x) rct.x = vp.x;
            if (rct.y < vp.y) rct.y = vp.y;
            if (rct.z > vp.z) rct.z = vp.z;
            if (rct.w > vp.w) rct.w = vp.w;
            rct = toImageRct(rct);
            size_t stride_x = _image.getXStride();
            size_t stride_y = _image.getYStride();
            uint8_t* img_start = _image.getData();

            uint8_t* row_ptr = img_start + rct.y * stride_y + rct.x * stride_x;
            uint8_t* row_end = img_start + rct.y * stride_y + rct.z * stride_x;
            uint8_t* pix_ptr = row_ptr;
            uint8_t* rct_end = img_start + rct.w * stride_y + rct.x * stride_x;
            uint32_t img_color = _image.turnColorToImagePixel(_color);
            // compiler does a terrible job here. But duffs device is ugly
            // as shit so im not gonna do it
            while (row_ptr != rct_end) {
                while (pix_ptr != row_end) {
                    _image.setPixelAt(pix_ptr, img_color);
                    pix_ptr += stride_x;
                }
                row_ptr += stride_y;
                row_end += stride_y;
                pix_ptr = row_ptr;
            }
        }
        void drawString(const std::string& text, vec2i position) override{};
        const Font& getFont() const override
        {
           PGT_ASSERT(false,"Not Implemented");
        };
        vec4i getCurrentViewport() const override
        {
            if (_viewport_stack.size() == 1) {
                return vec4i(0, 0, _image.getWidth(), _image.getHeight());
            }
            else {
                return _viewport_stack.back();
            }
        }
        vec4i toImageRct(const vec4i& rct) const
        {
            vec4i res;
            res.x = rct.x;
            res.z = rct.z;
            res.y = _image.getHeight() - rct.w;
            res.w = _image.getHeight() - rct.y;
            return res;
        }
        vec2i toImagePoint(const vec2i& p) const
        {
            return vec2i(p.x, _image.getHeight() - p.y - 1);
        }
    };
}
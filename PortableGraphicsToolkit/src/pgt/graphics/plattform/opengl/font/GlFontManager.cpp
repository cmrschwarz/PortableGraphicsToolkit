#include "GlFontManager.h"
#include "GlFontInternal.h"
#include <pgt/utils/string/string_utils.h>
#include <pgt/io/vfs/VirtualFileSystem.h>
#include "GlFont.h"

namespace pgt {
    namespace plattform {
        GlFontManager::GlFontManager()
            : _default_font_internal(
                  "ArialRoundedMT", 16,
                  pgt::VfsFileStreamReader("/res/fonts/arialroundedmt.ttf")),
              _default_font(_default_font_internal)
        {
            _default_font_internal.setManaged(true);
        }
        GlFontInternal* GlFontManager::getFont(const std::string& name,
                                               size_t size)
        {
            GlFontInternal* match = nullptr;
            for (auto it = _fonts.begin(); it != _fonts.end(); ++it) {
                if ((*it)->getSize() == size &&
                    pgt::compare_string_case_insensitive((*it)->getName(),
                                                        name)) {
                    match = (*it);
                    break;
                }
            }
            return match;  // may return nullptr if font doesn't exist yet
        }

        void GlFontManager::submitFont(const IFont& font)
        {
            auto* fnt = ((GlFont&)font)._font_internal;
            _fonts.push_back(fnt);
            fnt->setManaged(true);
        }



        GlFontManager::~GlFontManager()
        {
            for (auto it = _fonts.begin(); it != _fonts.end(); ++it) {
                delete (*it);
            }
        }


        pgt::Font& GlFontManager::getDefaultFont()
        {
            return _default_font;
        }
    }
}
#include "MessageBoxes.h"
#include <windows.h>
#include <pgt/io/logger/logger.h>
namespace pgt {
    size_t getButtonlayout(size_t buttonlayout)
    {
        switch (buttonlayout) {
        case BUTTONLAYOUT_OK:
            return MB_OK;
        case BUTTONLAYOUT_OK_CANCEL:
            return MB_OKCANCEL;
        case BUTTONLAYOUT_YES_NO:
            return MB_YESNO;
        case BUTTONLAYOUT_YES_NO_CANCEL:
            return MB_YESNOCANCEL;
        default:
            PGT_ASSERT(false, "Invcalid buttons type");
        }
    }
    size_t getClickedButton(size_t res)
    {
        switch (res) {
        case IDOK:
            return BUTTON_OK;
        case IDCANCEL:
            return BUTTON_CANCEL;
        case IDABORT:
            return BUTTON_ABORT;
        case IDRETRY:
            return BUTTON_RETRY;
        case IDIGNORE:
            return BUTTON_IGNORE;
        case IDYES:
            return BUTTON_YES;
        case IDNO:
            return BUTTON_NO;
        default:
            PGT_ASSERT(false, "Invalid button result");
            return 0;
        }
    }
    size_t messageBox(const std::string& text, const std::string& title,
                      int buttonlayout)
    {
        int ret = MessageBox(NULL, text.c_str(), title.c_str(),
                             getButtonlayout(buttonlayout));
        return getClickedButton(ret);
    }

    std::string inputBox(const std::string& text, const std::string& title)
    {
        return "";
    }
}

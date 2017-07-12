#pragma once
#include <string>
namespace pgt {
    enum MsgBoxButtonLayouts : size_t {
        BUTTONLAYOUT_OK_CANCEL,
        BUTTONLAYOUT_YES_NO,
        BUTTONLAYOUT_OK,
        BUTTONLAYOUT_YES_NO_CANCEL,
        BUTTONLAYOUT_ABORT_RETRY_IGNORE
    };
    enum MsgBoxButtons : size_t {
        BUTTON_OK,
        BUTTON_CANCEL,
        BUTTON_YES,
        BUTTON_NO,
        BUTTON_ABORT,
        BUTTON_RETRY,
        BUTTON_IGNORE,
    };
    size_t messageBox(const std::string& text = "MsgBox",
                      const std::string& title = "",
                      int buttonlayout = BUTTONLAYOUT_OK);
    std::string inputBox(const std::string& text, const std::string& title);
}
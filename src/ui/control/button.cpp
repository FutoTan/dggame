#include "button.h"

Button::Button(SkRect rect, CallbackFun callbackFun, DrawFun drawFun) {
    Rect = rect;
    CallbackFunc = callbackFun;
    DrawFunc = drawFun;
}
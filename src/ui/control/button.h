#include <skia/core/SkRect.h>
#include <skia/core/SkCanvas.h>
#include "control.h"

#ifndef DGGAME_BUTTON_H
#define DGGAME_BUTTON_H

class Button{
public:
    typedef void (* DrawFun)(SkCanvas* canvas, Button* button);
    typedef void (* CallbackFun)();

public:
    DrawFun DrawFunc;
    SkRect Rect{};
    CallbackFun CallbackFunc;

public:
    Button(SkRect rect, CallbackFun callbackFun, DrawFun drawFun);

};


#endif //DGGAME_BUTTON_H

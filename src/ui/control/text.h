#include <string>
#include <utility>
#include <skia/core/SkColor.h>
#include <skia/core/SkTypeface.h>
#include <skia/core/SkCanvas.h>
#include <skia/core/SkFont.h>
#include "../../game/assets.h"
#include "control.h"

using namespace std;

#ifndef DGGAME_TEXT_H
#define DGGAME_TEXT_H

class Text{
private:
    static Text Instance;

public:
    typedef struct {
        int fontSize;
        string fontName;
        SkColor color;
    } TextStyle;

    typedef void (* DrawFun)(SkCanvas* canvas, Text* text);

public:
    DrawFun DrawFunc;

    string TextToDraw;
    Vec2D Pos{};
    TextStyle Style;
    sk_sp<SkTypeface> TypefacePointer;

public:
    Text(string text, TextStyle style, Vec2D pos, DrawFun drawFunc);

    Text(string text, TextStyle style, Vec2D pos) : Text(
            std::move(text),std::move(style),pos,DefaultDraw){}

    static void DefaultDraw(SkCanvas* canvas, Text* text);
};


#endif //DGGAME_TEXT_H

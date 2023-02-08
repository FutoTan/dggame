#include "text.h"

Text::Text(string text, TextStyle style, Vec2D pos, DrawFun drawFun) {
    TextToDraw = std::move(text);
    Style = std::move(style);
    Pos = pos;

    TypefacePointer = SkTypeface::MakeFromData(Assets::GetInstance()->GetAsset("/font/" + Style.fontName + ".ttf"));
    DrawFunc = drawFun;
}

void Text::DefaultDraw(SkCanvas* canvas,Text* text) {
    SkString textToDraw(text->TextToDraw);
    SkFont font;
    SkPaint paint;

    font.setSize(text->Style.fontSize);
    font.setTypeface(text->TypefacePointer);
    paint.setColor(text->Style.color);

    canvas->drawSimpleText(textToDraw.c_str(), textToDraw.size(), SkTextEncoding::kUTF8, text->Pos.x, text->Pos.y, font, paint);
}
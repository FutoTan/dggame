#include "ui_manager.h"

void UIManager::Init(SkCanvas* canvas) {
	Canvas = canvas;
    Button button({100,100,200,150},[](){},[](SkCanvas* canvas, Button* button){
        SkPaint paint;
        paint.setAntiAlias(true);

        paint.setColor(SK_ColorYELLOW);

        canvas->drawRoundRect(button->Rect,10,10,paint);

        Text _text("你好", Text::TextStyle{24,"unifont",SK_ColorBLACK}, Vec2D{125, 135});
        (*_text.DrawFunc)(canvas,&_text);

        paint.setColor(SK_ColorBLACK);
        paint.setStyle(SkPaint::kStroke_Style);
        paint.setStrokeWidth(5.0f);

        canvas->drawRoundRect(button->Rect,10,10,paint);
    });
    ButtonList.push_back(button);
}

void UIManager::AddTextControl(string text, Text::TextStyle style, Vec2D pos) {
	Text _text(std::move(text), std::move(style), pos);
	TextList.push_back(_text);
}

void UIManager::Render() {
    for (auto text: TextList) {
        (*text.DrawFunc)(Canvas, &text);
    }
    for (auto button: ButtonList) {
        (*button.DrawFunc)(Canvas, &button);
    }
}
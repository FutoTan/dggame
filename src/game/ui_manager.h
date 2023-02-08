#include <skia/core/SkCanvas.h>
#include <skia/core/SkColorSpace.h>
#include <skia/core/SkSurface.h>
#include <skia/core/SkFont.h>
#include <skia/core/SkStream.h>
#include <skia/core/SkTypeface.h>
#include <vector>
#include <utility>
#include "assets.h"
#include "../ui/control/text.h"
#include "../ui/control/button.h"

#ifndef DGGAME_UI_MANAGER_H
#define DGGAME_UI_MANAGER_H


class UIManager {

private:
	vector<Text> TextList;
    vector<Button> ButtonList;
	SkCanvas* Canvas;
	SkPaint Paint;

public:
	void Init(SkCanvas* canvas);

	void AddTextControl(string text, Text::TextStyle style, Vec2D pos);

	void Render();
};


#endif //DGGAME_UI_MANAGER_H

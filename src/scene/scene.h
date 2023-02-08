#include <skia/core/SkCanvas.h>

#ifndef DGGAME_SCENE_H
#define DGGAME_SCENE_H


class Scene {
public:
    SkCanvas* Canvas;

public:
    Scene();

    virtual void Init(SkCanvas* canvas);
};


#endif //DGGAME_SCENE_H

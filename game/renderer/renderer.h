#ifndef RENDERER_H
#define RENDERER_H

#include "player/player.h"

class Renderer
{
public:
    int width, height;
    char playerChar, emptyChar, borderChar;
    Renderer(int w, int h, char p, char e, char b);

    void render(const Player &player);
};

#endif // RENDERER_H

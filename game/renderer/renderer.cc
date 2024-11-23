#include "renderer/renderer.h"
#include <ncurses.h>

Renderer::Renderer(int w, int h, char p, char e, char b)
    : width(w), height(h), playerChar(p), emptyChar(e), borderChar(b) {}

void Renderer::render(const Player &player)
{
    clear();
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                mvaddch(i, j, borderChar);
            }
            else if (i == player.y && j == player.x)
            {
                mvaddch(i, j, playerChar);
            }
            else
            {
                mvaddch(i, j, emptyChar);
            }
        }
    }
    refresh();
}

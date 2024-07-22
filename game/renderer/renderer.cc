#include "renderer/renderer.h"
#include <iostream>

Renderer::Renderer(int w, int h, char p, char e, char b)
    : width(w), height(h), playerChar(p), emptyChar(e), borderChar(b) {}

void Renderer::render(const Player &player)
{
    clearScreen();
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                std::cout << borderChar;
            }
            else if (i == player.y && j == player.x)
            {
                std::cout << playerChar;
            }
            else
            {
                std::cout << emptyChar;
            }
        }
        std::cout << std::endl;
    }
}

void Renderer::clearScreen()
{
    std::cout << "\x1B[2J\x1B[H";
}

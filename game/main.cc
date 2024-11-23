#include "player/player.h"
#include "renderer/renderer.h"
#include "utils/utils.h"
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <algorithm>

int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(100);

    const int width = 20;
    const int height = 10;
    Renderer renderer(width, height, '@', ' ', '#');
    Player player(width / 2, height / 2);

    renderer.render(player);

    while (true)
    {
        int ch = getKey();
        if (ch != ERR)
        {
            int newX = player.x;
            int newY = player.y;

            switch (ch)
            {
            case 'w':
                newY = std::max(1, player.y - 1);
                break;
            case 's':
                newY = std::min(height - 2, player.y + 1);
                break;
            case 'a':
                newX = std::max(1, player.x - 1);
                break;
            case 'd':
                newX = std::min(width - 2, player.x + 1);
                break;
            default:
                break;
            }

            player.x = newX;
            player.y = newY;

            renderer.render(player);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    endwin();
    return 0;
}

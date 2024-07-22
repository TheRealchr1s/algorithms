#include "player/player.h"
#include "renderer/renderer.h"
#include "utils/utils.h"
#include <thread>
#include <chrono>
#include <algorithm>

int main()
{
    const int width = 20;
    const int height = 10;
    Renderer renderer(width, height, '@', ' ', '#');
    Player player(width / 2, height / 2);

    renderer.render(player);

    while (true)
    {
        if (isKeyPressed())
        {
            char key = getKey();
            int newX = player.x;
            int newY = player.y;

            switch (key)
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

    return 0;
}

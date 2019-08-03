#include "Utils/ConfigStore.h"
#include "Game/Game.h"


int main() {
    // todo read from file
    ConfigStore config = ConfigStore();
    config.setScreenWidth(800);
    config.setScreenHeight(600);

    Game game(config);
    game.run();

    return 0;
}
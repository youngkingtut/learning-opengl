
#include "ConfigStore.h"
#include "Game.h"


int main() {
    // todo read from file
    ConfigStore config = ConfigStore();
    config.setScreenWidth(800);
    config.setScreenHeight(600);

    Game game{};

    game.initialize(config);
    game.run();

    return 0;
}
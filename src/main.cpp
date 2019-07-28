
#include "ConfigStore.h"
#include "Game.h"


int main() {
    // todo read from file
    ConfigStore config = ConfigStore();
    config.setScreenWidth(800);
    config.setScreenHeight(600);
    config.setWorldWidth(1.5f);
    config.setWorldHeight(1.5f);

    Game game;

    game.initialize(config);
    game.run();

    return 0;
}
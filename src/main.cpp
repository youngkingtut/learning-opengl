
#include "ConfigStore.h"
#include "Game.h"


int main() {
    // todo read from file
    ConfigStore config = ConfigStore();
    config.setScreenWidth(800);
    config.setScreenHeight(600);
    config.setWorldWidth(10.0f);
    config.setWorldHeight(10.0f);

    Game game(config);
    game.run();

    return 0;
}
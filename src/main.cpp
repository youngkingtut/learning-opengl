#include "Utils/ConfigStore.h"
#include "Game/Game.h"


int main() {
    // todo read from file
    ConfigStore config = ConfigStore();
    config.setScreenSize(800.0f, 600.0f);
    config.setWorldSize(400.0f, 300.0f);
    config.setPlayerSize(15.0f, 15.0f);

    Game game(config);
    game.run();

    return 0;
}
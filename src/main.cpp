#include "ConfigStore.h"
#include "Game.h"

int main() {
    // todo read from file
    ConfigStore configStore = ConfigStore();
    configStore.setScreenWidth(800);
    configStore.setScreenHeight(600);

    Game game = Game(configStore);

    game.initialize();
    game.run();

    return 0;
}
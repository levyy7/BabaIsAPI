//
// Created by Eneko on 21/03/2025.
//
#ifndef GAME_HPP
#define GAME_HPP

import GameManager;
import LevelLoader;
#include "GameLogic.h"
#include "../../../api/command/CommandQueue.h"

class Game {
public:
    Game(EventManager *eventManager);

    Game(std::vector<EventManager *> eventManagers);

    ~Game();

    // Starts the game loop.
    void start();

private:
    GameManager *gameManager;
    GameLogic *gameLogic;

    void restartLevel();

    void loadNextLevel();

    std::shared_ptr<Command> startWinProcedure();
};

#endif // GAME_HPP

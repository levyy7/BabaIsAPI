//
// Created by Eneko on 21/03/2025.
//
#ifndef GAME_HPP
#define GAME_HPP

#include "game/logic/GameLogic.h"
#include "engine/WindowedGameManager.h"
#include "api/command/CommandQueue.h"
#include "api/command/StatusCommand.h"

enum GameMode {
    Headless,
    Windowed
};

class Game {
public:
    Game(EventManager *eventManager, GameMode mode);

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

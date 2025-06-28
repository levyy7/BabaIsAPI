#include "Game.h"

#include <iostream>
#include <chrono>

#include "../api/command/StatusCommand.h"

Game::Game(EventManager *eventManager, GameMode mode) {
    LevelInfo currentLevel = LevelLoader::currentLevel();

    switch (mode) {
        case GameMode::Headless:
            gameManager = new GameManager(dynamic_cast<ApiEventManager *>(eventManager), currentLevel);
            break;
        case GameMode::Windowed:
            gameManager = new WindowedGameManager(eventManager, currentLevel);
            break;
    }

    gameLogic = new GameLogic(currentLevel.sizeX, currentLevel.sizeY, currentLevel.blocks);
}

Game::Game(std::vector<EventManager *> eventManagers) {
    LevelInfo currentLevel = LevelLoader::currentLevel();

    gameManager = new WindowedGameManager(eventManagers, currentLevel);
    gameLogic = new GameLogic(currentLevel.sizeX, currentLevel.sizeY, currentLevel.blocks);
}

Game::~Game() {
    delete gameManager;
}

void Game::start() {
    std::shared_ptr<Command> command;
    auto rules = gameLogic->getRules();
    do {
        command = gameManager->waitUntilCommand();

        switch (command->getCommandType()) {
            case CommandType::LEFT:
                gameLogic->move(MoveDirection::LEFT);
                break;
            case CommandType::RIGHT:
                gameLogic->move(MoveDirection::RIGHT);
                break;
            case CommandType::UP:
                gameLogic->move(MoveDirection::UP);
                break;
            case CommandType::DOWN:
                gameLogic->move(MoveDirection::DOWN);
                break;
            case CommandType::STILL:
                gameLogic->move(MoveDirection::STILL);
                break;
            case CommandType::RESTART:
                restartLevel();
                break;
            case CommandType::NEXT:
                loadNextLevel();
                break;
            case CommandType::STATUS:
                LevelInfo currentLevel = LevelLoader::currentLevel();
                if (std::shared_ptr<StatusCommand> statusCommand = std::static_pointer_cast<StatusCommand>(command)) {
                    std::shared_ptr<StatusDTO> status = std::make_shared<StatusDTO>(
                        currentLevel.levelId, currentLevel.levelName,
                        std::make_pair(currentLevel.sizeX, currentLevel.sizeY), gameLogic->levelCompleted(),
                        gameLogic->getLevelMap(), gameLogic->getRules());
                    statusCommand->setStatus(status);
                }
                break;
        }

        if (gameLogic->levelCompleted())
            command = startWinProcedure();

        //printBlockMapJson(gameLogic->getLevelInfo());
        gameManager->updateGameState(gameLogic->getLevelMap());
    } while (command->getCommandType() != CommandType::EXIT);
}

void Game::restartLevel() {
    LevelInfo currentLevel = LevelLoader::currentLevel();
    gameLogic->loadLevel(currentLevel.sizeX, currentLevel.sizeY, currentLevel.blocks);
}

void Game::loadNextLevel() {
    LevelInfo currentLevel = LevelLoader::nextLevel();
    gameLogic->loadLevel(currentLevel.sizeX, currentLevel.sizeY, currentLevel.blocks);
}

std::shared_ptr<Command> Game::startWinProcedure() {
    gameManager->updateGameState(gameLogic->getLevelMap());
    std::cout << "Level Completed!" << std::endl;

    std::shared_ptr<Command> command;
    auto rules = gameLogic->getRules();

    // Record the start time
    auto start_time = std::chrono::steady_clock::now();

    do {
        command = gameManager->waitUntilCommand(1.0);

        switch (command->getCommandType()) {
            case CommandType::RESTART:
                restartLevel();
                return command;
            case CommandType::NEXT:
                loadNextLevel();
                return command;
            case CommandType::STATUS: {
                LevelInfo currentLevel = LevelLoader::currentLevel();
                if (std::shared_ptr<StatusCommand> statusCommand = std::static_pointer_cast<StatusCommand>(command)) {
                    std::shared_ptr<StatusDTO> status = std::make_shared<StatusDTO>(
                        currentLevel.levelId, currentLevel.levelName,
                        std::make_pair(currentLevel.sizeX, currentLevel.sizeY), gameLogic->levelCompleted(),
                        gameLogic->getLevelMap(), gameLogic->getRules());
                    statusCommand->setStatus(status);
                }
            }
            break;
        }

        // Check elapsed time
        auto elapsed_time = std::chrono::duration<double>(std::chrono::steady_clock::now() - start_time).count();
        if (elapsed_time > 3.0) {
            std::cout << "Time limit exceeded! Automatically proceeding to next level.\n";
            break;
        }
    } while (command->getCommandType() != CommandType::EXIT);

    loadNextLevel();
    return command;
}

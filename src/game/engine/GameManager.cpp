//
// Created by levy on 6/28/25.
//

#include "GameManager.h"

GameManager::GameManager(LevelInfo level) {
    currentMap = level;
    gameState = currentMap.blocks;
}

GameManager::GameManager(ApiEventManager *apiEventManager, LevelInfo level) {
    this->eventManagers.push_back(apiEventManager);

    currentMap = level;
    gameState = currentMap.blocks;
}

std::shared_ptr<Command> GameManager::waitUntilCommand() {
    int index = 0;
    std::optional<std::shared_ptr<Command> > command;
    while (not command.has_value()) {
        //animations....

        command = eventManagers[index % static_cast<int>(eventManagers.size())]->pollCommand();

        ++index;
    }

    return command.value();
}

std::shared_ptr<Command> GameManager::waitUntilCommand(double max_wait_time) {
    int index = 0;
    std::optional<std::shared_ptr<Command> > command;

    // Record the start time
    auto start_time = std::chrono::steady_clock::now();

    while (!command.has_value()) {
        // animations...

        command = eventManagers[index % static_cast<int>(eventManagers.size())]->pollCommand();
        ++index;

        // Check if max wait time is exceeded
        auto elapsed_time = std::chrono::duration<double>(std::chrono::steady_clock::now() - start_time).count();
        if (elapsed_time > max_wait_time) {
            return std::make_shared<Command>(CommandType::STILL);
        }
    }

    return command.value();
}

void GameManager::updateLevel(LevelInfo newLevel) {
    currentMap = newLevel;
    gameState = currentMap.blocks;
}

void GameManager::updateGameState(BlockMap newState) {
    gameState = newState;
}

BlockMap GameManager::getGameState() {
    return gameState;
}

GameManager::~GameManager() {

}
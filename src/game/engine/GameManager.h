//
// Created by levy on 6/28/25.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <map>
#include <memory>

#include "LevelLoader.h"
#include "event/ApiEventManager.h"
#include "../../api/command/Command.h"

class GameManager {
public:
    GameManager(LevelInfo level);

    GameManager(ApiEventManager *apiEventManager, LevelInfo level);

    std::shared_ptr<Command> waitUntilCommand();

    std::shared_ptr<Command> waitUntilCommand(double max_wait_time);

    virtual void updateLevel(LevelInfo newLevel);

    virtual void updateGameState(BlockMap newState);

    virtual BlockMap getGameState();

    ~GameManager();

protected:
    const unsigned int SCREEN_WIDTH = 1280;
    const unsigned int SCREEN_HEIGHT = 720;

    const std::string MAP_PATH = "maps/";
    const std::vector<std::string> MAP_FILENAMES = {"level00.json"};
    const int DEFAULT_MAP_INDEX = 0;

    LevelInfo currentMap;
    BlockMap gameState;

    std::vector<EventManager *> eventManagers;
};



#endif //GAMEMANAGER_H

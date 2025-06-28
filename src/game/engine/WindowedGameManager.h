//
// Created by levy on 6/28/25.
//

#ifndef WINDOWEDGAMEMANAGER_H
#define WINDOWEDGAMEMANAGER_H

#include <SFML/Graphics.hpp>

#include "GameManager.h"
#include "GraphicManager.h"
#include "event/KeyboardEventManager.h"


class WindowedGameManager : public GameManager {
public:
    WindowedGameManager(LevelInfo level);

    WindowedGameManager(EventManager *eventManager, LevelInfo level);

    WindowedGameManager(std::vector<EventManager *> &eventManagers, LevelInfo level);

    void updateLevel(LevelInfo newLevel) override;

    void updateGameState(BlockMap newState) override;

    BlockMap getGameState() override;

    ~WindowedGameManager();

private:
    GraphicManager *graphicManager;

    void refreshGameWindow();
};



#endif //WINDOWEDGAMEMANAGER_H

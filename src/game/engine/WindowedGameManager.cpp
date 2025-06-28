//
// Created by levy on 6/28/25.
//

#include "WindowedGameManager.h"

WindowedGameManager::WindowedGameManager(LevelInfo level) : GameManager(level) {
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "BabaIsBot",
        sf::Style::Default);
    window->setFramerateLimit(30);

    graphicManager = new GraphicManager(window);
    eventManagers.push_back(new KeyboardEventManager(window));

    graphicManager->setPlayingArea(currentMap.sizeX, currentMap.sizeY);

    refreshGameWindow();
}

WindowedGameManager::WindowedGameManager(EventManager *eventManager, LevelInfo level) : GameManager(level) {
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "BabaIsBot",
        sf::Style::Default);
    window->setFramerateLimit(30);

    graphicManager = new GraphicManager(window);

    this->eventManagers.push_back(eventManager);
    if (KeyboardEventManager *kem = dynamic_cast<KeyboardEventManager *>(eventManager)) {
        kem->setWindow(window);
    }

    graphicManager->setPlayingArea(currentMap.sizeX, currentMap.sizeY);

    refreshGameWindow();
}

WindowedGameManager::WindowedGameManager(std::vector<EventManager *> &eventManagers, LevelInfo level) : GameManager(level)  {
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "BabaIsBot",
        sf::Style::Default);
    window->setFramerateLimit(30);

    graphicManager = new GraphicManager(window);

    this->eventManagers = eventManagers;
    for (EventManager *eventManager: eventManagers) {
        if (KeyboardEventManager *kem = dynamic_cast<KeyboardEventManager *>(eventManager)) {
            kem->setWindow(window);
        }
    }

    graphicManager->setPlayingArea(currentMap.sizeX, currentMap.sizeY);

    refreshGameWindow();
}

void WindowedGameManager::updateLevel(LevelInfo newLevel) {
    currentMap = newLevel;
    gameState = currentMap.blocks;

    graphicManager->setPlayingArea(currentMap.sizeX, currentMap.sizeY);

    refreshGameWindow();
}

void WindowedGameManager::updateGameState(BlockMap newState) {
    gameState = newState;
    refreshGameWindow();
}

BlockMap WindowedGameManager::getGameState() {
    return gameState;
}

WindowedGameManager::~WindowedGameManager() {
    delete graphicManager;
}

void WindowedGameManager::refreshGameWindow() {
    graphicManager->drawPlayingArea();

    for (auto const &block: gameState) {
        std::string blockName = block.first;
        std::vector<std::pair<int, int> > blockPositions = block.second;

        for (std::pair<int, int> blockPosition: blockPositions) {
            graphicManager->drawSpriteAtCell(blockName, blockPosition.first, blockPosition.second);
        }
    }

    graphicManager->display();
}
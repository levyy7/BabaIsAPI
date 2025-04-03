//
// Created by Eneko on 02/03/2025.
//
module;

#include <iostream>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "../../api/command/Command.h"

export module GameManager;

import LevelLoader;
import GraphicManager;
export import KeyboardEventManager;
export import ApiEventManager;


export class GameManager {
public:
    GameManager(LevelInfo level) {
        std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(
            sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "BabaIsBot",
            sf::Style::Default);
        window->setFramerateLimit(30);

        graphicManager = new GraphicManager(window);
        eventManagers.push_back(new KeyboardEventManager(window));
        currentMap = level;
        gameState = currentMap.blocks;

        graphicManager->setPlayingArea(currentMap.sizeX, currentMap.sizeY);

        refreshGameWindow();
    }

    GameManager(EventManager *eventManager, LevelInfo level) {
        std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(
            sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "BabaIsBot",
            sf::Style::Default);
        window->setFramerateLimit(30);

        graphicManager = new GraphicManager(window);

        this->eventManagers.push_back(eventManager);
        if (KeyboardEventManager *kem = dynamic_cast<KeyboardEventManager *>(eventManager)) {
            kem->setWindow(window);
        }

        currentMap = level;
        gameState = currentMap.blocks;

        graphicManager->setPlayingArea(currentMap.sizeX, currentMap.sizeY);

        refreshGameWindow();
    }

    GameManager(std::vector<EventManager *> &eventManagers, LevelInfo level) {
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

        currentMap = level;
        gameState = currentMap.blocks;

        graphicManager->setPlayingArea(currentMap.sizeX, currentMap.sizeY);

        refreshGameWindow();
    }


    std::shared_ptr<Command> waitUntilCommand() {
        int index = 0;
        std::optional<std::shared_ptr<Command> > command;
        while (not command.has_value()) {
            //animations....

            command = eventManagers[index % static_cast<int>(eventManagers.size())]->pollCommand();

            ++index;
        }

        return command.value();
    }

    std::shared_ptr<Command> waitUntilCommand(double max_wait_time) {
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

    void updateLevel(LevelInfo newLevel) {
        currentMap = newLevel;
        gameState = currentMap.blocks;

        graphicManager->setPlayingArea(currentMap.sizeX, currentMap.sizeY);

        refreshGameWindow();
    }

    void updateGameState(BlockMap newState) {
        gameState = newState;
        refreshGameWindow();
    }

    BlockMap getGameState() {
        return gameState;
    }

    ~GameManager() {
        delete graphicManager;
    }

private:
    const unsigned int SCREEN_WIDTH = 1280;
    const unsigned int SCREEN_HEIGHT = 720;

    const std::string MAP_PATH = "maps/";
    const std::vector<std::string> MAP_FILENAMES = {"level00.json"};
    const int DEFAULT_MAP_INDEX = 0;

    LevelInfo currentMap;
    BlockMap gameState;

    GraphicManager *graphicManager;
    std::vector<EventManager *> eventManagers;

    void refreshGameWindow() {
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
};

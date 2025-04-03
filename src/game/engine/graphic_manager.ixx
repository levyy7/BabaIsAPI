//
// Created by Eneko on 21/02/2025.
//
module;

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>

export module GraphicManager;

import SpriteManager;


export class GraphicManager {
public:
    explicit GraphicManager() {
        this->window = std::make_shared<sf::RenderWindow>(
            sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "BabaIsBot",
            sf::Style::Default);
        window->setFramerateLimit(30);

        spriteManager = new SpriteManager();
    }

    explicit GraphicManager(const std::shared_ptr<sf::RenderWindow> &window) {
        this->window = window;

        spriteManager = new SpriteManager();
    }

    void display() {
        window->display();
    }

    void setPlayingArea(int numCellsX, int numCellsY) {
        sf::Vector2u windowSize = window->getSize();

        if (numCellsX / (float) numCellsY > windowSize.x / (float) windowSize.y) {
            int availablePixelsX = floor(windowSize.x - PADDING_MIN_X * 2 * windowSize.x);
            mapSizeX = availablePixelsX - availablePixelsX % numCellsX;

            cellSize = mapSizeX / numCellsX;

            mapSizeY = numCellsY * cellSize;
        } else {
            int availablePixelsY = floor(windowSize.y - PADDING_MIN_Y * 2 * windowSize.y);
            mapSizeY = availablePixelsY - availablePixelsY % numCellsY;

            cellSize = mapSizeY / numCellsY;

            mapSizeX = numCellsX * cellSize;
        }
        //std::cout << mapSizeX << " " << mapSizeY << std::endl;
        //std::cout << cellSize << std::endl;

        mapIniPixelX = (windowSize.x - mapSizeX) / 2;
        mapIniPixelY = (windowSize.y - mapSizeY) / 2;


        assert(mapSizeX%numCellsX == 0);
        assert(mapSizeY%numCellsY == 0);
    }

    void drawPlayingArea() {
        sf::RectangleShape playArea(sf::Vector2f(mapSizeX, mapSizeY));
        // Size (width: 100, height: 200)
        playArea.setPosition(sf::Vector2f(mapIniPixelX, mapIniPixelY));
        // Set position (x: 100, y: 100)
        playArea.setFillColor(sf::Color::Black);

        window->clear(sf::Color(2, 2, 14));
        window->draw(playArea);
    }

    void drawSpriteAtCell(std::string blockName, int posBlockX, int posBlockY) {
        assert(posBlockX >= 0 && posBlockX < mapSizeX/cellSize);
        assert(posBlockY >= 0 && posBlockY < mapSizeY/cellSize);

        sf::Sprite *sprite = spriteManager->getSprite(blockName);

        sf::Vector2f sprite_size = sprite->getGlobalBounds().size;
        //std::cout << sprite_size.x << " " << sprite_size.y << std::endl;
        float scale_factor = cellSize / sprite_size.x;

        unsigned int sprite_pos_X = mapIniPixelX + posBlockX * cellSize;
        unsigned int sprite_pos_Y = mapIniPixelY + posBlockY * cellSize;
        sf::Vector2f sprite_pos(sprite_pos_X, sprite_pos_Y);
        //std::cout << sprite_pos.x << " " << sprite_pos.y << std::endl;

        if (scale_factor != 1.0f) sprite->setScale({scale_factor, scale_factor});
        sprite->setPosition(sprite_pos);

        window->draw(*sprite);
    }

    ~GraphicManager() {
        delete spriteManager;
    }

private:
    const unsigned int SCREEN_WIDTH = 1280;
    const unsigned int SCREEN_HEIGHT = 720;
    const float PADDING_MIN_X = 0.05f;
    const float PADDING_MIN_Y = 0.05f;

    std::shared_ptr<sf::RenderWindow> window;

    unsigned int mapIniPixelX = 0;
    unsigned int mapIniPixelY = 0;
    unsigned int mapSizeX = 0;
    unsigned int mapSizeY = 0;
    unsigned int cellSize = 0;

    SpriteManager *spriteManager;
    float spriteScaleFactor = 1.0f;
};

//
// Created by levy on 6/28/25.
//

#ifndef GRAPHICMANAGER_H
#define GRAPHICMANAGER_H

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include "SpriteManager.h"

class GraphicManager {
public:
    explicit GraphicManager();

    explicit GraphicManager(const std::shared_ptr<sf::RenderWindow> &window);

    void display();

    void setPlayingArea(int numCellsX, int numCellsY);

    void drawPlayingArea();
    void drawSpriteAtCell(std::string blockName, int posBlockX, int posBlockY);

    ~GraphicManager();

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



#endif //GRAPHICMANAGER_H

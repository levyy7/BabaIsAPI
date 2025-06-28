//
// Created by levy on 6/28/25.
//

#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class SpriteManager {
public:
    // Structure to hold sprite info: which sheet and the rectangle in that sheet.
    struct SpriteInfo {
        size_t sheetIndex; // index in the textures vector
        sf::IntRect rect; // rectangle defining the sprite block
    };

    SpriteManager();

    // Given a sprite name, return the configured sprite.
    sf::Sprite *getSprite(const std::string &name);

    ~SpriteManager();

private:
    // Container for textures corresponding to each sprite sheet.
    std::vector<sf::Texture *> textures;
    // Map from sprite name to its associated SpriteInfo.
    std::map<std::string, sf::Sprite *> spriteMap;

    // Load each sprite sheet file once.
    void loadTextures();

    std::string toLowerCase(const std::string &s);

    // Set up the mapping between names and sprite information.
    void setupSpriteMap();
};



#endif //SPRITEMANAGER_H

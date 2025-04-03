//
// Created by Eneko on 08/03/2025.
//
export module SpriteManager;

import <SFML/Graphics.hpp>;
import <map>;
import <vector>;
import <string>;
import <iostream>;


export class SpriteManager {
public:
    // Structure to hold sprite info: which sheet and the rectangle in that sheet.
    struct SpriteInfo {
        size_t sheetIndex; // index in the textures vector
        sf::IntRect rect; // rectangle defining the sprite block
    };

    SpriteManager() {
        loadTextures();
        setupSpriteMap();
    }

    // Given a sprite name, return the configured sprite.
    sf::Sprite *getSprite(const std::string &name) {
        auto it = spriteMap.find(toLowerCase(name));
        if (it != spriteMap.end()) {
            return it->second;
        }
        // If not found, print error and return an empty sprite.
        std::cerr << "Sprite with name '" << name << "' not found.\n";
        return spriteMap["me"];
    }

    ~SpriteManager() {
        // Clean up textures
        for (auto tex: textures) {
            delete tex;
        }

        for (std::pair<std::string, sf::Sprite *> spr: spriteMap) {
            delete spr.second;
        }
    }

private:
    // Container for textures corresponding to each sprite sheet.
    std::vector<sf::Texture *> textures;
    // Map from sprite name to its associated SpriteInfo.
    std::map<std::string, sf::Sprite *> spriteMap;

    // Load each sprite sheet file once.
    void loadTextures() {
        std::vector<std::string> fileNames = {
            "./resources/sprites/characters.png",
            "./resources/sprites/statics.png",
            "./resources/sprites/texts.png",
            "./resources/sprites/tiles.png",
            "./resources/sprites/animated.png",
        };
        for (const auto &file: fileNames) {
            sf::Texture *texture = new sf::Texture();
            if (!texture->loadFromFile(file)) {
                std::cerr << "Error loading texture: " << file << "\n";
            }
            textures.push_back(texture);
        }
    }

    std::string toLowerCase(const std::string &s) {
        std::string result = s;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        return result;
    }

    // Set up the mapping between names and sprite information.
    void setupSpriteMap() {
        // Example: Map the name "Baba" to a sprite on sheet 0.
        // Assume each sprite is 25x25 pixels and the position is given by block indices.
        // Here, for "Baba", the sprite is at block (x=1, y=2) on the first sheet.
        spriteMap["baba"] = new sf::Sprite(*textures[0], sf::IntRect({25 * 23 + 1, 25 * 0 + 1}, {24, 24}));
        spriteMap["text_baba"] = new sf::Sprite(*textures[0], sf::IntRect({25 * 22 + 1, 25 * 0 + 1}, {24, 24}));
        spriteMap["keke"] = new sf::Sprite(*textures[0], sf::IntRect({25 * 23 + 1, 25 * 30 + 1}, {24, 24}));
        spriteMap["text_keke"] = new sf::Sprite(*textures[0], sf::IntRect({25 * 22 + 1, 25 * 30 + 1}, {24, 24}));
        spriteMap["me"] = new sf::Sprite(*textures[0], sf::IntRect({25 * 23 + 1, 25 * 36 + 1}, {24, 24}));
        spriteMap["text_me"] = new sf::Sprite(*textures[0], sf::IntRect({24 * 23 + 1, 25 * 36 + 1}, {24, 24}));

        spriteMap["rock"] = new sf::Sprite(*textures[1], sf::IntRect({25 * 9 + 1, 25 * 24 + 1}, {24, 24}));
        spriteMap["text_rock"] = new sf::Sprite(*textures[1], sf::IntRect({25 * 8 + 1, 25 * 24 + 1}, {24, 24}));
        spriteMap["flag"] = new sf::Sprite(*textures[1], sf::IntRect({25 * 4 + 1, 25 * 9 + 1}, {24, 24}));
        spriteMap["text_flag"] = new sf::Sprite(*textures[1], sf::IntRect({25 * 3 + 1, 25 * 9 + 1}, {24, 24}));
        spriteMap["door"] = new sf::Sprite(*textures[1], sf::IntRect({25 * 9 + 1, 25 * 6 + 1}, {24, 24}));
        spriteMap["text_door"] = new sf::Sprite(*textures[1], sf::IntRect({25 * 8 + 1, 25 * 6 + 1}, {24, 24}));
        spriteMap["key"] = new sf::Sprite(*textures[1], sf::IntRect({25 * 4 + 1, 25 * 15 + 1}, {24, 24}));
        spriteMap["text_key"] = new sf::Sprite(*textures[1], sf::IntRect({25 * 3 + 1, 25 * 15 + 1}, {24, 24}));

        spriteMap["is"] = new sf::Sprite(*textures[2], sf::IntRect({25 * 11 + 1, 25 * 3 + 1}, {24, 24}));
        spriteMap["you"] = new sf::Sprite(*textures[2], sf::IntRect({25 * 11 + 1, 25 * 9 + 1}, {24, 24}));
        spriteMap["push"] = new sf::Sprite(*textures[2], sf::IntRect({25 * 2 + 1, 25 * 12 + 1}, {24, 24}));
        spriteMap["stop"] = new sf::Sprite(*textures[2], sf::IntRect({25 * 8 + 1, 25 * 12 + 1}, {24, 24}));
        spriteMap["win"] = new sf::Sprite(*textures[2], sf::IntRect({25 * 11 + 1, 25 * 44 + 22 + 1}, {24, 24}));
        spriteMap["defeat"] = new sf::Sprite(*textures[2], sf::IntRect({25 * 2 + 1, 25 * 29 + 5}, {24, 24}));
        spriteMap["sink"] = new sf::Sprite(*textures[2], sf::IntRect({25 * 2 + 1, 25 * 32 + 5}, {24, 24}));
        spriteMap["hot"] = new sf::Sprite(*textures[2], sf::IntRect({25 * 5 + 1, 25 * 29 + 5}, {24, 24}));
        spriteMap["melt"] = new sf::Sprite(*textures[2], sf::IntRect({25 * 8 + 1, 25 * 29 + 5}, {24, 24}));

        spriteMap["wall"] = new sf::Sprite(*textures[3], sf::IntRect({25 * 19 + 1, 25 * 60 + 1}, {24, 24}));
        spriteMap["text_wall"] = new sf::Sprite(*textures[3], sf::IntRect({25 * 18 + 1, 25 * 60 + 1}, {24, 24}));
        spriteMap["water"] = new sf::Sprite(*textures[3], sf::IntRect({25 * 19 + 1, 25 * 63 + 1}, {24, 24}));
        spriteMap["text_water"] = new sf::Sprite(*textures[3], sf::IntRect({25 * 18 + 1, 25 * 63 + 1}, {24, 24}));
        spriteMap["lava"] = new sf::Sprite(*textures[3], sf::IntRect({25 * 19 + 1, 25 * 36 + 1}, {24, 24}));
        spriteMap["text_lava"] = new sf::Sprite(*textures[3], sf::IntRect({25 * 18 + 1, 25 * 36 + 1}, {24, 24}));

        spriteMap["skull"] = new sf::Sprite(*textures[4], sf::IntRect({25 * 7 + 1, 25 * 36 + 21 + 1}, {24, 24}));
        spriteMap["text_skull"] = new sf::Sprite(*textures[4], sf::IntRect({25 * 6 + 1, 25 * 36 + 21 + 1}, {24, 24}));
    }
};

//
// Created by levy on 6/28/25.
//

#include <boost/json/src.hpp>
#include "LevelLoader.h"

LevelInfo LevelLoader::currentLevel() {
    return loadFromFile(MAP_PATH + MAP_FILENAMES[mapIndex]);
}

LevelInfo LevelLoader::nextLevel() {
    if (mapIndex < MAP_FILENAMES.size() - 1)
        ++mapIndex;
    else
        mapIndex = 0;

    return currentLevel();
}

LevelInfo LevelLoader::loadFromFile(const std::string &filePath) {
    // Check file extension.
    if (filePath.size() >= 5 && filePath.substr(filePath.size() - 5) == ".json") {
        std::ifstream ifs(filePath);
        if (!ifs.is_open()) {
            throw std::runtime_error("Unable to open file: " + filePath);
        }
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        boost::json::value jv = boost::json::parse(buffer.str());

        // Serialize the JSON value to a string and print it.
        std::string json_str = boost::json::serialize(jv);
        std::cout << json_str << std::endl;

        return parseLevel(jv.as_object());
    } else if (filePath.size() >= 4 && filePath.substr(filePath.size() - 4) == ".txt") {
        return loadFromTxtFile(filePath);
    } else {
        throw std::runtime_error("Unsupported file extension in file: " + filePath);
    }
}

LevelInfo LevelLoader::loadFromString(const std::string &jsonString) {
    boost::json::value jv = boost::json::parse(jsonString);
    return parseLevel(jv.as_object());
}

LevelInfo LevelLoader::parseLevel(const boost::json::object &obj) {
    LevelInfo level;
    level.levelId = obj.at("level id").as_int64();
    level.levelName = obj.at("level name").as_string().c_str();
    level.sizeX = obj.at("sizeX").as_int64();
    level.sizeY = obj.at("sizeY").as_int64();

    // Parse the blocks object.
    const boost::json::object &blocksObj = obj.at("blocks").as_object();
    for (const auto &item: blocksObj) {
        const std::string &key = item.key();
        const boost::json::array &positions = item.value().as_array();
        std::vector<std::pair<int, int> > posVec;
        for (const auto &pos: positions) {
            const boost::json::array &coords = pos.as_array();
            int x = coords.at(0).as_int64();
            int y = coords.at(1).as_int64();
            posVec.emplace_back(x, y);
        }
        level.blocks[key] = posVec;
    }
    return level;
}

LevelInfo LevelLoader::loadFromTxtFile(const std::string &filePath) {
    std::ifstream mapFile(filePath);
    if (!mapFile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }

    int width = 0, height = 0;
    mapFile >> width >> height;
    if (!mapFile) {
        throw std::runtime_error("Failed to read width and height from file: " + filePath);
    }

    std::filesystem::path pathObj(filePath);

    LevelInfo level;
    level.levelId = mapIndex;
    level.levelName = pathObj.stem().string();
    level.sizeX = width;
    level.sizeY = height;

    // Calculate total number of tiles.
    int totalTiles = width * height;

    // Determine the total number of block types.
    int totalBlockTypes = sizeof(BlockTypeNames) / sizeof(BlockTypeNames[0]);

    // Read each tile value and map it to a block type.
    for (int i = 0; i < totalTiles; ++i) {
        int val = 0;
        mapFile >> val;
        if (!mapFile) {
            throw std::runtime_error("Failed to read block value from file: " + filePath);
        }

        if (val < 0 || val >= totalBlockTypes) {
            throw std::runtime_error("Invalid block type value (" + std::to_string(val) + ") in file: " + filePath);
        }
        std::string blockName = BlockTypeNames[val];

        if (blockName == "EMPTY") continue; //For simplicity purposes

        // Determine (x,y) position from the tile index.
        int x = i % width;
        int y = i / width;

        // Add the position to the block map.
        level.blocks[blockName].emplace_back(x, y);
    }
    return level;
}
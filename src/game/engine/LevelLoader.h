//
// Created by levy on 6/28/25.
//

#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <boost/json.hpp>


// Typedef for blocks mapping
using BlockMap = std::map<std::string, std::vector<std::pair<int, int> > >;

// Structure that resembles your JSON level format.
struct LevelInfo {
    int levelId;
    std::string levelName;
    int sizeX;
    int sizeY;
    BlockMap blocks;
};

const std::string MAP_PATH = "resources/maps/";
const std::vector<std::string> MAP_FILENAMES = {
    "baba_is_you.txt", "off_limits.txt", "off_limits_bug.txt", "out_of_reach.txt", "volcano.txt"
};

// Enum and names definitions for block types.
enum BlockType {
    NOUN_TYPE,
#define X(a) a,
#include "NounType.def"
#undef X
    OP_TYPE,
#define X(a) a,
#include "OpType.def"
#undef X
    PROPERTY_TYPE,
#define X(a) a,
#include "PropertyType.def"
#undef X
    ICON_TYPE,
#define X(a) a,
#include "IconType.def"
#undef X
};

inline const char *BlockTypeNames[] = {
    "NOUN_TYPE",
#define X(a) #a,
#include "NounType.def"
#undef X
    "OP_TYPE",
#define X(a) #a,
#include "OpType.def"
#undef X
    "PROPERTY_TYPE",
#define X(a) #a,
#include "PropertyType.def"
#undef X
    "ICON_TYPE",
#define X(a) #a,
#include "IconType.def"
#undef X
};

class LevelLoader {
public:
    inline static int mapIndex = 0;

    static LevelInfo currentLevel();

    static LevelInfo nextLevel();

private:
    // Loads a Level from a file. Supports both JSON (.json) and text (.txt) formats.
    static LevelInfo loadFromFile(const std::string &filePath);

    // Loads a Level from a JSON string.
    static LevelInfo loadFromString(const std::string &jsonString);

    // Helper function to parse the JSON object into a LevelInfo struct.
    static LevelInfo parseLevel(const boost::json::object &obj);

    // Loads a Level from a .txt file.
    static LevelInfo loadFromTxtFile(const std::string &filePath);
};



#endif //LEVELLOADER_H

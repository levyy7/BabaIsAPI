//
// Created by Eneko on 22/03/2025.
//

#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H
#include <map>
#include "Block.h"


class BlockFactory {
public:
    static Block *produceBlock(const std::string &blockName);

    static Block *produceBlock(const std::string &blockName, Location location);

private:
    static std::string toUpperCase(const std::string &s);
};


#endif //BLOCKFACTORY_H

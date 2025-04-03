//
// Created by Eneko on 23/03/2025.
//

#ifndef PROPERTY_H
#define PROPERTY_H
#include <set>

#include "Block.h"


class Property {
public:
    Property(std::string name);

    virtual ~Property() = default;

    [[nodiscard]] std::string getName() const;

    virtual std::set<Block *> getBlocksToDelete(Block *const executedBy, const std::vector<Block *> &blocksInCell);

    virtual bool stops(const Block *&block);

    virtual bool isPushedBy(const Block *&block);

    virtual bool isMoveable();

    virtual bool isWin(const std::vector<Block *> &blocksInCell);

private:
    std::string name;
};


#endif //PROPERTY_H

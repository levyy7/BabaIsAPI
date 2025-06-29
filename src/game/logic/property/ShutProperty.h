//
// Created by Eneko on 01/04/2025.
//

#ifndef SHUTPROPERTY_H
#define SHUTPROPERTY_H
#include "Property.h"
#include "game/logic/level/block/Block.h"


class ShutProperty : public Property {
public:
    ShutProperty();

    bool stops(const Block *&block) override;

    std::set<Block *> getBlocksToDelete(Block *const executedBy, const std::vector<Block *> &blocksInCell) override;
};


#endif //SHUTPROPERTY_H

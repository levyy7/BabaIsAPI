//
// Created by Eneko on 01/04/2025.
//

#ifndef HOTPROPERTY_H
#define HOTPROPERTY_H
#include "Property.h"


class HotProperty : public Property {
public:
    HotProperty();

    std::set<Block *> getBlocksToDelete(Block *const executedBy, const std::vector<Block *> &blocksInCell) override;
};


#endif //HOTPROPERTY_H

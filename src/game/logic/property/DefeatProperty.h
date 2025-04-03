//
// Created by Eneko on 01/04/2025.
//

#ifndef DEFEATPROPERTY_H
#define DEFEATPROPERTY_H
#include "Property.h"


class DefeatProperty : public Property {
public:
    DefeatProperty();

    std::set<Block *> getBlocksToDelete(Block *const executedBy, const std::vector<Block *> &blocksInCell) override;
};


#endif //DEFEATPROPERTY_H

//
// Created by Eneko on 01/04/2025.
//

#ifndef SINKPROPERTY_H
#define SINKPROPERTY_H
#include "Property.h"


class SinkProperty : public Property {
public:
    SinkProperty();

    std::set<Block *> getBlocksToDelete(Block *const executedBy, const std::vector<Block *> &blocksInCell) override;
};


#endif //SINKPROPERTY_H

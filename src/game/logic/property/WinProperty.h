//
// Created by Eneko on 26/03/2025.
//

#ifndef WINPROPERTY_H
#define WINPROPERTY_H
#include <vector>

#include "Property.h"
#include "game/logic/level/block/Block.h"


class WinProperty : public Property {
public:
    WinProperty();

    bool isWin(const std::vector<Block *> &blocksInCell) override;
};


#endif //WINPROPERTY_H

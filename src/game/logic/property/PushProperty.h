//
// Created by Eneko on 26/03/2025.
//

#ifndef PUSHPROPERTY_H
#define PUSHPROPERTY_H
#include "Property.h"
#include "game/logic/level/block/Block.h"


class PushProperty final : public Property {
public:
    PushProperty();

    bool isPushedBy(const Block *&block) override;
};


#endif //PUSHPROPERTY_H

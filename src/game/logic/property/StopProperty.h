//
// Created by Eneko on 26/03/2025.
//

#ifndef WALLPROPERTY_H
#define WALLPROPERTY_H
#include "Property.h"


class StopProperty final : public Property {
public:
    StopProperty();

    bool stops(const Block *&block) override;
};


#endif //WALLPROPERTY_H

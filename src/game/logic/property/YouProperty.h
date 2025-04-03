//
// Created by Eneko on 26/03/2025.
//

#ifndef YOUPROPERTY_H
#define YOUPROPERTY_H
#include "Property.h"


class YouProperty final : public Property {
public:
    YouProperty();

    bool isMoveable() override;
};


#endif //YOUPROPERTY_H

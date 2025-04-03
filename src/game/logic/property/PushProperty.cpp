//
// Created by Eneko on 26/03/2025.
//

#include "PushProperty.h"

PushProperty::PushProperty() : Property("PUSH") {
}

bool PushProperty::isPushedBy(const Block *&block) {
    return true;
}

//
// Created by Eneko on 26/03/2025.
//

#include "StopProperty.h"

StopProperty::StopProperty() : Property("STOP") {
}

bool StopProperty::stops(const Block *&block) {
    return true;
}

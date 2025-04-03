//
// Created by Eneko on 27/03/2025.
//

#include "PropertyController.h"


Property *PropertyController::getProperty(std::string propertyName) {
    return PROPERTY_MAP[propertyName];
}

std::map<std::string, Property *> PropertyController::getPropertyMap() {
    return PROPERTY_MAP;
}

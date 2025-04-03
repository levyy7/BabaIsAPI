//
// Created by Eneko on 27/03/2025.
//

#include "PropertyRule.h"

PropertyRule::PropertyRule(NounBlock *subject, PropertyBlock *object) : Rule(subject) {
    this->object = object;
}

PropertyBlock *PropertyRule::getObject() const {
    return object;
}

std::string PropertyRule::getObjectName() const {
    return object->getName();
}

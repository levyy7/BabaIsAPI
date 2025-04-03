//
// Created by Eneko on 27/03/2025.
//

#include "NounRule.h"

NounRule::NounRule(NounBlock *subject, NounBlock *object) : Rule(subject) {
    this->object = object;
}

NounBlock *NounRule::getObject() const {
    return object;
}

std::string NounRule::getObjectName() const {
    return object->getName();
}

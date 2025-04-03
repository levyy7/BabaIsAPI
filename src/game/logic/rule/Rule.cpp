//
// Created by Eneko on 27/03/2025.
//

#include "Rule.h"

Rule::Rule(NounBlock *subject) {
    this->subject = subject;
}

NounBlock *Rule::getSubject() const {
    return subject;
}

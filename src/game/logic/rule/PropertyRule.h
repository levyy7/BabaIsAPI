//
// Created by Eneko on 27/03/2025.
//

#ifndef PROPERTYRULE_H
#define PROPERTYRULE_H
#include "PropertyBlock.h"
#include "Rule.h"


class PropertyRule : public Rule {
public:
    PropertyRule(NounBlock *subject, PropertyBlock *object);

    [[nodiscard]] PropertyBlock *getObject() const;

    [[nodiscard]] std::string getObjectName() const override;

private:
    PropertyBlock *object;
};


#endif //PROPERTYRULE_H

//
// Created by Eneko on 27/03/2025.
//

#ifndef NOUNRULE_H
#define NOUNRULE_H
#include "Rule.h"


class NounRule : public Rule {
public:
    NounRule(NounBlock *subject, NounBlock *object);

    [[nodiscard]] NounBlock *getObject() const;

    [[nodiscard]] std::string getObjectName() const override;

private:
    NounBlock *object;
};


#endif //NOUNRULE_H

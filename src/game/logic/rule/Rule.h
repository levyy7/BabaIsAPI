//
// Created by Eneko on 27/03/2025.
//

#ifndef RULE_H
#define RULE_H
#include "NounBlock.h"
#include "TextBlock.h"


class Rule {
public:
    Rule(const Rule &) = default;

    Rule &operator=(const Rule &) = default;

    explicit Rule(NounBlock *subject);

    virtual ~Rule() = default;

    [[nodiscard]] NounBlock *getSubject() const;

    [[nodiscard]] virtual std::string getObjectName() const = 0;

private:
    NounBlock *subject;
    //std::vector<Condition> conditions{};
    //bool negated{};
};


#endif //RULE_H

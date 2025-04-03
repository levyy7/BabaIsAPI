//
// Created by Eneko on 27/03/2025.
//

#ifndef RULEINTERPRETER_H
#define RULEINTERPRETER_H
#include <unordered_set>

#include "NounRule.h"
#include "PropertyRule.h"
#include "Rule.h"


class BlockConcept;

class RuleInterpreter {
public:
    static void clearRules(const std::unordered_set<BlockConcept *> &concepts);

    static void executeNounRules(const std::vector<NounRule *> &rules);

    static void addDefaultPropertyRules();

    static void addPropertyRules(const std::vector<PropertyRule *> &rules);
};


#endif //RULEINTERPRETER_H

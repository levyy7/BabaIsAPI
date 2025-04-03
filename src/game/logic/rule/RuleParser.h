//
// Created by Eneko on 27/03/2025.
//

#ifndef RULEPARSER_H
#define RULEPARSER_H

#include "Rule.h"
#include "TextBlock.h"

class RuleParser {
public:
    static std::vector<Rule *> parseText(const std::vector<std::vector<TextBlock *> > &textSequences);
};


#endif //RULEPARSER_H

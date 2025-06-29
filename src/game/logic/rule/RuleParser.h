//
// Created by Eneko on 27/03/2025.
//

#ifndef RULEPARSER_H
#define RULEPARSER_H

#include <vector>

#include "game/logic/level/block/TextBlock.h"
#include "game/logic/rule/Rule.h"


class RuleParser {
public:
    static std::vector<Rule *> parseText(const std::vector<std::vector<TextBlock *> > &textSequences);
};


#endif //RULEPARSER_H

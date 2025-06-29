//
// Created by Eneko on 27/03/2025.
//

#include "RuleParser.h"

#include "game/logic/rule/NounRule.h"
#include "game/logic/rule/PropertyRule.h"
#include "game/logic/level/block/NounBlock.h"
#include "game/logic/level/block/PropertyBlock.h"
#include "game/logic/level/block/VerbBlock.h"


//Trivial way to parse text, which works only for 3 word texts
std::vector<Rule *> RuleParser::parseText(const std::vector<std::vector<TextBlock *> > &textSequences) {
    std::vector<Rule *> rules{};

    for (const std::vector<TextBlock *> &textSequence: textSequences) {
        for (int i = 0; i < static_cast<int>(textSequence.size() - 2); i++) {
            NounBlock *subject = dynamic_cast<NounBlock *>(textSequence[i]);
            VerbBlock *verb = dynamic_cast<VerbBlock *>(textSequence[i + 1]);
            PropertyBlock *property = dynamic_cast<PropertyBlock *>(textSequence[i + 2]);
            NounBlock *object = dynamic_cast<NounBlock *>(textSequence[i + 2]);

            if (subject and verb and property) {
                PropertyRule *rule = new PropertyRule(subject, property);
                rules.push_back(rule);
            } else if (subject and verb and object) {
                NounRule *rule = new NounRule(subject, object);
                rules.push_back(rule);
            }
        }
    }

    return rules;
}

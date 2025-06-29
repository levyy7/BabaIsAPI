//
// Created by Eneko on 23/03/2025.
//

#include "GameLogic.h"

#include "game/logic/level/block/NounBlock.h"
#include "game/logic/level/block/concept/ConceptController.h"
#include "game/logic/rule/RuleInterpreter.h"
#include "game/logic/rule/RuleParser.h"


GameLogic::GameLogic(int levelSizeX, int levelSizeY, const BlockMap &blockMap) {
    this->level = new Level(levelSizeX, levelSizeY, blockMap);
    winconFullfilled = false;

    rulePhase();
    actionPhase();
}

BlockMap GameLogic::getLevelMap() const {
    return level->toBlockMap();
}

std::map<std::string, std::vector<std::map<std::string, std::string> > > GameLogic::getRules() const {
    std::map<std::string, std::vector<std::map<std::string, std::string> > > rulesMap;

    for (const Rule *rule: rules) {
        if (rule) {
            // Retrieve the object name
            std::string objectName = rule->getObjectName();

            // Retrieve the subject
            NounBlock *subject = rule->getSubject();
            if (subject) {
                // Assuming NounBlock has a method getName() that returns std::string
                std::string subjectName = subject->getReferencedConcept()->getName();

                // Create a map representing the rule details
                std::map<std::string, std::string> ruleDetails;
                ruleDetails["subject"] = subjectName;
                ruleDetails["verb"] = "IS";
                ruleDetails["object"] = objectName;

                // Add the rule details to the corresponding vector in the map
                rulesMap[subjectName].push_back(ruleDetails);
            }
        }
    }

    return rulesMap;
}

void GameLogic::loadLevel(int levelSizeX, int levelSizeY, const BlockMap &blockMap) {
    delete this->level;
    this->level = new Level(levelSizeX, levelSizeY, blockMap);
    rulePhase();
    actionPhase();
}

void GameLogic::move(MoveDirection direction) {
    movePhase(direction);
    rulePhase();
    actionPhase();
}

bool GameLogic::levelCompleted() const {
    return winconFullfilled;
}

void GameLogic::movePhase(MoveDirection direction) {
    level->tryMoveAll(direction);
    level->refresh();
}

void GameLogic::rulePhase() {
    RuleInterpreter::clearRules(ConceptController::getBlockConcepts());
    RuleInterpreter::addDefaultPropertyRules();

    std::list<std::list<TextBlock *> > textSequencesList = level->getTextSequences();
    std::vector<std::vector<TextBlock *> > textSequences;
    for (const auto &lst: textSequencesList) {
        textSequences.emplace_back(lst.begin(), lst.end());
    }

    rules = RuleParser::parseText(textSequences);

    std::vector<PropertyRule *> propertyRules;

    for (const auto &rule: rules) {
        if (PropertyRule *propertyRule = dynamic_cast<PropertyRule *>(rule)) {
            propertyRules.push_back(propertyRule);
        }
    }

    RuleInterpreter::addPropertyRules(propertyRules);
}

void GameLogic::actionPhase() {
    std::vector<NounRule *> nounRules;
    for (const auto &rule: rules) {
        if (NounRule *nounRule = dynamic_cast<NounRule *>(rule)) {
            nounRules.push_back(nounRule);
        }
    }
    RuleInterpreter::executeNounRules(nounRules);
    level->refresh();

    level->tryExecuteAll();
    level->refresh();

    winconFullfilled = level->tryWinAll();

    level->refresh();
}

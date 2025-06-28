//
// Created by Eneko on 27/03/2025.
//

#include "RuleInterpreter.h"


#include "BlockConcept.h"
#include "BlockFactory.h"
#include "ConceptController.h"
#include "PropertyController.h"


void RuleInterpreter::clearRules(const std::unordered_set<BlockConcept *> &concepts) {
    for (BlockConcept *bc: concepts) {
        bc->clearProperties();
    }
}

void RuleInterpreter::executeNounRules(const std::vector<NounRule *> &rules) {
    for (NounRule *rule: rules) {
        std::unordered_set<Block *> subjectRepresentations = rule->getSubject()->getReferencedConcept()->
                getBlockRepresentations();
        std::string objectName = rule->getObject()->getReferencedConcept()->getName();

        for (Block *subject: subjectRepresentations) {
            BlockFactory::produceBlock(objectName, subject->getLocation());
            delete subject;
        }
    }
}

void RuleInterpreter::addDefaultPropertyRules() {
    ConceptController::getBlockConcept("TEXT")->addProperty(PropertyController::getProperty("PUSH"));
    //ConceptController::getBlockConcept("baba")->addProperty(PropertyController::getProperty("you"));
    //ConceptController::getBlockConcept("wall")->addProperty(PropertyController::getProperty("stop"));
}


void RuleInterpreter::addPropertyRules(const std::vector<PropertyRule *> &rules) {
    for (PropertyRule *rule: rules) {
        BlockConcept *bc = rule->getSubject()->getReferencedConcept();
        bc->addProperty(rule->getObject()->getProperty());
    }
}

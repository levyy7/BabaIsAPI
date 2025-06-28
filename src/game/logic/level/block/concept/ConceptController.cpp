//
// Created by Eneko on 22/03/2025.
//

#include "ConceptController.h"

#include <algorithm>

#include "Block.h"
#include "NounBlock.h"

std::unordered_set<BlockConcept *> ConceptController::getBlockConcepts() {
    return blockConcepts;
}

BlockConcept *ConceptController::getBlockConcept(const std::string &conceptName) {
    auto it = std::find_if(blockConcepts.begin(), blockConcepts.end(),
                           [&](BlockConcept *bc) {
                               return bc->getName() == conceptName;
                           });

    if (it == blockConcepts.end()) {
        BlockConcept *newConcept = new BlockConcept(conceptName);
        auto [insertedIt, inserted] = blockConcepts.insert(newConcept);
        it = insertedIt;
    }

    return *it;
}

void ConceptController::clearConcepts() {
    for (BlockConcept *bc: blockConcepts) {
        std::unordered_set<Block *> blockRepresentations = bc->getBlockRepresentations();
        std::unordered_set<NounBlock *> blockReferences = bc->getBlockReferences();

        for (Block *b: blockRepresentations) {
            delete b;
        }

        for (NounBlock *b: blockReferences) {
            delete b;
        }
    }

    blockConcepts.clear();
}

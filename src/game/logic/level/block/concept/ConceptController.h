//
// Created by Eneko on 22/03/2025.
//

#ifndef CONCEPTCONTROLLER_H
#define CONCEPTCONTROLLER_H
#include "BlockConcept.h"


class ConceptController {
public:
    static std::unordered_set<BlockConcept *> getBlockConcepts();

    static BlockConcept *getBlockConcept(const std::string &conceptName);

    static void clearConcepts();

private:
    inline static std::unordered_set<BlockConcept *> blockConcepts{};
};


#endif //CONCEPTCONTROLLER_H

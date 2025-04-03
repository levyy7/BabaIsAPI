//
// Created by Eneko on 22/03/2025.
//

#ifndef NOUN_H
#define NOUN_H
#include "TextBlock.h"


class NounBlock : public TextBlock {
public:
    explicit NounBlock(const std::string &name, BlockConcept *blockConcept, BlockConcept *referencedConcept);

    explicit NounBlock(const std::string &name, Location location, BlockConcept *blockConcept,
                       BlockConcept *referencedConcept);

    virtual ~NounBlock();

    [[nodiscard]] BlockConcept *getReferencedConcept() const;

private:
    BlockConcept *referencedConcept;
};


#endif //NOUN_H

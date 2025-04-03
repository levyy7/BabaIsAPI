//
// Created by Eneko on 22/03/2025.
//

#ifndef TEXT_H
#define TEXT_H
#include "Block.h"


class TextBlock : public Block {
public:
    explicit TextBlock(std::string name, BlockConcept *blockConcept);

    explicit TextBlock(std::string name, Location location, BlockConcept *blockConcept);

    virtual ~TextBlock();
};


#endif //TEXT_H

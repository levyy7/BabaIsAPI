//
// Created by Eneko on 22/03/2025.
//
#include <catch2/catch_test_macros.hpp>
#include "BlockFactory.h"
#include <string>
#include <unordered_set>

#include "ConceptController.h"
#include "NounBlock.h"

TEST_CASE("block concepts expand and shrink based on block instances", "[TestBlock]") {
    ConceptController::clearConcepts();
    BlockConcept *babaConcept = ConceptController::getBlockConcept("baba");

    REQUIRE(babaConcept->getName() == "baba");
    REQUIRE(babaConcept->getBlockRepresentations().empty());

    Block *baba1 = BlockFactory::produceBlock("baba");
    Block *baba2 = BlockFactory::produceBlock("baba");

    REQUIRE(baba1->getName() == "baba");
    REQUIRE(baba2->getName() == "baba");
    REQUIRE(baba1->getBlockConcept() == baba2->getBlockConcept());

    SECTION("block concept has declared blocks") {
        std::unordered_set<Block *> babaBlocks = babaConcept->getBlockRepresentations();

        REQUIRE(babaBlocks.size() == 2);
        REQUIRE(babaBlocks.find(baba1) != babaBlocks.end());
        REQUIRE(babaBlocks.find(baba2) != babaBlocks.end());
    }

    SECTION("block concept loses blocks when deleting block") {
        delete baba1;

        std::unordered_set<Block *> babaBlocks = babaConcept->getBlockRepresentations();
        REQUIRE(babaBlocks.size() == 1);
        REQUIRE(babaBlocks.find(baba1) == babaBlocks.end());
        REQUIRE(babaBlocks.find(baba2) != babaBlocks.end());
    }

    SECTION("noun blocks are added to referenced block in its according block concept") {
        Block *babatext = BlockFactory::produceBlock("text_baba");

        REQUIRE(dynamic_cast<NounBlock*>(babatext));

        NounBlock *babaNoun = dynamic_cast<NounBlock *>(babatext);

        BlockConcept *textConcept = babaNoun->getBlockConcept();
        std::unordered_set<Block *> textBlocks = textConcept->getBlockRepresentations();

        REQUIRE(textConcept->getName() == "TEXT");
        REQUIRE(textBlocks.size() == 1);
        REQUIRE(textBlocks.find(babatext) != textBlocks.end());

        BlockConcept *referencedConcept = babaNoun->getReferencedConcept();
        std::unordered_set<NounBlock *> babaTexts = referencedConcept->getBlockReferences();

        REQUIRE(referencedConcept->getName() == "baba");
        REQUIRE(babaTexts.size() == 1);
        REQUIRE(babaTexts.find(babaNoun) != babaTexts.end());
    }
}

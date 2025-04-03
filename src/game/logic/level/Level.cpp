//
// Created by Eneko on 23/03/2025.
//

#include "Level.h"

#include <algorithm>
#include <list>
#include <boost/move/utility_core.hpp>

#include "BlockFactory.h"
#include "ConceptController.h"
#include "PropertyController.h"
#include "SFML/Graphics/Text.hpp"

Level::Level(int levelSizeX, int levelSizeY, const BlockMap &blockMap) {
    this->levelSizeX = levelSizeX;
    this->levelSizeY = levelSizeY;
    blockLevel = std::vector<std::vector<Cell> >(levelSizeX, std::vector<Cell>(levelSizeY));
    fromBlockMap(blockMap);
}

Level::~Level() {
    ConceptController::clearConcepts();
}

void Level::refresh() {
    blockLevel = std::vector<std::vector<Cell> >(levelSizeX, std::vector<Cell>(levelSizeY));
    std::unordered_set<BlockConcept *> blockConcepts = ConceptController::getBlockConcepts();

    for (BlockConcept *bc: blockConcepts) {
        for (Block *b: bc->getBlockRepresentations()) {
            Location bLoc = b->getLocation();
            blockLevel[bLoc.x][bLoc.y].push_back(b);
        }
    }
}

void Level::tryMoveAll(MoveDirection direction) {
    for (int i = 0; i < levelSizeX; i++) {
        for (int j = 0; j < levelSizeY; j++) {
            tryMove(direction, Location(i, j));
        }
    }
}

void Level::tryMove(MoveDirection direction, Location pos) {
    bool anyMovedCell = false;
    for (Block *b: blockLevel[pos.x][pos.y]) {
        std::vector<Cell> cellsInDirection = getCellsInDirection(direction, pos);

        if (b->getBlockConcept()->isMoveable() and canMove(b, cellsInDirection)) {
            if (!anyMovedCell) {
                moveWithCollaterals(b, direction, cellsInDirection);
                anyMovedCell = true;
            } else {
                b->move(direction);
            }
        }
    }
}

bool Level::tryWinAll() {
    for (int i = 0; i < levelSizeX; i++) {
        for (int j = 0; j < levelSizeY; j++) {
            if (tryWin(Location(i, j))) return true;
        }
    }

    return false;
}

bool Level::tryWin(Location pos) {
    std::vector<Block *> blocksAtCell = blockLevel[pos.x][pos.y];
    for (Block *b: blocksAtCell) {
        if (b->getBlockConcept()->isWin(blocksAtCell)) return true;
    }

    return false;
}

void Level::tryExecuteAll() {
    for (int i = 0; i < levelSizeX; i++) {
        for (int j = 0; j < levelSizeY; j++) {
            tryExecute(Location(i, j));
        }
    }
}

void Level::tryExecute(Location pos) {
    std::vector<Block *> blocksAtCell = blockLevel[pos.x][pos.y];
    std::set<Block *> blocksToDelete = {};

    for (Block *b: blocksAtCell) {
        blocksToDelete = BlockConcept::unionSets(blocksToDelete,
                                                 b->getBlockConcept()->getBlocksToDelete(b, blocksAtCell));
    }

    for (Block *b: blocksToDelete) {
        delete b;
    }
}

std::list<std::list<TextBlock *> > Level::getTextSequences() const {
    std::list<std::list<TextBlock *> > textSequences{};

    for (int i = 0; i < levelSizeX; i++) {
        for (int j = 0; j < levelSizeY; j++) {
            bool hasTextLeft = i != 0 and isAnyTextBlock(blockLevel[i - 1][j]);
            bool hasTextUp = j != 0 and isAnyTextBlock(blockLevel[i][j - 1]);
            bool hasText = isAnyTextBlock(blockLevel[i][j]);

            if (not hasTextUp and hasText) {
                auto seqDown = getTextSequences(blockLevel[i][j],
                                                getCellsInDirection(MoveDirection::DOWN, Location(i, j)));

                textSequences.splice(textSequences.end(), seqDown);
            }

            if (not hasTextLeft and hasText) {
                auto seqRight = getTextSequences(blockLevel[i][j],
                                                 getCellsInDirection(MoveDirection::RIGHT, Location(i, j)));

                textSequences.splice(textSequences.end(), seqRight);
            }
        }
    }

    return textSequences;
}

BlockMap Level::toBlockMap() const {
    BlockMap blockMap;

    for (const auto &cellVec: blockLevel) {
        for (const Cell &c: cellVec) {
            for (Block *b: c) {
                std::string blockName = b->getName();
                Location blockLocation = b->getLocation();

                if (!blockMap.contains(blockName)) {
                    blockMap[blockName] = std::vector<std::pair<int, int> >();
                }

                blockMap[b->getName()].emplace_back(blockLocation.x, blockLocation.y);
            }
        }
    }

    return blockMap;
}

void Level::fromBlockMap(const BlockMap &blockMap) {
    blockLevel = std::vector<std::vector<Cell> >(levelSizeX, std::vector<Cell>(levelSizeY));

    for (const auto &keyValPair: blockMap) {
        std::string blockName = keyValPair.first;

        for (const auto &pair: keyValPair.second) {
            Block *newBlock = BlockFactory::produceBlock(blockName, {pair.first, pair.second});
            blockLevel[pair.first][pair.second].push_back(newBlock);
        }
    }
}

std::vector<Cell> Level::getCellsInDirection(MoveDirection direction, Location startingFrom) const {
    std::vector<Cell> cells;

    switch (direction) {
        case MoveDirection::UP:
            for (int i = startingFrom.y - 1; 0 <= i; --i) {
                cells.push_back(blockLevel[startingFrom.x][i]);
            }
            break;

        case MoveDirection::DOWN:
            cells = std::vector<Cell>(blockLevel[startingFrom.x].begin() + startingFrom.y + 1,
                                      blockLevel[startingFrom.x].end());
            break;

        case MoveDirection::LEFT:
            for (int i = startingFrom.x - 1; 0 <= i; --i) {
                cells.push_back(blockLevel[i][startingFrom.y]);
            }
            break;

        case MoveDirection::RIGHT:
            for (int i = startingFrom.x + 1; i < levelSizeX; ++i) {
                cells.push_back(blockLevel[i][startingFrom.y]);
            }
            break;

        case MoveDirection::STILL:
            cells = std::vector<Cell>();
    }

    return cells;
}

std::list<std::list<TextBlock *> > Level::getTextSequences(const Cell &currentCell,
                                                           const std::vector<Cell> &remainingCells) const {
    if (remainingCells.empty() or !isAnyTextBlock(currentCell)) return std::list<std::list<TextBlock *> >{{}};

    std::list<std::list<TextBlock *> > sequences{};

    Cell nextCell = remainingCells[0];
    std::vector<Cell> nextRemainingCells = std::vector<Cell>(remainingCells.begin() + 1, remainingCells.end());

    std::list<std::list<TextBlock *> > followingSubsequences = getTextSequences(nextCell, nextRemainingCells);

    for (Block *block: currentCell) {
        if (TextBlock *textBlock = dynamic_cast<TextBlock *>(block)) {
            std::list<std::list<TextBlock *> > subsCopy;
            for (const std::list<TextBlock *> &sub: followingSubsequences) {
                subsCopy.emplace_back(sub.begin(), sub.end()); // Copies each inner list
            }

            for (std::list<TextBlock *> &sub: subsCopy) {
                sub.push_front(textBlock);
            }

            sequences.splice(sequences.end(), subsCopy);
        }
    }

    return sequences;
}

bool Level::canMove(Block *block, const std::vector<Cell> &cellsInDirection) {
    if (cellsInDirection.empty()) {
        return false;
    } else {
        Cell nextCell = cellsInDirection[0];

        bool isAnyPushable = false;
        for (const Block *b: nextCell) {
            if (b->getBlockConcept()->stops(block)) return false;
            if (b->getBlockConcept()->isPushedBy(block)) isAnyPushable = true;
        }

        if (isAnyPushable) return canMove(
            block, std::vector<Cell>(cellsInDirection.begin() + 1, cellsInDirection.end()));
        else return true;
    }
}

void Level::moveWithCollaterals(Block *block, MoveDirection direction, std::vector<Cell> cellsInDirection) {
    block->move(direction);

    bool anyMoved = true;
    for (Cell &cell: cellsInDirection) {
        anyMoved = false;

        for (Block *b: cell) {
            if (b->getBlockConcept()->isPushedBy(block)) {
                b->move(direction);
                anyMoved = true;
            }
        }

        if (not anyMoved) break;
    }
}

bool Level::isAnyTextBlock(const Cell &cell) {
    for (Block *b: cell) {
        if (dynamic_cast<TextBlock *>(b)) return true;
    }

    return false;
}

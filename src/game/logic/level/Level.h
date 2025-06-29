//
// Created by Eneko on 23/03/2025.
//

#ifndef LEVEL_H
#define LEVEL_H
#include <list>
#include <map>
#include <string>
#include <vector>

#include "game/logic/level/block/TextBlock.h"
#include "game/logic/level/block/Block.h"


typedef std::vector<Block *> Cell;
typedef std::map<std::string, std::vector<std::pair<int, int> > > BlockMap;

class Level {
public:
    explicit Level(int levelSizeX, int levelSizeY, const BlockMap &blockMap);

    ~Level();

    void refresh();

    void tryMoveAll(MoveDirection direction);

    void tryMove(MoveDirection direction, Location pos);

    bool tryWinAll();

    bool tryWin(Location pos);

    void tryExecuteAll();

    void tryExecute(Location pos);

    [[nodiscard]] std::list<std::list<TextBlock *> > getTextSequences() const;

    [[nodiscard]] BlockMap toBlockMap() const;

private:
    int levelSizeX, levelSizeY;
    std::vector<std::vector<Cell> > blockLevel;

    void fromBlockMap(const BlockMap &blockMap);

    std::vector<Cell> getCellsInDirection(MoveDirection direction, Location startingFrom) const;

    std::list<std::list<TextBlock *> > getTextSequences(const Cell &currentCell,
                                                        const std::vector<Cell> &remainingCells) const;

    static bool canMove(Block *block, const std::vector<Cell> &cellsInDirection);

    static void moveWithCollaterals(Block *block, MoveDirection direction, std::vector<Cell> cellsInDirection);

    static bool isAnyTextBlock(const Cell &cell);
};


#endif //LEVEL_H

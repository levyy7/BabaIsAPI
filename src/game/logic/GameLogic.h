//
// Created by Eneko on 23/03/2025.
//

#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include "game/engine/LevelLoader.h"
#include "game/logic/level/Level.h"
#include "game/logic/level/block/Block.h"
#include "game/logic/rule/Rule.h"


class GameLogic {
public:
    GameLogic() = default;

    GameLogic(int levelSizeX, int levelSizeY, const BlockMap &blockMap);

    [[nodiscard]] BlockMap getLevelMap() const;

    [[nodiscard]] std::map<std::string, std::vector<std::map<std::string, std::string> > > getRules() const;

    [[nodiscard]] bool levelCompleted() const;

    void loadLevel(int levelSizeX, int levelSizeY, const BlockMap &blockMap);

    void move(MoveDirection direction);

private:
    Level *level;
    std::vector<Rule *> rules;
    bool winconFullfilled;

    void movePhase(MoveDirection direction);

    void rulePhase();

    void actionPhase();
};


#endif //GAMELOGIC_H

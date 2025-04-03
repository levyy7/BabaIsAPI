//
// Created by Eneko on 21/03/2025.
//

#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <vector>

class BlockConcept;

struct Location {
    int x, y;

    Location(int x, int y) : x(x), y(y) {
    }
};

enum MoveDirection {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STILL
};

class Block {
public:
    explicit Block(const std::string &name, BlockConcept *blockConcept);

    explicit Block(const std::string &name, const Location &location, BlockConcept *blockConcept);

    virtual ~Block();


    [[nodiscard]] std::string getName() const;

    [[nodiscard]] Location getLocation() const;

    [[nodiscard]] BlockConcept *getBlockConcept() const;

    Location move(MoveDirection moveDirection);

    Location move(const Location &moveTo);

protected:
    std::string name;
    Location location;
    BlockConcept *blockConcept;

private:
};


#endif //BLOCK_H

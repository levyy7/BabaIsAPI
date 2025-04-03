//
// Created by Eneko on 30/03/2025.
//

#ifndef COMMAND_H
#define COMMAND_H

enum class CommandType {
    LEFT = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    STILL = 4,
    RESTART = 5,
    NEXT,
    PREVIOUS,
    BACK = 6,
    EXIT = 7,
    STATUS = 8,
};

class Command {
public:
    explicit Command(CommandType type);

    [[nodiscard]] CommandType getCommandType() const;

private:
    CommandType type;
};


#endif //COMMAND_H

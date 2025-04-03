//
// Created by Eneko on 30/03/2025.
//

#include "Command.h"

Command::Command(CommandType type) {
    this->type = type;
}

CommandType Command::getCommandType() const {
    return type;
}

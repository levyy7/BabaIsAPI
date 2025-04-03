//
// Created by Eneko on 08/03/2025.
//
module;

#include <iostream>
#include <optional>
#include "../../../api/command/Command.h"

export module EventManager;


export class EventManager {
public:
    virtual std::optional<std::shared_ptr<Command> > pollCommand() = 0;
};

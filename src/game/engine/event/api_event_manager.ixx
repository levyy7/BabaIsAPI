//
// Created by Eneko on 30/03/2025.
//
module;

#include <memory>
#include <optional>
#include "../../../api/command/CommandQueue.h"

export module ApiEventManager;

import EventManager;


export class ApiEventManager : public EventManager {
public:
    ApiEventManager() = default;

    explicit ApiEventManager(CommandQueue *commandQueue) {
        this->commandQueue = commandQueue;
    }

    std::optional<std::shared_ptr<Command> > pollCommand() override {
        if (not commandQueue->empty())
            return commandQueue->pop();

        return {};
    }

private:
    CommandQueue *commandQueue;
};

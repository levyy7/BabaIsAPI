//
// Created by levy on 6/28/25.
//

#include "ApiEventManager.h"

ApiEventManager::ApiEventManager(CommandQueue *commandQueue) {
    this->commandQueue = commandQueue;
}

std::optional<std::shared_ptr<Command> > ApiEventManager::pollCommand() {
    if (not commandQueue->empty())
        return commandQueue->pop();

    return {};
}

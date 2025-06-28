//
// Created by levy on 6/28/25.
//

#ifndef APIEVENTMANAGER_H
#define APIEVENTMANAGER_H

#include <memory>
#include <optional>
#include "EventManager.h"
#include "../../../api/command/CommandQueue.h"

class ApiEventManager : public EventManager {
public:
    ApiEventManager() = default;

    explicit ApiEventManager(CommandQueue *commandQueue);

    std::optional<std::shared_ptr<Command> > pollCommand() override;

private:
    CommandQueue *commandQueue;
};



#endif //APIEVENTMANAGER_H

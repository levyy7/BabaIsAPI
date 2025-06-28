//
// Created by levy on 6/28/25.
//

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <memory>
#include <optional>
#include "../../../api/command/Command.h"

class EventManager {
public:
    virtual std::optional<std::shared_ptr<Command> > pollCommand() = 0;
};



#endif //EVENTMANAGER_H

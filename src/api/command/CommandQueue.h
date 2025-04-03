//
// Created by Eneko on 30/03/2025.
//

#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H
#include <condition_variable>
#include <queue>

#include "Command.h"


class CommandQueue {
public:
    CommandQueue() = default;

    void push(std::shared_ptr<Command> cmd);

    [[nodiscard]] std::shared_ptr<Command> pop();

    [[nodiscard]] bool empty();

private:
    std::queue<std::shared_ptr<Command> > queue_;
    std::mutex mutex_;
    //std::condition_variable cv_;
};


#endif //COMMANDQUEUE_H

//
// Created by Eneko on 30/03/2025.
//

#include "CommandQueue.h"

void CommandQueue::push(std::shared_ptr<Command> cmd) { {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(cmd);
    }
    //cv_.notify_one();
}

std::shared_ptr<Command> CommandQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex_);
    //cv_.wait(lock, [&]{ return !queue_.empty(); });
    std::shared_ptr<Command> cmd = std::move(queue_.front());
    queue_.pop();
    return cmd;
}

bool CommandQueue::empty() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }
}

//
// Created by Eneko on 31/03/2025.
//

#include "StatusCommand.h"

std::shared_ptr<StatusDTO> StatusCommand::getStatus() {
    std::unique_lock<std::mutex> lock(mutex_);
    // Wait until status is ready
    cv_.wait(lock, [this] { return status_ready_; });
    return status_;
}

void StatusCommand::setStatus(std::shared_ptr<StatusDTO> status) { {
        std::lock_guard<std::mutex> lock(mutex_);
        if (status_ready_) {
            throw std::runtime_error("Status has already been set.");
        }
        status_ = status;
        status_ready_ = true;
    }
    // Notify one waiting thread
    cv_.notify_one();
}

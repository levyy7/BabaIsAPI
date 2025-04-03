//
// Created by Eneko on 31/03/2025.
//

#ifndef STATUSCOMMAND_H
#define STATUSCOMMAND_H
#include "Command.h"
#include "../dto/StatusDTO.h"


class StatusCommand : public Command {
public:
    explicit StatusCommand(CommandType type)
        : Command(type) {
    }

    std::shared_ptr<StatusDTO> getStatus();

    void setStatus(std::shared_ptr<StatusDTO> status);

private:
    std::shared_ptr<StatusDTO> status_;
    mutable std::mutex mutex_;
    std::condition_variable cv_;
    bool status_ready_ = false;
};


#endif //STATUSCOMMAND_H

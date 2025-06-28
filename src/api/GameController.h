//
// Created by Eneko on 30/03/2025.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <crow.h>

#include "command/CommandQueue.h"

class GameController {
public:
    GameController(CommandQueue *commandQueue);

    void runServer(unsigned short port = 8000);

private:
    crow::SimpleApp app;
    CommandQueue *commandQueue;

    void addEndpoints();
};


#endif //GAMECONTROLLER_H

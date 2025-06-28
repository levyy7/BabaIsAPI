//
// Created by Eneko on 30/03/2025.
//

#include "GameController.h"

#include "command/StatusCommand.h"

GameController::GameController(CommandQueue *commandQueue) {
    addEndpoints();
    this->commandQueue = commandQueue;
}

void GameController::runServer(unsigned short port) {
    std::thread([this, port]() {
        app.port(port).run();
    }).detach();

    std::cout << "Crow API service started on port " << port << std::endl;
}

void GameController::addEndpoints() {
    CROW_ROUTE(app, "/hello")([]() {
        return "Hello from Crow API!";
    });
    CROW_ROUTE(app, "/status")([this]() {
        std::shared_ptr<StatusCommand> statusCommand = std::make_shared<StatusCommand>(CommandType::STATUS);
        commandQueue->push(statusCommand);

        std::shared_ptr<StatusDTO> status = statusCommand->getStatus();

        return status->toJSON();
    });
    CROW_ROUTE(app, "/move/<string>").methods("GET"_method, "POST"_method)
    ([this](const crow::request &req, crow::response &res, const std::string &direction) {
        std::shared_ptr<Command> cmd;

        if (direction == "up") {
            cmd = std::make_shared<Command>(CommandType::UP);
        } else if (direction == "down") {
            cmd = std::make_shared<Command>(CommandType::DOWN);
        } else if (direction == "left") {
            cmd = std::make_shared<Command>(CommandType::LEFT);
        } else if (direction == "right") {
            cmd = std::make_shared<Command>(CommandType::RIGHT);
        } else if (direction == "still") {
            cmd = std::make_shared<Command>(CommandType::STILL);
        } else {
            cmd = nullptr; // Handle unknown direction
        }

        if (cmd) {
            commandQueue->push(cmd);
            res.code = 200;
            res.body = "Moved " + direction;
        } else {
            // Respond with an error message for invalid directions
            res.code = 400;
            res.body = "Invalid direction: " + direction +
                       "\n Valid directions are: ['up', 'down', 'left', 'right', 'still']";
        }

        res.end();
    });
    CROW_ROUTE(app, "/level/<string>").methods("GET"_method, "POST"_method)
    ([this](const crow::request &req, crow::response &res, const std::string &action) {
        std::shared_ptr<Command> cmd;

        if (action == "restart") {
            cmd = std::make_shared<Command>(CommandType::RESTART);
        } else if (action == "next") {
            cmd = std::make_shared<Command>(CommandType::NEXT);
        } else {
            cmd = nullptr; // Handle unknown action
        }

        if (cmd) {
            commandQueue->push(cmd);
            res.code = 200;
            res.body = "Action: '" + action + "' executed";
        } else {
            // Respond with an error message for invalid directions
            res.code = 400;
            res.body = "Invalid actions: " + action + "\n Valid directions are: ['restart', 'next']";
        }

        res.end();
    });
    CROW_CATCHALL_ROUTE(app)
    ([]() {
        return "Route not found";
    });
}

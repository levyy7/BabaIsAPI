//
// Created by Eneko on 08/03/2025.
//
module;

#include <iostream>
#include <optional>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../../../api/command/CommandQueue.h"

export module KeyboardEventManager;

export import EventManager;


export class KeyboardEventManager : public EventManager {
public:
    KeyboardEventManager() = default;

    explicit KeyboardEventManager(std::shared_ptr<sf::RenderWindow> window) {
        this->window = window;
    }

    std::optional<std::shared_ptr<Command> > pollCommand() override {
        if (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                return std::make_shared<Command>(CommandType::EXIT);

                // Handle key pressed events
            else if (const sf::Event::KeyPressed *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (std::optional<CommandType> type = pollKeyEvent(keyPressed))
                    return std::make_shared<Command>(type.value());
            }
        }

        return {};
    }

    void setWindow(std::shared_ptr<sf::RenderWindow> window) {
        this->window = std::move(window);
    }

private:
    std::shared_ptr<sf::RenderWindow> window;

    std::optional<CommandType> pollKeyEvent(const sf::Event::KeyPressed *keyPressed) {
        switch (keyPressed->scancode) {
            case sf::Keyboard::Scancode::A:
            case sf::Keyboard::Scancode::Left:
                return CommandType::LEFT;
            case sf::Keyboard::Scancode::W:
            case sf::Keyboard::Scancode::Up:
                return CommandType::UP;
            case sf::Keyboard::Scancode::D:
            case sf::Keyboard::Scancode::Right:
                return CommandType::RIGHT;
            case sf::Keyboard::Scancode::S:
            case sf::Keyboard::Scancode::Down:
                return CommandType::DOWN;
            case sf::Keyboard::Scancode::Space:
                return CommandType::STILL;
            case sf::Keyboard::Scancode::R:
                return CommandType::RESTART;
            case sf::Keyboard::Scancode::N:
                return CommandType::NEXT;
            case sf::Keyboard::Scancode::P:
                return CommandType::PREVIOUS;
            case sf::Keyboard::Scancode::Q:
                return CommandType::BACK;
            case sf::Keyboard::Scancode::Escape:
                return CommandType::EXIT;
            default:
                return {};
        }
    }
};

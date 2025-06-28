//
// Created by levy on 6/28/25.
//

#ifndef KEYBOARDEVENTMANAGER_H
#define KEYBOARDEVENTMANAGER_H

#include <optional>
#include <memory>
#include <SFML/Graphics.hpp>
#include "EventManager.h"
#include "../../../api/command/CommandQueue.h"

class KeyboardEventManager : public EventManager {
public:
    KeyboardEventManager() = default;

    explicit KeyboardEventManager(std::shared_ptr<sf::RenderWindow> window);

    std::optional<std::shared_ptr<Command> > pollCommand() override;

    void setWindow(std::shared_ptr<sf::RenderWindow> window);

private:
    std::shared_ptr<sf::RenderWindow> window;

    std::optional<CommandType> pollKeyEvent(const sf::Event::KeyPressed *keyPressed);
};



#endif //KEYBOARDEVENTMANAGER_H

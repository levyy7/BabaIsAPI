//
// Created by Eneko on 27/03/2025.
//

#ifndef PROPERTYCONTROLLER_H
#define PROPERTYCONTROLLER_H
#include <map>
#include <string>

#include "DefeatProperty.h"
#include "HotProperty.h"
#include "Property.h"
#include "PushProperty.h"
#include "ShutProperty.h"
#include "SinkProperty.h"
#include "StopProperty.h"
#include "WinProperty.h"
#include "YouProperty.h"


class PropertyController {
public:
    static Property *getProperty(std::string propertyName);

    static std::map<std::string, Property *> getPropertyMap();

private:
    inline static std::map<std::string, Property *> PROPERTY_MAP = {
        {"STOP", new StopProperty},
        {"PUSH", new PushProperty},
        {"WIN", new WinProperty},
        {"YOU", new YouProperty},
        {"DEFEAT", new DefeatProperty},
        {"SHUT", new ShutProperty},
        {"OPEN", new Property("OPEN")},
        {"HOT", new HotProperty},
        {"MELT", new Property("MELT")},
        {"SINK", new SinkProperty},
    };
};


#endif //PROPERTYCONTROLLER_H

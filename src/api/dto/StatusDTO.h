//
// Created by Eneko on 30/03/2025.
//

#ifndef STATUSDTO_H
#define STATUSDTO_H
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <Crow.h>

class StatusDTO {
public:
    int levelId;
    std::string levelName;
    std::pair<int, int> levelSize;
    bool levelCompleted;
    std::map<std::string, std::vector<std::pair<int, int> > > blocks;
    std::map<std::string, std::vector<std::map<std::string, std::string> > > rules;


    StatusDTO() = default;

    StatusDTO(const int level_id, const std::string &level_name, const std::pair<int, int> &level_size,
              const bool levelCompleted, const std::map<std::string, std::vector<std::pair<int, int> > > &blocks,
              const std::map<std::string, std::vector<std::map<std::string, std::string> > > &rules)
        : levelId(level_id),
          levelName(level_name),
          levelSize(level_size),
          levelCompleted(levelCompleted),
          blocks(blocks),
          rules(rules) {
    }

    [[nodiscard]] crow::json::wvalue toJSON() const;
};


#endif //STATUSDTO_H

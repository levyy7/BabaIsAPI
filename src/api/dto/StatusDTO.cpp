//
// Created by Eneko on 30/03/2025.
//

#include "StatusDTO.h"

crow::json::wvalue StatusDTO::toJSON() const {
    crow::json::wvalue j;

    // Serialize basic fields.
    j["levelId"] = levelId;
    j["levelName"] = levelName;

    // Serialize levelSize (pair<int, int>).
    {
        std::vector<int> vec(2);
        vec[0] = levelSize.first;
        vec[1] = levelSize.second;
        j["levelSize"] = vec;
    }

    j["levelCompleted"] = levelCompleted;

    // Serialize blocks (map<string, vector<pair<int, int>>>).
    {
        crow::json::wvalue jBlocks;
        for (const auto &kv: blocks) {
            // Use a vector to hold the JSON items.
            std::vector<crow::json::wvalue> vec;
            for (const auto &p: kv.second) {
                crow::json::wvalue item;
                item["x"] = p.first;
                item["y"] = p.second;
                vec.push_back(std::move(item));
            }
            jBlocks[kv.first] = std::move(vec);
        }
        j["blocks"] = std::move(jBlocks);
    }

    // Serialize rules (map<string, vector<map<string, string>>>).
    {
        crow::json::wvalue jRules;
        for (const auto &kv: rules) {
            std::vector<crow::json::wvalue> vec;
            for (const auto &ruleMap: kv.second) {
                crow::json::wvalue rule;
                for (const auto &pair: ruleMap) {
                    rule[pair.first] = pair.second;
                }
                vec.push_back(std::move(rule));
            }
            jRules[kv.first] = std::move(vec);
        }
        j["rules"] = std::move(jRules);
    }

    return j;
}

//
// Created by Eneko on 22/03/2025.
//

#ifndef BLOCKCONCEPT_H
#define BLOCKCONCEPT_H
#include <vector>
#include <string>
#include <set>
#include <unordered_set>

class Block;
class NounBlock;
class Property;


class BlockConcept {
public:
    explicit BlockConcept(std::string name);

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::unordered_set<Block *> getBlockRepresentations() const;

    [[nodiscard]] std::unordered_set<NounBlock *> getBlockReferences() const;

    [[nodiscard]] std::unordered_set<Property *> getBlockProperties() const;

    [[nodiscard]] bool isPushedBy(const Block *block) const;

    [[nodiscard]] bool stops(const Block *block) const;

    [[nodiscard]] bool isMoveable() const;

    [[nodiscard]] bool isWin(const std::vector<Block *> &blocksInCell) const;

    [[nodiscard]] bool hasProperty(const std::string &name) const;

    [[nodiscard]] std::set<Block *> getBlocksToDelete(Block *const calledBy,
                                                      const std::vector<Block *> &blocksInCell) const;

    void addPhysicalRepresentation(Block *block);

    void removePhysicalRepresentation(Block *block);

    void addPhysicalReference(NounBlock *noun);

    void removePhysicalReference(NounBlock *noun);

    void addProperty(Property *property);

    void clearProperties();

    static std::set<Block *> unionSets(const std::set<Block *> &set1, const std::set<Block *> &set2);

    bool operator==(const BlockConcept &other) const {
        return name == other.name;
    }

private:
    std::string name;
    std::unordered_set<Block *> physicalRepresentations;
    std::unordered_set<NounBlock *> physicalReferences;
    std::unordered_set<Property *> properties;
};


#endif //BLOCKCONCEPT_H

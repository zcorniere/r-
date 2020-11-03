#include "ComponentStorage.hpp"
#include <iostream>

static bool test_component_join()
{
    std::cout << "component_join tests...";
    std::map<unsigned, char> chars;
    std::map<unsigned, short> shorts;

    chars.emplace(0, 'z'); chars.emplace(1, 'a'); chars.emplace(3, 'b');
    chars.emplace(4, 'z'); chars.emplace(5, 'c'); chars.emplace(6, 'd');
    shorts.emplace(1, 1); shorts.emplace(2, -1); shorts.emplace(3, 2);
    shorts.emplace(5, 3); shorts.emplace(6, 4); shorts.emplace(7, -1);

    std::map<unsigned, std::tuple<char&, short&>> result = join_components(chars, shorts);
    std::map<unsigned, std::tuple<char, short>> model;

    model.emplace(1, std::tuple<char, short>{'a', 1}); model.emplace(3, std::tuple<char, short>{'b', 2});
    model.emplace(5, std::tuple<char, short>{'c', 3}); model.emplace(6, std::tuple<char, short>{'d', 4});

    if (result.size() != 4) {
        std::cerr << "Wrong result size, expected 4, got " << result.size() << std::endl;
        return false;
    }

    for (const auto& [key, value] : result) {
        const auto& [ra, rb] = value;
        const auto& [ma, mb] = model[key];

        if (ra != ma || rb != mb) {
            std::cerr << "Wrong content, at" << key;
            std::cerr << " expected {" << ma << ", " << mb;
            std::cerr << "} got {" << ra << ", " << rb << std::endl;
            return 1;
        }
    }

    std::cout << "Done !" << std::endl;
    return true;
}

class FiveHandler {
    public:
    int giveMeFive(void)
    {
        return 5;
    }
};

int main(void)
{
    std::cout << "ComponentStorage tests...";

    ComponentStorage storage;
    FiveHandler handler;
    FiveHandler handler2;

    storage.registerComponent<FiveHandler>();
    storage.registerComponent<int>();

    int id = storage.buildEntity()
    .withComponent(handler)
    .build();
    if (id != 0) {
        std::cerr << "Invalid entity id, expected 0, found " << id << std::endl;
        return 1;
    }

    id = storage.buildEntity()
    .withComponent(5)
    .build();
    if (id != 1) {
        std::cerr << "Invalid entity id, expected 1, found " << id << std::endl;
        return 1;
    }

    id = storage.buildEntity()
    .withComponent(handler2)
    .withComponent(10)
    .build();
    if (id != 2) {
        std::cerr << "Invalid entity id, expected 2, found " << id << std::endl;
        return 1;
    }

    std::map<unsigned, int> ints = storage.getComponents<int>();

    if (ints.size() != 2) {
        std::cerr << "Invalid int components number, expected 2, found " << ints.size() << std::endl;
        return 1;
    }
    if (ints[1] != 5 || ints[2] != 10) {
        std::cerr << "Ints components aren't correctly stored" << std::endl;
        return 1;
    }

    std::cout << "Done !" << std::endl;

    if (!test_component_join())
        return 1;
}

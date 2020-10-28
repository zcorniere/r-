#include "ComponentStorage.hpp"
#include <iostream>

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

    std::unordered_map<unsigned, int> ints = storage.getComponents<int>();

    if (ints.size() != 2) {
        std::cerr << "Invalid int components number, expected 2, found " << ints.size() << std::endl;
        return 1;
    }
    if (ints[1] != 5 || ints[2] != 10) {
        std::cerr << "Ints components aren't correctly stored" << std::endl;
        return 1;
    }

    std::cout << "Done !" << std::endl;
}

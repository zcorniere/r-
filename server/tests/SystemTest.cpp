#include "System.hpp"
#include "SystemStorage.hpp"
#include "Game.hpp"

class Id
{
  public:
    Id(int id) : id(id){};
    int id;
};

void s1_f(Id id, int i)
{
    std::cerr << "Id:" << id.id << " i:" << i << std::endl;
}

int main(void)
{
    Game game("game");

    game.componentStorage.registerComponent<Id>();
    game.componentStorage.registerComponent<int>();

    game.componentStorage.buildEntity().withComponent(Id(42)).withComponent(666).build();
    game.componentStorage.buildEntity().withComponent(Id(69)).build();

    System s1(s1_f);


    System s2 = [](Id id) { std::cerr << "Only id: " << id.id << std::endl; };

    SystemStorage systems;

    systems.addSystem(s1);
    systems.addSystem(s2);
    systems.runTick(game.componentStorage);
    // System s3 = [](){};
    // System s3 = 3;
    return 0;
}

#include "System.hpp"
#include "SystemStorage.hpp"
#include "ComponentStorage.hpp"

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
    ComponentStorage storage;

    storage.registerComponent<Id>();
    storage.registerComponent<int>();

    storage.buildEntity().withComponent(Id(42)).withComponent(666).build();
    storage.buildEntity().withComponent(Id(69)).build();

    System s1(s1_f);


    System s2 = [](Id id) { std::cerr << "Only id: " << id.id << std::endl; };

    SystemStorage systems;

    systems.addSystem(s1);
    systems.addSystem(s2);
    systems.runTick(storage);
    // System s3 = [](){};
    // System s3 = 3;
    return 0;
}

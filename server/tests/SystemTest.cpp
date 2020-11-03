#include "System.hpp"
#include "ComponentStorage.hpp"

class Id
{
  public:
    Id(int id) : id(id){};
    int id;
};

int main(void)
{
    ComponentStorage storage;

    storage.registerComponent<Id>();
    storage.registerComponent<int>();

    storage.buildEntity().withComponent(Id(42)).withComponent(666).build();
    storage.buildEntity().withComponent(Id(69)).build();

    System s1(std::function([](Id id, int i) {
        std::cerr << "Id:" << id.id << " i:" << i << std::endl;
    }));

    s1.call(storage);

    System s2(std::function(
        [](Id id) { std::cerr << "Only id: " << id.id << std::endl; }));

    s2.call(storage);
    return 0;
}

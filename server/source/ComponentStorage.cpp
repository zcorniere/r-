#include "ComponentStorage.hpp"

// ComponentStorage methods

ComponentStorage::ComponentStorage() : m_entityCount(0)
{}

ComponentStorage::~ComponentStorage()
{}

ComponentStorage::EntityBuilder ComponentStorage::buildEntity()
{
    EntityBuilder builder(*this);

    return builder;
}

void ComponentStorage::destroyEntity(unsigned id)
{
    m_dead[id] = true;
}

unsigned ComponentStorage::getNextFreeId() const
{
    for (const auto& [id, isDead] : m_dead) {
        if (isDead == true)
            return id;
    }
    return m_entityCount;
}

// EntityBuilder methods

ComponentStorage::EntityBuilder::EntityBuilder(ComponentStorage &dest)
: m_id(dest.getNextFreeId()), m_dest(dest)
{}

ComponentStorage::EntityBuilder::EntityBuilder(ComponentStorage::EntityBuilder &other)
: m_id(other.m_id), m_dest(other.m_dest)
{
    std::cout << "BUILDER COPIED, CARE\n";
}

unsigned ComponentStorage::EntityBuilder::build()
{
    m_dest.m_entityCount++;
    m_dest.m_dead[m_id] = false;

    return m_id;
}

unsigned ComponentStorage::EntityBuilder::buildAsOrphan()
{
    return build();
}


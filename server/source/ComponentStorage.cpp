#include "ComponentStorage.hpp"

// ComponentStorage methods

ComponentStorage::ComponentStorage()
{}

ComponentStorage::~ComponentStorage()
{}

ComponentStorage::EntityBuilder ComponentStorage::buildEntity()
{
    EntityBuilder builder(*this);

    return builder;
}

unsigned ComponentStorage::getNextFreeId() const
{
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

    return m_id;
}

unsigned ComponentStorage::EntityBuilder::buildAsOrphan()
{
    return build();
}


#ifndef COMPONENT_STORAGE_HPP
#define COMPONENT_STORAGE_HPP

#include "Snitch.hpp"
#include "StateMachine.hpp"

#include <any>
#include <map>
#include <memory>
#include <string>
#include <optional>
#include <tuple>
#include <functional>
#include <typeindex>
#include <vector>
#include <stdexcept>
#include <variant>
#include <type_traits>
#include <boost/type_index.hpp>

class Enemy;

class ComponentStorage {
class EntityBuilder;
private:
    std::unordered_map<std::type_index, std::any> m_storage;
    unsigned m_entityCount;
    std::map<unsigned, bool> m_dead;
    StateMachine &m_stateMachine;
    std::map<unsigned, short> m_parentStates;

public:
    ComponentStorage(StateMachine &stateMachine);

    template<typename T>
    void registerComponent()
    {
        std::map<unsigned, T> new_row;

        m_storage.emplace(typeid(T), std::move(new_row));
    }

    template<typename T>
    std::map<unsigned, T> &getComponents()
    {
        for (auto &[storage_type, storage] : m_storage) {
            if (storage_type == typeid(T)) {
                try {
                    auto &output =
                        std::any_cast<std::map<unsigned, T> &>(storage);
                    clearZombies(output);
                    return output;
                } catch (std::bad_any_cast const &) {
                    break;
                }
            }
        }

        Snitch::warn() << "Trying to find unregistered components '"
                       << boost::typeindex::type_id_with_cvr<T>().pretty_name()
                       << "'" << Snitch::endl;
        throw std::runtime_error("Couldn't read given storage");
    }

    template<typename First, typename... Rest>
    std::map<unsigned int, std::tuple<First&, Rest&...>> join_components
    (std::map<unsigned int, First>& first, std::map<unsigned int, Rest>&... rest)
    {
        std::map<unsigned int, std::tuple<First&, Rest&...>> result;
            for (auto& [key, value]: first)
                if (
                    ((rest.find(key) != rest.end()) && ...)
                    && (
                        !(m_stateMachine.getCurrentState())
                        || (*m_stateMachine.getCurrentState()).get().getId() == m_parentStates.at(key)
                        || (*m_stateMachine.getCurrentState()).get().getId() == -1
                    )
                )
                    result.emplace(key, std::tuple<First&, Rest&...>{value, rest.at(key)...});
        return result;
    }

    EntityBuilder buildEntity();
    void destroyEntity(unsigned id);
    ~ComponentStorage();

private:

    template<typename T>
    void storeComponent(T componenent, unsigned index)
    {
        for (auto &[storage_type, storage] : m_storage) {
            if (storage_type == typeid(T)) {
                std::map<unsigned, T> &map = std::any_cast<std::map<unsigned, T>&>(storage);
                map.emplace(index, componenent);
                return;
            }
        }
        Snitch::warn() << "Couldn't store unregistered component '"
                       << boost::typeindex::type_id_with_cvr<T>().pretty_name()
                       << "'" << Snitch::endl;
    }

    template<typename T>
    void clearZombies(std::map<unsigned, T>& components)
    {
        for (const auto&[id, isDead] : m_dead) {
            if (isDead && components.find(id) != components.end())
                components.erase(id);
        }
    }

    unsigned getNextFreeId() const;


private:

    friend EntityBuilder;
    friend Enemy;
    class EntityBuilder {
    private:
        unsigned m_id;
        ComponentStorage &m_dest;
    public:
        EntityBuilder(ComponentStorage &dest);
        EntityBuilder(EntityBuilder &other);
        template<typename T>
        EntityBuilder &withComponent(T component)
        {
            m_dest.storeComponent<std::decay_t<T>>(component, m_id);
            return *this;
        }
        template <typename... Variants>
        EntityBuilder &withComponent(std::variant<Variants...> component)
        {
            std::visit(
                [this](auto &&component) {
                    this->withComponent(component);
                },
                component);
            return *this;
        }
        template <typename Optional>
        EntityBuilder &withComponent(std::optional<Optional> component)
        {
            if (component) {
                this->withComponent(component.value());
            }
            return *this;
        }
        template <typename T>
        EntityBuilder &withBuilder(const T &bundle)
        {
            bundle.build(*this);
            return *this;
        }
        unsigned build();
        unsigned buildAsOrphan();
    };
};


#endif


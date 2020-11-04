#ifndef MODULES_HPP
#define MODULES_HPP

#include "components/Transform.hpp"
#include <vector>
#include <string>
#include <optional>

// General Module Interface

class IModule {
public:
    virtual void update() = 0;
    virtual ~IModule() = 0;
};

// Specific modules

class IDisplayModule : public IModule {
public:
    virtual void setAssetPath(const std::string &path) = 0;
    virtual void drawSprite(const std::string &name, Transform const &transform, unsigned tile_id) = 0;
};

class IInputModule : public IModule {
public:
    //enum Input {}
    //virtual std::vector<Input> getInputEvents() = 0;
    //TODO: Créer l'enum Input et l'implémenter ici
};

class IAudioModule : public IModule {
public:
    virtual void setAssetPath(const std::string &path) = 0;
    virtual void playSound(const std::string &name, float volume, float pitch) = 0;
};

class INetworkModule : public IModule {
public:
    virtual long initInstance(unsigned maxPlayers) = 0;
    //virtual std::optional<Instance> getInstance();
    //TODO: Créer la classe instance et l'implémenter ici (voir l'UML)'
};

#endif

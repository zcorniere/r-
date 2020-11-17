#include "SfmlAudioModule.hpp"
#include "Snitch.hpp"
#include <SFML/Audio.hpp>

SfmlAudioModule::SfmlAudioModule(const std::filesystem::path &asset_location)
    : m_asset_location(asset_location)
{
    std::clog << "loading audio from " << asset_location.string() << std::endl;
    for (auto &file : std::filesystem::directory_iterator(m_asset_location)) {
        std::clog << "path "<< file.path().string() << std::endl;
        if (file.path().extension() == ".ogg")
            this->loadSound(file);
    }
}

void SfmlAudioModule::update()
{
}

void SfmlAudioModule::playSound(const std::string &name, float volume,
                                float pitch, bool looping)
{
    if (!m_cached_assets.contains(name)) {
        Snitch::warn() << "Could not find sound " << name << Snitch::endl;
        return;
    }
    sf::Music &asset = m_cached_assets[name];

    asset.setVolume(volume * 100);
    asset.setPitch(pitch);
    asset.setLoop(looping);
    asset.stop();
    asset.play();
}
void SfmlAudioModule::stopSound(const std::string &name)
{
    if (m_cached_assets.contains(name))
        m_cached_assets[name].stop();
}

sf::Music &SfmlAudioModule::loadSound(const std::filesystem::path &asset_path)
{
    auto [value, success] = m_cached_assets.try_emplace(asset_path.stem());
    auto &[key, asset] = *value;

    if (!success) {
        return asset;
    }

    Snitch::info() << "Loading audio file " << asset_path.string() << Snitch::endl;
    if (!asset.openFromFile(asset_path)) {
        throw SfmlAudioError("could not load asset " + asset_path.string());
        // throw std::runtime_error("Could not load music " + asset_path.string());
    }
    return asset;
}

SfmlAudioError::SfmlAudioError(const std::string &error)
    : AudioError("SfmlAudioModule error: " + error)
{
}

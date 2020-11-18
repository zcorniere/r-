#include "components/Speaker.hpp"
#include "components/Destructible.hpp"
#include "components/WaveCannon.hpp"
#include "components/BackgroundMusic.hpp"
#include "Game.hpp"
#include <cstdlib>

void speaker_player(IAudioModule &module, Speaker &speaker)
{
    float factor = static_cast<float>(rand() % 200) / 100;
    float pitch_variation = speaker.variation * factor - speaker.variation;

    if (speaker.status == Speaker::Status::Starting) {
        module.playSound(speaker.asset, speaker.volume, 1 + pitch_variation);
        speaker.status = Speaker::Status::Playing;
    }
}

void death_speaker_player(IAudioModule &module, DeathSpeaker &speaker)
{
    float factor = static_cast<float>(rand() % 200) / 100;
    float pitch_variation = speaker.variation * factor - speaker.variation;

    if (speaker.status == Speaker::Status::Starting) {
        module.playSound(speaker.asset, speaker.volume, 1 + pitch_variation);
        speaker.status = Speaker::Status::Playing;
    }
}

void shoot_speaker_player(IAudioModule &module, ShootSpeaker &speaker)
{
    float factor = static_cast<float>(rand() % 200) / 100;
    float pitch_variation = speaker.variation * factor - speaker.variation;

    if (speaker.status == Speaker::Status::Starting) {
        module.playSound(speaker.asset, speaker.volume, 1 + pitch_variation);
        speaker.status = Speaker::Status::Playing;
    }
}

void death_speaker_activator(DeathSpeaker &speaker, const Destructible &destructible)
{
    if (speaker.status == Speaker::Status::Inactive
    && destructible.status == Destructible::Status::Dying)
        speaker.play();
}

void shoot_speaker_activator(ShootSpeaker &speaker, const WaveCannon &cannon)
{
    if (cannon.status == WaveCannon::Status::Firing)
        speaker.play();
}

void play_background_music(IAudioModule &audio, BackgroundMusic &music)
{
    music.counter++;
    if (music.counter > 20) {
        audio.playSound(music.name, music.volume, 1, true);
        music.counter = 0;
    }
}

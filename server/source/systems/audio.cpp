#include "components/Speaker.hpp"
#include "components/Destructible.hpp"
#include "Game.hpp"

void speaker_player(IAudioModule &module, Speaker &speaker)
{
    if (speaker.status == Speaker::Status::Starting) {
        module.playSound(speaker.asset);
        speaker.status = Speaker::Status::Playing;
    }
}

void death_speaker_player(IAudioModule &module, DeathSpeaker &speaker)
{
    if (speaker.status == Speaker::Status::Starting) {
        module.playSound(speaker.asset);
        speaker.status = Speaker::Status::Playing;
    }
}

void death_speaker_activator(DeathSpeaker &speaker, const Destructible &destructible)
{
    if (speaker.status == Speaker::Status::Inactive
    && destructible.status == Destructible::Status::Dying)
        speaker.play();
}

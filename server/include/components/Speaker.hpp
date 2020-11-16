#ifndef SPEAKER_HPP
#define SPEAKER_HPP

#include <string>

class Speaker {
public:
    enum class Status {
        Inactive,
        Starting,
        Playing,
    };
    std::string asset;
    Status status;
    float volume;
    float variation;
    Speaker(std::string _asset, float _volume = 1, float _variation = 0);
    void play();
};

class DeathSpeaker : public Speaker {
        using Speaker::Speaker;
};

class ShootSpeaker : public Speaker {
        using Speaker::Speaker;
};

#endif

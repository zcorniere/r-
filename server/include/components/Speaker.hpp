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
    Speaker(std::string _asset);
    void play();
};

class DeathSpeaker : public Speaker {
        using Speaker::Speaker;
};

#endif

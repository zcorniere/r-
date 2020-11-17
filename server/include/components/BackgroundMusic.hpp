#ifndef RTYPE_BACKGROUND_MUSIC_H_
#define RTYPE_BACKGROUND_MUSIC_H_

#include <string>

struct BackgroundMusic {
    std::string name;
    float volume;
    unsigned counter = 0;
};

#endif // RTYPE_BACKGROUND_MUSIC_H_

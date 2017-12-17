#ifndef SOUND_H
#define SOUND_H
#include "SFML/Audio.hpp"
using namespace sf;


class Sound
{
    public:
        Sound();
        virtual ~Sound();
        void play();
        void stop();

    protected:

    private:
        Music bgm;
};

#endif // SOUND_H

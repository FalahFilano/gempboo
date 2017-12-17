#ifndef SOUNDTETRIS_H
#define SOUNDTETRIS_H
#include <SFML/Audio.hpp>

using namespace sf;

class SoundTetris
{
    public:
        SoundTetris();
        virtual ~SoundTetris();

        bool open_music();
        void play_music();
        void stop_music();

        sf::SoundBuffer load;
        sf::Sound musics;

    protected:

    private:
};
#endif // SOUNDTETRIS_H

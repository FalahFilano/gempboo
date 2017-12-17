#define BGMSOUND_H
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class BGMSound
{
    public:
        BGMSound();
        virtual ~BGMSound();
        void play();
        void stop();

    protected:

    private:
        Music bgm;
};

#include "Sound.h"

Sound::Sound()
{
    if (!bgm.openFromFile("music/tetris.ogg"))
    return -1; // error

}

Sound::~Sound()
{
    //dtor
}
void Sound::play()
{
    bgm.play();
}

void Sound::stop()
{
    bgm.stop();
}

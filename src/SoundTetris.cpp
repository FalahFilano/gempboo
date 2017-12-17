#include "SoundTetris.h"

SoundTetris::SoundTetris()
{
    //ctor
}

SoundTetris::~SoundTetris()
{
    //dtor
}

bool SoundTetris::open_music()
{
    if(!load.loadFromFile("music\tetris.ogg"))
    {
        return -1;
    }
}

void SoundTetris::play_music()
{
    musics.play();
}

void SoundTetris::stop_music()
{
    musics.stop();
}

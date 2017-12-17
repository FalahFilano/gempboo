#include "BGMSound.h"

BGMSound::BGMSound()
{
    if (!bgm.openFromFile("music/tetris.ogg"))
    cout<<"error Opening Music"<<endl;
    else cout<<"Music Opened"<<endl;
}
BGMSound::~BGMSound()
{
    //dtor
}
void BGMSound::play()
{
    bgm.setLoop(true);
    bgm.play();
}

void BGMSound::stop()
{
    bgm.stop();
    cout<<"Music Stopped"<<endl;
}

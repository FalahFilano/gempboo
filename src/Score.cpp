#include "Score.h"

Score::Score()
{
    fontuse.loadFromFile("Geforce Bold.ttf");

    scoringtext.setFillColor(Color::White);
    scoringtext.setPosition(140, 510);
    scoringtext.setCharacterSize(24);
    scoringtext.setFont(fontuse);
}

Score::~Score()
{
    //dtor
}

void Score::update(int score)
{
    scorestring.str("");
	scorestring<<"Score : "<<score;
	scoringtext.setString(scorestring.str());
}

Text Score::draw()
{
    return scoringtext;
}

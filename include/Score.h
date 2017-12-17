#define SCORE_H
#include <SFML/Graphics.hpp>

class Score
{
    public:
        Score(int score);
        virtual ~Score();

    protected:

    private:
        int score;
};

#define SCORE_H
#include "SFML/Graphics.hpp"
#include <sstream>
using namespace sf;
using namespace std;


class Score
{
    public:
        Score();
        virtual ~Score();

        void update(int score);
        Text draw();

    protected:

    private:
        Font fontuse;
        Text scoringtext;

        ostringstream scorestring;
};

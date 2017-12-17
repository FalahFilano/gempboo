#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 2


class GameoverMenu
{
    public:
        GameoverMenu(float Width, float Height);
        ~GameoverMenu();

        void draw2(sf::RenderWindow &window);
        void MoveUp2();
        void MoveDown2();
        int GetPressedItem2() { return setPressedItem2; }

    protected:

    private:
    int setPressedItem2;
    sf::Font font;
    sf::Texture texture;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    sf::Text text;
    sf::Text text1;
    sf::Sprite imageSprite;
};

#endif // PAUSEMENU_H

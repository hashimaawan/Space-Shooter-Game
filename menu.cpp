#include "menu.h"

Menu::Menu(float width,float height)
{
    // if(!font.loadFromFile("Roboto.ttf"))
    // cout<<"No font\n";

    //Play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::White);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition(300,200);

    //Options
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::White);
    mainMenu[1].setString("Options");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition(300,300);

    //Instructions
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::White);
    mainMenu[2].setString("Instructions");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition(300,400);

    //Exit
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(Color::White);
    mainMenu[3].setString("Exit");
    mainMenu[3].setCharacterSize(70);
    mainMenu[3].setPosition(300,500);

    MenuSelected=-1;
}

Menu ::~Menu(){}


// Draw
void Menu:: draw(RenderWindow & window)
{
    for(int i=0;i<4;i++)
    {
        window.draw(mainMenu[i]);
    }

}
//Move Up
void Menu:: MoveUp()
{
    if(MenuSelected-1>=0)
    {
        mainMenu[MenuSelected].setFillColor(Color::White);

        MenuSelected--;
        if(MenuSelected== -1)
        {
            MenuSelected=2;
        }
        mainMenu[MenuSelected].setFillColor(Color::Blue);

    }
}

// Move Down
void Menu:: MoveDown()
{
    if(MenuSelected+1<= maxx)
    {
        mainMenu[MenuSelected].setFillColor(Color:: White);
        MenuSelected++;
        if(MenuSelected==4)
        {
            MenuSelected=0;
        }
        mainMenu[MenuSelected].setFillColor(Color::White);

    }
}
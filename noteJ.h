#ifndef __$__NoteJ_h
#define __$__NoteJ_h
#define DSCREENWIDTH 800
#define DSCREENHEIGHT 600
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define DELETE 8
#define ENTER 13
#define COPY 3
#define PASTE 22 //previously 16
#define SAVE 19
#define SELECTALL 1
#define UNDO 26
#define CUT 24
#define TAB 9
#define NEWFILE 100
#define OPEN 101
#define EXIT 102
#define SAVEAS 103
#define NOTHINGSELECTED 104
#define ABOUT 105
#define HELP 106
#define WORDWRAP 107
#define CHANGEFONT 108
#define ZOOMIN 109
#define ZOOMOUT 110
#define STATUSBAR 111
#define NEWWINDOW 112
//Define these using unicode
#define FIND 154    //Ctrl+F
#define REPLACE 564 //Ctrl+R
#define SCREENSHOT 113
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <windows.h>
#include <sstream>
#include <cmath>
#include <direct.h>
int fontSize;
int windowWidth = 800;
int windowHeight = 600;
sf::Vector2f mainWindowReferencepos;
class Textbox
{
private:
    sf::Text textbox;
    std::string text;
    int currentPos;
    int isSelectionOn;
    std::string selectedString;
    int selectionStart;
    int selectionEnd;
    int currentLine;
    int saveState;
    int currentColoumn;
    int addCharacter(int charEntered)
    {
        int lastCharacter = charEntered;
        if (charEntered > 31)
        {
            text.insert(currentPos, 1, static_cast<char>(charEntered));
            textbox.setString(text);
            currentPos++;
        }
        else if (charEntered == 8)
        {
            deleteAtPos();
        }
        else if (charEntered == 9)
        {
            text.insert(currentPos, 1, '\t');
            currentPos++;
            textbox.setString(text);
        }
        else if (charEntered == ENTER)
        {
            text.insert(currentPos, 1, '\n');
            textbox.setString(text);
            currentPos++;
        }
        else if (charEntered == PASTE)
        {
            int size;
            std::string clip;
            clip = sf::Clipboard::getString().toAnsiString();
            if (clip.size() != 0)
            {
                text.insert(currentPos, clip);
                currentPos += clip.size();
            }
            textbox.setString(text);
        }
        else if (charEntered == SAVE)
        {
            saveState = 1;
        }
        else if (charEntered == COPY)
        {
            //To Be Handeled --This Copies the whole data
            sf::String str=text;
            sf::Clipboard::setString(str);
        }
        return lastCharacter;
    }
    void deleteAtPos()
    {
        if (currentPos >= 0)
        {
            std::string t = text;
            std::string newT("");
            if (currentPos != 0)
            {
                currentPos--;
                for (int i = 0; i < t.length(); i++)
                {
                    if (i != currentPos)
                        newT.append(1, t[i]);
                }
                text = newT;
            }
            textbox.setString(text);
        }
        textbox.setString(text);
    }

public:
    Textbox(int size, sf::Color color)
    {
        textbox.setCharacterSize(size);
        textbox.setColor(color);
        textbox.setString("");
        currentPos = 0;
        saveState = 0;
    }
    void saved()
    {
        this->saveState = 0;
    }
    void setPosition(sf::Vector2f(pos))
    {
        textbox.setPosition(pos);
    }
    void resizer(int size, sf::Color color)
    {
        textbox.setColor(color);
        textbox.setCharacterSize(size);
    }
    void insertString(std::string string)
    {
        int size = string.size();
        text.insert(currentPos, string);
        currentPos = 0;
        textbox.setString(text);
    }
    void setFont(sf::Font &font)
    {
        textbox.setFont(font);
    }
    std::string getText()
    {
        return text;
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(textbox);
    }
    int takeInput(sf::Event event)
    {
        int lastCharacter = -1;
        int charEntered = event.text.unicode;
        if (charEntered <= 128)
        {
            lastCharacter = addCharacter(charEntered);
            return lastCharacter;
        }
        return lastCharacter;
    }
    sf::Vector2f getCharacterPos()
    {
        return textbox.findCharacterPos(currentPos);
    }
    int getLength()
    {
        return text.size();
    }
    void moveCursor(int i)
    {
        if (i == 1)
        {
            if (currentPos != text.size())
                currentPos++;
        }
        else
        {
            if (currentPos != 0)
                currentPos--;
        }
    }
    void cursorUp()
    {
        int i;
        std::string t = text;
        i = currentPos;
        int j = getColoumnNumber();
        if(t[currentPos-1]=='\n')
        {
            if(currentPos!=0)currentPos--;
        }
        else
        {
        while (i > 0)
        {
            if (t[i] == '\n')
                break;
            i--;
        }
        if (i != 0)
        {
            if(t[i-1]=='\n')currentPos=i;
            else currentPos = i-1;
        }
        else
            currentPos = 0;
        }
    }
    void cursorDown()
    {
        int i;
        std::string t = text;
        i = currentPos;
        while (i < text.size())
        {
            if (t[i] == '\n')
                break;
            i++;
        }
        if (i != text.size())
            currentPos = i + 1;
        else
        {
            currentPos = text.size();
        }
    }
    int getSaveState()
    {
        return saveState;
    }
    void setColoumnNumber()
    {
        int i;
        for (i = currentPos; i > 0; i--)
        {
            if (text[i] == '\n')
            {
                break;
            }
        }
        if (currentPos == 0)
            this->currentColoumn = 0;
        else
            this->currentColoumn = currentPos - i;
    }
    int getColoumnNumber()
    {
        setColoumnNumber();
        return currentColoumn;
    }
    void pasteIt()
    {
        int size;
        std::string clip;
        clip = sf::Clipboard::getString().toAnsiString();
        if (clip.size() != 0)
        {
            text.insert(currentPos, clip);
            currentPos += clip.size();
        }
        textbox.setString(text);
    }
    int setString(std::string string)
    {
        text.clear();
        currentPos = 0;
        insertString(string);
        textbox.setString(text);
    }
    void setLineNumber()
    {
        int i;
        int j = 1;
        for (i = 0; i <= currentPos; i++)
        {
            if (text[i] == '\n')
                j++;
        }
        this->currentLine = j;
    }
    int getLineNumber()
    {
        setLineNumber();
        return this->currentLine;
    }
    int isClicked(sf::Event event,sf::RenderWindow &window)
    {
        int pressed = 0;
        int x, y;
        if (event.type == sf::Event::MouseButtonPressed)
        {
            switch (event.key.code)
            {
            case sf::Mouse::Left:
                pressed = 1;
                break;
            case sf::Mouse::Right:
                pressed = 2;
                break;
            }
        }
        x = sf::Mouse::getPosition(window).x;
        y = sf::Mouse::getPosition(window).y;
        if (pressed == 1)
        {
            if ((x > 0 && x <= windowWidth-20) && (y > 40 && y <= windowHeight-20))
            {
                int i;sf::Vector2f pos(0,0);
                for(i=0;i<text.size();i++)
                {
                    pos=textbox.findCharacterPos(i);
                    if(pos.x>x)
                    {
                        if(pos.y+fontSize>=y)
                        {
                            break;
                        }
                    }
                }
                if(i==text.size())currentPos=text.size();
                else currentPos=i-1;
                return 1;
            }
        }
        else if (pressed == 2)
        {
            if ((x > 0 && x <= windowWidth) && (y > 40 && y <= windowHeight))
            {
                
            }
        }
        return 0;
    }
    void setColor(sf::Color color)
    {
        textbox.setColor(color);
    }
    void setSize(int size)
    {
        textbox.setCharacterSize(size);
    }
};
class Button
{
private:
    sf::Text button;
    sf::Vector2f startPos;
    sf::Vector2f endPos;
    sf::FloatRect pos;
    int last;

public:
    Button(int size, sf::Color color)
    {
        button.setCharacterSize(size);
        button.setColor(color);
        last = 0;
    }
    int setButtonText(std::string string)
    {
        button.setString(string);
        last = string.size();
        endPos = button.findCharacterPos(last);
        pos = button.getLocalBounds();
    }
    void setButtonPosition(sf::Vector2f pos)
    {
        button.setPosition(pos);
        startPos = pos;
    }
    sf::Vector2f getEndingButtonPos()
    {
        return button.findCharacterPos(last);
    }
    int isClicked(sf::Event event, sf::RenderWindow &window)
    {
        //Pressed=1 Left Mouse Button Pressed Pressed=2 Right Mouse Button Pressed
        int pressed = 0;
        int x, y;
        if (event.type == sf::Event::MouseButtonPressed)
        {
            switch (event.key.code)
            {
            case sf::Mouse::Left:
                pressed = 1;
                break;
            case sf::Mouse::Right:
                pressed = 2;
                break;
            }
        }
        x = sf::Mouse::getPosition(window).x;
        y = sf::Mouse::getPosition(window).y;
        if (pressed == 1)
        {
            if ((x > startPos.x && x <= startPos.x + pos.width) && (y > startPos.y && y <= startPos.y + button.getCharacterSize()))
            {
                return 1;
            }
        }
        else if (pressed == 2)
        {
            if ((x > startPos.x && x <= startPos.x + pos.width) && (y >= startPos.y && y <= startPos.y + button.getCharacterSize()))
            {
                return 2;
            }
        }
        return 0;
    }
    void setFont(sf::Font &font)
    {
        button.setFont(font);
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(button);
    }
    int getCharacterSize()
    {
        return button.getCharacterSize();
    }
    void setLineSpacing(float factor)
    {
        button.setLineSpacing(factor);
    }
    float getLineSpacing()
    {
        return button.getLineSpacing();
    }
    void setCharacterSize(int size)
    {
        return button.setCharacterSize(size);
    }
    void setFillColor(sf::Color color)
    {
        button.setOutlineColor(color);
        button.setOutlineThickness(5);
    }
};
class ButtonRect
{
private:
    sf::Text text;
    int posX, posY;
    sf::Vector2f rectSize;
    sf::RectangleShape buttonRect;

public:
    ButtonRect(int posX, int posY, sf::Vector2f size, sf::Color color)
    {
        this->posX = posX;
        this->posY = posY;
        rectSize = size;
        buttonRect.setPosition(this->posX, this->posY);
        buttonRect.setSize(this->rectSize);
        buttonRect.setFillColor(color);
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(buttonRect);
        window.draw(text);
    }
    int isClicked(sf::Event event, sf::RenderWindow &window)
    {
        int pressed = 0;
        int x, y;
        if (event.type == sf::Event::MouseButtonPressed)
        {
            switch (event.key.code)
            {
            case sf::Mouse::Left:
                pressed = 1;
                break;
            case sf::Mouse::Right:
                pressed = 2;
                break;
            }
        }

        x = sf::Mouse::getPosition(window).x;
        y = sf::Mouse::getPosition(window).y;
        if (pressed == 1)
        {
            if ((x > posX && y > posY) && (x < rectSize.x + posX && y < rectSize.y + posY))
            {
                return 1;
            }
        }
        else if (pressed == 2)
        {
            if ((x > posX && y > posY) && (x < rectSize.x + posX && y < rectSize.y + posY))
            {
                return 2;
            }
        }
        return 0;
    }
    void setTextPos(sf::Vector2f pos)
    {
        text.setPosition(pos);
    }
    void setFont(sf::Font &font)
    {
        text.setFont(font);
        sf::Vector2f textPos;
        textPos.x = this->posX;
        textPos.y = this->posY + rectSize.y / 2;
        setTextPos(textPos);
    }
    void setTextColor(sf::Color color)
    {
        text.setColor(color);
    }
    void setCharacterSize(int size)
    {
        text.setCharacterSize(size);
        sf::Vector2f textPos;
        textPos.x = this->posX;
        textPos.y = this->posY + rectSize.y / 2 - size / 2;
        setTextPos(textPos);
    }
    void setRectColor(sf::Color color)
    {
        buttonRect.setFillColor(color);
    }
    void setText(const char *string)
    {
        text.setString(string);
    }
    void setTextOutline(sf::Color color, int size)
    {
        text.setOutlineColor(color);
        text.setOutlineThickness(size);
    }
    void setSize(sf::Vector2f size)
    {
        this->rectSize = size;
        buttonRect.setSize(size);
    }
    void setPosition(int posX, int posY)
    {
        this->posX = posX;
        this->posY = posY;
        buttonRect.setPosition(this->posX, this->posY);
    }
};
class ButtonCircle
{
private:
    sf::Text text;
    int centerX, centerY;
    int radius;
    sf::CircleShape buttonCircle;

public:
    ButtonCircle(int posX, int posY, int radius, sf::Color color)
    {
        this->centerX = posX + radius;
        this->centerY = posY + radius;
        this->radius = radius;
        buttonCircle.setPosition(posX, posY);
        buttonCircle.setRadius(radius);
        buttonCircle.setFillColor(color);
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(buttonCircle);
        window.draw(text);
    }
    int isClicked(sf::Event event, sf::RenderWindow &window)
    {
        int pressed = 0;
        int x, y;
        if (event.type == sf::Event::MouseButtonPressed)
        {
            switch (event.key.code)
            {
            case sf::Mouse::Left:
                pressed = 1;
                break;
            case sf::Mouse::Right:
                pressed = 2;
                break;
            }
        }
        x = sf::Mouse::getPosition(window).x;
        y = sf::Mouse::getPosition(window).y;
        double distance = pow(x - centerX, 2) + pow(y - centerY, 2);
        distance = sqrt(distance);
        if (pressed == 1)
        {

            if (distance < radius)
            {
                return 1;
            }
        }
        else if (pressed == 2)
        {
            if ((distance < radius))
            {
                return 2;
            }
        }
        return 0;
    }
    void setTextPos(sf::Vector2f pos)
    {
        text.setPosition(pos);
    }
    void setFont(sf::Font &font)
    {
        text.setFont(font);
        sf::Vector2f textPos;
        textPos.x = this->centerX - radius;
        textPos.y = this->centerY;
        setTextPos(textPos);
    }
    void setTextColor(sf::Color color)
    {
        text.setColor(color);
    }
    void setCharacterSize(int size)
    {
        text.setCharacterSize(size);
        sf::Vector2f textPos;
        textPos.x = this->centerX - radius;
        textPos.y = this->centerY - size / 2;
        setTextPos(textPos);
    }
    void setCircleColor(sf::Color color)
    {
        buttonCircle.setFillColor(color);
    }
    void setText(const char *string)
    {
        text.setString(string);
    }
    void setTextOutline(sf::Color color, int size)
    {
        text.setOutlineColor(color);
        text.setOutlineThickness(size);
    }
    void setSize(int size)
    {
        buttonCircle.setRadius(size);
    }
    void setPosition(int posX, int posY)
    {
        this->centerX = posX + radius;
        this->centerY = posY + radius;
        buttonCircle.setPosition(posX, posY);
    }
};
class PhotoButton
{
private:
    sf::Text text;
    int posX, posY;
    sf::Vector2f rectSize;
    sf::RectangleShape buttonRect;
    sf::Texture *Texture;

public:
    PhotoButton(int posX, int posY, sf::Vector2f size, const char *filePath)
    {
        Texture = new sf::Texture;
        Texture->loadFromFile(filePath);
        this->posX = posX;
        this->posY = posY;
        rectSize = size;
        buttonRect.setPosition(this->posX, this->posY);
        buttonRect.setSize(this->rectSize);
        buttonRect.setTexture(Texture);
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(buttonRect);
        window.draw(text);
    }
    int isClicked(sf::Event event, sf::RenderWindow &window)
    {
        int pressed = 0;
        int x, y;
        if (event.type == sf::Event::MouseButtonPressed)
        {
            switch (event.key.code)
            {
            case sf::Mouse::Left:
                pressed = 1;
                break;
            case sf::Mouse::Right:
                pressed = 2;
                break;
            }
        }

        x = sf::Mouse::getPosition(window).x;
        y = sf::Mouse::getPosition(window).y;
        if (pressed == 1)
        {
            if ((x > posX && y > posY) && (x < rectSize.x + posX && y < rectSize.y + posY))
            {
                return 1;
            }
        }
        else if (pressed == 2)
        {
            if ((x > posX && y > posY) && (x < rectSize.x + posX && y < rectSize.y + posY))
            {
                return 2;
            }
        }
        return 0;
    }
    void setTextPos(sf::Vector2f pos)
    {
        text.setPosition(pos);
    }
    void setFont(sf::Font &font)
    {
        text.setFont(font);
        sf::Vector2f textPos;
        textPos.x = this->posX;
        textPos.y = this->posY + rectSize.y / 2;
        setTextPos(textPos);
    }
    void setTextColor(sf::Color color)
    {
        text.setColor(color);
    }
    void setCharacterSize(int size)
    {
        text.setCharacterSize(size);
        sf::Vector2f textPos;
        textPos.x = this->posX;
        textPos.y = this->posY + rectSize.y / 2 - size / 2;
        setTextPos(textPos);
    }
    void setRectColor(sf::Color color)
    {
        buttonRect.setFillColor(color);
    }
    void setText(const char *string)
    {
        text.setString(string);
    }
    void setTextOutline(sf::Color color, int size)
    {
        text.setOutlineColor(color);
        text.setOutlineThickness(size);
    }
    void setSize(sf::Vector2f size)
    {
        this->rectSize = size;
        buttonRect.setSize(size);
    }
    void setPosition(int posX, int posY)
    {
        this->posX = posX;
        this->posY = posY;
        buttonRect.setPosition(this->posX, this->posY);
    }
};
#endif
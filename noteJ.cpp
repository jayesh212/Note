#include "noteJGlobal.h"
#include "noteJ.h"
using namespace sf;
char *filePath;
// To Compile
//g++ notej.cpp icon.res -Ic:\sfml\include -Lc:\sfml\lib -lsfml-graphics -lsfml-window -lsfml-system -lcomdlg32 -o note.exe
int main(int argc, char *argv[])
{
    filePath = new char[100];
    char *tempFilePath;
    tempFilePath = new char[100];
    _chdir("c:/Program Files/note");
    filePath[0] = '\0';
    fontSize = 20;
    fileSaved = true;
    if (argc == 2)
    {
        strcpy(filePath, argv[1]);
        newFile = false;
    }
    else
    {
        newFile = true;
    }
    std::string textData("");
    if (!newFile)
    {
        textData = readFileToString(filePath);
    }
    hWnd = GetConsoleWindow();
    if (argc == 1)
    {
        ShowWindow(hWnd, SW_HIDE);
    }
    int fileClicked, editClicked, viewClicked, formatClicked, helpClicked;
    RenderWindow window(VideoMode(DSCREENWIDTH, DSCREENHEIGHT), "Note-J", Style::Default);
    window.setFramerateLimit(30);
    if (!font.loadFromFile("resources/Fonts/consolas.ttf"))
    {
        if (!font.loadFromFile("c:/Program Files/note/resources/Fonts/consolas.ttf"))
        {
            std::cout << "Error Loading Font" << std::endl;
            return 0;
        }
    }
    Image image;
    image.loadFromFile("resources/icon.png");
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    bool cursorUsed = true;
    Textbox textbox(fontSize, lightPurple);
    textbox.setFont(font);
    textbox.setString("");
    textbox.insertString(textData);
    textbox.setPosition(sf::Vector2f(0, 40));
    Textbox currentColoumnBar(17, textLighter);
    Textbox currentLineBar(17, textLighter);
    currentLineBar.setFont(font);
    currentLineBar.setPosition(sf::Vector2f(SCREEN_WIDTH - 390, SCREEN_HEIGHT - 18));
    currentColoumnBar.setFont(font);
    currentColoumnBar.setPosition(sf::Vector2f(DSCREENWIDTH - 200, DSCREENHEIGHT - 18));
    std::string currentColoumn(""), currentLine("");
    //Some Flags for buttons
    int fileMenuFlag, editMenuFlag, formatMenuFlag, viewMenuFlag, helpMenuFlag, textFlag;
    //Creating Top ,Side And Bottom Bars
    sf::RectangleShape topBar, bottomBar, sideBar;
    topBar.setPosition(Vector2f(0, 0));
    sideBar.setPosition(Vector2f(DSCREENWIDTH - 18, 0));
    bottomBar.setPosition(Vector2f(0, DSCREENHEIGHT - 18));
    topBar.setSize(Vector2f(DSCREENWIDTH, 20));
    sideBar.setSize(Vector2f(18, DSCREENHEIGHT));
    bottomBar.setSize(Vector2f(DSCREENWIDTH, 18));
    topBar.setFillColor(atomBackground);
    sideBar.setFillColor(boundaryColor);
    bottomBar.setFillColor(boundaryColor);
    // Creating Scrollers
    sf::Vector2f scrollerVerticalSize(12, DSCREENHEIGHT / 7), scrollerHorizontalSize(DSCREENWIDTH / 8, 12);
    ButtonRect scrollV(DSCREENWIDTH - 15, 18, scrollerVerticalSize, scrollerColor), scrollH(0, DSCREENHEIGHT - 15, scrollerHorizontalSize, scrollerColor);
    //Menu Buttons
    sf::Vector2f menuButtonSize(60, 20);
    ButtonRect file(0, -2, menuButtonSize, atomBackground), view(60, -2, menuButtonSize, atomBackground), edit(120, -2, menuButtonSize, atomBackground), format(180, -2, menuButtonSize, atomBackground), help(240, -2, menuButtonSize, atomBackground);
    sf::Vector2f fileButtonStartPos, editButtonStartPos, formatButtonStartPos, helpButtonStartPos, viewButtonStartPos;
    fileButtonStartPos = Vector2f(0, 0);
    viewButtonStartPos = Vector2f(60, 0);
    editButtonStartPos = Vector2f(120, 0);
    formatButtonStartPos = Vector2f(180, 0);
    helpButtonStartPos = Vector2f(240, 0);
    file.setFont(font);
    edit.setFont(font);
    view.setFont(font);
    help.setFont(font);
    format.setFont(font);
    file.setCharacterSize(fontSize);
    edit.setCharacterSize(fontSize);
    help.setCharacterSize(fontSize);
    format.setCharacterSize(fontSize);
    view.setCharacterSize(fontSize);
    file.setText("File  ");
    file.setTextColor(lightGrey);
    edit.setText("Edit  ");
    edit.setTextColor(lightGrey);
    view.setText("View  ");
    view.setTextColor(lightGrey);
    help.setText("  Help");
    help.setTextColor(lightGrey);
    format.setText("Format  ");
    format.setTextColor(lightGrey);
    sf::RectangleShape explorerBar;
    explorerBar.setSize(Vector2f(DSCREENWIDTH, 20));
    explorerBar.setPosition(Vector2f(0, 20));
    explorerBar.setFillColor(boundaryColor);
    //   Cursor
    ButtonRect play(DSCREENWIDTH - 120, 18, Vector2f(40, 20), boundaryColor);
    play.setFont(font);
    play.setCharacterSize(18);
    play.setText("Play");
    play.setTextColor(cursorBlue);
    sf::RectangleShape cursor;
    sf::Vector2f cursorPos = textbox.getCharacterPos();
    cursor.setPosition(cursorPos);
    cursor.setSize(Vector2f(2, fontSize + 2));
    cursor.setFillColor(cursorBlue);
    HWND windowHandle;
    windowHandle = window.getSystemHandle();
    sf::Clock clock, clock2;
    sf::Time time, time2;
    int doYouWantToSaveFile = 1;
    sf::View fullScreenView, normalView;
    fullScreenView.setSize(Vector2f(1366, 768));
    fullScreenView.setCenter(Vector2f(683, 384));
    normalView.setSize(Vector2f(800, 600));
    normalView.setCenter(400, 300);
    mainWindowReferencepos = (Vector2f)window.getPosition();
    int scrollX = 0, scrollY = 40;
    int playFlag = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                if (!fileSaved)
                {
                    if (textbox.getText().size() == 0 && newFile)
                    {
                        window.close();
                        break;
                    }
                    doYouWantToSaveFile = fileSaveDialog();
                    if (doYouWantToSaveFile == 1)
                    {
                        if (newFile)
                        {
                            tempFilePath = getSaveFilePath(windowHandle);
                            if (flagSave)
                            {
                                filePath = tempFilePath;
                                textData = textbox.getText();
                                writeToFile(textData, filePath);
                                fileSaved = true;
                                flagSave = false;
                                window.close();
                            }
                        }
                        else
                        {
                            textData = textbox.getText();
                            writeToFile(textData, filePath);
                            fileSaved = true;
                            window.close();
                        }
                    }
                    else if (doYouWantToSaveFile == 0)
                    {
                        window.close();
                    }
                }
                else
                {
                    window.close();
                }
                break;
            case sf::Event::Resized:
                //Dealing with Resizing
                if (windowHeight == 600)
                {
                    mainWindowReferencepos = (Vector2f)window.getPosition();
                    windowHeight = 768;
                    windowWidth = 1366;
                    window.setView(fullScreenView);
                    textbox.resizer(fontSize + 2, lightPurple);
                    file.setFont(font);
                    edit.setFont(font);
                    view.setFont(font);
                    help.setFont(font);
                    format.setFont(font);
                    edit.setCharacterSize(fontSize);
                    help.setCharacterSize(fontSize);
                    format.setCharacterSize(fontSize);
                    file.setCharacterSize(fontSize);
                    view.setCharacterSize(fontSize);
                    topBar.setSize(Vector2f(windowWidth, 20));
                    topBar.setPosition(0, 0);
                    sideBar.setSize(Vector2f(20, windowHeight));
                    sideBar.setPosition(windowWidth - 20, 20);
                    bottomBar.setSize(Vector2f(windowWidth, 20));
                    bottomBar.setPosition(0, windowHeight - 20);
                    scrollerHorizontalSize.x = windowWidth / 8;
                    scrollerHorizontalSize.y = 14;
                    scrollerVerticalSize.x = 14;
                    scrollerVerticalSize.y = windowHeight / 7;
                    scrollV.setSize(scrollerVerticalSize);
                    scrollV.setPosition(windowWidth - 18, 20);
                    scrollH.setPosition(0, windowHeight - 18);
                    scrollH.setSize(scrollerHorizontalSize);
                    currentLineBar.setFont(font);
                    currentLineBar.setPosition(sf::Vector2f(windowWidth - 390, windowHeight - 18));
                    currentColoumnBar.setFont(font);
                    explorerBar.setSize(sf::Vector2f(windowWidth, 16));
                    currentColoumnBar.setPosition(sf::Vector2f(windowWidth - 200, windowHeight - 18));
                    cursor.setSize(Vector2f(2, fontSize + 2));
                }
                else
                {
                    mainWindowReferencepos = (Vector2f)window.getPosition();
                    windowHeight = 600;
                    windowWidth = 800;
                    window.setView(normalView);
                    textbox.resizer(fontSize, lightPurple);
                    file.setFont(font);
                    edit.setFont(font);
                    view.setFont(font);
                    help.setFont(font);
                    format.setFont(font);
                    edit.setCharacterSize(fontSize - 2);
                    help.setCharacterSize(fontSize - 2);
                    format.setCharacterSize(fontSize - 2);
                    file.setCharacterSize(fontSize - 2);
                    view.setCharacterSize(fontSize - 2);
                    topBar.setSize(Vector2f(windowWidth, 18));
                    topBar.setPosition(0, 0);
                    sideBar.setSize(Vector2f(18, windowHeight));
                    sideBar.setPosition(windowWidth - 18, 18);
                    bottomBar.setSize(Vector2f(windowWidth, 18));
                    bottomBar.setPosition(0, windowHeight - 18);
                    scrollerHorizontalSize.x = windowWidth / 8;
                    scrollerHorizontalSize.y = 12;
                    scrollerVerticalSize.x = 12;
                    scrollerVerticalSize.y = windowHeight / 7;
                    scrollV.setSize(scrollerVerticalSize);
                    scrollV.setPosition(windowWidth - 18, 18);
                    scrollH.setPosition(0, windowHeight - 18);
                    scrollH.setSize(scrollerHorizontalSize);
                    currentLineBar.setFont(font);
                    currentLineBar.setPosition(sf::Vector2f(windowWidth - 390, windowHeight - 18));
                    currentColoumnBar.setFont(font);
                    explorerBar.setSize(sf::Vector2f(windowWidth, 16));
                    currentColoumnBar.setPosition(sf::Vector2f(windowWidth - 200, windowHeight - 18));
                    cursor.setSize(Vector2f(2, fontSize));
                }
                break;
            case sf::Event::TextEntered:
                textbox.takeInput(event);
                fileSaved = false;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Left)
                {
                    textbox.moveCursor(0);
                    clock2.restart();
                    cursorUsed = true;
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    textbox.moveCursor(1);
                    clock2.restart();
                    cursorUsed = true;
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    textbox.cursorUp();
                    clock2.restart();
                    cursorUsed = true;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    textbox.cursorDown();
                    clock2.restart();
                    cursorUsed = true;
                }
                break;
            case sf::Event::MouseButtonPressed:
                //Handling Mouse Clicks
                fileClicked = file.isClicked(event, window);
                editClicked = edit.isClicked(event, window);
                viewClicked = view.isClicked(event, window);
                helpClicked = help.isClicked(event, window);
                formatClicked = format.isClicked(event, window);
                playFlag = play.isClicked(event, window);
                textFlag = textbox.isClicked(event, window);
                break;
            }
        }
        if (textFlag == 1)
        {
            textFlag = 0;
        }
        if (fileClicked == 1)
        {
            mainWindowReferencepos = (Vector2f)window.getPosition();
            fileMenuFlag = fileWindow(fileButtonStartPos);
            if (fileMenuFlag == NEWFILE)
            {
                if (!fileSaved)
                {
                    doYouWantToSaveFile = fileSaveDialog();
                    if (doYouWantToSaveFile == 1)
                    {
                        if (newFile)
                        {
                            tempFilePath = getSaveFilePath(windowHandle);
                            if (flagSave)
                            {
                                filePath = tempFilePath;
                                textData = textbox.getText();
                                writeToFile(textData, filePath);
                                fileSaved = true;
                                flagSave = false;
                            }
                        }
                        else
                        {
                            textData = textbox.getText();
                            writeToFile(textData, filePath);
                            fileSaved = true;
                        }
                        textbox.setString("");
                        fileSaved = true;
                        newFile = true;
                    }
                    else if (doYouWantToSaveFile == 0)
                    {
                        textbox.setString("");
                        fileSaved = true;
                        newFile = true;
                    }
                }
                else
                {
                    textbox.setString("");
                    fileSaved = true;
                    newFile = true;
                }
            }
            else if (fileMenuFlag == NEWWINDOW)
            {
                //Experimental
                system("note.exe");
            }
            else if (fileMenuFlag == OPEN)
            {
                if (!fileSaved)
                {
                    doYouWantToSaveFile = fileSaveDialog();
                    if (doYouWantToSaveFile == 1)
                    {
                        if (newFile)
                        {
                            tempFilePath = getSaveFilePath(windowHandle);
                            if (flagSave)
                            {
                                filePath = tempFilePath;
                                textData = textbox.getText();
                                writeToFile(textData, filePath);
                                fileSaved = false;
                                newFile = false;
                            }
                        }
                        else
                        {
                            textData = textbox.getText();
                            writeToFile(textData, filePath);
                            fileSaved = true;
                        }
                        textbox.setString("");
                        filePath = openNewFile(windowHandle);
                        textData = readFileToString(filePath);
                        textbox.setString(textData);
                        fileSaved = true;
                        newFile = false;
                    }
                    else if (doYouWantToSaveFile == 0)
                    {
                        tempFilePath = openNewFile(windowHandle);
                        if (flagSave)
                        {
                            filePath = tempFilePath;
                            textbox.setString("");
                            textData = readFileToString(filePath);
                            textbox.setString(textData);
                            fileSaved = true;
                            newFile = false;
                            fileSaved = false;
                        }
                    }
                }
                else
                {
                    tempFilePath = openNewFile(windowHandle);
                    if (flagSave)
                    {
                        filePath = tempFilePath;
                        textbox.setString("");
                        textData = readFileToString(filePath);
                        textbox.setString(textData);
                        fileSaved = true;
                        newFile = false;
                        flagSave = false;
                    }
                }
            }
            else if (fileMenuFlag == EXIT)
            {
                if (!fileSaved)
                {
                    doYouWantToSaveFile = fileSaveDialog();
                    if (doYouWantToSaveFile == 1)
                    {
                        if (newFile)
                        {
                            tempFilePath = getSaveFilePath(windowHandle);
                            if (flagSave)
                            {
                                filePath = tempFilePath;
                                textData = textbox.getText();
                                writeToFile(textData, filePath);
                                fileSaved = true;
                                flagSave = false;
                            }
                        }
                        else
                        {
                            textData = textbox.getText();
                            writeToFile(textData, filePath);
                            fileSaved = true;
                        }
                        window.close();
                    }
                    else if (doYouWantToSaveFile == 0)
                    {
                        window.close();
                    }
                }
                else
                {
                    window.close();
                }
            }
            else if (fileMenuFlag == SAVE)
            {
                if (!fileSaved)
                {
                    if (newFile)
                    {
                        tempFilePath = getSaveFilePath(windowHandle);
                        if (flagSave)
                        {
                            filePath = tempFilePath;
                            textData = textbox.getText();
                            writeToFile(textData, filePath);
                            fileSaved = true;
                            flagSave = false;
                            newFile = false;
                        }
                    }
                    else
                    {
                        textData = textbox.getText();
                        writeToFile(textData, filePath);
                        fileSaved = true;
                        newFile = false;
                    }
                }
            }
            else if (fileMenuFlag == SAVEAS)
            {
                tempFilePath = getSaveFilePath(windowHandle);
                if (flagSave)
                {
                    filePath = tempFilePath;
                    textData = textbox.getText();
                    writeToFile(textData, filePath);
                    fileSaved = true;
                    flagSave = false;
                    newFile = false;
                }
            }
            fileClicked = 0;
        }
        else if (editClicked == 1)
        {
            mainWindowReferencepos = (Vector2f)window.getPosition();
            editMenuFlag = editWindow(editButtonStartPos);
            editClicked = 0;
        }
        else if (viewClicked == 1)
        {
            mainWindowReferencepos = (Vector2f)window.getPosition();
            viewMenuFlag = viewWindow(viewButtonStartPos);
            viewClicked = 0;
        }
        else if (helpClicked == 1)
        {
            mainWindowReferencepos = (Vector2f)window.getPosition();
            helpMenuFlag = helpWindow(helpButtonStartPos);
            helpClicked = 0;
        }
        else if (formatClicked == 1)
        {
            mainWindowReferencepos = (Vector2f)window.getPosition();
            formatMenuFlag = formatWindow(formatButtonStartPos);
            if (formatMenuFlag == CHANGEFONT)
            {
                launchSettingsWindow();
                textbox.setColor(textColor);
                textbox.setFont(font);
                textbox.setSize(fontSize);
            }
            formatClicked = 0;
        }
        else if (playFlag == 1)
        {
            if (!fileSaved)
            {
                if (newFile)
                {
                    tempFilePath = getSaveFilePath(windowHandle);
                    if (flagSave)
                    {
                        filePath = tempFilePath;
                        textData = textbox.getText();
                        writeToFile(textData, filePath);
                        fileSaved = true;
                        flagSave = false;
                        newFile = false;
                    }
                }
                else
                {
                    textData = textbox.getText();
                    writeToFile(textData, filePath);
                    fileSaved = true;
                    newFile = false;
                }
            }
            if (fileSaved)
                programRunner();
            playFlag = 0;
        }
        if (textbox.getSaveState() == 1)
        {
            if (!fileSaved)
            {
                if (newFile)
                {
                    tempFilePath = getSaveFilePath(windowHandle);
                    if (flagSave)
                    {
                        filePath = tempFilePath;
                        std::cout << filePath;
                        textData = textbox.getText();
                        writeToFile(textData, filePath);
                        fileSaved = true;
                        flagSave = false;
                        newFile = false;
                    }
                }
                else
                {
                    textData = textbox.getText();
                    writeToFile(textData, filePath);
                    fileSaved = true;
                    newFile = false;
                }
            }
            textbox.saved();
        }
        cursorPos = textbox.getCharacterPos();
        if (cursorPos.x > windowWidth - fontSize)
        {
            scrollX -= fontSize;
            textbox.setPosition(Vector2f(scrollX, scrollY));
        }
        else if (cursorPos.x <= fontSize && scrollX < 0)
        {
            scrollX += fontSize;
            textbox.setPosition(Vector2f(scrollX, scrollY));
        }
        if (cursorPos.y > windowHeight - 2 * fontSize)
        {
            scrollY -= fontSize;
            textbox.setPosition(Vector2f(scrollX, scrollY));
        }
        else if (cursorPos.y <= 40 && scrollY < 40)
        {
            scrollY += fontSize;
            textbox.setPosition(Vector2f(scrollX, scrollY));
        }
        scrollH.setPosition(cursorPos.x, windowHeight - 16);
        scrollV.setPosition(windowWidth - 16, cursorPos.y);
        cursor.setPosition(cursorPos);
        currentLine = "Line : " + std::to_string(textbox.getLineNumber());
        currentColoumn = "Coloumn : " + std::to_string(textbox.getColoumnNumber());
        currentColoumnBar.setString(currentColoumn);
        currentLineBar.setString(currentLine);
        window.clear(backgroundColor);
        textbox.draw(window);
        time = clock.getElapsedTime();
        time2 = clock2.getElapsedTime();
        if (cursorUsed)
        {
            window.draw(cursor);
            if (time2.asSeconds() > 1)
            {
                cursorUsed = false;
            }
        }
        else
        {
            if (time.asMilliseconds() % 1000 < 500)
            {
                window.draw(cursor);
            }
        }
        window.draw(bottomBar);
        window.draw(sideBar);
        window.draw(topBar);
        scrollV.draw(window);
        scrollH.draw(window);
        currentColoumnBar.draw(window);
        currentLineBar.draw(window);
        window.draw(explorerBar);
        play.draw(window);
        file.draw(window);
        edit.draw(window);
        help.draw(window);
        view.draw(window);
        format.draw(window);
        window.display();
    }
    if (argc == 1)
    {
        ShowWindow(hWnd, SW_SHOW);
    }
    return 0;
}
std::string readFileToString(std::string filePath)
{
    std::string line, string;
    std::fstream file(filePath);
    if (filePath.size() != 0)
    {
        while (std::getline(file, line))
        {
            string.append(line);
            string.append(1, '\n');
        }
        if (string.size() != 0)
            string.pop_back();
    }
    return string;
}
void writeToFile(std::string string, std::string filePath)
{
    std::fstream file(filePath, std::ios::out);
    file << string;
    file.close();
}
char *getSaveFilePath(HWND hwnd)
{
    char *fileName;
    fileName = new char[150];
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = fileName;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 150;
    ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.txt\0C Files\0*.c\0CPP Files\0*.cpp\0";
    ofn.nFilterIndex = 1;
    flagSave = GetSaveFileName(&ofn);
    if (flagSave)
        return fileName;
    fileName = NULL;
    return fileName;
}
char *openNewFile(HWND hwnd)
{
    char *fileName;
    fileName = new char[150];
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = fileName;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 150;
    ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.txt\0C Source Files\0*.c\0CPP Source Files\0*.cpp\0";
    ofn.nFilterIndex = 1;
    flagSave = GetOpenFileName(&ofn);
    if (flagSave)
        return fileName;
    else
        fileName = NULL;
}
int fileWindow(Vector2f pos)
{
    int newClicked, newWindowClicked, openClicked, saveClicked, exitClicked, saveAsClicked;
    VideoMode vm(250, (fontSize + 1) * 8);
    RenderWindow fileMenu(vm, "", Style::None);
    fileMenu.setPosition(Vector2i(pos.x + mainWindowReferencepos.x + 7, pos.y + fontSize + mainWindowReferencepos.y + 33));
    sf::Color windowColor(37, 37, 38), textColor(177, 177, 177);
    //Setting Up The Menu Buttons
    Button New(fontSize, textColor), newWindow(fontSize, textColor), save(fontSize, textColor), saveAs(fontSize, textColor), Open(fontSize, textColor), Exit(fontSize, textColor);
    New.setFont(font);
    newWindow.setFont(font);
    save.setFont(font);
    saveAs.setFont(font);
    Open.setFont(font);
    Exit.setFont(font);
    New.setButtonText("  New File (Ctrl + N)       ");
    newWindow.setButtonText("  New Window            ");
    save.setButtonText("  Save (Ctrl + S)             ");
    saveAs.setButtonText("  Save As..            ");
    Open.setButtonText("  Open (Ctrl + O)            ");
    Exit.setButtonText("  Exit (Alt + F4)          ");
    New.setButtonPosition(Vector2f(pos.x + 7, pos.y + 10));
    newWindow.setButtonPosition(Vector2f(pos.x + 7, pos.y + fontSize + 15));
    Open.setButtonPosition(Vector2f(pos.x + 7, pos.y + 2 * fontSize + 20));
    save.setButtonPosition(Vector2f(pos.x + 7, pos.y + 3 * fontSize + 25));
    saveAs.setButtonPosition(Vector2f(pos.x + 7, pos.y + 4 * fontSize + 30));
    Exit.setButtonPosition(Vector2f(pos.x + 7, pos.y + 5 * fontSize + 35));
    fileMenu.setFramerateLimit(30);
    newClicked = 0;
    newWindowClicked = 0;
    saveClicked = 0;
    saveAsClicked = 0;
    exitClicked = 0;
    openClicked = 0;
    while (fileMenu.isOpen())
    {
        Event event;
        while (fileMenu.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                fileMenu.close();
                return NOTHINGSELECTED;
            }
            else if (event.type == Event::LostFocus)
            {
                fileMenu.close();
                return NOTHINGSELECTED;
            }
            else if (event.type == Event::MouseButtonPressed)
            {
                newClicked = New.isClicked(event, fileMenu);
                exitClicked = Exit.isClicked(event, fileMenu);
                saveClicked = save.isClicked(event, fileMenu);
                saveAsClicked = saveAs.isClicked(event, fileMenu);
                openClicked = Open.isClicked(event, fileMenu);
                newWindowClicked = newWindow.isClicked(event, fileMenu);
            }
        }
        if (newClicked == 1)
        {
            fileMenu.close();
            return NEWFILE;
        }
        else if (exitClicked == 1)
        {
            fileMenu.close();
            return EXIT;
        }
        else if (openClicked == 1)
        {
            fileMenu.close();
            return OPEN;
        }
        else if (saveClicked == 1)
        {
            fileMenu.close();
            return SAVE;
            saveClicked = 0;
        }
        else if (saveAsClicked == 1)
        {
            fileMenu.close();
            return SAVEAS;
            saveAsClicked = 0;
        }
        else if (newWindowClicked == 1)
        {
            fileMenu.close();
            return NEWWINDOW;
        }
        fileMenu.clear(windowColor);
        New.draw(fileMenu);
        newWindow.draw(fileMenu);
        Open.draw(fileMenu);
        save.draw(fileMenu);
        saveAs.draw(fileMenu);
        Exit.draw(fileMenu);
        fileMenu.display();
    }
    return NOTHINGSELECTED;
}
int viewWindow(Vector2f pos)
{

    int zoomOutClicked, screenShotClicked, zoomInClicked;
    VideoMode vm(230, (fontSize + 1) * 5);
    RenderWindow viewMenu(vm, "", Style::None);
    viewMenu.setPosition(Vector2i(pos.x + mainWindowReferencepos.x + 7, pos.y + fontSize + mainWindowReferencepos.y + 33));
    sf::Color windowColor(37, 37, 38), textColor(177, 177, 177);
    //Setting Up The Menu Buttons
    Button zoomOut(fontSize, textColor), zoomIn(fontSize, textColor), screenShot(fontSize, textColor);
    zoomOut.setFont(font);
    zoomIn.setFont(font);
    screenShot.setFont(font);
    zoomIn.setButtonText("  Zoom In(Ctrl +)  ");
    zoomOut.setButtonText("  Zoom Out(Ctrl -)        ");
    screenShot.setButtonText("  Take ScreenShot        ");
    zoomIn.setButtonPosition(Vector2f(0, pos.y + 10));
    zoomOut.setButtonPosition(Vector2f(0, pos.y + fontSize + 15));
    screenShot.setButtonPosition(Vector2f(0, pos.y + fontSize * 2 + 20));
    viewMenu.setFramerateLimit(30);
    while (viewMenu.isOpen())
    {
        Event event;
        while (viewMenu.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                viewMenu.close();
                return NOTHINGSELECTED;
            }
            else if (event.type == Event::LostFocus)
            {
                viewMenu.close();
                return NOTHINGSELECTED;
            }
            else if (event.type == Event::MouseButtonPressed)
            {
                zoomInClicked = zoomIn.isClicked(event, viewMenu);
                zoomOutClicked = zoomOut.isClicked(event, viewMenu);
                screenShotClicked = screenShot.isClicked(event, viewMenu);
            }
        }
        if (zoomInClicked == 1)
        {
            viewMenu.close();
            return ZOOMIN;
        }
        else if (zoomOutClicked == 1)
        {
            viewMenu.close();
            return ZOOMOUT;
        }
        else if (screenShotClicked == 1)
        {
            viewMenu.close();
            return SCREENSHOT;
        }
        viewMenu.clear(windowColor);
        zoomIn.draw(viewMenu);
        zoomOut.draw(viewMenu);
        screenShot.draw(viewMenu);
        viewMenu.display();
    }
}
int formatWindow(Vector2f pos)
{
    int wordWrapClicked, changeFontClicked;
    VideoMode vm(150, (fontSize + 1) * 4);
    RenderWindow formatMenu(vm, "", Style::None);
    formatMenu.setPosition(Vector2i(pos.x + mainWindowReferencepos.x + 7, pos.y + fontSize + mainWindowReferencepos.y + 33));
    sf::Color windowColor(37, 37, 38), textColor(177, 177, 177);
    //Setting Up The Menu Buttons
    Button wordWrap(fontSize, textColor), changeFont(fontSize, textColor);
    wordWrap.setFont(font);
    changeFont.setFont(font);
    wordWrap.setButtonText("  Word Wrap      ");
    changeFont.setButtonText("  Font...        ");
    wordWrap.setButtonPosition(Vector2f(0, pos.y + 10));
    changeFont.setButtonPosition(Vector2f(0, pos.y + fontSize + 15));
    formatMenu.setFramerateLimit(30);
    while (formatMenu.isOpen())
    {
        Event event;
        while (formatMenu.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                formatMenu.close();
                return NOTHINGSELECTED;
            }
            else if (event.type == Event::LostFocus)
            {
                formatMenu.close();
                return NOTHINGSELECTED;
            }
            else if (event.type == Event::MouseButtonPressed)
            {
                wordWrapClicked = wordWrap.isClicked(event, formatMenu);
                changeFontClicked = changeFont.isClicked(event, formatMenu);
            }
        }
        if (wordWrapClicked == 1)
        {
            formatMenu.close();
            return WORDWRAP;
        }
        else if (changeFontClicked == 1)
        {
            formatMenu.close();
            return CHANGEFONT;
        }
        formatMenu.clear(windowColor);
        wordWrap.draw(formatMenu);
        changeFont.draw(formatMenu);
        formatMenu.display();
    }
}
int helpWindow(Vector2f pos)
{
    int aboutClicked, viewHelpClicked;
    VideoMode vm(150, (fontSize + 1) * 4);
    RenderWindow helpMenu(vm, "", Style::None);
    helpMenu.setPosition(Vector2i(pos.x + mainWindowReferencepos.x + 7, pos.y + fontSize + mainWindowReferencepos.y + 33));
    sf::Color windowColor(37, 37, 38), textColor(177, 177, 177);
    //Setting Up The Menu Buttons
    Button viewHelp(fontSize, textColor), about(fontSize, textColor);
    viewHelp.setFont(font);
    about.setFont(font);
    viewHelp.setButtonText("  View Help       ");
    about.setButtonText("  About       ");
    viewHelp.setButtonPosition(Vector2f(0, pos.y + 10));
    about.setButtonPosition(Vector2f(0, pos.y + fontSize + 15));
    helpMenu.setFramerateLimit(30);
    while (helpMenu.isOpen())
    {
        Event event;
        while (helpMenu.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                helpMenu.close();
                return NOTHINGSELECTED;
            }
            else if (event.type == Event::LostFocus)
            {
                helpMenu.close();
                return NOTHINGSELECTED;
            }
            else if (event.type == Event::MouseButtonPressed)
            {
                aboutClicked = about.isClicked(event, helpMenu);
                viewHelpClicked = viewHelp.isClicked(event, helpMenu);
            }
        }
        if (aboutClicked == 1)
        {
            helpMenu.close();
            return ABOUT;
        }
        else if (viewHelpClicked == 1)
        {
            helpMenu.close();
            return HELP;
        }
        helpMenu.clear(windowColor);
        about.draw(helpMenu);
        viewHelp.draw(helpMenu);
        helpMenu.display();
    }
}
int editWindow(Vector2f pos)
{
    int undoClicked, cutClicked, copyClicked, pasteClicked, findClicked, replaceClicked, selectAllClicked, deleteClicked;
    VideoMode vm(250, (fontSize + 2) * 10);
    RenderWindow editMenu(vm, "", Style::None);
    editMenu.setPosition(Vector2i(pos.x + mainWindowReferencepos.x + 7, pos.y + fontSize + mainWindowReferencepos.y + 33));
    sf::Color windowColor(37, 37, 38), textColor(177, 177, 177);
    //Setting Up The Menu Buttons
    Button Undo(fontSize, textColor), Cut(fontSize, textColor), Copy(fontSize, textColor), Paste(fontSize, textColor), Delete(fontSize, textColor), Find(fontSize, textColor), Replace(fontSize, textColor), SelectAll(fontSize, textColor);
    Undo.setFont(font);
    Cut.setFont(font);
    Copy.setFont(font);
    Paste.setFont(font);
    Delete.setFont(font);
    Find.setFont(font);
    Replace.setFont(font);
    SelectAll.setFont(font);
    Undo.setButtonText("  Undo (Ctrl + Z)       ");
    Cut.setButtonText("  Cut (Ctrl +X)            ");
    Copy.setButtonText("  Copy (Ctrl + C)             ");
    Paste.setButtonText("  Paste (Ctrl + V)            ");
    Delete.setButtonText("  Delete (DEL)            ");
    Replace.setButtonText("  Replace (Ctrl + H)          ");
    Find.setButtonText("  Find(Ctrl + F)");
    SelectAll.setButtonText("  Select All (Ctrl +A)      ");
    Undo.setButtonPosition(Vector2f(0, pos.y + 10));
    Cut.setButtonPosition(Vector2f(0, pos.y + fontSize + 15));
    Copy.setButtonPosition(Vector2f(0, pos.y + 2 * fontSize + 20));
    Paste.setButtonPosition(Vector2f(0, pos.y + 3 * fontSize + 25));
    Delete.setButtonPosition(Vector2f(0, pos.y + 4 * fontSize + 30));
    Find.setButtonPosition(Vector2f(0, pos.y + 5 * fontSize + 35));
    Replace.setButtonPosition(Vector2f(0, pos.y + 6 * fontSize + 40));
    SelectAll.setButtonPosition(Vector2f(0, pos.y + 7 * fontSize + 45));
    editMenu.setFramerateLimit(30);
    while (editMenu.isOpen())
    {
        Event event;
        while (editMenu.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                editMenu.close();
                return NOTHINGSELECTED;
            }
            else if (event.type == Event::LostFocus)
            {
                editMenu.close();
                return NOTHINGSELECTED;
            }
            else if (event.type == Event::MouseButtonPressed)
            {
                undoClicked = Undo.isClicked(event, editMenu);
                cutClicked = Cut.isClicked(event, editMenu);
                copyClicked = Copy.isClicked(event, editMenu);
                pasteClicked = Paste.isClicked(event, editMenu);
                deleteClicked = Delete.isClicked(event, editMenu);
                findClicked = Find.isClicked(event, editMenu);
                replaceClicked = Replace.isClicked(event, editMenu);
                selectAllClicked = SelectAll.isClicked(event, editMenu);
            }
        }
        if (undoClicked == 1)
        {
            editMenu.close();
            return UNDO;
        }
        else if (cutClicked == 1)
        {
            editMenu.close();
            return CUT;
        }
        else if (copyClicked == 1)
        {
            editMenu.close();
            return COPY;
        }
        else if (pasteClicked == 1)
        {
            editMenu.close();
            return PASTE;
        }
        else if (findClicked == 1)
        {
            editMenu.close();
            return FIND;
        }
        else if (replaceClicked == 1)
        {
            editMenu.close();
            return REPLACE;
        }
        else if (selectAllClicked == 1)
        {
            editMenu.close();
            return SELECTALL;
        }
        else if (deleteClicked == 1)
        {
            editMenu.close();
            return DELETE;
        }
        editMenu.clear(windowColor);
        Cut.draw(editMenu);
        Undo.draw(editMenu);
        Copy.draw(editMenu);
        Paste.draw(editMenu);
        Find.draw(editMenu);
        Replace.draw(editMenu);
        Delete.draw(editMenu);
        SelectAll.draw(editMenu);
        editMenu.display();
    }
}
void selector(sf::Event event, sf::RenderWindow &window, int &number)
{
    int i, x, y;
    x = Mouse::getPosition().x;
    y = Mouse::getPosition().y;
    sf::RectangleShape selectionRect;
    selectionRect.setSize(Vector2f(10, 4));
}
void changeFontSize()
{
    RenderWindow changeFont;
}
void about()
{
    sf::RenderWindow aboutWindow(VideoMode(700, 350), "About", Style::Close);
    Textbox aboutText(24, Color(217, 217, 217));
    aboutText.setFont(font);
    aboutText.setPosition(Vector2f(0, 20));
    aboutText.setString("A Small Project By Jayesh Sharma\nIf You Find This Project Cool and Exciting and\nwant to get the source code contact me\n\nAny Feature Requirments!!! Mail me\nI will be pleased to see Your feedback :)\nEnjoy\n\n\n\t\t\t\t\tEmail: jsharma7869@gmail.com");
    while (aboutWindow.isOpen())
    {
        Event event;
        while (aboutWindow.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                aboutWindow.close();
                break;
            }
            else if (event.type == Event::LostFocus)
            {
                aboutWindow.close();
                break;
            }
        }
        aboutWindow.clear(Color(30, 30, 30));
        aboutText.draw(aboutWindow);
        aboutWindow.display();
    }
}
int changeFont(int characterSize)
{
    sf::RenderWindow fontWindow(VideoMode(700, 500), "About", Style::Close);
    Button font1Text(20, Color(217, 217, 217)), font2Text(20, Color(217, 217, 217)), font3Text(20, Color(217, 217, 217));
    sf::Font font1, font2, font3;
    int flag1, flag2, flag3, plusFlag, minusFlag, flag;
    font1.loadFromFile("c:/Program Files/Note/resources/consolas.ttf");
    font2.loadFromFile("c:/Program Files/Note/resources/Monaco.ttf");
    font3.loadFromFile("c:/Program Files/Note/resources/Victoria.ttf");
    font1Text.setFont(font1);
    font2Text.setFont(font2);
    font3Text.setFont(font3);
    font1Text.setButtonText("Reach For The Stars");
    font2Text.setButtonText("Reach For The Stars");
    font3Text.setButtonText("Reach For The Stars");
    font1Text.setButtonPosition(Vector2f(0, 20));
    font2Text.setButtonPosition(Vector2f(0, 80));
    font3Text.setButtonPosition(Vector2f(0, 150));
    Button plus(25, Color(217, 217, 217)), minus(25, Color(217, 217, 217));
    plus.setFont(font1);
    minus.setFont(font2);
    plus.setButtonText("+");
    minus.setButtonText("-");
    plus.setButtonPosition(Vector2f(300, 300));
    minus.setButtonPosition(Vector2f(330, 300));
    plus.setFillColor(Color(99, 99, 99));
    minus.setFillColor(Color(99, 99, 99));
    sf::CircleShape circle, plusCircle, minusCircle;
    circle.setRadius(10);
    circle.setFillColor(Color(30, 215, 96));
    circle.setPosition(Vector2f(500, 20));
    Button charSize(20, Color(217, 217, 217));
    charSize.setFont(font1);
    int baseSize = 20;
    std::stringstream str1;
    str1 << "Character Size : " << baseSize;
    charSize.setButtonText(str1.str());
    charSize.setButtonPosition(Vector2f(50, 300));
    flag = 1;
    while (fontWindow.isOpen())
    {
        Event event;
        while (fontWindow.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                fontWindow.close();
                break;
            }
            else if (event.type == Event::LostFocus)
            {
                fontWindow.close();
                break;
            }
            else if (event.type == Event::MouseButtonPressed)
            {
                flag1 = font1Text.isClicked(event, fontWindow);
                flag2 = font2Text.isClicked(event, fontWindow);
                flag3 = font3Text.isClicked(event, fontWindow);
                plusFlag = plus.isClicked(event, fontWindow);
                minusFlag = minus.isClicked(event, fontWindow);
            }
        }
        if (flag1 == 1)
        {

            circle.setPosition(Vector2f(500, 20));
            flag1 = 0;
            flag = 1;
        }
        else if (flag2 == 1)
        {
            circle.setPosition(Vector2f(500, 80));
            flag2 = 0;
            flag = 2;
        }
        else if (flag3 == 1)
        {
            circle.setPosition(Vector2f(500, 150));
            flag3 = 0;
            flag = 3;
        }
        else if (plusFlag == 1)
        {
            baseSize++;
            font1Text.setCharacterSize(baseSize);
            font2Text.setCharacterSize(baseSize);
            font3Text.setCharacterSize(baseSize);
            std::stringstream str;
            str << "Character Size : " << baseSize;
            charSize.setButtonText(str.str());
            plusFlag = 0;
        }
        else if (minusFlag == 1)
        {
            baseSize--;
            font1Text.setCharacterSize(baseSize);
            font2Text.setCharacterSize(baseSize);
            font3Text.setCharacterSize(baseSize);
            std::stringstream str;
            str << "Character Size : " << baseSize;
            charSize.setButtonText(str.str());
            minusFlag = 0;
        }
        fontWindow.clear(Color(30, 30, 30));
        fontWindow.draw(circle);
        font1Text.draw(fontWindow);
        font2Text.draw(fontWindow);
        font3Text.draw(fontWindow);
        charSize.draw(fontWindow);
        plus.draw(fontWindow);
        minus.draw(fontWindow);
        fontWindow.display();
    }
    return flag;
}
void launchSettingsWindow()
{
    Vector2f size(150, 25);
    int settingFlag = 1;
    int changeFontFlag, changeThemeFlag, flag, pinkFlag, redFlag, whiteFlag, greenFlag, blueFlag, pinkBFlag, redBFlag, whiteBFlag, greenBFlag, blueBFlag, blackFlag, blackFlagB, purpleflag, darkTFlag, darkBackFlag, menuBackFlag;
    ButtonRect changeFont(0, 0, size, darkBack1), changeTheme(0, 30, size, darkBack1);
    changeFont.setFont(font);
    changeFont.setCharacterSize(20);
    changeFont.setText("Colors");
    changeFont.setTextColor(textColor);
    changeTheme.setFont(font);
    changeTheme.setCharacterSize(20);
    changeTheme.setText("Font");
    changeTheme.setTextColor(textColor);
    //Changing Tetx Color
    ButtonCircle pinkButton(160, 80, 15, magenta), greenButton(200, 80, 15, limeGreen), redButton(240, 80, 15, errorRed), blueButton(280, 80, 15, cursorBlue), whiteButton(320, 80, 15, white), blackButton(360, 80, 15, black);
    ButtonCircle darktextButton(160, 120, 15, darkText), purpleButton(200, 120, 15, lightPurple);
    Textbox textColorChanger(fontSize, textColor);
    textColorChanger.setFont(font);
    textColorChanger.setString("Change Text Color : ");
    textColorChanger.setPosition(Vector2f(160, 50));
    Textbox textBackChanger(fontSize, textColor);
    textBackChanger.setFont(font);
    textBackChanger.setString("Change Background Color : ");
    textBackChanger.setPosition(Vector2f(160, 200));
    //Changing Background Color
    ButtonCircle pinkButtonB(160, 220, 15, pink), greenButtonB(200, 220, 15, limeGreen), redButtonB(240, 220, 15, errorRed), blueButtonB(280, 220, 15, cursorBlue), whiteButtonB(320, 220, 15, white), blackButtonB(360, 220, 15, black);
    ButtonCircle darkBackButton(160, 260, 15, atomBackground), menuBackColor(200, 260, 15, menuColor);
    pinkButtonB.setCircleColor(pink);
    redButtonB.setCircleColor(errorRed);
    blueButtonB.setCircleColor(cursorBlue);
    whiteButtonB.setCircleColor(white);
    greenButtonB.setCircleColor(limeGreen);
    blackButtonB.setCircleColor(black);
    RenderWindow window(VideoMode(450, 450), "Settings", Style::Close);
    window.setVerticalSyncEnabled(true);
    sf::RectangleShape menuRect;
    menuRect.setPosition(Vector2f(150, 0));
    menuRect.setSize(Vector2f(300, 450));
    menuRect.setFillColor(backgroundColor);
    changeThemeFlag = 0;
    changeFontFlag = 1;
    flag = 1;
    Textbox fontChanger(fontSize, textColor);
    fontChanger.setFont(font);
    fontChanger.setString("Select Font : ");
    fontChanger.setPosition(Vector2f(160, 0));
    sf::Font monacoF,menloF,azonixF,consolasF;
    monacoF.loadFromFile("resources/fonts/monaco.ttf");
    menloF.loadFromFile("resources/fonts/menlo.ttf");
    azonixF.loadFromFile("resources/fonts/azonix.otf");
    consolasF.loadFromFile("resources/fonts/consolas.ttf");
    ButtonRect azonix(180, 200,Vector2f(80,fontSize+2), lightDark), consolas(350, 80,Vector2f(80,fontSize+2), lightDark), menlo(350, 200,Vector2f(80,fontSize+2), lightDark), monaco(180, 80,Vector2f(80,fontSize+2), lightDark);
    azonix.setCharacterSize(fontSize);
    consolas.setCharacterSize(fontSize);
    menlo.setCharacterSize(fontSize);
    monaco.setCharacterSize(fontSize);
    azonix.setFont(azonixF);
    consolas.setFont(consolasF);
    menlo.setFont(menloF);
    monaco.setFont(monacoF);
    azonix.setText("Azonix");
    consolas.setText("Consolas");
    monaco.setText("Monaco");
    menlo.setText("Menlo");
    azonix.setTextPos(Vector2f(180,200));
    consolas.setTextPos(Vector2f(350,80));
    menlo.setTextPos(Vector2f(350,200));
    monaco.setTextPos(Vector2f(180,80));
    consolas.setTextColor(textColor);
    menlo.setTextColor(textColor);
    monaco.setTextColor(textColor);
    azonix.setTextColor(textColor);
    int fontMenloFlag, fontMonacoFlag, fontConsolasFlag, fontAzonixFlag;
    int selectedFont = 1;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed)
            {
                changeFontFlag = changeFont.isClicked(event, window);
                changeThemeFlag = changeTheme.isClicked(event, window);
                if (settingFlag == 1)
                {
                    pinkFlag = pinkButton.isClicked(event, window);
                    redFlag = redButton.isClicked(event, window);
                    blueFlag = blueButton.isClicked(event, window);
                    greenFlag = greenButton.isClicked(event, window);
                    whiteFlag = whiteButton.isClicked(event, window);
                    pinkBFlag = pinkButtonB.isClicked(event, window);
                    redBFlag = redButtonB.isClicked(event, window);
                    blueBFlag = blueButtonB.isClicked(event, window);
                    greenBFlag = greenButtonB.isClicked(event, window);
                    whiteBFlag = whiteButtonB.isClicked(event, window);
                    blackFlag = blackButton.isClicked(event, window);
                    blackFlagB = blackButtonB.isClicked(event, window);
                    purpleflag = purpleButton.isClicked(event, window);
                    darkTFlag = darktextButton.isClicked(event, window);
                    darkBackFlag = darkBackButton.isClicked(event, window);
                    menuBackFlag = menuBackColor.isClicked(event, window);
                }
                else if (settingFlag == 2)
                {
                    fontMenloFlag = menlo.isClicked(event, window);
                    fontMonacoFlag = monaco.isClicked(event, window);
                    fontConsolasFlag=consolas.isClicked(event,window);
                    fontAzonixFlag=azonix.isClicked(event,window);
                }
                if (changeThemeFlag == 0)
                {
                    changeTheme.setRectColor(darkBack1);
                }
                if (changeFontFlag == 0)
                {
                    changeFont.setRectColor(darkBack1);
                }
            }
        }
        if (changeFontFlag == 1)
        {
            changeFont.setRectColor(buttonColor);
            flag = 1;
            changeFontFlag = 0;
            settingFlag = 1;
        }
        else if (changeThemeFlag == 1)
        {
            changeTheme.setRectColor(buttonColor);
            flag = 2;
            changeThemeFlag = 0;
            settingFlag = 2;
        }
        if(settingFlag==1)
        {
         if (pinkFlag == 1)
        {
            textColor = pink;
            pinkFlag = 0;
        }
        else if (redFlag == 1)
        {
            textColor = errorRed;
            redFlag = 0;
        }
        else if (greenFlag == 1)
        {
            textColor = limeGreen;
            greenFlag = 0;
        }
        else if (whiteFlag == 1)
        {
            textColor = white;
            whiteFlag = 0;
        }
        else if (blueFlag == 1)
        {
            textColor = cursorBlue;
            blueFlag = 0;
        }
        else if (blackFlag == 1)
        {
            textColor = black;
            blackFlag = 0;
        }
        else if (darkTFlag == 1)
        {
            textColor = darkText;
            darkTFlag = 0;
        }
        else if (purpleflag == 1)
        {
            textColor = lightPurple;
            purpleflag = 0;
        }
        else if (pinkBFlag == 1)
        {
            backgroundColor = pink;
            pinkBFlag = 0;
        }
        else if (redBFlag == 1)
        {
            backgroundColor = errorRed;
            redBFlag = 0;
        }
        else if (greenBFlag == 1)
        {
            backgroundColor = limeGreen;
            greenBFlag = 0;
        }
        else if (whiteBFlag == 1)
        {
            backgroundColor = white;
            whiteBFlag = 0;
        }
        else if (blueBFlag == 1)
        {
            backgroundColor = cursorBlue;
            blueBFlag = 0;
        }
        else if (blackFlagB == 1)
        {
            backgroundColor = black;
            blackFlagB = 0;
        }
        else if (menuBackFlag == 1)
        {
            backgroundColor = menuColor;
            menuBackFlag = 0;
        }
        else if (darkBackFlag == 1)
        {
            backgroundColor = atomBackground;
            darkBackFlag = 0;
        }
        }
        else if(settingFlag==2)
        {
            if(fontMenloFlag==1)
            {
                font.loadFromFile("resources/fonts/menlo.ttf");
                fontMenloFlag=0;
            }
            else if(fontMonacoFlag==1)
            {
                font.loadFromFile("resources/fonts/monaco.ttf");
                fontMonacoFlag=0;
            }
            else if(fontConsolasFlag==1)
            {
                font.loadFromFile("resources/fonts/consolas.ttf");
                fontConsolasFlag=0;
            }
            else if(fontAzonixFlag==1)
            {
                font.loadFromFile("resources/fonts/azonix.otf");
                fontAzonixFlag=0;
            }
        }
        if (flag == 1)
        {
        }
        else if (flag == 2)
        {
        }
        window.clear(darkBack5);
        changeFont.draw(window);
        changeTheme.draw(window);
        window.draw(menuRect);
        if (settingFlag == 1)
        {
            pinkButton.draw(window);
            redButton.draw(window);
            whiteButton.draw(window);
            greenButton.draw(window);
            blueButton.draw(window);
            blackButton.draw(window);
            pinkButtonB.draw(window);
            redButtonB.draw(window);
            whiteButtonB.draw(window);
            greenButtonB.draw(window);
            blueButtonB.draw(window);
            blackButtonB.draw(window);
            textColorChanger.draw(window);
            textBackChanger.draw(window);
            menuBackColor.draw(window);
            purpleButton.draw(window);
            darkBackButton.draw(window);
            darktextButton.draw(window);
        }
        else if(settingFlag==2)
        {
            fontChanger.draw(window);
            menlo.draw(window);
            consolas.draw(window);
            monaco.draw(window);
            azonix.draw(window);
        }
        window.display();
    }
}
int fileSaveDialog()
{
    int yesF, noF, cancelF;
    yesF = 0;
    noF = 0;
    cancelF = 0;
    VideoMode vmSave(450, 200);
    RenderWindow saveCheck(vmSave, "Note-Js", Style::None);
    Image image;
    image.loadFromFile("resources/icon.png");
    saveCheck.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    sf::Vector2f questionSize(350, 60), buttonSize(80, 40);
    ButtonRect question(0, 40, questionSize, darkBack1), yes(120, 150, buttonSize, limeGreen), no(220, 150, buttonSize, errorRed), cancel(320, 150, buttonSize, limeGreen);
    question.setFont(font);
    yes.setFont(font);
    no.setFont(font);
    cancel.setFont(font);
    question.setCharacterSize(fontSize);
    yes.setCharacterSize(fontSize);
    no.setCharacterSize(fontSize);
    cancel.setCharacterSize(fontSize);
    question.setText(" Do You Want To Save This File ?");
    yes.setText("  Yes");
    no.setText("  No");
    cancel.setText(" Cancel");
    while (saveCheck.isOpen())
    {
        Event saveEvent;
        while (saveCheck.pollEvent(saveEvent))
        {
            switch (saveEvent.type)
            {
            case Event::Closed:
                saveCheck.close();
                return 2;
                break;
            case sf::Event::MouseButtonPressed:
                yesF = yes.isClicked(saveEvent, saveCheck);
                noF = no.isClicked(saveEvent, saveCheck);
                cancelF = cancel.isClicked(saveEvent, saveCheck);
                break;
            }
        }
        if (yesF == 1)
        {
            saveCheck.close();
            return 1;
        }
        else if (noF == 1)
        {
            saveCheck.close();
            return 0;
        }
        else if (cancelF == 1)
        {
            saveCheck.close();
            return 2;
        }
        saveCheck.clear(darkBack);
        question.draw(saveCheck);
        yes.draw(saveCheck);
        no.draw(saveCheck);
        cancel.draw(saveCheck);
        saveCheck.display();
        if (!saveCheck.hasFocus())
        {
            saveCheck.close();
            return 2;
        }
    }
    return 2;
}
void programRunner()
{
    char command[400];
    DWORD *d;
    d = new DWORD;
    *d = 100;
    char *userName;
    userName = new char[100];
    GetUserNameA(userName, d);
    ShowWindow(hWnd, SW_SHOW);
    Clock clock;
    Time time;
    time = clock.getElapsedTime();
    if (filePath[0] == '\0')
        return;
    //for executing c programs
    system("cls");
    if (filePath[strlen(filePath) - 1] == 'c')
    {
        strcpy(command, "path=c:/mingw/bin;c:/mingw32/bin; && gcc ");
        strcat(command, filePath);
        strcat(command, " -o ");
        strcat(command, filePath);
        command[strlen(command) - 1] = '\0';
        strcat(command, "exe");
        if (system(command) == 0)
        {
            command[0] = '\0';
            strcat(command, filePath);
            command[strlen(command) - 1] = '\0';
            strcat(command, "exe");
            system(command);
        }
    }
    //For executing c++ programs
    else if (filePath[strlen(filePath) - 1] == 'o')
    {
        strcpy(command, "path=c:/windows/system32;c:/mingw/bin;c:/mingw32/bin;c:/python/bin;c:/go/bin; && g++ ");
        strcat(command, filePath);
        strcat(command, " -o ");
        strcat(command, filePath);
        command[strlen(command) - 3] = '\0';
        strcat(command, "exe");
        if (system(command) == 0)
        {
            command[0] = '\0';
            strcat(command, filePath);
            command[strlen(command) - 3] = '\0';
            strcat(command, "exe");
            system(command);
        }
    }
    else if (filePath[strlen(filePath) - 1] == 'y')
    {
        strcpy(command, "path=c:/users/");
        strcat(command, userName);
        strcat(command, "/AppData/Local/Programs/Python/Python38-32; && python ");
        strcat(command, filePath);
        system(command);
    }
    ShowWindow(hWnd, SW_HIDE);
}
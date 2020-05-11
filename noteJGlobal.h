#include "noteJ.h"
using namespace sf;
//Colors Used
sf::Color darkBack1(32, 33, 36), lightBack(255, 255, 255), darkText(30, 30, 30), lightText(193, 204, 204), menuColor(177, 177, 177), magenta(255, 0, 255), bitYellow(130, 104, 34), orange(255, 87, 51), red(228, 66, 54);
sf::Color blue(0, 120, 215), grey(120, 120, 120), lightBlue(37, 204, 247), green(46, 204, 114), grey2(218, 224, 226);
sf::Color darkBack(18, 18, 18), pink(234, 128, 252), darkBack2(27, 28, 34), blue2(61, 80, 250), lightGrey(159, 159, 160);
sf::Color darkWhite(217, 217, 217), boundaryColor(33, 37, 43), textFrameColor(40, 44, 52), scrollerColor(54, 59, 71);
sf::Color textLighter(157, 165, 180), textLighter1(167, 175, 190), cursorBlue(97, 175, 239), limeGreen(152, 195, 121), lightPurple(198, 120, 221), errorRed(224, 108, 117);
sf::Color lightDark(60, 54, 60), atomBackground(40, 44, 52), boundaryLighter(40, 44, 48), darkBack4(40, 44, 54), darkBack5(33, 37, 43), buttonColor(44, 49, 58);;
sf::Color black(0,0,0),white(255,255,255);
//Main Font
sf::Font font;
bool fileSaved;
bool newFile;
bool flagSave=false;
sf::Color textColor=lightPurple;
sf::Color backgroundColor=textFrameColor;
// Function Declaration
std::string readFileToString(std::string filePath);
void writeToFile(std::string string, std::string filePath);
int getSave();
char *getSaveFilePath(HWND windowHandle);
char *openNewFile(HWND windowHandle);
int fileWindow(Vector2f pos, Font &font, int buttonSize);
int formatWindow(Vector2f pos, Font &font, int buttonSize);
int viewWindow(Vector2f pos, Font &font, int buttonSize);
int helpWindow(Vector2f pos, Font &font, int buttonSize);
int editWindow(Vector2f pos, Font &font, int buttonSize);
void selector(sf::Event event, sf::RenderWindow &window, int &number);
void about(sf::Font &font);
int changeFont(int characterSize);
void launchSettingsWindow();
int fileSaveDialog();
int fileWindow(Vector2f pos);
void about();
int formatWindow(Vector2f pos);
int viewWindow(Vector2f pos);
int helpWindow(Vector2f pos);
int editWindow(Vector2f pos);
void programRunner();
int screenWidth = 800;
int screenHeight = 600;
HWND hWnd, compilerWindow;
Vector2u windowResolution;
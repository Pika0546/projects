#ifndef GAMEHEADER
#define GAMEHEADER

#pragma warning (disable:4996)
#pragma warning (disable:0102)

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <thread>
#include <chrono>
#include <random>
#include <conio.h>
#include <fstream>
#include <array>
#include <vector>
#include <math.h>
#include <algorithm>
#include <Windows.h>

using namespace std;
using namespace std::chrono;
#pragma region Forward declaration
struct Coordinate;
struct User;
struct Snake;
struct Food;
struct Map;
struct Object;
struct MovingObject;

enum Direction;
enum class Screen;

#pragma endregion
ostream& operator<<(ostream& os, Screen input);
ostream& operator<<(ostream& os, Direction input);

#pragma region Default const value
// GetKey const value
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ESC 27
#define ENTER 13

#define UP_ -84
#define LEFT_ -81
#define RIGHT_ -79
#define DOWN_ -76

#define P 80
#define p 112
#define s 115
#define S 83

#define BoardWidth 100
#define BoardHeight 30
#define MenuWidth 15
#define MenuHeight 22
#define GameWidth 70
#define GameHeight 20

#define BoardOrigin_x 0
#define BoardOrigin_y 0
#define MenuOrigin_x 6
#define MenuOrigin_y 4
#define InteractOrigin_x 25
#define InteractOrigin_y 5

#define DownStateBoard_x 7
#define DownStateBoard_y 25
#define UpStateBoard_x 7
#define UpStateBoard_y 5
#define DrawFood_x 7
#define DrawFood_y 10
#define DrawTime_x 7
#define DrawTime_y 15
#define StateBoard_Width 14
#define StateBoard_Height 21

#define OutPortal_x 26
#define OutPortal_y 15

#define End_x 0
#define End_y 31

#define AbMenu_x 4
#define AbMenu_y 1
#define InMenu_x 7
#define InMenu_y 5
#define AbScreen_x 27
#define AbScreen_y 1
#define BlScreen_x 27
#define BlScreen_y 27

#define BlankSpace u8"                                                    "
#define InfiSecond 1000000s
#pragma endregion

#pragma region GotoXy
void gotoXY(int, int);
void gotoXY(Coordinate Where);
#pragma endregion

#pragma region Update
struct Coordinate
{
	int x, y; //dòng - cột
};

bool operator==(Coordinate a, Coordinate b);
Direction operator!(Direction a);

enum Direction
{
	Up, Down, Left, Right, All
};

struct Map
{
	int Level;
	int FoodEaten;
	seconds Timeleft;

	Coordinate* MapWall;
	Coordinate* Portal;
	Coordinate inPortal = { 0,0 };
	bool Portalable = true;
	bool Outable = true;
	int BaseLength[5] = { 4,8,16,24,32 };
	int TotalWall[5] = { 0, 60, 113, 81,0 };

	Coordinate Level_2[60] = { {46, 13}, {47, 13}, {48, 13}, {49, 13},{50, 13}, {51,13}, {52,13}, {53,13}, {54,13}, {55,13}, {56,13}, {56,12}, {56,11}, {56,10}, {56, 9}, {62, 9}, {62, 10}, {62, 11}, {62, 12}, {62, 13}, {63, 13}, {64, 13}, {65, 13}, {66, 13}, {67, 13},{68, 13}, {69, 13}, {70, 13}, {71, 13}, {72, 13},{46, 17}, {47, 17}, {48, 17}, {49, 17}, {50, 17}, {51, 17}, {52, 17}, {53, 17}, {54, 17}, {55, 17}, {56, 17}, {56, 18}, {56, 19}, {56, 20}, {56, 21}, {62, 21}, {62, 20}, {62, 19}, {62, 18}, {62, 17}, {63, 17}, {64, 17}, {65, 17}, {66, 17}, {67, 17}, {68, 17}, {69, 17}, {70, 17}, {71, 17}, {72, 17} };
	Coordinate Level_3[113] = { {45, 9} ,{75, 21} ,{75, 9}, {59, 21}, {45, 15}, {56, 15}, {75, 21}, {74, 21}, {46, 9}, {73, 21}, {47, 9}, {72, 21} ,{48, 9} ,{71, 21} ,{49, 9} ,{70, 21}, {50, 9}, {69, 21} ,{51, 9}, {68, 21}, {52, 9} ,{67, 21} ,{53, 9} ,{66, 21}, {54, 9} ,{65, 21} ,{55, 9} ,{64, 21} ,{56, 9} ,{63, 21} ,{57, 9} ,{62, 21} ,{58, 9}, {61, 21}, {59, 9}, {60, 21} ,{60, 9}, {59, 21} ,{61, 9} ,{58, 21}, {62, 9}, {57, 21}, {63, 9} ,{56, 21} ,{64, 9}, {55, 21}, {65, 9}, {54, 21} ,{66, 9}, {53, 21} ,{67, 9}, {52, 21}, {68, 9}, {51, 21} ,{69, 9} ,{50, 21} ,{70, 9} ,{49, 21}, {71, 9} ,{48, 21} ,{72, 9}, {47, 21}, {73, 9} ,{46, 21} ,{74, 9} ,{45, 21} ,{75, 9}, {44, 21}, {76, 9}, {43, 21} ,{77, 9} ,{42, 21}, {78, 9}, {41, 21}, {79, 9}, {40, 21}, {80, 9}, {75, 16}, {45, 14} ,{75, 17}, {45, 13}, {75, 18} ,{45, 12}, {75, 19}, {45, 11}, {75, 20}, {45, 10} ,{75, 15}, {65, 15}, {55, 15}, {66, 15} ,{54, 15} ,{67, 15}, {53, 15}, {68, 15} ,{52, 15}, {69, 15} ,{51, 15} ,{70, 15}, {50, 15} ,{71, 15}, {49, 15}, {72, 15}, {48, 15}, {73, 15} ,{47, 15} ,{74, 15} ,{46, 15}, {64, 15}, {64, 17}, {56, 14}, {64, 16},{56, 13} };
	Coordinate Level_4[81] = { {32,6},  {88,21}, {32,7},  {88,22}, {32,8},  {88,23}, {32,9},  {88,24}, {32,5},  {88,25}, {89,10}, {26,20},{90,10},{27,20},{91,10},{28,20},{92,10},{29,20},{93,10},{30,20},{94,10},{31,20},{95,10},{25,20},{60,12},{60,13},{60,14},{60,15},{60,16},{60,17},{60,18},{59,14},{61,16},{58,14},{62,16},{57,14},{63,16},{56,14},{64,16},{55,14},{65,16},{54,14},{66,16},{53,14},{67,16},{52,14},{68,16},{51,14},{69,16},{50,14},{70,16},{49,14},{71,16},{48,14},{72,16},{47,14},{73,16},{46,14},{74,16},{45,14},{75,16},{44,14},{76,16},{43,14},{77,16},{42,14},{78,16},{41,14},{79,16},{40,14},{80,16},{39,14},{81,16},{38,14},{82,16},{37,14},{83,16},{36,14},{84,16},{35,14},{85,16} };
	Map();
	void drawLevelWall();
	void drawLevel_2();
	void drawLevel_3();
	void drawLevel_4();

	void drawLevel();

	bool isHitMap(Coordinate Where);
	bool isMapWall(Coordinate Where);
	bool isPortal(Coordinate Where);
	bool isEnough();
	bool isOutOfPortal(Snake snake);
	bool isSnakeArea(Snake activeSnake);

	void createPortal(Snake snake);
	void drawPortal(int Color = 244);
	void drawBegin();
	void clearPortal();

	void drawEnterAnimation(Snake& snake);
	void clearEntrance();

	int getBaseLength();

	void CreateMap();
	void resetbyPasslevel();
	void reset();
	void deleteMap();
};

struct Snake
{
	string MSSV = "19120476191204791912054619120573";

	Coordinate* snake;
	Coordinate tail;
	int length;
	int value;
	bool Death;
	Direction direction;
	milliseconds Speed;

	Snake();

	void eat(int addvalue = 0);
	void move();
	void changeDirection(Direction);
	void setBegin(Map map);

	bool isDeath(Object object, Map map);

	bool isSnake(Coordinate Where);
	bool isSnakeBody(Coordinate Where);
	bool isGrass(Coordinate Where, Object object, Map map);

	Coordinate WhereisHit(Object object);

	bool isInPortal(Map map);

	void resetbyPasslevel();

	void draw(int from = 0);

	void deathAnimation(Coordinate Where);
	void reset();
	void deleteSnake();
};

struct Food
{
	Coordinate* food;
	int total;

	Food();

	void firstGenerate(Snake snake, Object object, Map map);
	void Generate(Snake snake, Object object, Map map, int num = 0);
	void timeGenerate(Snake snake, Object object, Map map);
	void eaten(Snake snake, Object object, Map map, Coordinate Where = { -1,-1 });

	bool isFood(Coordinate Where);

	void draw(int Pos = -1);
	void drawDelete();
	void reset();
	void resetbyPasslevel();

	void deleteFood();
};

struct Object
{
	// Default Orbit
	Coordinate Orbit_4[132] = { {32, 10}, {33, 10}, {34, 10}, {35, 10}, {36, 10}, {37, 10}, {38, 10}, {39, 10}, {40, 10}, {41, 10}, {42, 10}, {43, 10}, {44, 10}, {45, 10}, {46, 10}, {47, 10}, {48, 10}, {49, 10}, {50, 10}, {51, 10}, {52, 10}, {53, 10}, {54, 10}, {55, 10}, {56, 10}, {57, 10}, {58, 10}, {59, 10}, {60, 10}, {61, 10}, {62, 10}, {63, 10}, {64, 10}, {65, 10}, {66, 10}, {67, 10}, {68, 10}, {69, 10}, {70, 10}, {71, 10}, {72, 10}, {73, 10}, {74, 10}, {75, 10}, {76, 10}, {77, 10}, {78, 10}, {79, 10}, {80, 10}, {81, 10}, {82, 10}, {83, 10}, {84, 10}, {85, 10}, {86, 10}, {87, 10}, {88, 10}, {88, 11}, {88, 12}, {88, 13}, {88, 14}, {88, 15}, {88, 16}, {88, 17}, {88, 18}, {88, 19}, {88, 20}, {87, 20}, {86, 20}, {85, 20}, {84, 20}, {83, 20}, {82, 20}, {81, 20}, {80, 20}, {79, 20}, {78, 20}, {77, 20}, {76, 20}, {75, 20}, {74, 20}, {73, 20}, {72, 20}, {71, 20}, {70, 20}, {69, 20}, {68, 20}, {67, 20}, {66, 20}, {65, 20}, {64, 20}, {63, 20}, {62, 20}, {61, 20}, {60, 20}, {59, 20}, {58, 20}, {57, 20}, {56, 20}, {55, 20}, {54, 20}, {53, 20}, {52, 20}, {51, 20}, {50, 20}, {49, 20}, {48, 20}, {47, 20}, {46, 20}, {45, 20}, {44, 20}, {43, 20}, {42, 20}, {41, 20}, {40, 20}, {39, 20}, {38, 20}, {37, 20}, {36, 20}, {35, 20}, {34, 20}, {33, 20}, {32, 20}, {32, 19}, {32, 18}, {32, 17}, {32, 16}, {32, 15}, {32, 14}, {32, 13}, {32, 12}, {32, 11} };
	int* Current;

	// Base variables
	Coordinate* object;
	int total;
	bool eatable;
	// State variable
	vector<bool> flag;
	void setflag();
	void deleteflag();

	Object();
	Object(Coordinate* Current, int total, bool eatable);

	void reGenerate(Snake snake, Food food, Map map, Coordinate Pos = { -1,-1 });
	void addTimeFood(Snake snake, Food food, Map map);

	void draw();
	void drawBegin();
	void drawDelete(bool canDelete = false);
	void move(Snake snake, Food food, Map map);

#pragma region External
	bool waitObject(milliseconds time);
#pragma endregion

	int locate(Coordinate Where);

	bool isObject(Coordinate Where);
	bool isObject(Snake snake);
	bool isObject(Coordinate* snakebody, int length);
	bool isOrbit(Coordinate Where);

	bool isTimeFood(Coordinate Where);

	void beginWithLevel(Snake snake, Food food, Map map);

	void reset();

	void deleteObject();
};

#pragma endregion

#pragma region Render
// enum
enum class Screen
{
	StartGame,
	LoadGame,
	HighScore,
	Tutorial_n_Introduction,
	ExitGame,
};
enum class NumberPos
{
	Left, Right, Mid
};

// Draw Egde
void drawMenuBoard(int Color = 251);
void drawInteractBoard(int Color = 249);

//Menu
void drawStartingMenu();
void drawMenuOptions();
void drawSelectedOption(int Selected);

void drawStartGameScreen();
void drawLoadGameScreen(User* user);
void drawIntroduction();
void drawExit();
void QuitGame();

Screen Option(Screen& input, char MainKey);


void clearInteractScreen(int x = InteractOrigin_x + 1, int y = InteractOrigin_y + 1, int width = GameWidth - 1, int height = GameHeight - 1);
void clearMenuScreen(int x = UpStateBoard_x, int y = UpStateBoard_y, int width = 14, int height = 21);
void clearBelowScreen();

// Load Game
int showLoadGame(User* user_arr);
// High Score
void showHighScore(User* users);
// Pause
bool showPause();
// Ready
void Ready(User user);
// Next Level
void ReadyLevel(User user);

// Base draw

void drawAboveMenu(const char* Line1 = u8"       ", const char* Line2 = u8"       ", const char* Line3 = u8"       ");
void drawInMenu(const char* Write, int Line);
void drawAboveScreen(const char* Line1 = BlankSpace, const char* Line2 = BlankSpace, const char* Line3 = BlankSpace, const char* Line4 = BlankSpace);
void drawBelowScreen(const char* Line1 = BlankSpace, const char* Line2 = BlankSpace, const char* Line3 = BlankSpace, const char* Line4 = BlankSpace);

void clearAboveScreen();


void drawBoard(int height, int width, int posX, int posY);
void drawSnakeTitle();
void drawLoadGameTitle();
void drawHighScoreTitle();
void drawIntroductionTitle();
void drawExitGameTitle();
void drawGoodByeTitle();
#pragma endregion

#pragma region User

struct User
{
	static int totalUser;
	string Name;

	int Score;
	tm Timesave;

	int HighScore;
	tm Deathsave;

	Snake userSnake;
	Food userFood;
	Object userObject;
	Map userMap;

	User();
	static void getAllInfo(User*& gameUsers);
	static void checkAllInfo(User*& gameUsers);
	static void getBasicInfo(User*& gameUsers);
	static void checkBasicInfo(User*& gameUsers);
	static void saveBasicInfo(User*& gameUsers);
	static void deleteUsers(User*& gameUsers);
	static void push_backUser(User newUser, User*& gameUsers);
	static void SavetoArr(User oldUser, User*& gameUsers);

	void getInfo();
	void checkInfo();
	void saveInfo();
	void saveHighScore();

	bool isUser();
	bool isReset();
	bool isAlreadyUser(User* gameUsers);

	void reCreate();
	void reset();
	void clearInfo();
	void freeUser();

	bool saveUser();
	void resultOnDeath();

	void copyUser(User Out);

#pragma region render Gameplay
	void drawBeginLevelState();
	void drawLevelState();
	void drawTimeNumber(seconds time);
	template<class T>
	void drawNote(T Note)
	{
		gotoXY(DrawTime_x, DrawTime_y + 6);
		cout << Note;
	}
#pragma endregion


};

#pragma endregion


#pragma region Algorithm
void FixConsoleWindow();
void resizeConsole(int height, int width);
void ShowConsoleCursor(bool showFlag);
int Distance(Coordinate a, Coordinate b);

void setTextColor(int color = 240);

int getRandNumber(int, int);
template<class T> T getRandAmong(vector<T> Arr)
{
	random_device seed;
	mt19937 randNum(seed());
	uniform_int_distribution<int> randRange(0, Arr.size() - 1);
	int posResult = randRange(randNum);
	return Arr[posResult];
}
bool getRandBool();

void GetKey(char& Key);
void GetManyKey(char& Key);
void GetUpgradeManyKey(char& Key);
void GetWaitKey(char& Key);
void GetWaitManyKey(char& Key);
void GetUpgradeWaitKey(char& Key);
void GetSelectedKey(char& Key, vector<char> sKey);
void GetScreenKey(char& Key, Screen screen);

bool is_leap_year(int y);
int DateToDay(tm time);

bool isMoveableGround(Coordinate Where, Snake snake, Food food, Object object, Map map);
bool isGround(Coordinate Where, Snake snake, Food food, Object object, Map map);
bool isGround(Coordinate Where, Snake snake, Object object, Map map);
bool isGround(Coordinate Where, Snake snake, Food food, Map map);
bool isSpawnFood(Coordinate Where, Snake snake, Object object, Map map);
bool isWall(Coordinate Where);
bool isName(const string& Instring);
Direction facing(Coordinate Portal);

Screen ItoScr(int input);
int ScrtoI(Screen input);
char DtoK(Direction input);


string operator*(string a, int b);

void SortUserArrDate(User* a, int R = -1, int L = 0);
#pragma endregion

#pragma region Time
tm getNow();
tm correctNow(tm Now);
bool wait(seconds);
bool wait(milliseconds);
bool waitPause(milliseconds time);
bool waitAddtime(milliseconds time);
bool waitClock(milliseconds time);
bool countdown(seconds& timeleft, bool reset = false);
bool stop(milliseconds);
#pragma endregion


#endif
#pragma once

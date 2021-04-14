#include "GameHeader.h"
#include "SoundHeader.h"

#pragma region Console Window
void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void gotoXY(Coordinate Where)
{
	COORD coord;
	coord.X = Where.x;
	coord.Y = Where.y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void resizeConsole(int height, int width)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

int Distance(Coordinate a, Coordinate b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}
#pragma endregion

#pragma region Color
void setTextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
#pragma endregion

#pragma region Random
int getRandNumber(int from, int to)
{
	random_device seed;
	mt19937 randNum(seed());
	uniform_int_distribution<int> randRange(from, to);
	int result = randRange(randNum);
	return result;
}

bool getRandBool()
{
	random_device seed;
	mt19937 randNum(seed());
	uniform_int_distribution<int> randRange(0, 1);
	bool result = randRange(randNum);
	return result;
}
#pragma endregion

#pragma region Basic interact Keyboard
void GetKey(char& Key)
{
	if (!_kbhit())
	{
		Key = _getch();
		if (Key == -32) Key = _getch();
	}
}

void GetManyKey(char& Key)
{
	if (!_kbhit())
	{
		Key = _getch();
		if (Key == -32) Key = _getch();
	}
	while (_kbhit())
	{
		Key = _getch();
		if (Key == -32) Key = _getch();
	}

}

void GetUpgradeManyKey(char& Key)
{
	if (!_kbhit())
	{
		Key = _getch();
		if (Key == -32) Key = _getch() + 100;
	}
	while (_kbhit())
	{
		Key = _getch();
		if (Key == -32) Key = _getch() + 100;
	}
}

void GetWaitKey(char& Key)
{
	if (_kbhit())
	{
		Key = _getch();
		if (Key == -32) Key = _getch();
	}
}

void GetWaitManyKey(char& Key)
{
	Key = NULL;
	int flag = 0;
	do
	{
		GetWaitKey(Key);
		flag++;
	} while (Key == NULL && flag <= 100);
}

void GetUpgradeWaitKey(char& Key)
{
	if (_kbhit())
	{
		Key = _getch();
		if (Key == -32) Key = _getch() + 100;
	}
}

void GetSelectedKey(char& Key, vector<char> sKey)
{
	auto isKey = [&]() -> bool
	{
		for (int i = 0; i < sKey.size(); i++)
		{
			if (Key == sKey[i]) return true;
		}
		return false;
	};

	do
	{
		GetUpgradeManyKey(Key);
	} while (!isKey());
}

void GetScreenKey(char& Key, Screen screen)
{
	switch (screen)
	{
	case Screen::StartGame:
		GetSelectedKey(Key, vector<char> {DOWN_, ENTER});
		return;
	case Screen::LoadGame:
		GetSelectedKey(Key, vector<char> {UP_,DOWN_,RIGHT_,ENTER});
		return;
	case Screen::HighScore:
		GetSelectedKey(Key, vector<char> {UP_, DOWN_});
		return;
	case Screen::Tutorial_n_Introduction:
		GetSelectedKey(Key, vector<char> {UP_, DOWN_});
		return;
	case Screen::ExitGame:
		GetSelectedKey(Key, vector<char> {UP_, ENTER});
		return;
	}
}
#pragma endregion

#pragma region Time up to
bool is_leap_year(int y) // No forward declaration
{
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int DateToDay(tm time) // No forward declaration
{
	int md[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int day = time.tm_mday;
	int month = time.tm_mon;
	int year = time.tm_year;
	if (is_leap_year(year))
		md[1] = 29;
	int sum = day;
	for (int i = 0; i < month; i++)
	{
		sum += md[i];
	}
	for (int i = 1900; i < year; i++)
	{
		sum += 365;
		if (is_leap_year(i))
			sum += 1;
	}
	return sum;
}
#pragma endregion

#pragma region Update Algorithm
bool isMoveableGround(Coordinate Where, Snake snake, Food food, Object object, Map map)
{
	if (isWall(Where)) return false;
	if (snake.isSnake(Where)) return false;
	if (food.isFood(Where)) return false;
	if (object.isObject(Where)) return false;
	if (map.isMapWall(Where)) return false;
	return true;
}

bool isGround(Coordinate Where, Snake snake, Food food, Object object, Map map) // Check spawn food
{
	if (snake.isSnake(Where)) return false;
	if (food.isFood(Where)) return false;
	if (object.isObject(snake)) return false;
	if (object.isOrbit(Where)) return false;
	if (map.isMapWall(Where)) return false;
	return true;
}

bool isGround(Coordinate Where, Snake snake, Object object, Map map)
{
	if (snake.isSnake(Where)) return false;
	if (object.isObject(snake)) return false;
	if (object.isOrbit(Where)) return false;
	if (map.isMapWall(Where)) return false;
	if (map.isPortal(Where)) return false;
	return true;
}

bool isSpawnFood(Coordinate Where, Snake snake, Object object, Map map)
{
	if (snake.isSnake(Where)) return false;
	if (object.isObject(Where)) return false;
	if (object.isOrbit(Where)) return false;
	if (map.isMapWall(Where)) return false;
	if (map.isPortal(Where)) return false;
	return true;
}

bool isGround(Coordinate Where, Snake snake, Food food, Map map) // Check spawn time food
{
	if (snake.isSnake(Where)) return false;
	if (food.isFood(Where)) return false;
	if (map.isMapWall(Where)) return false;
	return true;
}

bool isWall(Coordinate Where)
{
	if (Where.x <= InteractOrigin_x || Where.x >= InteractOrigin_x + GameWidth ||
		Where.y <= InteractOrigin_y || Where.y >= InteractOrigin_y + GameHeight) return true;
	else return false;
}

bool isName(const string& Instring)
{
	int n = Instring.size();
	if (n > 15)
		return false;
	bool a1 = 1, a2 = 1, a3 = 1;
	for (auto i : Instring)
	{
		if (!((i <= 'z' && i >= 'a') || (i <= 'Z' && i >= 'A') || (i <= '9' && i >= '0')))
			return false;
	}
	return true;
}

Direction facing(Coordinate Portal)
{
	if (InteractOrigin_x < Portal.x && Portal.x < InteractOrigin_x + GameWidth)
	{
		if (Portal.y == InteractOrigin_y) return Direction::Down;
		else return Direction::Up;
	}
	else
	{
		if (Portal.x == InteractOrigin_x) return Direction::Right;
		else return Direction::Left;
	}
}
#pragma endregion

#pragma region Convert
Screen ItoScr(int input)
{
	switch (input)
	{
	case 1: return Screen::StartGame;
	case 2: return Screen::LoadGame;
	case 3: return Screen::HighScore;
	case 4: return Screen::Tutorial_n_Introduction;
	case 5: return Screen::ExitGame;
	default: return Screen::StartGame;
	}
}

int ScrtoI(Screen input)
{
	switch (input)
	{
	case Screen::StartGame: return 1;
	case Screen::LoadGame: return 2;
	case Screen::HighScore: return 3;
	case Screen::Tutorial_n_Introduction: return 4;
	case Screen::ExitGame: return 5;
	default: return 1;
	}
}

char DtoK(Direction input)
{
	switch (input)
	{
	case Up: return UP_;
	case Down: return DOWN_;
	case Left: return LEFT_;
	case Right: return RIGHT_;
	default: return RIGHT_;
	}
}
#pragma endregion

#pragma region OverRide
string operator*(string a, int b)
{
	string result = "";
	for (int i = 0; i < b; i++) result += a;
	return result;
}

ostream& operator<<(ostream& os, Screen input)
{
	os << ScrtoI(input);
	return os;
}

ostream& operator<<(ostream& os, Direction input)
{
	switch (input)
	{
	case Up:	 os << "Up"; return os;
	case Down:	 os << "Down"; return os;
	case Left:	 os << "Left"; return os;
	case Right:	 os << "Right"; return os;
	}
}

Direction operator!(Direction a)
{
	switch (a)
	{
	case Up:	return Direction::Down;
	case Down:	return Direction::Up;
	case Left:	return Direction::Right;
	case Right:	return Direction::Left;
	}
}

bool operator==(Coordinate a, Coordinate b)
{
	if (a.x == b.x && a.y == b.y) return true;
	else return false;
}
#pragma endregion


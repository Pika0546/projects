#include "GameHeader.h"
#include "SoundHeader.h"

#pragma region Animation
void Snake::draw(int from)
{
	setTextColor(253);
	for (int i = from; i < length; i++)
	{
		gotoXY(snake[i].x, snake[i].y);
		if (i != 0) setTextColor(246);
		cout << MSSV[i % 32];
	}
	if (snake == nullptr) return;
	if (tail.x == snake[length - 1].x && tail.y == snake[length - 1].y && from == 0) return;
	gotoXY(tail.x, tail.y);
	cout << " ";
}

void Snake::deathAnimation(Coordinate Where)
{
	if (Where == snake[0]) sound.playLose1();
	else sound.playLose2();
	gotoXY(tail.x, tail.y);
	cout << " ";
	setTextColor(252);
	for (int time = 0; time < 14; time++)
	{
		if (time % 2 == 0)
			for (int i = 0; i < length; i++)
			{
				gotoXY(snake[i].x, snake[i].y);
				if (snake[i] == Where) cout << u8"◊";
				else cout << MSSV[i % 32];
			}
		else
			for (int i = 0; i < length; i++)
			{
				gotoXY(snake[i].x, snake[i].y);
				cout << " ";
			}
		stop(100ms);
	}
}

void Food::draw(int Pos)
{
	if (food == nullptr) return;

	setTextColor(242);
	if (Pos == -1)
	{
		for (int i = 0; i < total; i++)
		{
			gotoXY(food[i].x, food[i].y); cout << u8"■";
		}
		return;
	}
	gotoXY(food[Pos].x, food[Pos].y); cout << u8"■";
	return;
}

void Food::drawDelete()
{
	if (food == nullptr) return;
	for (int i = 0; i < total; i++)
	{
		gotoXY(food[i]); cout << " ";
	}
	total = 0;
}
#pragma endregion

#pragma region Object
void Object::draw()
{
	if (eatable) setflag();
	for (int i = 0; i < total; i++)
	{
		gotoXY(object[i]);
		if (eatable)
		{
			setTextColor(253);
			if (flag[i]) cout << u8"֎";
			else cout << u8"҉";
		}
		else
		{
			setTextColor(252);
			if (0 <= Current[i] && Current[i] < 56) cout << u8"►";
			if (56 <= Current[i] && Current[i] < 66) cout << u8"▼";
			if (66 <= Current[i] && Current[i] < 122) cout << u8"◄";
			if (122 <= Current[i] && Current[i] <= 132) cout << u8"▲";

			setTextColor(244);

			int BackOrbit_1 = Current[i] - 1;
			gotoXY(Orbit_4[(BackOrbit_1 < 0) ? 131 : BackOrbit_1]);
			if ((0 < BackOrbit_1 && BackOrbit_1 < 56) || (66 < BackOrbit_1 && BackOrbit_1 < 122)) cout << u8"═";
			if ((56 < BackOrbit_1 && BackOrbit_1 < 66) || (122 < BackOrbit_1 && BackOrbit_1 < 131))  cout << u8"║";
			if (0 == BackOrbit_1) cout << u8"╔";
			if (56 == BackOrbit_1) cout << u8"╗";
			if (66 == BackOrbit_1) cout << u8"╝";
			if (122 == BackOrbit_1) cout << u8"╚";

			int BackOrbit_2 = Current[i] - 2;
			gotoXY(Orbit_4[(BackOrbit_2 < 0) ? BackOrbit_2 + 132 : BackOrbit_2]);
			if (0 <= BackOrbit_2 && BackOrbit_2 < 56) cout << u8"╠";
			if (56 <= BackOrbit_2 && BackOrbit_2 < 66) cout << u8"╦";
			if (66 <= BackOrbit_2 && BackOrbit_2 < 122) cout << u8"╣";
			if (122 <= BackOrbit_2 && BackOrbit_2 < 132) cout << u8"╩";
		}
	}
}
void Object::drawBegin()
{
	draw();
}
void Object::drawDelete(bool canDelete)
{
	if (object == nullptr) return;
	for (int i = 0; i < total; i++)
	{
		gotoXY(object[i]); cout << " ";
		if (!eatable)
		{
			gotoXY(Orbit_4[(Current[i] - 1 < 0) ? 131 : Current[i] - 1]); cout << " ";
			gotoXY(Orbit_4[(Current[i] - 2 < 0) ? Current[i] - 2 + 132 : Current[i] - 2]); cout << " ";
		}
	}
	if (canDelete)
	{
		object = nullptr;
		total = 0;
	}
}
#pragma endregion

#pragma region Map
void Map::drawPortal(int Color)
{
	setTextColor((Color - 1 < 240) ? 254 : Color - 1);
	gotoXY(inPortal.x, inPortal.y); cout << u8"⃝";
	setTextColor(Color);
	switch (facing(inPortal))
	{
	case Direction::Down:
		gotoXY(Portal[0]); cout << u8"╔";
		gotoXY(Portal[1]); cout << u8"╗";
		gotoXY(Portal[2]); cout << u8"║";
		gotoXY(Portal[3]); cout << u8"║";
		gotoXY(Portal[4]); cout << u8"╩";
		gotoXY(Portal[5]); cout << u8"╩";
		break;
	case Direction::Up:
		gotoXY(Portal[0]); cout << u8"╚";
		gotoXY(Portal[1]); cout << u8"╝";
		gotoXY(Portal[2]); cout << u8"║";
		gotoXY(Portal[3]); cout << u8"║";
		gotoXY(Portal[4]); cout << u8"╦";
		gotoXY(Portal[5]); cout << u8"╦";
		break;
	case Direction::Right:
		gotoXY(Portal[0]); cout << u8"╔";
		gotoXY(Portal[1]); cout << u8"╚";
		gotoXY(Portal[2]); cout << u8"═";
		gotoXY(Portal[3]); cout << u8"═";
		gotoXY(Portal[4]); cout << u8"╣";
		gotoXY(Portal[5]); cout << u8"╣";
		break;
	case Direction::Left:
		gotoXY(Portal[0]); cout << u8"╗";
		gotoXY(Portal[1]); cout << u8"╝";
		gotoXY(Portal[2]); cout << u8"═";
		gotoXY(Portal[3]); cout << u8"═";
		gotoXY(Portal[4]); cout << u8"╠";
		gotoXY(Portal[5]); cout << u8"╠";
		break;
	}
}
void Map::drawBegin()
{

	setTextColor(253); gotoXY(OutPortal_x - 1, OutPortal_y - 1); cout << u8"»";
	setTextColor(251); gotoXY(OutPortal_x - 1, OutPortal_y); cout << u8"Ͼ";
	setTextColor(253); gotoXY(OutPortal_x - 1, OutPortal_y + 1); cout << u8"»";
}

void Map::drawEnterAnimation(Snake& snake)
{
	for (int i = 0, color = 252; i < snake.length; i++, color++)
	{
		snake.snake[i] = inPortal;
		if (color > 254) color = 252;
		setTextColor(color);
		drawBoard(GameHeight, GameWidth, InteractOrigin_x, InteractOrigin_y);
		drawPortal(color);
		snake.draw(i);
		snake.move();
		stop(30ms);
	}
}

void Map::clearEntrance()
{
	drawInteractBoard();
	Outable = false;
}

void Map::drawLevelWall()
{
	switch (Level % 5)
	{
	case 1: return;
	case 2: drawLevel_2(); return;
	case 3: drawLevel_3(); return;
	case 4: drawLevel_4(); return;
	case 0: return;
	default:
		return;
	}
}
void Map::drawLevel_2()
{
	clearInteractScreen();
	for (int i = 9; i <= 13; i++) {
		gotoXY(56, i);
		cout << u8"║";
		gotoXY(62, i);
		cout << u8"║";
	}
	for (int i = 17; i <= 21; i++) {
		gotoXY(56, i);
		cout << u8"║";
		gotoXY(62, i);
		cout << u8"║";
	}
	for (int i = 46; i <= 56; i++) {
		gotoXY(i, 13);
		cout << u8"═";
		gotoXY(i, 17);
		cout << u8"═";
	}
	for (int i = 62; i <= 72; i++) {
		gotoXY(i, 13);
		cout << u8"═";
		gotoXY(i, 17);
		cout << u8"═";
	}
	gotoXY(56, 13);     cout << u8"╝";
	gotoXY(62, 13);     cout << u8"╚";
	gotoXY(56, 17);     cout << u8"╗";
	gotoXY(62, 17);     cout << u8"╔";
}
void Map::drawLevel_3()
{

	gotoXY(InteractOrigin_x + 20, InteractOrigin_y + 4); cout << u8"╔";

	gotoXY(InteractOrigin_x + 50, InteractOrigin_y + 16); cout << u8"╝";

	gotoXY(InteractOrigin_x + 50, InteractOrigin_y + 4); cout << u8"╗";

	gotoXY(InteractOrigin_x + 34, InteractOrigin_y + 16); cout << u8"╚";

	gotoXY(InteractOrigin_x + 20, InteractOrigin_y + 10); cout << u8"╚";

	gotoXY(InteractOrigin_x + 31, InteractOrigin_y + 10); cout << u8"╝";

	gotoXY(InteractOrigin_x + 50, InteractOrigin_y + 16); cout << u8"╝";

	for (int i = 1; i <= 35; i++)
	{
		gotoXY(InteractOrigin_x + 50 - i, InteractOrigin_y + 16); cout << u8"═";
		gotoXY(InteractOrigin_x + 20 + i, InteractOrigin_y + 4); cout << u8"═";
	}

	for (int i = 1; i <= 5; i++)
	{
		gotoXY(InteractOrigin_x + 50, InteractOrigin_y + 10 + i); cout << u8"║";
		gotoXY(InteractOrigin_x + 20, InteractOrigin_y + 10 - i); cout << u8"║";
	}

	gotoXY(InteractOrigin_x + 50, InteractOrigin_y + 10); cout << u8"╗";

	for (int i = 1; i <= 10; i++)
	{
		gotoXY(InteractOrigin_x + 39 + i, InteractOrigin_y + 10); cout << u8"═";
		gotoXY(InteractOrigin_x + 31 - i, InteractOrigin_y + 10); cout << u8"═";
	}

	gotoXY(InteractOrigin_x + 39, InteractOrigin_y + 10); cout << u8"╔";

	for (int i = 1; i <= 2; i++)
	{
		gotoXY(InteractOrigin_x + 39, InteractOrigin_y + 13 - i); cout << u8"║";
		gotoXY(InteractOrigin_x + 31, InteractOrigin_y + 10 - i); cout << u8"║";
	}
}
void Map::drawLevel_4()
{

#pragma region Default variables
	const int ObjectX = InteractOrigin_x + 7;
	const int ObjectY = InteractOrigin_y + 5;
	const int ObjectW = GameWidth - 14;
	const int ObjectH = GameHeight - 10;
	const int WallSizeY = 3 + 1;
	const int WallSizeX = 4 + 2;
	const int FirstItemX = ObjectX;
	const int FirstItemY = InteractOrigin_y;
	const int SecItemX = ObjectX + ObjectW;
	const int SecItemY = ObjectY;
	const int ThItemX = ObjectX + ObjectW;
	const int ThItemY = ObjectY + ObjectH;
	const int FoItemX = InteractOrigin_x;
	const int FoItemY = ObjectY + ObjectH;
#pragma endregion

	//2 tường đứng
	for (int i = 1; i <= WallSizeY; i++)
	{
		gotoXY(FirstItemX, FirstItemY + i);
		cout << u8"║";
		gotoXY(ThItemX, ThItemY + i);
		cout << u8"║";
	}
	gotoXY(FirstItemX, FirstItemY);
	cout << u8"╦";
	gotoXY(ThItemX, ThItemY + WallSizeY + 1);
	cout << u8"╩";
	//2 tường ngang
	for (int i = 1; i <= WallSizeX; i++)
	{
		gotoXY(SecItemX + i, SecItemY);
		cout << u8"═";
		gotoXY(FoItemX + i, FoItemY);
		cout << u8"═";
	}
	gotoXY(SecItemX + WallSizeX + 1, SecItemY);
	cout << u8"╣";
	gotoXY(FoItemX, FoItemY);
	cout << u8"╠";

	//Bảng quỹ đạo
	//drawBoard(ObjectH, ObjectW, ObjectX, ObjectY);

	//Dấu cộng
	for (int i = 1; i <= 7; i++)
	{
		gotoXY(ObjectX + ObjectW / 2, ObjectY + 1 + i);
		if (i == 3)
			cout << u8"╣";
		else if (i == 5)
			cout << u8"╠";
		else
			cout << u8"║";
	}
	for (int i = 1; i <= 25; i++)
	{
		gotoXY(ObjectX + ObjectW / 2 - i, ObjectY + 4);
		cout << u8"═";
		gotoXY(ObjectX + ObjectW / 2 + i, ObjectY + 6);
		cout << u8"═";
	}
}
#pragma endregion

#pragma region Menu
// ---> Draw egde
void drawMenuBoard(int Color)
{
	setTextColor(Color);
	drawBoard(MenuHeight, MenuWidth, MenuOrigin_x, MenuOrigin_y);
	setTextColor();
}

void drawInteractBoard(int Color)
{
	setTextColor(Color);
	drawBoard(GameHeight, GameWidth, InteractOrigin_x, InteractOrigin_y);
	setTextColor();
}

// ---> Draw Opening 
void drawSnakeIntro1(int i) {
	setTextColor(250);
	gotoXY(17 + i, 6);  cout << u8"        ▄■■■■■■■■▄                                                                   ";
	gotoXY(17 + i, 7);  cout << u8"       ■     ●    ▀■                                                                 ";
	gotoXY(17 + i, 8);  cout << u8"  ╼▀■■■            ▀■                                                                ";
	gotoXY(17 + i, 9);  cout << u8"  ╼▀    ■▄▄▄▄■■▀▀■   ▀■                                                              ";
	gotoXY(17 + i, 10); cout << u8"                 ▀■   ▀■                                                             ";
	gotoXY(17 + i, 11); cout << u8"                   ▀   ▀                                                             ";
	gotoXY(17 + i, 12); cout << u8"                   ▀   ▀                                                             ";
	gotoXY(17 + i, 13); cout << u8"                  ▀   ▀                                                              ";
	gotoXY(17 + i, 14); cout << u8"                   ▀   ▀                                                             ";
	gotoXY(17 + i, 15); cout << u8"                   ▀   ▀                                                             "; setTextColor(254);
	gotoXY(48 + i, 9);  cout << u8"■■■■■■■■";
	gotoXY(48 + i, 10); cout << u8"█       ";
	gotoXY(48 + i, 11); cout << u8"█▄▄▄▄▄▄▄";
	gotoXY(48 + i, 12); cout << u8"       █";
	gotoXY(48 + i, 13); cout << u8"▄▄▄▄▄▄▄█"; setTextColor(253);
	gotoXY(58 + i, 9);  cout << u8"■■       █";
	gotoXY(58 + i, 10); cout << u8"█ ▀▄     █";
	gotoXY(58 + i, 11); cout << u8"█   ▀▄   █";
	gotoXY(58 + i, 12); cout << u8"█     ▀▄ █";
	gotoXY(58 + i, 13); cout << u8"█       ▀█"; setTextColor(249);
	gotoXY(69 + i, 9);  cout << u8"    ▄▀▀▄    ";
	gotoXY(69 + i, 10); cout << u8"   ▄▀  ▀▄   ";
	gotoXY(69 + i, 11); cout << u8"  ▄▀▄▄▄▄▀▄  ";
	gotoXY(69 + i, 12); cout << u8" ▄▀      ▀▄ ";
	gotoXY(69 + i, 13); cout << u8"▄▀        ▀▄"; setTextColor(246);
	gotoXY(82 + i, 9);  cout << u8"█    ▄▀▀";
	gotoXY(82 + i, 10); cout << u8"█ ▄▄▀   ";
	gotoXY(82 + i, 11); cout << u8"█▀▄▄    ";
	gotoXY(82 + i, 12); cout << u8"█   ▀▄  ";
	gotoXY(82 + i, 13); cout << u8"█     ▀▄"; setTextColor(244);
	gotoXY(92 + i, 9);  cout << u8"█▀▀▀▀▀▀▀  ";
	gotoXY(92 + i, 10); cout << u8"█         ";
	gotoXY(92 + i, 11); cout << u8"█■■■■■■■  ";
	gotoXY(92 + i, 12); cout << u8"█         ";
	gotoXY(92 + i, 13); cout << u8"█▄▄▄▄▄▄▄  "; setTextColor(242);
	gotoXY(92 + i, 15); cout << u8"THE GAME"; setTextColor(250);
	gotoXY(17 + i, 14); cout << u8"                   ▀   ▀                                                             ";
	gotoXY(17 + i, 15); cout << u8"                   ▀   ▀                                           ";
	gotoXY(17 + i, 16); cout << u8"                  ▀   ▀                                                              ";
	gotoXY(17 + i, 17); cout << u8"                 ▀   ▀                                                               ";
	gotoXY(17 + i, 18); cout << u8"                ▀   ▀               ▄▄▄▄                                             ";
	gotoXY(17 + i, 19); cout << u8"                 ▀  ▀■            ▄▀    ▀▄▄▄▄▄▄▄                                     ";
	gotoXY(17 + i, 20); cout << u8"                 ▀■   ▀■■■■■■■■■■▀              ▀■■■■■■■■■■■▄▄▄▄                     ";
	gotoXY(17 + i, 21); cout << u8"                  ▀■                ▄▄▄▄                        ▀▄                   ";
	gotoXY(17 + i, 22); cout << u8"                    ▀■■■■■■■■■■■■■▄▀    ▀▀▀▀▀▀▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄    ▄▀                  ";
	gotoXY(17 + i, 23); cout << u8"                                                              ▀▄▀                    ";
	gotoXY(17 + i, 24); cout << u8"                                                            ▄■▀                      ";
	gotoXY(17 + i, 25); cout << u8"                                                                                     ";
	if (i == -16) {
		setTextColor(244);
		gotoXY(40, 28); cout << u8"⃝ PRESS ENTER TO BEGIN ⃝";
	}
}

void drawSnakeIntro2(int i) {
	setTextColor(250);
	gotoXY(17 + i, 6); cout << u8"       ▄■■■■■■■■▄                                                                     ";
	gotoXY(17 + i, 7); cout << u8"      ■     ●    ▀■                                                                   ";
	gotoXY(17 + i, 8); cout << u8"    ■              ▀■                                                                 ";
	gotoXY(17 + i, 9); cout << u8"     ■■■■▄▄▄▄■■▀▀■   ▀■                                                               ";
	gotoXY(17 + i, 10); cout << u8"                 ▀■   ▀■                                                             ";
	gotoXY(17 + i, 11); cout << u8"                   ▀   ▀                                                             ";
	gotoXY(17 + i, 12); cout << u8"                  ▀   ▀                                                              ";
	gotoXY(17 + i, 13); cout << u8"                ▀   ▀                                                                ";
	gotoXY(17 + i, 14); cout << u8"               ▀   ▀                                                                 ";
	gotoXY(17 + i, 15); cout << u8"              ▀   ▀                                                                  ";
	gotoXY(17 + i, 16); cout << u8"               ▀                                                                     "; setTextColor(254);
	gotoXY(48 + i, 10); cout << u8"■■■■■■■■";
	gotoXY(48 + i, 11); cout << u8"█       ";
	gotoXY(48 + i, 12); cout << u8"█▄▄▄▄▄▄▄";
	gotoXY(48 + i, 13); cout << u8"       █";
	gotoXY(48 + i, 14); cout << u8"▄▄▄▄▄▄▄█"; setTextColor(253);
	gotoXY(58 + i, 10); cout << u8"■■       █";
	gotoXY(58 + i, 11); cout << u8"█ ▀▄     █";
	gotoXY(58 + i, 12); cout << u8"█   ▀▄   █";
	gotoXY(58 + i, 13); cout << u8"█     ▀▄ █";
	gotoXY(58 + i, 14); cout << u8"█       ▀█"; setTextColor(249);
	gotoXY(69 + i, 10); cout << u8"    ▄▀▀▄    ";
	gotoXY(69 + i, 11); cout << u8"   ▄▀  ▀▄   ";
	gotoXY(69 + i, 12); cout << u8"  ▄▀▄▄▄▄▀▄  ";
	gotoXY(69 + i, 13); cout << u8" ▄▀      ▀▄ ";
	gotoXY(69 + i, 14); cout << u8"▄▀        ▀▄"; setTextColor(246);
	gotoXY(82 + i, 10); cout << u8"█    ▄▀▀";
	gotoXY(82 + i, 11); cout << u8"█ ▄▄▀   ";
	gotoXY(82 + i, 12); cout << u8"█▀▄▄    ";
	gotoXY(82 + i, 13); cout << u8"█   ▀▄  ";
	gotoXY(82 + i, 14); cout << u8"█     ▀▄"; setTextColor(244);
	gotoXY(92 + i, 10); cout << u8"█▀▀▀▀▀▀▀  ";
	gotoXY(92 + i, 11); cout << u8"█         ";
	gotoXY(92 + i, 12); cout << u8"█■■■■■■■  ";
	gotoXY(92 + i, 13); cout << u8"█         ";
	gotoXY(92 + i, 14); cout << u8"█▄▄▄▄▄▄▄  "; setTextColor(242);
	gotoXY(92 + i, 16); cout << u8"THE GAME"; setTextColor(250);
	gotoXY(17 + i, 15); cout << u8"              ▀   ▀                                                                  ";
	gotoXY(17 + i, 16); cout << u8"               ▀   ▀                                                ";
	gotoXY(17 + i, 17); cout << u8"               ▀   ▀                                                                 ";
	gotoXY(17 + i, 18); cout << u8"                ▀   ▀                                                                ";
	gotoXY(17 + i, 19); cout << u8"                 ▀  ▀■            ▄▄▄▄▄▄▄▄▄▄▄▄▄                                      ";
	gotoXY(17 + i, 20); cout << u8"                 ▀■   ▀■■■■■■■■■■▀              ▀■■■■■■■■■■■▄▄▄▄                     ";
	gotoXY(17 + i, 21); cout << u8"                  ▀■                                             ▀▄▄▄▄▄▄╾            ";
	gotoXY(17 + i, 22); cout << u8"                    ▀■■■■■■■■■■■■■▄▀▄▄▄▄▄▄▄▄▄▄▄▄             ▄▄▄▄▀                   ";
	gotoXY(17 + i, 23); cout << u8"                                                ▀■■■■■■■■■■■▀                        ";
	gotoXY(17 + i, 24); cout << u8"                                                                                     ";
	gotoXY(17 + i, 25); cout << u8"                                                                                     ";
	if (i == -16) {
		gotoXY(40, 28); cout << u8"                             ";
	}
}

void drawSnakeIntro3(int i) {
	setTextColor(250);
	gotoXY(17 + i, 6);  cout << u8"       ▄■■■■■■■■▄                                                                    ";
	gotoXY(17 + i, 7);  cout << u8"▄     ■      ●   ▀■                                                                  ";
	gotoXY(17 + i, 8);  cout << u8"╼▀■■■■            ▀■                                                                 ";
	gotoXY(17 + i, 9);  cout << u8"▄▀     ■▄▄▄▄■■▀▀■   ▀■                                                               ";
	gotoXY(17 + i, 10); cout << u8"                 ▀■   ▀■                                                             ";
	gotoXY(17 + i, 11); cout << u8"                   ▀    ▀                                                            ";
	gotoXY(17 + i, 12); cout << u8"                    ▀    ▀                                                           ";
	gotoXY(17 + i, 13); cout << u8"                     ▀   ▀                                                           ";
	gotoXY(17 + i, 14); cout << u8"                    ▀   ▀                                                            "; setTextColor(244);
	gotoXY(48 + i, 9);  cout << u8"■■■■■■■■";
	gotoXY(48 + i, 10); cout << u8"█       ";
	gotoXY(48 + i, 11); cout << u8"█▄▄▄▄▄▄▄";
	gotoXY(48 + i, 12); cout << u8"       █";
	gotoXY(48 + i, 13); cout << u8"▄▄▄▄▄▄▄█"; setTextColor(242);
	gotoXY(58 + i, 9);  cout << u8"■■       █";
	gotoXY(58 + i, 10); cout << u8"█ ▀▄     █";
	gotoXY(58 + i, 11); cout << u8"█   ▀▄   █";
	gotoXY(58 + i, 12); cout << u8"█     ▀▄ █";
	gotoXY(58 + i, 13); cout << u8"█       ▀█"; setTextColor(253);
	gotoXY(69 + i, 9);  cout << u8"    ▄▀▀▄    ";
	gotoXY(69 + i, 10); cout << u8"   ▄▀  ▀▄   ";
	gotoXY(69 + i, 11); cout << u8"  ▄▀▄▄▄▄▀▄  ";
	gotoXY(69 + i, 12); cout << u8" ▄▀      ▀▄ ";
	gotoXY(69 + i, 13); cout << u8"▄▀        ▀▄"; setTextColor(254);
	gotoXY(82 + i, 9);  cout << u8"█    ▄▀▀";
	gotoXY(82 + i, 10); cout << u8"█ ▄▄▀   ";
	gotoXY(82 + i, 11); cout << u8"█▀▄▄    ";
	gotoXY(82 + i, 12); cout << u8"█   ▀▄  ";
	gotoXY(82 + i, 13); cout << u8"█     ▀▄"; setTextColor(249);
	gotoXY(92 + i, 9);  cout << u8"█▀▀▀▀▀▀▀  ";
	gotoXY(92 + i, 10); cout << u8"█         ";
	gotoXY(92 + i, 11); cout << u8"█■■■■■■■  ";
	gotoXY(92 + i, 12); cout << u8"█         ";
	gotoXY(92 + i, 13); cout << u8"█▄▄▄▄▄▄▄  "; setTextColor(246);
	gotoXY(92 + i, 15); cout << u8"THE GAME"; setTextColor(250);
	gotoXY(17 + i, 14); cout << u8"                    ▀   ▀                                                            ";
	gotoXY(17 + i, 15); cout << u8"                   ▀   ▀                                            ";
	gotoXY(17 + i, 16); cout << u8"                  ▀   ▀                                                              ";
	gotoXY(17 + i, 17); cout << u8"                 ▀   ▀                                                               ";
	gotoXY(17 + i, 18); cout << u8"                ▀   ▀                                                                ";
	gotoXY(17 + i, 19); cout << u8"                ▀  ▀■                                                ▄■              ";
	gotoXY(17 + i, 20); cout << u8"                ▀■   ▀■■■■■■■■■■■▄                                  ▄■               ";
	gotoXY(17 + i, 21); cout << u8"                  ▀■              ▀▀▄                             ▄■▀                ";
	gotoXY(17 + i, 22); cout << u8"                    ▀▄               ▀▀▀▀▀▀▀▀▄▄▄▄▄▄▄             ▄▀                  ";
	gotoXY(17 + i, 23); cout << u8"                      ▀■■■■■■■■■■■■▄                ▀▄▄▄▄▄▄▀▀▀▀▀ ▄▀                  ";
	gotoXY(17 + i, 24); cout << u8"                                    ▀▄▄▄▄▄▄                    ■▀                    ";
	gotoXY(17 + i, 25); cout << u8"                                           ▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄■▀                       ";
	if (i == -16) {
		setTextColor(244);
		gotoXY(40, 28); cout << u8"⃝ PRESS ENTER TO BEGIN ⃝";
	}
}

void drawStartingMenu()
{
	int i = -4;
	char key = NULL;
	int flag = 1;

	while (true)
	{
		if (wait(100ms))
		{

			switch (flag)
			{
			case 1: drawSnakeIntro1(i); break;
			case 2: drawSnakeIntro2(i); break;
			case 3: drawSnakeIntro3(i); break;
			case 4: drawSnakeIntro2(i); break;
			}
			if (flag == 4 && i > -16) i -= 2;
			flag = (flag == 4) ? flag = 1 : ++flag;
		}
		if (i == -16) {
			GetWaitManyKey(key);
			if (key == ENTER)
			{
				sound.playEnter();
				setTextColor(240);
				clearInteractScreen(1, 1, BoardWidth - 1, BoardHeight - 1);
				return;
			}
		}
	}
}

// ---> Draw before Screen
void drawStartGameScreen() //(int gameWidth, int gameHeight) 
{
	setTextColor(244);
	gotoXY(InteractOrigin_x + 17, InteractOrigin_y + 5); cout << u8"▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄  ▄▄▄   ▄▄▄▄▄▄ ▄▄▄▄▄▄▄\n";
	gotoXY(InteractOrigin_x + 17, InteractOrigin_y + 6); cout << u8"█          █    ▄▀ ▀▄  █    █    █   \n";
	gotoXY(InteractOrigin_x + 17, InteractOrigin_y + 7); cout << u8"▀■■■■■▄    █    █■■■█  █■■■■▀    █   \n";
	gotoXY(InteractOrigin_x + 17, InteractOrigin_y + 8); cout << u8"      █    █   ▄▀   ▀▄ █ ▀■▄     █   \n";
	gotoXY(InteractOrigin_x + 17, InteractOrigin_y + 9); cout << u8"▀▀▀▀▀▀▀    ▀   ▀     ▀ ▀    ▀    ▀   \n";

	gotoXY(InteractOrigin_x + 24, InteractOrigin_y + 12);
	setTextColor(246);
	cout << u8"PRESS ENTER TO START!";
}

void drawLoadGameScreen(User* user_arr)
{
#pragma region Số liệu
	int maxlen = 15;
	const int leftHeadX = MenuOrigin_x + 2;
	const int leftHeadY = MenuOrigin_y + MenuHeight / 2;
	const int headx = GameWidth / 2 + InteractOrigin_x - 5;
	const int heady = InteractOrigin_y - 1;
	const int firstItemX = InteractOrigin_x + (GameWidth * 1) / 3 / 4;
	const int ItemY = InteractOrigin_y + 1 + 1;
	const int SecItemX = InteractOrigin_x + (GameWidth * 1) / 3 + (GameWidth * 2) / 9 / 4;
	const int ThirdItemX = InteractOrigin_x + (GameWidth * 5) / 9 + (GameWidth * 2) / 9 / 4;
	const int FourItemX = InteractOrigin_x + (GameWidth * 7) / 9 + (GameWidth * 2) / 9 / 4;
	const int choose = 0;
#pragma endregion

	// Render
	setTextColor(241);
	gotoXY(firstItemX, ItemY);
	cout << "NAME";
	gotoXY(SecItemX, ItemY);
	cout << "LEVEL";
	gotoXY(ThirdItemX, ItemY);
	cout << "SCORE";
	gotoXY(FourItemX, ItemY);
	cout << "DATE";

	int nItem = user_arr->totalUser;

	if (nItem < maxlen)
	{
		maxlen = nItem;
	}

	setTextColor(247);

	for (int k = choose; k < maxlen + choose; k++)
	{
		gotoXY(firstItemX - 3, ItemY + 1 + k - choose);
		string str = user_arr[k].Name;
		cout << "   " + str;
		//In thông tin
		gotoXY(SecItemX + 2, ItemY + 1 + k - choose);
		cout << user_arr[k].userMap.Level;
		gotoXY(ThirdItemX + 1, ItemY + 1 + k - choose);
		cout << user_arr[k].Score;
		gotoXY(FourItemX - 2, ItemY + 1 + k - choose);
		cout << user_arr[k].Timesave.tm_mday << "/" << user_arr[k].Timesave.tm_mon << "/" << user_arr[k].Timesave.tm_year;
	}
	setTextColor();
}

void drawIntroduction()
{
	//chỉ số bảng thông tin của ae
	const int BoardLeftX = InteractOrigin_x + 2;
	const int BoardLeftY = InteractOrigin_y + 2 + 4 + 2;
	const int BoardLeftW = GameWidth / 3 + 10;
	const int BoardLeftH = GameHeight - 4 - 4 - 2;
	const int MemX = BoardLeftX + 1;
	const int FirstMemY = BoardLeftY + 2;
	const int SecMemY = BoardLeftY + 4;
	const int ThirdMemY = BoardLeftY + 6;
	const int FourthMemY = BoardLeftY + 8;
	//Chỉ số bảng HowToPlay
	const int BoardRightW = GameWidth - BoardLeftW - 6;
	const int BoardRightH = GameHeight - 4;
	const int BoardRightX = BoardLeftX + BoardLeftW + 2;
	const int BoardRightY = InteractOrigin_y + 3;

	//Nội dung bảng Howtoplay
	setTextColor(245);
	gotoXY(BoardRightX + BoardRightW / 2 - 6, BoardRightY - 1);
	cout << "HOW TO PLAY";
	setTextColor(243);
	drawBoard(BoardRightH, BoardRightW, BoardRightX, BoardRightY);
	setTextColor(250);
	gotoXY(BoardRightX + 1, BoardRightY + 1);
	cout << u8"                          ▲   ";
	gotoXY(BoardRightX + 1, BoardRightY + 2);
	cout << u8"Control your snake with ◄   ► ";
	gotoXY(BoardRightX + 1, BoardRightY + 3);
	cout << u8"                          ▼   ";
	gotoXY(BoardRightX + 1, BoardRightY + 5);
	cout << u8"Avoid hitting walls";
	gotoXY(BoardRightX + 1, BoardRightY + 7);
	cout << u8"Avoid hitting yourself";
	gotoXY(BoardRightX + 1, BoardRightY + 9);
	cout << u8"Try to eat enough food";
	gotoXY(BoardRightX + 1 + 10, BoardRightY + 10);
	cout << u8" to pass each level";
	gotoXY(BoardRightX + 1, BoardRightY + 12);
	cout << u8"Press P to pause the game";
	gotoXY(BoardRightX + 1, BoardRightY + 14);
	setTextColor(253);
	cout << "        ENJOY! GOOD LUCK     ";
	//Nội dung bảng thông tin

	setTextColor(252);
	gotoXY(BoardLeftX, BoardLeftY - 6);
	cout << u8"                               ❹  ";
	gotoXY(BoardLeftX, BoardLeftY - 5);
	cout << u8"                             ❹ ❹  ";
	gotoXY(BoardLeftX, BoardLeftY - 4);
	cout << u8"▄▄▄▄▄ ▄▄▄  ▄▄▄   ▄▄  ▄▄     ❹  ❹  ";
	gotoXY(BoardLeftX, BoardLeftY - 3);
	cout << u8"  █   █■■ ▄█■█▄  █▀▄▄▀█    ❹   ❹  ";
	gotoXY(BoardLeftX, BoardLeftY - 2);
	cout << u8"  ▀   ▀▀▀ ▀   ▀  ▀ ▀▀ ▀   ❹ ❹  ❹ ❹";
	gotoXY(BoardLeftX, BoardLeftY - 1);
	cout << u8"                               ❹  ";
	setTextColor(251);
	drawBoard(BoardLeftH, BoardLeftW, BoardLeftX, BoardLeftY);
	setTextColor(240);
	gotoXY(MemX, FirstMemY);  cout << u8"Trần Phương Đình       19120476";
	gotoXY(MemX, SecMemY);    cout << u8"Trần Quốc Đông         19120479";
	gotoXY(MemX, ThirdMemY);  cout << u8"Lê Trần Đăng Khoa      19120546";
	gotoXY(MemX, FourthMemY); cout << u8"Huỳnh Nguyễn Thị Lựu   19120573";
	setTextColor();
}

void drawExit()
{
	const int X = InteractOrigin_x + 3;
	const int Y = InteractOrigin_y + 1;
	const int snakeX = X + 30 + 5;
	const int snakeY = Y + 8;
	//218,219,222
	setTextColor(245);
	gotoXY(X, Y + 0); cout << u8"████████████████████████████████████████████████";
	gotoXY(X, Y + 1); cout << u8"█                                              █";
	gotoXY(X, Y + 2); cout << u8"█                                              █";
	gotoXY(X, Y + 3); cout << u8"█                                              █";
	gotoXY(X, Y + 4); cout << u8"█                                              █";
	gotoXY(X, Y + 5); cout << u8"█                                              █";
	gotoXY(X, Y + 6); cout << u8"████████████████████████████████████████████████";

	setTextColor(244);
	gotoXY(X + 2, Y + 2); cout << u8"      ╔══ ╦╗ ╦ ═╦═ ╔══ ╔═╗                 ";
	gotoXY(X + 2, Y + 3); cout << u8"PRESS ╠══ ║╚╗║  ║  ╠══ ╠╦╝ TO EXIT THE GAME";
	gotoXY(X + 2, Y + 4); cout << u8"      ╚══ ╩ ╚╝  ╩  ╚══ ╩╚╛                 ";

	setTextColor(242);
	gotoXY(snakeX, snakeY);			 cout << u8"        ▄■■■■■■■■▄";
	gotoXY(snakeX, snakeY + 1);		 cout << u8"       ■  ◙       ▀■";
	gotoXY(snakeX, snakeY + 2);		 cout << u8"  ╼▀■■■            ▀■";
	gotoXY(snakeX, snakeY + 3);		 cout << u8"  ╼▀    ■▄▄▄▄■■▀▀■   ▀■";
	gotoXY(snakeX, snakeY + 4);		 cout << u8"                 ▀■   ▀■";
	gotoXY(snakeX, snakeY + 5);		 cout << u8"                   ▀   ▀";
	gotoXY(snakeX, snakeY + 9 - 3);	 cout << u8"                   ▀   ▀";
	gotoXY(snakeX, snakeY + 10 - 3); cout << u8"                  ▀   ▀";
	gotoXY(snakeX, snakeY + 11 - 3); cout << u8"                 ▀   ▀";
	gotoXY(snakeX, snakeY + 12 - 3); cout << u8"                ▀   ▀       ▄▄▄▄";
	gotoXY(snakeX, snakeY + 13 - 3); cout << u8"                 █  ▀█▄■■■■▀    ";
	setTextColor(252);
	gotoXY(snakeX + 10, snakeY + 1); cout << u8"◙";
	setTextColor();

}

void QuitGame()
{
	system("cls");
	sound.playCredit();
	ShowConsoleCursor(false);
	const int BoardX = 20;
	const int BoardY = 5;
	const int BoardW = 50;
	const int BoardH = 13;
	const int X = BoardX + 2 + 2 + 1 + 1;
	const int Y = BoardH + BoardY;
	setTextColor(240);
	drawBoard(BoardH, BoardW, BoardX, BoardY);
	for (int i = Y; i > -Y; i--)
	{
		int j = 0;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			cout << u8"     Đồ án môn Kỹ Thuật Lập Trình      ";

		}; j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"  Game rắn săn mồi - Snake-The Game ";

		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"   Trường Đại học Khoa học Tự nhiên     ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"Lớp:                                    ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"             19CTT3                     ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"Giáo viên hướng dẫn:              ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"             Trương Toàn Thịnh    ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"Nhóm thực hiện:                   ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"             Nhóm 4               ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y) cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"Các thành viên:                   ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"             Trần Quốc Đông(nhóm trưởng)";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"             Trần Phương Đình           ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"             Lê Trần Đăng Khoa          ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"             Huỳnh Nguyễn Thị Lựu       ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"       ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥       ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"       ♥   Thank for playing    ♥       ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"       ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥       ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		Sleep(450);
	}

}

void clearInteractScreen(int x, int y, int width, int height)
{
	string drawblank = " ";
	drawblank = drawblank * width;
	gotoXY(x, y);
	for (int i = 0; i < height; i++)
	{
		gotoXY(x, y + i);
		cout << drawblank;
	}
}

void clearMenuScreen(int x, int y, int width, int height)
{
	string drawblank = " ";
	drawblank = drawblank * width;
	gotoXY(x, y);
	for (int i = 0; i < height; i++)
	{
		gotoXY(x, y + i);
		cout << drawblank;
	}
}

void clearBelowScreen()
{
	gotoXY(24, 26);
	cout << "                                                                        ";
}
// ---> Draw menu
void drawMenuOptions()
{
	setTextColor(253);
	drawInMenu(u8"   NEW GAME   ", 2);
	drawInMenu(u8"   LOAD GAME  ", 6);
	drawInMenu(u8"  HIGH SCORE  ", 10);
	drawInMenu(u8" INTRODUCTION ", 14);
	drawInMenu(u8"     Exit     ", 18);
	setTextColor();
}

void drawSelectedOption(int Selected)
{
	switch (Selected)
	{
	case 1:
		setTextColor(252);
		drawInMenu(u8"«  NEW GAME  »", 2); // New
		setTextColor(253);
		drawInMenu(u8"   LOAD GAME  ", 6); // Reset
		setTextColor();
		return;
	case 2:
		setTextColor(252);
		drawInMenu(u8"«  LOAD GAME »", 6); // New
		setTextColor(253);
		drawInMenu(u8"   NEW GAME   ", 2); // Reset
		drawInMenu(u8"  HIGH SCORE  ", 10); // Reset
		setTextColor();
		return;
	case 3:
		setTextColor(252);
		drawInMenu(u8"« HIGH SCORE »", 10); // New
		setTextColor(253);
		drawInMenu(u8"   LOAD GAME  ", 6); // Reset
		drawInMenu(u8" INTRODUCTION ", 14); // Reset
		setTextColor();
		return;
	case 4:
		setTextColor(252);
		drawInMenu(u8"«INTRODUCTION»", 14); // New
		setTextColor(253);
		drawInMenu(u8"  HIGH SCORE  ", 10); // Reset
		drawInMenu(u8"     Exit     ", 18); // Reset
		setTextColor();
		return;
	case 5:
		setTextColor(252);
		drawInMenu(u8"«    Exit    »", 18); // New
		setTextColor(253);
		drawInMenu(u8" INTRODUCTION ", 14); // Reset
		setTextColor();
		return;
	}
}

// ---> Draw interact Screen
#pragma endregion

#pragma region Render Interact screen
int showLoadGame(User* user_arr)
{
#pragma region số liệu
	int maxlen = 15;
	const int leftHeadX = MenuOrigin_x + 2;
	const int leftHeadY = MenuOrigin_y + MenuHeight / 2;
	const int headx = GameWidth / 2 + InteractOrigin_x - 5;
	const int heady = InteractOrigin_y - 1;
	const int firstItemX = InteractOrigin_x + (GameWidth * 1) / 3 / 4;
	const int ItemY = InteractOrigin_y + 1 + 1;
	const int SecItemX = InteractOrigin_x + (GameWidth * 1) / 3 + (GameWidth * 2) / 9 / 4;
	const int ThirdItemX = InteractOrigin_x + (GameWidth * 5) / 9 + (GameWidth * 2) / 9 / 4;
	const int FourItemX = InteractOrigin_x + (GameWidth * 7) / 9 + (GameWidth * 2) / 9 / 4;
#pragma endregion



	// Render
	setTextColor(241);
	gotoXY(firstItemX, ItemY);
	cout << "NAME";
	gotoXY(SecItemX, ItemY);
	cout << "LEVEL";
	gotoXY(ThirdItemX, ItemY);
	cout << "SCORE";
	gotoXY(FourItemX, ItemY);
	cout << "DATE";
	setTextColor(240);
	gotoXY(InteractOrigin_x + GameWidth - 40, InteractOrigin_y - 1 + GameHeight);
	cout << "Press ESC or Left to return to MENU... ";

	int nItem = user_arr->totalUser;

	bool* selected = new bool[nItem];
	selected[0] = 1;
	user_arr[0].Name.insert(0, "   ");
	for (int i = 1; i < nItem; i++)
	{
		selected[i] = 0;
		user_arr[i].Name.insert(0, "   ");
	}

	int choose = 0;
	if (nItem < maxlen)
	{
		maxlen = nItem;
	}

	//Menu
	while (true)
	{
		char key = 'c';
		for (int k = choose; k < maxlen + choose; k++)
		{
			gotoXY(firstItemX - 3, ItemY + 1 + k - choose);
			if (selected[k] == 1)
			{
				setTextColor(252);
				string a = "=> ";
				user_arr[k].Name.erase(0, 3);
				int pTemlen = user_arr[k].Name.size();
				user_arr[k].Name.insert(0, a);
				//int pTemlen = pTem[k].size();
				string str = user_arr[k].Name;
				for (int x = 0; x < maxlen - pTemlen; x++)
					str += " ";
				cout << str;
				user_arr[k].Name.erase(0, 3);
				user_arr[k].Name.insert(0, "   ");
				setTextColor();
			}
			else
			{
				int pTemlen = user_arr[k].Name.size();
				string str = user_arr[k].Name;
				for (int x = 0; x < maxlen - pTemlen; x++)
					str += " ";
				cout << str;
			}

			//In thông tin
			gotoXY(SecItemX + 2, ItemY + 1 + k - choose);
			cout << user_arr[k].userMap.Level;
			gotoXY(ThirdItemX + 1, ItemY + 1 + k - choose);
			cout << user_arr[k].Score;
			gotoXY(FourItemX - 2, ItemY + 1 + k - choose);
			cout << user_arr[k].Timesave.tm_mday << "/" << user_arr[k].Timesave.tm_mon << "/" << user_arr[k].Timesave.tm_year;
		}
		//Xử lý  lựa chọn
		GetManyKey(key);
		if (key == UP && selected[0] != 1)
		{
			sound.playMenu();
			for (int j = 1; j < nItem; j++)
			{
				if (selected[j] == 1)
					if (selected[j] == 1)
					{

						selected[j] = 0;
						selected[j - 1] = 1;
						if (j == choose)
							choose--;
						break;
					}
			}
		}
		else if (key == DOWN && selected[nItem - 1] != 1)
		{
			sound.playMenu();
			for (int j = 0; j < nItem; j++)
			{
				if (selected[j] == 1)
				{
					selected[j] = 0;
					selected[j + 1] = 1;
					if (j == choose + maxlen - 1)
					{
						choose++;
					}
					break;
				}
			}
		}
		else if (key == ENTER)
		{
			sound.playEnter();
			for (int k = 0; k < nItem; k++)
			{
				user_arr[k].Name.erase(0, 3);
			}

			for (int j = 0; j < nItem; j++)
			{
				if (selected[j] == 1)
				{
					delete[] selected;
					return j;
				}
			}
		}
		else if (key == ESC || key == LEFT)
		{
			sound.playMenu();
			for (int k = 0; k < nItem; k++)
			{
				user_arr[k].Name.erase(0, 3);
			}
			delete[] selected;
			return -1;
		}
	}
}

// High Score
struct UserHinghScore {
	string Name;
	int Level;
	int HighScore;
	tm Deathsave;
};
typedef struct UserHinghScore USERHSC;

bool operator <(const USERHSC& a, const USERHSC& b)
{
	if (a.HighScore < b.HighScore)
		return true;
	return false;
}

void showHighScore(User* users)
{
	size_t size = users->totalUser;
	USERHSC* NEWUSER = new USERHSC[size];
	// Copy users  sang users để sort
	for (size_t i = 0; i < size; i++)
	{
		NEWUSER[i].Name = users[i].Name;
		NEWUSER[i].HighScore = users[i].HighScore;
		NEWUSER[i].Level = users[i].userMap.Level;
		NEWUSER[i].Deathsave = users[i].Deathsave;
	}
	// Sort theo high score
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = i + 1; j < size; j++)
			if (NEWUSER[i] < NEWUSER[j]) {
				USERHSC x = NEWUSER[i];
				NEWUSER[i] = NEWUSER[j];
				NEWUSER[j] = x;
			}
	}
	// Tọa độ in
	const int col1 = MenuOrigin_x + 23;
	const int col2 = MenuOrigin_x + 35;
	const int col3 = MenuOrigin_x + 53;
	const int col4 = MenuOrigin_x + 64;
	const int col5 = MenuOrigin_x + 78;
	const int row = 7;
	setTextColor(241);
	gotoXY(col1, row);
	cout << "TOP";
	gotoXY(col2, row);
	cout << "NAME";
	gotoXY(col3, row);
	cout << "SCORE";
	gotoXY(col4, row);
	cout << "LEVEL";
	gotoXY(col5, row);
	cout << "DATE";
	setTextColor(240);
	size_t i = 0;
	while (i < size && i < 15) {
		if (i == 0)		   setTextColor(252);
		else if (i == 1)   setTextColor(253);
		else if (i == 2)   setTextColor(244);
		else if (i < 10)  setTextColor(246);
		else			   setTextColor(248);
		gotoXY(col1 - 1, row + 2 + i);  cout << "No." << i + 1;
		gotoXY(col2 - 2, row + 2 + i);  cout << NEWUSER[i].Name;
		gotoXY(col3 + 1, row + 2 + i);  cout << NEWUSER[i].HighScore;
		gotoXY(col4 + 2, row + 2 + i);  cout << NEWUSER[i].Level;
		gotoXY(col5 - 3, row + 2 + i);  cout << NEWUSER[i].Deathsave.tm_mday << "/" << NEWUSER[i].Deathsave.tm_mon << "/" << NEWUSER[i].Deathsave.tm_year;
		i++;
		setTextColor();
	}
	delete[] NEWUSER;
}

void Ready(const User user)
{
	//Clear bảng
	clearInteractScreen(53, 14, 17, 6);
	//Bảng
	const int BoardW = 16;
	const int BoardH = 5;
	const int BoardX = (GameWidth - BoardW) / 2 + InteractOrigin_x;
	const int BoardY = InteractOrigin_y + GameHeight / 2 - BoardH / 2;
	const int NumX = BoardX + BoardW / 2;
	const int NumY = BoardY + 2 + 1;
	const milliseconds SPEED = 28ms;
	string a;
	if (user.userSnake.length == 0)
		a = "Start New Game";
	else
		a = "Continue";

	for (int i = 0; i <= BoardW; i++)
	{
		gotoXY(BoardX + i, BoardY);
		if (i == 0)
			cout << u8"╔";
		else if (i == BoardW)
			cout << u8"╗";
		else
			cout << u8"═";

	}
	for (int i = 1; i < BoardH; i++)
	{
		gotoXY(BoardX + BoardW, BoardY + i);
		cout << u8"║";
	}
	for (int i = 0; i <= BoardW; i++)
	{
		gotoXY(BoardX + BoardW - i, BoardY + BoardH);
		if (i == 0)
			cout << u8"╝";
		else if (i == BoardW)
			cout << u8"╚";
		else
			cout << u8"═";

	}
	for (int i = 1; i < BoardH; i++)
	{
		gotoXY(BoardX, BoardY + BoardH - i);
		cout << u8"║";
	}

	sound.playReady();
	for (int j = 1; j <= 3; j++)
	{
		setTextColor(240);
		gotoXY(BoardX + BoardW / 2 - a.size() / 2, BoardY + 1);
		cout << a;
		for (int i = 1; i <= 7; i++)
		{
			gotoXY(BoardX + (BoardW - 7) / 2 + i - 1, BoardY + 3);
			cout << "      ";
		}
		if (j == 1)
			setTextColor(249);
		else
			setTextColor(250 + j);
		if (j == 1)
		{
			gotoXY(BoardX + (BoardW - 6) / 2, BoardY + 3);
			cout << u8"«READY»";
		}
		else if (j == 2)
		{
			gotoXY(BoardX + (BoardW - 4) / 2, BoardY + 3);
			cout << u8"«SET»";
		}
		else
		{
			gotoXY(BoardX + (BoardW - 3) / 2, BoardY + 3);
			cout << u8"«GO»";
		}
		//gotoXY(NumX, NumY); cout << 4 - j;


		for (int i = BoardW / 2 + 1; i <= BoardW; i++)
		{
			gotoXY(BoardX + i - 1, BoardY);
			cout << u8"═";
			gotoXY(BoardX + i, BoardY);
			if (i == BoardW)
				cout << u8"╗";
			else
				cout << u8"●";
			stop(SPEED);

		}
		for (int i = 1; i < BoardH; i++)
		{
			gotoXY(BoardX + BoardW, BoardY + i - 1);
			if (i == 1)
				cout << u8"╗";
			else
				cout << u8"║";
			gotoXY(BoardX + BoardW, BoardY + i);
			cout << u8"●";
			stop(SPEED);
		}
		gotoXY(BoardX + BoardW, BoardY + BoardH - 1);
		cout << u8"║";
		for (int i = 0; i <= BoardW; i++)
		{
			gotoXY(BoardX + BoardW - i, BoardY + BoardH);
			cout << u8"●";
			if (i > 0)
			{
				gotoXY(BoardX + BoardW - i + 1, BoardY + BoardH);
				if (i == 1)
					cout << u8"╝";
				else
					cout << u8"═";
			}
			stop(SPEED);
		}
		for (int i = 1; i < BoardH; i++)
		{
			gotoXY(BoardX, BoardY + BoardH - i);
			cout << u8"●";
			if (i == 1)
			{
				gotoXY(BoardX, BoardY + BoardH);
				cout << u8"╚";
			}
			if (i > 1)
			{
				gotoXY(BoardX, BoardY + BoardH - i + 1);
				cout << u8"║";
			}

			stop(SPEED);
		}
		for (int i = 0; i <= BoardW / 2; i++)
		{
			gotoXY(BoardX + i, BoardY);
			cout << u8"●";
			if (i == 0)
			{
				gotoXY(BoardX, BoardY + BoardH - (BoardH - 1));
				cout << u8"║";
			}
			if (i > 0)
			{
				gotoXY(BoardX + i - 1, BoardY);
				if (i == 1)
					cout << u8"╔";
				else
					cout << u8"═";
			}

			stop(SPEED);
		}
	}

	gotoXY(NumX, NumY); cout << 0;
	setTextColor();
}

void ReadyLevel(User user)
{
	//Clear bảng
	clearInteractScreen(53, 14, 17, 6);
	//Bảng
	const int BoardW = 16;
	const int BoardH = 5;
	const int BoardX = (GameWidth - BoardW) / 2 + InteractOrigin_x;
	const int BoardY = InteractOrigin_y + GameHeight / 2 - BoardH / 2;
	const int NumX = BoardX + BoardW / 2;
	const int NumY = BoardY + 2 + 1;
	const milliseconds SPEED = 20ms;
	string a;
	a = "Level " + to_string(user.userMap.Level);

	for (int i = 0; i <= BoardW; i++)
	{
		gotoXY(BoardX + i, BoardY);
		if (i == 0)
			cout << u8"╔";
		else if (i == BoardW)
			cout << u8"╗";
		else
			cout << u8"═";

	}
	for (int i = 1; i < BoardH; i++)
	{
		gotoXY(BoardX + BoardW, BoardY + i);
		cout << u8"║";
	}
	for (int i = 0; i <= BoardW; i++)
	{
		gotoXY(BoardX + BoardW - i, BoardY + BoardH);
		if (i == 0)
			cout << u8"╝";
		else if (i == BoardW)
			cout << u8"╚";
		else
			cout << u8"═";

	}
	for (int i = 1; i < BoardH; i++)
	{
		gotoXY(BoardX, BoardY + BoardH - i);
		cout << u8"║";
	}

	gotoXY(NumX - 1, NumY); cout << u8"⌠";
	gotoXY(NumX + 1, NumY); cout << u8"⌡";
	for (int j = 1; j <= 3; j++)
	{
		setTextColor(240);
		gotoXY(BoardX + BoardW / 2 - a.size() / 2, BoardY + 1);
		cout << a;
		if (j == 1)
			setTextColor(249);
		else
			setTextColor(250 + j);
		gotoXY(NumX, NumY); cout << 4 - j;

		for (int i = BoardW / 2 + 1; i <= BoardW; i++)
		{
			gotoXY(BoardX + i - 1, BoardY);
			cout << u8"═";
			gotoXY(BoardX + i, BoardY);
			if (i == BoardW)
				cout << u8"╗";
			else
				cout << u8"●";
			stop(SPEED);

		}
		for (int i = 1; i < BoardH; i++)
		{
			gotoXY(BoardX + BoardW, BoardY + i - 1);
			if (i == 1)
				cout << u8"╗";
			else
				cout << u8"║";
			gotoXY(BoardX + BoardW, BoardY + i);
			cout << u8"●";
			stop(SPEED);
		}
		gotoXY(BoardX + BoardW, BoardY + BoardH - 1);
		cout << u8"║";
		for (int i = 0; i <= BoardW; i++)
		{
			gotoXY(BoardX + BoardW - i, BoardY + BoardH);
			cout << u8"●";
			if (i > 0)
			{
				gotoXY(BoardX + BoardW - i + 1, BoardY + BoardH);
				if (i == 1)
					cout << u8"╝";
				else
					cout << u8"═";
			}
			stop(SPEED);
		}
		for (int i = 1; i < BoardH; i++)
		{
			gotoXY(BoardX, BoardY + BoardH - i);
			cout << u8"●";
			if (i == 1)
			{
				gotoXY(BoardX, BoardY + BoardH);
				cout << u8"╚";
			}
			if (i > 1)
			{
				gotoXY(BoardX, BoardY + BoardH - i + 1);
				cout << u8"║";
			}

			stop(SPEED);
		}
		for (int i = 0; i <= BoardW / 2; i++)
		{
			gotoXY(BoardX + i, BoardY);
			cout << u8"●";
			if (i == 0)
			{
				gotoXY(BoardX, BoardY + BoardH - (BoardH - 1));
				cout << u8"║";
			}
			if (i > 0)
			{
				gotoXY(BoardX + i - 1, BoardY);
				if (i == 1)
					cout << u8"╔";
				else
					cout << u8"═";
			}
			stop(SPEED);
		}
	}
	gotoXY(NumX, NumY); cout << 0;
	setTextColor();
}
#pragma endregion

#pragma region Base draw
// Cần forward declaration

void drawBoard(int height, int width, int posX, int posY)
{
	gotoXY(posX, posY); cout << u8"╔";
	for (int i = 1, j = 1; i < height + width; i++, j++)
	{
		if (i < width) { gotoXY(posX + i, posY + 0); cout << u8"═"; }
		else if (i == width) { gotoXY(posX + width, posY + 0); cout << u8"╗"; }
		else { gotoXY(posX + width, posY + i - width); cout << u8"║"; }

		if (j < height) { gotoXY(posX + 0, posY + j); cout << u8"║"; }
		else if (i == height) { gotoXY(posX + 0, posY + height); cout << u8"╚"; }
		else { gotoXY(posX + j - height, posY + height); cout << u8"═"; }
	}
	gotoXY(posX + width, posY + height); cout << u8"╝";
}

void drawAboveMenu(const char* Line1, const char* Line2, const char* Line3)
{
	gotoXY(AbMenu_x, AbMenu_y);		cout << Line1;
	gotoXY(AbMenu_x, AbMenu_y + 1); cout << Line2;
	gotoXY(AbMenu_x, AbMenu_y + 2); cout << Line3;
}

void drawInMenu(const char* Write, int Line)
{
	gotoXY(InMenu_x, InMenu_y + Line); cout << Write;
}

void drawAboveScreen(const char* Line1, const char* Line2, const char* Line3, const char* Line4)
{
	gotoXY(AbScreen_x, AbScreen_y);		cout << Line1;
	gotoXY(AbScreen_x, AbScreen_y + 1); cout << Line2;
	gotoXY(AbScreen_x, AbScreen_y + 2); cout << Line3;
	gotoXY(AbScreen_x, AbScreen_y + 3); cout << Line4;
}

void drawBelowScreen(const char* Line1, const char* Line2, const char* Line3, const char* Line4)
{
	gotoXY(BlScreen_x, BlScreen_y); cout << Line1;
	gotoXY(BlScreen_x, BlScreen_y + 1); cout << Line2;
	gotoXY(BlScreen_x, BlScreen_y + 2); cout << Line3;
	gotoXY(BlScreen_x, BlScreen_y + 3); cout << Line4;
}

void clearAboveScreen()
{
	gotoXY(AbScreen_x, AbScreen_y);		cout << "                                                                     ";
	gotoXY(AbScreen_x, AbScreen_y + 1); cout << "                                                                     ";
	gotoXY(AbScreen_x, AbScreen_y + 2); cout << "                                                                     ";
	gotoXY(AbScreen_x, AbScreen_y + 3); cout << "                                                                     ";
}

// hàm dùng 4 hàm trên

void Map::drawLevel()
{
	setTextColor(246);
	switch (Level % 5)
	{
	case 1: {
		clearAboveScreen();
		drawAboveScreen(
			u8"            ▄      ▄▄▄▄▄  ▄     ▄  ▄▄▄▄▄  ▄           ▄",
			u8"            █      █▄▄▄▄   █   █   █▄▄▄▄  █           █",
			u8"            █      █        █ █    █      █           █",
			u8"            ▀▀▀▀▀  ▀▀▀▀▀     ▀     ▀▀▀▀▀  ▀▀▀▀▀       ▀"
		);
		setTextColor();
		return;
	}
	case 2: {
		clearAboveScreen();
		drawAboveScreen(
			u8"            ▄      ▄▄▄▄▄  ▄     ▄  ▄▄▄▄▄  ▄          ▄ ▄",
			u8"            █      █▄▄▄▄   █   █   █▄▄▄▄  █          █ █",
			u8"            █      █        █ █    █      █          █ █",
			u8"            ▀▀▀▀▀  ▀▀▀▀▀     ▀     ▀▀▀▀▀  ▀▀▀▀▀      ▀ ▀"
		);
		setTextColor();
		return;
	}
	case 3: {
		clearAboveScreen();
		drawAboveScreen(
			u8"            ▄      ▄▄▄▄▄  ▄     ▄  ▄▄▄▄▄  ▄         ▄ ▄ ▄",
			u8"            █      █▄▄▄▄   █   █   █▄▄▄▄  █         █ █ █",
			u8"            █      █        █ █    █      █         █ █ █",
			u8"            ▀▀▀▀▀  ▀▀▀▀▀     ▀     ▀▀▀▀▀  ▀▀▀▀▀     ▀ ▀ ▀"
		);
		setTextColor();
		return;
	}
	case 4: {
		clearAboveScreen();
		drawAboveScreen(
			u8"            ▄      ▄▄▄▄▄  ▄     ▄  ▄▄▄▄▄  ▄        ▄ ▄     ▄",
			u8"            █      █▄▄▄▄   █   █   █▄▄▄▄  █        █  █   █ ",
			u8"            █      █        █ █    █      █        █   █ █  ",
			u8"            ▀▀▀▀▀  ▀▀▀▀▀     ▀     ▀▀▀▀▀  ▀▀▀▀▀    ▀    ▀   "
		);
		setTextColor();
		return;
	}
	case 0: {
		setTextColor(252);
		clearAboveScreen();
		drawAboveScreen(
			u8"                ▄▄▄▄▄  ▄▄▄▄▄▄  ▄▄   ▄  ▄    ▄  ▄▄▄▄▄▄",
			u8"                █▄▄▄▄█ █    █  █ █  █  █    █  █▄▄▄▄▄",
			u8"                █    █ █    █  █  █ █  █    █       █",
			u8"                ▀▀▀▀▀  ▀▀▀▀▀▀  ▀   ▀▀  ▀▀▀▀▀▀  ▀▀▀▀▀▀"
		);
		setTextColor();
		return;
	}
	}
}

void drawSnakeTitle()
{
	clearAboveScreen();
	setTextColor(246);
	drawAboveScreen(
		u8"                   ▄▄▄▄▄ ▄▄  ▄   ▄▄   ▄     ▄▄▄▄▄",
		u8"                   █     █▀▄ █  ▄▀▀▄  █ ▄▄▄ █    ",
		u8"                   ▀▀▀▀█ █ ▀▄█ ▄█▄▄█▄ █■█   █▀▀▀▀",
		u8"                   ▀▀▀▀▀ ▀  ▀▀ ▀    ▀ ▀ ▀▀▀ ▀▀▀▀▀");
	setTextColor();
}

void drawLoadGameTitle()
{
	clearAboveScreen();
	setTextColor(244);
	drawAboveScreen(
		u8"       ▄    ▄▄▄▄▄   ▄▄   ▄▄▄▄     ▄▄▄▄   ▄▄   ▄▄    ▄▄ ▄▄▄▄▄",
		u8"       █    █   █  ▄▀▀▄  █  ▀▄    █     ▄▀▀▄  █▀▄  ▄▀█ █    ",
		u8"       █    █   █ ▄█▄▄█▄ █  ▄▀    █ ▀█ ▄█▄▄█▄ █ ▀▄▄▀ █ █▀▀▀▀",
		u8"       ▀▀▀▀ ▀▀▀▀▀ ▀    ▀ ▀▀▀▀     ▀▀▀▀ ▀    ▀ ▀  ▀▀  ▀ ▀▀▀▀▀"
	);
	setTextColor();
}

void drawHighScoreTitle()
{
	clearAboveScreen();
	setTextColor(253);
	drawAboveScreen(u8"       ▄   ▄ ▄ ▄▄▄▄▄ ▄   ▄     ▄▄▄▄▄ ▄▄▄▄▄ ▄▄▄▄▄ ▄▄▄▄▄ ▄▄▄▄▄",
		u8"       █   █ █ █     █   █     █     █     █   █ █   █ █    ",
		u8"       █▀▀▀█ █ █  ▀█ █▀▀▀█     ▀▀▀▀█ █     █   █ █▀█▀▀ █▀▀▀▀",
		u8"       ▀   ▀ ▀ ▀▀▀▀▀ ▀   ▀     ▀▀▀▀▀ ▀▀▀▀▀ ▀▀▀▀▀ ▀  ▀▀ ▀▀▀▀▀"
	);
	setTextColor();
}

void drawIntroductionTitle()
{
	clearAboveScreen();
	setTextColor(249);
	drawAboveScreen(u8"  ▄ ▄▄  ▄ ▄▄▄▄▄ ▄▄▄▄▄ ▄▄▄▄▄ ▄▄▄▄  ▄   ▄ ▄▄▄▄▄ ▄▄▄▄▄ ▄ ▄▄▄▄▄ ▄▄  ▄",
		u8"  █ █▀▄ █   █   █   █ █   █ █  ▀▄ █   █ █       █   █ █   █ █▀▄ █",
		u8"  █ █ ▀▄█   █   █▀█▀▀ █   █ █  ▄▀ █   █ █       █   █ █   █ █ ▀▄█",
		u8"  ▀ ▀  ▀▀   ▀   ▀  ▀▀ ▀▀▀▀▀ ▀▀▀▀  ▀▀▀▀▀ ▀▀▀▀▀   ▀   ▀ ▀▀▀▀▀ ▀  ▀▀"
	);
	setTextColor();
}

void drawExitGameTitle()
{
	clearAboveScreen();
	setTextColor(245);
	drawAboveScreen(u8"                         ▄▄▄▄▄ ▄   ▄ ▄ ▄▄▄▄▄",
		u8"                         █      ▀▄▀  █   █  ",
		u8"                         █▀▀▀▀  ▄▀▄  █   █  ",
		u8"                         ▀▀▀▀▀ ▀   ▀ ▀   ▀  ");
	setTextColor();
}

void drawGoodByeTitle()
{
	clearAboveScreen();
	setTextColor(252);
	drawAboveScreen(u8"       ▄▄▄▄▄ ▄▄▄▄▄ ▄▄▄▄▄ ▄▄▄▄     ▄▄▄▄  ▄   ▄ ▄▄▄▄▄",
		u8"       █     █   █ █   █ █  ▀▄    █▄▄▄█  ▀▄▀  █    ",
		u8"       █  ▀█ █   █ █   █ █  ▄▀    █   █   █   █▀▀▀▀",
		u8"       ▀▀▀▀▀ ▀▀▀▀▀ ▀▀▀▀▀ ▀▀▀▀     ▀▀▀▀    ▀   ▀▀▀▀▀"
	);
	setTextColor();
}
#pragma endregion

#pragma region User
void User::drawBeginLevelState()
{
	setTextColor(242);
	switch (this->userMap.Level % 5)
	{
	case 1:
		switch (this->userMap.FoodEaten) // Không break 4 3 2 để nó lần lượt xuống vẽ lại
		{
		case 4:
			for (int i = 0; i < 4; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"██████████████";
			}
		case 3:
			for (int i = 4; i < 8; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"▓▓▓▓▓▓▓▓▓▓▓▓▓▓";
			}
		case 2:
			for (int i = 8; i < 12; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
			}
		case 1:
			for (int i = 12; i < 16; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"░░░░░░░░░░░░░░";
			}
			break;
		}
		break;
	case 2:
	case 3:
	case 4:
		switch (this->userMap.FoodEaten) // Không break 4 3 2 để nó lần lượt xuống vẽ lại
		{
		case 8:
			for (int i = 0; i < 2; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"██████████████";
			}
		case 7:
			for (int i = 2; i < 4; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"██████████████";
			}
		case 6:
			for (int i = 4; i < 6; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"▓▓▓▓▓▓▓▓▓▓▓▓▓▓";
			}
		case 5:
			for (int i = 6; i < 8; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"▓▓▓▓▓▓▓▓▓▓▓▓▓▓";
			}
		case 4:
			for (int i = 8; i < 10; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
			}
		case 3:
			for (int i = 10; i < 12; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
			}
		case 2:
			for (int i = 12; i < 14; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"░░░░░░░░░░░░░░";
			}
		case 1:
			for (int i = 14; i < 16; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"░░░░░░░░░░░░░░";
			}
			break;
		}
		break;
	case 0:
		return;
	}
}

void User::drawLevelState()
{
	setTextColor(246);

	gotoXY(UpStateBoard_x, UpStateBoard_y);		cout << u8"◊SCORE : " << setw(5) << right << this->Score;

	gotoXY(UpStateBoard_x, UpStateBoard_y + 1); cout << u8"◊LENGTH: " << setw(5) << right << this->userSnake.length;

	gotoXY(UpStateBoard_x, UpStateBoard_y + 2); cout << u8"◊SPEED : " << setw(5) << right << this->userSnake.Speed.count();

	// Draw state
	gotoXY(UpStateBoard_x, UpStateBoard_y + 3);
	switch (this->userMap.Level % 5)
	{
	case 0:
		cout << u8"◙TIME LEFT: " << setw(2) << right << this->userMap.Timeleft.count();
		if (this->userMap.Timeleft <= 6s && this->userMap.Timeleft > 0s)
		{
			if (waitClock(1000ms)) sound.playClock();
		}
		break;
	case 1:
		cout << u8"◊FOOD: " << setw(5) << right << this->userMap.FoodEaten << "/4";
		break;
	case 2:
	case 3:
	case 4:
		cout << u8"◊FOOD: " << setw(5) << right << this->userMap.FoodEaten << "/8";
		break;
	}

	// Draw thanh food
	gotoXY(InteractOrigin_x + 41, InteractOrigin_y + 21);  cout << u8"╊";
	gotoXY(InteractOrigin_x + 70, InteractOrigin_y + 21);  cout << u8"╊";
	if (this->userMap.Level % 5 != 0)
	{
		setTextColor(240);
		gotoXY(MenuOrigin_x + 1, MenuOrigin_y + 5); cout << u8"══════════════";

		setTextColor(242);
		for (int i = 1; i <= this->userSnake.length - 4; i++)
		{
			if (i <= 4) { gotoXY(InteractOrigin_x + 41 + i, InteractOrigin_y + 21); cout << u8"░"; }
			else if (i <= 12) { gotoXY(InteractOrigin_x + 41 + i, InteractOrigin_y + 21); cout << u8"▒"; }
			else if (i <= 20) { gotoXY(InteractOrigin_x + 41 + i, InteractOrigin_y + 21); cout << u8"▓"; }
			else if (i <= 28) { gotoXY(InteractOrigin_x + 41 + i, InteractOrigin_y + 21); cout << u8"█"; }
		}
	}
	else
	{
		setTextColor(250);
		gotoXY(InteractOrigin_x + 42, InteractOrigin_y + 21); cout << u8"≡≈≡≈≡≈≡≈≡≈≡≈≡≈≡≈≡≈≡≈≡≈≡≈≡≈≡≈";
	}

	// Draw FoodBar State
	setTextColor(250);
	switch (this->userMap.Level % 5)
	{
	case 1:
		switch (this->userMap.FoodEaten) // Không break 4 3 2 để nó lần lượt xuống vẽ lại
		{
		case 4:
			for (int i = 0; i < 4; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"██████████████";
			}
			break;
		case 3:
			for (int i = 4; i < 8; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"▓▓▓▓▓▓▓▓▓▓▓▓▓▓";
			}
			break;
		case 2:
			for (int i = 8; i < 12; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
			}
			break;
		case 1:
			for (int i = 12; i < 16; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"░░░░░░░░░░░░░░";
			}
			break;
		}
		break;
	case 2:
	case 3:
	case 4:
		switch (this->userMap.FoodEaten)
		{
		case 8:
			for (int i = 0; i < 2; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"██████████████";
			}
			break;
		case 7:
			for (int i = 2; i < 4; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"██████████████";
			}
			break;
		case 6:
			for (int i = 4; i < 6; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"▓▓▓▓▓▓▓▓▓▓▓▓▓▓";
			}
			break;
		case 5:
			for (int i = 6; i < 8; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"▓▓▓▓▓▓▓▓▓▓▓▓▓▓";
			}
			break;
		case 4:
			for (int i = 8; i < 10; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
			}
			break;
		case 3:
			for (int i = 10; i < 12; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
			}
			break;
		case 2:
			for (int i = 12; i < 14; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"░░░░░░░░░░░░░░";
			}
			break;
		case 1:
			for (int i = 14; i < 16; i++)
			{
				gotoXY(DrawFood_x, DrawFood_y + i); cout << u8"░░░░░░░░░░░░░░";
			}
			break;
		}
		break;
	case 0:
		// Draw time
		setTextColor(246);
		drawTimeNumber(userMap.Timeleft);
		// Draw Notes below time
		if (userMap.Timeleft <= 0s)
		{
			static bool flag = true;
			if (flag) setTextColor(252);
			else setTextColor(254);
			drawNote(" ! Time  Up ! ");
			setTextColor();
			return;
		}
		setTextColor();
		return;
	}
}

void User::drawTimeNumber(seconds time)
{
	auto drawDigit = [](int Digit, int BeginPos = 6)
	{
		switch (Digit)
		{
		case 0:
			gotoXY(DrawTime_x + BeginPos, DrawTime_y);     cout << u8"▄▄▄▄▄";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 1); cout << u8"█   █";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 2); cout << u8"█   █";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 3); cout << u8"█   █";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 4); cout << u8"▀▀▀▀▀";
			return;
		case 1:
			gotoXY(DrawTime_x + BeginPos, DrawTime_y);     cout << u8"  ▄▄ ";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 1); cout << u8" ▄██ ";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 2); cout << u8"  ██ ";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 3); cout << u8"  ██ ";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 4); cout << u8"  ▀▀ ";
			return;
		case 2:
			gotoXY(DrawTime_x + BeginPos, DrawTime_y);     cout << u8"▄▄▄▄▄";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 1); cout << u8"  ▄▄█";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 2); cout << u8" ▄█  ";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 3); cout << u8"▄▀   ";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 4); cout << u8"▀▀▀▀▀";
			return;
		case 3:
			gotoXY(DrawTime_x + BeginPos, DrawTime_y);     cout << u8"▄▄▄▄▄";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 1); cout << u8"    █";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 2); cout << u8"▄▄▄▄█";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 3); cout << u8"    █";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 4); cout << u8"▀▀▀▀▀";
			return;
		case 4:
			gotoXY(DrawTime_x + BeginPos, DrawTime_y);     cout << u8"    ▄";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 1); cout << u8"  ▄▀█";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 2); cout << u8" ▄▀ █";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 3); cout << u8"▄█▄▄█";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 4); cout << u8"    ▀";
			return;
		case 5:
			gotoXY(DrawTime_x + BeginPos, DrawTime_y);     cout << u8"▄▄▄▄▄";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 1); cout << u8"█    ";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 2); cout << u8"▀▀▀▀█";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 3); cout << u8"    █";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 4); cout << u8"▀▀▀▀▀";
			return;
		case 6:
			gotoXY(DrawTime_x + BeginPos, DrawTime_y);     cout << u8"▄▄▄▄▄";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 1); cout << u8"█    ";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 2); cout << u8"█▀▀▀█";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 3); cout << u8"█   █";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 4); cout << u8"▀▀▀▀▀";
			return;
		case 7:
			gotoXY(DrawTime_x + BeginPos, DrawTime_y);     cout << u8"▄▄▄▄▄";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 1); cout << u8"   ▄▀";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 2); cout << u8"  ▄▀ ";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 3); cout << u8" ▄▀  ";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 4); cout << u8" ▀   ";
			return;
		case 8:
			gotoXY(DrawTime_x + BeginPos, DrawTime_y);     cout << u8"▄▄▄▄▄";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 1); cout << u8"█   █";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 2); cout << u8"█▀▀▀█";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 3); cout << u8"█   █";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 4); cout << u8"▀▀▀▀▀";
			return;
		case 9:
			gotoXY(DrawTime_x + BeginPos, DrawTime_y);     cout << u8"▄▄▄▄▄";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 1); cout << u8"█   █";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 2); cout << u8"▀▀▀▀█";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 3); cout << u8"    █";
			gotoXY(DrawTime_x + BeginPos, DrawTime_y + 4); cout << u8"▀▀▀▀▀";
			return;
		}
	};
	auto clear = []() ->void
	{
		for (int i = 0; i < 10; i++)
		{
			gotoXY(DrawTime_x, DrawTime_y + i);
			cout << "              ";
		}
	};

	if (time.count() < 20 && time.count() >= 18) clear();
	if (time.count() < 10 && time.count() >= 8) clear();

	if (time.count() < 10) drawDigit(time.count(), 5);
	else if (time.count() <= 19)
	{
		drawDigit(time.count() / 10, 1);
		drawDigit(time.count() % 10, 7);
	}
	else if (time.count() <= 99)
	{
		drawDigit(time.count() / 10, 1);
		drawDigit(time.count() % 10, 7);
	}
	else if (time.count() == 100)
	{
		gotoXY(DrawTime_x, DrawTime_y);     cout << u8" ▄╔════╗╔════╗";
		gotoXY(DrawTime_x, DrawTime_y + 1); cout << u8"▄█║    ║║    ║";
		gotoXY(DrawTime_x, DrawTime_y + 2); cout << u8" █║    ║║    ║";
		gotoXY(DrawTime_x, DrawTime_y + 3); cout << u8" █║    ║║    ║";
		gotoXY(DrawTime_x, DrawTime_y + 4); cout << u8" ▀╚════╝╚════╝";
	}
	else if (time.count() > 100)
	{
		gotoXY(DrawTime_x, DrawTime_y);     cout << u8" ▄╔═══╗╔══╗═╬═";
		gotoXY(DrawTime_x, DrawTime_y + 1); cout << u8"▄█║   ║║  ║   ";
		gotoXY(DrawTime_x, DrawTime_y + 2); cout << u8" █║   ║║  ║   ";
		gotoXY(DrawTime_x, DrawTime_y + 3); cout << u8" █║   ║║  ║   ";
		gotoXY(DrawTime_x, DrawTime_y + 4); cout << u8" ▀╚═══╝╚══╝   ";
	}
	setTextColor();
}
#pragma endregion

#pragma region GamePlay
bool showPause()
{
	setTextColor(240);
	clearInteractScreen();
	clearBelowScreen();
	drawInteractBoard();
	drawBoard(GameHeight - 10, GameWidth - 20, InteractOrigin_x + 10, InteractOrigin_y + 7);
	gotoXY(InteractOrigin_x + 4, InteractOrigin_y + 2); cout << u8"            ▄▄▄▄▄▄   ▄▄▄    ▄    ▄  ▄▄▄▄▄▄  ▄▄▄▄▄▄ \n";
	gotoXY(InteractOrigin_x + 4, InteractOrigin_y + 3); cout << u8"░░░░░░░░░░░ █    █  ▄▀ ▀▄   █    █  █       █      ░░░░░░░░░░░\n";
	gotoXY(InteractOrigin_x + 4, InteractOrigin_y + 4); cout << u8"◘◘◘◘◘◘◘◘◘◘◘ █■■■■▀  █■■■█   █    █  ▀■■■■▄  █■■■■■ ◘◘◘◘◘◘◘◘◘◘◘\n";
	gotoXY(InteractOrigin_x + 4, InteractOrigin_y + 5); cout << u8"░░░░░░░░░░░ █      ▄▀   ▀▄  █    █       █  █      ░░░░░░░░░░░\n";
	gotoXY(InteractOrigin_x + 4, InteractOrigin_y + 6); cout << u8"            ▀      ▀     ▀  ▀▀▀▀▀▀  ▀▀▀▀▀▀  ▀▀▀▀▀▀ \n";

	gotoXY(InteractOrigin_x + 30, InteractOrigin_y + 7); cout << "GAME PAUSED";

	setTextColor(250);
	gotoXY(InteractOrigin_x + 14, InteractOrigin_y + 15); cout << "CONTINUE";
	gotoXY(InteractOrigin_x + 13, InteractOrigin_y + 16); cout << "[PRESS P]";

	setTextColor(253);
	gotoXY(InteractOrigin_x + 51, InteractOrigin_y + 15); cout << "SAVE";
	gotoXY(InteractOrigin_x + 49, InteractOrigin_y + 16); cout << "[PRESS S]";

	setTextColor(240);

	char key = NULL;

	Coordinate POS[23] = { {63, 14}, { 65,14 }, { 66,15 }, { 65,16 }, { 64,17 }, { 63,18 }, { 62,19 }, { 61,20 }, { 60,21 }, { 59,20 }, { 58,19 }, { 57,18 }, { 56,17 }, { 55,16 }, { 54,15 }, { 55,14 }, { 57,14 }, { 58,15 }, { 59,16 }, { 60,17 }, { 61,16 },{62,15}, {63,14} };

	do
	{
		clearInteractScreen(InteractOrigin_x + 26, InteractOrigin_y + 8, 20, 9);

		//vẽ trái tim
		setTextColor(244);
		for (int i = 0; i < 23; i++)
		{
			gotoXY(POS[i].x, POS[i].y);
			cout << u8"♥";
			stop(50ms);
			GetWaitManyKey(key);
			if (key == NULL) continue;
			if (key == p || key == P) return true;
			else if (key == s || key == S) return false;
		}
		setTextColor(240);

		clearInteractScreen(InteractOrigin_x + 26, InteractOrigin_y + 8, 20, 9);

		//vẽ c++
		for (int i = 1; i <= 3; i++)
		{
			switch (i)
			{
			case 1:
				setTextColor(244);
				gotoXY(InteractOrigin_x + 27, InteractOrigin_y + 11);
				cout << u8"█▀▀▀▀    ▄      ▄";
				break;
			case 2:
				setTextColor(246);
				gotoXY(InteractOrigin_x + 27, InteractOrigin_y + 12);
				cout << u8"█      ■■█■■  ■■█■■";
				break;
			case 3:
				setTextColor(247);
				gotoXY(InteractOrigin_x + 27, InteractOrigin_y + 13);
				cout << u8"█▄▄▄▄    ▀      ▀";
				break;
			}

			stop(90ms);
			GetWaitManyKey(key);
			if (key == NULL) continue;
			if (key == p || key == P) {
				sound.playEnter();
				return true;
			}
			else if (key == s || key == S) {
				sound.playEnter();
				return 0;
			}
		}

		clearInteractScreen(InteractOrigin_x + 26, InteractOrigin_y + 8, 20, 9);

		//vẽ mặt cười
		for (int i = 1; i <= 3; i++)
		{
			switch (i)
			{
			case 1:
				setTextColor(246);
				gotoXY(InteractOrigin_x + 31, InteractOrigin_y + 10); cout << u8"█▀█";
				gotoXY(InteractOrigin_x + 39, InteractOrigin_y + 10); cout << u8"█▀█";
				break;
			case 2:
				setTextColor(247);
				gotoXY(InteractOrigin_x + 31, InteractOrigin_y + 11); cout << u8"█▄█";
				gotoXY(InteractOrigin_x + 39, InteractOrigin_y + 11); cout << u8"█▄█";
				break;
			case 3:

				setTextColor(253);
				gotoXY(InteractOrigin_x + 41, InteractOrigin_y + 15); cout << u8"█";
				gotoXY(InteractOrigin_x + 31, InteractOrigin_y + 15); cout << u8"█";

				for (int i = 1; i <= 9; i++)
				{
					gotoXY(InteractOrigin_x + 31 + i, InteractOrigin_y + 15); cout << u8"▄";
				}
			}

			stop(90ms);
			GetWaitManyKey(key);
			if (key == NULL) continue;
			if (key == p || key == P) {
				sound.playEnter();
				return true;
			}
			else if (key == s || key == S) {
				sound.playEnter();
				return 0;
			}
		}

		for (int i = 1; i <= 9; i++)
		{
			stop(75ms);
			GetWaitManyKey(key);
			if (key == NULL) continue;
			if (key == p || key == P) {
				sound.playEnter();
				return true;
			}
			else if (key == s || key == S) {
				sound.playEnter();
				return 0;
			}
		}
		clearInteractScreen(InteractOrigin_x + 26, InteractOrigin_y + 8, 20, 9);

	} while (true);
	setTextColor();
}
#pragma endregion

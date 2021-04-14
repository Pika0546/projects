#include "GameHeader.h"
#include "SoundHeader.h"

int User::totalUser = 0;

User::User()
{
	Name = "";
	Score = 0;
	Timesave = getNow();
	HighScore = 0;
	Deathsave = getNow();
}

#pragma region Static function
void User::getAllInfo(User*& gameUsers)
{
	User::getBasicInfo(gameUsers);
	for (int i = 0; i < User::totalUser; i++)
	{
		gameUsers[i].getInfo();
	}
}

void User::checkAllInfo(User*& gameUsers)
{
	for (int i = 0; i < User::totalUser; i++)
	{
		gameUsers[i].checkInfo();
		cout << endl << endl;
	}
}

void User::getBasicInfo(User*& gameUsers)
{
	if (gameUsers != nullptr) return;

	ifstream fin("User//Basic Info.txt");
	if (!fin.is_open()) cout << "Opening file error";
	fin >> User::totalUser; fin.ignore(1);
	gameUsers = new User[User::totalUser];
	for (int i = 0; i < User::totalUser; i++)
	{
		getline(fin, gameUsers[i].Name);
	}
	fin.close();
}

void User::checkBasicInfo(User*& gameUsers)
{
	cout << User::totalUser << endl;
	for (int i = 0; i < User::totalUser; i++)
	{
		cout << gameUsers[i].Name << endl;
	}
}

void User::saveBasicInfo(User*& gameUsers)
{
	SortUserArrDate(gameUsers);
	ofstream fout("User//Basic Info.txt");
	if (!fout.is_open()) cout << "Opening file error";
	fout << User::totalUser << endl;
	for (int i = 0; i < User::totalUser; i++)
	{
		fout << gameUsers[i].Name << endl;
	}
	fout.close();
}

void User::deleteUsers(User*& gameUsers)
{
	for (int i = 0; i < User::totalUser; i++)
	{
		gameUsers[i].freeUser();
	}
	delete[] gameUsers;
	gameUsers = nullptr;
}

void User::push_backUser(User newUser, User*& gameUsers)
{
	User::totalUser++;
	User* push = new User[totalUser];
	for (int i = 0; i < User::totalUser - 1; i++)
		push[i].copyUser(gameUsers[i]);

	push[User::totalUser - 1].copyUser(newUser);
	delete[] gameUsers;
	gameUsers = push;
}

void User::SavetoArr(User oldUser, User*& gameUsers)
{
	for (int i = 0; i < User::totalUser; i++)
	{
		if (oldUser.Name == gameUsers[i].Name)
		{
			gameUsers[i].freeUser();
			gameUsers[i].copyUser(oldUser);
			return;
		}
	}
}

#pragma endregion

#pragma region Individual
void User::getInfo()
{
	string Link = "User//Info//" + Name + ".txt";
	ifstream fin(Link, ios::in);
	if (!fin.is_open())
	{
		cout << "Error opening file";
		return;
	}

	//Lấy Điểm
	fin.ignore(100, ' ');
	fin >> Score; fin.ignore(1);

	//Lấy Ngày Tháng năm
	fin.ignore(100, ' ');
	fin >> Timesave.tm_mday; fin.ignore(1);
	fin >> Timesave.tm_mon; fin.ignore(1);
	fin >> Timesave.tm_year; fin.ignore(1);

	//Lấy HighScore và Deathtime
	fin.ignore(100, ' ');
	fin >> HighScore; fin.ignore(1);
	fin >> Deathsave.tm_mday; fin.ignore(1);
	fin >> Deathsave.tm_mon; fin.ignore(1);
	fin >> Deathsave.tm_year; fin.ignore(1);

	//Lấy độ dài
	fin.ignore(100, ' ');
	fin >> userSnake.length; fin.ignore(1);
	fin >> userSnake.value; fin.ignore(1);

	//Lấy thân rắn
	fin.ignore(100, ' ');
	userSnake.snake = new Coordinate[userSnake.length];
	for (int i = 0; i < userSnake.length; i++)
	{
		fin >> userSnake.snake[i].x; fin.ignore(1);
		fin >> userSnake.snake[i].y; fin.ignore(1);
	}
	fin.ignore(100, ' ');
	fin >> userSnake.tail.x; fin.ignore(1);
	fin >> userSnake.tail.y; fin.ignore(1);

	//Lấy Direction
	fin.ignore(100, ' ');
	string a;

	fin >> a; fin.ignore(1);
	if (a == "Up")
		userSnake.direction = Up;
	else if (a == "Down")
		userSnake.direction = Down;
	else if (a == "Left")
		userSnake.direction = Left;
	else
		userSnake.direction = Right;

	//Lấy speed
	fin.ignore(100, ' ');
	int SPEED;
	fin >> SPEED; fin.ignore(1);
	userSnake.Speed = milliseconds(SPEED);

	//Lấy FOOD
	fin.ignore(100, ' ');
	fin >> userFood.total; fin.ignore(1);
	fin.ignore(100, ' ');
	userFood.food = new Coordinate[userFood.total];
	for (int i = 0; i < userFood.total; i++)
	{
		fin >> userFood.food[i].x; fin.ignore();
		fin >> userFood.food[i].y; fin.ignore();
	}

	//Lấy Object
	fin.ignore(100, ' ');
	fin >> userObject.total; fin.ignore(1);
	if (userObject.total == 0) userObject.object = nullptr;
	else userObject.object = new Coordinate[userObject.total];
	fin.ignore(100, ' ');
	for (int i = 0; i < userObject.total; i++)
	{
		fin >> userObject.object[i].x; fin.ignore(1);
		fin >> userObject.object[i].y; fin.ignore(1);
	}

	//Lấy Map;
	fin.ignore(100, ' ');
	fin >> userMap.Level; fin.ignore(1);
	fin.ignore(100, ' ');
	fin >> userMap.FoodEaten; fin.ignore(1);
	fin.ignore(100, ' ');
	int time;
	fin >> time;
	userMap.Timeleft = (seconds)time;
	fin.ignore(100, ' ');
	fin >> userMap.inPortal.x; fin.ignore(1);
	fin >> userMap.inPortal.y;
	fin.close();
}

void User::checkInfo()
{
	cout << Name << endl;
	cout << "Score: " << Score << endl;
	cout << "Time: " << Timesave.tm_mday << "/" << Timesave.tm_mon << "/" << Timesave.tm_year << endl;
	cout << "HighScore: " << HighScore << "-" << Deathsave.tm_mday << "/" << Deathsave.tm_mon << "/" << Deathsave.tm_year << endl;
	cout << endl;
	cout << "-Snake:" << endl;
	cout << "Length: " << userSnake.length << "-" << userSnake.value << endl;
	cout << "Body: ";
	for (int i = 0; i < userSnake.length; i++)
	{
		cout << userSnake.snake[i].x << "-" << userSnake.snake[i].y;
		if (i != userSnake.length - 1) cout << ",";
	}
	cout << endl;
	cout << "Tail: " << userSnake.tail.x << "-" << userSnake.tail.y << endl;
	cout << "Direction: " << userSnake.direction << endl;
	cout << "Speed: " << userSnake.Speed.count() << endl;
	cout << endl;
	cout << "-Food:" << endl;
	cout << "Total: " << userFood.total << endl;
	cout << "Food: ";
	for (int i = 0; i < userFood.total; i++)
	{
		cout << userFood.food[i].x << "-" << userFood.food[i].y;
		if (i != userFood.total - 1) cout << ",";
	}
	cout << endl;
	cout << endl;
	cout << "-Object:" << endl;
	cout << "Total: " << userObject.total << endl;
	cout << "Object: ";
	for (int i = 0; i < userObject.total; i++)
	{
		cout << userObject.object[i].x << "-" << userObject.object[i].y;
		if (i != userObject.total - 1) cout << ",";
	}
	cout << endl;
	cout << endl;
	cout << "-Map:" << endl;
	cout << "Level: " << userMap.Level << endl;
	cout << "Foodeaten: " << userMap.FoodEaten << endl;
	cout << "TimeLeft: " << userMap.Timeleft.count() << endl;
	cout << "Portal: " << userMap.inPortal.x << "-" << userMap.inPortal.y;
	cout << "____________________________________________________________\n";
}

void User::saveInfo()
{
	if (Score > HighScore) HighScore = Score;
	string Link = "User//Info//" + Name + ".txt";
	ofstream fout(Link, ios::trunc);
	if (!fout.is_open()) {
		cout << "Error opening file!\n";
		return;
	}
	fout << Name << endl;
	fout << "Score: " << Score << endl;
	fout << "Time: " << Timesave.tm_mday << "/" << Timesave.tm_mon << "/" << Timesave.tm_year << endl;
	fout << "HighScore: " << HighScore << "-" << Deathsave.tm_mday << "/" << Deathsave.tm_mon << "/" << Deathsave.tm_year << endl;
	fout << endl;
	fout << "-Snake:" << endl;
	fout << "Length: " << userSnake.length << "-" << userSnake.value << endl;
	fout << "Body: ";
	for (int i = 0; i < userSnake.length; i++)
	{
		fout << userSnake.snake[i].x << "-" << userSnake.snake[i].y;
		if (i != userSnake.length - 1) fout << ",";
	}
	fout << endl;
	fout << "Tail: " << userSnake.tail.x << "-" << userSnake.tail.y << endl;
	fout << "Direction: " << userSnake.direction << endl;
	fout << "Speed: " << userSnake.Speed.count() << endl;
	fout << endl;
	fout << "-Food:" << endl;
	fout << "Total: " << userFood.total << endl;
	fout << "Food: ";
	for (int i = 0; i < userFood.total; i++)
	{
		fout << userFood.food[i].x << "-" << userFood.food[i].y;
		if (i != userFood.total - 1) fout << ",";
	}
	fout << endl;
	fout << endl;
	fout << "-Object:" << endl;
	fout << "Total: " << userObject.total << endl;
	fout << "Object: ";
	for (int i = 0; i < userObject.total; i++)
	{
		fout << userObject.object[i].x << "-" << userObject.object[i].y;
		if (i != userObject.total - 1) fout << ",";
	}
	fout << endl;
	fout << endl;
	fout << "-Map:" << endl;
	fout << "Level: " << userMap.Level << endl;
	fout << "Foodeaten: " << userMap.FoodEaten << endl;
	fout << "TimeLeft: " << userMap.Timeleft.count() << endl;
	fout << "Portal: " << userMap.inPortal.x << "-" << userMap.inPortal.y;
	fout.close();
}

void User::saveHighScore()
{
#pragma region Save info
	// Xử lý số liệu
	reset();
	if (Score > HighScore)
	{
		HighScore = Score;
		Deathsave = getNow();
	}
#pragma endregion
	string Link = "User//Info//" + Name + ".txt";
	ofstream fout(Link, ios::trunc);
	if (!fout.is_open()) {
		cout << "Error opening file!\n";
		return;
	}
	fout << Name << endl;
	fout << "Score: " << endl;
	fout << "Time: " << Timesave.tm_mday << "/" << Timesave.tm_mon << "/" << Timesave.tm_year << endl;
	fout << "HighScore: " << HighScore << "-" << Deathsave.tm_mday << "/" << Deathsave.tm_mon << "/" << Deathsave.tm_year << endl;
	fout << endl;
	fout << "-Snake:" << endl;
	fout << "Length: " << userSnake.length << endl;
	fout << "Body: ";
	for (int i = 0; i < userSnake.length; i++)
	{
		fout << userSnake.snake[i].x << "-" << userSnake.snake[i].y;
		if (i != userSnake.length - 1) fout << ",";
	}
	fout << endl;
	fout << "Tail: " << userSnake.tail.x << "-" << userSnake.tail.y << endl;
	fout << "Direction: " << userSnake.direction << endl;
	fout << "Speed: " << userSnake.Speed.count() << endl;
	fout << endl;
	fout << "-Food:" << endl;
	fout << "Total: " << userFood.total << endl;
	fout << "Food: ";
	for (int i = 0; i < userFood.total; i++)
	{
		fout << userFood.food[i].x << "-" << userFood.food[i].y;
		if (i != userFood.total - 1) fout << ",";
	}
	fout << endl;
	fout << endl;
	fout << "-Object:" << endl;
	fout << "Total: " << userObject.total << endl;
	fout << "Object: ";
	for (int i = 0; i < userObject.total; i++)
	{
		fout << userObject.object[i].x << "-" << userObject.object[i].y;
		if (i != userObject.total - 1) fout << ",";
	}
	fout << endl;
	fout << endl;
	fout << "-Map:" << endl;
	fout << "Level: " << userMap.Level << endl;
	fout << "Foodeaten: " << userMap.FoodEaten << endl;
	fout << "TimeLeft: " << userMap.Timeleft.count() << endl;
	fout << "Portal: " << userMap.inPortal.x << "-" << userMap.inPortal.y;
	fout.close();
}

void User::freeUser()
{
	Name = "";
	userSnake.deleteSnake();
	userFood.deleteFood();
	userObject.deleteObject();
	userMap.deleteMap();
}

void User::clearInfo()
{
	reset();
	Name = "";
	HighScore = 0;
	userSnake.reset();
	userFood.reset();
	userObject.reset();
	userMap.reset();
}

void User::reCreate()
{
	User Next;
	if (isUser())
	{
		Next.Name = Name;
		Next.Timesave = Timesave;
		Next.HighScore = HighScore;
		Next.Deathsave = Deathsave;
	}
	copyUser(Next);
}

bool User::saveUser()
{
	clearInteractScreen();

#pragma region cosnt value
	//các giá trị
	const int HeadX = InteractOrigin_x + 12;
	const int HeadY = InteractOrigin_y + 2;

	//Bảng to
	const int BoardBigX = InteractOrigin_x + 10;
	const int BoardBigY = InteractOrigin_y + 7;
	const int BoardBigW = GameWidth - 20;
	const int BoardBigH = GameHeight - 10;
	const int ItemX = InteractOrigin_x + 25;
	const int ItemY = InteractOrigin_y + 8 + 2;
	const int ExitX = InteractOrigin_x + 14;
	const int ExitY = InteractOrigin_y + 18;
	const int SaveY = ExitY;
	const int SaveX = InteractOrigin_x + 51;
	//Bảng nhỏ
	const int BoardRightX = InteractOrigin_x + 10 + 21 + 12;
	const int BoardRightY = InteractOrigin_y + 7;
	const int BoardRightW = 25;
	const int BoardRightH = GameHeight - 10;
	const int BoardLeftX = InteractOrigin_x + 2;
	const int BoardLeftY = InteractOrigin_y + 7;
	const int BoardLeftW = GameWidth - 20 - 13;
	const int BoardLeftH = GameHeight - 10;
#pragma endregion

	// Vẽ 1 cái khung nhỏ hơn bên trong cái khung trò chơi
	drawBoard(GameHeight, GameWidth, InteractOrigin_x, InteractOrigin_y);
	drawBoard(BoardBigH, BoardBigW, BoardBigX, BoardBigY);
	// Tiêu đề là chữ result
	setTextColor(245);
	gotoXY(HeadX, HeadY + 0); cout << u8" ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄     ▄  ▄     ▄▄▄▄▄▄▄\n";
	gotoXY(HeadX, HeadY + 1); cout << u8" █     █ █       █       █     █  █        █   \n";
	gotoXY(HeadX, HeadY + 2); cout << u8" █■■■■■▀ █■■■■■■ █▄▄▄▄▄▄ █     █  █        █   \n";
	gotoXY(HeadX, HeadY + 3); cout << u8" █ ▀■▄▄  █             █ █     █  █        █   \n";
	gotoXY(HeadX, HeadY + 4); cout << u8" ▀    ▀▀ ▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀  ▀▀▀▀▀▀  ▀▀▀  \n";

	// Báo cáo màn chơi - điểm - độ dài - tốc độ của user gọi hàm nầy
	gotoXY(InteractOrigin_x + 30, InteractOrigin_y + 8);
	cout << "USER INFO";
	setTextColor(250);
	gotoXY(ItemX, ItemY);
	cout << "Level        : ";
	gotoXY(ItemX, ItemY + 2);
	cout << "Score        : ";
	gotoXY(ItemX, ItemY + 4);
	cout << "Snake's size : ";
	gotoXY(ItemX, ItemY + 6);
	cout << "Snake's speed: ";
	setTextColor(240);
	gotoXY(ItemX + 15, ItemY);
	cout << userMap.Level;
	gotoXY(ItemX + 15, ItemY + 2);
	cout << Score;
	gotoXY(ItemX + 15, ItemY + 4);
	cout << userSnake.length;
	gotoXY(ItemX + 15, ItemY + 6);
	cout << userSnake.Speed.count();

	// Yêu cầu người chơi chọn Lựu kết quá hoặc ko
	setTextColor(245);
	gotoXY(ExitX, ExitY); cout << "EXIT";
	gotoXY(ExitX - 2, ExitY + 1); cout << "[PRESS E]";
	gotoXY(SaveX, SaveY); cout << "SAVE";
	gotoXY(SaveX - 2, SaveY + 1); cout << "[PRESS S]";
	setTextColor(240);
	char key = NULL;
	do
	{
		GetWaitKey(key);
		if ((key == 'S' || key == 's') && isUser()) {
			sound.playEnter();
			return true;
		}
		// Nếu yêu cầu Lưu kết quả thì cin vào name của user gọi hàm nầy
		if (key == 'S' || key == 's')
		{
			sound.playEnter();
			clearInteractScreen();
			setTextColor(245);
			gotoXY(HeadX, HeadY + 0); cout << u8" ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄     ▄  ▄     ▄▄▄▄▄▄▄\n";
			gotoXY(HeadX, HeadY + 1); cout << u8" █     █ █       █       █     █  █        █   \n";
			gotoXY(HeadX, HeadY + 2); cout << u8" █■■■■■▀ █■■■■■■ █▄▄▄▄▄▄ █     █  █        █   \n";
			gotoXY(HeadX, HeadY + 3); cout << u8" █ ▀■▄▄  █             █ █     █  █        █   \n";
			gotoXY(HeadX, HeadY + 4); cout << u8" ▀    ▀▀ ▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀  ▀▀▀▀▀▀  ▀▀▀  \n";

			//Khung quy định
			drawBoard(BoardRightH, BoardRightW, BoardRightX, BoardRightY);
			setTextColor(252);
			gotoXY(BoardRightX + 2, BoardRightY + 2);
			cout << "Contains only";
			gotoXY(BoardRightX + 2, BoardRightY + 3);
			cout << "alphanumeric characters";
			gotoXY(BoardRightX + 2, BoardRightY + 5);
			cout << "=> From A - Z (a - z)";
			gotoXY(BoardRightX + 2, BoardRightY + 7);
			cout << "=> From 0-9";
			gotoXY(BoardRightX + 2, BoardRightY + 9);
			cout << "At most 15 characters";

			//Khung nhập
			drawBoard(BoardLeftH, BoardLeftW, BoardLeftX, BoardLeftY);
			while (1)
			{
				gotoXY(BoardLeftX + 10, BoardLeftY + 4);
				cout << "Enter your name: " << endl;
				gotoXY(BoardLeftX + 9, BoardLeftY + 5);
				cout << "=> ";
				char Input = NULL;
				do
				{
					GetManyKey(Input);
					if (Input == '\b' && Name.length() > 0) Name.pop_back();
					else if (Input == ENTER) break;
					else if (Name.length() < 15) Name += Input;
					gotoXY(39, 17); cout << Name + string(" ") * (15 - Name.length());
				} while (Input != ENTER);

				string Link = "User//Info//" + Name + ".txt";
				ifstream ftemp;
				ftemp.open(Link);
				if (isName(Name) && ftemp.fail() && Name.length() != 0)
				{

					break;
				}
				else
				{
					sound.playError();
					Name.clear();
					gotoXY(39, 17); cout << "             ";
					gotoXY(BoardLeftX + 2, BoardLeftY + 1);
					if (!ftemp.fail())
					{
						cout << "Your input already exists!";
						gotoXY(BoardLeftX + 17, BoardLeftY + 2);
						cout << "Please try again!";
					}
					else
					{
						cout << "Your input is invalid!     ";
						gotoXY(BoardLeftX + 17, BoardLeftY + 2);
						cout << "Please try again!";
					}
					string t = "";
					for (int i = 0; i < Name.size() + 5; i++)
						t += " ";
					gotoXY(BoardLeftX + 10, BoardLeftY + 5);
					cout << t;
				}
			}
			clearInteractScreen();
			drawBoard(BoardBigH, BoardBigW, BoardBigX, BoardBigY);
			setTextColor(245);
			gotoXY(HeadX, HeadY + 0); cout << u8" ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄     ▄  ▄     ▄▄▄▄▄▄▄\n";
			gotoXY(HeadX, HeadY + 1); cout << u8" █     █ █       █       █     █  █        █   \n";
			gotoXY(HeadX, HeadY + 2); cout << u8" █■■■■■▀ █■■■■■■ █▄▄▄▄▄▄ █     █  █        █   \n";
			gotoXY(HeadX, HeadY + 3); cout << u8" █ ▀■▄▄  █             █ █     █  █        █   \n";
			gotoXY(HeadX, HeadY + 4); cout << u8" ▀    ▀▀ ▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀  ▀▀▀▀▀▀  ▀▀▀  \n";
			gotoXY(BoardBigX + BoardBigW / 2 - 10, BoardBigY + BoardBigH / 2);
			cout << "YOUR WORK HAS BEEN SAVED !!";
			Sleep(2000);
			return true;
		}
		else if (key == 'e' || key == 'E')
		{
			sound.playEnter();
			return false;
		}
	} while (key != 'e' && key != 'E' && key != 's' && key != 'S');
}

void User::resultOnDeath()
{
	clearInteractScreen();

#pragma region cosnt value
	//các giá trị
	const int HeadX = InteractOrigin_x + 10;
	const int HeadY = InteractOrigin_y + 2;

	//Bảng to
	const int BoardBigX = InteractOrigin_x + 10;
	const int BoardBigY = InteractOrigin_y + 7;
	const int BoardBigW = GameWidth - 20;
	const int BoardBigH = GameHeight - 10;
	const int ItemX = InteractOrigin_x + 25;
	const int ItemY = InteractOrigin_y + 8 + 2;
	const int ExitX = InteractOrigin_x + 14;
	const int ExitY = InteractOrigin_y + 18;
	const int SaveY = ExitY;
	const int SaveX = InteractOrigin_x + 51;
#pragma endregion

	// Vẽ 1 cái khung nhỏ hơn bên trong cái khung trò chơi
	drawBoard(GameHeight, GameWidth, InteractOrigin_x, InteractOrigin_y);
	drawBoard(BoardBigH, BoardBigW, BoardBigX, BoardBigY);
	// Tiêu đề là chữ result
	setTextColor(245);


	gotoXY(HeadX, HeadY + 0); cout << u8" ▄▄▄▄   ▄▄   ▄▄    ▄▄ ▄▄▄▄▄    ▄▄▄▄▄ ▄     ▄ ▄▄▄▄▄ ▄▄▄▄▄\n";
	gotoXY(HeadX, HeadY + 1); cout << u8" █     ▄▀▀▄  █▀▄  ▄▀█ █        █   █ ▀█   █▀ █     █   █\n";
	gotoXY(HeadX, HeadY + 2); cout << u8" █ ▀█ ▄█▄▄█▄ █ ▀▄▄▀ █ █▀▀▀▀    █   █  ▀▄ ▄▀  █▀▀▀▀ █▀█▀▀\n";
	gotoXY(HeadX, HeadY + 3); cout << u8" ▀▀▀▀ ▀    ▀ ▀  ▀▀  ▀ ▀▀▀▀▀    ▀▀▀▀▀    ▀    ▀▀▀▀▀ ▀  ▀▀\n";


	// Báo cáo màn chơi - điểm - độ dài - tốc độ của user gọi hàm nầy
	gotoXY(InteractOrigin_x + 30, InteractOrigin_y + 8);
	cout << "USER INFO";
	setTextColor(250);
	gotoXY(ItemX, ItemY);
	cout << "Level        : ";
	gotoXY(ItemX, ItemY + 2);
	cout << "Score        : ";
	gotoXY(ItemX, ItemY + 4);
	cout << "Snake's size : ";
	gotoXY(ItemX, ItemY + 6);
	cout << "Snake's speed: ";
	setTextColor(240);
	gotoXY(ItemX + 15, ItemY);
	cout << userMap.Level;
	gotoXY(ItemX + 15, ItemY + 2);
	cout << Score;
	gotoXY(ItemX + 15, ItemY + 4);
	cout << userSnake.length;
	gotoXY(ItemX + 15, ItemY + 6);
	cout << userSnake.Speed.count();
	stop(2000ms);
	gotoXY(BoardBigX + BoardBigW / 2 - 12, BoardBigY + BoardBigH + 1);
	cout << u8"Press any key to continue...";
	char key;
	GetKey(key);
}

// Hàm để lấy điểm cao
void User::reset()
{
	Timesave = getNow();
	if (HighScore < Score) HighScore = Score;
	Score = 0;
	Deathsave = getNow();

	userSnake.reset();
	userFood.reset();
	userObject.reset();
	userMap.reset();
}

void User::copyUser(User Out)
{
	Name = Out.Name;
	Score = Out.Score;
	Timesave = Out.Timesave;
	HighScore = Out.HighScore;
	Deathsave = Out.Deathsave;

	// Snake
	userSnake.length = Out.userSnake.length;
	if (userSnake.length == 0) userSnake.snake = nullptr;
	else userSnake.snake = new Coordinate[userSnake.length];
	for (int i = 0; i < userSnake.length; i++)
		userSnake.snake[i] = Out.userSnake.snake[i];
	userSnake.Death = Out.userSnake.Death;
	userSnake.direction = Out.userSnake.direction;
	userSnake.Speed = Out.userSnake.Speed;
	userSnake.value = Out.userSnake.value;

	// Food
	userFood.total = Out.userFood.total;
	if (Out.userFood.total == 0) userFood.food = nullptr;
	else
	{
		userFood.food = new Coordinate[userFood.total];
		for (int i = 0; i < userFood.total; i++)
			userFood.food[i] = Out.userFood.food[i];
	}

	// Object
	userObject.total = Out.userObject.total;
	if (userObject.total == 0) userObject.object = nullptr;
	else userObject.object = new Coordinate[userObject.total];
	for (int i = 0; i < userObject.total; i++)
		userObject.object[i] = Out.userObject.object[i];

	// Map
	userMap.Level = Out.userMap.Level;
	userMap.inPortal = Out.userMap.inPortal;
	userMap.FoodEaten = Out.userMap.FoodEaten;
	userMap.Timeleft = Out.userMap.Timeleft;
}

bool User::isUser()
{
	if (Name != "") return true;
	else return false;
}

bool User::isAlreadyUser(User* gameUsers)
{
	for (int i = 0; i < User::totalUser; i++)
	{
		if (Name == gameUsers[i].Name) return true;
	}
	return false;
}

bool User::isReset()
{
	if (userSnake.length == 0) return true;
	else return false;
}
#pragma endregion

#pragma region Algorithm
void SortUserArrDate(User* a, int R, int L)
{
	if (R == -1) R = a->totalUser - 1;
	int i = L, j = R;
	User x = a[(L + R) / 2];
	do
	{
		while (DateToDay(x.Timesave) < DateToDay(a[i].Timesave)) i++;
		while (DateToDay(x.Timesave) > DateToDay(a[j].Timesave)) j--;
		if (i <= j)
		{
			swap(a[i], a[j]);
			i++;
			j--;
		}
	} while (i <= j);

	if (L < j)
	{
		SortUserArrDate(a, j, L);
	}
	if (R > i)
	{
		SortUserArrDate(a, R, i);
	}
}
#pragma endregion

#pragma region Overloaded

#pragma endregion


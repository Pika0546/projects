#include "GameHeader.h"
#include "SoundHeader.h"

#pragma pack(1)
#if 1
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitle(L"Snake The Game");

    #pragma region Main algorithm
    FixConsoleWindow();
    resizeConsole(535, 765);
    ShowConsoleCursor(false);
    drawBoard(BoardHeight, BoardWidth, BoardOrigin_x, BoardOrigin_y);
    #pragma endregion

    #pragma region Default variables
    User* user = nullptr;
    Screen screen = Screen::StartGame;
    char key = RIGHT_;
    char MainKey = NULL;

    User MainUser;
    #pragma endregion

    #pragma region Handle one time before starting game
    user->getAllInfo(user);
    #pragma endregion

    #pragma region Handle Login Screen
    sound.playBackground();
    drawStartingMenu();
    clearInteractScreen(15, 8, 60, 10);
    drawMenuBoard();
    drawInteractBoard();
    drawMenuOptions();
    #pragma endregion

    #pragma region Handle Interact Screen
    do
    {
        drawSelectedOption(ScrtoI(screen));
        switch (screen)
        {
        case Screen::StartGame:
            #pragma region StartGame
            clearInteractScreen();
            drawSnakeTitle();
            drawStartGameScreen();

            if (MainKey == ENTER)
            {
                sound.playEnter();
                StartIfLoad:
                clearInteractScreen();

                // Set before render ;
                if (!MainUser.isUser() || MainUser.isReset()) MainUser.reCreate();

                // Starting render
                do
                {
                    // Xử lý màn
                    clearMenuScreen();
                    MainUser.drawBeginLevelState();
                    MainUser.userSnake.setBegin(MainUser.userMap);
                    MainUser.userMap.drawLevel();
                    MainUser.userMap.CreateMap();
                    MainUser.userMap.drawBegin();
                    MainUser.userFood.firstGenerate(MainUser.userSnake, MainUser.userObject, MainUser.userMap);
                    MainUser.userObject.beginWithLevel(MainUser.userSnake, MainUser.userFood, MainUser.userMap);
                    MainUser.userObject.drawBegin();

                    do
                    {
                        MainUser.userSnake.draw();
                        MainUser.userFood.draw();
                        if (MainUser.userMap.isOutOfPortal(MainUser.userSnake) && MainUser.userMap.Outable) MainUser.userMap.clearEntrance();

                        // Xử lý ăn - Tăng độ dài
                        if (MainUser.userMap.Level % 5 == 0) countdown(MainUser.userMap.Timeleft);
                        if (MainUser.userFood.isFood(MainUser.userSnake.snake[0]))
                        {
                            sound.playEat1();
                            MainUser.Score += (MainUser.userMap.Level * 2 + 3);
                            MainUser.userSnake.eat(1);
                            if (MainUser.userMap.Level % 5 != 0)MainUser.userMap.FoodEaten++;
                            MainUser.userFood.eaten(MainUser.userSnake, MainUser.userObject, MainUser.userMap, MainUser.userSnake.snake[0]);
                        }
                        if (MainUser.userMap.isEnough()) MainUser.userFood.drawDelete();

                        // Xử lý Object - TimeFood
                        if (MainUser.userObject.isTimeFood(MainUser.userSnake.snake[0]))
                        {
                            sound.playEat2();
                            if (MainUser.userSnake.value == 0) MainUser.drawNote(u8"↑ +3 seconds ↑");
                            else MainUser.drawNote(u8"↑ +1 seconds ↑");
                            MainUser.Score += (MainUser.userMap.Level * 5 + 5);
                            if (MainUser.userSnake.value == 0) MainUser.userMap.Timeleft += 3s;
                            else MainUser.userMap.Timeleft++;
                            MainUser.userSnake.eat(3);
                            MainUser.userObject.reGenerate(MainUser.userSnake, MainUser.userFood, MainUser.userMap, MainUser.userSnake.snake[0]);
                        }
                        if (MainUser.userObject.eatable && waitAddtime(800ms)) MainUser.drawNote("              ");

                        if (MainUser.userObject.eatable && MainUser.userMap.isEnough()) MainUser.userObject.drawDelete(true);
                        MainUser.userObject.move(MainUser.userSnake, MainUser.userFood, MainUser.userMap);

                        // Xử lý cổng ra
                        if (MainUser.userMap.isEnough() && MainUser.userMap.Portalable) MainUser.userMap.createPortal(MainUser.userSnake);

                        // Xử lý di chuyển
                        GetUpgradeWaitKey(key);
                        if (wait(MainUser.userSnake.Speed))
                        {
                            MainUser.userSnake.eat();
                            MainUser.drawLevelState();
                            switch (key)
                            {
                            case DOWN_:
                                MainUser.userSnake.changeDirection(Down);
                                MainUser.userSnake.move();
                                break;
                            case UP_:
                                MainUser.userSnake.changeDirection(Up);
                                MainUser.userSnake.move();
                                break;
                            case LEFT_:
                                MainUser.userSnake.changeDirection(Left);
                                MainUser.userSnake.move();
                                break;
                            case RIGHT_:
                                MainUser.userSnake.changeDirection(Right);
                                MainUser.userSnake.move();
                                break;
                            case p:
                            case P:
                                sound.playEnter();
                                MainUser.userMap.Portalable = true;
                                if (!MainUser.userMap.isOutOfPortal(MainUser.userSnake)) MainUser.userMap.Outable = true;
                                if (!showPause())
                                {
                                    // Dùng tên để lưu
                                    if (MainUser.isUser())
                                    {
                                        MainUser.saveInfo();
                                        User::SavetoArr(MainUser, user);
                                    }
                                    else if (MainUser.saveUser())
                                    {
                                        MainUser.saveInfo();
                                        User::push_backUser(MainUser, user);
                                        User::saveBasicInfo(user);
                                    }
                                    MainUser.freeUser();
                                    MainUser.reCreate();
                                    clearInteractScreen();
                                    goto OutSnakeLoop;
                                }
                                else
                                {
                                    key = DtoK(MainUser.userSnake.direction);
                                    clearInteractScreen();
                                    MainUser.userFood.draw();
                                    MainUser.userMap.drawLevelWall();
                                    if (MainUser.userSnake.length < MainUser.userMap.getBaseLength()) MainUser.userMap.drawBegin();
                                    countdown(MainUser.userMap.Timeleft, true);
                                }
                                break;
                            default:
                                MainUser.userSnake.move();
                                break;
                            }

                            // Xử lý qua màn - Kiểm tra rắn - Xử lý tốc độ

                            if (MainUser.userSnake.isInPortal(MainUser.userMap))
                            {
                                if (MainUser.userMap.Level % 5 == 0)
                                {
                                    sound.playPassLevel5();
                                }
                                else sound.playPassLevel();

                                MainUser.userMap.drawEnterAnimation(MainUser.userSnake);

                                clearInteractScreen();
                                drawInteractBoard();
                                MainUser.userMap.Level++;
                                MainUser.userMap.resetbyPasslevel();
                                MainUser.userSnake.resetbyPasslevel();
                                MainUser.userFood.resetbyPasslevel();
                                MainUser.userObject.reset();
                                key = RIGHT_;
                                break;
                            }
                            else
                            {
                                MainUser.userSnake.isDeath(MainUser.userObject, MainUser.userMap);
                            }
                        }
                    } while (!MainUser.userSnake.Death);
                } while (!MainUser.userSnake.Death);

                if (MainUser.userSnake.Death)
                {
                    if (MainUser.saveUser())
                    {
                        if (MainUser.isAlreadyUser(user))
                        {
                            MainUser.resultOnDeath();
                            MainUser.reset();
                            MainUser.saveInfo();
                            User::SavetoArr(MainUser, user);
                            User::saveBasicInfo(user);
                        }
                        else
                        {
                            MainUser.reset();
                            MainUser.saveInfo();
                            User::push_backUser(MainUser, user);
                            User::saveBasicInfo(user);
                        }
                    }
                    MainUser.freeUser();
                    MainUser.reCreate();
                    clearInteractScreen();
                }

                OutSnakeLoop:
                key = NULL;
                #pragma region ReDraw
                screen = Screen::StartGame;
                clearMenuScreen();
                clearBelowScreen();
                drawMenuOptions();
                drawSelectedOption(ScrtoI(screen));
                drawSnakeTitle();
                drawStartGameScreen();
                #pragma endregion
            }

            drawInteractBoard();

            break;
            #pragma endregion
        case Screen::LoadGame:
            #pragma region LoadGame
            clearInteractScreen();
            drawLoadGameScreen(user);
            drawLoadGameTitle();

            if (MainKey == ENTER || MainKey == RIGHT_)
            {
                sound.playEnter();
                int base = showLoadGame(user);
                if (base != -1) // Xóa?
                {
                    MainUser.copyUser(user[base]);
                    clearInteractScreen();
                    user[base].userSnake.draw();
                    Ready(user[base]);
                    goto StartIfLoad;
                }
                else
                {
                    drawLoadGameScreen(user);
                }
            }
            break;
            #pragma endregion
        case Screen::HighScore:
            #pragma region HighScore
            clearInteractScreen();
            showHighScore(user);
            drawHighScoreTitle();
            break;
            #pragma endregion
        case Screen::Tutorial_n_Introduction:
            #pragma region Tutorial
            clearInteractScreen();
            drawIntroduction();
            drawIntroductionTitle();
            break;
            #pragma endregion
        case Screen::ExitGame:
            #pragma region Exit Game
            clearInteractScreen();
            drawExitGameTitle();
            drawExit();

            if (MainKey == ENTER)
            {
                sound.playEnter();
                drawGoodByeTitle();
                User::saveBasicInfo(user);
                User::deleteUsers(user);
                delete[] user;

                MainUser.freeUser();

                QuitGame();
                gotoXY(End_x, End_y);
                exit(0);
            }
            break;
            #pragma endregion
        }
        GetScreenKey(MainKey, screen);
        Option(screen, MainKey);
        sound.playMenu();
    } while (true);
    #pragma endregion
}
#endif



#if 0
int main()
{
    SetConsoleOutputCP(CP_UTF8);
   /* User test;
    test.Name = "AD4Begin";
    SaveInfo(test, "nhap.bin");
    User test1;
    getInfo(test1, "nhap.bin");
    test1.checkInfo();*/
    cout << sizeof(User);
}
#endif
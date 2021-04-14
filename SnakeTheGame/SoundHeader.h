#include "GameHeader.h"

#define _CRT_SECURE_NO_WARNINGS
#ifndef UNICODE
#define UNICODE
#endif
#include <stdio.h>
#pragma comment(lib, "winmm.lib")

#ifndef SOUND_HEADER
#define SOUND_HEADER

struct SoundEffect;
struct Sound;


#pragma region Sound
struct Sound
{
	LPCWSTR filename;
	Sound();
	~Sound();
	//Thiết lập đường dẫn tên file âm thanh
	void SetSound(string file);
	//Lặp âm thanh cho tới khi gọi hàm StopPlaying hoặc có âm thanh khác dc play
	bool PlayLoop();
	//Chơi 1 lần và dừng toàn bộ chương trình tới khi kết thúc âm thanh
	bool PlayOnce();
	//Chơi 1 lần và chạy ngầm, sẽ dừng khi có âm thanh khác dc chơi hoặc kết thúc âm thanh
	bool PlayOnceBackground();
	//Dừng âm thanh
	bool StopPlaying();
};

struct SoundEffect
{
	Sound eat1;
	Sound eat2;
	Sound lose2;
	Sound passLevel;
	Sound lose1;
	Sound background;
	Sound menu;
	Sound enter;
	Sound clock;
	Sound timeoff;
	Sound passLevel5;
	Sound ready;
	Sound credit;
	Sound error;
	Sound start;


	SoundEffect();
	~SoundEffect();

	//Nhạc ra cổng
	void playStart();

	//Mở nhạc credit
	void playCredit();

	//Nhạc nhập sai
	void playError();


	//Mở sound ăn
	void playEat1();
	void playEat2();
	//Mở sound thua
	void playLose1();
	void playLose2();
	//Mở sound qua màn
	void playPassLevel();
	void playPassLevel5();
	//Mở nhạc nền ban đầu
	void playBackground();

	//Mở nhạc khi đang chọn trên menu
	void playMenu();

	//Mở nhạc khi enter chọn gì đó
	void playEnter();

	//mở nhạc khung ready set go
	void playReady();

	//Mở nhạc đồng hồ
	void playClock();

	//Nhạc time off
	void playTimeOff();

	//Stop mọi âm thanh đang dc mở
	void StopSound();

};

static SoundEffect sound;
#endif // ! SOUND_HEADER
#pragma once

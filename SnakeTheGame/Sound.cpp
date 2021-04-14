#include "GameHeader.h"
#include "SoundHeader.h"

#pragma region Sound
Sound::Sound()
{
	filename = NULL;
}

Sound::~Sound()
{
	if (filename != NULL)
	{
		delete filename;
		filename = NULL;
	}

}

void Sound::SetSound(string file)
{
	wchar_t* wtext = new wchar_t[file.size() + 1];
	mbstowcs(wtext, file.c_str(), file.size() + 1);//Plus null
	filename = wtext;

}

bool Sound::PlayLoop()
{
	return PlaySound(filename, NULL, SND_LOOP | SND_ASYNC | SND_FILENAME | SND_NOSTOP);
}

bool Sound::PlayOnce()
{
	return PlaySound(filename, NULL, SND_FILENAME | SND_SYNC);
}

bool Sound::PlayOnceBackground()
{
	return PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC);
}

bool Sound::StopPlaying()
{
	return PlaySound(NULL, NULL, NULL);
}
#pragma endregion

#pragma region SoundEffect
SoundEffect::SoundEffect()
{
	start.SetSound("Audio//start.wav");
	credit.SetSound("Audio//credit.wav");
	eat1.SetSound("Audio//eating.wav");
	eat2.SetSound("Audio//CartoonAccent.wav");
	lose1.SetSound("Audio//lose1.wav");
	lose2.SetSound("Audio//lose2.wav");
	passLevel.SetSound("Audio//passLeve2.wav");
	background.SetSound("Audio//Snake_runner.wav");
	menu.SetSound("Audio//menu0.wav");
	enter.SetSound("Audio//Enter2.wav");
	clock.SetSound("Audio//10tick.wav");
	timeoff.SetSound("Audio//portal.wav");
	passLevel5.SetSound("Audio//pass5.wav");
	ready.SetSound("Audio//count.wav");
	error.SetSound("Audio//error.wav");
}

SoundEffect::~SoundEffect()
{

}

void SoundEffect::playStart()
{
	start.PlayOnceBackground();
}

void SoundEffect::playBackground()
{
	background.PlayLoop();
}

void SoundEffect::playEat1()
{
	eat1.PlayOnceBackground();
}

void SoundEffect::playEat2()
{
	eat2.PlayOnceBackground();
}

void SoundEffect::playEnter()
{
	enter.PlayOnceBackground();
}

void SoundEffect::playLose1()
{
	lose1.PlayOnceBackground();
}

void SoundEffect::playCredit()
{
	credit.PlayOnceBackground();
}

void SoundEffect::playLose2()
{
	lose2.PlayOnceBackground();
}

void SoundEffect::playPassLevel()
{
	passLevel.PlayOnceBackground();
}

void SoundEffect::playClock()
{
	clock.PlayOnceBackground();
}

void SoundEffect::playReady()
{
	ready.PlayOnceBackground();
}

void SoundEffect::playTimeOff()
{
	timeoff.PlayOnceBackground();
}

void SoundEffect::playMenu()
{
	menu.PlayOnceBackground();
}

void SoundEffect::playPassLevel5()
{
	passLevel5.PlayOnceBackground();
}

void SoundEffect::playError()
{
	error.PlayOnceBackground();
}

void SoundEffect::StopSound()
{
	PlaySound(NULL, NULL, NULL);
}
#pragma endregion
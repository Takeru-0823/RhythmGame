#include "stdlib.h"
#include "time.h"
#include "Variable.h"
#include "Resource.h"

enum Scene
{
	TITLE,
	PLAY,
};

Scene title();
Scene play();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetWindowText("‰¹ƒQ[");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	imgTitle = LoadGraph("RhythmGameTitle.png");
	bgm = LoadSoundMem("Digilune.mp3");
	perfectSE = LoadSoundMem("perfectSE.mp3");
	goodSE = LoadSoundMem("goodSE.mp3");
	badSE = LoadSoundMem("badSE.mp3");

	Scene scene = TITLE;

	//PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);


	while (1)
	{
		ClearDrawScreen();

		switch (scene)
		{
		case TITLE:
			scene = title();
			break;
		case PLAY:
			scene = play();
			break;
		}

		ScreenFlip();
		WaitTimer(33);
		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	DxLib_End();
	return 0;

}

Scene title()
{
	DrawGraph(300, 200, imgTitle, TRUE);

	SetFontSize(50);
	DrawString(350, 400, "PUSH SPACE", WHITE);
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
		return PLAY;
	}
	return TITLE;
}

Scene play()
{
	POSITION scorePos;
	scorePos.x = 10;
	scorePos.y = 590;

	static POSITION notesPos = { WIDTH, CENTER };

	static SCORE score = {0, 0, 0};

	static int notesSpeed = 10;

	static bool hitKey = false;

	SetFontSize(40);
	DrawFormatString(scorePos.x, scorePos.y, WHITE, "P:%d  G:%d  B:%d", score.perfect, score.good, score.bad);

	DrawCircle(CENTER, CENTER, RADIUS, WHITE, TRUE);

	notesPos.x = notesPos.x - notesSpeed;
	DrawCircle(notesPos.x, notesPos.y, RADIUS, RED, TRUE);

	if (notesPos.x >= WIDTH - 20)
	{
		notesSpeed = rand() % 20 + 5;
		hitKey = false;
	}
	else if (notesPos.x < 0)
	{
		notesPos.x = WIDTH;
	}



	if (CheckHitKey(KEY_INPUT_SPACE) && hitKey == false)
	{
		hitKey = true;
		int distance = (CENTER - notesPos.x);

		if (distance < PERFECTDISTANCE && distance > -PERFECTDISTANCE)
		{
			PlaySoundMem(perfectSE, DX_PLAYTYPE_BACK);
			score.perfect++;
		}
		else if (distance < GREATDISTANCE && distance > -GREATDISTANCE)
		{
			PlaySoundMem(goodSE, DX_PLAYTYPE_BACK);
			score.good++;
		}
		else
		{
			PlaySoundMem(badSE, DX_PLAYTYPE_BACK);
			score.bad++;
		}

		notesPos.x = WIDTH;

	}
	return PLAY;

}



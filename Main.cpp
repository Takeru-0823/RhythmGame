#include "stdlib.h"
#include "Color.h"
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
	SetWindowText("âπÉQÅ[");
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

	static int blink = 0;

	blink++;
	if ((blink / 20) % 2 == 0) 
	{
		SetFontSize(50);
		DrawString(350, 400, "PUSH SPACE", WHITE);
	}

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
		return PLAY;
	}
	return TITLE;
}

Scene play()
{
	POSITION scorePos = { 10, 590 };
	static POSITION notesPos = { WIDTH, CENTER };
	static SCORE score = {0, 0, 0};
	static int beforeSpace = 0;
	static bool showJudge = false;
	static int timer = 50;

	SetFontSize(40);
	DrawFormatString(scorePos.x, scorePos.y, WHITE, "P:%d  G:%d  B:%d", score.perfect, score.good, score.bad);

	DrawCircle(CENTER, CENTER, RADIUS + 10, WHITE, FALSE);

	notesPos.x -= SPEED;
	DrawCircle(notesPos.x, notesPos.y, RADIUS, RED, TRUE);

	if (notesPos.x < 0)
	{
		notesPos.x = WIDTH;
	}

	int nowSpace = CheckHitKey(KEY_INPUT_SPACE);

	if (beforeSpace == 0 && nowSpace == 1)
	{
		showJudge = true;
		int distance = abs((CENTER - notesPos.x));

		if (distance <= PERFECTDISTANCE)
		{
			SetFontSize(30);
			DrawString(270, 200, "Perfect", RED);

			PlaySoundMem(perfectSE, DX_PLAYTYPE_BACK);
			score.perfect++;
		}
		else if (distance <= GREATDISTANCE)
		{
			SetFontSize(30);
			DrawString(290, 200, "Good", YELLOW);

			PlaySoundMem(goodSE, DX_PLAYTYPE_BACK);
			score.good++;
		}
		else
		{
			SetFontSize(30);
			DrawString(290, 200, "Bad", BLUE);

			PlaySoundMem(badSE, DX_PLAYTYPE_BACK);
			score.bad++;
		}

	}
	beforeSpace = nowSpace;
	return PLAY;

}



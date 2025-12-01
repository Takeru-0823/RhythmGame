#pragma once

const int WIDTH = 960, HEIGHT = 640;
const int CENTER = 320;
const int RADIUS = 50;
const int PERFECTDISTANCE = 20;
const int GREATDISTANCE = 50;
const int SPEED = 20;

struct POSITION
{
	int x;
	int y;
};

struct SCORE
{
	int perfect = 0;
	int good = 0;
	int bad = 0;
};



#pragma once
class ChessPoint
{
public:
	POINT p;
	POINT up;
	POINT down;
	POINT left;
	POINT right;
	ChessPoint(POINT pxy);
	~ChessPoint();
};


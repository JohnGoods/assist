#include "stdafx.h"
#include "ChessPoint.h"


ChessPoint::ChessPoint(POINT pxy)
{
	up = pxy; down = pxy; left = pxy; right = pxy;
	p = pxy;
	up.y = pxy.y - 1;
	down.y = pxy.y + 1;
	left.x = pxy.x - 1;
	right.x = pxy.x + 1;
}


ChessPoint::~ChessPoint()
{
}

#pragma once
#include "Block.h"
class Player : public Block
{
public:
	Player();
	void tryMove(const int& x, const int& y, Block*** block);
};


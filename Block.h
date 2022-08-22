#pragma once
#include "constants.h"
#include <qcolor.h>


class Block
{
protected:
	int m_x, m_y; // координаты
	QColor m_color;
public:
	Block();
	Block(const int& x, const int& y, const QColor& color);
	void operator=(const Block&);
	int GetX() const;
	int GetY() const;
	QColor GetColor() const;
	void SetColor(const QColor& other);
};
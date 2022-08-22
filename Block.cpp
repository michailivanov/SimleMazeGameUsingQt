#include "Block.h"


Block::Block() : m_color("Black"), m_x(0), m_y(0){}

Block::Block(const int& x, const int& y, const QColor& color) : m_x(x), m_y(y), m_color(color) {}

void Block::operator=(const Block& other)
{
	m_x = other.m_x;
	m_y = other.m_y;
	m_color = other.m_color;
}

int Block::GetX() const
{
	return m_x;
}

int Block::GetY() const
{
	return m_y;
}

QColor Block::GetColor() const
{
	return m_color;
}

void Block::SetColor(const QColor& other)
{
	m_color = other;
}

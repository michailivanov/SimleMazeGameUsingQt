#include "Player.h"

Player::Player() : Block(1, MAZE_HEIGHT - 2, "Green"){}

void Player::tryMove(const int& x, const int& y, Block*** block)
{
    if (block[x][y]->GetColor() == "white")
    {
        if ((m_x == x && m_y == y - 1) || //top
            (m_x == x - 1 && m_y == y) || //left
            (m_x == x + 1 && m_y == y) || //right
            (m_x == x && m_y == y + 1)) //bottom

        {
            m_x = x;
            m_y = y;
            
        }
    }
}



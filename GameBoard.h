#pragma once
#include <qwidget.h>
#include <qpainter.h>
#include <QKeyEvent>
#include <qstack.h>

#include "constants.h"
#include "Block.h"
#include "Player.h"

class GameBoard : public QWidget
{
    Q_OBJECT

private:
    Block*** m_block;
    Player* m_player;
    Block* m_finish;
    bool playerCanMove;
    void GenerateAbsoluteRandom();
    void GenerateGreatMaze();

protected:
    void paintEvent(QPaintEvent* event) override;

public:
    GameBoard();
    ~GameBoard();
    void drawSquare(QPainter* p, Block* block);
    void setPlayerCanMove(const bool&);
    void keyPressEvent(QKeyEvent* event) override;

public slots:
    void GenerateNewMazeLevel();

signals:
    void PlayerReachedFinish();
};


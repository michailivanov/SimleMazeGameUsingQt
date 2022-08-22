#pragma once
#include "GameBoard.h"
#include <qwidget.h>
#include <qlabel.h> // Для надписей "You Win" и "You Lose"
#include <qlcdnumber.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qtimer.h>
#include <qapplication.h>
#include <qgridlayout.h>

class GameWindow : public QWidget
{
	Q_OBJECT

public:
    GameWindow();
    void keyPressEvent(QKeyEvent* event);

private:
    void GameOver();
    int timeLeft;
    bool isStarted;
    QTimer* timer;
    GameBoard* board;
    QLCDNumber* LCDNum;
    QPushButton* startButton;
    QPushButton* quitButton;
    QPushButton* newLevelButton;
    QLabel* loseLable;
    QLabel* winLable;

signals:
    void timeIsUp();

public slots:
    void UpdateLcdTimer();
    void GameStart();
    void GameLose();
    void GameWin();
    void NewLevel();
};


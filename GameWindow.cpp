#include "GameWindow.h"
#include "constants.h"


GameWindow::GameWindow() : timer(0)
{
	board = new GameBoard();
    resize(1920, 1080);
    setWindowState(Qt::WindowFullScreen);

    LCDNum = new QLCDNumber(3);
    LCDNum->setSegmentStyle(QLCDNumber::Filled);

    //Start Button
    startButton = new QPushButton("Start");
    QFont font = startButton->font();
    font.setBold(true); //set style bold if is true
    font.setPixelSize(100); // Sets the font size to pixelSize pixels.
    startButton->setFont(font);

    // Quit Button
    quitButton = new QPushButton("Quit");
    font.setPixelSize(40);
    font.setBold(false);
    quitButton->setFont(font);

    //New Level Button
    newLevelButton = new QPushButton("New Level");
    font.setPixelSize(40);
    newLevelButton->setFont(font);


    //Set Focuses
    board->setFocus();
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton->setFocusPolicy(Qt::NoFocus);
    newLevelButton->setFocusPolicy(Qt::NoFocus);

    // Buttons Connectors
    connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(newLevelButton, SIGNAL(clicked()), this, SLOT(NewLevel()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(GameStart()));

    connect(this, SIGNAL(timeIsUp()), this, SLOT(GameLose()));
    connect(board, SIGNAL(PlayerReachedFinish()), this, SLOT(GameWin()));

    //Win/Lose labels
    loseLable = new QLabel("<p style='color:Red; text-align: center;\
                    font-size: 150pt; font-weight: bold;'>You Lose!</p>");
    winLable = new QLabel("<p style='color:Green; text-align: center;\
                    font-size: 150pt; font-weight: bold;'>You Win!</p>");
    loseLable->hide();
    winLable->hide();

    QGridLayout* layout = new QGridLayout;
    // row, column, rowSpan, columnSpan
    layout->addWidget(board, 0, 0, 8, 4);
    layout->addWidget(loseLable, 0, 0, 8, 4);
    layout->addWidget(winLable, 0, 0, 8, 4);
    layout->addWidget(LCDNum, 0, 5);
    layout->addWidget(startButton, 1, 5);
    
    layout->addWidget(newLevelButton, 2, 5);
    layout->addWidget(quitButton, 3, 5);

    setLayout(layout);


}
void GameWindow::NewLevel()
{
    if (timer != 0 && timer->isActive()) // Если игра была в процессе, то необходимо ee прервать
    {
        GameOver();
    }

    LCDNum->display(0);
    loseLable->hide(); 
    winLable->hide();

    board->GenerateNewMazeLevel();
}
void GameWindow::GameLose()
{
    GameOver();
    loseLable->show();
}
void GameWindow::GameWin()
{
    GameOver();
    winLable->show();
}

void GameWindow::GameOver()
{
    //Stop and Delete timer
    timer->stop();
    delete timer;
    timer = 0;

    isStarted = false;
    
    // Stop player
    board->setPlayerCanMove(false);
}

void GameWindow::UpdateLcdTimer()
{
    timeLeft--;
    LCDNum->display(timeLeft);
    if (timeLeft == 0)
    {
        emit timeIsUp();
    }
}
void GameWindow::keyPressEvent(QKeyEvent* event)
{
    board->keyPressEvent(event);
}


void GameWindow::GameStart()
{
    if (!isStarted)
    {
        if (loseLable->isHidden() == false)
        {
            loseLable->hide();
            //Generate new level
            board->GenerateNewMazeLevel();
        }
        if (winLable->isHidden() == false)
        {
            winLable->hide();
            board->GenerateNewMazeLevel();
        }
       

        isStarted = true;
        board->setPlayerCanMove(true);
    
        //Start Timer
        timeLeft = ROUND_TIME;
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(UpdateLcdTimer()));
        timer->start(1000);
    }
}

#include "GameBoard.h"

void GameBoard::setPlayerCanMove(const bool& b)
{
	playerCanMove = b;
}

void GameBoard::GenerateAbsoluteRandom()
{
	// Randomize
	srand(time(0));
	m_block = new Block** [MAZE_WIDTH];
	for (int x = 0; x < MAZE_WIDTH; x++)
	{
		m_block[x] = new Block*[MAZE_HEIGHT];
		for (int y = 0; y < MAZE_HEIGHT; y++)
		{
			//начало и конец должны быть без стен
			if ((x == MAZE_WIDTH - 2 && y == 1) || (x == 1 && y == MAZE_HEIGHT - 2))
			{
				m_block[x][y] = new Block(x, y, "white");
			}
			else if (x == 0 || y == 0 || x == MAZE_WIDTH - 1 || y == MAZE_HEIGHT - 1)
			{//стены ограничивающие лабиринт
				m_block[x][y] = new Block(x, y, "black");
			}
			else
			{
				if (rand() % 4 == 0)
				{
					m_block[x][y] = new Block(x, y, "black");
				}
				else
				{
					m_block[x][y] = new Block(x, y, "white");
				}
			}
		}
	}
}

void GameBoard::GenerateGreatMaze()
{
	srand(time(0));

	//BlockForGeneration
	struct G_Block
	{
		int m_x, m_y;//координаты
		bool m_isWall; // true = стена, false = пустота
		bool m_isVisited; // относится только к пустотам: true = посещенная, false = нет. Все стены = всегда true 
		void Set(const int& x, const int& y, const bool& isWall, const bool& isVisited)
		{
			m_x = x;
			m_y = y;
			m_isWall = isWall;
			m_isVisited = isVisited;
		}
	};
	QStack<G_Block*> NotVisited;
	
	G_Block G_block[MAZE_WIDTH][MAZE_HEIGHT];
	for (int x = 0; x < MAZE_WIDTH; x++)
	{
		for (int y = 0; y < MAZE_HEIGHT; y++)
		{
			//Start generation position
			if (x % 2 == 1 && y % 2 == 1)
			{
				G_block[x][y].Set(x, y, false, false);

				//Записываем непосещенные клетки
				NotVisited.push(&G_block[x][y]);
			}
			else
			{
				G_block[x][y].Set(x, y, true, true);
			}
		}
	}
	//Сделайте начальную клетку текущей и отметьте ее как посещенную.
	G_Block* curBlock = NotVisited.pop();
	curBlock->m_isVisited = true;


	G_Block* neighbors[4];
	int neighborsCount = 0;

	//Пока есть непосещенные клетки
	while (!NotVisited.isEmpty())
	{
		neighborsCount = 0;

		//Поиск непосещенных «соседей»
		if (curBlock->m_x - 2 > 0) // ЛЕВАЯ клетка
		{
			if (G_block[curBlock->m_x - 2][curBlock->m_y].m_isVisited == false) // клетка непосещенная
			{
				neighbors[neighborsCount] = &G_block[curBlock->m_x - 2][curBlock->m_y];
				neighborsCount++;
			}
		}
		if (curBlock->m_x + 2 < MAZE_WIDTH) // ПРАВАЯ клетка
		{
			if (G_block[curBlock->m_x + 2][curBlock->m_y].m_isVisited == false) // клетка непосещенная
			{
				neighbors[neighborsCount] = &G_block[curBlock->m_x + 2][curBlock->m_y];
				neighborsCount++;
			}
		}
		if (curBlock->m_y - 2 > 0) // ВЕРХНЯЯ клетка 
		{
			if (G_block[curBlock->m_x][curBlock->m_y - 2].m_isVisited == false) // клетка непосещенная
			{
				neighbors[neighborsCount] = &G_block[curBlock->m_x][curBlock->m_y - 2];
				neighborsCount++;
			}
		}
		if (curBlock->m_y + 2 < MAZE_HEIGHT) // НИЖНЯЯ клетка 
		{
			if (G_block[curBlock->m_x][curBlock->m_y + 2].m_isVisited == false) // клетка непосещенная
			{
				neighbors[neighborsCount] = &G_block[curBlock->m_x][curBlock->m_y + 2];
				neighborsCount++;
			}
		}

		if (neighborsCount > 0) ////Если текущая клетка имеет непосещенных «соседей»
		{
			
			//Протолкните текущую клетку в стек
			NotVisited.push(curBlock);

			//Выберите случайную клетку из соседних
			// и уберите стенку между текущей клеткой и выбранной
			G_Block* neighbor = neighbors[rand() % neighborsCount];//случайная клетка из соседних
			if (neighbor->m_x > curBlock->m_x) // ПРАВЫЙ сосед
			{
				G_block[curBlock->m_x + 1][curBlock->m_y].m_isWall = false;
			}
			else if (neighbor->m_x < curBlock->m_x) // ЛЕВЫЙ сосед
			{
				G_block[curBlock->m_x - 1][curBlock->m_y].m_isWall = false;
			}
			else
			{
				if (neighbor->m_y > curBlock->m_y) // НИЖНИЙ сосед
				{
					G_block[curBlock->m_x][curBlock->m_y + 1].m_isWall = false;
				}
				else // ВЕРХНИЙ СОСЕД
				{
					G_block[curBlock->m_x][curBlock->m_y - 1].m_isWall = false;
				}
			}
			//Сделайте выбранную клетку текущей и отметьте ее как посещенную.
			curBlock = neighbor;
			curBlock->m_isVisited = true;
		}
		else // если непосещенных соседей нет
		{
			//Выдерните клетку из стека и Сделайте ее текущей
			curBlock = NotVisited.pop();
			curBlock->m_isVisited = true;
		}
	}



	//Копируем данные из G_block в m_block
	
	m_block = new Block** [MAZE_WIDTH];
	for (int x = 0; x < MAZE_WIDTH; x++)
	{
		m_block[x] = new Block * [MAZE_HEIGHT];
		for (int y = 0; y < MAZE_HEIGHT; y++)
		{
			if (G_block[x][y].m_isWall == true)
			{
				m_block[x][y] = new Block(x, y, "black");
			}
			else
			{
				m_block[x][y] = new Block(x, y, "white");
			}
		}
	}
}



GameBoard::~GameBoard()
{
	for (int x = 0; x < MAZE_WIDTH; x++)
	{
		for (int y = 0; y < MAZE_HEIGHT; y++)
		{
			delete m_block[x][y];
		}
	}
	for (int x = 0; x < MAZE_WIDTH; x++)
	{
		delete m_block[x];
	}
	delete m_block;
}

GameBoard::GameBoard() : m_player(0), m_finish(0), playerCanMove(false)
{
	GenerateNewMazeLevel();
}

void GameBoard::drawSquare(QPainter* p, Block* block)
{
	QRect rect(block->GetX() * LENGTH_OF_SQUARE, block->GetY() * LENGTH_OF_SQUARE, LENGTH_OF_SQUARE, LENGTH_OF_SQUARE);
	p->drawRect(rect);
	p->fillRect(rect, block->GetColor());
}

void GameBoard::GenerateNewMazeLevel()
{
	//Create Player
	delete m_player;
	m_player = new Player;

	//Create Finish Block
	delete m_finish;
	m_finish = new Block(MAZE_WIDTH - 2, 1, "Blue");

	//Generate Level
	GenerateGreatMaze();
	//GenerateAbsoluteRandom();

	update();
}


void GameBoard::paintEvent(QPaintEvent* event)
{
	QPainter *p = new QPainter(this);
	
	QPen* pen = new QPen;
	pen->setWidth(3);
	p->setPen(*pen);

	//Draw Blocks
	for (int x = 0; x < MAZE_WIDTH; x++)
	{
		for (int y = 0; y < MAZE_HEIGHT; y++)
		{
			drawSquare(p, m_block[x][y]);
		}
	}

	//Draw Player
	drawSquare(p, m_player);
	

	//Draw Finish
	drawSquare(p, m_finish);
}



void GameBoard::keyPressEvent(QKeyEvent* event)
{
	if (playerCanMove)
	{
		switch (event->key())
		{
		case Qt::Key_Left:
		case Qt::Key_A:
			for (int i = 0; i < PLAYER_SPEED; i++)
				m_player->tryMove(m_player->GetX() - 1, m_player->GetY(), m_block);
			break;
		case Qt::Key_Right:
		case Qt::Key_D:
			for (int i = 0; i < PLAYER_SPEED; i++)
				m_player->tryMove(m_player->GetX() + 1, m_player->GetY(), m_block);
			break;
		case Qt::Key_Down:
		case Qt::Key_S:
			for (int i = 0; i < PLAYER_SPEED; i++)
				m_player->tryMove(m_player->GetX(), m_player->GetY() + 1, m_block);
			break;
		case Qt::Key_Up:
		case Qt::Key_W:
			for (int i = 0; i < PLAYER_SPEED; i++)
				m_player->tryMove(m_player->GetX(), m_player->GetY() - 1, m_block);
			break;
		}
		
		// Проверка, достиг ли финиша
		if (m_player->GetX() == MAZE_WIDTH - 2 && m_player->GetY() == 1)
		{
			emit PlayerReachedFinish();
		}
		update();
	}
}

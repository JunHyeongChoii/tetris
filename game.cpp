#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "game.h"
#include "console/console.h"
#include "tetromino.h"


#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define LINES 40

#define DROP_DELAY 60


#define SHADOW_STRING "⛶"
#define BLOCK_STRING "■"

Game::Game()
{
  initBorad_();

}

// 게임의 한 프레임을 처리한다.

void Game::update()
{
  moveTime--;
  if(moveTime == 0)
  {
      moveTime = DROP_DELAY;
  }

  


}

  // 게임 화면을 그린다.
void Game::draw()
{
  drawWall();

  if(haveDeleteLine == 0)
  {
    console::draw(2,BOARD_HEIGHT/2,"You Win");
    
  }
   if(console::key(console::K_ESC))
  {
    console::draw(2,BOARD_HEIGHT/2, "Lose");
  }
}

  // 게임 루프가 종료되어야 하는지 여부를 반환한다.
bool Game::shouldExit()
{
  std::string Lose = "You Lose";
  if(console::key(console::K_ESC))
  {
    console::draw(2,BOARD_HEIGHT/2, Lose);

    return 1;
  }

  return 0;
}

// drawing main game fram, next tetromino fram, holdtetromino fram
void Game::drawWall()
{
  console::drawBox(0,0, BOARD_WIDTH+1, BOARD_HEIGHT+1);

  std::string leftLine = " lines left";

   // main game frame
  leftLine = std::to_string(haveDeleteLine) + leftLine;
  // Next frame
  std::string next = "Next";
  console::drawBox(BOARD_WIDTH + 2 +1, 0, BOARD_WIDTH + 2 +5 +1 , BOARD_HEIGHT/4);
  console::draw(BOARD_WIDTH + 2 + 1 +1, 0, next);

  // Hold frame
  std::string hold = "Hold";
  console::drawBox(BOARD_WIDTH + 2 +6 +1, 0, BOARD_WIDTH + 2 +5 + 6 +1, BOARD_HEIGHT/4);
  console::draw(BOARD_WIDTH + 2 +5 + 2 +1, 0, hold);

    // 남은 없애야 할 줄 개수
  console::draw(0 , BOARD_HEIGHT + 1+1, leftLine);
}

//bord_[][] 않을 모두 0으로 초기화 한다.
void Game::initBorad_()
{
  for(int i = 0 ;i<BOARD_WIDTH; i++)
    {
      for(int j = 0; j<BOARD_HEIGHT; j++)
      {
        board_[i][j] = 0;
      }
    }
}


void Game::initNow()
{//I, O, T, S, Z, J, L;

  sdt::srand(std::time(nullptr));

  

  std::string <Tetromino> tetrominoForRand;

  tetrominoForRand.push_back(Tetromino::I);
  tetrominoForRand.push_back(Tetromino::O);
  tetrominoForRand.push_back(Tetromino::T);
  tetrominoForRand.push_back(Tetromino::S);
  tetrominoForRand.push_back(Tetromino::Z);
  tetrominoForRand.push_back(Tetromino::J);
  tetrominoForRand.push_back(Tetromino::L);

  int randNumber = std::(rand() % tetrominoForRand.size());

  now = &tetrominoForRand[randNumber];

}

void Game::initHold()
{

}


void Game::initNext()
{
  
}
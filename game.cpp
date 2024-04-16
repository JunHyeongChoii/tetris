#include <iostream>
#include <string>

#include "game.h"
#include "console/console.h"
#include "tetromino.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define LINES 40

#define DROP_DELAY 60




Game::Game()
{
  // memset(board_, 0, sizeof(board));
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
}

  // 게임 루프가 종료되어야 하는지 여부를 반환한다.
bool Game::shouldExit()
{
  if(haveDeleteLine == 0)
  {
    return 0;
  }
    // else if()
    // {

    // }
    
  return 1;
}

// drawing main game fram, next tetromino fram, holdtetromino fram
void Game::drawWall()
{
  console::drawBox(0,0, BOARD_WIDTH, BOARD_HEIGHT);

  std::string leftLine = " lines left";

   // main game frame
  leftLine = std::to_string(haveDeleteLine) + leftLine;
  // Next frame
  std::string next = "Next";
  console::drawBox(BOARD_WIDTH + 2, 0, BOARD_WIDTH + 2 +5 , BOARD_HEIGHT/4);
  console::draw(BOARD_WIDTH + 2 + 1, 0, next);

  // Hold frame
  std::string hold = "Hold";
  console::drawBox(BOARD_WIDTH + 2 +6, 0, BOARD_WIDTH + 2 +5 + 6 , BOARD_HEIGHT/4);
  console::draw(BOARD_WIDTH + 2 +5 + 2, 0, hold);

    // 남은 없애야 할 줄 개수
  console::draw(0 , BOARD_HEIGHT + 1, leftLine);
}





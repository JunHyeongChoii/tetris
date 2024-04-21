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
  initBoard_();
  initXXYY();
  initNow();
  initNext();
  
  // now->p();
  
}

// 게임의 한 프레임을 처리한다.

void Game::update()
{
  moveTime--;
  if(moveTime == 0) // 60프레임에 맞춰서 떨어진다.
  {
      moveTime = DROP_DELAY;
      if(checkYYsizeMax <BOARD_HEIGHT)
        yy++;
  }
  else if(console::key(console::K_DOWN) && checkYYsizeMax <BOARD_HEIGHT)
  {
    yy++;
    moveTime = DROP_DELAY;
  }

  // checkYYsizeMax = 1;
  xxMinMax();
  
  if(console::key(console::K_SPACE) && checkHoldKey == 0) // HOLD 그냥 처음할때
  {
    // moveTime = DROP_DELAY;
    checkHoldKey = 2;
    initHold();
  
    now = next->original();
    initNext();
    initXXYY();
    checkYYsizeMax = 1;
  }
  // hold 한번 누르면 무조건 써야한다. (hold 연속으로 눌리지 않는다.)
  else if(console::key(console::K_SPACE) && checkHoldKey == 1) 
  {
    // moveTime = DROP_DELAY;
    checkHoldKey = 2;
    changeNowHold();
    initXXYY();
    checkYYsizeMax = 1;
   
  }

  if(console::key(console::K_LEFT) && checkXXsizeMin > 1)// xx ■(==1) 제일 작은값이 0이 아닐때
  {  
    xx--;
  }

  if(console::key(console::K_RIGHT) && checkXXsizeMax <BOARD_WIDTH) // xx ■(==1) 제일 큰값이 BOARD_WIDTH +1 아닐때
  {
    xx++;
  }
  checkXXsizeMin = BOARD_WIDTH/2;
  checkXXsizeMax = BOARD_WIDTH/2;

  // if(console::key(console::K_UP))
  // {
  //   for(int i = BOARD_HEIGHT-1; i >= 0; i--)
  //   {
  //     for(int jj = 0; jj< 25; jj ++)
  //     {
  //       std::cout <<" ";
  //     }
  //     for(int j = 0; j < BOARD_WIDTH; j++)
  //     { 
  //       //board_[j][i] =1; //확인용

  //       std::cout << board_[j][i] << " ";
  //     }
  //     std::cout << std::endl;
  //   }
  // }



  if(console::key(console::K_X)) // 시계 방향으로 회전
  {
    *now = now->rotatedCW();
  }

  else if(console::key(console::K_Z)) // 반시계 반향으로 회전
  {
    *now = now->rotatedCCW();
  }


  // board_ 한 줄 다 채워졌을 때
  int fullLine = 0;

  for(int i = BOARD_HEIGHT-1; i >= 0; i--)
  {
    for(int j = 0; j < BOARD_WIDTH; j++)
    {
      if(board_[j][i] == 1)
      {
        fullLine++;
      }
    }
    if(fullLine == 10)
    {
      haveDeleteLine --;
      fullLine = 0;

      int ii = i; // 없어진줄 확인하고 저장하고 한칸씩 땡기고 맨 윗줄은 0으로 채워준다.
      if(ii != 0)
      {
        for(ii; ii>= 0; ii--)
        {
          for(int jj = 0; jj< BOARD_WIDTH; jj++)
          {
            if(ii != 0)
            {
              board_[jj][ii] =board_[jj][ii-1];
            }
            else
            {
              board_[jj][ii] = 0;
            }
          }
        }
      }
      else
      {
        for(int jj = 0; jj< BOARD_WIDTH; jj++)
        {
          board_[ii][jj] = 0;
        }
      }
    }
    fullLine = 0;
  }

}

  // 게임 화면을 그린다.
void Game::draw()
{
  drawWall();
  drawNowT();
  drawBoard();
  if(haveDeleteLine == 0)
  {
    console::draw(2,BOARD_HEIGHT/2,"You Win");
    
  }
   if(console::key(console::K_ESC))
  {
    console::draw(2,BOARD_HEIGHT/2, "Lose");
  }

  drawNext();

  if(checkHoldKey > 0 )
  {
    drawHold();
  }

  int size = now->size();
  for(int i = 0; i<size; i++)
  {
    for(int j = 0; j<size; j++)
    {
      if(now->check(i,j) == 1)
      {
        if(board_[j+(BOARD_WIDTH/2 -1)][i+1] == 1)
        {
          console::draw(2,BOARD_HEIGHT/2, "You Lose");
          
          lose = 1;
        }
      }
    }

  }
  


}

  // 게임 루프가 종료되어야 하는지 여부를 반환한다.
bool Game::shouldExit()
{
 
  if(console::key(console::K_ESC))
  {
    return 1;
  }
  if(haveDeleteLine == 0)
  {
    return 1;
  }
  if(lose == 1)
  {
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

//bord_[][] 내부를 모두 0으로 초기화 한다.
void Game::initBoard_()
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


  std::vector <Tetromino> tetrominoForRand;

  tetrominoForRand.push_back(Tetromino::I);
  tetrominoForRand.push_back(Tetromino::O);
  tetrominoForRand.push_back(Tetromino::T);
  tetrominoForRand.push_back(Tetromino::S);
  tetrominoForRand.push_back(Tetromino::Z);
  tetrominoForRand.push_back(Tetromino::J);
  tetrominoForRand.push_back(Tetromino::L);

  int randNumber = std::rand() % tetrominoForRand.size();

  now = &tetrominoForRand[randNumber];

}

void Game::initHold()
{
  hold = now->original();
}


void Game::initNext()
{
  // std::srand(std::time(nullptr));

  std::vector <Tetromino> tetrominoForRand;

  tetrominoForRand.push_back(Tetromino::I);
  tetrominoForRand.push_back(Tetromino::O);
  tetrominoForRand.push_back(Tetromino::T);
  tetrominoForRand.push_back(Tetromino::S);
  tetrominoForRand.push_back(Tetromino::Z);
  tetrominoForRand.push_back(Tetromino::J);
  tetrominoForRand.push_back(Tetromino::L);

  int randNumber = std::rand() % tetrominoForRand.size();

  next = &tetrominoForRand[randNumber];
}

void Game::initXXYY()
{
  xx = BOARD_WIDTH/2 -1;  // 커질수록 오른쪽 작아질수록 왼쪽
  yy = 1; // 커질수록 밑으로 내려간다.
  // checkYYsizeMax = 1;
}

void Game::changeNowHold()
{
  keepOrigianl();
  now = hold -> original();
  hold = temp->original();
}

void Game::drawHold()
{
    int size = hold->size();
    for(int i = 1; i<  size +1; i++)
    {
      for(int j = 1; j <size+1; j++ )
      {
        if(hold->check(i-1,j-1) == 1)
        {
          hold->drawAt(BLOCK_STRING,(j + BOARD_WIDTH +9),i+1);
        }
        
      }
    }
}

void Game::drawNext()
{
    int size = next->size();
    for(int i = 1; i<  size +1; i++)
    {
      for(int j = 1; j <size+1; j++ )
      {
        if(next->check(i-1,j-1) == 1)
        {
          next->drawAt(BLOCK_STRING,(j + BOARD_WIDTH + 3),i+1);
        }
      }
    }


}

void Game::drawBoard()
{
  for(int i = BOARD_HEIGHT-1; i >= 0; i--)
  {
    for(int j = 0; j < BOARD_WIDTH; j++)
    { 
      //board_[j][i] =1; //확인용
      if(board_[j][i] == 1)
        console::draw(j+1, i+1, BLOCK_STRING );
    }
  }



}

void Game::drawNowT()
{
  int size = now->size();

  for(int i = 0; i<size; i++)
  {
    for(int j = 0; j< size; j++)
    {
      if(now->check(i,j) == 1)
      {
        now->drawAt(BLOCK_STRING, (j + xx), i + yy);
      }
    }
  }
}

void Game::keepOrigianl()
{
  temp = now->original();
}

void Game::xxMinMax()
{
  int size = now->size();
  bool checkOne = 0;
  int iii = BOARD_HEIGHT;
  for(int i = 0; i<size; i++)
  {
    int holdiii = BOARD_HEIGHT;
    for(int j = 0; j< size; j++)
    {
      if(now->check(i,j) == 1)
      {
        if(checkXXsizeMin > (j + xx))
        {
          checkXXsizeMin = j + xx;
        }
        if(checkXXsizeMax < (j+xx))
        {
          checkXXsizeMax = j+ xx;
        }
        if(checkYYsizeMax < i+ yy )
        {
          checkYYsizeMax = i + yy;

        }

        if (board_[j+xx-1][i+yy-1] == 1)
        {
          checkYYsizeMax =BOARD_HEIGHT -1;

           holdiii = i+ yy -1;
           checkOne = 1;
          
        }
      }
    }
    if ( iii > holdiii)
    {
      iii = holdiii;
    }
  }
  if(checkYYsizeMax == BOARD_HEIGHT -1 )
  {
    for(int i = 0; i< size; i++)
    {
      for(int j = 0; j<size; j++)
      {
        if(now->check(i,j) == 1)
        {
          if(checkYYsizeMax == BOARD_HEIGHT-1 )
          { 
            if(checkOne == 1)
            {
              //int ii = iii - i  ;
              
              // if(i+yy == BOARD_HEIGHT -1)
              // {
              //   fillBoard(j+ xx, i+yy-1);
              // }
              // else
              // {
                fillBoard(j+ xx, i+yy-2);
              // }
            }

            else
            {
              fillBoard(j+xx, i + yy);
            }
            
          }
        }
      }
    }
    checkOne = 0;
    moveTime = DROP_DELAY;
    checkYYsizeMax = 1;
    now = next->original();
    initNext();
    initXXYY();
    if (checkHoldKey ==2 )
      checkHoldKey = 1;

  }
}


void Game::fillBoard(int x, int y)
{
  board_[x-1][y] = 1;
}

#ifndef GAME_H
#define GAME_H

#include "tetromino.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define LINES 40

#define DROP_DELAY 60

class Tetromino;

class Game {
private:
  // 게임 판을 나타내는 배열
  // board[x][y]가 true 인 경우 x, y 위치에 고정된 블록이 존재하는 것을 의미한다
  bool board_[BOARD_WIDTH][BOARD_HEIGHT];

  int moveTime = DROP_DELAY;
  int haveDeleteLine = LINES;

  Tetromino* now;
  Tetromino* next;
  Tetromino* hold;
  Tetromino *temp;

  void drawWall();
  void drawBoard();
  void drawHold();
  void drawNext();
  void drawNowT();

  void initBoard_();
  void initNow();
  void initHold();  // 현재 테트로미노 hold
  void initNext(); // next tetromino 생성
  void initXXYY();
  void changeNowHold();

  void keepOrigianl();
  void xxMinMax();
  
  void fillBoard(int x, int y);

  int checkXXsizeMin = BOARD_WIDTH/2;
  int checkXXsizeMax = BOARD_WIDTH/2;

  int checkYYsizeMax = 1;

  int checkHoldKey = 0; // hold가 눌렸는지 확인한다. 눌리지 않았으면 출력하지 않는다.

  int xx = BOARD_WIDTH/2 -1;  // 커질수록 오른쪽 작아질수록 왼쪽     0< j+xx < 
  int yy = 1; // 커질수록 밑으로 내려간다.

  bool lose = 0;
public:
  // 게임의 한 프레임을 처리한다.
  void update();

  // 게임 화면을 그린다.
  void draw();

  // 게임 루프가 종료되어야 하는지 여부를 반환한다.
  bool shouldExit();



  Game();
};
#endif
#include "tetromino.h"
#include "console/console.h"
// 사이즈와 shape 문자열을 통해 생성한다.
  // 문자열은 size * size 길이의 문자열이 주어진다.

  // 블록이 존재한다면 O를 통해 표시하고 아니라면 X를 통해 표시한다.
  // 문자열은 개행 없이 일렬로 나열되어 주어진다.
  // 예를 들어 T 미노의 모양과 생성은 다음과 같다.
  // XOX
  // OOO
  // XXX
  //
  // Tetromino T("T", 3, "XOXOOOXXX")

  // I 미노의 경우 다음과 같다.
  // XXXX
  // OOOO
  // XXXX
  // XXXX
  //
  // Tetromino I("I", 4, "XXXXOOOOXXXXXXXX")
Tetromino::Tetromino(std::string name, int size, std::string shape)
  : name_(name), size_(size)
{
  int a = 0;
  for(int i = 0; i< size; i++)
  {
    for(int j = 0; j< size; j++)
    {
      
      if('O' == shape[a])
        shape_[i][j] = 1;

      else
        shape_[i][j] = 0;
        
      a++;
    }
  }
  
  original_ = this;

}

// 시계 방향으로 회전한 모습의 테트로미노 객체를 반환한다.
Tetromino Tetromino::rotatedCW()
{
  Tetromino rotated = *this;

  bool temp[MAX_SIZE][MAX_SIZE];

  for(int i = 0; i<MAX_SIZE; i++)
  {
    for(int j = 0; j<MAX_SIZE; j++)
    {
      if(i >=0 && i<size_ &&  j >=0 && j<size_ )
        temp[j][size_ -1 -i] = shape_[i][j];
      else
        temp[i][j] = 0;
    }
  }

  for(int i = 0; i< MAX_SIZE; i++)
  {
    for(int j = 0; j< MAX_SIZE; j++)
    {
      rotated.shape_[i][j] = temp[i][j];
    }
  }

  return rotated; 
}

  // 반시계 방향으로 회전한 모습의 테트로미노 객체를 반환한다.
Tetromino Tetromino::rotatedCCW()
{
  Tetromino rotated = *this;

  bool temp[MAX_SIZE][MAX_SIZE]; 
  

  for(int i = 0; i<MAX_SIZE; i++)
  {
    for(int j = 0; j<MAX_SIZE; j++)
    {
      if(i >=0 && i<size_ &&  j >=0 && j<size_ )
        temp[size_ -1 -j][i] = shape_[i][j];
      else
        temp[i][j] = 0;
    }
  }

  for(int i = 0; i<size_; i++)
  {
    for(int j = 0; j<size_; j++)
    {
      rotated.shape_[i][j] = temp[i][j];
    }
  }
  return rotated;
}

  // 화면의 x, y 위치에 s 문자열로  테트로미노를 그린다
void Tetromino::drawAt(std::string s, int x, int y)
{
  
  console::draw(x,y,s);
  
}

// 각 테트로미노 종류에 대한 선언
// cpp 파일에서 Tetromino Tetromino::I(...); 와 같이 구현한다

Tetromino Tetromino::I("I", 4, "XXXXOOOOXXXXXXXX");
Tetromino Tetromino::O("O", 2, "OOOO");
Tetromino Tetromino::T("T", 3, "XOXOOOXXX");
Tetromino Tetromino::S("S", 3, "XOOOOXXXX");
Tetromino Tetromino::Z("Z", 3, "OOXXOOXXX");
Tetromino Tetromino::J("J", 3, "OXXOOOXXX");
Tetromino Tetromino::L("L", 3, "XXOOOOXXX");




 
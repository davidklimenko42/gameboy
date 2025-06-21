#include "mainRacing.h"
#include "mainSnake.h"
#include "mainTetris.h"
#include <GameBoy.h>
GameBoy gb;

byte ARROWS[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {1, 1, 1, 0, 0, 1, 1, 1},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
};
byte CAR[8][8] = {
  {0, 1, 0, 1, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 0, 1, 0},
};
byte SNAKE[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
};
int modeCount;
int mode;
void mainRacing();
int speed = 200;

void setup() {
  gb.begin(13);
  randomSeed(analogRead(A5));
  createBlock(random(0, 7));
}
void loop() {
  // for test
  if (lossTetris() == true) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 16; j++) {
        gb.wipePoint(i, j);
      }
    } 
    Serial.println("You lost the game");
    gb.sound(COLLISION);
    gb.testMatrix(10);
  }
  if(winTetris() == true){
    for(int i = 0;i < 8; i++){
      for(int j = 0;j < 16; j++){
        gb.wipePoint(i, j);
        gb.setLed(i, j, WIN[j][i]);
      }
    }
    delay(2000);
    gb.clearDisplay();
    score = 0;
    level = 0;
  }
  makeMoveTetris();
  if (gb.checkBlockCollision(gb.block[rot], xT, yT + 1)) {
    gb.memBlock(gb.block[rot], xT, yT);
    int lines = gb.fullLine();
    if (lines != 0) {
      score += lines;
      level += lines;
    }
    if (level >= 5) {
      gb.sound(SCORE);
      acc += 1;
      level = 0;
    }
    createBlock(random(0, 7));
  }
  else {
    yT++;
  }
  gb.drawDisplay();
  drawBlock(gb.block[rot], xT, yT);
  delay(speed / acc);
}
//gb.clearDisplay();
//drawBlocks(gb.block(rot), xT, yT);
//yT++;
//delay(100);

//  if (gb.getKey() == 2 && modeSelector() == 0)
//  {
//    gb.clearDisplay();
//    mode = 1;
//  }
//  else if (gb.getKey() == 2 && modeSelector() == 1)
//  {
//    gb.clearDisplay();
//    mode = 2;
//  }
//  else if(gb.getKey() == 1)
//  {
//    gb.clearDisplay();
//    mode = 0;
//  }
//  switchMode(mode);
//mainRaicing();
// mainSnake();
void mainMenu() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      gb.wipePoint(i, j);
      gb.setLed(i, j, ARROWS[j][i]);
    }
  }
  if (modeSelector() == 0)
  {
    for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
      {
        gb.wipePoint(i, 8 + j);
        gb.setLed(i, 8 + j, CAR[j][i]);
      }
    }
  }
  if (modeSelector() == 1)
  {
    for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
      {
        gb.wipePoint(i, 8 + j);
        gb.setLed(i, 8 + j, SNAKE[j][i]);
      }
    }
  }
}
int modeSelector() {
  if (gb.getKey() == 4) {
    modeCount++;
    delay(250);
    if (modeCount > 1)
    {
      modeCount = 0;
    }

  }
  else if (gb.getKey() == 5) {
    modeCount--;
    delay(250);
    if (modeCount < 0)
    {
      modeCount = 1;
    }
  }
  return modeCount;
}
void switchMode(int mode)
{
  switch (mode)
  {
    case 0:
      mainMenu();
      break;
    case 1:
      mainRacing();
      break;
    case 2:
      mainSnake();
      break;
  }
}

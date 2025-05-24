#ifndef MAINRAICING_H
#define MAINRAICING_H
#include <Arduino.h>
#include <GameBoy.h>

GameBoy gb;

int enemy_x = 3;
int enemy_y = 5;
int mycar_x = 2;
int mycar_y = 12;
int car_speed = 100;

void enemyCar(int x, int y);    
void myCar(int x, int y);
void clearMyCar(int x, int y);
void clearEnemyCar(int x, int y);
void createLine(int y);
void clearLine(int y);
bool Collision(int mycar_x, int mycar_y, int enemy_car_x, int enemy_car_y);
void mainRaicing();

void enemyCar(int x, int y) {
  gb.drawPoint(x, y);
  gb.drawPoint(x - 1, y - 1);
  gb.drawPoint(x, y - 1);
  gb.drawPoint(x + 1, y - 1);
  gb.drawPoint(x, y - 2);
  gb.drawPoint(x - 1, y - 3);
  gb.drawPoint(x + 1, y - 3);
}
void myCar(int x, int y) {
  gb.drawPoint(x, y);
  gb.drawPoint(x - 1, y + 1);
  gb.drawPoint(x, y + 1);
  gb.drawPoint(x + 1, y + 1);
  gb.drawPoint(x, y + 2);
  gb.drawPoint(x - 1, y + 3);
  gb.drawPoint(x + 1, y + 3);
}
void clearMyCar(int x, int y) {
  gb.wipePoint(x, y);
  gb.wipePoint(x - 1, y + 1);
  gb.wipePoint(x, y + 1);
  gb.wipePoint(x + 1, y + 1);
  gb.wipePoint(x, y + 2);
  gb.wipePoint(x - 1, y + 3);
  gb.wipePoint(x + 1, y + 3);
}
void clearEnemyCar(int x, int y) {
  gb.wipePoint(x, y);
  gb.wipePoint(x - 1, y - 1);
  gb.wipePoint(x, y - 1);
  gb.wipePoint(x + 1, y - 1);
  gb.wipePoint(x, y - 2);
  gb.wipePoint(x - 1, y - 3);
  gb.wipePoint(x + 1, y - 3);
}
void mainRaicing() {
  enemy_x = random(0, 10);
  if (enemy_x > 5) {
    enemy_x = 2;
  }
  else {
    enemy_x = 5;
  }
  for (int enemy_y = 0; enemy_y < 16; enemy_y++) {
    createLine(enemy_y);
    createLine(enemy_y - 15);
    createLine(enemy_y - 10);
    createLine(enemy_y - 5);
    createLine(enemy_y + 0);
    createLine(enemy_y + 5);
    createLine(enemy_y + 10);
    createLine(enemy_y + 15);
    enemyCar(enemy_x, enemy_y);
    if (gb.getKey() == 4) {
      clearMyCar(5, 12);
      mycar_x = 2;
    }
    else if (gb.getKey() == 5) {
      clearMyCar(2, 12);
      mycar_x = 5;
    }
    myCar(mycar_x, mycar_y);
    if (Collision(mycar_x, mycar_y, enemy_x, enemy_y) == true) {
      gb.sound(COLLISION);
      gb.testMatrix(10);
      gb.clearDisplay();
      return;
    }
    if (enemy_y > 14) {
      gb.sound(SCORE);
    }
    delay(car_speed);
    clearLine(enemy_y);
    clearLine(enemy_y - 15);
    clearLine(enemy_y - 10);
    clearLine(enemy_y - 5);
    clearLine(enemy_y + 0);
    clearLine(enemy_y + 5);
    clearLine(enemy_y + 10);
    clearLine(enemy_y + 15);
    clearEnemyCar(enemy_x, enemy_y);
  }

}
void createLine(int y) {
  gb.drawPoint(0, y);
  gb.drawPoint(0, y + 1);
  gb.drawPoint(0, y + 2);

  gb.drawPoint(7, y);
  gb.drawPoint(7, y + 1);
  gb.drawPoint(7, y + 1);
  gb.drawPoint(7, y + 2);
}
void clearLine(int y) {
  gb.wipePoint(0, y);
  gb.wipePoint(0, y + 1);
  gb.wipePoint(0, y + 2);

  gb.wipePoint(7, y);
  gb.wipePoint(7, y + 1);
  gb.wipePoint(7, y + 1);
  gb.wipePoint(7, y + 2);
}
bool Collision(int mycar_x, int mycar_y, int enemy_car_x, int enemy_car_y) {
  if (mycar_y == enemy_car_y and mycar_x == enemy_car_x) {
    return true;
  }
  if (mycar_x == enemy_car_x and enemy_car_y > 12) {
    return true;
  }
  return false;
}
#endif

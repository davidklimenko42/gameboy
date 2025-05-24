#include <Blocks.h>
#include <GameBoy.h>
GameBoy tatemae;
#define left 4
#define right 5
int enemy_x = 3;
int enemy_y = 5;
int mycar_x = 2;
int mycar_y = 12;
int car_speed = 100;
void setup() {
  Serial.begin(9600);
  tatemae.begin(13);
  randomSeed(analogRead(0));
}
void loop() {
  // myCar(2, 12);
  //  enemyCar(3, 5);
  mainRaicing();
}
void enemyCar(int x, int y) {
  tatemae.drawPoint(x, y);
  tatemae.drawPoint(x - 1, y - 1);
  tatemae.drawPoint(x, y - 1);
  tatemae.drawPoint(x + 1, y - 1);
  tatemae.drawPoint(x, y - 2);
  tatemae.drawPoint(x - 1, y - 3);
  tatemae.drawPoint(x + 1, y - 3);
}
void myCar(int x, int y) {
  tatemae.drawPoint(x, y);
  tatemae.drawPoint(x - 1, y + 1);
  tatemae.drawPoint(x, y + 1);
  tatemae.drawPoint(x + 1, y + 1);
  tatemae.drawPoint(x, y + 2);
  tatemae.drawPoint(x - 1, y + 3);
  tatemae.drawPoint(x + 1, y + 3);
}
void clearMyCar(int x, int y) {
  tatemae.wipePoint(x, y);
  tatemae.wipePoint(x - 1, y + 1);
  tatemae.wipePoint(x, y + 1);
  tatemae.wipePoint(x + 1, y + 1);
  tatemae.wipePoint(x, y + 2);
  tatemae.wipePoint(x - 1, y + 3);
  tatemae.wipePoint(x + 1, y + 3);
}
void clearEnemyCar(int x, int y) {
  tatemae.wipePoint(x, y);
  tatemae.wipePoint(x - 1, y - 1);
  tatemae.wipePoint(x, y - 1);
  tatemae.wipePoint(x + 1, y - 1);
  tatemae.wipePoint(x, y - 2);
  tatemae.wipePoint(x - 1, y - 3);
  tatemae.wipePoint(x + 1, y - 3);
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
    if (tatemae.getKey() == 4) {
      clearMyCar(5, 12);
      mycar_x = 2;
    }
    else if (tatemae.getKey() == 5) {
      clearMyCar(2, 12);
      mycar_x = 5;
    }
    myCar(mycar_x, mycar_y);
    if (Collision(mycar_x, mycar_y, enemy_x, enemy_y) == true) {
      tatemae.sound(COLLISION);
      tatemae.testMatrix(10);
      tatemae.clearDisplay();
      return;
    }
    if (enemy_y > 14) {
      tatemae.sound(SCORE);
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
  tatemae.drawPoint(0, y);
  tatemae.drawPoint(0, y + 1);
  tatemae.drawPoint(0, y + 2);

  tatemae.drawPoint(7, y);
  tatemae.drawPoint(7, y + 1);
  tatemae.drawPoint(7, y + 1);
  tatemae.drawPoint(7, y + 2);
}
void clearLine(int y) {
  tatemae.wipePoint(0, y);
  tatemae.wipePoint(0, y + 1);
  tatemae.wipePoint(0, y + 2);

  tatemae.wipePoint(7, y);
  tatemae.wipePoint(7, y + 1);
  tatemae.wipePoint(7, y + 1);
  tatemae.wipePoint(7, y + 2);
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

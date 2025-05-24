#include <GameBoy.h>
GameBoy gb;
// Пины для кнопок направления
#define forward 3
#define left 4
#define right 5
#define backward 6
// Константы направлений
#define dirUp 0
#define dirRight 1
#define dirLeft 2
#define dirDown 3
int lenSnake = 1; // Длина змейки
int snakeX[10]; // Положение по X
int snakeY[10]; // Положение по Y
int direction = dirRight; // Начальное направление
int FoodX, FoodY; // Координаты еды
int x = 0;
int y = 0;
void randomFood();
void makeMove();
bool collision(int x, int y, int fx, int fy);
bool state;
void drawSnake();
void drawFood();
void move();
boolean isPartOfSnake(int x, int y);
void lose();
void setup() {
    gb.begin(13); // Инициализация дисплея
    snakeX[0] = 4; // Начальная позиция головы
    snakeY[0] = 7;
    randomSeed(analogRead(2)); // Инициализация генератора случайных чисел
    randomFood(); // Создание первой еды
}
void loop() {
   mainSnake;
}
void makeMove() {
    int key = gb.getKey();
    if (key == forward && direction != dirDown) {
        direction = dirUp;
        y = -1;
        x = 0;
     
  } else if (key == left && direction != dirRight) {
        direction = dirLeft;
        x = -1;
        y = 0;
     
  } else if (key == right && direction != dirLeft) {
        direction = dirRight;
        x = 1;
        y = 0;
     
  } else if (key == backward && direction != dirUp) {
        direction = dirDown;
        y = 1;
        x = 0;
     
  }
}
bool collision(int x, int y, int fx, int fy) {
    return (x == fx && y == fy);
}
void drawFood() {
    state = !state;
    if (state == true) {
        gb.drawPoint(FoodX, FoodY);
     
  } else {
        gb.wipePoint(FoodX, FoodY);
     
  }
}
void randomFood() {
    FoodX = random(0, 8); // По ширине (0–7)
    FoodY = random(0, 16); // По высоте (0–15)
    while (isPartOfSnake(FoodX, FoodY)) {
        FoodX = random(0, 8);
        FoodY = random(0, 16);
     
  }
}
void move() {
    // Проверка на столкновение с телом
    for (int i = lenSnake - 1; i > 1; i--) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            gb.sound(COLLISION);
            lose();
            return;
         
    }
     
  }
    // Сдвиг тела змейки
    for (int i = lenSnake - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
     
  }
    // Перемещение головы
    if (direction == dirUp) {
        snakeY[0] = (snakeY[0] == 0) ? 15 : snakeY[0] - 1;
     
  } else if (direction == dirDown) {
        snakeY[0] = (snakeY[0] == 15) ? 0 : snakeY[0] + 1;
     
  } else if (direction == dirLeft) {
        snakeX[0] = (snakeX[0] == 0) ? 7 : snakeX[0] - 1;
     
  } else if (direction == dirRight) {
        snakeX[0] = (snakeX[0] == 7) ? 0 : snakeX[0] + 1;
     
  }
    // Проверка на поедание еды
    if (snakeX[0] == FoodX && snakeY[0] == FoodY) {
        lenSnake++;
        randomFood();
        gb.sound(SCORE);
     
  }
}
void drawSnake() {
    for (int i = 0; i < lenSnake; i++) {
        gb.drawPoint(snakeX[i], snakeY[i]);
     
  }
}
boolean isPartOfSnake(int x, int y) {
    for (int i = 0; i < lenSnake; i++) {
        if (x == snakeX[i] && y == snakeY[i]) {
            return true;
         
    }
     
  }
    return false;
}
void lose() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            gb.drawPoint(i, j);
            delay(50);
         
    }
     
  }
    delay(500);
    gb.clearDisplay();
    for (int i = 0; i < lenSnake; i++) {
        snakeX[i] = 0;
        snakeY[i] = 0;
     
  }
    direction = dirRight;
    FoodX = 3;
    FoodY = 3;
    lenSnake = 1;
    snakeX[0] = 4;
    snakeY[0] = 7;
}
void mainSnake() {
  do{
    randomSeed(analogRead(A2));
    randomFood();
    snakeX[0] = 4;
    snakeY[0] = 7; 
  } while (false);
  makeMove(); // Чтение нажатий кнопок
    move(); // Перемещение змейки
    gb.clearDisplay(); // Очистка экрана
    drawSnake(); // Отрисовка змейки
    drawFood(); // Отрисовка еды
  delay(250);
}

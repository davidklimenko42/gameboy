#include <GameBoy.h>
GameBoy gb;
// Pin definitions for directional buttons
#define forward 3
#define left 4
#define right 5
#define backward 6
// Direction constants
#define dirUp 0
#define dirRight 1
#define dirLeft 2
#define dirDown 3
int lenSnake = 1; // Snake length (initial length)
int snakeX[25]; // Snake's X positions
int snakeY[25]; // Snake's Y positions
int direction = dirRight; // Initial direction of the snake
int FoodX, FoodY; // Food position
// Declare x and y for movement (to control the changes in position)
int x = 0;
int y = 0;
// Declare dirX and dirY to track the snake's head position
int dirX = 0;
int dirY = 0;
void randomFood();
void makeMove();
bool collision(int x, int y, int fx, int fy);
bool state;
void drawSnake();
void drawFood();
void move();
void setup() {
  gb.begin(13); // Initialize GameBoy display
  snakeX[0] = 4; // Initial snake head position
  snakeY[0] = 7;
  randomSeed(analogRead(2)); // Random seed for food generation
  randomFood(); // Generate food on start
}
void loop() {
  makeMove(); // Handle input from the buttons
  move(); // Move snake based on direction
  // Check if snake eats food
  if ((snakeX[0] == FoodX) && (snakeY[0] == FoodY)) {
    lenSnake++;
    randomFood(); // Respawn food
  }
  gb.clearDisplay(); // Clear the screen for the next frame
  drawSnake(); // Draw the snake on the screen
  drawFood(); // Draw the food on the screen
  delay(250); // Frame delay for game speed
}
void makeMove() {
  int key = gb.getKey(); // Get input from the buttons
  // Change direction based on button press, avoiding 180-degree turns
  if (key == forward && direction != dirDown) {
    direction = dirUp;
    y = -1; // Move up
    x = 0;
  } else if (key == left && direction != dirRight) {
    direction = dirLeft;
    x = -1; // Move left
    y = 0;
  } else if (key == right && direction != dirLeft) {
    direction = dirRight;
    x = 1; // Move right
    y = 0;
  } else if (key == backward && direction != dirUp) {
    direction = dirDown;
    y = 1; // Move down
    x = 0;
  }
}
bool collision(int x, int y, int fx, int fy) {
  return (x == fx && y == fy);
}
void drawFood() {
  state = !state;
  if (state == true){
    gb.drawPoint(FoodX, FoodY); // Draw food at the generated position
  }
  else{
    gb.wipePoint(FoodX, FoodY);
  }
} // <--- This closing brace was missing
void randomFood() {
  FoodX = random(0, 8); // Food X position (0-7, as there are 8 columns)
  FoodY = random(0, 16);
  while (isPartOfSnake(FoodX, FoodY)) {
    FoodX = random(0, 8);
    FoodY = random(0, 16);// Food Y position (0-15, as there are 16 rows)
  }
}
void move() {
  // Shift the snake's body to the next position
  for (int i = lenSnake - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }
  // Move the snake's head based on direction
  if (direction == dirUp) {
    snakeY[0] = (snakeY[0] == 0) ? 15 : snakeY[0] - 1;
  } else if (direction == dirDown) {
    snakeY[0] = (snakeY[0] == 15) ? 0 : snakeY[0] + 1;
  } else if (direction == dirLeft) {
    snakeX[0] = (snakeX[0] == 0) ? 7 : snakeX[0] - 1;
  } else if (direction == dirRight) {
    snakeX[0] = (snakeX[0] == 7) ? 0 : snakeX[0] + 1;
  }
}
void drawSnake() {
  for (int i = 0; i < lenSnake; i++) {
    gb.drawPoint(snakeX[i], snakeY[i]); // Draw each segment of the snake
  }
}
boolean isPartOfSnake(int x, int y) {
  for (int i = 0; i < lenSnake - 1; i++) {
    if ((x == snakeX[i]) && (y == snakeY[i])) {
    return true;
  }
}
return false;
}

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
int modeCount()
int gb
void setup(){
  
}
void loop(){
  
}
void mainMenu(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      gb.wipePoint(i, j);
      gb.setLed(i, j, ARROWS[j][i]);
    }
  }
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      gb.wipePoint(i, 8 + j);
      gb.setLed(i, 8 + j, CAR[j][i]);
    }
  }
}
int modeSelector(){
  if(gb.getKey() == 4){
    modeCount++;
    delay(250);
    if(modeCount > 1)
    {
      modeCount = 0;
    }
    
    }
  else if(gb.getKey() == 5){
    modeCount--;
    delay(250);
    if(modeCount < 0)
    {
      modeCount = 1;
    }
}
return modeCount;

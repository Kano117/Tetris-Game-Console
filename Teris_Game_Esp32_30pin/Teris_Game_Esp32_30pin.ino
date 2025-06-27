#include <Wire.h>

#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>
#include <cstdlib>
#include <ctime>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define WIDTH 64 // OLED display width, in pixels

#define HEIGHT 128 // OLED display height, in pixels

Adafruit_SSD1306 display(128, 64, &Wire, -1);


const char pieces_S_l[2][2][4] = { { {0, 0, 1, 1}, {0, 1, 1, 2} },
                                   { {0, 1, 1, 2}, {1, 1, 0, 0} } };

const char pieces_S_r[2][2][4] = { { {1, 1, 0, 0}, {0, 1, 1, 2}},
                                   { {0, 1, 1, 2}, {0, 0, 1, 1} } };

const char pieces_L_l[4][2][4] = { { {0, 0, 0, 1}, {0, 1, 2, 2} },
                                   { {0, 1, 2, 2}, {1, 1, 1, 0} }, 
                                   { {0, 1, 1, 1}, {0, 0, 1, 2} },
                                   { {0, 0, 1, 2}, {1, 0, 0, 0} } };

const char pieces_Sq[1][2][4] = { { {0, 1, 0, 1}, {0, 0, 1, 1} } };

const char pieces_T[4][2][4] =  { { {0, 0, 1, 0}, {0, 1, 1, 2} },
                                  { {0, 1, 1, 2}, {1, 0, 1, 1} },
                                  { {1, 0, 1, 1}, {0, 1, 1, 2} },
                                  { {0, 1, 1, 2}, {0, 0, 1, 0} } };

const char pieces_l[2][2][4] =  { { {0, 1, 2, 3}, {0, 0, 0, 0} },
                                  { {0, 0, 0, 0}, {0, 1, 2, 3} } };

const short MARGIN_TOP = 19;
const short MARGIN_LEFT = 3;
const short SIZE = 5;
const short TYPES = 6;
#define SPEAKER_PIN 19 // Adjust according to your hardware
const int MELODY_LENGTH = 10;
const int MELODY_NOTES[MELODY_LENGTH] = {262, 294, 330, 262};
const int MELODY_DURATIONS[MELODY_LENGTH] = {500, 500, 500, 500};
int click[] = { 1047 };
int click_duration[] = { 100 };
int erase[] = { 2093 };
int erase_duration[] = { 100 };

const unsigned char logo [] PROGMEM = {
	0x00, 0x60, 0x06, 0x00, 0x00, 0x98, 0x19, 0x00, 0x00, 0x8e, 0x71, 0x00, 0x00, 0x87, 0xe1, 0x00, 
	0x00, 0x47, 0xe2, 0x00, 0x00, 0x4f, 0xf2, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x11, 0x88, 0x00, 
	0x00, 0x3b, 0xdc, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0x00, 0x3b, 0xdc, 0x00, 
	0x00, 0x07, 0xe0, 0x00, 0x00, 0x36, 0x6c, 0x00, 0x00, 0x0a, 0x50, 0x00, 0x00, 0x11, 0x88, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xff, 0xe0, 0x0c, 0x1c, 0x3f, 0xf0, 
	0x1d, 0xfb, 0xd9, 0xd8, 0x1d, 0xfb, 0xdc, 0x98, 0x1c, 0x3b, 0xde, 0x38, 0x1d, 0xfb, 0xdc, 0x78, 
	0x1d, 0xfc, 0x39, 0x38, 0x1d, 0xff, 0xfb, 0x98, 0x0d, 0xf0, 0x0f, 0xf0, 0x07, 0xe0, 0x07, 0xe0, 
	0x03, 0xc0, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char car_art [] PROGMEM = {
	0x7e, 0xff, 0xff, 0xc3, 0xbd, 0xbd, 0xbd, 0xff, 0xff, 0xc3
};

const unsigned char mycar [] PROGMEM = {
	0x7e, 0xff, 0xff, 0xc3, 0xbd, 0xa5, 0xa5, 0xe7, 0xff, 0xc3
};

const unsigned char cargame [] PROGMEM = {
	0x00, 0x3f, 0xff, 0xc0, 0x00, 0x3f, 0xff, 0xc0, 0x00, 0xff, 0xff, 0xf0, 0x00, 0xff, 0xff, 0xf0, 
	0x03, 0x00, 0x0c, 0x3c, 0x03, 0x00, 0x0c, 0x3c, 0x0f, 0x00, 0x0c, 0x3c, 0x0f, 0x00, 0x0c, 0x3c, 
	0x3f, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xc3, 0xfc, 0x3f, 0xff, 0xc3, 0xfc, 0x3f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x0f, 0xff, 0xff, 0xfc, 0x0f, 0xff, 0xff, 
	0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x0f, 0xc0, 0x0f, 0xf0, 0x0f, 0xc0, 0x0f, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x38, 0x00, 0x00, 0x94, 0xa4, 0x00, 
	0x00, 0x87, 0xb8, 0x00, 0x00, 0x94, 0xa8, 0x00, 0x00, 0x64, 0xa4, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char musicgame [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x7f, 0xfc, 0x00, 0x00, 0x7f, 0xff, 0xe0, 
	0x00, 0x7f, 0xff, 0xe0, 0x00, 0x43, 0xff, 0xe0, 0x00, 0x40, 0x03, 0xe0, 0x00, 0x78, 0x00, 0x20, 
	0x00, 0x47, 0xf8, 0x40, 0x00, 0x40, 0x07, 0xc0, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 
	0x07, 0xc0, 0x03, 0xe0, 0x1f, 0xf0, 0x0f, 0xf8, 0x3f, 0xf8, 0x1f, 0xfc, 0x3f, 0xf8, 0x1f, 0xfc, 
	0x3f, 0xf8, 0x1f, 0xfc, 0x1f, 0xf0, 0x0f, 0xf8, 0x07, 0xc0, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xa4, 0xee, 0x60, 
	0x0d, 0xa5, 0x04, 0x90, 0x0a, 0xa4, 0xc4, 0x80, 0x08, 0xa4, 0x24, 0x90, 0x08, 0x99, 0xce, 0x60
};

const unsigned char arrowleft [] PROGMEM = {
	0x04, 0x00, 0x0c, 0x00, 0x1c, 0x00, 0x3f, 0xf0, 0x7f, 0xf0, 0xff, 0xf0, 0xff, 0xf0, 0x7f, 0xf0, 
	0x3f, 0xf0, 0x1c, 0x00, 0x0c, 0x00, 0x04, 0x00
};

const unsigned char arrowup [] PROGMEM = {
	0x06, 0x00, 0x0f, 0x00, 0x1f, 0x80, 0x3f, 0xc0, 0x7f, 0xe0, 0xff, 0xf0, 0x1f, 0x80, 0x1f, 0x80, 
	0x1f, 0x80, 0x1f, 0x80, 0x1f, 0x80, 0x1f, 0x80
};

const unsigned char arrowright [] PROGMEM = {
	0x02, 0x00, 0x03, 0x00, 0x03, 0x80, 0xff, 0xc0, 0xff, 0xe0, 0xff, 0xf0, 0xff, 0xf0, 0xff, 0xe0, 
	0xff, 0xc0, 0x03, 0x80, 0x03, 0x00, 0x02, 0x00
};

const unsigned char arrowdown [] PROGMEM = {
	0x1f, 0x80, 0x1f, 0x80, 0x1f, 0x80, 0x1f, 0x80, 0x1f, 0x80, 0x1f, 0x80, 0xff, 0xf0, 0x7f, 0xe0, 
	0x3f, 0xc0, 0x1f, 0x80, 0x0f, 0x00, 0x06, 0x00
};

const unsigned char arrowL [] PROGMEM = {
	0x04, 0x00, 0x0c, 0x00, 0x14, 0x00, 0x27, 0xf0, 0x40, 0x10, 0x80, 0x10, 0x80, 0x10, 0x40, 0x10, 
	0x27, 0xf0, 0x14, 0x00, 0x0c, 0x00, 0x04, 0x00
};

const unsigned char arrowU [] PROGMEM = {
	0x06, 0x00, 0x09, 0x00, 0x10, 0x80, 0x20, 0x40, 0x40, 0x20, 0xf0, 0xf0, 0x10, 0x80, 0x10, 0x80, 
	0x10, 0x80, 0x10, 0x80, 0x10, 0x80, 0x1f, 0x80
};

const unsigned char arrowR [] PROGMEM = {
	0x02, 0x00, 0x03, 0x00, 0x02, 0x80, 0xfe, 0x40, 0x80, 0x20, 0x80, 0x10, 0x80, 0x10, 0x80, 0x20, 
	0xfe, 0x40, 0x02, 0x80, 0x03, 0x00, 0x02, 0x00
};

const unsigned char arrowD [] PROGMEM = {
	0x1f, 0x80, 0x10, 0x80, 0x10, 0x80, 0x10, 0x80, 0x10, 0x80, 0x10, 0x80, 0xf0, 0xf0, 0x40, 0x20, 
	0x20, 0x40, 0x10, 0x80, 0x09, 0x00, 0x06, 0x00
};

word currentType, nextType, rotation;
short pieceX, pieceY;
short piece[2][4];
int interval = 20, score;
int speedgame = 400;
long timer, delayer;

boolean grid[10][18];
boolean b1, b2, b3;

int left = 5; // Adjust according to your hardware
int right = 18; // Adjust according to your hardware
int change = 4; // Adjust according to your hardware
int speed = 2; // Adjust according to your hardware
int start = 15;

int restart = 0;
int highscore1 = 0;
int highscore2 = 0;
int highscore3 = 0;
int combo = 1;
int game = 0;
int mode = 0;
int menu = 1;
int quit = 0;
int play = 0;

const short car_random[7][5] = {{1,0,0,0,0},{0,0,1,0,0},{0,0,0,1,0},{0,0,0,0,1},{0,1,0,0,0},{0,1,0,1,0},{1,0,0,0,1}};
short car[11][5];

int car_move = 2;

short music[9];

short fail = 0;
long speednote;


void drawmusic() {
  for(int i = 8; i >=0 ; i--)
    if (music[i] > 0){
      switch(music[i]) {
        case 1:
          display.drawBitmap(2 + (music[i]-1)*16 , 19 + i*12, arrowleft, 12, 12, WHITE);
          break;
        case 2:
          display.drawBitmap(2 + (music[i]-1)*16 , 19 + i*12, arrowup, 12, 12, WHITE);
          break;
        case 3:
          display.drawBitmap(2 + (music[i]-1)*16 , 19 + i*12, arrowright, 12, 12, WHITE);
          break;
        case 4:
          display.drawBitmap(2 + (music[i]-1)*16 , 19 + i*12, arrowdown, 12, 12, WHITE);
          break;
      }
    }
      
  
}

void drawbasemusic() {
  display.drawBitmap(2 + 0*16 , 19 + 8*12, arrowL, 12, 12, WHITE);
  display.drawBitmap(2 + 1*16 , 19 + 8*12, arrowU, 12, 12, WHITE);
  display.drawBitmap(2 + 2*16 , 19 + 8*12, arrowR, 12, 12, WHITE);
  display.drawBitmap(2 + 3*16 , 19 + 8*12, arrowD, 12, 12, WHITE);
}

void drawmap2() {
  display.drawLine(0, 15, WIDTH, 15, WHITE);
  display.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
  char text[6];
  itoa(score, text, 10);
  drawText(text, getNumberLength(score), 7, 4);
}

void update2() {
  display.clearDisplay();
  drawbasemusic();
  drawmusic();
  drawmap2();
  display.display();
}

void movenote() {
  for(int i = 8; i > 0; i--)
    music[i] = music[i-1];
  music[0] = random(3) + 1;
}

void drawcar() {
  for(int i = 0; i < 11; i++)
    for (int j = 0; j < 5; j++)
      if (car[i][j] == 1)
        display.drawBitmap(4 + j*12, 16 + i*10, car_art, 8, 10, WHITE);
  display.drawBitmap(4 + car_move*12, 16 + 70, mycar,8 , 10, WHITE);
}

void drawmap() {
  display.drawLine(0, 15, WIDTH, 15, WHITE);
  display.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
  for (int i = 0; i < 6; i++)
    display.fillRect(1 + i*12, 15, 2, 112, WHITE);
  char text[6];
  itoa(score, text, 10);
  drawText(text, getNumberLength(score), 7, 4);
}

void update() {
  display.clearDisplay();
  drawcar();
  drawmap();
  display.display();
}

void movecar() {
  for(int i = 10; i > 0; i--)
    for (int j = 4; j >= 0; j--)
      car[i][j] = car[i-1][j];
  int typecar = random(6);
  for (int j = 4; j >= 0; j--)
    car[0][j] = car_random[typecar][j];
}



void checkLines() {
  boolean full;
  for (short y = 17; y >= 0; y--) {
    full = true;
    for (short x = 0; x < 10; x++) {
      full = full && grid[x][y];
    }
    if (full) {
      breakLine(y);
      y++;
      combo++;
    }
  }
  combo = 1;
}

void breakLine(short line) {
  tone(SPEAKER_PIN, erase[0], 1000 / erase_duration[0]);
  delay(100);
  noTone(SPEAKER_PIN);
  for (short y = line; y >= 0; y--) {
    for (short x = 0; x < 10; x++) {
      grid[x][y] = grid[x][y - 1];
    }
  }
  for (short x = 0; x < 10; x++) {
    grid[x][0] = 0;
  }
  display.invertDisplay(true);
  delay(50);
  display.invertDisplay(false);
  score += 10*combo;
}

bool gameover() {
  boolean go;
  int t = 0;
  for (short y = 0; y < 19; y++) {
    go = false;
    for (short x = 0; x < 10; x++) {
      go = go || grid[x][y];
    }
    if (go) {
      t++;
    }
  }
  if (t > 18) return true;
  return false;
}

void gameoverscreen(int quit, int highscore) {
  display.clearDisplay();
  display.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
  drawText("GAMEOVER", 9, 9, 30);
  drawText("Highscore", 10, 5, 40);
  char text1[6];
  itoa(highscore, text1, 10);
  drawText(text1, getNumberLength(highscore), 35 - 5*getNumberLength(highscore), 50);
  drawText("Score", 6, 18, 60);
  char text2[6];
  itoa(score, text2, 10);
  drawText(text2, getNumberLength(score), 35 - 5*getNumberLength(score), 70);
  if (quit == 0) {
    drawText("> Retry <",10, 4, 90);
    drawText("Quit",5, 14, 100);
  } else {
    drawText("Retry",6, 12, 90);
    drawText("> Quit <",9, 6, 100);
  }
  display.display();
}

void gamescreen(int game) {
  drawText("Game", 5, 12, 6);
  display.drawRect(8, 16, 48, 57, WHITE);
  display.fillTriangle(1, 44, 6, 39, 6, 49, WHITE);
  display.fillTriangle(62, 44, 57, 39, 57, 49, WHITE);
  switch(game) {
    case 0:
    {
      for (short i = 0; i < 3; i++)
        display.fillRect(23, 20 + (8+2)*i, 8, 8, WHITE);
      display.fillRect(33, 20 + (8+2)*2, 8, 8, WHITE);
      drawText("Tetris", 7, 12, 62);
    }
    break;
    case 1:
    {
      display.drawBitmap(16, 24, cargame, 32, 32, WHITE);
    }
    break;
    case 2:
    display.drawBitmap(16, 24, musicgame, 32, 32, WHITE);
    break;
  }
}

void modescreen(int mode) {
  drawText("Mode", 5, 12, 80);
  if (mode == 0) 
    drawText("> Easy <", 9, 6, 90);
  else drawText("Easy", 5, 14, 90);
  if (mode == 1)
    drawText("> Normal <", 11, 2, 100);
  else drawText("Normal", 7, 10, 100);
  if (mode == 2)
    drawText("> Hard <", 9, 6, 110);
  else drawText("Hard", 5, 14, 110);
}

void menuscreen(int game, int mode) {
  display.clearDisplay();
  gamescreen(game);
  modescreen(mode);
  display.display();
}

void refresh() {
  display.clearDisplay();
  drawLayout();
  drawGrid();
  drawPiece(currentType, 0, pieceX, pieceY);
  display.display();
}

void drawGrid() {
  for (short x = 0; x < 10; x++)
    for (short y = 0; y < 18; y++)
      if (grid[x][y])
        display.fillRect(MARGIN_LEFT + (SIZE + 1)*x, MARGIN_TOP + (SIZE + 1)*y, SIZE, SIZE, WHITE);
}

boolean nextHorizontalCollision(short piece[2][4], int amount) {
  for (short i = 0; i < 4; i++) {
    short newX = pieceX + piece[0][i] + amount;
    if (newX > 9 || newX < 0 || grid[newX][pieceY + piece[1][i]])
      return true;
  }
  return false;
}
boolean nextCollision() {
  for (short i = 0; i < 4; i++) {
    short y = pieceY + piece[1][i] + 1;
    short x = pieceX + piece[0][i];
    if (y > 17 || grid[x][y])
      return true;
  }
  return false;
}

void generate() {
  currentType = nextType;
  nextType = random(TYPES);
  if (currentType != 5)
    pieceX = 4;
  else
    pieceX = 3;
  pieceY = 0;
  rotation = 0;
  copyPiece(piece, currentType, rotation);
}

void drawPiece(short type, short rotation, short x, short y) {
  for (short i = 0; i < 4; i++)
    display.fillRect(MARGIN_LEFT + (SIZE + 1) * (x + piece[0][i]), MARGIN_TOP + (SIZE + 1) * (y + piece[1][i]), SIZE, SIZE, WHITE);
}

void drawNextPiece() {
  short nPiece[2][4];
  copyPiece(nPiece, nextType, 0);
  for (short i = 0; i < 4; i++)
    display.fillRect(50 + 3 * nPiece[0][i], 4 + 3 * nPiece[1][i], 2, 2, WHITE);
}

void copyPiece(short piece[2][4], short type, short rotation) {
  switch (type) {
    case 0: //L_l
      for (short i = 0; i < 4; i++) {
        piece[0][i] = pieces_L_l[rotation][0][i];
        piece[1][i] = pieces_L_l[rotation][1][i];
      }
      break;
    case 1: //S_l
      for (short i = 0; i < 4; i++) {
        piece[0][i] = pieces_S_l[rotation][0][i];
        piece[1][i] = pieces_S_l[rotation][1][i];
      }
      break;
    case 2: //S_r
      for (short i = 0; i < 4; i++) {
        piece[0][i] = pieces_S_r[rotation][0][i];
        piece[1][i] = pieces_S_r[rotation][1][i];
      }
      break;
    case 3: //Sq
      for (short i = 0; i < 4; i++) {
        piece[0][i] = pieces_Sq[0][0][i];
        piece[1][i] = pieces_Sq[0][1][i];
      }
      break;
    case 4: //T
      for (short i = 0; i < 4; i++) {
        piece[0][i] = pieces_T[rotation][0][i];
        piece[1][i] = pieces_T[rotation][1][i];
      }
      break;
    case 5: //l
      for (short i = 0; i < 4; i++) {
        piece[0][i] = pieces_l[rotation][0][i];
        piece[1][i] = pieces_l[rotation][1][i];
      }
      break;
  }
}

short getMaxRotation(short type) {
  if (type == 1 || type == 2 || type == 5)
    return 2;
  else if (type == 0 || type == 4)
    return 4;
  else if (type == 3)
    return 1;
  else
    return 0;
}

boolean canRotate(short rotation) {
  short piece[2][4];
  copyPiece(piece, currentType, rotation);
  return !nextHorizontalCollision(piece, 0);
}

void drawLayout() {
  display.drawLine(0, 15, WIDTH, 15, WHITE);
  display.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
  drawNextPiece();
  char text[6];
  itoa(score, text, 10);
  drawText(text, getNumberLength(score), 7, 4);
}

short getNumberLength(int n) {

  short counter = 1;

  while (n >= 10) {

    n /= 10;

    counter++;

  }

  return counter;

}

void drawText(char text[], short length, int x, int y) {

  display.setTextSize(1);      // Normal 1:1 pixel scale

  display.setTextColor(WHITE); // Draw white text

  display.setCursor(x, y);     // Start at top-left corner

  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  for (short i = 0; i < length; i++)

    display.write(text[i]);

}
short randomNumber(short n) {
  short temp =0 ;
  temp = rand() % n;
  return temp;
}

void setup() {
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  pinMode(change, INPUT_PULLUP);
  pinMode(speed, INPUT_PULLUP);
  pinMode(start, INPUT_PULLUP);
  pinMode(SPEAKER_PIN, OUTPUT);
  Serial.begin(9600); Serial.println("Tetris startet ... ");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.setRotation(3);
  display.clearDisplay();
  display.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
  display.drawBitmap(16, 48, logo, 32, 32, WHITE);
  display.display();

  delay(2000);
  //display.drawBitmap(3, 23, mantex_logo, 64, 82,  WHITE);
  
}

void loop() {
  if (menu == 1) {
    score = 0;
    menuscreen(game, mode);
    if (!digitalRead(right)) {
      if (game < 2) game++;
      delay(250);
    }
    if (!digitalRead(left)) {
      if (game > 0) game--;
      delay(250);
    }
    if (!digitalRead(change)) {
      if (mode == 0) mode = 2;
      else mode--;
      delay(250);
    }
    if (!digitalRead(speed)) {
      if (mode == 2) mode = 0;
      else mode++;
      delay(250);
    }
    if (!digitalRead(start)) menu = 0;
  }
  if (menu == 0 && game == 0) {
    if (play == 0) {
      display.clearDisplay();
      display.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
      drawText("TETRIS", 7, 12, 40);
      drawText("GAME", 5, 15, 50);
      display.display();

      delay(2000);
      nextType = random(TYPES);
      display.clearDisplay();
      drawLayout();
      display.display();

      generate();
      timer = millis();
      speedgame = 100*(4 - mode);
      play = 1;
    }
    
    if (play == 1 ) {
      if(restart == 1) {
        gameoverscreen(quit, highscore1);
        if (!digitalRead(change)) {
          if (quit == 1) quit = 0;
          else quit = 1;
          delay(250);
    }
    if (!digitalRead(speed)) {
      if (quit == 0) quit = 1;
      else quit = 0;
      delay(250);
    }
      if(!digitalRead(start) && quit == 0){
        restart = 0;
        for (short y = 0; y < 20; y++) {
        for (short x = 0; x < 10; x++) {
        grid[x][y] = false;
      }}
      score = 0;
      display.clearDisplay();
      drawLayout();
      display.display();
      generate();
      timer = millis();
    }
    if(!digitalRead(start) && quit == 1){
    restart = 0;
    for (short y = 0; y < 20; y++) {
    for (short x = 0; x < 10; x++) {
      grid[x][y] = false;
    }}
    score = 0;
    menu = 1;
    play = 0;
    display.clearDisplay();
  display.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
  display.drawBitmap(16, 48, logo, 32, 32, WHITE);
  display.display();

  delay(1000);
  }
      }
      
  if (restart == 0) {
    if (millis() - timer > interval) {
    checkLines();
    refresh();
    if (nextCollision()) {
      for (short i = 0; i < 4; i++)
        grid[pieceX + piece[0][i]][pieceY + piece[1][i]] = 1;
      generate();
    } else
      pieceY++;
    timer = millis();
  }

  if (!digitalRead(left)) {
    tone(SPEAKER_PIN, click[0], 1000 / click_duration[0]);
    delay(100);
    noTone(SPEAKER_PIN);
      if (!nextHorizontalCollision(piece, -1)) {
        pieceX--;
        refresh();
      }
    delay(100);
  } 
  if (!digitalRead(right)) {
    tone(SPEAKER_PIN, click[0], 1000 / click_duration[0]);
    delay(100);
    noTone(SPEAKER_PIN);
      if (!nextHorizontalCollision(piece, 1)) {
        pieceX++;
        refresh();
      }
    delay(100);
  } 

  if (!digitalRead(speed)) {
    interval = 20;
  } else {
    interval = speedgame;
  }

  if (!digitalRead(change)) {
    tone(SPEAKER_PIN, click[0], 1000 / click_duration[0]);
    delay(100);
    noTone(SPEAKER_PIN);
    if (b3) {
      if (rotation == getMaxRotation(currentType) - 1 && canRotate(0)) {
        rotation = 0;
      } else if (canRotate(rotation + 1)) {
        rotation++;
      }
      copyPiece(piece, currentType, rotation);
      refresh();
      b3 = false;
      delayer = millis();
    }
  } else if (millis() - delayer > 50) {
    b3 = true;
  }
  if (gameover()){
    restart = 1;
    if (highscore1 < score) highscore1 = score;
    gameoverscreen(quit, highscore1);
   int melody[] = {
  262, 196,196, 220, 196,0, 247, 262};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

 for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(SPEAKER_PIN, melody[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(SPEAKER_PIN);
    }
  }
  }
    }
  }

  if (menu == 0 && game == 1) {
    if (play == 0) {
      display.clearDisplay();
      display.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
      drawText("CAR", 7, 16, 40);
      drawText("GAME", 5, 15, 50);
      display.display();

      delay(2000);
      display.clearDisplay();
      int typecar = random(6);
        for (int j = 4; j >= 0; j--)
        car[0][j] = car_random[typecar][j];
      drawmap();
      drawcar();
      display.display();

      timer = millis();
      speedgame = 100*(4 - mode);
      play = 1;
    }
    
    if (play == 1 ) {
      if(restart == 1) {
        gameoverscreen(quit, highscore2);
        if (!digitalRead(change)) {
          if (quit == 1) quit = 0;
          else quit = 1;
          delay(250);
    }
    if (!digitalRead(speed)) {
      if (quit == 0) quit = 1;
      else quit = 0;
      delay(250);
    }
      if(!digitalRead(start) && quit == 0){
        restart = 0;
        for(int i = 0; i < 11; i++)
          for (int j = 0; j < 5; j++)
            car[i][j] = 0;
      score = 0;
      display.clearDisplay();
        int typecar = random(6);
        for (int j = 4; j >= 0; j--)
        car[0][j] = car_random[typecar][j];
      drawmap();
      drawcar();
      display.display();
      generate();
      timer = millis();
    }
    if(!digitalRead(start) && quit == 1){
    restart = 0;
    for(int i = 0; i < 11; i++)
          for (int j = 0; j < 5; j++)
            car[i][j] = 0;
    score = 0;
    menu = 1;
    play = 0;
    display.clearDisplay();
  display.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
  display.drawBitmap(16, 48, logo, 32, 32, WHITE);
  display.display();

  delay(1000);
  }
      }
      
  if (restart == 0) {
    if (millis() - timer > speedgame) {
      movecar();
      score += 2;
      update();
    timer = millis();
  }

  if (!digitalRead(left)) {
    if (car_move != 0) car_move--;
    update();
    delay(250);
  } 
  if (!digitalRead(right)) {
    if (car_move != 4) car_move++;
    update();
    delay(250);
  }

  if (car[7][car_move] == 1){
    restart = 1;
    car_move = 2;
    if (highscore2 < score) highscore2 = score;
    gameoverscreen(quit, highscore2);
   int melody[] = {
  262, 196,196, 220, 196,0, 247, 262};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

 for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(SPEAKER_PIN, melody[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(SPEAKER_PIN);
    }
  }
  }
    }
  }

  if (menu == 0 && game == 2) {
    if (play == 0) {
      display.clearDisplay();
      display.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
      drawText("MUSIC", 7, 16, 40);
      drawText("GAME", 5, 15, 50);
      display.display();

      delay(2000);
      display.clearDisplay();
      music[0] = random(3) + 1;
      drawmap2();
      drawbasemusic();
      drawmusic();
      display.display();

      timer = millis();
      speedgame = 150*(4 - mode);
      play = 1;
    }
    
    if (play == 1 ) {
      if(restart == 1) {
        gameoverscreen(quit, highscore3);
        if (!digitalRead(change)) {
          if (quit == 1) quit = 0;
          else quit = 1;
          delay(250);
    }
    if (!digitalRead(speed)) {
      if (quit == 0) quit = 1;
      else quit = 0;
      delay(250);
    }
      if(!digitalRead(start) && quit == 0){
        restart = 0;
        for(int i = 0; i < 9; i++)
          music[i] = 0;
      score = 0;
      display.clearDisplay();
        music[0] = random(3) + 1;
      drawmap2();
      drawmusic();
      display.display();
      generate();
      timer = millis();
    }
    if(!digitalRead(start) && quit == 1){
    restart = 0;
    for(int i = 0; i < 9; i++)
      music[i] = 0;
    score = 0;
    menu = 1;
    play = 0;
    display.clearDisplay();
  display.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
  display.drawBitmap(16, 48, logo, 32, 32, WHITE);
  display.display();

  delay(1000);
  }
      }
      
  if (restart == 0) {
  if (music[8] == 0) {
    if (millis() - timer > speedgame) {
      movenote();
      update2();
    timer = millis();
    }
  }
  if (music[8] > 0) {
    if (music[8] == 1) {
      if (!digitalRead(left) && digitalRead(right) && digitalRead(change) && digitalRead(speed)){
        score += 5;
        speednote = millis();
        delay(speedgame - speednote + timer);
        movenote();
        update2();
        timer = millis();
      } else {
        fail = 1;
      }
    }
    if (music[8] == 2) {
      if (digitalRead(left) && digitalRead(right) && !digitalRead(change) && digitalRead(speed)){
        score += 5;
        speednote = millis();
        delay(speedgame - speednote + timer);
        movenote();
        update2();
        timer = millis();
      } else {
        fail = 1;
      }
    }
    if (music[8] == 3) {
      if (digitalRead(left) && !digitalRead(right) && digitalRead(change) && digitalRead(speed)){
        score += 5;
        speednote = millis();
        delay(speedgame - speednote + timer);
        movenote();
        update2();
        timer = millis();
      } else {
        fail = 1;
      }
    }
    if (music[8] == 4) {
      if (digitalRead(left) && digitalRead(right) && digitalRead(change) && !digitalRead(speed)){
        score += 5;
        speednote = millis();
        delay(speedgame - speednote + timer);
        movenote();
        update2();
        timer = millis();
      } else {
        fail = 1;
      }
    }
    if ((millis() - timer > speedgame) && fail == 1){
      restart = 1;
      fail = 0;
      movenote();
      update2();
      timer = millis();
      if (highscore3 < score) highscore3 = score;
    gameoverscreen(quit, highscore3);
   int melody[] = {
  262, 196,196, 220, 196,0, 247, 262};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

 for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(SPEAKER_PIN, melody[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(SPEAKER_PIN);
    }
    }

  }
  

  
  }
    }
  }
  
}  // loop endet
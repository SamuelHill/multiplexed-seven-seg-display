/* Multiplexed seven segment display general code. 
   Written for 3 seven segment displays. */

// Seven segment display wiring:
// 9=Top left     2=Top
// 8=Middle       3=Top right
// 7=Bottom left  4=DP
// 6=Bottom       5=Bottom right
// The binary number order is reversed... (DP/4 = ...0)
const int segmentNum = 8;
const int segmentPins[segmentNum]= { 4,2,3,5,6,7,8,9 };

// Transistor wiring:
const int controlNum = 3;
const int controlPins[controlNum]= { 12,11,10 };

//bits representing general purpose configurations
const byte blank = B00000000;
const byte decimal = B00000001;

//bits representing numerals 0-9
const byte numerals[10] = {
B10111110, // 0
B00001100, // 1
B01110110, // 2
B01011110, // 3
B11001100, // 4
B11011010, // 5
B11111010, // 6
B00001110, // 7
B11111110, // 8
B11011110 // 9
};

void showDigit(int number, int control, int delayTime) {
  digitalWrite(controlPins[control], HIGH);
  for (int segment = 0; segment < segmentNum; segment++) {
    digitalWrite(segmentPins[segment], bitRead(numerals[number], segment));
  }
  delay(delayTime);
  digitalWrite(controlPins[control], LOW);
}

void showDigitDecimal(int number, int control, int delayTime) {
  digitalWrite(controlPins[control], HIGH);
  byte decimalAdded = numerals[number] + decimal;
  for (int segment = 0; segment < segmentNum; segment++) {
    digitalWrite(segmentPins[segment], bitRead(decimalAdded, segment));
  }
  delay(delayTime);
  digitalWrite(controlPins[control], LOW);
}

void show3Digits_1000(int number) {
  int onesPlace = 0;
  int tensPlace = 0;
  int hundPlace = 0;
  if (number < 1000 && number > -1) {
    onesPlace = number % 10;
    tensPlace = ((number % 100) - onesPlace)/10;
    hundPlace = (number - (10 * tensPlace) - onesPlace)/100;
    for (int k = 0; k < 33; k++) {
      showDigit(hundPlace,0,10);
      showDigit(tensPlace,1,10);
      showDigit(onesPlace,2,10);
    }
  }
  else {
    Serial.print("Number out of range (0 - 999).");
  }
}

void show3Digits_1000(int number, int timer) {
  int onesPlace = 0;
  int tensPlace = 0;
  int hundPlace = 0;
  if (number < 1000 && number > -1) {
    onesPlace = number % 10;
    tensPlace = ((number % 100) - onesPlace)/10;
    hundPlace = (number - (10 * tensPlace) - onesPlace)/100;
    for (int k = 0; k < timer; k++) {
      showDigit(hundPlace,0,10);
      showDigit(tensPlace,1,10);
      showDigit(onesPlace,2,10);
    }
  }
  else {
    Serial.print("Number out of range (0 - 999).");
  }
}

void show3Digits_100(float number) {
  int replace = 0;
  int onesPlace = 0;
  int tensPlace = 0;
  int hundPlace = 0;
  if (number < 100.0 && number > -0.1) {
    replace = static_cast<int>(number * 10);
    onesPlace = replace % 10;
    tensPlace = ((replace % 100) - onesPlace)/10;
    hundPlace = (replace - (10 * tensPlace) - onesPlace)/100;
    for (int k = 0; k < 33; k++) {
      showDigit(hundPlace,0,10);
      showDigitDecimal(tensPlace,1,10);
      showDigit(onesPlace,2,10);
    }
  }
  else {
    Serial.print("Number out of range (0 - 999).");
  }
}

void show3Digits_100(float number, int timer) {
  int replace = 0;
  int onesPlace = 0;
  int tensPlace = 0;
  int hundPlace = 0;
  if (number < 100.0 && number > -0.1) {
    replace = static_cast<int>(number * 10);
    onesPlace = replace % 10;
    tensPlace = ((replace % 100) - onesPlace)/10;
    hundPlace = (replace - (10 * tensPlace) - onesPlace)/100;
    for (int k = 0; k < timer; k++) {
      showDigit(hundPlace,0,10);
      showDigitDecimal(tensPlace,1,10);
      showDigit(onesPlace,2,10);
    }
  }
  else {
    Serial.print("Number out of range (0 - 999).");
  }
}

void show3Digits_10(float number) {
  int replace = 0;
  int onesPlace = 0;
  int tensPlace = 0;
  int hundPlace = 0;
  if (number < 10.00 && number > -0.01) {
    replace = static_cast<int>(number * 100);
    onesPlace = replace % 10;
    tensPlace = ((replace % 100) - onesPlace)/10;
    hundPlace = (replace - (10 * tensPlace) - onesPlace)/100;
    for (int k = 0; k < 33; k++) {
      showDigitDecimal(hundPlace,0,10);
      showDigit(tensPlace,1,10);
      showDigit(onesPlace,2,10);
    }
  }
  else {
    Serial.print("Number out of range (0 - 999).");
  }
}

void show3Digits_10(float number, int timer) {
  int replace = 0;
  int onesPlace = 0;
  int tensPlace = 0;
  int hundPlace = 0;
  if (number < 10.00 && number > -0.01) {
    replace = static_cast<int>(number * 100);
    onesPlace = replace % 10;
    tensPlace = ((replace % 100) - onesPlace)/10;
    hundPlace = (replace - (10 * tensPlace) - onesPlace)/100;
    for (int k = 0; k < timer; k++) {
      showDigitDecimal(hundPlace,0,10);
      showDigit(tensPlace,1,10);
      showDigit(onesPlace,2,10);
    }
  }
  else {
    Serial.print("Number out of range (0 - 999).");
  }
}

//bits representing select letters and a blank
const byte alphas[21] = {
B11101110, // A
B11111000, // b
B10110010, // C
B01111100, // d
B11110010, // E
B11100010, // F
// no g, looks like 6 or 9...
B11101100, // H
B10100000, // I
B00011100, // J
// no K, looks like H...
B10110000, // L
// no M...
B01101000, // n
B01111000, // o
B11100110, // P
B11001110, // q
B01100000, // r
B11011010, // S (same as 5...)
B11110000, // t
B10111100, // U
B00111000, // v
// no W...
// no X, looks like H...
B11011100, // Y
B01110110 // Z (same as 2...)
};

const char alphaMapping[21] = {'a','b','c','d','e','f','h','i','j','l','n','o','p','q','r','s','t','u','v','y','z'};

void showLetter(char alpha, int control, int delayTime) {
  int alphaPosition = -1;
  int curPosition = 0;
  boolean foundLetter = false;
  while (foundLetter == false && curPosition < 21) {
    if (alpha == alphaMapping[curPosition]) {
      alphaPosition = curPosition;
      foundLetter = true;
    }
    curPosition = curPosition + 1;
  }
  if (alphaPosition != -1) {
    digitalWrite(controlPins[control], HIGH);
    for (int segment = 0; segment < segmentNum; segment++) {
      digitalWrite(segmentPins[segment], bitRead(alphas[alphaPosition], segment));
    }
    delay(delayTime);
    digitalWrite(controlPins[control], LOW);
  }
  else {
    Serial.print("Not a valid letter.");
  }
}

//array of arrays of characters containing all 1-3 letter words with the given alphas
//http://www.litscape.com/word_tools/contains_only.php
const char words[][3] = {{' ', ' ', 'a'}, {' ', 'a', 'b'}, {'a', 'b', 's'}, {'a', 'c', 'e'}, {'a', 'c', 't'}, {' ', 'a', 'd'}, {'a', 'd', 'o'}, {'a', 'd', 's'}, {'a', 'd', 'z'}, {'a', 'f', 't'}, {' ', 'a', 'h'}, {' ', 'a', 'i'}, {'a', 'i', 'd'}, {'a', 'i', 'l'}, {'a', 'i', 'r'}, {'a', 'i', 's'}, {'a', 'l', 'b'}, {'a', 'l', 'e'}, {' ', 'a', 'n'}, {'a', 'n', 'd'}, {'a', 'n', 't'}, {'a', 'n', 'y'}, {'a', 'p', 'e'}, {'a', 'p', 't'}, {' ', 'a', 'r'}, {'a', 'r', 'c'}, {'a', 'r', 'e'}, {'a', 'r', 's'}, {'a', 'r', 't'}, {' ', 'a', 's'}, {'a', 's', 'h'}, {'a', 's', 'p'}, {' ', 'a', 't'}, {'a', 't', 'e'}, {' ', 'a', 'y'}, {'a', 'y', 'e'}, {'a', 'y', 's'}, {'b', 'a', 'd'}, {'b', 'a', 'n'}, {'b', 'a', 'r'}, {'b', 'a', 't'}, {'b', 'a', 'y'}, {' ', 'b', 'e'}, {'b', 'e', 'd'}, {'b', 'e', 't'}, {'b', 'i', 'd'}, {'b', 'i', 'n'}, {'b', 'i', 't'}, {'b', 'o', 'a'}, {'b', 'o', 'p'}, {'b', 'o', 'y'}, {'b', 'r', 'a'}, {'b', 'u', 'd'}, {'b', 'u', 'n'}, {'b', 'u', 's'}, {'b', 'u', 't'}, {'b', 'u', 'y'}, {' ', 'b', 'y'}, {'b', 'y', 'e'}, {'c', 'a', 'b'}, {'c', 'a', 'd'}, {'c', 'a', 'n'}, {'c', 'a', 'p'}, {'c', 'a', 'r'}, {'c', 'a', 't'}, {'c', 'a', 'y'}, {'c', 'h', 'i'}, {'c', 'i', 's'}, {'c', 'o', 'b'}, {'c', 'o', 'd'}, {'c', 'o', 'n'}, {'c', 'o', 'p'}, {'c', 'o', 't'}, {'c', 'o', 'y'}, {'c', 'r', 'y'}, {'c', 'u', 'b'}, {'c', 'u', 'd'}, {'c', 'u', 'e'}, {'c', 'u', 'p'}, {'c', 'u', 'r'}, {'c', 'u', 't'}, {'d', 'a', 'b'}, {'d', 'a', 'y'}, {'d', 'e', 'n'}, {'d', 'e', 'y'}, {'d', 'i', 'e'}, {'d', 'i', 'n'}, {'d', 'i', 'p'}, {' ', 'd', 'o'}, {'d', 'o', 'e'}, {'d', 'o', 'n'}, {'d', 'o', 's'}, {'d', 'o', 't'}, {'d', 'r', 'y'}, {'d', 'u', 'b'}, {'d', 'u', 'e'}, {'d', 'u', 'o'}, {'d', 'y', 'e'}, {'e', 'a', 'r'}, {'e', 'a', 't'}, {' ', 'e', 'f'}, {'e', 'f', 's'}, {' ', 'e', 'h'}, {' ', 'e', 'l'}, {'e', 'l', 'f'}, {'e', 'l', 's'}, {' ', 'e', 'n'}, {'e', 'n', 'd'}, {'e', 'n', 's'}, {'e', 'o', 'n'}, {'e', 'r', 'a'}, {'e', 't', 'a'}, {' ', 'f', 'a'}, {'f', 'a', 'd'}, {'f', 'a', 'n'}, {'f', 'a', 'r'}, {'f', 'a', 't'}, {'f', 'e', 'd'}, {'f', 'e', 'n'}, {'f', 'i', 'b'}, {'f', 'i', 'n'}, {'f', 'i', 'r'}, {'f', 'i', 't'}, {'f', 'l', 'u'}, {'f', 'l', 'y'}, {'f', 'o', 'e'}, {'f', 'o', 'p'}, {'f', 'o', 'r'}, {'f', 'r', 'o'}, {'f', 'r', 'y'}, {'f', 'u', 'n'}, {'f', 'u', 'r'}, {' ', 'h', 'a'}, {'h', 'a', 'd'}, {'h', 'a', 'p'}, {'h', 'a', 's'}, {'h', 'a', 't'}, {'h', 'a', 'y'}, {' ', 'h', 'e'}, {'h', 'e', 'n'}, {'h', 'e', 'r'}, {'h', 'e', 's'}, {'h', 'e', 't'}, {'h', 'e', 'y'}, {' ', 'h', 'i'}, {'h', 'i', 'd'}, {'h', 'i', 'p'}, {'h', 'i', 's'}, {'h', 'i', 't'}, {'h', 'o', 'e'}, {'h', 'o', 'p'}, {'h', 'o', 't'}, {'h', 'u', 'b'}, {'h', 'u', 'e'}, {'h', 'u', 't'}, {'i', 'c', 'e'}, {'i', 'c', 'y'}, {' ', 'i', 'd'}, {'i', 'd', 'e'}, {'i', 'd', 's'}, {' ', 'i', 'f'}, {'i', 'f', 's'}, {' ', 'i', 'n'}, {'i', 'n', 's'}, {'i', 'o', 'n'}, {'i', 'r', 'e'}, {' ', 'i', 's'}, {' ', 'i', 't'}, {'i', 't', 's'}, {'i', 'v', 'y'}, {'j', 'a', 'b'}, {'j', 'a', 'r'}, {'j', 'a', 'y'}, {'j', 'e', 't'}, {'j', 'i', 'b'}, {' ', 'j', 'o'}, {'j', 'o', 'b'}, {'j', 'o', 't'}, {'j', 'o', 'y'}, {'j', 'u', 't'}, {' ', 'l', 'a'}, {'l', 'a', 'b'}, {'l', 'a', 'd'}, {'l', 'a', 'p'}, {'l', 'a', 'y'}, {'l', 'e', 'a'}, {'l', 'e', 'd'}, {'l', 'e', 't'}, {'l', 'e', 'u'}, {'l', 'e', 'v'}, {'l', 'i', 'd'}, {'l', 'i', 'e'}, {'l', 'i', 'p'}, {'l', 'i', 't'}, {'l', 'o', 'b'}, {'l', 'o', 'p'}, {'l', 'o', 't'}, {'l', 'y', 'e'}, {'n', 'a', 'b'}, {'n', 'a', 'p'}, {'n', 'a', 'y'}, {'n', 'e', 't'}, {'n', 'i', 'b'}, {'n', 'i', 'l'}, {'n', 'i', 'p'}, {'n', 'i', 't'}, {' ', 'n', 'o'}, {'n', 'o', 'b'}, {'n', 'o', 'd'}, {'n', 'o', 'r'}, {'n', 'o', 's'}, {'n', 'o', 't'}, {' ', 'n', 'u'}, {'n', 'u', 's'}, {'n', 'u', 't'}, {'o', 'a', 'f'}, {'o', 'a', 'r'}, {'o', 'a', 't'}, {'o', 'd', 'e'}, {' ', 'o', 'f'}, {'o', 'f', 't'}, {' ', 'o', 'h'}, {'o', 'h', 's'}, {'o', 'i', 'l'}, {'o', 'l', 'd'}, {' ', 'o', 'n'}, {'o', 'n', 'e'}, {'o', 'p', 's'}, {'o', 'p', 't'}, {' ', 'o', 'r'}, {'o', 'r', 'b'}, {'o', 'r', 'e'}, {'o', 'r', 's'}, {' ', 'o', 's'}, {'o', 'u', 'r'}, {'o', 'u', 't'}, {'o', 'v', 'a'}, {' ', 'p', 'a'}, {'p', 'a', 'd'}, {'p', 'a', 'l'}, {'p', 'a', 'n'}, {'p', 'a', 'r'}, {'p', 'a', 't'}, {'p', 'a', 'y'}, {' ', 'p', 'e'}, {'p', 'e', 'a'}, {'p', 'e', 'n'}, {'p', 'e', 'r'}, {'p', 'e', 't'}, {'p', 'h', 'i'}, {' ', 'p', 'i'}, {'p', 'i', 'e'}, {'p', 'i', 'n'}, {'p', 'i', 's'}, {'p', 'i', 't'}, {'p', 'l', 'y'}, {'p', 'o', 'd'}, {'p', 'o', 't'}, {'p', 'r', 'y'}, {'p', 's', 'i'}, {'p', 'u', 'b'}, {'p', 'u', 'n'}, {'p', 'u', 's'}, {'p', 'u', 't'}, {' ', 'q', 'i'}, {'q', 'o', 'f'}, {'r', 'a', 'n'}, {'r', 'a', 'p'}, {'r', 'a', 't'}, {'r', 'a', 'y'}, {' ', 'r', 'e'}, {'r', 'e', 'd'}, {'r', 'e', 'f'}, {'r', 'e', 'v'}, {'r', 'h', 'o'}, {'r', 'i', 'b'}, {'r', 'i', 'd'}, {'r', 'i', 'p'}, {'r', 'o', 'b'}, {'r', 'o', 'd'}, {'r', 'o', 'e'}, {'r', 'o', 't'}, {'r', 'u', 'b'}, {'r', 'u', 'e'}, {'r', 'u', 'n'}, {'r', 'u', 't'}, {'r', 'y', 'e'}, {'s', 'a', 'c'}, {'s', 'a', 'd'}, {'s', 'a', 'p'}, {'s', 'a', 't'}, {'s', 'a', 'y'}, {'s', 'e', 'a'}, {'s', 'e', 't'}, {'s', 'h', 'e'}, {'s', 'h', 'y'}, {'s', 'i', 'n'}, {'s', 'i', 'p'}, {'s', 'i', 'r'}, {'s', 'i', 't'}, {'s', 'l', 'y'}, {' ', 's', 'o'}, {'s', 'o', 'b'}, {'s', 'o', 'd'}, {'s', 'o', 'l'}, {'s', 'o', 'n'}, {'s', 'o', 'p'}, {'s', 'o', 't'}, {'s', 'o', 'y'}, {'s', 'p', 'a'}, {'s', 'p', 'y'}, {'s', 't', 'y'}, {'s', 'u', 'b'}, {'s', 'u', 'e'}, {'s', 'u', 'n'}, {' ', 't', 'a'}, {'t', 'a', 'b'}, {'t', 'a', 'd'}, {'t', 'a', 'n'}, {'t', 'a', 'p'}, {'t', 'a', 'r'}, {'t', 'a', 'u'}, {'t', 'a', 'v'}, {'t', 'e', 'a'}, {'t', 'e', 'n'}, {'t', 'h', 'e'}, {'t', 'h', 'y'}, {'t', 'i', 'c'}, {'t', 'i', 'e'}, {'t', 'i', 'n'}, {'t', 'i', 'p'}, {' ', 't', 'o'}, {'t', 'o', 'e'}, {'t', 'o', 'n'}, {'t', 'o', 'p'}, {'t', 'o', 'y'}, {'t', 'r', 'y'}, {'t', 'u', 'b'}, {' ', 'u', 'h'}, {'u', 'h', 's'}, {' ', 'u', 'n'}, {' ', 'u', 'p'}, {'u', 'p', 's'}, {'u', 'r', 'n'}, {' ', 'u', 's'}, {'u', 's', 'e'}, {'v', 'a', 'n'}, {'v', 'a', 't'}, {'v', 'e', 't'}, {'v', 'i', 'a'}, {'v', 'i', 'e'}, {' ', 'y', 'a'}, {'y', 'a', 'h'}, {'y', 'a', 'p'}, {'y', 'a', 'r'}, {' ', 'y', 'e'}, {'y', 'e', 'a'}, {'y', 'e', 'h'}, {'y', 'e', 'n'}, {'y', 'e', 'p'}, {'y', 'e', 's'}, {'y', 'e', 't'}, {'y', 'i', 'n'}, {'y', 'i', 'p'}, {'y', 'o', 'd'}, {'y', 'o', 'n'}, {'y', 'o', 'u'}, {'y', 'u', 'p'}, {' ', 'z', 'a'}, {'z', 'a', 'p'}, {'z', 'a', 's'}, {'z', 'e', 'd'}, {'z', 'e', 'n'}, {'z', 'i', 'p'}, {'z', 'i', 't'}, {'z', 'o', 'a'}};

void showWord(const char wordParts[3]) {
  for (int k = 0; k < 69; k++) {
    showLetter(wordParts[0],0,10);
    showLetter(wordParts[1],1,10);
    showLetter(wordParts[2],2,10);
  }
}

void showWord(const char wordParts[3], int timer) {
  for (int k = 0; k < timer; k++) {
    showLetter(wordParts[0],0,10);
    showLetter(wordParts[1],1,10);
    showLetter(wordParts[2],2,10);
  }
}

void scrollText(char wordParts[], int numLetters, int timer){
  for (int i = 0; i < numLetters - 2; i++) {
    for (int k = 0; k < timer; k++) {
      showLetter(wordParts[i],0,10);
      showLetter(wordParts[i+1],1,10);
      showLetter(wordParts[i+2],2,10);
    }
  }
}

void setup() {
  for (int segment = 0; segment < segmentNum; segment++) {
    pinMode(segmentPins[segment], OUTPUT);
  }
  for (int controller = 0; controller < controlNum; controller++) {
    pinMode(controlPins[controller], OUTPUT);
  }
}

void loop() {
//  int timer = 1;
//  double i = 0.00;
//  while (i < 10.00) {
//    show3Digits_10(i,timer);
//    i = i + 0.01;
//  }
//  while (i < 100.0) {
//    show3Digits_100(i,timer);
//    i = i + 0.1;
//  }
//  while (i < 1000) {
//    show3Digits_1000(i,timer);
//    i = i + 1;
//  }
//  for (int i = 0; i < 376; i++) {
//    showWord(words[i], 5);
//  }

  //show3Digits_10(8.65); // Rounding error??
  
  //show3Digits_1000(420,33);
  //showWord(words[81],33); //dab
  
  char w[21] = {' ', ' ', ' ', 'h', 'a', 'v', 'e', ' ', 'a', ' ', 'n', 'i', 'c', 'e', ' ', 'd', 'a', 'y', ' ', ' ', ' '};
  
  scrollText(w, 21, 25);
}

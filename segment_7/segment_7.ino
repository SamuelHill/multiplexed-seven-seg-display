/*This is the code to show numerals 0 to 9 on a 7 segment LED display
It represents seconds*/

//bits representing numerals 0-9
const byte numeral[12]= {
B10111110, // 0
B00001100, // 1
B01110110, // 2
B01011110, // 3
B11001100, // 4
B11011010, // 5
B11111010, // 6
B00001110, // 7
B11111110, // 8
B11011110, // 9
B00000000, // none
B00000001, // DP
};

// 9=Top left     2=Top
// 8=Middle       3=Top right
// 7=Bottom left  4=DP
// 6=Bottom       5=Bottom right
// The binary number order is reversed... (DP/4 = ...0)
const int segmentNum = 8;
const int segmentPins[segmentNum]= { 4,2,3,5,6,7,8,9 };

void setup() {
  for (int segment = 0; segment < segmentNum; segment++) {
    pinMode(segmentPins[segment], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 10); i++) {
    showDigit(i);
    delay(1000);
  }
}

void showDigit (int number) {
  for (int segment = 0; segment < segmentNum; segment++) {
    digitalWrite(segmentPins[segment], bitRead(numeral[number], segment));
  }
}

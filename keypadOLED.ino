//A is for going to the next line
//B is for viewing pressed number
//
//



#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
uint8_t count = 0;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//Create an object of keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

long last = 0;
uint16_t number = 0, pressedNumber = 0, loop_count = 0, current_loop = 0, on_time = 0, off_time = 0;
uint8_t line = 5;
String numString = "";

void startupMessage()
{
  String splashString = "Developed by";
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setCursor(64 - (splashString.length() * 3), 0);
  display.print(splashString);
  display.setTextSize(2);
  splashString = "the.A.D";
  display.setCursor(64 - (splashString.length() * 6), 25);
  display.print(splashString);
  display.display();
  delay(3000);
}
void staticText()
{

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 5);
  display.println("ON:");
  display.setCursor(0, 20);
  display.println("OFF:");
  display.setCursor(0, 35);
  display.println("LOOP:");
  display.setCursor(0, 50);
  display.println("CURRENT LOOP:");


  display.display();
}
void setup()
{
  Serial.begin(115200);

  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  //  startupMessage();

  delay(1000);
  display.clearDisplay();

  staticText();
  //  delay(1000);
}

void loop() {
  //  display.clearDisplay();
  char key = keypad.getKey();// Read the key

  if (key)
  {
    Serial.print("Key Pressed : ");
    Serial.println(key);
    switch (key)
    {
      case 'B':
        {
          Serial.print("No. Pressed : ");
          Serial.println(pressedNumber);


          numString = String(pressedNumber);
          Serial.println(numString.length());
          displayData(numString, 90, line);
          numString = "";
          pressedNumber = 0;
          break;
        }
      case 'A':
        {
          //display.setCursor(90, line);
          if (line != 15)
          {
            line = line + 15;
          }
          else
          {
            line = 5;
          }

          numString = "";
          pressedNumber = 0;
          break;
        }
      case 'C':
        {
          //display.drawRect(80, 3, 20, 60, WHITE);
          display.fillRect(80, 3, 35, 60, BLACK);
          display.display();
          delay(500);
          display.setCursor(90, 5);
          display.print("0000");
          display.setCursor(90, 20);
          display.print("0000");
          display.setCursor(90, 35);
          display.print("0000");
          display.setCursor(90, 50);
          display.print("0000");
          display.display();
          line = 5;
          break;
        }
      default :
        {
          number = number * 10 + (int)key;
          number = number - 48;
          pressedNumber = pressedNumber * 10 + number;
          number = 0;
          break;
        }
    }
  }

}


void displayData(String data, int x, int y)
{
  display.fillRect(80, (line - 2), 35, (line + 12), BLACK);
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(x, y);

  display.print(data);
  display.display();

}

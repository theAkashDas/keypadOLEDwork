//A is for going to the next line
//B is for viewing pressed number
//C is for clear and reset
//* is used for starting the function.



#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>


#define SCREEN_WIDTH              128 // OLED display width, in pixels
#define SCREEN_HEIGHT             64  // OLED display height, in pixels
#define KEY_LED                   10
#define RELAY_ON_OFF_LED          12
#define RELAY_PIN                 A0


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
uint16_t number = 0, pressedNumber = 0, loop_count = 0, counter = 0, current_loop = 0, on_time = 0, off_time = 0;
uint8_t line = 5, pinState = 0;
String numString = "", counterString = "";
bool startFunctioning = false;
long lastMillis = 0;

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
  display.setTextSize(1);
  splashString = "v1.0.9";
  display.setCursor(64 - (splashString.length() * 3), 55);
  display.print(splashString);
  display.display();
  delay(2000);
}

void staticText()
{
  loop_count = 0;
  current_loop = 0;
  on_time = 0;
  off_time = 0;

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

void initialValues()
{
  display.setCursor(90, 5);
  display.print("0000");
  display.setCursor(90, 20);
  display.print("0000");
  display.setCursor(90, 35);
  display.print("0000");
  if (!startFunctioning)
  {
    display.setCursor(90, 50);
    display.print("0000");
  }
  display.display();
  lastMillis = 0;
  numString = "";
  pressedNumber = 0;
  on_time = 0;
  off_time = 0;
  loop_count = 0;
  current_loop = 0;
  startFunctioning = 0;
  line = 5;
  counter = 0;

  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(RELAY_ON_OFF_LED, LOW);
}

void pinSetup()
{
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  pinMode(KEY_LED, OUTPUT);
  digitalWrite(KEY_LED, LOW);
  pinMode(RELAY_ON_OFF_LED, OUTPUT);
  digitalWrite(RELAY_ON_OFF_LED, LOW);
}


void setup()
{
  Serial.begin(115200);

  pinSetup();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  startupMessage();

  delay(1000);
  display.clearDisplay();

  staticText();
  initialValues();
  //  delay(1000);
}

void loop() {
  //  display.clearDisplay();
  char key = keypad.getKey();// Read the key

  if (key)
  {
    digitalWrite(KEY_LED, HIGH);
    delay(50);
    digitalWrite(KEY_LED, LOW);

    Serial.print("Key Pressed : ");
    Serial.println(key);
    if (key == '*')
    {
      startFunctioning = !startFunctioning;
      key = '0';
    }
    Serial.print("Start ? ");
    Serial.println(startFunctioning);
    if (!startFunctioning)
    {
      switch (key)
      {
        case 'B':
          {
            Serial.print("No. Pressed : ");
            Serial.println(pressedNumber);


            numString = String(pressedNumber);
            Serial.println(numString.length());
            Serial.println(line);

            displayData(numString, 90, line);
            if (line == 5)
            {
              on_time = pressedNumber;
            }
            else if (line == 20)
            {
              off_time = pressedNumber;
            }
            else if (line == 35)
            {
              loop_count = pressedNumber;
            }
            else if (line == 50)
            {
              current_loop = pressedNumber;
            }


            numString = "";
            pressedNumber = 0;
            break;
          }
        case 'A':
          {
            //display.setCursor(90, line);
            if (line < 35)
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
            initialValues();
            line = 5;
            break;
          }
        default :
          {
            number = number * 10 + (int)key;
            number = number - 48;
            pressedNumber = pressedNumber * 10 + number;
            if ((pressedNumber / 10000) >= 1) //to truncate the last part of the numbers with more than 4 digit
            {
              Serial.print("Bef : ");
              Serial.println(pressedNumber);
              pressedNumber = pressedNumber / 10;
              Serial.print("After : ");
              Serial.println(pressedNumber);
            }
            number = 0;
            break;
          }
      }
    }
    else
    {
      if (!loop_count)
      {
        while (true)
        {
          if (counter > 9999)
          {
            counter = 0;
          }
          else
          {
            if (millis() - lastMillis > on_time && pinState)
            {
              digitalWrite(RELAY_PIN, LOW);
              digitalWrite(RELAY_ON_OFF_LED, LOW);
              pinState = 0;
              lastMillis = millis();
            }
            else if (millis() - lastMillis > off_time && !pinState)
            {
              digitalWrite(RELAY_PIN, HIGH);
              digitalWrite(RELAY_ON_OFF_LED, HIGH);
              pinState = 1;
              lastMillis = millis();
              counterString = String(counter);
              line = 50;
              displayData(counterString, 90, 50);
              counter ++;
            }
          }
        }
      }
      else
      {
        while (counter <= loop_count)
        {
          if (millis() - lastMillis > on_time && pinState)
          {
            digitalWrite(RELAY_PIN, LOW);
            digitalWrite(RELAY_ON_OFF_LED, LOW);
            pinState = 0;
            lastMillis = millis();
          }
          else if (millis() - lastMillis > off_time && !pinState)
          {
            digitalWrite(RELAY_PIN, HIGH);
            digitalWrite(RELAY_ON_OFF_LED, HIGH);
            pinState = 1;
            lastMillis = millis();
            counterString = String(counter);
            line = 50;
            displayData(counterString, 90, 50);
            counter ++;
          }
        }
        delay(2000);
        display.fillRect(80, 3, 35, 40, BLACK);
        initialValues();
      }
    }
  }
}


void displayData(String data, int x, int y)
{
  display.fillRect(80, (line - 2), 50, 10, BLACK); // fillRect( x , y , width , height, color)
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(x, y);

  display.print(data);
  display.display();

}

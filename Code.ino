/* 
 || @version 1.0
 || @author Andrew Mascolo
 || @date May 15, 2013
 ||
 || @description
 || Simple use of keypad and LCD
*/

#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

long first = 0;
long second = 0;
double total = 0;

char customKey;
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};
byte rowPins[ROWS] = {2,3,4,5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6,7,8,9}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

void setup()
{
  lcd.begin(); // initialize the lcd 
  lcd.backlight();
//  Serial.begin(9600);
  lcd.clear();
  lcd.print("starting . . .  ");
  delay(1000);
  lcd.clear();
}

void loop()
{

  customKey = customKeypad.getKey();
//  Serial.print(customKey);
  
  if(customKey == '0' || customKey == '1' || customKey == '2' || customKey == '3' || customKey ==  '4' || customKey ==  '5' || customKey ==  '6' || customKey ==  '7' || customKey == '8' || customKey == '9' ) 
  {
    lcd.setCursor(0,0);
   
    first = first * 10 + (customKey - '0');
  //  Serial.print(first);
    lcd.print(first);
  
  }else if(customKey == '+')
  {
    lcd.setCursor(0,1);
    lcd.print("                ");  // 16 spaces will clear the space
    if(total != 0)
    {
      first = total;
      lcd.setCursor(0,0);
      lcd.print(first);
    }
    
    lcd.setCursor(0,1);
 //   Serial.println(first);
    lcd.print("+");
    
    second = SecondNumber(); // get the collected the second number
    total = first + second;
    lcd.setCursor(0,1);
    lcd.print(total);
    first = 0, second = 0; // reset values back to zero for next use
  }else if(customKey == '-')
  {
    lcd.setCursor(0,1);
    lcd.print("                ");  // 16 spaces will clear the space
    if(total != 0)
    {
      first = total;
      lcd.setCursor(0,0);
      lcd.print(first);
    }
    lcd.setCursor(0,1);
    lcd.print("-");
    second = SecondNumber();
    total = first - second;
    lcd.setCursor(0,1);
    lcd.print(total);
    first = 0, second = 0;
  }else if( customKey == '*')
  {
    
    lcd.setCursor(0,1);
    lcd.print("                ");  // 16 spaces will clear the space
    if(total != 0)
    {
      first = total;
      lcd.setCursor(0,0);
      lcd.print(first);
    }
    lcd.setCursor(0,1);
    lcd.print("*");
    second = SecondNumber();
    total = first * second;
    lcd.setCursor(0,3);
    lcd.print(total);
    first = 0, second = 0;
  }else if(customKey == '/')
  {
    
    lcd.setCursor(0,1);
    lcd.print("                ");  // 16 spaces will clear the space
    if(total != 0)
    {
      first = total;
      lcd.setCursor(0,0);
      lcd.print(first);
    }
    lcd.setCursor(0,1);
    lcd.print("/");
    second = SecondNumber();
    lcd.setCursor(0,1);

    if(second == 0)
    {
      lcd.print("Invalid");
    }else
    {
       total = (float)first / (float)second;
       lcd.print(total);
    }

    first = 0, second = 0;
  }else if(customKey == 'C')
  {
    total = 0;
    lcd.clear();
    first = second = 0;
  }
}

long SecondNumber()
{
  while( 1 )
  {
    customKey = customKeypad.getKey();
    if(customKey >= '0' && customKey <= '9')
    {
      second = second * 10 + (customKey - '0');
      lcd.setCursor(1,1);   // on the first column will be the operator and after that will come the second number 
      lcd.print(second);
    }
    if(customKey == '=') break;  //return second;
  }
 return second; 
}

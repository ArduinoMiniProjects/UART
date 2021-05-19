#include <math.h>

String command;
int sense_pin = 0;
int led_pin = 2;
int buzzer_pin = 3;

bool my_str_compare(String s1, String s2);

void setup()
{
  analogReference(DEFAULT);
  pinMode(A0, INPUT); // sensor pin
  pinMode(led_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  Serial.begin(9600);
}


void loop()
{
  if(Serial.available() > 0) // some value is send from PC
  {
    command = Serial.readString();
    delay(10);
    Serial.print(command);
    
    //if(command[0] == 'o' and command[1] == 'n')
    //{
    //  digitalWrite(13, HIGH);
    //}

    if( my_str_compare(command, "led on") )
    {
      digitalWrite(led_pin, HIGH);
    }

    if(my_str_compare(command, "led off") )
    {
      digitalWrite(led_pin, LOW);
    }

    if(my_str_compare(command, "buzzer") )
    {
      for(int i = 0; i < 4; i++)
      {
        digitalWrite(buzzer_pin, HIGH);
        delay(300);
        digitalWrite(buzzer_pin, LOW);
        delay(300);
      }
    }

    if(my_str_compare(command, "temperature") )
    {
      // Thermometer
      Serial.print("Temperature is  ");
      Serial.print(-1481.96 + sqrt(2196200 + (1.839 - analogRead(sense_pin) / 1024.0 * 5.0)/0.00000388 ));
      Serial.println(" C");
    }
  }
}


bool my_str_compare(String s1, String s2)
{
  for(int i = 0; i < s2.length(); i++)
  {
    if(s1[i] != s2[i])
    {
      return false; // if characters aren't equal
    }
  }
  return true; // if 6 characters are equal
}

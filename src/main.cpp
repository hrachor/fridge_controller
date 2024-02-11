#include <Arduino.h>
#include <Wire.h>
#include <time_print.h>
#include <temp_print.h>
#include <LiquidCrystal_I2C.h>
#include <menu.h>
#include <pins.h>

bool clear = true;
long old_encoder_value = 0;

void clear_lcd();

void setup () 
{
  pinMode(button, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  temp_setup();
  time_setup();
}

void loop () 
{
  button_state = !digitalRead(button);

  if (button_state == true)
  {
    menu_active = true;
    clear_lcd();
    menu();
  }
  if (menu_active == false)
  {
    print_temp();
    print_time();
  }

  long curr = Enc.read();

  if(old_encoder_value != curr and menu_active)
  {
    old_encoder_value = curr;
    menu();
  }

}

void clear_lcd()
{
  if (clear == true)
  {
    lcd.clear();
    clear = false;
  }
  else
  {
    clear = false;
  }
}
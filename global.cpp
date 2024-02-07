#include "global.h"
#include "Arduino.h"
  
uint8_t getkeys(int Tasto){
uint8_t key;
  if (Tasto < 60) {
    key = DX; 
  } else if (Tasto < 200) {
    key = SU; 
  } else if (Tasto < 400){
    key = GIU; 
  } else if (Tasto < 600){
    key = SX; 
  } else if (Tasto < 800){
    key = SEL; 
  } else {
    key = NULL;
  }
  return key;
}



  //if (analogKey < 60) {
  //  lcd.print("Destra       ");  
  //} else if (analogKey < 200) {
 //   lcd.print("Su           ");
 // } else if (analogKey < 400){
  //  lcd.print("Giù          ");
  //} else if (analogKey < 600){
  //  lcd.print("Sinistra     ");
 // } else if (analogKey < 800){
   // lcd.print("Seleziona    ");
  //} else {
   // lcd.print("Nessun tasto ");
 // }
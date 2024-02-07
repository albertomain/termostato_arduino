// numeroCicli.cpp
//*************************************************
// scrive ed IMPOSTA IL NUMERO DI CICLI DA ESEGUIRE
//*************************************************  

#include "numeroCicli.h"
#include "MyLiquidCrystal.h"
#include "global.h"


numeroCicli::numeroCicli(){
  Cicli = 10;
}


numeroCicli::posPrint(uint8_t X, uint8_t Y) {
    uint16_t blinker = millis();
    //"%08ld" è ul numero di CIFRECILI se si modificano le cifre modificare 9 uguale al numero di cifre
    sprintf(buffer, "%08ld", Cicli);
    lcd.setCursor(X,Y);
    lcd.print(buffer);
    checkPosCursore();
    lcd.setCursor(X+_Cursore,Y);
    
    if (_CursoreOn)
      if ((blinker%500) < 100) lcd.print("_");
 }



uint8_t numeroCicli::tasti(uint8_t key) {
  
  lcd.setCursor(2, 1);
  if (key!=oldkey) 
  {
     oldkey = key;
  switch (key)
    {
      case DX:  posCursoreDx(); break;
      case SX:  posCursoreSx(); break;
      case GIU: Decrementa(); return NEW_CICLE; break;
      case SU:  Incrementa(); return NEW_CICLE; break;
      case SEL: break;
      default:
           key=0;
    }  
   
  }  
  return 0;
}

numeroCicli::IncDec(){
  unsigned long factor = 1;
  uint8_t i;
  unsigned long tmpCicli = Cicli;
  const long maxValue = Pow10<CIFRECILI>::value;
   
  if (!_CursoreOn) return;

  for(int i = 0; i < ((CIFRECILI - _Cursore)-1); i++) {
     factor *= 10;
  }
  tmpCicli += direction * factor;
  if (tmpCicli < maxValue) Cicli = tmpCicli;
   
 } 

unsigned long numeroCicli::getCicli(){
   return Cicli;
 } 

void numeroCicli::setCicli(unsigned long int nCicli){ 
  Cicli = nCicli;
} 

numeroCicli::Incrementa(){
  direction = 1;
  IncDec();
 } 

numeroCicli::Decrementa(){
  direction = -1;
  IncDec();
 } 


numeroCicli::posCursoreDx(){
  _Cursore++;
  checkPosCursore();
 } 

numeroCicli::posCursoreSx(){
  _Cursore--;
   checkPosCursore();
 } 


numeroCicli::setCursoreOn() {
  _CursoreOn = true;
 }

numeroCicli::setCursoreOff(){
  _CursoreOn = false;
}

numeroCicli::checkPosCursore(){
 if (_Cursore >= CIFRECILI) _Cursore = CIFRECILI-1;
}


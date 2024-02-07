// statoDeiCicli.cpp
//*************************************************
// scrive ed IMPOSTA IL NUMERO DI CICLI DA ESEGUIRE
//*************************************************  

#include "statoDeiCicli.h"
#include "MyLiquidCrystal.h"
#include "global.h"

 

statoDeiCicli::posPrint(uint8_t X, uint8_t Y) {
    
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



uint8_t statoDeiCicli::tasti(uint8_t key) {
  //#define NEW_RESETCOUNTER 16
  if ((reset_contatore) && (key == GIU)){
    if ((millis() - reset_contatore) > TIMEOUTRESETCONTATORE) {
       reset_contatore = 0;

       return NEW_RESETCOUNTER;       
       
    }
  }

  lcd.setCursor(2, 1);
  if (key!=oldkey) 
  {
    oldkey = key;
    switch (key)
    {
      case DX:
        posCursoreDx();
      break;
      case SX:
       posCursoreSx();
      break;
      case GIU:
       reset_contatore = millis();
      break;
      case SU:
        key = SU; 

        return NEW_STARTSTOP;
       
      break;
      case SEL:
        key = SEL; 
       
    //    lcd.print("Seleziona    ");
      break;
      default:
      //    lcd.print("Nessun tasto ");
          key=0;
    }  
  
  }  
  return 0;
}

statoDeiCicli::IncDec(){
  unsigned long factor = 1;
  uint8_t i;
  unsigned long tmpCicli = Cicli;
  const long maxValue = Pow10<CIFRECILI>::value;
   
  if (!_CursoreOn) return; //se il curose è attivo vuol dire che sono selezionato

  for(int i = 0; i < ((CIFRECILI - _Cursore)-1); i++) {
     factor *= 10;
  }
  tmpCicli += direction * factor;
  if (tmpCicli < maxValue) Cicli = tmpCicli;
   
 } 

unsigned long statoDeiCicli::getCicli(){
   return Cicli;
 } 

void statoDeiCicli::setCicli(unsigned long NewCicli){
   Cicli = NewCicli;
 }  

statoDeiCicli::posCursoreDx(){
  _Cursore++;
  
  checkPosCursore();
 } 

statoDeiCicli::posCursoreSx(){
  _Cursore--;
    checkPosCursore();
 } 


statoDeiCicli::setCursoreOn() {
  _CursoreOn = true;
 }

statoDeiCicli::setCursoreOff(){
  _CursoreOn = false;
}

statoDeiCicli::checkPosCursore(){
 if (_Cursore >= CIFRECILI) _Cursore = CIFRECILI-1;
}

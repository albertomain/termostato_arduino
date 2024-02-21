// TimeOut.cpp
//*************************************************
// scrive ed IMPOSTA IL TIME OuT
//*************************************************

#include "TimeOut.h"
#include "MyLiquidCrystal.h"
#include "global.h"


TimeOut::TimeOut(){
   minimo_uno();
   TimeOut = 150; //inizializzo
}

TimeOut::posPrint(uint8_t X, uint8_t Y) {
    uint16_t blinker = millis();
    // Formatta il numero con una cifra decimale e zeri iniziali/finali

    sprintf(buffer, "%03d", TimeOut);
  
    lcd.setCursor(X,Y);
    lcd.print(buffer);
    checkPosCursore();
    lcd.setCursor(X+_Cursore,Y);

    if (_CursoreOn)
       if ((blinker%500) < 100) lcd.print("_");
    

}


uint8_t TimeOut::tasti(uint8_t key) {
  
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
        Decrementa();
        return 1;
      break;
      case SU:
        Incrementa();
        return 1;
      break;
      case SEL:
        break;
      default:
          key=0;
    }  
    
  }  
  return 0;
}

TimeOut::IncDec(){
  unsigned long factor = 1;

  unsigned int tmpTimeOut = TimeOut;
  const long maxValue = Pow10<CIFRETIMEOUT>::value;
  
   if (!_CursoreOn) return;

   switch (_Cursore) {
    case 0:  factor = 100; break;
    case 1:  factor = 10; break;
    case 2:  factor = 1; break;
    //case 3:  factor = 1; break;
   } 

   tmpTimeOut += direction * factor;


   if (tmpTimeOut < maxValue) TimeOut = tmpTimeOut;
   minimo_uno();
  
} 
 

TimeOut::minimo_uno(){
  if (!TimeOut) TimeOut = 1;
}

unsigned int TimeOut::getTimeOut(){
   return TimeOut;
} 

TimeOut::Incrementa(){
  direction = 1;
  IncDec();
} 

TimeOut::Decrementa(){
  direction = -1;
  IncDec();
} 


TimeOut::posCursoreDx(){
  _Cursore++;
  checkPosCursore();
} 

TimeOut::posCursoreSx(){
  _Cursore--;
  checkPosCursore();
} 


TimeOut::setCursoreOn() {
  _CursoreOn = true;
}

TimeOut::setCursoreOff(){
  _CursoreOn = false;
}

TimeOut::checkPosCursore(){
 if (_Cursore >= CIFRETIMEOUT) _Cursore = CIFRETIMEOUT-1;
 
}


// TimeOut.h
//*************************************************
// scrive ed IMPOSTA IL NUMERO DI CICLI DA ESEGUIRE
//*************************************************

#ifndef TimeOut_h
#define TimeOut_h
#include "Arduino.h"
#include "global.h"

 


class TimeOut {
public:
    TimeOut();
    posPrint(uint8_t X, uint8_t Y);
    uint8_t tasti(uint8_t key);
    unsigned int getTimeOut(); 
    setCursoreOn();
    setCursoreOff();
   
private:
    checkPosCursore();
    Incrementa();
    Decrementa();
    IncDec();
    posCursoreDx();
    posCursoreSx();
    minimo_uno(); 
    char buffer[CIFRETIMEOUT+4];
    unsigned int TimeOut;
    uint8_t _Cursore;
    bool    _CursoreOn;
    uint8_t  oldkey;
    int8_t direction; //incremento decremento
};

#endif
// numeroCicli.h
//*************************************************
// scrive ed IMPOSTA IL NUMERO DI CICLI DA ESEGUIRE  
//*************************************************

#ifndef numeroCicli_h
#define numeroCicli_h
#include "Arduino.h"
#include "global.h"




class numeroCicli {
public:
    numeroCicli();
    posPrint(uint8_t X, uint8_t Y);
    uint8_t tasti(uint8_t key);
    unsigned long getCicli(); 
    void setCicli(unsigned long int nCicli); 
    
    setCursoreOn();
    setCursoreOff();

private:
    checkPosCursore();
    Incrementa();
    Decrementa();
    IncDec();
    posCursoreDx();
    posCursoreSx();

    char buffer[CIFRECILI+1];
    unsigned long Cicli;
    uint8_t _Cursore;
    bool    _CursoreOn;
    uint8_t oldkey;
    int8_t direction; //incremento decremento
};

#endif
// statoDeiCicli.h
//*************************************************
// scrive IL NUMERO EFFETTIVO DEI CONTATORI DEI CICLI
//*************************************************  

#ifndef contaCicli_h
#define contaCicli_h
#include "Arduino.h"
#include "global.h"




class statoDeiCicli {
public:
    posPrint(uint8_t X, uint8_t Y);
    uint8_t tasti(uint8_t key);
    unsigned long getCicli(); 
    void setCicli(unsigned long NewCicli); 
    
    setCursoreOn();
    setCursoreOff();
    
  
private:
    checkPosCursore();
    IncDec();
    posCursoreDx();
    posCursoreSx();

    char buffer[CIFRECILI+1];
    unsigned long Cicli;
    uint8_t _Cursore;
    bool    _CursoreOn;
    unsigned long reset_contatore; //timer per reset del contatore
    uint8_t oldkey;
    int8_t direction; //incremento decremento

};

#endif
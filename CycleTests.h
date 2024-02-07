#ifndef CYCLETEST_H
#define CYCLETEST_H

#include "Arduino.h"
#include "global.h"

 


class CycleTests {
public:
    CycleTests();
    Cycle();
    unsigned char getStato();
    unsigned long getCicleCounting();
    unsigned int getCycleTick();

    void ResetCicle();
    void Start();
    void Stop();
   
private:
    
    StatoMacchina(byte NuovoStato);
    unsigned char Stato;
    unsigned char debounce;
    int OldVerificaPresenzaCorrente;
    bool PresenzaCorrente;
    bool OldPresenzaCorrente;
    unsigned int CycleTick; //conta i decimi di secondo per il timeout
    unsigned char TimerRele_StalloOff;

    unsigned long Cicli;
};


#endif // CYCLETEST_H
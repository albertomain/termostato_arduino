#include "CycleTests.h"
#include "MyLiquidCrystal.h"
#include "global.h"

bool CurrentPresent;



CycleTests::CycleTests()
{


}



unsigned char CycleTests::getStato()
{
 return Stato;
}
  
void CycleTests::Start(void)
{
  TimerRele_StalloOff = TIMEOUTSTALLO_OFF;
  digitalWrite(TEST_ENDPIN, LOW); 
  StatoMacchina(HEATING);
  CycleTick = 0;
}
   
void CycleTests::Stop(void)
{
  TimerRele_StalloOff = TIMEOUTSTALLO_OFF;
  StatoMacchina(SPEGNIMENTO_STALLO);
  CycleTick = 0;
}
   

CycleTests::StatoMacchina(byte NuovoStato)
{
  if (NuovoStato!=DO_NOTHING) Stato = NuovoStato;
  switch(Stato){
    case TUTTO_SPENTO:
       digitalWrite(TEST_ENDPIN, LOW); 
       digitalWrite(HEATING_PIN, LOW);  
       digitalWrite(COOLING_PIN, LOW);
       TimerRele_StalloOff = TIMEOUTSTALLO_OFF;
    break;
    case SPEGNIMENTO_STALLO:
       digitalWrite(TEST_ENDPIN, HIGH); 
       digitalWrite(HEATING_PIN, LOW);  
       digitalWrite(COOLING_PIN, LOW);
    
       if (TimerRele_StalloOff)  TimerRele_StalloOff --;
       if (TimerRele_StalloOff == 0) Stato = TUTTO_SPENTO;
    break;
    case HEATING:
       digitalWrite(HEATING_PIN, HIGH);  //Scalda
       digitalWrite(COOLING_PIN, LOW);
     
    break;
    case COOLING:
        digitalWrite(HEATING_PIN, LOW);  //Raffredda
        digitalWrite(COOLING_PIN, HIGH);  
      
    break;
  }
//  Serial.print(Stato); 
 // Serial.println(TimerRele_StalloOff); 
}



unsigned long CycleTests::getCicleCounting()
{
  return Cicli;
}

unsigned int CycleTests::getCycleTick()
{
  return CycleTick;
}

void CycleTests::ResetCicle()
{
  Cicli = 0;
}


CycleTests::Cycle()
{
  
  int VerificaPresenzaCorrente;
  bool ChgStatoCorrente;
  
  VerificaPresenzaCorrente = digitalRead(CURRENT_INP); 
  if (OldVerificaPresenzaCorrente != VerificaPresenzaCorrente) {
     debounce = 0;
  } 

  if (debounce < MAX_DEBOUNCE)  debounce++;
  OldVerificaPresenzaCorrente = VerificaPresenzaCorrente;
  
   
  if (debounce == MAX_DEBOUNCE) {
    if (VerificaPresenzaCorrente){ 
          PresenzaCorrente = true;
       } else {
          PresenzaCorrente = false;
       }
  }
   

  if (Stato>SPEGNIMENTO_STALLO){ //SE STATO è ACCESO
    CycleTick++;
    ChgStatoCorrente = (OldPresenzaCorrente ^ PresenzaCorrente);
    if (ChgStatoCorrente) CycleTick = 0;

    if (ChgStatoCorrente & PresenzaCorrente) Cicli++;
    if (PresenzaCorrente) {
         StatoMacchina(HEATING);
     } else{
        StatoMacchina(COOLING);
     }
  } else StatoMacchina(DO_NOTHING);


  OldPresenzaCorrente = PresenzaCorrente;
  
  
}
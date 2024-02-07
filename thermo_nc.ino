#include <LiquidCrystal.h>
#include "MyLiquidCrystal.h"
#include "numeroCicli.h"
#include "TimeOut.h"
#include "CycleTests.h"
#include "MyDebug.h"
#include "TimeOut.h"

#include "statoDeiCicli.h"

//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int serial_in;
  
numeroCicli Cicli;
statoDeiCicli contatore;
TimeOut    TimeOutOn;
TimeOut    TimeOutOff;
CycleTests CycleTest;

MyDebug    myDebug;

unsigned char Errore;

void setup() {
  pinMode(HEATING_PIN, OUTPUT);
  pinMode(TEST_ENDPIN, OUTPUT);
  pinMode(COOLING_PIN, OUTPUT);
  pinMode(CURRENT_INP, INPUT);
  
  //setupTimer(); DA INTERRUPT

 // lcd.begin(16,2); // Dimensioni del display LCD
 // lcd.print("www.14core.com"); // Visualizza il testo sul display
  //lcd.setCursor(0,1); // Imposta il cursore (colonna,riga)
  lcd.print("IMQ RELE TEST");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  Serial.begin(9600); // Apertura della porta seriale a 9600 baud
  lcd.begin(16, 2);
//  lcd.print("Premi un tasto");
  lcd.clear();
  
    
  TimeOutOn.setCursoreOff();
  TimeOutOff.setCursoreOff();
  Cicli.setCursoreOn();
  // setTimerData(TimeOutOn.getTimeOut(), TimeOutOff.getTimeOut()); DA INTERRUPT

  //  Cicli.setCicli(fineCicli); DA INTERRUPT
}

void loop() {
  static uint8_t key;
  static uint8_t oldkey;
  static uint8_t Campo = 0;
  

  volatile  int analogKey;
 // for (int lcd_cursor = 0; lcd_cursor < 32; lcd_cursor++) {
 //   if (lcd_cursor == 15) lcd.setCursor(0,1);
 //   else if (lcd_cursor == 31) lcd.home();
 //   while (!Serial.available()); // Attende un segnale dal computer
 //  serial_in = Serial.read(); // Riceve il segnale in ASCII
 //  lcd.write(serial_in); // Scrive sul display
 // }

  analogKey = analogRead(A0);

  Cicli.posPrint(0,0);
  contatore.posPrint(0,1);
  TimeOutOn.posPrint(13,0);
  TimeOutOff.posPrint(13,1);
  
  lcd.setCursor(8,0);

  switch (CycleTest.getStato())
  {
    case DO_NOTHING:
     lcd.print("N");
    break;
    case TUTTO_SPENTO:
     lcd.print("S");
    break;
    case SPEGNIMENTO_STALLO:
     lcd.print("T");
    break;
    case HEATING:
     lcd.print("H");
    break;
    case COOLING:
     lcd.print("C");
    break;
  }    

 Serial.print(Errore);
  lcd.setCursor(8,1);
  switch (Errore)
  {
    case NO_ERROR:
     lcd.print("NE"); //NO ERROR
    break;
    case TIMEOUT_HEATING: //ERRORE HEATING
     lcd.print("EH");
    break;
    case TIMEOUT_COOLING: //ERRORE HEATING
     lcd.print("EC");
    break;
  }
  
  key = getkeys(analogKey);
  
  uint8_t action_requested = 0;
  switch (Campo){ //mando la pressione del tasto al campo evidenziato sul display con il cursore
        case 0:  if (Cicli.tasti(key)) action_requested = NEW_CICLE; break;
        case 1:  if (TimeOutOn.tasti(key)) action_requested = NEW_TIMEOUTON; break;
        case 2:  if (TimeOutOff.tasti(key)) action_requested = NEW_TIMEOUTOFF; break;
        case 3:  if (action_requested|=contatore.tasti(key))   break;
  }    
 
//esegue funzioni di refresh del timer a seguito di pressione dei tasti
  if (action_requested & (NEW_CICLE)){
   // unsigned long int tmpCilci=Cicli.getCicli();  DA INTERRUPT
    //setTimerCicle(tmpCilci); DA INTERRUPT
    // Serial.println(tmpCilci); DA INTERRUPT
  }
 // if (action_requested & (NEW_TIMEOUTON|NEW_TIMEOUTOFF)) setTimerData(TimeOutOn.getTimeOut(), TimeOutOff.getTimeOut()); DA INTERRUPT
  if (action_requested & (NEW_STARTSTOP)) {
       if (CycleTest.getStato()>SPEGNIMENTO_STALLO) CycleTest.Stop();
       else CycleTest.Start();
       Errore = 0;
  }

  if (action_requested & (NEW_RESETCOUNTER)){
     CycleTest.Stop();
     CycleTest.ResetCicle();
  }


    

    if (key!=oldkey){
      if (key == SEL){
        Cicli.setCursoreOff();
        TimeOutOn.setCursoreOff();
        TimeOutOff.setCursoreOff(); 
        contatore.setCursoreOff(); 
        Campo++; //CAMPO DEL DISPLAY EVEDENZIATO (cursore attivo)
        if (Campo >= 4) Campo = 0;
        switch (Campo){
          case 0: Cicli.setCursoreOn(); break;
          case 1: TimeOutOn.setCursoreOn();    break;
          case 2: TimeOutOff.setCursoreOn();   break;
          case 3: contatore.setCursoreOn();   break;
        }    
      }
      oldkey = key;;
    }
  //lcd.setCursor(2, 1);


    CycleTest.Cycle();
    contatore.setCicli(CycleTest.getCicleCounting());

    if (CycleTest.getStato()>SPEGNIMENTO_STALLO){ //SE SONO ATTIVO IN HEATIG O COOLING
      if (CycleTest.getStato() == HEATING){
        if (CycleTest.getCycleTick() > (TimeOutOn.getTimeOut()*10)) {
          Errore = TIMEOUT_HEATING;
          CycleTest.Stop();
        }
      }else
        if (CycleTest.getStato() == COOLING){
          if (CycleTest.getCycleTick() > (TimeOutOff.getTimeOut()*10)){
          Errore = TIMEOUT_COOLING;
          CycleTest.Stop();
        }
      } 
                   
      if (CycleTest.getCicleCounting() >= Cicli.getCicli()) 
      {
        CycleTest.Stop();
        Errore = 0;
      }
    }


     
      Serial.print(" ");
      Serial.print(CycleTest.getCycleTick());
      Serial.print(" ");
      Serial.println(TimeOutOff.getTimeOut());
  myDebug.MyPrint();

  delay(100);

}





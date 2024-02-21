// numeroCicli.h
#ifndef global_h
#define global_h
 
#include "Arduino.h"
//Se si modifica CIFRECILI modificare anche il numero in sprintf nel file numeroCicli.cpp
#define CIFRECILI 8
#define CIFRETIMEOUT 3

#define NEW_CICLE 1
#define NEW_TIMEOUTON 2
#define NEW_TIMEOUTOFF 4
#define NEW_STARTSTOP 8
#define NEW_RESETCOUNTER 16

#define HEATING_PIN 2
#define COOLING_PIN 17
#define TEST_ENDPIN 3
#define CURRENT_INP 16

#define TIMEOUTRESETCONTATORE 5000
#define TIMEOUTSTALLO_OFF 10

#define SU  1
#define GIU 2
#define SX  3
#define DX  4
#define SEL 5

#define DO_NOTHING          0   
#define TUTTO_SPENTO        1
#define SPEGNIMENTO_STALLO  2
#define HEATING             3 
#define COOLING             4


#define MAX_DEBOUNCE        5

#define NO_ERROR 0
#define TIMEOUT_HEATING 1
#define TIMEOUT_COOLING 2 

//usato per invertire i attivi basso
//#define INVERTI_RELE 1

#ifdef INVERTI_RELE
  #define RELE_OFF_ HIGH
  #define RELE_ON_  LOW
#else
  #define RELE_OFF_ LOW
  #define RELE_ON_  HIGH
#endif

void RELE_TEST_END(int value);
void RELE_COOLING(int value);

template <unsigned int exponent>
struct Pow10 {
    static const long value = 10 * Pow10<exponent - 1>::value;
};

template <>
struct Pow10<0> {
    static const long value = 1;
};


uint8_t getkeys(int Tasto);


#endif
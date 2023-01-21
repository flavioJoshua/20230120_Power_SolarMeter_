#define funzionuiV1

#include <Arduino.h>
#include "funzioni.h"
#if defined(ESP8266) || defined(ARDUINO_ARCH_SAMD)
   #include <avr/dtostrf.h>
#endif




/// @brief  qualcosa  di descrizione
void testfunc()
{
    Serial.println("test Func");    

}


#if  defined(ARDUINO_AVR_UNO) ||  defined(ARDUINO_AVR_MEGA2560) 

    int freeRam() {
    extern int __heap_start,*__brkval;
    int v;
    return (int)&v - (__brkval == 0
    ? (int)&__heap_start : (int) __brkval);
    }

    void display_freeram(){
    Serial.print(F("- SRAM left: "));
    Serial.println(freeRam());
    }

#elif (ARDUINO_ARCH_SAMD )
    //#include "thingProperties.h"
  

    extern "C" char* sbrk(int incr);

    int freeRam() {
    char top;
    return &top - reinterpret_cast<char*>(sbrk(0));
    }

    void display_freeram(){
    Serial.print(F("- SRAM left: "));
    Serial.println(freeRam());
    }

   

#else

#endif



/// @brief take  last  10 misure  whether  are less duplicate misure for have 10 total misures /  
/// @param voltages[]  //for make avarage  of last 10 Voltages misures- declare a module Variable: long voltages[10];
/// @param valore 
/// @return return  avarage  of last  10 misure 
/// @warning  need a static  variable for  have a memory of last 10 values
long GetAvarageMisure(long valore,long voltages[])
{
  ///faccio la somma per dividerlo per il numero di misurazione 10
  long Totale=0;
  ///prima verifico che non ci siano valori non validi come inferiore a 1
  for (size_t i = 0; i < 9; i++)
  {
    if(voltages[i]<1)
    {
      Serial.println(F("valore AdjVoltages inferiore a 1  "));
      voltages[i]=valore;
    }
    else
    {
      
    }
  }
  ///scrivo l'ultimo valore 
  voltages[9]=valore;

  ///sommo tutti i valori 
  for (size_t i = 0; i < 10; i++)
  {
    Totale=Totale + voltages[i];
   /*  Serial.print( F(" Valore  Voltages aggiunto : "));
    Serial.print( voltages[i]);
    Serial.print(F(" -Valore Totale AdjVoltage: "));
    Serial.println(Totale); */
  }

    for (size_t i = 0; i < 10; i++)
  {
    voltages[i]=voltages[i+1];
  }
  long valoreMedio=0;
  valoreMedio=Totale/10;
  return valoreMedio;
}




/// @brief funzione  prende un Nuemro Float e  ritorna le due parti Intera e Decimale in formato Stringa
/// @param valoreFloat numero Float da  dividere 
/// @param Intero output  Stringa parte intera 
/// @param Decimale  output String  parte  decimale
void separaDecimali(float valoreFloat, String &Intero, String &Decimale)
{
#pragma region primo metodo
//   char line[20] = {' '};
//   // char lineDecimal[20]={' '};
//   // char lineInteraDecimale[30]={' '};
//   // conversione da  float a   char[]

//   // da Float  prendi la parte Intera e la parte decimale
  int numeroIntero = (int)valoreFloat;
//   // float numeroDecimale=(abs(valore) - abs((int)numeroIntero) * 10000 );
//   float numeroDecimale = (abs(valoreFloat) - abs((int)numeroIntero));

//   // Serial.println(" float  NumeroDecimal:" + String(numeroDecimale));
//   // int numeroIntDecimale=(int)(numeroDecimale*100);  //crerebbe  semplicemente  la elidazione dalla parte  decimale

//   int numeroIntDecimale = round(numeroDecimale * 100); /* sopra  creo il giusto arrotondamento per difetto o per eccesso e non la elidazione semplice della  parte decimale */

//   // sprintf(lineDecimal, "%d.%05d ", numeroIntero ,numeroIntDecimale);/* non funziona la parte Float  */
//   Serial.print(F(" Func  separaDecimali primo metodo --- NumeroIntDecimale : "));
//   Serial.println(numeroIntDecimale);
//   sprintf(line, "parte intera: %d parte decimale: %i ", numeroIntero, numeroIntDecimale);
//   // Serial.println( "LineDecimal: " + String( lineDecimal) );
//   Serial.print(F("Line: ")); //+ String(line));
//   Serial.println(line);
#pragma endregion 
  // parte Separazione Float Intera  Decimale  finita
#pragma region secondo metodo di separazione intero - Decimale
  // da Float  "valore" a String "temp"
  char temp[30];
  dtostrf(valoreFloat, 5, 3, temp);
  Serial.print("Func  separaDecimali Secondo metodo dtostrf ");
  Serial.println(temp);

  //  converto  da Float a String con due cifre decimali
  String convStrFloat = String(valoreFloat, 2);
  int virgolaPos = convStrFloat.indexOf(".");
/*   Serial.print(F("  ConvStrFloat: "));
  Serial.println(convStrFloat);
  Serial.print(F(" posizione . "));
  Serial.println(virgolaPos); */
  String parteIntera = String(numeroIntero);
  // posso avere  una o due cifre Decimali
  String parteDecimale = convStrFloat.substring(virgolaPos + 1, convStrFloat.length());
  Serial.print(" stringa parte decimale: ");
  Serial.println(parteDecimale);

  // metto sempre la String con l doppia cifra
  int grandezza = parteIntera.length();
  if (grandezza == 1)
  {
    parteIntera = "0" + parteIntera;
  }
  Serial.print(F("Grandezza : ")); // + String(grandezza));
  Serial.println(grandezza);
#pragma endregion 
  Intero = parteIntera;
  Decimale = parteDecimale;

  Serial.println(F("fine funzione Separa Decimali"));
}

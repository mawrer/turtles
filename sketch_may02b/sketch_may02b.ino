#include <SnoozeLib.h>
const int LEDPin = 13;        // pin para el LED
const int PIRPin = 2;         // pin de entrada (for PIR sensor)
 
int pirState = LOW;           // de inicio no hay movimiento
int val = 0;                  // estado del pin
int state = HIGH;             // estado alto 
int count_cycle = 0;
int count_mov = 0;


void setup() 
{
 pinMode(LEDPin, OUTPUT); 
 pinMode(PIRPin, INPUT);
 Serial.begin(9600);
}
 
void loop()
{
 delay(1000);
 Serial.println("        Leyendo cada 1 seg...");
 if (count_cycle <= 6){
   Serial.println("count cycle:");
   Serial.println(count_cycle);
   val = digitalRead(PIRPin);
   if (val == HIGH)   //si está activado
   {
     Serial.println("count mov: ");
     Serial.println(count_mov);     
     Serial.println("    Movimiento DETECTADO! contador + 1");
     count_mov = count_mov + 1;
     Serial.println("count mov: ");
     Serial.println(count_mov);
     Serial.println("    Snoozing 20 seg...");
     if (count_mov == 3){
       Serial.println("count mov:");
       Serial.println(count_mov);
       digitalWrite(LEDPin, HIGH);  //LED ON
       if (pirState == LOW)  //si previamente estaba apagado
       {
         Serial.println("    Sensor activado");
         pirState = HIGH;
       }
       delay(100);
       snoozeLib.snooze(20000);
       Serial.println("    Wake UP!!!");
       digitalWrite(6,state); 
       count_cycle = 0;
       count_mov = 0;
      }
   } 
   else   //si esta desactivado
   {
     Serial.println("Movimiento NO detectado.");
     digitalWrite(LEDPin, LOW); // LED OFF
     if (pirState == HIGH)  //si previamente estaba encendido
     {
       Serial.println("Sensor parado");
       pirState = LOW;
     }
   }
   count_cycle = count_cycle + 1 ;
 }
 else
 {
   count_cycle = 0;
   count_mov = 0;
   Serial.println("count cycle: ");
   Serial.println(count_cycle);
   Serial.println("count mov: ");
   Serial.println(count_mov);
 }
}

void wakeup(){
  snoozeLib.wakeup();    //wakeup the CPU
  state=!state;         //change the state
  }

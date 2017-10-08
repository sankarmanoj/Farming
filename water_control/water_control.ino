#include <NewPing.h>
#include <CircularBuffer.h>
#include <SoftTimer.h>

#define PUMP_PIN 4
NewPing ultrasonic(3,2,100);
bool pump_state = false;

unsigned long last_read_time = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Task update(50,updatePump);
  Task print(500,printDistance);  
  SoftTimer.add(&update);
  SoftTimer.add(&print);
  pinMode(PUMP_PIN,OUTPUT);
}


void updatePump(Task * task)
{
  digitalWrite(PUMP_PIN,pump_state);
}

void printDistance(Task * task)
{
     int height = 21 - (ultrasonic.ping_cm()); 
     Serial.print(ultrasonic.ping_cm());
     Serial.print(" ");
     Serial.println(height);
     if(height > 15&&(!pump_state))
     {
      pump_state = true;
      Serial.println("Pump On");
     }
     if(height < 9&&pump_state)
     {
      pump_state = false;
      Serial.println("Pump Off");
     }
}
  



 #include "BluetoothSerial.h"
#include "ELMduino.h"


BluetoothSerial SerialBT;
#define ELM_PORT   SerialBT
#define DEBUG_PORT Serial


ELM327 myELM327;

int obr;
uint16_t rpm;
int CT;

void setup()
{
  
#if LED_BUILTIN
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
#endif
  
  DEBUG_PORT.begin(115200);
  
  SerialBT.setPin("1234");
  ELM_PORT.begin("ArduHUD", true);
  pinMode(5, OUTPUT);
  pinMode(19, OUTPUT);
   pinMode(21, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(19, LOW);
   digitalWrite(21, LOW);
  if (!ELM_PORT.connect("OBDII"))
  {
    DEBUG_PORT.println("Couldn't connect to OBD scanner - Phase 1");
    while(1);
  }

  if (!myELM327.begin(ELM_PORT, true))
  {
    Serial.println("Couldn't connect to OBD scanner - Phase 2");
    while (1);
  }

  Serial.println("Connected to ELM327");
//test 
dacWrite(25, 0);
   digitalWrite(21, HIGH);
   digitalWrite(5, LOW);
   delay(100);
   dacWrite(25, 111);
   digitalWrite(19, HIGH);
   digitalWrite(21, LOW); 
    delay(100);
dacWrite(25, 222);
digitalWrite(19, LOW);
   digitalWrite(5, HIGH);
    delay(100);
  digitalWrite(5, LOW);
  dacWrite(25, 0);
}


void loop()
{
  float tempRPM = myELM327.rpm();

  float temp= myELM327.engineCoolantTemp();
  if (myELM327.status == ELM_SUCCESS)
  {
    rpm = (uint16_t)tempRPM;//read RPM
    CT=(int8_t)temp;//read engine coolant temperature
    obr=int(rpm/25);
    //Serial.println(CT);
    //Serial.println("st C TC");
    if(obr>222){obr=222;}//max RPM is 6k
    dacWrite(25, obr);
    if(70>=CT and CT>40){//show coolant temperature
      digitalWrite(21, HIGH);
      digitalWrite(19, LOW); 
      digitalWrite(5, LOW);
    }else if (100>=CT and CT>70){
      digitalWrite(21, LOW);
      digitalWrite(19, HIGH);
      digitalWrite(5, LOW);
    }else if (CT>100){
      digitalWrite(21, LOW);
      digitalWrite(19, LOW);
      digitalWrite(5, HIGH);
    } else{
      digitalWrite(21, LOW);
      digitalWrite(19, LOW);
      digitalWrite(5, LOW);
    }
   
    delay(1);
    
  }
  else
    myELM327.printError();
}

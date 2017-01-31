#include <SoftwareSerial.h>


unsigned char state=0;

SoftwareSerial swSer(13, 15, false, 256);
enum mystate {
  INIT, 
  CLOSE_ECHO,
  START_CAM,
  CAPTURE,
  READ,
  WAIT,
  
  };


void setup() {
  Serial.begin(115200);
  swSer.begin(115200);

  Serial.println("\nSoftware serial test started");
 
}

void loop() 
{
  switch(state)
  {
    case INIT:
        init_gsm();
    break;
    case CLOSE_ECHO:
        close_echo();
    break;
    case START_CAM:
       // Serial.println("Start cam");
        startcam();
    break;
    case CAPTURE:
        capture();
    break;
    case READ:
      
    break;  
    case WAIT:
        wait();
    break;
  }
  
  /* while (swSer.available() > 0) {
    Serial.write(swSer.read());
  }
  while (Serial.available() > 0) {
    swSer.write(Serial.read());
  }
  */
}

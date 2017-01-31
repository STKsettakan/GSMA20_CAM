

unsigned long pv_gsm = 0; 
long intval_gsm = 1000;
unsigned long currentgsm;
void init_gsm()
{
  currentgsm = millis();
  if (currentgsm - pv_gsm >= intval_gsm) 
  {
      swSer.println("AT");
      pv_gsm = currentgsm;
      Serial.println("init");
  }
  while (swSer.available() > 0) 
  {
    String input = swSer.readStringUntil('\r');
    if(input.indexOf("OK")!=-1)
    {
      state = CLOSE_ECHO;
      return;
    }
  }
}

void close_echo()
{
  currentgsm = millis();
  if (currentgsm - pv_gsm >= intval_gsm) 
  {
      swSer.println("ATE0");
      pv_gsm = currentgsm;
      Serial.println("Close Echo");
  }
  
  while (swSer.available() > 0) 
  {
    String input = swSer.readStringUntil('\r');
    if(input.indexOf("OK")!=-1)
    {
      state = START_CAM;
      return;
    }
  }
}

void startcam()
{
  intval_gsm=3000;
  currentgsm = millis();
  if (currentgsm - pv_gsm >= intval_gsm) 
  {
      swSer.println("AT+CAMSTART=1");
      pv_gsm = currentgsm;
      Serial.println("Start");
  }
  
  while (swSer.available() > 0) 
  {
    String input = swSer.readStringUntil('\r');
    if(input.indexOf("OK")!=-1)
    {
      state = CAPTURE;
      intval_gsm=1000;
      return;
    }
    if(input.indexOf("+CME ERROR:50")!=-1)
    {
      state = CAPTURE;
      intval_gsm=1000;
      return;
    }
  }
}
void capture()
{
  intval_gsm=3000;
  currentgsm = millis();
  if (currentgsm - pv_gsm >= intval_gsm) 
  {
      swSer.println("AT+CAMCAP");
      pv_gsm = currentgsm;
      Serial.println("Capture");
  }
  //+CAMCAP:22039
  while (swSer.available() > 0) 
  {
    String input = swSer.readStringUntil('\r');
    Serial.println(input);
    if(input.indexOf("OK")!=-1)
    {
      state = WAIT;
      intval_gsm=1000;
      return;
    }
    
    if(input.indexOf("+CAMCAP:")!=-1)
    {
      unsigned int len = input.indexOf(":");
      len = input.substring(len+1).toInt();
      Serial.println(len);
      state = WAIT;
      intval_gsm=1000;
      return;
    }
    
  }
}
void wait()
{
  while (swSer.available() > 0) {
    Serial.write(swSer.read());
  }
  while (Serial.available() > 0) {
    swSer.write(Serial.read());
  }
}



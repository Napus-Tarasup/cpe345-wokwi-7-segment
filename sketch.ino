//            0   1  2   3  4   5  6
//            a   b  c   d  e   f  g
int pin[] = {23, 22, 5, 15, 2, 21, 4};

//               0   1
int digits[] = {19, 18};

// button     0   1   2   3
int BTN[] = {34, 12, 13, 14};
int swt0, swt1, swt2, swt3;
int runcountup = 1;

// set number
int valueAnalog = 0;
int mapValueAnalog;

// segment
int a,b,c,d,e,f,g;
int count = 0;
int state = 0;
int endCount = 0;
int stopCount = 0;

/* 
   0babcdefg
   0b0000001 - 0
   0b1001111 - 1
   0b0010010 - 2
   0b0000110 - 3
   0b1001100 - 4
   0b0100100 - 5
   0b0100000 - 6
   0b0001111 - 7
   0b0000000 - 8
   0b0000100 - 9
*/

void runSegment(int a, int b, int c, int d, int e, int f, int g){

  digitalWrite(pin[0], a);
  digitalWrite(pin[1], b);
  digitalWrite(pin[2], c);
  digitalWrite(pin[3], d);
  digitalWrite(pin[4], e);
  digitalWrite(pin[5], f);
  digitalWrite(pin[6], g);

}

int runNumber(int count){

  if(count == 0)
    return a=0,b=0,c=0,d=0,e=0,f=0,g=1;
  else if(count == 1)
    return a=1,b=0,c=0,d=1,e=1,f=1,g=1;
  else if(count == 2)
    return a=0,b=0,c=1,d=0,e=0,f=1,g=0;
  else if(count == 3)
    return a=0,b=0,c=0,d=0,e=1,f=1,g=0;
  else if(count == 4)
    return a=1,b=0,c=0,d=1,e=1,f=0,g=0;
  else if(count == 5)
    return a=0,b=1,c=0,d=0,e=1,f=0,g=0;
  else if(count == 6)
    return a=0,b=1,c=0,d=0,e=0,f=0,g=0;
  else if(count == 7)
    return a=0,b=0,c=0,d=1,e=1,f=1,g=1;
  else if(count == 8)
    return a=0,b=0,c=0,d=0,e=0,f=0,g=0;
  else if(count == 9)
    return a=0,b=0,c=0,d=0,e=1,f=0,g=0;

}

void setup() {

  Serial.begin(115200);
  Serial.println("Hello, 7 segment 2 digits");

  // segment pin
  for(int i=0; i<7; i++)
  {
    pinMode(pin[i], OUTPUT);
  }

  // segment digits
  for(int i=0; i<2; i++)
  {
    pinMode(digits[i], OUTPUT);
  }

  // button
  for(int i=0; i<4; i++){
    pinMode(BTN[i], INPUT);
  }

}

void loop() {

  swt0 = digitalRead(BTN[0]);
  swt1 = digitalRead(BTN[1]);
  swt2 = digitalRead(BTN[2]);
  swt3 = digitalRead(BTN[3]);

  // set number button
  if(swt3 == 0)
  {
    endCount = mapValueAnalog;
    Serial.println("Set number of count up : " + String(endCount));
  }
  else if(swt3 == 1)
  {
    if(endCount == 0)
    {
      valueAnalog = analogRead(36);
      mapValueAnalog = map(valueAnalog, 0, 4095, 0, 99);
      Serial.println("Number of count up : " + String(mapValueAnalog));
    }
  }

  // clear number set button 
  if(swt2 == 0)
  {
    count = 0;
    state = 0;
    endCount = 0;
    stopCount = 0;
    runcountup = 1;
    Serial.println("Clear number set count up");
  }

  // stop count up number button
  if(swt1 == 0)
  {
    runcountup = 1;
    Serial.println("Count up, Stop!");
  }

  // start count up number button
  if(swt0 == 0)
  {
    runcountup = 0;
    Serial.println("Count up, Start!");
  }

  // counter
  if(runcountup == 0)
  {

    if(endCount == 0)
    {
      runcountup = 1;
      Serial.println("Please, Set your 'Endnumber [00-99]'");
    }
    else
    {
      if(endCount != stopCount-1)
    {
      if(count == 10)
        {
          state++;
          count = 0;
        }

        digitalWrite(digits[0], 1);
        digitalWrite(digits[1], 1);
        a,b,c,d,e,f,g = runNumber(state);
        runSegment(a, b, c, d, e, f, g);
        delay(80);
        digitalWrite(digits[0], 1);
        digitalWrite(digits[1], 0);

        delay(400);
        digitalWrite(digits[0], 0);
        digitalWrite(digits[1], 1);
        a,b,c,d,e,f,g = runNumber(count);
        runSegment(a, b, c, d, e, f, g);

        Serial.println("Number : " + String(state) + String(count));

        count++;
        stopCount++;

        delay(600);
    }
    } 
  }

  if(runcountup == 1)
  delay(500);

}

/*
  if(count == 10)
  {
    if(state != 9)
    {
      state++;
    }  
    count = 0;
  }

  digitalWrite(digits[0], 1);
  digitalWrite(digits[1], 1);
  a,b,c,d,e,f,g = runNumber(state);
  runSegment(a, b, c, d, e, f, g);
  delay(80);
  digitalWrite(digits[0], 1);
  digitalWrite(digits[1], 0);

  delay(400);
  digitalWrite(digits[0], 0);
  digitalWrite(digits[1], 1);
  a,b,c,d,e,f,g = runNumber(count);
  runSegment(a, b, c, d, e, f, g);

  Serial.println("Number : " + String(state) + String(count));

  count++;

  delay(600);
*/

  //digitalWrite(digits[0], 1);
  //digitalWrite(digits[1], 1);

  //int d1 = count%10;
  //int d2 = count/10;

/*
  a,b,c,d,e,f,g = runNumber(count);
  runSegment(a, b, c, d, e, f, g);

  if(count == 10)
    count = 0;
  
  count++;
*/

/*
  valueAnalog = analogRead(36);
  mapValueAnalog = map(valueAnalog, 0, 4095, 0, 99);
  Serial.println("Number of count up : " + String(mapValueAnalog));
*/

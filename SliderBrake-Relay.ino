String inputString = "";
int cmd = 0;
bool stringComplete = false;
bool commandComplete = false;
#define brake1 2
#define brake2 3
#define brake3 4
#define brake4 5



void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(57600);
  inputString.reserve(200);
  pinMode(brake1, OUTPUT); //Slider Brake 1
  pinMode(brake2, OUTPUT); //Slider Brake 2
  pinMode(brake3, OUTPUT); //Slider Brake 3
  pinMode(brake4, OUTPUT); //Slider Brake 4

  digitalWrite(brake1, LOW);
  digitalWrite(brake2, LOW);
  digitalWrite(brake3, LOW);
  digitalWrite(brake4, LOW);
  Serial.println("Arduino Nano Setup OK");
  
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if (stringComplete)
  {
    switch(cmd){
      // Brake Open command: brake1open, brake2open, brake3open, brake4open
      case 0:   //(0:0) //first digit as brake no. starting from 0, to 3; second digit as on/off, 0 as open, 1 as off.
        digitalWrite(brake1, HIGH); //Toggle the output status of brake1
        break;
      case 1:   //(1:0)
        digitalWrite(brake2, HIGH);
        break;
      case 2:   //(2:0)
        digitalWrite(brake3, HIGH);
        break;
      case 3:   //(3:0)
        digitalWrite(brake4, HIGH);
        break;
      //Brake Close command: brake1close, brake2close, brake3close, brake4close, brakeall
      case 10:   //(0:1)
        digitalWrite(brake1, LOW);
        commandComplete = checkStatus(brake1);
        break;
      case 11:   //(1:1)
        digitalWrite(brake2, LOW);
        commandComplete = checkStatus(brake2);
        break;
      case 12:   //(2:1)
        digitalWrite(brake3, LOW);
        commandComplete = checkStatus(brake3);
        break;
      case 13:   //(3:1)
        digitalWrite(brake4, LOW);
        commandComplete = checkStatus(brake4);
        break;
      case 14:   //(4:1) // first digit 4, implies all 4 brakes
        digitalWrite(brake1, LOW);
        digitalWrite(brake2, LOW);
        digitalWrite(brake3, LOW);
        digitalWrite(brake4, LOW);
        if(checkStatus(brake1) && checkStatus(brake2) && checkStatus(brake3) && checkStatus(brake4))
        {
          commandComplete = true;
        }
        break;
      default:
        Serial.print("Invalid input: ");
        Serial.println(inputString);
        break;
    }
/* //    Brake Open command: brake1open, brake2open, brake3open, brake4open
    if(inputString == "brake0o")
    {
      digitalWrite(brake1, HIGH); //Toggle the output status of brake1
    }
    if(inputString == "brake1o")
    {
      digitalWrite(brake2, HIGH);
    }
    if(inputString == "brake2o")
    {
      digitalWrite(brake3, HIGH);
    }
    if(inputString == "brake3o")
    {
      digitalWrite(brake4, HIGH);
    }

    //Brake Close command: brake1close, brake2close, brake3close, brake4close, brakeall
    if(inputString == "brake0c")
    {
      digitalWrite(brake1, LOW);
      commandComplete = checkStatus(brake1);
    }
    if(inputString == "brake1c")
    {
      digitalWrite(brake2, LOW);
      commandComplete = checkStatus(brake2);
    }
    if(inputString == "brake2c")
    {
      digitalWrite(brake3, LOW);
      commandComplete = checkStatus(brake3);
    }
    if(inputString == "brake3c")
    {
      digitalWrite(brake4, LOW);
      commandComplete = checkStatus(brake4);
    }
    if(inputString == "brake4c") //Set LOW in all brake to close all the slider brake
    {
      digitalWrite(brake1, LOW);
      digitalWrite(brake2, LOW);
      digitalWrite(brake3, LOW);
      digitalWrite(brake4, LOW);
      if(checkStatus(brake1) && checkStatus(brake2) && checkStatus(brake3) && checkStatus(brake4))
      {
        commandComplete = true;
      }
    }*/

    inputString = "";
    stringComplete = false;
  }
  else
  {
    commandComplete = false;
    stringComplete = false;
  }
}

void serialEvent()
{
  while(Serial.available())
  {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == ')')
    {
      stringComplete = true;
      Serial.println(inputString);
      break;
    }
  }
  inputString.trim();
  int idx = inputString.indexOf(':');
  if(idx == -1) { cmd = 50; return; }
  String b = inputString.substring(idx-1,idx); // brake no.
  String s = inputString.substring(idx+1); // state: open or close
  cmd = b.toInt() + s.toInt()*10;
}

bool checkStatus(int pin)
{
  while(true)
  {
   if(!digitalRead(pin))
   {
    Serial.println("Close brake command completed");
    break;
   }
  }
 return digitalRead(pin);
 
}

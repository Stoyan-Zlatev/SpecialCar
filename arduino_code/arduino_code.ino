// initializes state variables
bool started = false;
bool leftWinker = false;
bool rightWinker = false;
bool emergencyLight = false;
int winkerDelayCounter = 0;
int specialLightsCounter  = 0;
bool stops = false;
bool specialLights = false;

// sets the pins' № to constants
const int motor1Pin1 = 5; 
const int motor1Pin2 = 6; 
const int motor2Pin1 = 11; 
const int motor2Pin2 = 3;
const int switchPin = A0;
const int leftWinkerPin= 12;
const int headLightsPin = 2;
const int backLightsPin = 8;
const int rightWinkerPin= 13;
const int specialLights1Pin = 4;
const int specialLights2Pin = 7;

void setup() 
{
    // sets the pins as outputs:
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(leftWinkerPin, OUTPUT);
    pinMode(headLightsPin, OUTPUT);
    pinMode(backLightsPin, OUTPUT);
    pinMode(rightWinkerPin, OUTPUT);
    pinMode(specialLights1Pin, OUTPUT);
    pinMode(specialLights2Pin, OUTPUT);

    // sets the pin as input:
    pinMode(switchPin, INPUT);

    // starts serial comminication with baudrate at 9600 bps
    Serial.begin(9600);
}


void loop() 
{
  // initialize local state and read analog data if the car is powered on
  int state = 0;
  int startedLocal = digitalRead(switchPin);

  // if the car is powered but not started -> start it
  if(startedLocal == 1 && !started)
  {
    digitalWrite(headLightsPin, HIGH);
    started = true;
  }

  if(started)
  {
    // handle winkers and special lights
    Winker();
    SpecialLights();
    
    // if some date is sent, reads it and saves in state
    if(Serial.available() > 0)
    {     
      state = Serial.read();  
      Serial.println(state);
      
      // Forward
      if (state == 'F') 
      {
          digitalWrite(motor1Pin1, HIGH);
          digitalWrite(motor1Pin2, LOW); 
          digitalWrite(motor2Pin1, LOW);
          digitalWrite(motor2Pin2, HIGH);
          Serial.println("FORWARD");
          stops = false;
      }
      
      // Backward
      else if (state == 'B') 
      {
          digitalWrite(backLightsPin, HIGH);
          digitalWrite(motor1Pin1, LOW); 
          digitalWrite(motor1Pin2, HIGH);
          digitalWrite(motor2Pin1, HIGH);
          digitalWrite(motor2Pin2, LOW);
          Serial.println("BACKWARD");
          stops = true;
      }
      
      // Stop
      else if (state == 'S') 
      {
          digitalWrite(motor1Pin1, LOW); 
          digitalWrite(motor1Pin2, LOW); 
          digitalWrite(motor2Pin1, LOW);
          digitalWrite(motor2Pin2, LOW);
          Serial.println("STOP");
          stops = true;
      }
      
      // Right
      else if (state == 'R') 
      {
          digitalWrite(motor1Pin1, HIGH); 
          digitalWrite(motor1Pin2, LOW); 
          digitalWrite(motor2Pin1, LOW);
          digitalWrite(motor2Pin2, LOW);
          Serial.println("RIGHT");
          stops = false;
      }
      
      // Left
      else if (state == 'L') 
      {
          digitalWrite(motor1Pin1, LOW); 
          digitalWrite(motor1Pin2, LOW); 
          digitalWrite(motor2Pin1, LOW);
          digitalWrite(motor2Pin2, HIGH);
          Serial.println("LEFT");
          stops = false;
      }
      
      // Forward - Left
      else if (state == 'A')
      {
          analogWrite(motor1Pin1, 100); 
          digitalWrite(motor1Pin2, LOW); 
          digitalWrite(motor2Pin1, LOW);
          analogWrite(motor2Pin2, 255);
          Serial.println("FRONT LEFT");
          stops = false;
      }

      //Forward - Right
      else if (state == 'D')
      {
          analogWrite(motor1Pin1, 255); 
          digitalWrite(motor1Pin2, LOW); 
          digitalWrite(motor2Pin1, LOW);
          analogWrite(motor2Pin2, 100);
          Serial.println("FRONT RIGHT");
          stops = false; 
      }

      //Backward - Left
      else if (state == 'Z')
      {
          digitalWrite(motor1Pin1, LOW); 
          analogWrite(motor1Pin2, 100); 
          analogWrite(motor2Pin1, 255);
          digitalWrite(motor2Pin2, LOW);
          Serial.println("BACK LEFT");
          stops = true;
      }

      //Backward - Right 
      else if (state == 'C')
      {
          digitalWrite(motor1Pin1, LOW); 
          analogWrite(motor1Pin2, 255); 
          analogWrite(motor2Pin1, 100);
          digitalWrite(motor2Pin2, LOW);
          Serial.println("BACK RIGHT");
          stops = true;
      }
      
      //Left Winker
      else if(state == 'Q')
      {
          rightWinker = false;
          leftWinker=!leftWinker;
          Serial.println("LEFT WINKER");
      }
      
      //Rght Winker
      else if(state == 'E')
      {
          leftWinker = false;
          rightWinker=!rightWinker;
          Serial.println("RIGHT WINKER");
      }

      //Emergency Lights
      else if(state == 'W')
      {
          emergencyLight = !emergencyLight;
          leftWinker = rightWinker = false;
          Serial.println("EMERGENCY LIGHTS");
      }

      //Special Lights
       else if(state == 'X')
      {
          specialLights=!specialLights;
          Serial.println("SPECIAL LIGHTS");
      }
    }
            
    if(stops)
    {
      digitalWrite(backLightsPin, HIGH);
    }
    else
    {
      digitalWrite(backLightsPin, LOW);
    }
  }

  // if car is started but powered off -> shut it down
  if(startedLocal == 0 && started)
  {
     TurnOff();
  }
}

void TurnOff()
{
    started = false;
    digitalWrite(motor1Pin1, LOW); 
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    digitalWrite(leftWinkerPin, LOW);
    digitalWrite(headLightsPin, LOW);
    digitalWrite(backLightsPin, LOW);
    digitalWrite(rightWinkerPin, LOW);
    digitalWrite(specialLights1Pin, LOW);
    digitalWrite(specialLights2Pin, LOW);
    emergencyLight = leftWinker = rightWinker = false;
    Serial.println("STOP");
}

void Winker()
{
  if(leftWinker || rightWinker || emergencyLight)
    {
        if(winkerDelayCounter == 0)
        {
          if(emergencyLight)
          {
            digitalWrite(leftWinkerPin, HIGH);
            digitalWrite(rightWinkerPin, HIGH); 
          }
          else
          {
            if(leftWinker)
            {
              digitalWrite(leftWinkerPin, HIGH);
              digitalWrite(rightWinkerPin, LOW);
            }
            else
            {
              digitalWrite(leftWinkerPin, LOW);
              digitalWrite(rightWinkerPin, HIGH); 
            }
          }
        }
        
         winkerDelayCounter++;
         delay(10);
        
        if(winkerDelayCounter == 30)
        {
            digitalWrite(leftWinkerPin, LOW);
            digitalWrite(rightWinkerPin, LOW); 
        }
        else if(winkerDelayCounter == 60)
        {
            winkerDelayCounter=0;
        }
    }
    else 
    {
        winkerDelayCounter = 0;  
        digitalWrite(leftWinkerPin,LOW);
        digitalWrite(rightWinkerPin,LOW);
    }
}

void SpecialLights()
{
  if(specialLights)
    {
        if(specialLightsCounter == 0)
        {
            digitalWrite(specialLights1Pin, HIGH);
            digitalWrite(specialLights2Pin, LOW);
        }
      
         specialLightsCounter ++;
         delay(10);
        
        if(specialLightsCounter == 20)
        {
            digitalWrite(specialLights1Pin, LOW);
            digitalWrite(specialLights2Pin, HIGH);
        }
        else if(specialLightsCounter == 40)
        {
            specialLightsCounter = 0;
        }
    }
    else 
    {
        specialLightsCounter  = 0;  
        digitalWrite(specialLights1Pin, LOW);
        digitalWrite(specialLights2Pin, LOW);
    }
}

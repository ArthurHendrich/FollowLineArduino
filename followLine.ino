//Follow line Arduin program
//We used 4 sensors to work our robot

//Control Pin
#define M1A 8 // Speed engine number1 (0 to 255) ATV_A port H bridge
#define M1B 9 // Speed engine number2 (0 to 255) ATV_B port H bridge
#define M2A 10 //Pin_Direction of 1º Engine: Forward / Back (HIGH or LOW) IN1 port H bridge
#define M2B 11 //Pin_Direction of 2º Engine: Forward / Back (HIGH or LOW) IN3 port H bridge

//Pin sensors definition
#define pin_S1 5
#define pin_S2 6
#define pin_S3 4
#define pin_S4 3
#define SENSORTRASHHOLD 700
int Sensor1 = 0;
int Sensor2 = 0;
int Sensor3 = 0;
int Sensor4 = 0;

//Speed Control
int speed_engine1 = 200;
int speed_engine2 = 200;
int velocidadei = 40; 
void Forward(void){
  analogWrite(M1A, HIGH); // Both engine starts at the same time
  analogWrite(M2A, HIGH);
  digitalWrite(M1B, LOW);
  digitalWrite(M2B, LOW);
}
void Right(void){ //2A Right
  analogWrite(M1A, speed_engine1); // Both engines starts at the same speed
  analogWrite(M2A, LOW);
  digitalWrite(M1B, LOW);
  analogWrite(M2B, velocidadei);
}

void Left(void){ //1A Left
  analogWrite(M1A, LOW); // Both engines starts at the same speed
  analogWrite(M2A, speed_engine2);
  analogWrite(M1B, velocidadei);
  digitalWrite(M2B, LOW);
}

void Stop(void){
  analogWrite(M1A, LOW); // Both engines starts at the same speed
  analogWrite(M2A, LOW);
  digitalWrite(M1B, LOW);
  digitalWrite(M2B, LOW);
}

//Here is where all happend

void setup(){
  Serial.begin(9600);
  //Output pins
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  //Both engines go forward
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, LOW);

  //Input pins
  pinMode(pin_S1, INPUT);
  pinMode(pin_S2, INPUT);
  pinMode(pin_S3, INPUT);
  pinMode(pin_S4, INPUT);
}
void loop(){
  //Here we put the value of the sensors(0 or 1)
  Sensor1 = digitalRead(pin_S1);
  Sensor2 = digitalRead(pin_S2);
  Sensor3 = digitalRead(pin_S3);
  Sensor4 = digitalRead(pin_S4);
  Serial.print("Sensor_1 => ");
  Serial.println(Sensor1);
  Serial.print("Sensor_2 => ");
  Serial.println(Sensor2);
  Serial.print("Sensor_3 => ");
  Serial.println(Sensor3);
  Serial.print("Sensor_4 => ");
  Serial.println(Sensor4);
  delay(5); //Its good to change if you think


  //White color: 0 and Black color: 1. 


    //Forward
    if(((Sensor1 == 1) && (Sensor2 == 1)) && ((Sensor3 == 1) && (Sensor4 == 1))) // Se detectar na extremidade das faixas duas cores brancas
    { 
     Forward();
    }


    //Sides
      if(((Sensor1 == 0)) && ((Sensor2 == 1) or (Sensor3 == 1)))
      {
        Forward();
        if((Sensor1 == 0) && (Sensor3 == 1))
        {
          speed_engine2 == speed_engine2 + 20;
          speed_engine1 == speed_engine1 + 55;
          Right();
        }else if((Sensor2 == 0) &&(Sensor2 == 1) or (Sensor3 == 1))
        {
          speed_engine1 == speed_engine1 + 20;
          speed_engine2 == speed_engine2 + 55;
          Left();
        }
      }

      if(((Sensor1 == 1)) && ((Sensor2 == 0) or (Sensor3 == 0)))
      {
        Forward();
        if((Sensor1 == 1) && (Sensor3 ==0))
        {
          speed_engine2 == speed_engine2 + 20;
          speed_engine1 == speed_engine1 + 55;
          Right();
        }else if((Sensor1 == 1) && (Sensor2 == 0))
        {
          speed_engine1 == speed_engine1 + 20;
          speed_engine2 == speed_engine2 + 55;
          Left();
        }
      }

    //Stop safety
    
    if(((Sensor1 == 0) && (Sensor2 == 0) && (Sensor3 == 0) && (Sensor4 == 0))){
      Stop();
    }
}

/****************************************************************************** 
SparkFun Spectrum Shield Demo
Toni Klopfenstein @ SparkFun Electronics
December 2015
https://github.com/sparkfun/Spectrum_Shield

This sketch shows the basic functionality of the Spectrum Shield, working with a basic RGB LED Matrix.

The Spectrum Shield code is based off of the original demo sketch by Ben Moyes @Bliptronics.  
This sketch is available in the Spectrum Shield repository. 

Development environment specifics:
Developed in Arduino 1.6.

This code is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!
Distributed as-is; no warranty is given.
*********************************************************************************/

//Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1 


//Define LED connections on the Arduino/Shield
int LED[] = {1,2,3,4,5,6,7};

//Define spectrum variables
int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7]; 
int i;

/*int motor1 = 11;
int motor2 = 10;
int motor3 = 9;
*/

int Motor[] = {9,10,11,12,13};



/********************Setup Loop*************************/
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  //Set LED pin configurations
  for(i=0; i<6; i++)
  {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], LOW);
  }


/* analogWrite(motor1, 127);
 delay(1000);
 analogWrite(motor1, 0);  
 
 analogWrite(motor2, 127);
 delay(1000);
 analogWrite(motor2, 0);
 
 analogWrite(motor3, 127);
 delay(1000);
 analogWrite(motor3, 0);
 */
  
  //Set spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);  
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);
  
  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);
}


/**************************Main Function Loop*****************************/
void loop() {
  
  Read_Frequencies();
  Graph_Frequencies();
  delay(50);
 
}


/*******************Pull frquencies from Spectrum Shield********************/
void Read_Frequencies(){
  //Read frequencies for each band
  for (freq_amp = 0; freq_amp<6; freq_amp++)
  {
    Frequencies_One[freq_amp] = analogRead(DC_One);
    Frequencies_Two[freq_amp] = analogRead(DC_Two); 
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
}

/*******************Light LEDs based on frequencies*****************************/
void Graph_Frequencies(){
   for( i= 0; i<6; i++){
    if( Frequencies_Two[i]< 1){
  Frequencies_Two[i] = 0;
        analogWrite(LED[i], 0);
        analogWrite(Motor[i], 0);
    }
    else{
        analogWrite(LED[i], Frequencies_One[i]/4);
         analogWrite(Motor[i], Frequencies_One[i]/4);

  Serial.print("Frequencies_One  ");
  Serial.print(i);
   Serial.print(": ");
  Serial.println(Frequencies_One[i]/4);
     
         }





     
   }
}

#define RPWM_PIN 9 
#define LPWM_PIN 10 
#define EN_PIN 7 
 
int motorSpeed = 0; 
 
void setup() { 
  pinMode(RPWM_PIN, OUTPUT); 
  pinMode(LPWM_PIN, OUTPUT); 
  pinMode(EN_PIN, OUTPUT); 
   
  digitalWrite(EN_PIN, HIGH);  // Enable ON 
   
  Serial.begin(9600); 
  Serial.println("=== BTS7960 Speed Control Ready (No Timeout Issue) ==="); 
  Serial.println("Speed daalo (Enter ke saath):"); 
  Serial.println("  0     → Stop"); 
  Serial.println("  1-255 → Forward"); 
  Serial.println(" -1--255→ Reverse (negative daalo)"); 
  Serial.println("Line ending: Newline ya Both NL&CR set kar sakte ho – ab issue nahi 
aayega!"); 
   
  analogWrite(RPWM_PIN, 0); 
  analogWrite(LPWM_PIN, 0); 
} 
 
void loop() { 
  if (Serial.available() > 0) { 
    String inputStr = Serial.readStringUntil('\n');  // Newline tak padho (ya '\r' agar chahiye) 
    inputStr.trim();  // Extra spaces remove kar do 
     
    if (inputStr.length() > 0) {  // Agar kuch padha 
      int newSpeed = inputStr.toInt();  // String ko int mein convert 
       
      if (newSpeed >= -255 && newSpeed <= 255) { 
        motorSpeed = newSpeed; 
         
        if (motorSpeed > 0) { 
          analogWrite(RPWM_PIN, motorSpeed); 
          analogWrite(LPWM_PIN, 0); 
          Serial.print("→ Forward | Speed: "); 
          Serial.println(motorSpeed); 
        } else if (motorSpeed < 0) { 
          analogWrite(RPWM_PIN, 0); 

          analogWrite(LPWM_PIN, -motorSpeed); 
          Serial.print("← Reverse | Speed: "); 
          Serial.println(-motorSpeed); 
        } else { 
          analogWrite(RPWM_PIN, 0); 
          analogWrite(LPWM_PIN, 0); 
          Serial.println("■ Stopped"); 
        } 
      } else { 
        Serial.println("Galat input! -255 se 255 tak daalo."); 
      } 
    } 
  } 
}
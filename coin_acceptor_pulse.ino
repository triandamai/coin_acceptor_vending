/*/
 * 
 * 
 * Trian Damai
 * 
 *
/*/
#include <Servo.h>
#include <LiquidCrystal.h>

/*Inisisasi Servo
*/
Servo servo1; //servo1.attach(31);
Servo servo2; //servo2.attach(35);
Servo servo3; //servo3.attach(33);
Servo servo4; //servo4.attach(37);
Servo servo5; //servo5.attach(39);
Servo servo6; //servo6.attach(41);
/* Inisiasi LCD
  lcd4 = 53 lcd6 = 51  lcd11 = 49 lcd12 = 47  lcd13 = 45 lcd14 = 43
*/
LiquidCrystal lcd(53,51,49,47,45,43);

int i = 0;

int j = 0;

int k = 0;

int delayTime2 = 350; // Delay between shifts

/*
* pin pushButton
*/
int btn1 = 48;
int btn2 = 50;
int btn3 = 52;

int btn4 = 46;
int btn5 = 44;
int btn6 = 42; 
/*
* pin buzzer
*/
const int pinBuzzer = 8;

/*
* Coin Acceptor
*/
volatile int pulse = 0;
int pinCoin = 2;

/*
* Variabel
*/
int uangAwal = 0;
int stok1 = 2;
int stok2 = 2;
int stok3 = 2;
int stok4 = 2;
int stok5 = 2;
int stok6 = 2;
boolean sudahMasukkanKoin = false;

/*
* deteksi koin
*/
void coin_value() {
  pulse = pulse + 1;
  sudahMasukkanKoin = true;
}

void setup() {
    Serial.begin(9600);
    delay(500);
    Serial.println("Ready..");
    pinMode(pinCoin, INPUT);
    pinMode(pinBuzzer, OUTPUT);
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("Welcome :)");
    lcd.setCursor(0,1);
    lcd.print("Masukkan koin..");
    
    Serial.print("Menunggu Koin : Rp ");
    Serial.println(uangAwal);
    
    /*mendeteksi coin*/    
    attachInterrupt(0, coin_value, FALLING);

    /*pushButton*/
    pinMode(btn1,INPUT);
    pinMode(btn2,INPUT);
    pinMode(btn3,INPUT);
    pinMode(btn4,INPUT);
    pinMode(btn5,INPUT);
    pinMode(btn6,INPUT);
    
    digitalWrite(btn1, HIGH);
    digitalWrite(btn2, HIGH);
    digitalWrite(btn3, HIGH);
    digitalWrite(btn4, HIGH);
    digitalWrite(btn5, HIGH);
    digitalWrite(btn6, HIGH);
}

void loop() {
  lcd.clear();
  scrollInFromRight(0, ((char *)"Menggunakan Uang Pas"));
  scrollInFromRight(1, ((char *)"Menggunakan uang koin Rp 1000 dan Rp 500 silver"));
  lcd.clear();
  //detect coin
  if (pulse > 0)
    {
    delay (600);   // sambil nunggu koin lain
    if (pulse == 3) {
      Serial.print("Koin Tidak di setujui");
    }
    if (pulse == 2) {
      uangAwal = uangAwal + 1000;
      
      Serial.print("saldo : Rp ");
      Serial.println(uangAwal);
    }
    if (pulse == 1) {
      uangAwal = uangAwal + 500;
      
      Serial.print("Uang : Rp ");
      Serial.println(uangAwal);
      
    }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Uang kamu..");
      lcd.setCursor(0,1);
      lcd.print("Rp");
      lcd.print(uangAwal);
      delay(250);
      pulse = 0;  // pulse jadi 0 hehe
  }

  //cek stok
  if(stok1 <= 0 ){
    kontrolBuzzer(true);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Oops..");
    lcd.setCursor(0,1);
    lcd.print("Stok 1 habis..!!");
  }else if(stok2 <= 0){
    kontrolBuzzer(true);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Oops..");
    lcd.setCursor(0,1);
    lcd.print("Stok 2 habis..!!");
  }else if(stok3 <= 0){
    kontrolBuzzer(true);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Oops..");
    lcd.setCursor(0,1);
    lcd.print("Stok 3 habis..!!");
  }else if(stok4 <= 0){
    kontrolBuzzer(true);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Oops..");
    lcd.setCursor(0,1);
    lcd.print("Stok 4 habis..!!");
  }else if(stok5 <= 0){
    kontrolBuzzer(true);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Oops..");
    lcd.setCursor(0,1);
    lcd.print("Stok 5 habis..!!");
  }else if(stok6 <= 0){
    kontrolBuzzer(true);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Oops..");
    lcd.setCursor(0,1);
    lcd.print("Stok 6 habis..!!");
  }
   //pushButton di klik
   if (digitalRead(btn1) == LOW) {
     Serial.println("btn low 1");
     if(stok1 > 0 ){
       if(sudahMasukkanKoin == true){
          if(uangAwal > 1999){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Silahkan..");
            lcd.setCursor(0,1);
            lcd.print("Rp 2000");
            Serial.print("Servo 1 Rp ");
            Serial.println(uangAwal);
            putarServo(1);
            uangAwal = uangAwal - 2000;
            stok1 = stok1 -1;
              if(uangAwal > 0){
                delay(500);
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("uangAwal Anda");
                lcd.setCursor(0,1);
                lcd.print(uangAwal);
                sudahMasukkanKoin = true;
              }else{
                //reset semua
                lcd.setCursor(0,0);
                lcd.print("Welcome :)");
                lcd.setCursor(0,1);
                lcd.print("Masukkan koin..");
                delay(500);
                sudahMasukkanKoin = false;
              }
          }else{
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Ooops...");
            lcd.setCursor(0,1);
            lcd.print("Koin Kurang..");
            Serial.print("uangAwal Tidak Cukup :");
            Serial.println(uangAwal);

            delay(500);
          }
        }else{
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Kamu Tidak..");
          lcd.setCursor(0,1);
          lcd.print("Masukkan koin");
          Serial.print("Masukkan Koin");
          Serial.println(uangAwal);
        
         delay(500);
        }    
     }else{
     
     }
    delay(250);         
   }else if(digitalRead(btn2) == LOW){
    Serial.println("low 2");
     if(stok2 > 0 ){
       if(sudahMasukkanKoin == true){
        if(uangAwal > 2999){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Silahkan..");
        lcd.setCursor(0,1);
        lcd.print("Rp 3000");
        Serial.print("Servo 2 Rp ");
        Serial.println(uangAwal);
        putarServo(2);        
        uangAwal = uangAwal - 3000;
        stok2 = stok2 -1;
        
       if(uangAwal > 0){
          delay(500);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("uangAwal Anda");
          lcd.setCursor(0,1);
          lcd.print(uangAwal);
          sudahMasukkanKoin = true;
        }else{
          //reset semua
          lcd.setCursor(0,0);
          lcd.print("Welcome :)");
          lcd.setCursor(0,1);
          lcd.print("Masukkan koin..");
          delay(500);
          sudahMasukkanKoin = false;
        }
       
      }else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Ooops...");
        lcd.setCursor(0,1);
        lcd.print("Koin Kurang..");
        Serial.print("uangAwal Tidak Cukup :");
        Serial.println(uangAwal);

        delay(500);
      }
     }else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Kamu Tidak..");
        lcd.setCursor(0,1);
        lcd.print("Masukkan koin");
        Serial.print("Masukkan Koin");
        Serial.println(uangAwal);
       delay(500);
     }
     }else{
     }
      delay(250);
   }else if(digitalRead(btn3) == LOW){
    Serial.println("low 3");
     if(stok3 > 0 ){
       if(sudahMasukkanKoin == true){
         if(uangAwal > 3999){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Silahkan..");
            lcd.setCursor(0,1);
            lcd.print("Rp 4000");
            Serial.print("Servo 3 Rp ");
            Serial.println(uangAwal);
            putarServo(3);
            uangAwal = uangAwal - 4000;
            stok3 = stok3 -1;
              if(uangAwal > 0){
                delay(500);
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("uangAwal Anda");
                lcd.setCursor(0,1);
                lcd.print(uangAwal);
                sudahMasukkanKoin = true;
              }else{
                //reset semua
                lcd.setCursor(0,0);
                lcd.print("Welcome :)");
                lcd.setCursor(0,1);
                lcd.print("Masukkan koin..");
                delay(500);
                sudahMasukkanKoin = false;
              }
            }else{
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Ooops...");
              lcd.setCursor(0,1);
              lcd.print("Koin Kurang..");
              Serial.print("uangAwal Tidak Cukup :");
              Serial.println(uangAwal);

              delay(500);
            }
          }else{
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Kamu Tidak..");
            lcd.setCursor(0,1);
            lcd.print("Masukkan koin");
            Serial.print("Masukkan Koin");
            Serial.println(uangAwal);
            delay(500);
         }
      }else{
     
      }
     delay(250);     
   }else if(digitalRead(btn4) == LOW){
     Serial.println("low 4");
      if(stok4 > 0 ){
        if(sudahMasukkanKoin == true){
          if(uangAwal > 4999){
            Serial.print("Servo 4 Rp ");
            Serial.println(uangAwal);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Silahkan..");
            lcd.setCursor(0,1);
            lcd.print("Rp 5000");
            putarServo(4);      
            uangAwal = uangAwal - 5000;
            stok4 = stok4 -1;
              if(uangAwal > 0){
                delay(500);
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("uangAwal Anda");
                lcd.setCursor(0,1);
                lcd.print(uangAwal);
                sudahMasukkanKoin = true;
              }else{
                //reset semua
                lcd.setCursor(0,0);
                lcd.print("Welcome :)");
                lcd.setCursor(0,1);
                lcd.print("Masukkan koin..");
                delay(500);
                sudahMasukkanKoin = false;
              }
            }else{
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Ooops...");
              lcd.setCursor(0,1);
              lcd.print("Koin Kurang..");
              Serial.print("uangAwal Tidak Cukup :");
              Serial.println(uangAwal);

              delay(500);
            }
          }else{
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Kamu Tidak..");
            lcd.setCursor(0,1);
            lcd.print("Masukkan koin");
            Serial.print("Masukkan Koin");
            Serial.println(uangAwal);
            delay(500);
          }
        }else{
     
        }
      delay(250);
   }else if(digitalRead(btn5) == LOW){
      Serial.println("low 5");
      if(stok5 > 0 ){
        if(sudahMasukkanKoin == true){
          if(uangAwal > 5999){
            Serial.print("Servo 5 Rp ");
            Serial.println(uangAwal);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Silahkan..");
            lcd.setCursor(0,1);
            lcd.print("Rp 6000");
            putarServo(1);        
            uangAwal = uangAwal - 6000;
            stok5 = stok5 -1;
              if(uangAwal > 0){
                delay(500);
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("uangAwal Anda");
                lcd.setCursor(0,1);
                lcd.print(uangAwal);
                sudahMasukkanKoin = true;
              }else{
                //reset semua
                lcd.setCursor(0,0);
                lcd.print("Welcome :)");
                lcd.setCursor(0,1);
                lcd.print("Masukkan koin..");
                delay(500);
                sudahMasukkanKoin = false;
              }
            }else{
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Ooops...");
              lcd.setCursor(0,1);
              lcd.print("Koin Kurang..");
              Serial.print("uangAwal Tidak Cukup :");
              Serial.println(uangAwal);

              delay(500);
            }
          }else{
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Ooops...");
            lcd.setCursor(0,1);
            lcd.print("Koin Kurang..");
            Serial.print("uangAwal Tidak Cukup :");
            Serial.println(uangAwal);

            delay(500);
          }
        }else{
      
        }
      delay(250);
   }else if(digitalRead(btn6) == LOW){
      Serial.println("low 6");
        if(stok6 > 0){
          if(sudahMasukkanKoin == true){
            if(uangAwal > 6999){
              Serial.print("Servo 6 Rp ");
              Serial.println(uangAwal);
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Silahkan..");
              lcd.setCursor(0,1);
              lcd.print("Rp 7000");
              putarServo(6);   
              uangAwal = uangAwal - 7000;
              stok6 = stok6 -1;
               if(uangAwal > 0){
                delay(500);
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("uangAwal Anda");
                lcd.setCursor(0,1);
                lcd.print(uangAwal);
                sudahMasukkanKoin = true;
              }else{
                //reset semua
                lcd.setCursor(0,0);
                lcd.print("Welcome :)");
                lcd.setCursor(0,1);
                lcd.print("Masukkan koin..");
                delay(500);
                sudahMasukkanKoin = false;
              }
            }else{
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Ooops...");
              lcd.setCursor(0,1);
              lcd.print("Koin Kurang..");
              Serial.print("uangAwal Tidak Cukup :");
              Serial.println(uangAwal);

              delay(500);
            }
          }else{
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Kamu Tidak..");
            lcd.setCursor(0,1);
            lcd.print("Masukkan koin");
            Serial.print("Masukkan Koin");
            Serial.println(uangAwal);
            delay(500);
          }
        }else{
        
        }
      delay(250);
   }else if(digitalRead(btn1) == HIGH){
      //Serial.println("high 1");
      delay(250);
   }else if(digitalRead(btn2) == HIGH){
      Serial.println("high 2");
      delay(250);
   }else if(digitalRead(btn3) == HIGH){
      Serial.println("high 3");
      delay(250);
   }else if(digitalRead(btn4) == HIGH){
      Serial.println("high 4");
      delay(250);
   }else if(digitalRead(btn5) == HIGH){
      Serial.println("high 5");
      delay(250);
   }else if(digitalRead(btn6) == HIGH){
      Serial.println("high 6");
      delay(250);
   }else {
     lcd.print("inputan salah");
   }
}

void putarServo(int serv){
  if(serv == 1){
    servo1.attach(31);
    servo1.writeMicroseconds(100); 
    delay(1000);
    servo1.detach();
  }else if(serv == 2){
    servo2.attach(35);
    servo2.writeMicroseconds(100);
    delay(1000);
    servo2.detach();
  }else if(serv == 3){
    servo3.attach(33);
    servo3.writeMicroseconds(100);
    delay(1000);
    servo3.detach();
  }else if(serv == 4){
    servo4.attach(37);
    servo4.writeMicroseconds(100);
    delay(1000);
    servo4.detach();
  }else if(serv == 5){
    servo6.attach(39);
    servo5.writeMicroseconds(100);
    delay(1000);
    servo5.detach();
  }else if(serv == 6){
    servo6.attach(41);
    servo6.writeMicroseconds(100);
    delay(1000);
    servo6.detach();
  }else {
    
  }
}

void kontrolBuzzer(boolean nyala){
    if(nyala == true){
      tone(pinBuzzer, 1000); // Send 1KHz sound signal...
      delay(600); 
      noTone(pinBuzzer);     // Stop sound...
      delay(600);       
              
    }else{
      noTone(pinBuzzer);     // Stop sound...
      //delay(600);
    }
}

void scrollInFromLeft (int line, char str1[]) {
  // test
  i = 40 - strlen(str1);
  line = line - 1;
  for (j = i; j <= i + 16; j++) {
    for (k = 0; k <= 15; k++) {
      lcd.print(" "); // Clear line
    }
    lcd.setCursor(j, line);
    lcd.print(str1);
    delay(delayTime2);
  }
}

void scrollInFromRight (int line, char str1[]) {
  //
  i = strlen(str1);
    for (j = 16; j >= 0; j--) {
      lcd.setCursor(0, line);
      for (k = 0; k <= 15; k++) {
        lcd.print(" "); // Clear line
      }
      lcd.setCursor(j, line);
      lcd.print(str1);
      delay(delayTime2);
    }
}





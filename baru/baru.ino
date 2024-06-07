#include <DHT.h>
#include <LiquidCrystal_I2C.h> 

#define DHTPIN 2    // Pin data sensor DHT22 terhubung ke pin 2 Arduino
#define DHTTYPE DHT22   // Jenis sensor DHT yang digunakan (DHT22)
const int relay = 3;

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
String dataHp = "";
String data = "";
int sh = 1;

void setup() {
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  dht.begin();
  lcd.init();
  lcd.backlight();

  lcd.setCursor(3,0);
  lcd.print("KOTAK OBAT");
  lcd.setCursor(0,1);
  lcd.print("NADYA SALSABILA");
  delay(5000);
}

void loop() {
  // Baca kelembaban dari sensor
  // float kelembaban = dht.readHumidity();
  
  if(Serial.available() > 0){
    data = char(Serial.read());
  }
  // Baca suhu dari sensor
  float suhu = dht.readTemperature();
  int ac = digitalRead(relay);

  if (data == "0" && dataHp !="mati") {
    digitalWrite(relay, HIGH);
    Serial.println("AC DIMATIKAN");
    data = "";
    dataHp = "mati";
    delay(5000);
  }else if(data == "1" && dataHp !="nyala"){
    digitalWrite(relay, LOW);
    Serial.println("AC DINYALAKAN");
    data = "";
    dataHp = "nyala";
    delay(5000);
  }else if(ac == LOW && suhu > 22 && sh == 30){
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("SUHU : " + String(suhu));
      lcd.setCursor(1,1);
      lcd.print("ES MULAI HABIS");

      String temperatur = String("SUHU : ") + String(suhu) + String("°C ") + String(" ES MULAI HABIS");
      Serial.println(temperatur);
      delay(2000);
  }else{
    if(suhu <= 20 && suhu >=15) {
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("SUHU : " + String(suhu));
      lcd.setCursor(3,1);
      lcd.print("SUHU NORMAL");
      sh = 1;

      String temperatur = String("SUHU : ") + String(suhu) + String("°C ") + String(" SUHU NORMAL");
      Serial.println(temperatur);
      delay(2000);
    } else if (suhu > 20) {
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("SUHU : " + String(suhu));
      lcd.setCursor(2,1);
      lcd.print("DIATAS NORMAL");

      String temperatur = String("SUHU : ") + String(suhu) + String("°C  ") + String("DIATAS NORMAL");
      Serial.println(temperatur);

      if(sh <=29){
        sh = sh + 1;
      }  

      delay(2000);
    } else if (suhu < 15) {
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("SUHU : " + String(suhu));
      lcd.setCursor(1,1);
      lcd.print("DIBAWAH NORMAL");

      String temperatur = String("SUHU : ") + String(suhu) + String("°C  ") + String("DIBAWAH NORMAL");
      Serial.println(temperatur);
      delay(2000);
    }
  }
}

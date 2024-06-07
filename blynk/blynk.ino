#define BLYNK_TEMPLATE_ID   "TMPL6VGUw3t_Y"
#define BLYNK_TEMPLATE_NAME "Suhu Ruangan Obat"
#define BLYNK_AUTH_TOKEN    "HRZGdleMNZISMUb8fTVkZvLidJu2u1V-"

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "rahma";
char pass[] = "hp12345678910";

int dataBlink;
String dataBaru = "";
String data = "";
WidgetLCD lcd(V0);

void setup()
{
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  lcd.clear();
  lcd.print(0, 0, "PENYIMPANAN OBAT");
  lcd.print(4, 1, "-NADIA-");
  delay(5000);
}

void loop()
{
  Blynk.run();

  if(dataBlink == 1 && dataBaru != "1"){
    Serial.println("1");
    dataBaru = "1";
  }else if(dataBlink == 0 && dataBaru != "0"){
    Serial.println("0");
    dataBaru = "0";
  }

  while(Serial.available() > 0){
    data += char(Serial.read());
  }

  if(data.length() > 0){
    lcd.clear();
    lcd.print(0, 0, data);
  }
  data = "";
  delay(500);
}
BLYNK_WRITE(V5) {
  dataBlink = param.asInt();
}

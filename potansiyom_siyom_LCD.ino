#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Çalışmazsa 0x3F yapın
Servo benimServom;

const int potPin = A0;
const int servoPin = 9;

int oncekiAci = -1; // Başlangıçta ekranın bir kez çizilmesi için -1 verdik

void setup() {
  lcd.init();
  lcd.backlight();
  benimServom.attach(servoPin);

  // Sabit metni sadece bir kez yazdır
  lcd.setCursor(0, 0);
  lcd.print("Servo Aci: ");
}

void loop() {
  int potDeger = analogRead(potPin);
  int aci = map(potDeger, 0, 1023, 0, 180);

  // Sadece açı en az 2 derece değiştiyse işlem yap (Paraziti engeller)
  if (abs(aci - oncekiAci) >= 2) {
    oncekiAci = aci;
    benimServom.write(aci);

    // Sadece sayı kısmını güncelle
    lcd.setCursor(11, 0);
    lcd.print(aci);
    lcd.print((char)223); // Derece sembolü
    lcd.print("   ");    // Kalan eski basamakları sil

    // 2. Satır: İlerleme çubuğunu güncelle
    int barUzunlugu = map(aci, 0, 180, 0, 16);
    lcd.setCursor(0, 1);
    for (int i = 0; i < 16; i++) {
      if (i < barUzunlugu) {
        lcd.print((char)255);
      } else {
        lcd.print(" ");
      }
    }
  }

  delay(50);
}

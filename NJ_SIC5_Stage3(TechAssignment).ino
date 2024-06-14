/*  YANG LAIN DARI YANG LAENNN B3 || saya salah satu anggota dari SPECTRO !!
    FNBTKRZ5 MEMPERSEMBAHKAN: Tech Assignment SIC5 Stage 3
    Dengan menggunakan sensor MQ135 dengan microcontroller ESP32.
    LESSGOOOOOOOOO
    Penggunaan bahasa disini: C++, Indo, Inggris. (Bukan jaksel)
    orang ini tepar seperti saya ketika pulang latihan sic5 ini, tiap malam-> 0(-=(
    kenapa malam? karena keseruan latihan jd kelamaan mlu hehehehehehehehhehhh >:3
*/
//Important Library! Without them, we'll be left in hell of errors
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h> //for the sensor

// to DOMINATE the internet, quirky I know <3
const char *wifiNM ="XTNET";
const char *wifiPSS ="Xst45ansr";
const char *serverdst ="http://192.168.4.149:5000/post"; //the path where you want them to belong
/* Just a note: I usually got errors because of the server which caused by the signal (i.e when using hotspot or other stuff). So error of Post -1 is pretty common. I'll study more about it later when I have time.
*/

DHT dht(26, DHT11);
void setup() {
  Serial.begin(115200); //i still don't really get things about serial AHH
  //^^but that should be it.
  WiFi.begin(wifiNM, wifiPSS);
  Serial.print("Lagi konek cuy..");
  Serial.println();
  while (WiFi.status() != WL_CONNECTION) {
    delay(1000);
    Serial.print(" hayoloh");
  }
  Serial.println("DAH KONEK DAH KONEKK!");
  dht.begin(); // starting the sensor
}
void loop() {
  float tempq=dht.readTemperature();
  float humq=dht.readHumidity();
  if (WiFi.status()==WL_CONNECTION) {
    HTTPClient http;
    http.begin(serverdst);
    http.addHeader("Content-Type", "application/json");
    String dtTosend = "{\"temperature\":"+String(tempq)+"\"humidity\":"+String(humq)+"}";
    int httpResponse = http.POST(dtTosend);
    if (httpResponse>0){ //to check if it really sended
    } else {
      Serial.println("Error on sending using the POST method : ");
      Serial.print(httpResponse);
      Serial.println(http.errorToString(httpResponse).c_str());
    }
    http.end();
  } else {Serial.println("Error in wifi connection. dammit")}

  //to show using the serial monitor? I think. So you can see the data from the sensor directly
  Serial.println("Temperature :");
  Serial.print(tempq);
  Serial.print(" C"); //previously I wanted to add Kelvin version of the temperature too, but I don't have time to test it more.. damn
  Serial.println("Humidity : ");
  Serial.print(humq);
  Serial.print("%");
  delay(2100); //wait for 2.1 secs before another loop. Idk why I pick 2.1 secs lol
}
// 일단 마리아db 커넥션 성공


#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// MySQL
IPAddress server_addr(192,168,1,133);
char user[] = "pepper"; 
char password[] = "vpvj135!#%";

char INSERT_DATA[] = "INSERT INTO pepper_log.measure (rawdata) VALUES (%s)";
char query[128];
char temperature[10];

// WiFi
char ssid[] = "Uranus_2.4G"; // SSID NAME
char pass[] = "1432587d!"; // SSID PASSWORD

WiFiClient client;
MySQL_Connection conn((Client *)&client);

void setup() {
 Serial.begin(115200);
  Serial.println ( "" );
 
 WiFi.begin(ssid, pass);

 while ( WiFi.status() != WL_CONNECTED ) {
 delay ( 500 );
 Serial.print ( "." );
 }
 Serial.println ( "" );
 Serial.print ( "Connected to " );
 Serial.println ( ssid );
 Serial.print ( "IP address: " );
 Serial.println ( WiFi.localIP() );
 Serial.println("DB - Connecting...");
 while (conn.connect(server_addr, 3306, user, password) != true) {
 delay(500);
 Serial.print ( "." );
 }
// setSyncInterval(300);
}

void saveTempData() {
//  if (((minute() == 0) || (minute() ==15) || (minute() ==30) || (minute() ==52)) && (second() == 0)) {
//  if (((now.minute() == 0) || (now.minute() ==15) || (now.minute() ==30) || (now.minute() ==45)) && (now.second() == 0)) {
//    if ( minute() == 00 && second() == 00 ) {
   // sensors.requestTemperatures();
   MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
   // Serial.print("Temp : ");
   // Serial.println(sensors.getTempCByIndex(0));
   Serial.print("Query : ");
   // dtostrf(sensors.getTempCByIndex(0), 2, 2, temperature);
   dtostrf(30.5, 2, 2, temperature);
   sprintf(query, INSERT_DATA, temperature);
   cur_mem->execute(query);
   Serial.println(query);
   delete cur_mem;
   Serial.println("Data stored!");
//   }
 }


void loop() {
  if (conn.connected())
    saveTempData();
  delay(5000);
}

// 일단 마리아db 커넥션 성공



#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>

#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// MySQL
IPAddress server_addr(192,168,1,133);
char user[] = "pepper"; 
char password[] = "vpvj135!#%";
char query[128];

// WiFi
char ssid[] = "Uranus_2.4G"; // SSID NAME
char pass[] = "1432587d!"; // SSID PASSWORD

WiFiClient client;
MySQL_Connection conn((Client *)&client);

void setup() {
 Serial.begin(115200);

 
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


void loop() {
}

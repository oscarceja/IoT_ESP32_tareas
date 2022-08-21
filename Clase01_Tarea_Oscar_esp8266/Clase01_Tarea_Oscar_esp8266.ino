//#include<WiFi.h>            //ESP32    https://www.arduino.cc/reference/en/libraries/wifinina/
#include<ESP8266WiFi.h>   //ESP8266  https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html

IPAddress ip(192,168,1,171);        //Static IP to be used in WiFi.config().
IPAddress gateway(192,168,1,254);   //Gateway IP Address configured at WiFi.config().
IPAddress subnet(255,255,255,0);    //Subnet mask configured at WiFi.config().

char ssid[] = "INFINITUM0001";
char password[] = "xsAX6SDA7Q";
#define LED 2 //PullUp resistor; 1:Off; 0: On

void setup() 
{
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  delay(500);   //Delay to let Serial start correclty
  Serial.println("-------------------------------------------------------------------------------------");
  Serial.println("------------------Oscar. Tarea Clase01 WiFi Connection with esp8266------------------");
  
  WiFiNeighboring();    
  
  Serial.print("\nConnecting to 2.4GHz WiFi, SSID: ");
  Serial.print(ssid);
  Serial.println(" with Static IP Address ");
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);  //Starts the WiFi connection

  while (WiFi.status() != WL_CONNECTED)   //While disconnected: !WL_CONNECTED; 3=connected; 6=disconnected
  {
    //delay(300);
    Serial.print(".");
    for(int i=0; i<6; i++)  //Led Blinking when waiting for connection
    {
      digitalWrite(LED,HIGH);      //Enciende LED
      delay(50);   //100 ms
      digitalWrite(LED,LOW);     //Apaga LED
      delay(50);   //100 ms
    }
  }
  printWiFiStatus();
  printWiFiSettings();
}

void loop()
{
}

void WiFiNeighboring() 
{
  Serial.println("\n**WiFi Neighboring Scan in 2.4GHz**\n");
  int NumberOfEntries = WiFi.scanNetworks();   //WiFiNeighboring scan and save NumberOfEntries

  Serial.print("Number of Scaned SSIDs: ");
  Serial.println(NumberOfEntries);
 
  for(int AccessPoint = 0; AccessPoint < NumberOfEntries; AccessPoint++) //AccesPoint is the NumberOfEntrie to be used
  {
    Serial.print(AccessPoint+1);
    Serial.print( ") SSID: " );
    Serial.print( WiFi.SSID(AccessPoint) );  //This method print the scaned SSID of index "AccessPoint"
    Serial.print( "\tBSSID: " );
    Serial.print( WiFi.BSSIDstr(AccessPoint) );
    Serial.print( "\tRSSI: " );
    Serial.print( WiFi.RSSI(AccessPoint) ); Serial.println(" dBm");
  }
}

void printWiFiStatus()
{
  Serial.printf("\nWiFi Status: ");
  Serial.print(WiFi.status());
  Serial.println("  Connected to WiFi!!!");
  digitalWrite(2,LOW);             //Turn On LED when WiFi is connected 
}

void printWiFiSettings()
{
    Serial.println("\n-----Settings of the STA (station): ");
  Serial.print("SSID...............: ");  Serial.println(WiFi.SSID());
  Serial.print("Pre-Shared Key.....: ");  Serial.println(WiFi.psk());
  Serial.print("MAC Address........: ");  Serial.println(WiFi.macAddress());  // 5C:CF:7F:0F:DD:51 (saw in modem)
  Serial.print("BSSID (MAC AP).....: ");  Serial.println(WiFi.BSSIDstr());    // A8:54:A2:26:16:B0 AP
  Serial.printf("Received Signal Strength (RSSI): "); Serial.print(WiFi.RSSI()); Serial.println(" dBm");
  Serial.print("Hostname...........: ");  Serial.println(WiFi.hostname());    // ESP-0FDD51
  Serial.print("Gateway IP.........: ");  Serial.println(WiFi.gatewayIP());
  Serial.print("Static IP Address..: ");  Serial.println(WiFi.localIP());
  Serial.print("Subnet Mask........: ");  Serial.println(WiFi.subnetMask());
  Serial.print("Primary DNS IP.....: ");  Serial.println(WiFi.dnsIP(0));
  Serial.print("Secondary DNS IP...: ");  Serial.println(WiFi.dnsIP(1));
  Serial.printf("\n\n\n");
}

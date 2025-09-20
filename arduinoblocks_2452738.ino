#include "WiFi.h"
#include "ABlocks_DHT.h"

String espwifi_ssid="";
String espwifi_pass="";
#define BLYNK_TEMPLATE_ID "TMPL3X2zgkkgy"
#define BLYNK_TEMPLATE_NAME "ecotherm"
#define BLYNK_AUTH_TOKEN "VlfYvqXDVT-SjyGEMVf01j8VlqdaOW_M"

#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
DHT dht13(13,DHT11);

void espwifi_check(){
	if (WiFi.status() != WL_CONNECTED){
		WiFi.reconnect();
		delay(2000);
	}
}

void espwifi_setup(String _ssid, String _pass){
	WiFi.mode(WIFI_STA);
	espwifi_ssid=_ssid;
	espwifi_pass=_pass;
	WiFi.begin(_ssid.c_str(),_pass.c_str());
	while (WiFi.status() != WL_CONNECTED) delay(500);
}

BLYNK_WRITE(V0){
	Blynk.virtualWrite(V1,dht13.readTemperature());
}

void setup()
{
  	pinMode(13, INPUT);

	dht13.begin();

	espwifi_setup(String("DG INT"),String("appolofish3839"));
	Blynk.begin(BLYNK_AUTH_TOKEN, String(espwifi_ssid).c_str(), String(espwifi_pass).c_str());

}


void loop()
{
	yield();

	espwifi_check();

	Blynk.run();

}
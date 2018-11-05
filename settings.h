const float latitude = 53.87302;
const float longitude = 10.65744;


const char* ssid2 = "Wohnzimmer_EG_WLAN";
const char* password2 = "net2012ge";

const char* ssid = "fablab";
const char* password = "fablabfdm";

const float FW_VERSION = 1.2;
const char* fwUrlBase = "http://xvmwbosvdsfkzgq1.myfritz.net/ota-sensor-update/";

// MQTT
// Make sure to update this for your own MQTT Broker!
const char* mqtt_server = "xvmwbosvdsfkzgq1.myfritz.net";
const char* mqtt_username = "mueller";
const char* mqtt_password = "codemueller";
// The client id identifies the ESP8266 device. Think of it a bit like a hostname (Or just a name, like Greg).
const char* clientID = "Badezimmer";
//const char* clientID = "\"Badezimmer\"";
const char* topic = "esp/multisensor";


WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker


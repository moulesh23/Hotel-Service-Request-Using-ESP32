#include <WiFi.h> // Always before HTTPClient.h header
#include <HTTPClient.h>
#include <ArduinoJson.h> //Version 5

const int inp1=15;
const int inp2=2;
const int inp3=4;
int val1=0;
int val2=0;
int val3=0;
int op=0;
int oldop=0;
void sendval(int op);
void connecttoWiFi(void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);                            //Serial connection
  
  pinMode(inp1,INPUT);
  pinMode(inp2,INPUT);
  pinMode(inp3,INPUT);
  
}

void loop()
{

  val1 = analogRead(inp1);
  val2 = analogRead(inp2);
  val3 = analogRead(inp3);
  Serial.println("****");

  if(val1>=4085)
  {
    op=1;
  }
  else if(val2>=4085)
  {
    op=2;
  }
  else if(val3>=4085)
  {
    op=3;
  }
  else
  {
    op=0;
  }
  
  //Serial.println(op);
  
 // delay(300);

}

void sendval(int op){
if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    const int capacity = JSON_OBJECT_SIZE(2); //Creating buffer
    StaticJsonBuffer<capacity> jb;

    JsonObject& obj = jb.createObject();  //Creating object
    obj["roomno"] = 1;
    obj["requesttype"]=op;

    HTTPClient http;    //Declare object of class HTTPClient
 
    http.begin("http://122.166.154.2:8200/sendservice");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header

    char JSONmessageBuffer[300];
    obj.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
 
    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    //Serial.println(obj);
    String payload = http.getString();                                        //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
 
    http.end();  //Close connection
 
  } else {
 
    Serial.println("Error in WiFi connection");
    Serial.println("Attempting to Reconnect......");
    connecttoWiFi();
 
  }
 }
 void connecttoWiFi(){
   WiFi.begin("SSID", "9642073373");
  while (WiFi.status() != WL_CONNECTED)
  {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
 }

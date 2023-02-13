#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h> 
#include <WebServer.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include <Update.h>
#define ANALOG_PIN_3 39 // pin untuk menerima data battry
#define ANALOG_PIN_0 36 // pin untuk menerima data stepper
#define PinOut1 2   // pin untuk mengambil data button LOCK
#define PinOut2 15   // pin untuk mengambil data button OPEN
#include <SocketIoClient.h>
     
WebServer server(80);
const char* host = "te-ja.id";

int valADC1;       // variabel untuk menyimpan nilai konversi analog ke digital
int valADC2;       // variabel untuk menyimpan nilai konversi analog ke digital

SocketIoClient webSocket;
void control(const char * cb, size_t length) {
  Serial.printf("got message: %s\n", cb);
}
void controlarduino(const char * cb2, size_t length) {
  Serial.printf("got message: %s\n", cb2);
}
void control_formserver(const char * webcb, size_t length) {
  String a = webcb;
  Serial.println(webcb);
  char b = a.charAt(92);
  int c = (int)b;
  Serial.println(b);
   char b1 = a.charAt(71);
  int c1 = (int)b1;
  Serial.println(b1);
  int i =0;
if (c == 48 || c1 == 48){
     for(i=0; i<=3; i++)
      {
        digitalWrite ( PinOut2, HIGH);
        webSocket.emit("control", "{\"HWID\":\"BKV2010501\",\"lock\":\"Unlock\",\"stpr\":\"Acess with Internet\"}");
      }
      digitalWrite ( PinOut2, LOW);
      btry();
  }
  else {
   for(i=0; i<=3; i++)
      {
        digitalWrite ( PinOut1, HIGH);
        webSocket.emit("control", "{\"HWID\":\"BKV2010501\",\"lock\":\"Lock\",\"stpr\":\"Acess with Internet\"}");
      }
      digitalWrite ( PinOut1, LOW);
      btry();
}
  }
 void btry(){
    valADC1 = analogRead(ANALOG_PIN_3);    // baca nilai analog data battry
  int prentase = ((valADC1 / 1000) * 100);
{
  int baterai[]={20,30,40,50,60,70,80,90,100};
{
if (prentase >= 1000)
 {
  webSocket.emit("control", "{\"HWID\":\"BKV2010501\",\"btry\":\"100%\"}");
   Serial.println(prentase);         // kirim nilai val ke koneksi serial data battry
 }
else if (prentase >= 900)
 {
  webSocket.emit("control", "{\"HWID\":\"BKV2010501\",\"btry\":\"90%\"}");
   Serial.println(prentase);         // kirim nilai val ke koneksi serial data battry
 }
else if (prentase >= 800)
 {
  webSocket.emit("control", "{\"HWID\":\"BKV2010501\",\"btry\":\"80%\"}");
   Serial.println(prentase);         // kirim nilai val ke koneksi serial data battry
 }  
 else if (prentase >= 700)
 {
  webSocket.emit("control", "{\"HWID\":\"BKV2010501\",\"btry\":\"70%\"}");
   Serial.println(prentase);         // kirim nilai val ke koneksi serial data battry
 } 
else if (prentase >= 600)
 {
  webSocket.emit("control", "{\"HWID\":\"BKV2010501\",\"btry\":\"60%\"}");
   Serial.println(prentase);         // kirim nilai val ke koneksi serial data battry
 }  
 else if (prentase >= 500)
 {
  webSocket.emit("control", "{\"HWID\":\"BKV2010501\",\"btry\":\"50%\"}");
   Serial.println(prentase);         // kirim nilai val ke koneksi serial data battry
 } 
else if (prentase >= 400)
 {
  webSocket.emit("control", "{\"HWID\":\"BKV2010501\",\"btry\":\"40%\"}");
   Serial.println(prentase);         // kirim nilai val ke koneksi serial data battry
 }
else if (prentase >= 300)
 {
  webSocket.emit("control", "{\"HWID\":\"BKV2010501\",\"btry\":\"30%\"}");
   Serial.println(prentase);         // kirim nilai val ke koneksi serial data battry
 }
else if (prentase >= 200)
 {
  webSocket.emit("control", "{\"HWID\":\"BKV2010501\",\"btry\":\"20%\"}");
   Serial.println(prentase);         // kirim nilai val ke koneksi serial data battry
 }
else
 {
  webSocket.emit("control", "{\"HWID\":\"BKV2010501\",\"btry\":\"battry low please charge!\"}");
   Serial.println(prentase);         // kirim nilai val ke koneksi serial data battry
 }
}
    }
 }
     void  stpr(){
      valADC2 = analogRead(ANALOG_PIN_0);
{
if (valADC2 > 900)
 {
  webSocket.emit("control", "{\"HWID\":\"BKV2010501\",\"Lock\":\"terkunci\",\"stpr\":\"Acess Local\"}");
  Serial.println(valADC2);// kirim nilai val ke koneksi serial data stepper
  btry();
  return;
 }
 else if(valADC2 > 0){
  webSocket.emit("control", "{\"HWID\":\"BKV2010501\",\"Unlock\":\"terkunci\",\"stpr\":\"Acess Local\"}");
  Serial.println(valADC2);// kirim nilai val ke koneksi serial data stepper
  btry();
  return;
  }
else{
  //Serial.println(valADC2);         // kirim nilai val ke koneksi serial data stepper
} 
}
}   
/* Style */
String style =
"<style>#file-input,input{width:100%;height:44px;border-radius:4px;margin:10px auto;font-size:15px}"
"input{background:#f1f1f1;border:0;padding:0 15px}body{background:#3498db;font-family:sans-serif;font-size:14px;color:#777}"
"#file-input{padding:0;border:1px solid #ddd;line-height:44px;text-align:left;display:block;cursor:pointer}"
"#bar,#prgbar{background-color:#f1f1f1;border-radius:10px}#bar{background-color:#3498db;width:0%;height:10px}"
"form{background:#fff;max-width:258px;margin:75px auto;padding:30px;border-radius:5px;text-align:center}"
".btn{background:#3498db;color:#fff;cursor:pointer}</style>";

/* Login page */
String loginIndex = 
"<form name=loginForm>"
"<h1>STAR 1 Login</h1>"
"<input name=userid placeholder='Username'> "
"<input name=pwd placeholder=Password type=Password> "
"<input type=submit onclick=check(this.form) class=btn value=Login></form>"
"<script>"
"function check(form) {"
"if(form.userid.value=='admin' && form.pwd.value=='admin')"
"{window.open('/serverIndex')}"
"else"
"{alert('Error Password or Username')}"
"}"
"</script>" + style;
 
/* Server Index Page */
String serverIndex = 
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
"<input type='file' name='update' id='file' onchange='sub(this)' style=display:none>"
"<label id='file-input' for='file'>   Choose file...</label>"
"<input type='submit' class=btn value='Update'>"
"<br><br>"
"<div id='prg'></div>"
"<br><div id='prgbar'><div id='bar'></div></div><br></form>"
"<script>"
"function sub(obj){"
"var fileName = obj.value.split('\\\\');"
"document.getElementById('file-input').innerHTML = '   '+ fileName[fileName.length-1];"
"};"
"$('form').submit(function(e){"
"e.preventDefault();"
"var form = $('#upload_form')[0];"
"var data = new FormData(form);"
"$.ajax({"
"url: '/update',"
"type: 'POST',"
"data: data,"
"contentType: false,"
"processData:false,"
"xhr: function() {"
"var xhr = new window.XMLHttpRequest();"
"xhr.upload.addEventListener('progress', function(evt) {"
"if (evt.lengthComputable) {"
"var per = evt.loaded / evt.total;"
"$('#prg').html('progress: ' + Math.round(per*100) + '%');"
"$('#bar').css('width',Math.round(per*100) + '%');"
"}"
"}, false);"
"return xhr;"
"},"
"success:function(d, s) {"
"console.log('success!') "
"},"
"error: function (a, b, c) {"
"}"
"});"
"});"
"</script>" + style;

void setup() {
  Serial.begin(115200);
  pinMode(ANALOG_PIN_3, INPUT); 
  pinMode(ANALOG_PIN_0, INPUT);
  pinMode(PinOut1, OUTPUT);
  pinMode(PinOut2, OUTPUT);
  WiFiManager wifiManager;
  wifiManager.autoConnect("SMART HANDLE STAR 1");
  Serial.println("Connected."); 
  server.begin();
 /*use mdns for host name resolution*/
  if (!MDNS.begin(host)) { http://te-ja.id
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  /*return index page which is stored in serverIndex */
  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
  });
  server.on("/serverIndex", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });
  server.begin();
  delay(10);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.setDebugOutput(true);
  webSocket.begin("te-ja.id", 3003, "/socket.io/?transport=websocket");
  // use HTTP Basic Authorization this is optional remove if not needed
  webSocket.setAuthorization("BKV2010501", "BKV2010501");
  webSocket.on("cb", control);
  webSocket.on("webcb", control_formserver);
  webSocket.on("arduino", controlarduino);
}

void loop(){
  webSocket.loop();
  server.handleClient();
  stpr();
}

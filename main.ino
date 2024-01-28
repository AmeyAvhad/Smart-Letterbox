#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP_Mail_Client.h>

#define WIFI_SSID "POCO"
#define WIFI_PASSWORD "avantika"

#define SMTP_server "smtp.gmail.com"
#define SMTP_Port 465

#define sender_email "autoresumebuilder@gmail.com"
#define sender_password "xgvetyxfhpumhdtm"

#define Recipient_email "avhadamey3@gmail.com"

int IR = 5;
int l = 4;
int val = 0;

SMTPSession smtp;
ESP_Mail_Session session;
SMTP_Message message;

void detect() {
  int IRState = digitalRead(IR);
  val = digitalRead(IR);
  if (IRState == 0) {
    digitalWrite(l, HIGH);
    if (!smtp.connect(&session))
      return;
  }

  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email");
  digitalWrite(l, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(l, OUTPUT);
  pinMode(IR, INPUT);

  Serial.println();
  Serial.print("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(50);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  smtp.debug(1);

  session.server.host_name = SMTP_server;
  session.server.port = SMTP_Port;
  session.login.email = sender_email;
  session.login.password = sender_password;
  session.login.user_domain = "";

  message.sender.name = "Smart LetterBox";
  message.sender.email = sender_email;
  message.subject = "Letter Received in LetterBox";
  message.addRecipient("Amey", Recipient_email);

  String htmlMsg = "<div style=\"color:#0000FF;\"><h1>Letter Received!</h1><p>You have received a letter</p></div>";
  message.html.content = htmlMsg.c_str();
  message.html.content = htmlMsg.c_str();
  message.text.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
}

void loop() {
  detect();
}

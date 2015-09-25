int pir = D2;
int led = D0;

int current = LOW;
bool occupied = FALSE;
String roomName = "room-1";


void sendRoomStatus(String roomStatus, String roomName) {
  Spark.publish(roomStatus, roomName, 60, PRIVATE);
}


void statusHandler(const char *event, const char *data) {
  if (occupied) {
    sendRoomStatus("occupied", roomName);
  } else {
    sendRoomStatus("empty", roomName);
  }
}


void setup() {

  pinMode(pir, INPUT);
  pinMode(led, OUTPUT);

  Spark.subscribe("roomStatus", statusHandler);

  Serial.begin(9600);

}


void loop() {

  current = digitalRead(pir);
  digitalWrite(led, current);

  if (current == HIGH) {
    Serial.println("Motion");
    if (!occupied) {
      occupied = TRUE;
      Serial.println("State change: Send room occupied notification");
      sendRoomStatus("occupied", roomName);
    }
  } else {
    Serial.println("No motion");
    if (occupied) {
      occupied = FALSE;
      Serial.println("State change: Send room empty notification");
      sendRoomStatus("empty", roomName);
    }
  }

  delay(1000);

}

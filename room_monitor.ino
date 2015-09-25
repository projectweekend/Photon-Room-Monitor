int pir = D2;
int led = D0;

int current = LOW;
bool occupied = FALSE;
String roomName = "room-1";


void statusHandler(const char *event, const char *data) {
  int reading = digitalRead(pir);
  if (reading == HIGH) {
    Spark.publish("occupied", roomName, 60, PRIVATE);
  } else {
    Spark.publish("empty", roomName, 60, PRIVATE);
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
      Spark.publish("occupied", roomName, 60, PRIVATE);
    }
  } else {
    Serial.println("No motion");
    if (occupied) {
      occupied = FALSE;
      Serial.println("State change: Send room empty notification");
      Spark.publish("empty", roomName, 60, PRIVATE);
    }
  }

  delay(1000);

}

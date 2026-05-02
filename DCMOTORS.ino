 int enA = 33;
int enB = 13;

int IN1 = 25;
int IN2 = 26;
int IN3 = 27;
int IN4 = 14;

int Speed = 200;


int chA = 0;)
int chB = 1;

void setup() {

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  ledcAttach(enA, 5000, 8;
  ledcAttach(enB, 5000, 8);
}

void loop() {
  forward();
  delay(3000);

  stopCar();
  delay(2000);
}

void forward() {
  ledcWrite(enA, Speed);
  ledcWrite(enB, Speed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopCar() {
  ledcWrite(enA, 0);
  ledcWrite(enB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
const int motor2Pin1 = 4;
const int motor2Pin2 = 5;
const int motor3Pin1 = 6;
const int motor3Pin2 = 7;
const int motor4Pin1 = 8;
const int motor4Pin2 = 9;


const int servoPin1 = 10;
const int servoPin2 = 11;


const int trigPin = 12;
const int echoPin = 13;


long duration;
int distance;

void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);
  pinMode(motor4Pin1, OUTPUT);
  pinMode(motor4Pin2, OUTPUT);
  
  pinMode(servoPin1, OUTPUT);
  pinMode(servoPin2, OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  checkObstacle();

  moveForward();
  delay(30000);
  
  checkObstacle();

  moveBackward();
  delay(60000);
  
  checkObstacle();

  unsigned long startTime = millis();
  while (millis() - startTime < 60000) {
    checkObstacle();
    turnRight();
    delay(1000);
    checkObstacle();
    turnLeft();
    delay(1000);
  }

  stopMotors();
  delay(1000);
}

void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW);
  Serial.println("Moving Forward");
}

void moveBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);
  Serial.println("Moving Backward");
}

void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);
  Serial.println("Turning Right");
}

void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW);
  Serial.println("Turning Left");
}

void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, LOW);
  Serial.println("Stopping Motors");
}

void setServoPosition(int angle) {
  if (angle == 90) {
    digitalWrite(servoPin1, LOW);
    digitalWrite(servoPin2, LOW);
    return;
  }
  
  
  if (angle < 90) {
    digitalWrite(servoPin1, HIGH);
    digitalWrite(servoPin2, LOW);
    delay(map(angle, 0, 90, 1000, 100));
    digitalWrite(servoPin1, LOW);
    return;
  }
  
  if (angle > 90) {
    digitalWrite(servoPin1, LOW);
    digitalWrite(servoPin2, HIGH);
    delay(map(angle, 90, 180, 100, 1000));
    digitalWrite(servoPin2, LOW);
    return;
  }
}

void checkObstacle() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  
  if (distance < 10) {
    Serial.println("Obstacle detected! Changing direction...");
    stopMotors();
    
    setServoPosition(0);
    delay(500);
    setServoPosition(180);
    delay(500);
    setServoPosition(90);
    delay(500);
    
    moveBackward();
    delay(2000);
    
    turnRight();
    delay(1000);
    
    stopMotors();
  }
}
/*
====================================================
Obstacle Avoiding Robot using Arduino Uno
Author: Yazdaan Khan

Components:
- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- L298N Motor Driver
- 4 DC Gear Motors
- Lithium-Ion Battery Pack

Description:
The robot continuously measures the distance
ahead using an ultrasonic sensor. If an obstacle
is detected within 20 cm, the robot stops and
turns right before continuing forward.

====================================================
*/

// Ultrasonic Sensor Pins
#define trigPin 9
#define echoPin 10

// Motor Driver Pins
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

long duration;
int distance;

void setup()
{
    // Sensor configuration
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Motor configuration
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // Serial Monitor
    Serial.begin(9600);

    Serial.println("Obstacle Avoiding Robot Started");
}

// Function: Move Forward
void moveForward()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

// Function: Stop Robot
void stopRobot()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

// Function: Turn Right
void turnRight()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

// Function: Turn Left
void turnLeft()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

// Function: Measure Distance
int getDistance()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    int dist = duration * 0.034 / 2;

    return dist;
}

void loop()
{
    distance = getDistance();

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Safe distance threshold
    if (distance > 20)
    {
        moveForward();
    }
    else
    {
        stopRobot();
        delay(300);

        turnRight();
        delay(500);
    }

    delay(100);
}

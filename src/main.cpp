
#include <Servo.h>
#include <TinyStepper_28BYJ_48.h>

const byte MOTORX_IN1_PIN = 16;
const byte MOTORX_IN2_PIN = 17;
const byte MOTORX_IN3_PIN = 21;
const byte MOTORX_IN4_PIN = 22;

const byte MOTORY_IN1_PIN = 23;
const byte MOTORY_IN2_PIN = 19;
const byte MOTORY_IN3_PIN = 18;
const byte MOTORY_IN4_PIN = 26;

const uint32_t STEPS_PER_REVOLUTION = 2048;
const float WHEEL_DIAMETER_MM = 60;
const float WHEEL_DISTANCE = 111;
const float ROTATION_UMFANG = WHEEL_DISTANCE * PI;
const float STEPS_PER_METER =
    (STEPS_PER_REVOLUTION * 1000) / (PI * WHEEL_DIAMETER_MM);

const float SPEED = 400.0;
const float ACC = 400.0;

TinyStepper_28BYJ_48 motLeft;
TinyStepper_28BYJ_48 motRight;
Servo servo;

void right(float degrees)
{
  auto dist = (STEPS_PER_METER * ROTATION_UMFANG * degrees) / (1000.0 * 360.0 * 2);
  motLeft.setupMoveInSteps(dist);
  motRight.setupMoveInSteps(dist);
  while (!motLeft.motionComplete() && !motRight.motionComplete())
  {
    motLeft.processMovement();
    motRight.processMovement();
  }
}
void left(float degrees) { right(degrees * -1.0); }

void forward(int32_t mm)
{
  auto dist = (STEPS_PER_METER * (float)mm) / 1000.0;
  motLeft.setupMoveInSteps(dist);
  motRight.setupMoveInSteps(-dist);
  while (!motLeft.motionComplete() && !motRight.motionComplete())
  {
    motLeft.processMovement();
    motRight.processMovement();
  }
}
void back(int32_t mm) { forward(mm * -1); }

void setup()
{

  Serial.begin(9600);

  motLeft.connectToPins(MOTORX_IN1_PIN, MOTORX_IN2_PIN, MOTORX_IN3_PIN,
                        MOTORX_IN4_PIN);
  motLeft.setAccelerationInStepsPerSecondPerSecond(ACC);
  motLeft.setSpeedInStepsPerSecond(SPEED);
  motRight.connectToPins(MOTORY_IN1_PIN, MOTORY_IN2_PIN, MOTORY_IN3_PIN,
                         MOTORY_IN4_PIN);
  motRight.setAccelerationInStepsPerSecondPerSecond(ACC);
  motRight.setSpeedInStepsPerSecond(SPEED);

  servo.attach(2, Servo::CHANNEL_NOT_ATTACHED, 45, 120);
}

void loop()
{
  right(180);
  delay(3);
  left(180);
  delay(2);
}

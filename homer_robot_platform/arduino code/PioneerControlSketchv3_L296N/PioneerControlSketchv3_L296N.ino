/**
 * ___________________________________________________________________________________________________________
 *|                                                                                                           |
 *|                             .                                                                             |
 *|                           MMMMM                                                                           |
 *|                        MNMMMMMMMM                                                                         |
 *|                      MMMMMMMMMMMMMM                                                                       |
 *|                   MMMMMMMMMMMMMMMMMMNM                                                                    |
 *|                 MMMMMMMMMMMMMMMMMMMMMMMM                                                                  |
 *|              MMMMMMMMMMMMMMMMMMMMMMMMMMMMM                                                                |
 *|            MNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                                                             |
 *|        MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                                                             |
 *|      MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                                                          |
 *|   MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                                                        |
 *| MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                                                      |
 *|MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                                                     |
 *|MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                                                     |
 *|MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                                                     |
 *|MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                                                     |
 *|MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                                                     |
 *|MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                                                     |
 *|MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                                                     |
 *|MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                                                     |
 *|MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                                                     |
 *|MMMMMMMMMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                                                     |
 *|MMMMMMMMMM                 MMMMMMMMMMMMMMMMMMMMMMMMMMM                                                     |
 *|MMMMMMMMMM                 MMMMMMMMMMMMMMMMMMMMMMMMMMM                                                     |
 *|MMMMMMMMMM                 MMMMMMMMMMMMMMMMMMMMMMMMMMM                                                     |
 *|MMMMMMMMMM                 MMMMMMMMMMMMMMMMMMMMMMMMMMM                                                     |
 *|MMMMMMMMMM                 MMMMMMMMMMMMMMMM0 MMMMMMMMM                                                     |
 *|MMMMMMMMMM                 MMMMMMMMMMMMMMMM  MMMMMMMMM                                                     |
 *|MMMMMMMMMM                 MMMMMMMMMMMMMMMM  MMMMMMMMM                                                     |
 *|MMMMMMMMMM                 MMMMMMMMMMMMMMMM         MM  MMMMMMM   MMMMMMMMM   MMMMMMM    MMMMMMMM          |
 *|MMMMMMMMMM                 MMMMMMMMMMMMMMMM  MMMMMM  M M       M  N   M   M  MMMMMMMMM  MM                 |
 *|MMMMMMMMMM                 MMMMMMMMMMMMMMMM  MMMMMM  M M       M  N   M   M  MM         MM                 |
 *|MMMMMMMMMM                 MMMMMMMMMMMMMMMM0 MMMMMM0 M  MMMMMMM   M   M   M   MMMMMMMM   M                 |
 *| NMMMMMMMM                  NMMMMMMMMMMMMMMMMMMMMMMMMM                                                     |
 *|  ......                     .......................                                                       |
 *|___________________________________________________________________________________________________________|
 *                                         HOMER@Uni-Koblenz
 *                                         Alexander Kreutz
 *                                         alexkreutz@uni-koblenz.de
 *
 *                                         Florian Polster
 *                                         fpolster@uni-koblenz.de
 *
 *  Arduino Robot Controller - Sketch 0.9b5
 *
 *  (c) 2014, GPLv3
 *
 *
 *
 **/

#include <digitalWriteFast.h>  // library for high performance reads and writes by jrraines
#include <L298N.h>

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <homer_robot_platform/EncoderValues.h>
#include <homer_robot_platform/RobotState.h>

#include <ros/time.h>

//pin definition
#define EN 9
#define IN1 8
#define IN2 7

#define EMERGENCY_PORT  26
////////////////////////////////////////////////////////
/*                  ENCODER PART                      */
////////////////////////////////////////////////////////

#define ENCODER_R_1     19
#define ENCODER_R_2     18
#define ENCODER_L_1     20
#define ENCODER_L_2     21  

// Quadrature encoders
// Left encoder
#define c_LeftEncoderInterrupt 3
//#define LeftEncoderIsReversed
volatile bool _LeftEncoderBSet;
volatile long _LeftEncoderTicks = 0;
 
// Right encoder
#define c_RightEncoderInterrupt 4
#define RightEncoderIsReversed
volatile bool _RightEncoderBSet;
volatile long _RightEncoderTicks = 0;


// Interrupt service routines for the left motor's quadrature encoder
void HandleLeftMotorInterruptA()
{
  // Test transition; since the interrupt will only fire on 'rising' we don't need to read pin A
  _LeftEncoderBSet = digitalReadFast(ENCODER_L_2);   // read the input pin

 
  // and adjust counter + if A leads B
  #ifdef LeftEncoderIsReversed
    _LeftEncoderTicks -= _LeftEncoderBSet ? -1 : +1;
  #else
    _LeftEncoderTicks += _LeftEncoderBSet ? -1 : +1;
  #endif
}
 
// Interrupt service routines for the right motor's quadrature encoder
void HandleRightMotorInterruptA()
{
  // Test transition; since the interrupt will only fire on 'rising' we don't need to read pin A
  _RightEncoderBSet = digitalReadFast(ENCODER_R_2);   // read the input pin
 
  // and adjust counter + if A leads B
  #ifdef RightEncoderIsReversed
    _RightEncoderTicks -= _RightEncoderBSet ? -1 : +1;
  #else
    _RightEncoderTicks += _RightEncoderBSet ? -1 : +1;
  #endif
}

void attachInterrupts()
{
  
  // Quadrature encoders
  // Left encoder
  pinMode(ENCODER_L_1, INPUT);      // sets pin A as input
  digitalWrite(ENCODER_L_1, LOW);  // turn on pullup resistors
  pinMode(ENCODER_L_2, INPUT);      // sets pin B as input
  digitalWrite(ENCODER_L_2, LOW);  // turn on pullup resistors
  attachInterrupt(c_LeftEncoderInterrupt, HandleLeftMotorInterruptA, RISING);
 
  // Right encoder
  pinMode(ENCODER_R_1, INPUT);      // sets pin A as input
  digitalWrite(ENCODER_R_1, LOW);  // turn on pullup resistors
  pinMode(ENCODER_R_2, INPUT);      // sets pin B as input
  digitalWrite(ENCODER_R_2, LOW);  // turn on pullup resistors
  attachInterrupt(c_RightEncoderInterrupt, HandleRightMotorInterruptA, RISING);
  
}

float f_distancePerTick = 0.0;
float f_half_wheel_diff = 0.2;
float f_wheel_diff = 0.41;

double d_targetSpeedL = 0;
double d_targetSpeedR = 0;

double d_currentSpeedL = 0;
double d_currentSpeedR = 0;

int i_m1Speed = 0;
int i_m2Speed = 0;

long l_lastT = 0;

////////////////////////////////////////////////////////
/*                    MOTOR PART                      */
////////////////////////////////////////////////////////

//DualVNH5019MotorShield md;

//create a motor instance
L298N motor1(EN, IN1, IN2);

void initMotors()
{
  //md.init();

}

void adjustSpeed()
{

  if ((fabs(d_targetSpeedL) < 0.001) && (fabs(d_targetSpeedR) < 0.001))
  {
    i_m1Speed = 0;
    i_m2Speed = 0;
  }
  else
  {
    float additionR = fabs(10 * fabs(d_targetSpeedR-d_currentSpeedR));
    float additionL = fabs(10 * fabs(d_targetSpeedL-d_currentSpeedL));
    
    if(additionR > 0.001 && additionR < 1.0)
    {
      additionR = 1; 
    }
    if(additionL > 0.001 && additionL < 1.0)
    {
      additionL = 1; 
    }
    
    if (d_targetSpeedR > d_currentSpeedR) // Porque se resta? Por el sentido de giro del motor? Negativo = hacia delante?
    {
      i_m1Speed -= additionR;
    }
    else if (d_targetSpeedR < d_currentSpeedR)
    {
      i_m1Speed += additionR;
    }
     
    if (d_targetSpeedL > d_currentSpeedL)
    {
      i_m2Speed -= additionL;
    }
    else if (d_targetSpeedL < d_currentSpeedL)
    {
      i_m2Speed += additionL;
    }
  }
  
  if(i_m1Speed > 400)
  {
    i_m1Speed = 400;
  }
  else if (i_m1Speed < -400)
  {
    i_m1Speed = -400;
  }
  
  if(i_m2Speed > 400)
  {
    i_m2Speed = 400;
  }
  else if (i_m2Speed < -400)
  {
    i_m2Speed = -400;
  }

  motor1.moveSpeed(i_m1Speed);
  //motor2.moveSpeed(i_m2Speed);

  //motor1.setSpeed(fabs(i_m1Speed));
  //motor2.setSpeed(fabs(i_m2Speed));

  //if (i_m1Speed > 0) motor1.forward();
  //else if (i_m1Speed < 0) motor1.backward();
  //else motor1.stop();

  //if (i_m2Speed > 0) motor2.forward();
  //else if (i_m2Speed > 0) motor2.backward();

  /*if (!md.getM1Fault() && !md.getM2Fault())
  {
    md.setSpeeds(i_m1Speed, i_m2Speed);
  }*/
}

////////////////////////////////////////////////////////
/*                    ROS PART                        */
////////////////////////////////////////////////////////

void cmd_velCallback( const geometry_msgs::Twist& msg)
{
    float angular = f_half_wheel_diff * msg.angular.z * 1.4;//* f_half_wheel_diff
    d_targetSpeedL = msg.linear.x - angular;
    d_targetSpeedR = msg.linear.x + angular;
}

ros::Publisher* encoderPublisher;
ros::Publisher* emergencyPublisher;
ros::Publisher* statePublisher;
ros::Subscriber<geometry_msgs::Twist> cmdvelSubscriber("/robot_platform/cmd_vel", &cmd_velCallback);

ros::NodeHandle nh;
std_msgs::Bool emergencyMessage;
homer_robot_platform::EncoderValues encoderMessage;
homer_robot_platform::RobotState stateMessage;

boolean readEmergency()
{
  if (digitalRead(EMERGENCY_PORT) == LOW)  // TO_DO: negar la igualdad con el circuito de emergencia (comprobar que el boton sea normalmente cerrado)
  {
    emergencyMessage.data = true;
    i_m1Speed = 0;
    i_m2Speed = 0;
    motor1.setSpeed(0);
    motor1.stop();
    //motor2.setSpeed(0);
    //md.setSpeeds(0, 0);
    return true;
  }
  else
  {
    emergencyMessage.data = false;
    return false;
  }
}

void updateEncoder()
{
  int left = _LeftEncoderTicks;
  int right = _RightEncoderTicks;
  
  encoderMessage.left += left;
  encoderMessage.right += right;

  _LeftEncoderTicks = 0;
  _RightEncoderTicks = 0;

  long currentTime = millis();
  double deltaTime = currentTime - l_lastT;
  l_lastT = currentTime;

  d_currentSpeedL = 1000.0 * (f_distancePerTick * left) / deltaTime;
  d_currentSpeedR = 1000.0 * (f_distancePerTick * right) / deltaTime;
}

void initRos()
{
  encoderPublisher = new ros::Publisher("/robot_platform/encoder", &encoderMessage);
  emergencyPublisher = new ros::Publisher("/emergency_button_pressed", &emergencyMessage);
  statePublisher = new ros::Publisher("/robot_platform/robotState", &stateMessage);
  
  nh.getHardware()->setBaud(262144);
  nh.initNode();
    
    do
  {
    nh.spinOnce();
  
    nh.advertise(*statePublisher);
    nh.advertise(*emergencyPublisher); //double advertisement for better stability
    nh.advertise(*encoderPublisher);
    nh.subscribe(cmdvelSubscriber);

    
  }while(!nh.connected());
    nh.spinOnce();
  
    nh.advertise(*statePublisher);
    nh.advertise(*emergencyPublisher); //double advertisement for better stability
    nh.advertise(*encoderPublisher);
    nh.subscribe(cmdvelSubscriber);

    nh.negotiateTopics();
  
}

void publishMessages()
{
    encoderPublisher->publish( &encoderMessage );
    nh.spinOnce();
    emergencyPublisher->publish( &emergencyMessage );
    
    stateMessage.targetSpeedLeft = d_targetSpeedL;
    stateMessage.targetSpeedRight = d_targetSpeedR;
    stateMessage.currentSpeedLeft = d_currentSpeedL;
    stateMessage.currentSpeedRight = d_currentSpeedR;
    stateMessage.encoderLeft = encoderMessage.left;
    stateMessage.encoderRight = encoderMessage.right;
    stateMessage.wheelDiff = f_wheel_diff;
    stateMessage.distancePerTick = f_distancePerTick;
    stateMessage.emergencyPressed = emergencyMessage.data;
    stateMessage.encoderForCalc = true;
    
    statePublisher->publish( &stateMessage );
    
    encoderMessage.left = 0;
    encoderMessage.right = 0;
}

void getParams()
{ 
  while(!nh.connected()) {nh.spinOnce();}

  if (!nh.getParam("/robot_platform/distancePerTick", &f_distancePerTick))
  {
    f_distancePerTick = 0.000027974;
  } 
  if (nh.getParam("/robot_platform/wheelDiff", &f_wheel_diff))
  {
    f_half_wheel_diff = f_wheel_diff / 2.0;
  } 
}

/////////////////////////////////////////////////////////
/*                   Arduino Logic                     */
/////////////////////////////////////////////////////////

void setup() {
  pinMode(EMERGENCY_PORT, INPUT);
  digitalWrite(EMERGENCY_PORT, HIGH);
  initMotors();
  initRos();
  attachInterrupts();
}

void loop() {
   if(!nh.connected())
  {
    do
    {
    i_m1Speed = 0;
    i_m2Speed = 0;
    motor1.setSpeed(0);
    motor1.stop();
    //motor2.setSpeed(0);
    //md.setSpeeds(0, 0);
    nh.spinOnce();
  
    nh.advertise(*statePublisher);
    nh.advertise(*emergencyPublisher); //double advertisement for better stability
    nh.advertise(*encoderPublisher);
    nh.subscribe(cmdvelSubscriber);
    
    }
    while(!nh.connected());
    nh.spinOnce();
  
    nh.advertise(*statePublisher);
    nh.advertise(*emergencyPublisher); //double advertisement for better stability
    nh.advertise(*encoderPublisher);
    nh.subscribe(cmdvelSubscriber);
    
    nh.negotiateTopics();
  }
  for(int i = 0; i <9; i++)
  {
    delay(10);
      nh.spinOnce();
      updateEncoder();
      
      if (!readEmergency())
      {
        adjustSpeed();
      }   
  }
  publishMessages();
  nh.spinOnce(); 
}

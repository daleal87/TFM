
#include <ros.h>
#include <std_msgs/Int32.h>
#include <Wire.h>
#include <MD25IIC.h>
// MD25IIC METHODS:
//    -----------------------   ------------------------
//   |       MOTOR          |  | BOARD                 |
// --------------------------  |-----------------------|
// 1 | setMotor1Speed(byte) |  | getAddress()          |
//   | getMotor1Encoder()   |  | setMode(byte)         |
//   | getMotor1Current()   |  | getBattery()          |
// -------------------------|  | enableTimeOut(T/F)    |
// 2 | setMotor2Speed(byte) |  | enableController(T/F) |
//   | getMotor2Encoder()   |  | resetEncoders()       |
//   | getMotor2Current()   |  | setAcceleration(byte) |
// -------------------------|  |-----------------------|

#define SERIAL_CLASS HardwareSerial

// ------------------------ Controladora MD25 ------------------------
MD25IIC MyBoard;


//  ------------------------ Variables PID ------------------------
float Kp = 1.2;                // Proportional gain (tune it!!)
float Ki = 0.0;                // Integral gain (tune it!!)
float Kd = 0.1;                // Derivative gain (tune it!!)
float integral = 0;            // Integral component
float derivativo = 0;          // Derivative component
float error_k = 0;             // Set-point error at time k
float error_k_1 = 0;           // Set-point error at time k-1
float cmd_vel_cable = 0;       // Command signal
float deltaT = 0.02;           // Sampling period
float f_corrector = 8.0;       // Factor correcto del command signal --> error de mas de 384mm implica velocidad maxima

byte motor = 128;              // Actuator signal
unsigned long time;


// ------------------------ Variables Cable ------------------------
long longitud_cable = 0; // Medida del cable extendido entre los robots en mm.
long longitud_inicial = 2000; //  El sistema se inicializa con una longitud minima de 500mm (50cm)
long l_objetivo = 2000; // Medida del cable extendido en mm.
long contador_encoder = 0; // Cuenta de los pulsos medidos por el encoder
long long_min = 50; // Longitud minima que puede tener el cable por seguridad
long long_max = 5000; // Longitud máxima que puede tener el cable por seguridad
bool modo_emergencia = false; // Modo Emergencia, el motor se deteniene
float pulsos_por_vuelta = 360.0;  // Pulsos por vuelta del encoder
float vueltas = 0.0; // Numero de vueltas giradas por el motor
int l_vuelta = 100; // Longitud media de cada vuelta en mm (10 cm por vuelta con el sedal)
int paso_l_vuelta = 20; // Disminucion de la longitud de cada capa de vueltas
int n_espiras = 15; // Numero de espiras del cable en cada
float diferencia_vel_max = l_vuelta * 5.0; // Diferencia entre longitud y longitud objetivo (en mm) que hace que el motor gire a máxima velocidad


// ------------------------ Variables ROS ------------------------
ros::NodeHandle  nh;
std_msgs::Int32 lMedidaEncoderMsg;
ros::Publisher l_medida_encoder_pub("/cable/longitud", &lMedidaEncoderMsg);

// Callback
void LongitudObjetivoCb(const std_msgs::Int32& msg)
{
  l_objetivo =  msg.data; // Leemos longitud objetivo publicada por ROS
}

// Subscribers
ros::Subscriber<std_msgs::Int32> longitud_objetivo_sub("/guiado/longitud_objetivo", LongitudObjetivoCb);

// TO_DO: incluir mecanimos de seguridad que desactive el motor



/***************************************************************
  // Devolvemos la estimacion de la longitud
  //**************************************************************/
int returnLongitudEncoder()
{
  long temp_long = 0;
  int temp_l_vuelta = l_vuelta;
  int cnt_capas = 0;

  contador_encoder = MyBoard.getMotor1Encoder();
  vueltas = contador_encoder / pulsos_por_vuelta;

  /* for (int i = 1; i < abs(vueltas); i++)
  {
    temp_long += l_vuelta - paso_l_vuelta * cnt_capas;

    if (i % 15 == 0) cnt_capas++;
  }

  temp_long += (temp_long - floor(temp_long)) * temp_l_vuelta;

  if (vueltas < 0) temp_long = -temp_long; */

  temp_long = (long)(vueltas * l_vuelta); // Numero de vueltas por 150 mm por vuelta

  // TO_DO: cambiar el 150 por la ley de la longitud del cable

  Serial.print("Contador: "); Serial.print(contador_encoder); Serial.print("  //  Longitud medida: ");
  Serial.print(temp_long);



  return temp_long;
}


/***************************************************************
  // Setup function
  //**************************************************************/
void setup()
{
  // Inicializamos ROS
  nh.initNode();
  nh.advertise(l_medida_encoder_pub);
  nh.subscribe(longitud_objetivo_sub);

  // Inicializamos control MD25 y motor EMG30
  Serial.begin(115200);           // Set Serial Port to 115200 bps

  MyBoard.resetEncoders();       // Initialize to zero the encoder register
  MyBoard.enableTimeOut(false);  // Disable automatic 2s timeout
  MyBoard.enableController(true);// Enable on-board feedback speed control
  MyBoard.setAcceleration(10);   // Increase acceleration (default = 5)
  MyBoard.setMotor1Speed(128);   // The motor is initially stoped

}
/***************************************************************
  // Loop function
  //**************************************************************/
void loop()
{
  time = millis();

  // PID Controller
  longitud_cable = -returnLongitudEncoder() + longitud_inicial;
  error_k = -(l_objetivo - longitud_cable); // Quitar "-" para invertir sentido de giro de motor
  integral = integral + error_k * deltaT;
  derivativo = (error_k - error_k_1) / deltaT;
  cmd_vel_cable = (Kp * error_k + Ki * integral + Kd * derivativo);
  error_k_1 = error_k;

  // Acotamos cmd_vel en -1 y 1
  cmd_vel_cable = cmd_vel_cable / diferencia_vel_max; // Dividimos cmd_vel entre la diferencia en mm que implica la velocidad máxima de giro
  if (cmd_vel_cable > 1) cmd_vel_cable = 1; // Si supera el valor 1, igualamos a 1
  else if (cmd_vel_cable < -1) cmd_vel_cable = -1; // Si es menor que -1, igualamos a -1

  motor = 128 + cmd_vel_cable * 100; // Velocidad del motor: 128 (parado) + cmd_vel_cable * 72 (vel max: 200 y 52 segun sentido de giro) (IMPORTANTE: maximo --> 128 + 127 * cmd_vel

  // Longitud minima
  if (longitud_cable < long_min && motor < 128) motor = 128; // Evitamos que se siga recogiendo el cable si la longitud está por debajo del minimo
  else if (longitud_cable > long_max && motor > 128) motor = 128; // Evitamos que se siga extendiendo el cable si la longitud está por encima del maximo
  // Modo emergencial
  if (modo_emergencia == true) motor = 128;

  Serial.print("  //  Longitud total: ");   Serial.print(longitud_cable);
  Serial.print("  //  Error: ");   Serial.print(error_k);
  Serial.print("  //  cmd_vel: ");   Serial.println(cmd_vel_cable);
  Serial.print("  //  Velocidad: ");   Serial.println(motor);

  // Establecemos la velocidad del motor
  MyBoard.setMotor1Speed(motor);

  // Publicamos la Longitud del Cable
  lMedidaEncoderMsg.data = longitud_cable;
  l_medida_encoder_pub.publish(&lMedidaEncoderMsg); // Publicamos el mensaje en ROS

  delay(20 - (millis() - time)); // Try to force sampling time to 20 ms
  nh.spinOnce();

}

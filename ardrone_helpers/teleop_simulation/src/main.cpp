#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Empty.h"
#include "std_srvs/Empty.h"
#include <std_msgs/Bool.h>
#include "std_msgs/Int32.h"
#include <math.h>

const int PUBLISH_FREQ = 25;
int accion_ard2;

using namespace std;

bool modo_automatico = false;
bool modo_aterrizaje = false;
bool modo_emergencia = false;
bool modo_apagado = false;

struct TeleopArDrone
{
    ros::Subscriber joy_sub, accion_ard2_sub, modo_aterrizaje_sub;
    ros::Publisher pub_takeoff, pub_land, pub_emergencia, pub_reset, pub_vel, pub_vel_p3at, pub_vel_cable, pub_modo_automatico, pub_modo_aterrizaje;

    bool got_first_joy_msg;

    bool is_flying;
    bool toggle_pressed_in_last_msg;
    bool cam_toggle_pressed_in_last_msg;
    bool control_ard2, control_p3at, control_cable;
    std_srvs::Empty srv_empty;
    std_msgs::Bool modo_automatico_msg, modo_aterrizaje_msg, modo_emergencia_msg;
    std_msgs::Int32 vel_cable_msg;

    ros::NodeHandle nh_;
    geometry_msgs::Twist twist, twist_p3at;
    ros::ServiceClient srv_cl_cam;


    void joyCb(const sensor_msgs::JoyConstPtr joy_msg){

        if (!got_first_joy_msg){
            ROS_INFO("Found joystick with %zu buttons and %zu axes", joy_msg->buttons.size(), joy_msg->axes.size());
            got_first_joy_msg = true;
        }

        // mapping from joystick to velocity
        float scale = 1;
        float scale_p3at = 0.5;

        // Teleoperacion ARD2
        twist.linear.x = scale*joy_msg->axes[1]; // forward, backward
        twist.linear.y = scale*joy_msg->axes[0]; // left right
        twist.linear.z = scale*joy_msg->axes[5]; // up down
        twist.angular.z = scale*joy_msg->axes[2]; // yaw

        // Teleoperacion P3AT
        twist_p3at.linear.x = scale_p3at*sqrt(pow(joy_msg->axes[1],2) + pow(joy_msg->axes[0],2)); // forward, backward
        if (joy_msg->axes[1] < 0){
            twist_p3at.linear.x = - twist_p3at.linear.x;
        }
        twist_p3at.angular.z = scale_p3at*joy_msg->axes[0]; // yaw
        if (twist_p3at.linear.x == 0) {
            twist_p3at.angular.z = 2*scale_p3at*joy_msg->axes[2]; // yaw
        }

        // Teleoperacion Cable
        vel_cable_msg.data = 10*joy_msg->axes[3]; // up down

        // Boton 2: activacion modo automatico
        bool activar_modo_automatico = joy_msg->buttons.at(1);

        // Boton 3: desactivacion modo automatico
        bool desactivar_modo_automatico = joy_msg->buttons.at(2);

        // Boton 4: iniciamos maniobra de aterrizaje automatico
        bool activar_aterrizaje = joy_msg->buttons.at(3);

        // button 5 (L1): dead man switch
        bool dead_man_pressed = joy_msg->buttons.at(4);

        // button 6 (L2): switch emergeny state
        bool boton_emergencia = joy_msg->buttons.at(6);

        // button 0 (select): switch camera mode
        bool cam_toggle_pressed = joy_msg->buttons.at(1);

        // button 8 (R2): control del Pioneer
        bool boton_control_p3at = joy_msg->buttons.at(7);

        // Boton 6: control del cable (solo en modo apagado)
        bool boton_control_cable = joy_msg->buttons.at(5);


        if (modo_apagado == true)
        {
            twist.linear.x = twist.linear.y = twist.linear.z = 0;
            twist.angular.x = twist.angular.y = twist.angular.z = 0;

            twist_p3at.linear.x = twist_p3at.linear.y = twist_p3at.linear.z = 0;
            twist_p3at.angular.x = twist_p3at.angular.y = twist_p3at.angular.z = 0;          

            control_ard2 = false;
            control_p3at = false;            
            modo_emergencia = true;

            if (boton_control_cable)
            {
                if (!control_cable)
                {
                    ROS_INFO("CONTROLANDO DIRECTAMENTE EL CABLE");
                }
                control_cable = true;
            }
            else
            {
                if (control_cable)
                {
                    ROS_INFO("FIN DEL CONTROL DEL CABLE");
                }
                control_cable = false;
                vel_cable_msg.data = 0;
            }
        }
        else if (modo_emergencia == true){
            if (boton_control_p3at)
            {
                ROS_INFO("APAGADO DRONE!!!");
                pub_land.publish(std_msgs::Empty());
                pub_reset.publish(std_msgs::Empty());
                is_flying = false;
                control_ard2 = false;
                control_p3at = false;
                control_cable = false;
                modo_emergencia = true;
                modo_apagado = true;
            }
            else if (!boton_emergencia && !modo_apagado)
            {
                modo_emergencia = false;
                ROS_INFO("Fin emergencia");
                modo_emergencia_msg.data = false;
                pub_emergencia.publish(modo_emergencia_msg);

                control_ard2 = false;
                control_p3at = false;
                control_cable = false;
            }

        }
        else if (modo_automatico == false)
        {
            if (boton_emergencia && dead_man_pressed)
            {
                modo_emergencia = true;
                ROS_INFO("EMERGENCIA!!!");
                modo_emergencia_msg.data = true;
                pub_emergencia.publish(modo_emergencia_msg);
            }
            else if (activar_modo_automatico)
            {
                ROS_INFO("Modo automatico activado!!");
                modo_automatico = true;

                // Mensajes ROS
                modo_automatico_msg.data = modo_automatico;

                // Publicamos mensajes
                pub_vel.publish(twist);
                pub_vel_p3at.publish(twist_p3at);

                pub_modo_automatico.publish(modo_automatico_msg);
                pub_takeoff.publish(std_msgs::Empty());

                is_flying = true;
                control_ard2 = false;
                control_p3at = false;
            }
            else if (activar_aterrizaje == true && !modo_aterrizaje && is_flying)
            {
                modo_aterrizaje = true;
                modo_aterrizaje_msg.data = modo_aterrizaje;
                pub_modo_aterrizaje.publish(modo_aterrizaje_msg);
                control_ard2 = false;
            }
            else if (!is_flying && dead_man_pressed && !modo_aterrizaje)
            {
                ROS_INFO("L1 was pressed, Taking off!");
                pub_takeoff.publish(std_msgs::Empty());
                is_flying = true;
                control_ard2 = true;
                control_p3at = false;
            }
            else if (is_flying && !dead_man_pressed && !modo_aterrizaje){
                ROS_INFO("L1 was released, landing");
                pub_land.publish(std_msgs::Empty());
                is_flying = false;
            }
            else if (boton_control_p3at && !dead_man_pressed && !control_p3at){
                ROS_INFO("R2 pulsado. Controlando el p3at");
                control_ard2 = false;
                control_p3at = true;
            }
            else if (!boton_control_p3at && control_p3at){
                ROS_INFO("R2 liberado. Control del p3at finalizado");
                control_p3at = false;
            }

            if (!cam_toggle_pressed_in_last_msg && cam_toggle_pressed){
                ROS_INFO("Changing Camera");
                if (!srv_cl_cam.call(srv_empty))  ROS_INFO("Failed to toggle Camera");
            }
            cam_toggle_pressed_in_last_msg = cam_toggle_pressed;
        }
        else
        {
            if (boton_emergencia && dead_man_pressed)
            {
                modo_emergencia = true;
                ROS_INFO("EMERGENCIA!!!");
                modo_emergencia_msg.data = true;
                pub_emergencia.publish(modo_emergencia_msg);
            }
            else if (is_flying && dead_man_pressed && desactivar_modo_automatico && !activar_modo_automatico)
            {
                ROS_INFO("Modo automatico desactivado. !Atención, drone volando!");
                modo_automatico = false;
                modo_aterrizaje = false;
                modo_automatico_msg.data = false;
                modo_aterrizaje_msg.data = false;

                pub_modo_automatico.publish(modo_automatico_msg);
                pub_modo_aterrizaje.publish(modo_aterrizaje_msg);
                pub_takeoff.publish(std_msgs::Empty());

                is_flying = true;
                control_ard2 = true;
                control_p3at = false;
            }
            else if (is_flying && dead_man_pressed && activar_aterrizaje == true && !modo_aterrizaje)
            {
                modo_aterrizaje = true;
                modo_aterrizaje_msg.data = modo_aterrizaje;
                pub_modo_aterrizaje.publish(modo_aterrizaje_msg);
            }
        }
    }

    void accionard2Callback(const std_msgs::Int32::ConstPtr& accion_ard2_msg)
    {
        accion_ard2 = accion_ard2_msg->data;
    }

    void modoaterrizajeCallback(const std_msgs::Bool::ConstPtr& msg)
    {
        if (modo_aterrizaje && msg->data == false)
        {
            modo_automatico = false;
            is_flying = false;
            control_ard2 = false;
            control_p3at = false;
        }
        modo_aterrizaje = msg->data;
        modo_aterrizaje_msg.data = msg->data;
    }


    TeleopArDrone(){

        twist.linear.x = twist.linear.y = twist.linear.z = 0;
        twist.angular.x = twist.angular.y = twist.angular.z = 0;

        twist_p3at.linear.x = twist_p3at.linear.y = twist_p3at.linear.z = 0;
        twist_p3at.angular.x = twist_p3at.angular.y = twist_p3at.angular.z = 0;

        vel_cable_msg.data = 0;

        is_flying = false;
        got_first_joy_msg = false;
        control_ard2 = false;
        control_p3at = false;

        joy_sub = nh_.subscribe("/joy", 1,&TeleopArDrone::joyCb, this);
        accion_ard2_sub = nh_.subscribe("guiado/accion_ard2", 1, &TeleopArDrone::accionard2Callback, this);
        modo_aterrizaje_sub = nh_.subscribe("guiado/modo_aterrizaje", 1, &TeleopArDrone::modoaterrizajeCallback, this);
        toggle_pressed_in_last_msg = cam_toggle_pressed_in_last_msg = false;

        pub_takeoff       = nh_.advertise<std_msgs::Empty>("ardrone/takeoff",1);
        pub_land          = nh_.advertise<std_msgs::Empty>("ardrone/land",1);
        pub_emergencia  = nh_.advertise<std_msgs::Bool>("guiado/modo_emergencia",1);
        pub_vel           = nh_.advertise<geometry_msgs::Twist>("guiado/joy_ard2_vel",1);
        pub_reset  = nh_.advertise<std_msgs::Empty>("ardrone/reset",1);
        srv_cl_cam        = nh_.serviceClient<std_srvs::Empty>("ardrone/togglecam",1);
        pub_vel_p3at      = nh_.advertise<geometry_msgs::Twist>("guiado/joy_p3at_vel", 10);
        pub_vel_cable      = nh_.advertise<std_msgs::Int32>("guiado/joy_cable_vel", 10);
        pub_modo_automatico =  nh_.advertise<std_msgs::Bool>("guiado/modo_automatico", 1);
        pub_modo_aterrizaje = nh_.advertise<std_msgs::Bool>("guiado/modo_aterrizaje", 1);
    }

    void send_cmd_vel()
    {
        pub_vel.publish(twist);
    }

    void send_cmd_vel_p3at()
    {
        pub_vel_p3at.publish(twist_p3at);
    }

    void send_cmd_vel_cable(){
        pub_vel_cable.publish(vel_cable_msg);
    }
};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "ardrone_teleop");

    ROS_INFO("Started ArDrone joystick-Teleop");
    ROS_INFO("Press L1 to toggle emergency-state");
    ROS_INFO("Press and hold L2 for takeoff");
    ROS_INFO("Press 'select' to choose camera");

    TeleopArDrone teleop;
    ros::Rate pub_rate(PUBLISH_FREQ);

    while (teleop.nh_.ok())
    {
        ros::spinOnce();
        if ((teleop.control_ard2 == true && !modo_automatico && accion_ard2 <= 2) || modo_emergencia) {
            teleop.send_cmd_vel();
        }
        // TO_DO: Aterrizaje++
        //else if (teleop.control_p3at == true && !modo_automatico && accion_ard2 <= 2) {
        else if (teleop.control_p3at == true  && !modo_automatico && (accion_ard2 == 1 || accion_ard2 == 2 || accion_ard2 == 5)) {
            teleop.send_cmd_vel_p3at();
        }

        if (modo_apagado == true && teleop.control_cable == true)
        {
            teleop.send_cmd_vel_cable();
        }

        pub_rate.sleep();
    }

    return 0;
}

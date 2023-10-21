#include "vex.h"
#include <cmath>
#include <algorithm>

using namespace vex;

// Robot configuration code.

// Brain should be defined by default
brain Brain;

pwm_out leftFrontMotor = pwm_out(Brain.ThreeWirePort.B);
pwm_out leftBackMotor = pwm_out(Brain.ThreeWirePort.F);
pwm_out rightFrontMotor = pwm_out(Brain.ThreeWirePort.D);
pwm_out rightBackMotor = pwm_out(Brain.ThreeWirePort.E);
pwm_out intakeMotor = pwm_out(Brain.ThreeWirePort.A);
pwm_out outtakeMotor = pwm_out(Brain.ThreeWirePort.C);



float leftFront = 0;
float leftBack = 0;
float rightFront = 0;
float rightBack = 0;

controller Controller1 = controller(primary);
controller Controller2 = controller(partner);

float theta = atan2(Controller1.Axis3.position(), Controller1.Axis4.position());
float power = sqrt((Controller1.Axis3.position()^2) + (Controller1.Axis4.position()^2));
float turn = Controller1.Axis1.position();

float sine = sin(theta - M_PI/4);
float cosine = cos(theta - M_PI/4);
float max = std::max(abs(sine),abs(cosine));

// Begin project code

void mecanumRun()
{
  leftFront = power * cosine/max + turn, percent;
  leftBack = power * sine/max - turn, percent;
  rightFront = power * sine/max + turn, percent;
  rightBack = power * cosine/max - turn, percent;

  if((power + abs(turn))> 1)
  {
    leftFront /= power + abs(turn);
    leftBack /= power + abs(turn);
    rightFront /= power + abs(turn);
    rightBack /= power + abs(turn);
  }
  leftFrontMotor.state(leftFront,percent);
  leftBackMotor.state(leftFront,percent);
  rightFrontMotor.state(leftFront,percent);
  rightBackMotor.state(leftFront,percent);
}

void intakeRun()
{
  if(Controller2.ButtonA.pressing())
  {
    intakeMotor.state(50, percent);
  }
  else
  {
    intakeMotor.state(0, percent);
  }
    
}
void outtakeRun()
{
  if(Controller2.ButtonB.pressing())
  {
    outtakeMotor.state(50, percent);
  }
  else
  {
    outtakeMotor.state(0, percent);
  }
    
}

int main() {

 

  // Main Controller loop to set motors to controller axis postiions
  while(true){
   mecanumRun();
   intakeRun();
   outtakeRun();

  }
}

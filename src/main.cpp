#include "vex.h"
#include <cmath>
#include <algorithm>

using namespace vex;

// Robot configuration code.

brain Brain;
// Brain should be defined by default
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);

pwm_out leftFrontMotor = pwm_out(Brain.ThreeWirePort.B);
pwm_out leftBackMotor = pwm_out(Brain.ThreeWirePort.E);
pwm_out rightFrontMotor = pwm_out(Brain.ThreeWirePort.D);
pwm_out rightBackMotor = pwm_out(Brain.ThreeWirePort.F);
pwm_out intakeMotor = pwm_out(Brain.ThreeWirePort.A);
pwm_out outtakeMotor = pwm_out(Brain.ThreeWirePort.C);
digital_in lSwitch = digital_in(Brain.ThreeWirePort.H);


// timer time;

float speed;
float turn;
float strafe;





// Begin project code

void mecanumRun()
{
  leftFrontMotor.state(speed - strafe + turn,percent);
  leftBackMotor.state(speed + strafe + turn,percent);
  rightFrontMotor.state(-speed - strafe + turn,percent);
  rightBackMotor.state(-speed + strafe + turn,percent);
}

void intakeRun()
{
  if(Controller2.ButtonB.pressing())
  {
    intakeMotor.state(100, percent);
  }
  else
  {
    intakeMotor.state(0, percent);
  }
}
void outtakeRun()
{
  
  if(Controller2.ButtonA.pressing() && lSwitch.value() == 1)
  {
    outtakeMotor.state(100, percent);
  }
  else if(Controller2.ButtonX.pressing() && lSwitch.value() == 0)
  {
    outtakeMotor.state(100, percent);
  }
  else
  {
    outtakeMotor.state(0, percent);
  }
}

int main() {

  // vexcodeInit();
  Controller2.Screen.clearScreen();

  // Main Controller loop to set motors to controller axis postiions
  while(true)
  {
    
    speed = Controller1.Axis3.position();
    turn = Controller1.Axis1.position();
    strafe = -Controller1.Axis4.position();
    mecanumRun();
    intakeRun();
    outtakeRun();

  }
}

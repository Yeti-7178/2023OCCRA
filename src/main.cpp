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
  leftFrontMotor.state(speed + turn + strafe,percent);
  leftBackMotor.state(speed - turn - strafe,percent);
  rightFrontMotor.state(speed + turn - strafe,percent);
  rightBackMotor.state(speed - turn + strafe,percent);
}

void intakeRun()
{
  if(Controller2.ButtonA.pressing())
  {
    //time.clear();
    if (/*time.time(seconds) <= 3 &&*/ lSwitch.value() == 0)
    {
      intakeMotor.state(50, percent);
    }
  }
  else if(Controller2.ButtonY.pressing() || lSwitch.value() == 1)
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

  // vexcodeInit();
  Brain.Screen.clearScreen();

  // Main Controller loop to set motors to controller axis postiions
  while(true)
  {
    speed = -Controller1.Axis3.position();
    turn = Controller1.Axis4.position();
    strafe = Controller1.Axis1.position();
    mecanumRun();
    // intakeRun();
    outtakeRun();

  }
}

#include "WPILib.h"

class Robot: public IterativeRobot {
private:
	Joystick*   joy;
	Jaguar* 	flDrive;
	Jaguar* 	rlDrive;
	Jaguar* 	frDrive;
	Jaguar* 	rrDrive;
	Relay*  	horn;
	Relay*  	light;
	RobotDrive*	drive;

	void RobotInit() {
		joy = new Joystick(0);
		flDrive = new Jaguar(0);
		rlDrive = new Jaguar(1);
		frDrive = new Jaguar(2);
		rrDrive = new Jaguar(3);
		horn = new Relay(0, Relay::kForwardOnly);
		light = new Relay(1, Relay::kForwardOnly);
		drive = new RobotDrive(flDrive, rlDrive, frDrive, rrDrive);
	}

	void AutonomousInit() {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {

//  Gamepad
		if (joy->GetRawButton(2) || joy->GetRawButton(3)) horn->Set(Relay::kOn);
		else horn->Set(Relay::kOff);

		float moveValue = ApplyDeadband(joy->GetRawAxis(1), 0.1);
		float rotateValue = ApplyDeadband(-joy->GetRawAxis(4), 0.1) * 0.6 ;
		drive->ArcadeDrive(moveValue, rotateValue, false);

//  Joystick

//		if (joy->GetRawButton(11)) horn->Set(Relay::kOn);
//		else horn->Set(Relay::kOff);

//		float moveValue = ApplyDeadband(-joy->GetY(), 0.1);
//		float rotateValue = ApplyDeadband(-joy->GetZ(), 0.1) * 0.8 ;
//		drive->ArcadeDrive(moveValue, rotateValue, false);

		if (moveValue != 0 || rotateValue != 0) light->Set(Relay::kOn);
		else light->Set(Relay::kOff);

	}

	void TestPeriodic() {
	}

	float ApplyDeadband(float joyValue, float deadband) {
		if (joyValue > 1.0)  joyValue = 1.0;
		if (joyValue < -1.0) joyValue = -1.0;

		if (fabs(joyValue) <= deadband) return 0.0;
		if (joyValue > 0)				return (joyValue - deadband) / (1.0 - deadband);
										return (joyValue + deadband) / (1.0 - deadband);

	}
};

START_ROBOT_CLASS(Robot);

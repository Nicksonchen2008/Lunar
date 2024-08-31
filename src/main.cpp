#include "main.h"
#include "lunar/api.hpp"  

/*	 /$$$$$$  /$$$$$$$$ /$$$$$$$$ /$$   /$$ /$$$$$$$ 
	/$$__  $$| $$_____/|__  $$__/| $$  | $$| $$__  $$
   | $$  \__/| $$         | $$   | $$  | $$| $$  \ $$
   |  $$$$$$ | $$$$$      | $$   | $$  | $$| $$$$$$$/
	\____  $$| $$__/      | $$   | $$  | $$| $$____/ 
	/$$  \ $$| $$         | $$   | $$  | $$| $$      
   |  $$$$$$/| $$$$$$$$   | $$   |  $$$$$$/| $$      
	\______/ |________/   |__/    \______/ |__/      */

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::MotorGroup leftMotors({-18, -19, -20}, pros::MotorGearset::blue); // Left motor group - ports 13 (reversed), 14 (reversed), 15 (reversed)
pros::MotorGroup rightMotors({15, 16, 17}, pros::MotorGearset::blue); // Right motor group - ports 16, 17, 18

// NOT PART OF TEMPLATE (Start)
pros::Imu imu(10);
pros::Motor intakebot(7);
pros::Motor intaketop(-13);
pros::Motor lift(-9);

pros::adi::DigitalOut mogo('A');
// pros::adi::DigitalOut stick('B');
// pros::adi::DigitalOut claw('C');

pros::adi::DigitalIn limitSwitch('F');
pros::adi::AnalogIn lineTracker(8);
// pros::ADIAnalogIn lineTracker(8);

// NOT PART OF TEMPLATE (End)

lunar::Drivetrain drivetrain(&leftMotors, // Left motor group
                              &rightMotors, // Right motor group
                              12.8, // Track width
                              3.25, // Wheel diameter
							  0.75 // Gear ratio with decimals ( Gear Ratios are buggy )
);

lunar::Sensors sensors(&imu, // inertial sensor
					   nullptr,
					   nullptr,
					   nullptr,
					   nullptr
);

// lateral motion controller
lunar::Constraints lateralController(7, // proportional gain (kP)
									 0, // integral gain (kI)
									 0, // derivative gain (kD)
									 3, // anti windup
									 1, // error range
									 100, // error timeout in milliseconds
									 10000 // total timeout in milliseconds
);

// angular motion controller
lunar::Constraints angularController(0.6, // proportional gain (kP)
									 0, // integral gain (kI)
									 0.8, // derivative gain (kD)
									 3, // anti windup
									 1, // error range
									 100, // error timeout in milliseconds
									 2000 // total timeout in milliseconds
);

// swing motion controller
lunar::Constraints swingController(3, // proportional gain (kP)
								   0, // integral gain (kI)
								   0, // derivative gain (kD)
								   3, // anti windup
								   1, // error range
								   100, // error timeout in milliseconds
								   2000 // total timeout in milliseconds
);

lunar::Chassis chassis(drivetrain, sensors, lateralController, angularController, swingController);

// int state;

// int redirectTask(){
// 	while(1){
// 		if(state == FWD) { intaketop.move(127); intakebot.move(127); }
// 		else if(state == REV) { intaketop.move(-127);  intakebot.move(-127); }
// 		else if(state == RED) { intaketop.move(-127); }
// 		else { intakebot.move(0); intaketop.move(0); }
// 		pros::delay(10);
// 	}
// 	return 1;
// }

// Path names: 
// Test, Pos Red, Neg Red, Pos Blue, Neg Blue, Skills
void test(){
	chassis.setHeading(0);
}
void posRed(){
	chassis.setHeading(0);
}
void negRed(){
	chassis.setHeading(0);
}
void posBlue(){
	chassis.setHeading(0);
}
void negBlue(){
	chassis.setHeading(0);
}
void skills(){
	chassis.setHeading(0);
}

int autonState = 0; 

// Auton Selector
void autonSelect(){
    while (1){ pros::delay(20); if(limitSwitch.get_new_press()){ autonState ++; if(autonState>5){ autonState = 0; } }
	switch(autonState){
		case 0: 
			pros::lcd::set_text(2, "Testing");
			break;
		case 1: 
			pros::lcd::set_text(2, "Positive Red");
			break;
		case 2: 
			pros::lcd::set_text(2, "Negative Red");
			break;
		case 3: 
			pros::lcd::set_text(2, "Positive Blue");
			break;
		case 4: 
			pros::lcd::set_text(2, "Negative Blue");
			break;
		case 5: 
			pros::lcd::set_text(2, "Skills");
			break;
		default: 
			pros::lcd::set_text(2, "AUTON");
			break;     
        }
    }
}

void initialize() {
	pros::lcd::initialize();
	pros::Task select(autonSelect);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
/*    /$$$$$$  /$$   /$$ /$$$$$$$$ /$$$$$$  /$$   /$$
	 /$$__  $$| $$  | $$|__  $$__//$$__  $$| $$$  |$$
	| $$  \ $$| $$  | $$   | $$  | $$  \ $$| $$$$| $$
	| $$$$$$$$| $$  | $$   | $$  | $$  | $$| $$ $$ $$
	| $$__  $$| $$  | $$   | $$  | $$  | $$| $$  $$$$
	| $$  | $$| $$  | $$   | $$  | $$  | $$| $$\  $$$
	| $$  | $$|  $$$$$$/   | $$  |  $$$$$$/| $$ \  $$
	|__/  |__/ \______/    |__/   \______/ |__/  \__/    */  

	// NOT PART OF TEMPLATE (Start)
	chassis.setHeading(0);
	// chassis.driveDist(24,0);
	chassis.turnHeading(90);
	// chassis.driveDist(24,0, {.minSpeed = 10, .earlyExit = 1}); // Early Exit for Motion Chaining
	pros::delay(10000000);
	
	// chassis.lSwing(90);
	// chassis.rSwing(90);
	// NOT PART OF TEMPLATE (End)

	switch(autonState){
		case 0: 
			test(); 
			break;
		case 1: 
			posRed(); 
			break;
		case 2: 
			negRed();  
			break;
		case 3: 
			posBlue(); 
			break;
		case 4: 
			negBlue(); 
			break;
		case 5:
			skills();
			break; 
		default: 
			break;
    }
}

void opcontrol() {
	// Boolean variables for driver control
	bool mogoc = false;
	bool clawc = false;
	bool stickc = false;
	bool intakestate = false;

	// Drive Curve Settings
	double leftCurveScale = 0.5; // Left Curve with curve of 0.5
	double RightCurveScale = 0.5; // Right Curve with curve of 0.5

	while(1){
		float lD = (drivetrain.leftMotors->get_position()*(drivetrain.gearRatio/360)*drivetrain.wheelDiameter*3.14);
		float rD = (drivetrain.rightMotors->get_position()*(drivetrain.gearRatio/360)*drivetrain.wheelDiameter*3.14);
		float avg1 = (lD+rD)/2.0;
		pros::lcd::print(2, "avg d: %f", avg1);
		
/*   /$$$$$$$  /$$$$$$$  /$$$$$$ /$$    /$$ /$$$$$$$$ /$$$$$$$ 
	| $$__  $$| $$__  $$|_  $$_/| $$   | $$| $$_____/| $$__  $$
	| $$  \ $$| $$  \ $$  | $$  | $$   | $$| $$      | $$  \ $$
	| $$  | $$| $$$$$$$/  | $$  |  $$ / $$/| $$$$$   | $$$$$$$/
	| $$  | $$| $$__  $$  | $$   \  $$ $$/ | $$__/   | $$__  $$
	| $$  | $$| $$  \ $$  | $$    \  $$$/  | $$      | $$  \ $$
	| $$$$$$$/| $$  | $$ /$$$$$$   \  $/   | $$$$$$$$| $$  | $$
	|_______/ |__/  |__/|______/    \_/    |________/|__/  |__/    */
                                                           
		int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y); // Input from Axis 3
		int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); // Input from Axis 1

		chassis.arcadeCurve(leftY,rightX,leftCurveScale,RightCurveScale); // Arcade drive with drive curves
		// chassis.arcade(leftY,rightX); // Arcade drive without drive curves


/*   /$$$$$$$  /$$$$$$  /$$$$$$  /$$$$$$$$ /$$$$$$  /$$   /$$
	| $$__  $$|_  $$_/ /$$__  $$|__  $$__//$$__  $$| $$$ | $$
	| $$  \ $$  | $$  | $$  \__/   | $$  | $$  \ $$| $$$$| $$
	| $$$$$$$/  | $$  |  $$$$$$    | $$  | $$  | $$| $$ $$ $$
	| $$____/   | $$   \____  $$   | $$  | $$  | $$| $$  $$$$
	| $$        | $$   /$$  \ $$   | $$  | $$  | $$| $$\  $$$
	| $$       /$$$$$$|  $$$$$$/   | $$  |  $$$$$$/| $$ \  $$
	|__/      |______/ \______/    |__/   \______/ |__/  \__/    */
                                                         

		// Mogo clamp
		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            mogoc = !mogoc; 
            mogo.set_value(mogoc);
        }

		// // Stick
		// if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        //     stickc = !stickc; 
        //     stick.set_value(stickc);
        // }
		// // Claw
		// if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        //     clawc = !clawc; 
        //     claw.set_value(clawc);
        // }
		
/*   /$$      /$$  /$$$$$$  /$$$$$$$$ /$$$$$$  /$$$$$$$ 
	| $$$    /$$$ /$$__  $$|__  $$__//$$__  $$| $$__  $$
	| $$$$  /$$$$| $$  \ $$   | $$  | $$  \ $$| $$  \ $$
	| $$ $$/$$ $$| $$  | $$   | $$  | $$  | $$| $$$$$$$/
	| $$  $$$| $$| $$  | $$   | $$  | $$  | $$| $$__  $$
	| $$\  $ | $$| $$  | $$   | $$  | $$  | $$| $$  \ $$
	| $$ \/  | $$|  $$$$$$/   | $$  |  $$$$$$/| $$  | $$
	|__/     |__/ \______/    |__/   \______/ |__/  |__/    */
                                                    
		// Hook + Flexwheel Motors

		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
            intakestate =! intakestate;
        }

		if(intakestate == 0){
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) { intaketop.move(127); intakebot.move(127); }
			else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { intaketop.move(-127);  intakebot.move(-127); }
			else { intakebot.move(0); intaketop.move(0); }
		}
		else if(intakestate == 1){
			if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) { intaketop.move(127); intakebot.move(127); } // WaitUntil linetracker thingy then reverse then setback
		}

		// Wall Stakes Motor
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { lift.move(127); }
			else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { lift.move(-127); }
			else { lift.set_brake_mode_all(pros::v5::MotorBrake::hold); lift.brake(); }

		pros::delay(10);
	}
}
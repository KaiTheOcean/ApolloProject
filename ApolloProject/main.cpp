/*************************************************************
* 1. Name:
*      -Daryl Appleton-
* 2. Assignment Name:
*      Practice 02: Physics simulator
* 3. Assignment Description:
*      Compute how the Apollo lander will move across the screen
* 4. What was the hardest part? Be as specific as possible.
*      -a paragraph or two about how the assignment went for you-
* 5. How long did it take for you to complete the assignment?
*      -total time in hours: reading the assignment, submitting, etc.
**************************************************************/

#include <iostream>  // for CIN and COUT
#include <math.h>
#include <ctime>

using namespace std;

#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)
#define PI       3.14159265359 // Number Pi

/***************************************************
* COMPUTE DISTANCE
* Apply inertia to compute a new position using the distance equation.
* The equation is:
*     s = s + v t + 1/2 a t^2
* INPUT
*     s : original position, in meters
*     v : velocity, in meters/second
*     a : acceleration, in meters/second^2
*     t : time, in seconds
* OUTPUT
*     s : new position, in meters
**************************************************/
double computeDistance(double s, double v, double a, double t)
{
   s = s + (v * t) + ((1.0 / 2.0) * a * t * t);
   return s;
}

/**************************************************
* COMPUTE ACCELERATION
* Find the acceleration given a thrust and mass.
* This will be done using Newton's second law of motion:
*     f = m * a
* INPUT
*     f : force, in Newtons (kg * m / s^2)
*     m : mass, in kilograms
* OUTPUT
*     a : acceleration, in meters/second^2
***************************************************/
double computeAcceleration(double f, double m)
{
   double a = f * m;
   return a;
}

/***********************************************
* COMPUTE VELOCITY
* Starting with a given velocity, find the new
* velocity once acceleration is applied. This is
* called the Kinematics equation. The
* equation is:
*     v = v + a t
* INPUT
*     v : velocity, in meters/second
*     a : acceleration, in meters/second^2
*     t : time, in seconds
* OUTPUT
*     v : new velocity, in meters/second
***********************************************/
double computeVelocity(double v, double a, double t)
{
   v = v + a * t;
   return v;
}

/***********************************************
* COMPUTE VERTICAL COMPONENT
* Find the vertical component of a velocity or acceleration.
* The equation is:
*     cos(a) = y / total
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     y : the vertical component of the total
***********************************************/
double computeVerticalComponent(double a, double total)
{
   double y = cos(a) * total;
   return y;
}

/***********************************************
* COMPUTE HORIZONTAL COMPONENT
* Find the horizontal component of a velocity or acceleration.
* The equation is:
*     sin(a) = x / total
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     x : the vertical component of the total
***********************************************/
double computeHorizontalComponent(double a, double total)
{
   double x = sin(a) * total;
   return x;
}

/************************************************
* COMPUTE TOTAL COMPONENT
* Given the horizontal and vertical components of
* something (velocity or acceleration), determine
* the total component. To do this, use the Pythagorean Theorem:
*    x^2 + y^2 = t^2
* where:
*      x
*    +-----
*    |   /
*  y |  / total
*    | /
*    |/
* INPUT
*    x : horizontal component
*    y : vertical component
* OUTPUT
*    total : total component
***********************************************/
double computeTotalComponent(double x, double y)
{
   double total = sqrt(pow(x, 2) + pow(y, 2));
   return total;
}

/*************************************************
* RADIANS FROM DEGEES
* Convert degrees to radians:
*     radians / 2pi = degrees / 360
* INPUT
*     d : degrees from 0 to 360
* OUTPUT
*     r : radians from 0 to 2pi
**************************************************/
double radiansFromDegrees(double d)
{
   double pi = 3.14159265;
   double r = d * (pi / 180);
   return r;
}

/**************************************************
* PROMPT
* A generic function to prompt the user for a double
* INPUT
*      message : the message to display to the user
* OUTPUT
*      response : the user's response
***************************************************/
double prompt(string x)
{
   double number;
   cout << x;
   cin >> number;
   return number;
}

/*******************************
* DISPLAY DATA
* A functino to output the data
* INPUT
*      seconds:
*      x:
*      y:
*      dx:
*      dy:
*      v:
*      aDegrees:
* OUTPUT
*      string.
********************************/
void displayData(int seconds, double x, double y, double dx, double dy, double v, double aDegrees)
{
   cout.setf(ios::fixed | ios::showpoint);
   cout.precision(2);
   cout << seconds << "s - x, y: (" << x << ", " << y << ")m dx, dy: (" << dx << ", " << dy << ") m/s speed: " << v << "m/s angle: " << aDegrees << "deg\n";
}

/****************************************************************
* MAIN
* Prompt for input, compute new position, and display output
****************************************************************/
int main()
{
   // Prompt for input and variables to be computed
   double dx = prompt("What is your horizontal velocity (m/s)? ");
   double dy = prompt("What is your vertical velocity (m/s)? ");
   double y = prompt("What is your altitude (m)? ");
   double x = 0;
   double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
   double t = 1.0;
   
   cout << endl;

   double ddxThrust;
   double ddyThrust;
   double ddx;
   double ddy;
   double v;

   double aRadians = radiansFromDegrees(aDegrees); // Angle in radians

   double accelerationThrust = THRUST / WEIGHT; // Acceleration due to thrust

   // Go through the simulator five times
   for (int i = 0; i < 5; i++)
   {
      ddxThrust = computeHorizontalComponent(aRadians, accelerationThrust); // Horizontal acceleration due to thrust
      ddx = ddxThrust; // Total horizontal acceleration
      ddyThrust = computeVerticalComponent(aRadians, accelerationThrust); // Vertical acceleration due to thrust
      ddy = ddyThrust + GRAVITY; // Total vertical acceleration
      dx = computeVelocity(dx, ddx, t); // Find horizontal velocity
      dy = computeVelocity(dy, ddy, t); // Find vertical velocity
      x = computeDistance(x, dx, ddx, t); // Find x position
      y = computeDistance(y, dy, ddy, t); // Find y position
      v = computeTotalComponent(dx, dy); // Find the total velocity

      // Output
      cout.setf(ios::fixed | ios::showpoint);
      cout.precision(2);

      displayData(t, x, y, dx, dy, v, aDegrees);

    }

   return 0;
}

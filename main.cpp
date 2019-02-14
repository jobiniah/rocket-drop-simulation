// SLR_sim.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "math.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define pi 3.14159265


int main() 
{
	ofstream f;
	f.open("ouput");
	double x = 0;
	double dx = 0;
	double y = 0;
	double dy = 0;
	double V = 0;
	double a = 0;
	double mass = 7.815;
	double thrust;
	double burn_rate = 0.015821;
	double drag = 0;
	double Pressure = 101.325;
	double g;
	double Rho; //Density
	double CdS = 0.42;
	int stage = 1;
	double t = 0;
	double dt = 0.001;
	double t_ignition;
	double distance_needed;
	while (true) //ascent
	{
		if (y<11000) //calculate density of air
		{
			Rho = -((6.43266*pow(10, -9)*pow(288.14 - (0.007788 * y), 5.265))) / (y - 44397.5);
		}
		if (11000 <= y && y <= 25000)
		{
			Rho = 2.05555*exp(-0.0001884*y);
		}
		if (25000 < y)
		{
			Rho = (1.15061 * pow(10, 30)) / (pow(((0.003588*y) + 141.89), 11.388)*(y + 47454.8));
		}
		if (t < 1) {
			mass = mass - (4 * burn_rate * dt);
			thrust = 4 * (192 + (162.909 - 192)*Pressure / 101.325);
		}
		else if (stage == 3 && t < t_ignition +1)
		{
			mass = mass - (burn_rate * dt);
			thrust = (192 + (162.909 - 192)*Pressure / 101.325);
		}
		else
		{
			thrust = 0;
		}
		f << t << "," << y << ",\n";
		//cout << t << " " << y << " " << V << " " << thrust << endl;
		Pressure = 101.325 * exp(-y / 5000);
		drag = (CdS * 0.5 * Rho * pow(V, 2)) / 1000;
		g = ((6.67408*pow(10, -11)*5.2915158*pow(10, 22)) / pow(600000 + y, 2));
		a = (thrust / mass) - g - (drag / mass);
		V += a*dt;
		dy = V;
		y += dy*dt;
		t += dt;
		distance_needed = -V*V / a + 1 / 2 * 9.81*pow(V / a, 2);
		if (abs(distance_needed-y) < 0.1 && stage == 2)
		{
			stage = 3;
			t_ignition = t;
			cout << "t=" << t_ignition << endl;
		}
		if (V < 0 && stage == 1)
		{
			cout << "t=" << t << " y=" << y << endl;
			mass = 4.295;
			stage = 2;
		}
		if ((int)y == 0 && t > 1)
		{
			break;
		}
	}
	f.close();
	system("Pause");
	return 0;
}

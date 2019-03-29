// SLR_sim.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "math.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define pi 3.14159265
double ThrustCurveD11(double time)
{
	double t[] = { 0, 0.033, 0.084, 0.144, 0.214, 0.261, 0.289, 0.311, 0.325, 0.338, 0.356, 0.398, 0.48, 0.618, 0.761, 0.955, 1.222, 1.402, 1.54, 1.701, 1.784, 1.803, 1.834, 1.86 };
	double T[] = { 0, 2.393, 5.783, 12.17, 20.757, 24.35, 26.01, 23.334, 18.532, 14.536, 12.331, 10.72, 9.303, 8.676, 8.247, 8.209, 7.955, 8.319, 8.291, 8.459, 8.442, 6.239, 3.033, 0 };
	for (int i = 0; i < sizeof(t) / sizeof(t[0]); i++)
	{
		if (abs(time - t[i]) < 0.001)
		{
			return T[i];
		}
		if (time < t[i])
		{
			return ((T[i] - T[i - 1]) / (t[i] - t[i - 1]))*time + T[i-1]- ((T[i] - T[i - 1]) / (t[i] - t[i - 1]))*t[i-1];
		}
	}
	return 0;
}

double ThrustCurveE12(double time)
{
	double t[] = { 0, 0.052, 0.096, 0.196, 0.251, 0.287, 0.300, 0.344, 0.370, 0.400, 0.500, 0.600, 0.700, 0.800, 0.900, 1.000, 1.101, 1.200, 1.300, 1.400, 1.500, 1.600, 1.700, 1.800, 1.900, 2.000, 2.100, 2.200, 2.300, 2.375, 2.400, 2.440 };
	double T[] = { 0, 5.045, 9.910, 24.144, 31.351, 32.973, 29.910, 17.117, 14.414, 12.973, 11.712, 11.171, 10.631, 10.09, 9.73,  9.55, 9.91, 9.55, 9.73, 9.73, 9.73, 9.73, 9.55, 9.73, 9.73, 9.55, 9.55, 9.73, 9.19, 9.37, 5.95, 0.0 };
	for (int i = 0; i < sizeof(t) / sizeof(t[0]); i++)
	{
		if (abs(time - t[i]) < 0.001)
		{
			return T[i];
		}
		if (time < t[i])
		{
			return ((T[i] - T[i - 1]) / (t[i] - t[i - 1]))*time + T[i - 1] - ((T[i] - T[i - 1]) / (t[i] - t[i - 1]))*t[i - 1];
		}
	}
	return 0;
}

double ThrustCurveE30(double time)
{
	double t[] = { 0, 0.01, 0.02, 0.05, 0.10, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50, 0.55, 0.60, 0.65, 0.70, 0.75, 0.80, 0.85, 0.90, 0.91, 0.93, 0.95, 0.97, 1.00 };
	double T[] = { 0, 49, 49, 46, 44, 43, 42, 41, 40, 39, 38, 37, 35, 33, 32, 31, 30, 27, 25, 20, 19, 12, 5, 1, 0 };
	for (int i = 0; i < sizeof(t) / sizeof(t[0]); i++)
	{
		if (abs(time - t[i]) < 0.001)
		{
			return T[i];
		}
		if (time < t[i])
		{
			return ((T[i] - T[i - 1]) / (t[i] - t[i - 1]))*time + T[i - 1] - ((T[i] - T[i - 1]) / (t[i] - t[i - 1]))*t[i - 1];
		}
	}
	return 0;
}

double ThrustCurveF15(double time)
{
	double t[] = { 0, 0.063, 0.118, 0.158, 0.228, 0.340, 0.386, 0.425, 0.481, 0.583, 0.883, 1.191, 1.364, 1.569, 1.727, 2.00, 2.39, 2.68, 2.96, 3.25, 3.35, 3.39, 3.40 };
	double T[] = { 0, 2.127, 4.407, 8.359, 13.68, 20.82, 26.75, 25.38, 22.19, 17.93, 16.11, 14.59, 15.35, 15.65, 14.74, 14.28, 13.68, 13.08, 13.07, 13.05, 13.0, 7.30, 0.00 };
	for (int i = 0; i < sizeof(t) / sizeof(t[0]); i++)
	{
		if (abs(time - t[i]) < 0.001)
		{
			return T[i];
		}
		if (time < t[i])
		{
			return ((T[i] - T[i - 1]) / (t[i] - t[i - 1]))*time + T[i - 1] - ((T[i] - T[i - 1]) / (t[i] - t[i - 1]))*t[i - 1];
		}
	}
	return 0;
}

int main() 
{
	ofstream f;
	f.open("ouput");
	double x = 0;
	double dx = 0;
	double y = 100;
	double dy = 0;
	double yi = 30;
	double a = 0;
	double mass = 0.6;
	double thrust = 0;
	double burn_time = 1.9;
	double burn_rate = 0.015821;
	double drag = 0;
	double Pressure = 101.325;
	double g = 9.81;
	double Rho = 1.225; //Density
	double Cd = 0.42;
	double A = pi*(0.076*0.076) / 4;
	int stage = 1;
	double t = 0;
	double dt = 0.001;
	double ti;
	bool ignition = false;
	double V = 0;
	while (true) 
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
		if (y < yi && ignition == false)
		{
			ti = t;
			ignition = true;
		}
		if (ignition)
		{
			thrust = ThrustCurveE30(t - ti);
			//thrust = 0;
		}
		f << t << "," << y << "," << thrust << "," << V << ",\n";
		//cout << "t=" << t << " y=" << y << " V=" << V << " T=" << thrust << endl;
		Pressure = 101.325 * exp(-y / 5000);
		drag = (Cd * A * 0.5 * Rho * pow(V, 2)) / 1000;
		g = ((6.67408*pow(10, -11)*5.2915158*pow(10, 22)) / pow(600000 + y, 2));
		a = (thrust / mass) - g - (drag / mass);
		V += a*dt;
		dy = V;
		y += dy*dt;
		t += dt;
		if (y < 0 && thrust == 0)
		{
			break;
		}
	}
	f.close();
	system("Pause");
	return 0;
}


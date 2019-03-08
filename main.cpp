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
	double yr = 100;
	double y = 0;
	double dy = 0;
	double a = 0;
	double mass = 1;
	double thrust = 10;
	double thrustr = 100;
	double burn_rate = 0.015821;
	double drag = 0;
	double Pressure = 101.325;
	double g = 9.81;
	double Rho = 1.225; //Density
	double Cd = 0.42;
	double A = 0.1;
	double t = 0;
	double dt = 0.001;
	double Vi = -sqrt((2 * mass * g) / (Rho * A * Cd));
	double V = Vi;
	for (int i = 0; i < yr; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			y = i;
			thrust = j;
			t = 0;
			V = Vi;
			a = 0;
			cout << "y=" << y << " thrust=" << thrust;
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
				if (t > 1) {
					thrust = 0;
				}
				//f << t << "," << y << ",\n";
				//cout << t << " " << y << " " << V << " " << thrust << endl;
				Pressure = 101.325 * exp(-y / 5000);
				drag = (Cd * A * 0.5 * Rho * pow(V, 2)) / 1000;
				g = ((6.67408*pow(10, -11)*5.9722*pow(10, 24)) / pow(6371000 + y, 2));
				a = (thrust / mass) - g - (drag / mass);
				V += a*dt;
				dy = V;
				y += dy*dt;
				t += dt;
				if (y < 0 && abs(V) > 0.1) {
					cout << " BOOM!" << endl;
					break;
				}
				if (y < 0.1 && abs(V) < 1 && t >= 1)
				{
					cout << " a=" << a << " V=" << V << " y=" << y << " t=" << t << endl;
					break;
				}
			}
		}
	}
	f.close();
	system("Pause");
	return 0;
}


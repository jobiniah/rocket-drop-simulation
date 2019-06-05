import csv
import numpy as np

def import_Thrust_Curve():
    times = []
    Thrust = []
    with open('C:/Users/Jonat/Documents/Rocket Sim/ESTE F15 data.csv') as csvfile:
        spamreader = csv.reader(csvfile, delimiter=',')
        for row in spamreader:
            times.append(row[0])
            Thrust.append(row[1])
    Thrust[0]=0.0
    times[0]=0.0
    for i in range(0, len(times)):
        Thrust[i] = float(Thrust[i])
        times[i] = float(times[i])
    return Thrust, times


# Adjust thrust time spacing
def adjustThrustCurve(dt, sigfigs):
    Thrust, times = import_Thrust_Curve()
    t = [0.0]
    i = 0
    #t=matlabFill(0.0, max(times), dt, sigfigs)
    
    while (max(t) < max(times)):
        roundedVal=np.round(max(t) + dt,sigfigs)
        t.append(roundedVal)
    
    Th = np.interp(t, times, Thrust)
    Thrust = Th
    times = t
    return Thrust, times

def analysis(y,v,t,i):
    tzero=(0-y[i-1])*(t[i]-t[i-1])/(y[i]-y[i-1])+t[i-1]
    vzero=(tzero-t[i-1])*(v[i]-v[i-1])/(t[i]-t[i-1])+v[i-1]
    return vzero, tzero

def matlabFill(start, stop, dt, sigfigs):
    range=[start]
    while(max(range) < stop):
        roundedVal=np.round(max(range) + dt,sigfigs)
        range.append(roundedVal)
    return range
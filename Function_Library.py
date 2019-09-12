import csv
import numpy as np

def import_Thrust_Curve(name):
    times = []
    Thrust = []
    with open('data/'+name) as csvfile:
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

def massLosses(t, Th, delay, mLost=10):
    mLoss={}
    integrated=0
    for i in range(len(t)-1):
        integrated+=(Th[i] + Th[i+1])/2
    for i in range(len(t)-1):
        mLoss[ t[i]+delay ]=Th[i] * mLost / integrated
    return mLoss

# Adjust thrust time spacing
def adjustThrustCurve(name, dt, sigfigs):
    Thrust, times = import_Thrust_Curve(name)
    t = [0.0]
    i = 0    
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

if __name__=='__main__':
    print("in Function Library")

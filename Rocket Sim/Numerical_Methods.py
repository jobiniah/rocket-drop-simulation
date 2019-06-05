#Numerical Method, setup
import numpy as np
import Drop_Sim
import Function_Library as lib
import matplotlib.pyplot as py

#import thrust curve

class Thrust_Curve:
    def __init__(self, dt, sigfigs,delay):
        self.Thrust, self.times=lib.adjustThrustCurve(dt, sigfigs)
        self.dt=dt
        self.sigfigs=sigfigs
        self.min=delay
        self.max=delay+max(self.times)
class Initial_Conditions:
    def __init__(self):
        self.m=1#input("Please input rocket mass in kg \n")
        self.y=[100.0]#[input("please input drop height in m \n")]
        self.a=[ -9.81 ]
        self.v=[0]
        self.t=[0.0]
        self.d=0.3
        self.A=np.pi*d**2/4


Range=[ [0] ]
Range.append([0,20])
#start, stop, dt = 0,20,0.1

Vterm=-1*Drop_Sim.terminalVel(25)

vzero,tzero=[0],[0]

for i in range(1,2):
    timeRange=lib.matlabFill(Range[i][0],Range[i][1],10**(-1*i),i)
    print(timeRange)
    F15=Thrust_Curve(10**(-1*i), i, 0)
    tzero.append([])
    vzero.append([])
    for j in range( len(timeRange) ):
        delay=timeRange[j]
        F15.min=delay
        F15.max=delay+max(F15.times)
        vz,tz=Drop_Sim.main(F15)
        vzero[i].append( vz )
        tzero[i].append( tz )
    print(vzero)
    index=(vzero[i]==max(vzero[i]))
    peakValue=np.where(index)[0]
    print('{}, {}'.format(timeRange[peakValue[0]-1],timeRange[peakValue[0]+1]))
    Range.append( [timeRange[peakValue[0]-1],timeRange[peakValue[0]+1]] )
    py.plot(timeRange,vzero[i])
    py.show()
    print(Range)


        
    

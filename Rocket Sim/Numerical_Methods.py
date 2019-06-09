#Numerical Method, setup
import numpy as np
import Drop_Sim
import Function_Library as lib
import matplotlib.pyplot as py

#import thrust curve

class Thrust_Curve:
    def __init__(self, name, dt, sigfigs,delay):
        self.name=name
        self.Thrust, self.times=lib.adjustThrustCurve(name, dt, sigfigs)
        self.dt=dt
        self.sigfigs=sigfigs
        self.min=delay
        self.max=np.round(.1,sigfigs)
class Initial_Conditions:
    def __init__(self):
        self.m=.7#input("Please input rocket mass in kg \n")
        self.y=[100.0]#[input("please input drop height in m \n")]
        self.a=[ -9.81 ]
        self.v=[0]
        self.t=[0.0]
        self.d=.076
        self.A=np.pi*self.d**2/4

def main(motorName):
    Range=[ [0] ]
    Range.append([0,20])
    
    vzero,tzero=[0],[0]
    
    for i in range(1,4):
        timeRange=lib.matlabFill(Range[i][0],Range[i][1],10**(-1*i),i)
        motor=Thrust_Curve(motorName, 10**(-1*i), i, 0)
        tzero.append([])
        vzero.append([])
        for j in range( len(timeRange) ):
            delay=timeRange[j]
            motor.min=delay
            motor.max=np.round(delay+max(motor.times),motor.sigfigs)
            vz,tz=Drop_Sim.main(motor)
            vzero[i].append( vz )
            tzero[i].append( tz )
        #print(vzero)
        index=(vzero[i]==max(vzero[i]))
        peakValue=np.where(index)[0]
        #print(timeRange)
        #print(vzero[i])
        #print(peakValue)
        #print(timeRange[peakValue[0]])
        #print("Here")
        #print(timeRange[peakValue[0]+1])
        #print('{}, {}'.format(timeRange[peakValue[0]-1],timeRange[peakValue[0]+1]))
        Range.append( [timeRange[peakValue[0]-2],timeRange[peakValue[0]+2]] )
        py.plot(timeRange,vzero[i])
        py.show()
        #print(Range)
        
    return max(vzero[len(vzero)-1]), timeRange[peakValue[0]]

main('ESTE C11.csv')

        
    

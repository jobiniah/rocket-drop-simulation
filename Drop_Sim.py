import numpy as np
import Function_Library as lib

m=1
y=[100.0]
a=[ -9.81 ]
v=[0]
t=[0.0]
d=0.3
A=np.pi*d**2/4

def main(M):
    m,y,v,t=1,[100.0],[0],[0.0]
    a=[-1*calcFg(y[0],m)]
    i=0
    dt=M.dt
    while(y[i]>0):
        newT=t[i]+dt
        t.append(np.round(newT,M.sigfigs))
        a.append( sumF(y[i],v[i],M,t[i],m)/m )
        v.append( a[i+1]*dt+v[i] )
        y.append( v[i+1]*dt+y[i] )
        
        i+=1
    vzero,tzero=lib.analysis(y,v,t,i)
    return vzero, tzero

def sumF(Y, V, M, T,m):
    sumF=0
    
    sumF-=calcFg(Y,m)
    
    sumF+=calcFd(V,Y)
    
    sumF+=calcFth(M, T,m)
    return sumF


def calcFg(Y, m):
    g = ((6.67408 * np.power(10.0, -11) * 5.2915158 * pow(10, 22)) / pow(600000 + Y, 2))
    W = float(m) * g
    return W


def calcFd(V, Y):
    Cd = 0.42  # drag coefficient
    Rho = calcRho(Y)
    drag_Force = (Cd * A * 0.5 * Rho * pow(V, 2))
    if(V>0):
        drag_Force=-1*drag_Force #Change Direction of drag_Force
        
    return drag_Force


def calcRho(Y):
    if (Y < 11000):  # calculate density of air
        Rho = -((6.43266 * pow(10, -9) * pow(288.14 - (0.007788 * Y), 5.265))) / (Y - 44397.5)
    elif ((11000 <= Y) & (Y <= 25000)):
        Rho = 2.05555 * np.exp(-0.0001884 * Y)
    elif (25000 < Y):
        Rho = (1.15061 * pow(10.0, 30)) / (pow(((0.003588 * Y) + 141.89), 11.388) * (Y + 47454.8))
    return Rho


def calcFth(M, T, m):
    if( (T>=M.min) & (T<=M.max) ):
        m=float(m)-M.mLoss[T]
        trel=np.round(T-M.min,M.sigfigs)
        index=(M.times==trel)
        FTh=M.Thrust[index]
        FTh=FTh[0]
    else:
        FTh=0
    return FTh

if __name__=="__main__":
    print("in Drop Sim")
    import Numerical_Methods as numeth
    motor=numeth.Thrust_Curve('ESTE F15 data.csv', .1, 1, 4.8)
    vz,tz,t,y=main(motor)
    print(vz)
    print(tz)
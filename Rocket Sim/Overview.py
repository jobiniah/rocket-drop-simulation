import Numerical_Methods as nm
#
motorArray=['ESTE F15 data.csv', 'ESTE C6.csv', 'ESTE C11.csv','ESTE D12.csv', 'ESTE D11.csv','ESTE E9.csv', 'ESTE E12.csv', 'ESTE E16.csv', 'ESTE E30.csv']

vzero,delay=[],[]

for i in range(len(motorArray)):
    vzero.append(1)
    delay.append(1)
    vzero[i], delay[i]=nm.main( motorArray[i] )
    print('motor {}, {} min velocity, {} delay \n'.format(motorArray[i], vzero[i], delay[i]))

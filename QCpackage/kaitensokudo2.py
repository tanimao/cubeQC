import matplotlib.pyplot as plt
import numpy as np 

#tmax1 = 1

#V = 18
#a0 = V*V/45
a0 = 13.68
V = (45*a0)**0.5
t0 = 45/V
print('V = ', V, ', a0 = ', a0, 't0 = ', t0)


a1 = a0
a2 = a0
#v0 = a1 * tmax1

v0 = 20.16 

tmax1 = v0 / a1
tau = t0 - tmax1
dt = tau * (V-v0)/v0
tmax2 = tmax1 + 2*tau + dt

tcut = 2*t0 + dt
vcut = v0 - a2*(tcut - tmax2)

t1 = np.arange(0,tmax1, 0.001)
v1 = a1*t1

tconst = np.arange(tmax1,tmax2, 0.001)
vconst = v0* (tconst **0)

t2 = np.arange(tmax2, tcut, 0.01)
v2 = v0 - a2*(t2-tmax2)


plt.plot(t1, v1)
plt.plot(tconst, vconst)
plt.plot(t2, abs(v2))

x= 0.5*v0*tmax1 + vcut*(tcut-tmax2) + 0.5*(v0-vcut)*(tcut-tmax2) + v0 *(tmax2-tmax1)
print ('the integral is ', x)
print ('tmax1 is ', tmax1)
print ('last velocity is ', vcut)
print ('tcut is ', tcut)
print ('v0 is ', v0)
plt.show()

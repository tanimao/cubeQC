import numpy as np
from numba.decorators import jit
import time

@jit
def sine(theta):

    a = np.sin(theta)
    return a

start = time.time()
for x in range(100000):
    for i in range(16):
        theta = i*np.pi/8
       # print(theta)
        A = sine(theta)
        #A = np.sin(theta)
        #print('sin(pi/3) = {}'.format(A)) 
print('time is {} sec'.format(time.time()-start))

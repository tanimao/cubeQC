import time

import hello
x = hello.greet(2)
print(x)
y = hello.fine()
print(y)


start = time.time()
import test1223
test1223.test1223()
print("root time = {} sec".format(time.time()-start))
start2 = time.time()
import minimizer
minimizer.minimizer()
print("minimization time = {} sec".format(time.time()- start2))


start = time.time()
#import test1223
test1223.test1223()
print("root time = {} sec".format(time.time()-start))

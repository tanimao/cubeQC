import numpy as np
import matplotlib.pyplot as plt
import signal
signal.signal(signal.SIGINT, signal.SIG_DFL)

#import cv2

date = '1114' 
gorb = 'good'
finCut = open("{}{}1cut.txt".format(date,gorb),'r')

dat = finCut.read()
print(dat)

l1 = dat.split("\n")
l1.pop(-1)
print(l1)


isurvive = len(l1)

print("the number of survived cubes is {}.".format(isurvive))

n_cubeSur = []

for num in l1:
    n_cubeSur.append(int(num))
    print("survived cube is {}.".format(num))
print(n_cubeSur)

for i in n_cubeSur:
    print("reading cube {}".format(i))

    
#for i in range(70):
    

    for j in range(6): 

        saveName = gorb+str(i+1)+'_'+str(j+1)
        #saveName = 'bad1_1'
        file_circle = '../../files/1114'+gorb+'1/th150/' + saveName + '.npy'
        fig = plt.figure(figsize = (8,6))
        hist_circle = np.load(file_circle)
        
        if hist_circle.any() == 0.:
            
            print(hist_circle)            
            file = open('{}{}1hist2.txt'.format(date, gorb),'a')
            
            file.write(saveName +' '+str(0)+' '+str(0)+' '+str(0)+'\n')

            file.close()
        else : 
            
            print('pic is {}.'.format(saveName))
            sum_hist = 0
            sum_histw = 0
            sum_all = 0
            weight = 5
            for ihist, num_hist in enumerate(hist_circle):
                sum_all = sum_all + num_hist
                
                if ihist >= 20 and ihist <= 59:
                    sum_histw = sum_histw + num_hist
                    sum_hist  = sum_hist  + num_hist
                if ihist >= 60 and ihist <= 200:
                    sum_histw = sum_histw + num_hist * weight
                    sum_hist = sum_hist + num_hist
            
                
            file = open('{}{}1hist1.txt'.format(date,gorb),'a')
            
            file.write(saveName +' '+str(sum_hist[0])+' '+str(sum_histw[0])+' '+str(sum_all[0])+'\n')
            file.close()
            
            
            plt.plot(hist_circle)
            plt.title('histogram for circle ({} {}_{})'.format(gorb, i+1, j+1))
            plt.xlim([0,256])
#            plt.show()


finCut.close()

import numpy as np
import matplotlib.pyplot as plt
import signal
signal.signal(signal.SIGINT, signal.SIG_DFL)

#import cv2

for i in range(70):


    for j in range(6): 

        goodorbad = 'bad'
        saveName = goodorbad+str(i+1)+'_'+str(j+1)
        #saveName = 'bad1_1'
        file_circle = '../../files/1108'+goodorbad+'1/th150/' + saveName + '.npy'
        fig = plt.figure(figsize = (8,6))
        hist_circle = np.load(file_circle)
        
        if hist_circle.any() == 0.:
            
            print(hist_circle)            
            file = open('1108{}1hist1.txt'.format(goodorbad),'a')
            
#            file.write(saveName +' '+str(0)+' '+str(0)+' '+str(0)+'\n')

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
                if ihist >= 60:
                    sum_histw = sum_histw + num_hist * weight
                    sum_hist = sum_hist + num_hist
            
                
            file = open('1108{}1hist1.txt'.format(goodorbad),'a')
            
 #           file.write(saveName +' '+str(sum_hist[0])+' '+str(sum_histw[0])+' '+str(sum_all[0])+'\n')
            file.close()
            
            
            plt.plot(hist_circle)
            plt.title('histogram for circle')
            plt.xlim([0,256])
            plt.show()

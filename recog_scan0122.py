# coding: utf-8 

#Python の実行を Ctrl-C で終了させる（SIGINTに反応する）
import signal
signal.signal(signal.SIGINT, signal.SIG_DFL)

import time

import cv2
import numpy as np
import matplotlib.pyplot as plt
#from matplotlib import pyplot as plt
from matplotlib.patches import Polygon
import matplotlib.patches as patches
from numba.decorators import jit

from package_cube import manualminimize
from package_cube import figureInfo
from package_cube import resizeFigure
from package_cube import extractionRGB 
from package_cube import trimmFig
from package_cube import houghCircle
from package_cube import searchCenter
from package_cube import outline
from package_cube import pixVal
from package_cube import houghLine
from package_cube import findThres
from package_cube import detectHole
from package_cube import choiceOutline



##############################################################################
def main():
        start = time.time()
        for i in range(10):

      #  for j in range(6):
           
     #       saveName  = 'good'+str(i+1)+'_'+str(j+1) 
            saveName  = '1119_test'+str(i+1)
            ImageName = 'mao_pictures/pic1119test/'+ saveName + '.jpg' 
            
            imgG= cv2.imread(ImageName,0)
            img = cv2.imread(ImageName,1)
            img = cv2.split(img)
            img = cv2.merge((img[2],img[1],img[0])) # => bgr
    #        img2 = cv2.merge((img[2],img[1],img[0])) # => bgr
            print("image is '{}'.".format(ImageName))
            figureInfo.get_FigureInfo(img)
    
    
    
            img =         resizeFigure.set_ResizeFigure(img,1)
            img_sample =  resizeFigure.set_ResizeFigure(img,1)
            img_sample2 = resizeFigure.set_ResizeFigure(img,1)
            img_sample3 = resizeFigure.set_ResizeFigure(img,1)
            # BGRでの白色抽出
            result =         extractionRGB.get_ExtractionRGB(img,40)
            result_sample =  extractionRGB.get_ExtractionRGB(img_sample,40)
            result_sample2 = extractionRGB.get_ExtractionRGB(img_sample2,40)
            result_sample3 = extractionRGB.get_ExtractionRGB(img_sample3,40)
            
            
            # ハフ変換による円検出
            circleInfo = houghCircle.detect_HoughCircles(saveName,img_sample,img,img_sample2,img_sample3, 1)
            #################################### 
            xhole = circleInfo[0]
            yhole = circleInfo[1]
            rhole = circleInfo[2]
            #hole_hist = [circleInfo[3], circleInfo[4], circleInfo[5]]
            vote  = circleInfo[3]
            edges2 = circleInfo[4]
            ####################################
            trimmForHole = trimmFig.get_TrimmedFigure(img_sample,int(yhole-rhole)-30,int(yhole+rhole)+30,int(xhole-rhole)-30,int(xhole+rhole)+30) # 左上0,0: y1,y2,x1,x2
            # 輪郭検出
 
            print("trimmed area is (x0,y0),(x1,y1) = ({}, {}), ({}, {})"
                .format(int(xhole-rhole)-30, int(yhole-rhole)-30,
                 int(xhole+rhole)+30, int(yhole+rhole)+30))

            trimmForHole2 = trimmForHole
            #######################
            colmean = findThres.findThreshold(trimmForHole, rhole)
            #######################
            holestart = time.time()
            xholecenter_, yholecenter_ = detectHole.detect_HoleCenter(trimmForHole, trimmForHole2, colmean, rate=0.7)
            print('hole time : {} sec'.format(time.time()-holestart))
            
            xholecenter = xholecenter_ + xhole - rhole -30
            yholecenter = yholecenter_ + yhole - rhole -30

            searchCenter.SearchCenter(xholecenter, yholecenter, rhole, edges2)
    
            #############################################################
            sizetime = time.time()
            cube_size = outline.detect_Outline_wColFigure(result_sample, 1, 500)
             #cube_size :: [size_x, size_y, max_x, max_y, min_x, min_y]
            #                 0        1     2      3      4       5
            
            outlinexmax = cube_size[2]
            outlinexmin = cube_size[4]
            outlineymax = cube_size[3]
            outlineymin = cube_size[5]
            #############################################################
            
            #print(cube_size)
    
    
            pixVal.get_PixelValues(saveName, img_sample, 1, cube_size)
            #'''
            ########################追加分    
#            extract =        trimmFig.get_TrimmedFigure(img,cube_size[5]-10,cube_size[3]+6,cube_size[4]-10,cube_size[2]+10) # 左上0,0: y1,y2,x1,x2
 #           extract_sample = trimmFig.get_TrimmedFigure(img_sample, cube_size[5]-10,cube_size[3]+6,cube_size[4]-10,cube_size[2]+10) # 左上0,0: y1,y2,x1,x2
            extract = img
            extract_sample = img_sample
            xylist = houghLine.hough_lines(extract_sample, extract)
            xmax = xylist[0] 
            xmin = xylist[1] 
            ymax = xylist[2] 
            ymin = xylist[3] 
            xsize= xmax - xmin
            ysize= ymax - ymin
            print("cube size by line detection : {},{}".format(xsize,ysize))
            ########################    

            print('outline(xmin, ymin, xmax, ymax); houghline(xmin, ymin, xmax, ymax) is \n ({}, {}, {}, {}); ({}, {}, {}, {})'
                    .format(outlinexmin, outlineymin, outlinexmax, outlineymax, 
                            xmin, ymin, xmax, ymax))
            chosen = choiceOutline.choice_Outline(extract_sample, outlinexmin, outlineymin, outlinexmax, outlineymax, 
                            xmin, ymin, xmax, ymax)
    
            #chosenOutline : [chosenxmax, chosenxmin, chosenymax, chosenymin]
            xmaxeff = chosen[0]
            xmineff = chosen[1]
            ymaxeff = chosen[2]
            ymineff = chosen[3]
            xsizeeff = xmaxeff - xmineff
            ysizeeff = ymaxeff - ymineff
            print("effective cube size : {}, {}".format(xsizeeff, ysizeeff))
            print('size_time : {} sec'.format(time.time()-sizetime))
            manualminimize.manualminimization()

            elapsed_time = time.time() - start
            print ("elapsed_time:{0}".format(elapsed_time) + "[sec]")    
            
            file = open('files/edgedata0127.txt', 'a')

            Xhole = min(xmax - xhole, xhole - xmin)
            Yhole = min(ymax - yhole, yhole - ymin)
            Xholecenter = min(xmax - xholecenter, xholecenter -xmin)
            Yholecenter = min(ymax - yholecenter, yholecenter -ymin)
            file.write(saveName +' radius:' +str(rhole)
                    #+' colorInfo:'+str(circleInfo[3])+' '+str(circleInfo[4])+' '+str(circleInfo[5])
                    +' vote:'+str(vote)+' HoughCircle('+str(Xhole)+' '+str(Yhole)
                    +') HoleCenter('+str(round(Xholecenter,1))+' '+str(round(Yholecenter))
                    +') size('+str(xsizeeff)+' '+str(ysizeeff)+')\n')
            file.close()
            file2 = open('files/cube_data0124.txt', 'a')
            file2.write(saveName + ' xmax: '+str(xmaxeff)+ ' xmin: '+str(xmineff)+ ' ymax: '+str(ymaxeff)+ ' ymin:'+str(ymineff)+ '\n')            
            plt.show()
            file2.close()





if __name__ == "__main__":
    main()


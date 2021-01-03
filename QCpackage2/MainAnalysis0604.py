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


###cubeQC.py の時はこれ
from QCpackage2.package_cube import manualminimize
from QCpackage2.package_cube import figureInfo
from QCpackage2.package_cube import resizeFigure
from QCpackage2.package_cube import extractionRGB 
from QCpackage2.package_cube import trimmFig
from QCpackage2.package_cube import houghCircle
from QCpackage2.package_cube import searchCenter
from QCpackage2.package_cube import outline
from QCpackage2.package_cube import pixVal
from QCpackage2.package_cube import houghLine2
from QCpackage2.package_cube import findThres
from QCpackage2.package_cube import detectHole
from QCpackage2.package_cube import outline2
from QCpackage2.package_cube import choiceOutline3


'''
###画像解析だけの時はこれ
from package_cube import manualminimize
from package_cube import figureInfo
from package_cube import resizeFigure
from package_cube import extractionRGB 
from package_cube import trimmFig
from package_cube import houghCircle
from package_cube import searchCenter
from package_cube import outline
from package_cube import pixVal
from package_cube import houghLine2
from package_cube import findThres
from package_cube import detectHole
from package_cube import outline2
from package_cube import choiceOutline3

###plt.show()する時はこれ
from package_cube_show import manualminimize
from package_cube_show import figureInfo
from package_cube_show import resizeFigure
from package_cube_show import extractionRGB 
from package_cube_show import trimmFig
from package_cube_show import houghCircle
from package_cube_show import searchCenter
from package_cube_show import outline
from package_cube_show import pixVal
from package_cube_show import houghLine2
from package_cube_show import findThres
from package_cube_show import detectHole
from package_cube_show import outline2
from package_cube_show import choiceOutline3

'''

##############################################################################

def ANALYSIS(saveName, ImageName, camID):
                    start = time.time()
   # for cubenumber in range(16):
    
      #  for i in range(576):
       #     for k in range(6):
            
#                for j in range(4):
#                    saveName='cube'+str(i+ 1)+'cam'+str(k+1) 
         #           saveName  = 'cube'+str(cubenumber+1)+'cam'+str(k+4)+'_'+str(i+1)+str(j+1)
 #                   ImageName = 'mao_pictures/pic200912/'+ saveName + '.jpg' 
                 #   print (saveName)   
                    filename = 'files/data201225_.txt'
                    imgG= cv2.imread(ImageName,0)
                    if imgG is None :
                        print('image not found!')

                    #if len(imgG[imgG >120]) < 400000 or len(imgG[imgG > 120]) > 500000:
#                    tr = imgG[int(768/2-30):int(768/2+30), int(1024/2-30):int(1024/2+30)]
#                    if len(tr[tr>140])<3590:
#                        print('cube is not here.')
#                        cubedata_err=[ 0, 0, 0, 0, 0, 0, 0, 0]
#                        file = open(filename,'a')
#                        file.write(saveName +' icam: '+str(0)+' direction: '+str(0)+' '+str(0)+' size(outline) :'+str(0)+','+str(0)+'\n')
#                        file.close()
#                        return cubedata_err
                        

                    
                    img = cv2.imread(ImageName,1)
                    img = cv2.split(img)
                    img = cv2.merge((img[2],img[1],img[0])) # => bgr
            #        img2 = cv2.merge((img[2],img[1],img[0])) # => bgr
                    print("image is '{}'.".format(ImageName))
                    figureInfo.get_FigureInfo(img)
                    #j=1 
                    #i=1
            
                    img =         resizeFigure.set_ResizeFigure(img,1)
                    img_sample =  resizeFigure.set_ResizeFigure(img,1)
                    img_sample2 = resizeFigure.set_ResizeFigure(img,1)
                    img_sample3 = resizeFigure.set_ResizeFigure(img,1)
                    img_forBump =  resizeFigure.set_ResizeFigure(img,1)
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
                    if colmean == 1 :
                        print('this cube is middle')
                        cubedata_err=[ 0, 0, 0, 0, 0, 0, 0, 0]
                        file = open(filename,'a')
                        file.write(saveName +' icam: '+str(0)+' direction: '+str(0)+' '+str(cubedata_err)+'\n')#' size(outline) :'+str(0)+','+str(0)+'\n')
                        file.close()
        #                continue
                        return cubedata_err




                    #######################
                    holestart = time.time()
                    xholecenter_, yholecenter_ = detectHole.detect_HoleCenter(trimmForHole, trimmForHole2, colmean, rate=0.7, radius=rhole)
                    print('hole time : {} sec'.format(time.time()-holestart))
                    
                    xholecenter = xholecenter_ + xhole - rhole -30
                    yholecenter = yholecenter_ + yhole - rhole -30
        
                    searchCenter.SearchCenter(xholecenter, yholecenter, rhole, edges2)
            
                    #############################################################
                    ###サイズ部門スタート
                    sizetime = time.time() 
                    ########################追加分    
        #            extract =        trimmFig.get_TrimmedFigure(img,cube_size[5]-10,cube_size[3]+6,cube_size[4]-10,cube_size[2]+10) # 左上0,0: y1,y2,x1,x2
         #           extract_sample = trimmFig.get_TrimmedFigure(img_sample, cube_size[5]-10,cube_size[3]+6,cube_size[4]-10,cube_size[2]+10) # 左上0,0: y1,y2,x1,x2
                    extract = img
                    extract_sample = img_sample
                    prex0, prey0, prex1, prey1 = outline2.detect_Outline_wColFigure(result_sample, 1, 500) #輪郭検出の際は閾値以下のところを黒にした画像を使う。
                    xylist = houghLine2.hough_lines(extract_sample, extract, prex0, prey0, prex1, prey1) #直線検出の際は生画像を使う。


###############deeplearning用の画像生成########## サイズを 660*60　に固定
                    '''
                    imgforDL = cv2.imread(ImageName,1)
                    imgforDL = cv2.split(imgforDL)
                    imgforDL = cv2.merge((imgforDL[2],imgforDL[1],imgforDL[0])) # => bgr

                    bx = int((prex0+prex1)/2)
                    by = int((prey0+prey1)/2)


                    eleft   = imgforDL[by-330:by+330, prex0-35:prex0+25]
                    etop    = imgforDL[20:80, bx-330:bx+330]
                    eright  = imgforDL[by-330:by+330, prex1-25:prex1+35]
                    ebottom = imgforDL[697:757, bx-330:bx+330]
                    cv2.imwrite('edgebad/'+ saveName +  'left.jpg',eleft)
                    cv2.imwrite('edgebad/'+ saveName+   'top.jpg',etop)
                    cv2.imwrite('edgebad/'+ saveName+ 'right.jpg',eright)
                    cv2.imwrite('edgebad/'+ saveName+'bottom.jpg',ebottom)
                    '''

                    xmax = xylist[0] 
                    xmin = xylist[1] 
                    ymax = xylist[2] 
                    ymin = xylist[3] 
                    xsize= xmax - xmin
                    ysize= ymax - ymin
                    Mat_rot = xylist[4]  ###回転行列と回転の中心。
                    rotx    = xylist[5] 
                    roty    = xylist[6]            
                    tan_mean= xylist[7]
                    
                    ###エラーが出たらerr=1となる。output を特殊なものにして、middle に分別されるようにする。
#                    '''
                    err     = xylist[8]
                    if err == 1:
                        cubedata_err=[ 0, 0, 0, 0, 0, 0, 0, 0]
                        file = open(filename,'a')
                        file.write(saveName +' icam: '+str(0)+' direction: '+str(0)+' '+str(cubedata_err)+'\n')#' size(outline) :'+str(0)+','+str(0)+'\n')
                        file.close()
#                        continue
                        return cubedata_err
 #                   '''    
        
                    print("cube size by line detection : {},{}".format(xsize,ysize))
                    ########################   
                    cube_size = outline.detect_Outline_wColFigure(result_sample, 1, 500, rotx, roty, Mat_rot)
                     #cube_size :: [size_x, size_y, max_x, max_y, min_x, min_y]
                    #                 0        1     2      3      4       5
                    
                    outlinexmax = cube_size[2]
                    outlinexmin = cube_size[4]
                    outlineymax = cube_size[3]
                    outlineymin = cube_size[5]

                    outlinexmax_y = cube_size[6]
                    outlinexmin_y = cube_size[7]
                    outlineymax_x = cube_size[8]
                    outlineymin_x = cube_size[9]
                    #############################################################
                    
                    #print(cube_size)
            
            
                    #pixValはほとんどコメントアウトしてるので何もしてなさそう1/1追記
                    pixVal.get_PixelValues(saveName, img_sample, 1, cube_size)
                    print('outline(xmin, ymin, xmax, ymax); houghline(xmin, ymin, xmax, ymax) is \n ({}, {}, {}, {}); ({}, {}, {}, {})'
                            .format(outlinexmin, outlineymin, outlinexmax, outlineymax, 
                                    xmin, ymin, xmax, ymax))
            #バンプ検出、どう扱うか。       
                    
                    chosen = choiceOutline3.choice_Outline(img_forBump, 
                                    outlinexmin, outlinexmin_y, outlineymin, outlineymin_x,
                                    outlinexmax, outlinexmax_y, outlineymax, outlineymax_x,
                                    xmin, ymin, xmax, ymax, rotx, roty, tan_mean)
            
                    #chosenOutline : [chosenxmax, chosenxmin, chosenymax, chosenymin, bump_judge]
                    #大きさを図るには直線検出のほうが良いかも
                    #xmaxeff = chosen[0]
                    #xmineff = chosen[1]
                    #ymaxeff = chosen[2]
                    #ymineff = chosen[3]
                    
                    xmaxeff = xmax
                    xmineff = xmin
                    ymaxeff = ymax
                    ymineff = ymin                
    
    
    
                    xsizeeff_ = xmaxeff - xmineff
                    ysizeeff_ = ymaxeff - ymineff
                    
                    bump_judge = chosen[4]
                    
                    print("effective cube size : {}, {}".format(xsizeeff_, ysizeeff_))
                    
                    print('size_time : {} sec'.format(time.time()-sizetime))
                    pos_min, Emin =  manualminimize.manualminimization()
                    opt_x = pos_min[0]
                    opt_y = pos_min[1]
                    print('opt_x, opt_y(before):{}, {}'.format(opt_x, opt_y))
                    opt_x, opt_y = np.dot(Mat_rot, [opt_x-rotx, opt_y-roty]) + [rotx, roty] ###穴中心の回転。 
                    
                    print('opt_x, opt_y(after):{}, {}'.format(opt_x, opt_y))
        
                    opt_r = pos_min[2] #####これらが穴の絶対位置。
                    print('pos_min, Emin = {}, {}'.format(pos_min, Emin))
                    elapsed_time = time.time() - start
                    print ("elapsed_time:{0}".format(elapsed_time) + "[sec]")    
                    
                    ####################################################################
                    Xhole = min(xmax - xhole, xhole - xmin)##xhole,yholeはハフ変換の結果。
                    Yhole = min(ymax - yhole, yhole - ymin)##多分もう使わない。
                    Xholecenter = min(xmax - xholecenter, xholecenter -xmin)##xholecenter,yholecenterは中央値。
                    Yholecenter = min(ymax - yholecenter, yholecenter -ymin)##これももう使わない。
                    ###################################################################


                    ####前はカメラごとにキューブの向きが決まっていたので、カメラのIDでキューブの穴位置を定義していた。
                    ####今回は穴位置が画面中心からどの象限にあるか、で穴位置を定義する。




                    ####穴がどこにあるか、でxhole とyholeの定義を変える。                   

                    if   opt_x > 512 and opt_y < 384 : ##右上
                        xc = xmaxeff - opt_x
                        yc = opt_y - ymineff
                        directionID = 0 

                        xsizeeff = xsizeeff_
                        ysizeeff = ysizeeff_

                    elif opt_x > 512 and opt_y > 384 : ##右下
                        yc = xmaxeff - opt_x
                        xc = ymaxeff - opt_y
                        directionID = 1

                        ysizeeff = xsizeeff_
                        xsizeeff = ysizeeff_
                                                
                    elif opt_x < 512 and opt_y > 384 : ##左下
                        xc = opt_x - xmineff
                        yc = ymaxeff - opt_y
                        directionID = 2

                        xsizeeff = xsizeeff_
                        ysizeeff = ysizeeff_

                    elif opt_x < 512 and opt_y < 384 : ##左上
                        yc = opt_x - xmineff
                        xc = opt_y - ymineff
                        directionID = 3

                        xsizeeff = ysizeeff_
                        ysizeeff = xsizeeff_

                    else : ##穴が中央にある？？
                        print('hole is on the center. why?')
                        xc = 0
                        yc = 0
                        directionID = 10

                    '''
                    I=i+1
                    if   I==1  :
                        xc = xmaxeff - opt_x
                        yc = ymaxeff - opt_y
                        print('I={}, (xc,yc)=({},{})'.format(I, xc, yc))
                    elif I==2  :
                        xc = opt_x - xmineff
                        yc = ymaxeff - opt_y
                        print('I={}, (xc,yc)=({},{})'.format(I, xc, yc))
                    elif I==3  :
                        xc = xmaxeff - opt_x
                        yc = opt_y - ymineff
                        print('I={}, (xc,yc)=({},{})'.format(I, xc, yc))
        
                    
                    file = open('files/edgedata0127.txt', 'a')
                    file.write(saveName +' radius:' +str(rhole)
                            #+' colorInfo:'+str(circleInfo[3])+' '+str(circleInfo[4])+' '+str(circleInfo[5])
                            +' vote:'+str(vote)+' HoughCircle('+str(Xhole)+' '+str(Yhole)
                            +') HoleCenter('+str(round(Xholecenter,1))+' '+str(round(Yholecenter))
                            +') size('+str(xsizeeff)+' '+str(ysizeeff)+')\n')
                    file.close()
                    file2 = open('files/cube_data0124.txt', 'a')
                    file2.write(saveName + ' xmax: '+str(xmaxeff)+ ' xmin: '+str(xmineff)+ ' ymax: '+str(ymaxeff)+ ' ymin:'+str(ymineff)+ '\n')            
                    file2.close()
                    '''


#                    if   k == 0 or k == 1 or k == 2 :
                    cubedata=[ directionID+1, round(xc,2), round(yc,2), round(opt_r,2), round(Emin,2), round(xsizeeff,2), round(ysizeeff,2), round(bump_judge, 5)]
                    ###カメラ４、５、６の時はxとｙを逆にする。<-これは却下。
#                    elif k == 3 or k == 4 or k == 5 :
#                        cubedata=[ directionID+1, round(yc,2), round(xc,2), round(opt_r,2), round(Emin,2), round(ysizeeff,2), round(xsizeeff,2), round(bump_judge, 5)]

                    print('saveName:{} ,output:{}\n'.format(saveName, cubedata))
                    file = open(filename,'a')
                    file.write(saveName +' icam: '+str(camID+1)+' direction: '+str(directionID+1)+' '+str(cubedata)+'\n')#' size(outline) :'+str(round(cube_size[0],2))+','+str(round(cube_size[1],2))+'\n')
                    file.close()


                    print('type of cubedata: ', type(cubedata))
  #                  plt.show()
                    return cubedata
    



if __name__ == "__main__":
    print('__name__ is ', __name__)

    ANALYSIS('', '',1)


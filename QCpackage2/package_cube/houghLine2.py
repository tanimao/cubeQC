import numpy as np
import math
#from package_cube import trimmFig
import cv2
import matplotlib.pyplot as plt

#ハフ変換で直線を抽出する関数
def hough_lines(image, outLineImage, prex0, prey0, prex1, prey1):
    print("\n#call hough_lines")
    result = image
    gray2 = cv2.cvtColor(outLineImage, cv2.COLOR_BGR2GRAY)
    gray2 = cv2.GaussianBlur(gray2, (5,5), 0)
    ret,th = cv2.threshold(gray2,40,255,cv2.THRESH_BINARY)

    #ret, th = cv2.threshold(gray2,0,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)
    minVal = 100
    maxVal = 200
    edges = cv2.Canny(th, minVal, maxVal)
    
    bx = int((prex0 + prex1)/2)
    by = int((prey0 + prey1)/2)
    

    '''    
    edges0_ = trimmFig.get_TrimmedFigure(gray2,prey0,by, prex0-50,prex0+50)
    edges1_ = trimmFig.get_TrimmedFigure(gray2,prey0,by, prex1-50,prex1+50)
    edges2_ = trimmFig.get_TrimmedFigure(gray2,by,prey1, prex0-50,prex0+50)
    edges3_ = trimmFig.get_TrimmedFigure(gray2,by,prey1, prex1-50,prex1+50)

    edges4_ = trimmFig.get_TrimmedFigure(gray2,prey0-50,prey0+50, prex0,bx)
    edges5_ = trimmFig.get_TrimmedFigure(gray2,prey1-50,prey1+50, prex0,bx)
    edges6_ = trimmFig.get_TrimmedFigure(gray2,prey0-50,prey0+50, bx,prex1)
    edges7_ = trimmFig.get_TrimmedFigure(gray2,prey1-50,prey1+50, bx,prex1)
    
    edges0 = trimmFig.get_TrimmedFigure(edges,prey0,by, prex0-50,prex0+50)
    edges1 = trimmFig.get_TrimmedFigure(edges,prey0,by, prex1-50,prex1+50)
    edges2 = trimmFig.get_TrimmedFigure(edges,by,prey1, prex0-50,prex0+50)
    edges3 = trimmFig.get_TrimmedFigure(edges,by,prey1, prex1-50,prex1+50)

    edges4 = trimmFig.get_TrimmedFigure(edges,0,prey0+50, prex0,bx)
    edges5 = trimmFig.get_TrimmedFigure(edges,prey1-50,767, prex0,bx)
    edges6 = trimmFig.get_TrimmedFigure(edges,0,prey0+50, bx,prex1)
    edges7 = trimmFig.get_TrimmedFigure(edges,prey1-50,767, bx,prex1)

    '''

    edges0 = edges[prey0:by, prex0-50:prex0+70]
    edges1 = edges[prey0:by, prex1-70:prex1+50]
    edges2 = edges[by:prey1, prex0-50:prex0+70]
    edges3 = edges[by:prey1, prex1-70:prex1+50]

    edges4 = edges[0:prey0+70, prex0:bx]
    edges5 = edges[prey1-70:767, prex0:bx]
    edges6 = edges[0:prey0+70, bx:prex1]
    edges7 = edges[prey1-70:767, bx:prex1]

    xmaxcandi = []
    xmincandi = []
    ymaxcandi = []
    ymincandi = [] 
    Xmaxcandi = []
    Xmincandi = []
    Ymaxcandi = []
    Ymincandi = [] 
    Line_topx1 = []
    Line_bottomx1 = []
    Line_leftx1 = []
    Line_rightx1 = []
    Line_topy1 = []
    Line_bottomy1 = []
    Line_lefty1 = []
    Line_righty1 = []

    Line_topx2 = []
    Line_bottomx2 = []
    Line_leftx2 = []
    Line_rightx2 = []
    Line_topy2 = []
    Line_bottomy2 = []
    Line_lefty2 = []
    Line_righty2 = []
    #ハフ変換で直線を抽出

    lines0 = cv2.HoughLinesP(edges0, rho=1, theta=np.pi/180, threshold=30, minLineLength=80, maxLineGap=50)
    lines1 = cv2.HoughLinesP(edges1, rho=1, theta=np.pi/180, threshold=30, minLineLength=80, maxLineGap=50)
    lines2 = cv2.HoughLinesP(edges2, rho=1, theta=np.pi/180, threshold=30, minLineLength=80, maxLineGap=50)
    lines3 = cv2.HoughLinesP(edges3, rho=1, theta=np.pi/180, threshold=30, minLineLength=80, maxLineGap=50)
    lines4 = cv2.HoughLinesP(edges4, rho=1, theta=np.pi/180, threshold=30, minLineLength=80, maxLineGap=50)
    lines5 = cv2.HoughLinesP(edges5, rho=1, theta=np.pi/180, threshold=30, minLineLength=80, maxLineGap=50)
    lines6 = cv2.HoughLinesP(edges6, rho=1, theta=np.pi/180, threshold=30, minLineLength=80, maxLineGap=50)
    lines7 = cv2.HoughLinesP(edges7, rho=1, theta=np.pi/180, threshold=30, minLineLength=80, maxLineGap=50)
    lines = []
    '''
    print("lines0 = {}, type={}".format(lines0, type(lines0)))
    print("lines1 = {}, type={}".format(lines1, type(lines1)))
    print("lines2 = {}, type={}".format(lines2, type(lines2)))
    print("lines3 = {}, type={}".format(lines3, type(lines3)))
    print("lines4 = {}, type={}".format(lines4, type(lines4)))
    print("lines5 = {}, type={}".format(lines5, type(lines5)))
    print("lines6 = {}, type={}".format(lines6, type(lines6)))
    print("lines7 = {}, type={}".format(lines7, type(lines7)))
    '''
    print("lines = {}, type={}".format(lines, type(lines)))
    if lines0 is None:
        print("lines0 is None")
    else :
        for line in lines0:
            
            for  x1, y1, x2, y2 in line:
                cv2.line(edges0,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
                x1 = x1 + prex0-50 
                x2 = x2 + prex0-50
                y1 = y1 + prey0
                y2 = y2 + prey0
                lines.append(x1)
                lines.append(y1)
                lines.append(x2)
                lines.append(y2)


#                print('line0_(x1,x2,y1,y2) = ({},{},{},{})'.format(x1, x2, y1, y2))
                cv2.line(result,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
                ###各直線の中心の点を得る
                if x1 < 300 and x2 < 300 and ((abs(y1-y2) >= 150 and abs(x1-x2) < 10) or (abs(y1-y2) < 150 and abs(x1-x2) < 5)) :
                    xmincandi.append(min(x1, x2))
                    xhalf=(x1+x2)/2
                    yhalf=(y1+y2)/2
                    Line_leftx1.append(xhalf)
                    Line_lefty1.append(yhalf)

    if lines2 is None:
        print("lines2 is None")
    else :                
        for line in lines2:
            for  x1, y1, x2, y2 in line:
                cv2.line(edges2,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
                
                x1 = x1 + prex0-50 
                x2 = x2 + prex0-50
                y1 = y1 + by
                y2 = y2 + by
    
                lines.append(x1)
                lines.append(y1)
                lines.append(x2)
                lines.append(y2)
                
#                print('line2_(x1,x2,y1,y2) = ({},{},{},{})'.format(x1, x2, y1, y2))
                cv2.line(result,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
                ###各直線の中心の点を得る
                if x1 < 300 and x2 < 300 and ((abs(y1-y2) >= 150 and abs(x1-x2) < 10) or (abs(y1-y2) < 150 and abs(x1-x2) < 5)) :
                    xmincandi.append(min(x1, x2))
                    xhalf=(x1+x2)/2
                    yhalf=(y1+y2)/2
                    Line_leftx2.append(xhalf)
                    Line_lefty2.append(yhalf)
        
    
    if lines1 is None:
        print("lines1 is None")
    else :                
        for line in lines1:
            for  x1, y1, x2, y2 in line:
                cv2.line(edges1,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
                
                x1 = x1 + prex1-70 
                x2 = x2 + prex1-70
                y1 = y1 + prey0
                y2 = y2 + prey0
    
                lines.append(x1)
                lines.append(y1)
                lines.append(x2)
                lines.append(y2)
#                print('line1_(x1,x2,y1,y2) = ({},{},{},{})'.format(x1, x2, y1, y2))
                cv2.line(result,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
                ###各直線の中心の点を得る
                if x1 > 750 and x2 > 750 and ((abs(y1-y2) >= 150 and abs(x1-x2) < 10) or (abs(y1-y2) < 150 and abs(x1-x2) < 5)) :
                    xmaxcandi.append(max(x1, x2))
                    xhalf=(x1+x2)/2
                    yhalf=(y1+y2)/2
                    Line_rightx1.append(xhalf)
                    Line_righty1.append(yhalf)
        
    if lines3 is None:
        print("lines3 is None")
    else :                
        for line in lines3:
            for  x1, y1, x2, y2 in line:
                cv2.line(edges3,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
    
                x1 = x1 + prex1-70 
                x2 = x2 + prex1-70
                y1 = y1 + by
                y2 = y2 + by
                
                lines.append(x1)
                lines.append(y1)
                lines.append(x2)
                lines.append(y2)
#                print('line3_(x1,x2,y1,y2) = ({},{},{},{})'.format(x1, x2, y1, y2))
                cv2.line(result,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
                ###各直線の中心の点を得る
                if x1 > 750 and x2 > 750 and ((abs(y1-y2) >= 150 and abs(x1-x2) < 10) or (abs(y1-y2) < 150 and abs(x1-x2) < 5)) :
                    xmaxcandi.append(max(x1, x2))
                    xhalf=(x1+x2)/2
                    yhalf=(y1+y2)/2
                    Line_rightx2.append(xhalf)
                    Line_righty2.append(yhalf)
        
        
    if lines4 is None:
        print("lines4 is None")
    else :                
        for line in lines4:
            for  x1, y1, x2, y2 in line:
                cv2.line(edges4,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
    
                x1 = x1 + prex0 
                x2 = x2 + prex0
                
                lines.append(x1)
                lines.append(y1)
                lines.append(x2)
                lines.append(y2)
#                print('line4_(x1,x2,y1,y2) = ({},{},{},{})'.format(x1, x2, y1, y2))
                cv2.line(result,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
                ###各直線の中心の点を得る
                if y1 < 150 and y2 < 150 and ((abs(x1-x2) >= 150 and abs(y1-y2) < 10) or (abs(x1-x2) < 150 and abs(y1-y2) < 5)) :
                    ymincandi.append(min(y1, y2))
                    xhalf=(x1+x2)/2
                    yhalf=(y1+y2)/2
                    Line_topx1.append(xhalf)
                    Line_topy1.append(yhalf)
        
    if lines5 is None:
        print("lines5 is None")
    else :                
        for line in lines5:
            for  x1, y1, x2, y2 in line:
                cv2.line(edges5,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
    
                x1 = x1 + prex0 
                x2 = x2 + prex0
                y1 = y1 + prey1-70
                y2 = y2 + prey1-70
                
                lines.append(x1)
                lines.append(y1)
                lines.append(x2)
                lines.append(y2)
#                print('line5_(x1,x2,y1,y2) = ({},{},{},{})'.format(x1, x2, y1, y2))
                cv2.line(result,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
                ###各直線の中心の点を得る
                if y1 > 600 and y2 > 600 and ((abs(x1-x2) >= 150 and abs(y1-y2) < 10) or (abs(x1-x2) < 150 and abs(y1-y2) < 5)) :
                    ymaxcandi.append(max(y1, y2))
                    xhalf=(x1+x2)/2
                    yhalf=(y1+y2)/2
                    Line_bottomx1.append(xhalf)
                    Line_bottomy1.append(yhalf)
        
        
    if lines6 is None:
        print("lines6 is None")
    else :                
        for line in lines6:
            for  x1, y1, x2, y2 in line:
                cv2.line(edges6,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
    
                x1 = x1 + bx
                x2 = x2 + bx
                
                lines.append(x1)
                lines.append(y1)
                lines.append(x2)
                lines.append(y2)
#                print('line6_(x1,x2,y1,y2) = ({},{},{},{})'.format(x1, x2, y1, y2))
                cv2.line(result,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
                ###各直線の中心の点を得る
                if y1 < 150 and y2 < 150 and ((abs(x1-x2) >= 150 and abs(y1-y2) < 10) or (abs(x1-x2) < 150 and abs(y1-y2) < 5)) :
                    ymincandi.append(min(y1, y2))
                    xhalf=(x1+x2)/2
                    yhalf=(y1+y2)/2
                    Line_topx2.append(xhalf)
                    Line_topy2.append(yhalf)
        
    if lines7 is None:
        print("lines7 is None")
    else :                
        for line in lines7:
            for  x1, y1, x2, y2 in line:
                cv2.line(edges7,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
    
                x1 = x1 + bx
                x2 = x2 + bx
                y1 = y1 + prey1-70
                y2 = y2 + prey1-70
                
                lines.append(x1)
                lines.append(y1)
                lines.append(x2)
                lines.append(y2)
#                print('line7_(x1,x2,y1,y2) = ({},{},{},{})'.format(x1, x2, y1, y2))
                cv2.line(result,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
                ###各直線の中心の点を得る
                if y1 > 600 and y2 > 600 and ((abs(x1-x2) >= 150 and abs(y1-y2) < 10) or (abs(x1-x2) < 150 and abs(y1-y2) < 5)) :
                    ymaxcandi.append(max(y1, y2))
                    xhalf=(x1+x2)/2
                    yhalf=(y1+y2)/2
                    Line_bottomx2.append(xhalf)
                    Line_bottomy2.append(yhalf)
    
    print('xmaxcandi =', xmaxcandi)
    print('xmincandi =', xmincandi)
    print('ymaxcandi =', ymaxcandi)
    print('ymincandi =', ymincandi)

    err = 0

    try : 
        xmax = max(xmaxcandi)
        xmin = min(xmincandi)
        ymax = max(ymaxcandi)
        ymin = min(ymincandi)
    except ValueError:
        print("Value Error occorred!")
        err = 1
        xylist_err = [0, 0, 0, 0, 0, 0, 0, 0, err]
        return xylist_err


    print ('size before rotation :({}, {})'.format(xmax-xmin, ymax-ymin))
    rotx = (xmax+xmin)/2
    roty = (ymax+ymin)/2 ###回転の中心。


    '''
    print('Line_lx1 = {}, Line_ly1 = {}'.format(Line_leftx1, Line_lefty1))        
    print('Line_rx1 = {}, Line_ry1 = {}'.format(Line_rightx1, Line_righty1))        
    print('Line_tx1 = {}, Line_ty1 = {}'.format(Line_topx1, Line_topy1))        
    print('Line_bx1 = {}, Line_by1 = {}'.format(Line_bottomx1, Line_bottomy1)) 

    print('Line_lx2 = {}, Line_ly2 = {}'.format(Line_leftx2, Line_lefty2))        
    print('Line_rx2 = {}, Line_ry2 = {}'.format(Line_rightx2, Line_righty2))        
    print('Line_tx2 = {}, Line_ty2 = {}'.format(Line_topx2, Line_topy2))        
    print('Line_bx2 = {}, Line_by2 = {}'.format(Line_bottomx2, Line_bottomy2)) 
    '''




    ###各辺の傾きtanθを計算する
    SumN=0
    tanleft  =np.nan
    tanright =np.nan
    tantop   =np.nan
    tanbottom=np.nan
    tanleft_mean = 0
    tanright_mean= 0
    tantop_mean  = 0
    tanbottom_mean=0
    nleft  =0
    nright =0
    ntop   =0
    nbottom=0
    '''
    leftymin     = min(Line_lefty)
    leftminindex = np.argmin(Line_lefty)
    leftx0       = Line_leftx[leftminindex]
    leftymax     = max(Line_lefty)
    leftmaxindex = np.argmax(Line_lefty)
    leftxi       = Line_leftx[leftmaxindex]
    tanleft = (leftxi-leftx0)/(leftymax-leftymin)
    if tanleft == tanleft and leftymax-leftymin > 100:
        print('OK.')
        SumN = SumN+1
    else:
        print('tanleft is nan or too big.')
        tanleft = 0
    '''

    #left について    
    for index1, y1 in enumerate(Line_lefty1):
        for index2, y2 in enumerate(Line_lefty2):
            if y2-y1 > 100:
                nleft = nleft + 1 
                tanleft  = (Line_leftx2[index2]-Line_leftx1[index1])/(y2-y1)
                if tanleft == tanleft :
                    tanleft_mean = ((nleft-1)*tanleft_mean + tanleft)/nleft
                    '''
                    print('nleft={}'.format(nleft))
                    print('tanleft={}'.format(tanleft))    
                    print('tanleft_mean={}'.format(tanleft_mean))    
                    print('tanleft_mean={}'.format( (nleft-1)*tanleft_mean))
                    '''
    if type(tanleft_mean) == np.float64:
        print('OK.')
        SumN = SumN+1
    else:
        print(type(tanleft_mean))
        print('tanleft is nan or too big.')
        tanleft_mean = 0

    #right について
    for index1, y1 in enumerate(Line_righty1):
        for index2, y2 in enumerate(Line_righty2):
            if y2-y1 > 100:
                nright = nright + 1 
                tanright  = (Line_rightx2[index2]-Line_rightx1[index1])/(y2-y1)
                if tanright == tanright:
                    tanright_mean = ((nright-1)*tanright_mean + tanright)/nright
                    #print('tanright={}'.format(tanright))    
    
    if type(tanright_mean) == np.float64 :
        print('OK.')
        SumN = SumN+1
    else:
        print('tanright is nan or too big.')
        tanright_mean = 0


    #top について
    for index1, y1 in enumerate(Line_topy1):
        for index2, y2 in enumerate(Line_topy2):
            if Line_topx2[index2]-Line_topx1[index1] > 100:
                ntop = ntop + 1 
                tantop  = -(y2-y1)/(Line_topx2[index2]-Line_topx1[index1])
                if tantop == tantop:
                    tantop_mean = ((ntop-1)*tantop_mean + tantop)/ntop
                    #print('tantop={}'.format(tantop))    
    
    if type(tantop_mean) == np.float64:
        print('OK.')
        SumN = SumN+1
    else:
        print('tantop is nan or too big.')
        tantop_mean = 0


    #bottom について
    for index1, y1 in enumerate(Line_bottomy1):
        for index2, y2 in enumerate(Line_bottomy2):
            if Line_bottomx2[index2]-Line_bottomx1[index1] > 100:
                nbottom = nbottom + 1 
                tanbottom  = -(y2-y1)/(Line_bottomx2[index2]-Line_bottomx1[index1])
                if tanbottom == tanbottom:
                    tanbottom_mean = ((nbottom-1)*tanbottom_mean + tanbottom)/nbottom
                    #print('tanbottom={}'.format(tanbottom))    
    
    if type(tanbottom_mean) == np.float64 :
        print('OK.')
        SumN = SumN+1
    else:
        print('tanbottom is nan or too big.')
        tanbottom_mean = 0

    
    '''
    topxmin     = min(Line_topx)
    topminindex = np.argmin(Line_topx)
    topyi       = Line_topy[topminindex]
    topxmax     = max(Line_topx)
    topmaxindex = np.argmax(Line_topx)
    topy0       = Line_topy[topmaxindex]

    tantop = (topyi-topy0)/(topxmax-topxmin)
    if tantop == tantop and topxmax-topxmin > 100:
        print('OK.')
        SumN = SumN+1
    else:
        print('tantop is nan or too big.')
        tantop = 0

    rightymax     = max(Line_righty)
    rightmaxindex = np.argmax(Line_righty)
    rightx0       = Line_rightx[rightmaxindex]
    rightymin     = min(Line_righty)
    rightminindex = np.argmin(Line_righty)
    rightxi       = Line_rightx[rightminindex]

    tanright = (rightx0-rightxi)/(rightymax-rightymin)
    if tanright == tanright and rightymax-rightymin > 100:
        print('OK.')
        SumN = SumN+1
    else:
        print('tanright is nan or too big.')
        tanright = 0
            
    bottomxmax     = max(Line_bottomx)
    bottommaxindex = np.argmax(Line_bottomx)
    bottomyi       = Line_bottomy[bottommaxindex]
    bottomxmin     = min(Line_bottomx)
    bottomminindex = np.argmin(Line_bottomx)
    bottomy0       = Line_bottomy[bottomminindex]

    tanbottom = (bottomy0-bottomyi)/(bottomxmax-bottomxmin)
    if tanbottom == tanbottom and bottomxmax-bottomxmin > 100:
        print('OK.')
        SumN = SumN+1
    else:
        print('tanbottom is nan or too big.')
        tanbottom = 0

    '''
    

    print('tan: {}, {}, {}, {}'.format(tanleft_mean, tantop_mean, tanright_mean, tanbottom_mean))
    print('SumN={}'.format(SumN)) 
    ###平均の傾きを求める
    try :
        tan_mean = (tanleft_mean+tantop_mean+tanright_mean+tanbottom_mean)/SumN
        print('mean tan = {}'.format(tan_mean))
    except ZeroDivisionError:
        print("ZeroDivisionError occorred!")
        err = 1
        xylist_err = [0, 0, 0, 0, 0, 0, 0, 0, err]
        return xylist_err
    ###回転行列を求める
    cos = 1/math.sqrt(1+tan_mean*tan_mean)
    Mat_rot_tan = np.array([[1, -tan_mean], [tan_mean, 1]])
    Mat_rot = cos * Mat_rot_tan 
    ###ここまでで回転行列を求めた。#######################
    

    lines_np = np.array(lines)
    lines_np = lines_np.reshape(-1,4)
    ###ここで4つ(x1,y1,x2,y2)をひとまとまりにした？   

    #print("lines_np = {},type = {}".format(lines_np,type(lines_np)))
    
    ###以下でそれぞれの直線を回転させた。
    for line in lines_np:
#        print("line = {}".format(line))
        #for  x1, y1, x2, y2 in line:

        x1 = line[0]
        y1 = line[1]
        x2 = line[2]
        y2 = line[3]
        
        xy1 = [x1-rotx, y1-roty]
        xy2 = [x2-rotx, y2-roty] 

        X1, Y1 = np.dot(Mat_rot, xy1)
        X2, Y2 = np.dot(Mat_rot, xy2)
        X1 = X1 + rotx
        X2 = X2 + rotx
        Y1 = Y1 + roty
        Y2 = Y2 + roty       ###回転中心を足しなおす。

        

        ###正しくエッジが取れているものを選んで、最大最小の候補としている
   #     print('(X1,X2,Y1,Y2) = ({},{},{},{})'.format(round(X1,2), round(X2,2), round(Y1,2), round(Y2,2)))
        if X1 < 300 and X2 < 300 and ((abs(Y1-Y2) >= 150 and abs(X1-X2) < 10) or (abs(Y1-Y2) < 150 and abs(X1-X2) < 5)) :
            #Xmincandi.append((X1+X2)/2)
            Xmincandi.append((X1+X2)/2)
        if X1 > 750 and X2 > 750 and ((abs(Y1-Y2) >= 150 and abs(X1-X2) < 10) or (abs(Y1-Y2) < 150 and abs(X1-X2) < 5)) :
            #Xmaxcandi.append((X1+X2)/2)
            Xmaxcandi.append((X1+X2)/2)
        if Y1 < 150 and Y2 < 150 and ((abs(X1-X2) >= 150 and abs(Y1-Y2) < 10) or (abs(X1-X2) < 150 and abs(Y1-Y2) < 5)) :
            #Ymincandi.append((Y1+Y2)/2)
            Ymincandi.append((Y1+Y2)/2)
        if Y1 > 600 and Y2 > 600 and ((abs(X1-X2) >= 150 and abs(Y1-Y2) < 10) or (abs(X1-X2) < 150 and abs(Y1-Y2) < 5)) :
            #Ymaxcandi.append((Y1+Y2)/2)
            Ymaxcandi.append((Y1+Y2)/2)

    #print("Xcandi(max, min) is ({}, {}), Ycandi(max, min) is ({}, {}).\n".format(Xmaxcandi,Xmincandi,Ymaxcandi,Ymincandi))
    try :
        Xmax = max(Xmaxcandi)
        Xmin = min(Xmincandi)
        Ymax = max(Ymaxcandi)
        Ymin = min(Ymincandi)
    except ValueError:
        print("Value Error occorred!")
        err = 1
        xylist_err = [0, 0, 0, 0, 0, 0, 0, 0, err]
        return xylist_err
    
    print("Xmax, Xmin, Ymax, Ymin : {}, {}, {}, {}.".format(round(Xmax,2),round(Xmin,2),round(Ymax,2),round(Ymin,2)))
    '''
    fig = plt.figure(figsize=(8, 6), dpi=100)
    fig.suptitle('hough lines', fontsize=24)
    ax1 = fig.add_subplot(1,2,1), plt.imshow(result)
    plt.imshow(result)
    ax2 = fig.add_subplot(1,2,2), plt.imshow(edges, 'gray')
    '''

    xylist_mat_center = [Xmax, Xmin, Ymax, Ymin, Mat_rot, rotx, roty, tan_mean, err]
    return xylist_mat_center

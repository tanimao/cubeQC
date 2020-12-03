import numpy as np
import math
import trimmFig
import cv2


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
    
    bx = (prex0 + prex1)/2
    by = (prey0 + prey1)/2
    
    edges0 = trimmFig.get_TrimmedFigure(edges,prey0,by, prex0-50,prex0+50)
    edges1 = trimmFig.get_TrimmedFigure(edges,prey0,by, prex1-50,prex1+50)
    edges2 = trimmFig.get_TrimmedFigure(edges,by,prey1, prex0-50,prex0+50)
    edges3 = trimmFig.get_TrimmedFigure(edges,by,prey1, prex1-50,prex1+50)

    edges4 = trimmFig.get_TrimmedFigure(edges,prey0-50,prey0+50, prex0,bx)
    edges5 = trimmFig.get_TrimmedFigure(edges,prey1-50,prey1+50, prex0,bx)
    edges6 = trimmFig.get_TrimmedFigure(edges,prey0-50,prey0+50, bx,prex1)
    edges7 = trimmFig.get_TrimmedFigure(edges,prey1-50,prey1+50, bx,prex1)



    xmaxcandi = []
    xmincandi = []
    ymaxcandi = []
    ymincandi = [] 
    Xmaxcandi = []
    Xmincandi = []
    Ymaxcandi = []
    Ymincandi = [] 
    Line_topx = []
    Line_bottomx = []
    Line_leftx = []
    Line_rightx = []
    Line_topy = []
    Line_bottomy = []
    Line_lefty = []
    Line_righty = []
    #ハフ変換で直線を抽出
    lines = cv2.HoughLinesP(edges, rho=1, theta=np.pi/180, threshold=30, minLineLength=60, maxLineGap=20)
    for line in lines:
        for  x1, y1, x2, y2 in line:
            
            print('(x1,x2,y1,y2) = ({},{},{},{})'.format(x1, x2, y1, y2))
            cv2.line(result,(x1,y1),(x2,y2),(0,255,0),1) # 緑色で直線を引く
            ###各直線の中心の点を得る
            if x1 < 250 and x2 < 250 and abs(x1-x2) < 10:
                xmincandi.append(min(x1, x2))
                xhalf=(x1+x2)/2
                yhalf=(y1+y2)/2
                Line_leftx.append(xhalf)
                Line_lefty.append(yhalf)
                
            if x1 > 750 and x2 > 750 and abs(x1-x2) < 10:
                xmaxcandi.append(max(x1, x2))
                xhalf=(x1+x2)/2
                yhalf=(y1+y2)/2
                Line_rightx.append(xhalf)
                Line_righty.append(yhalf)
    
            if y1 < 100 and y2 < 100 and abs(y1-y2) < 10:
                ymincandi.append(min(y1, y2))
                xhalf=(x1+x2)/2
                yhalf=(y1+y2)/2
                Line_topx.append(xhalf)
                Line_topy.append(yhalf)
    
            if y1 > 650 and y2 > 650 and abs(y1-y2) < 10:
                ymaxcandi.append(max(y1, y2))
                xhalf=(x1+x2)/2
                yhalf=(y1+y2)/2
                Line_bottomx.append(xhalf)
                Line_bottomy.append(yhalf)
    


    xmax = max(xmaxcandi)
    xmin = min(xmincandi)
    ymax = max(ymaxcandi)
    ymin = min(ymincandi)
    print ('size before rotation :({}, {})'.format(xmax-xmin, ymax-ymin))
    rotx = (xmax+xmin)/2
    roty = (ymax+ymin)/2 ###回転の中心。

    print('Line_lx = {}, Line_ly = {}'.format(Line_leftx, Line_lefty))        
    print('Line_rx = {}, Line_ry = {}'.format(Line_rightx, Line_righty))        
    print('Line_tx = {}, Line_ty = {}'.format(Line_topx, Line_topy))        
    print('Line_bx = {}, Line_by = {}'.format(Line_bottomx, Line_bottomy)) 

    '''
    ###各辺の傾きtanθを計算する
    leftxmin     = min(Line_leftx)
    leftminindex = np.argmin(Line_leftx)
    lefty0       = Line_lefty[leftminindex]
    leftxi       = max(Line_leftx)
    leftmaxindex = np.argmax(Line_leftx)
    leftyi       = Line_lefty[leftmaxindex]

    tanleft = (leftxi-leftxmin)/(leftyi-lefty0)


    topymin     = min(Line_topy)
    topminindex = np.argmin(Line_topy)
    topx0       = Line_topx[topminindex]
    topyi       = max(Line_topy)
    topmaxindex = np.argmax(Line_topy)
    topxi       = Line_topx[topmaxindex]

    tantop = (topyi-topymin)/(topxi-topx0)

    rightxmax     = max(Line_rightx)
    rightmaxindex = np.argmax(Line_rightx)
    righty0       = Line_righty[rightmaxindex]
    rightxi       = min(Line_rightx)
    rightminindex = np.argmin(Line_rightx)
    rightyi       = Line_righty[rightminindex]

    tanright = (rightxmax-rightxi)/(righty0-rightyi)
            
    bottomymax     = max(Line_bottomy)
    bottommaxindex = np.argmax(Line_bottomy)
    bottomx0       = Line_bottomx[bottommaxindex]
    bottomyi       = min(Line_bottomy)
    bottomminindex = np.argmin(Line_bottomy)
    bottomxi       = Line_bottomx[bottomminindex]

    tanbottom = (bottomymax-bottomyi)/(bottomx0-bottomxi)
    '''

    ###各辺の傾きtanθを計算する
    leftymin     = min(Line_lefty)
    leftminindex = np.argmin(Line_lefty)
    leftx0       = Line_leftx[leftminindex]
    leftymax     = max(Line_lefty)
    leftmaxindex = np.argmax(Line_lefty)
    leftxi       = Line_leftx[leftmaxindex]

    tanleft = (leftxi-leftx0)/(leftymax-leftymin)
    SumN=0
    if tanleft == tanleft:
        print('OK.')
        SumN = SumN+1
    else:
        print('tanleft is nan.')
        tanleft = 0


    topxmin     = min(Line_topx)
    topminindex = np.argmin(Line_topx)
    topyi       = Line_topy[topminindex]
    topxmax     = max(Line_topx)
    topmaxindex = np.argmax(Line_topx)
    topy0       = Line_topy[topmaxindex]

    tantop = (topyi-topy0)/(topxmax-topxmin)
    if tantop == tantop:
        print('OK.')
        SumN = SumN+1
    else:
        print('tantop is nan.')
        tantop = 0

    rightymax     = max(Line_righty)
    rightmaxindex = np.argmax(Line_righty)
    rightx0       = Line_rightx[rightmaxindex]
    rightymin     = min(Line_righty)
    rightminindex = np.argmin(Line_righty)
    rightxi       = Line_rightx[rightminindex]

    tanright = (rightx0-rightxi)/(rightymax-rightymin)
    if tanright == tanright:
        print('OK.')
        SumN = SumN+1
    else:
        print('tanright is nan.')
        tanright = 0
            
    bottomxmax     = max(Line_bottomx)
    bottommaxindex = np.argmax(Line_bottomx)
    bottomyi       = Line_bottomy[bottommaxindex]
    bottomxmin     = min(Line_bottomx)
    bottomminindex = np.argmin(Line_bottomx)
    bottomy0       = Line_bottomy[bottomminindex]

    tanbottom = (bottomy0-bottomyi)/(bottomxmax-bottomxmin)
    if tanbottom == tanbottom:
        print('OK.')
        SumN = SumN+1
    else:
        print('tanbottom is nan.')
        tanbottom = 0
    print('tan: {}, {}, {}, {}'.format(tanleft, tantop, tanright, tanbottom))
    print('SumN={}'.format(SumN)) 
    ###平均の傾きを求める
    tan_mean = (tanleft+tantop+tanright+tanbottom)/SumN
    print('mean tan = {}'.format(tan_mean))
    ###回転行列を求める
    cos = 1/math.sqrt(1+tan_mean*tan_mean)
    Mat_rot_tan = np.array([[1, -tan_mean], [tan_mean, 1]])
    Mat_rot = cos * Mat_rot_tan 

    for line in lines:
        for  x1, y1, x2, y2 in line:

            xy1 = [x1-rotx, y1-roty]
            xy2 = [x2-rotx, y2-roty] 

            X1, Y1 = np.dot(Mat_rot, xy1)
            X2, Y2 = np.dot(Mat_rot, xy2)
            X1 = X1 + rotx
            X2 = X2 + rotx
            Y1 = Y1 + roty
            Y2 = Y2 + roty       ###回転中心を足しなおす。

            
            print('(X1,X2,Y1,Y2) = ({},{},{},{})'.format(X1,X2, Y1, Y2))
            if X1 < 250 and X2 < 250 and abs(X1-X2) < 10:
                #Xmincandi.append((X1+X2)/2)
                Xmincandi.append(min(X1, X2))
            if X1 > 750 and X2 > 750 and abs(X1-X2) < 10:
                #Xmaxcandi.append((X1+X2)/2)
                Xmaxcandi.append(max(X1, X2))
            if Y1 < 100 and Y2 < 100 and abs(Y1-Y2) < 10:
                #Ymincandi.append((Y1+Y2)/2)
                Ymincandi.append(min(Y1, Y2))
            if Y1 > 650 and Y2 > 650 and abs(Y1-Y2) < 10:
                #Ymaxcandi.append((Y1+Y2)/2)
                Ymaxcandi.append(max(Y1, Y2))

    print("xcandi(max, min) is ({}, {}), ycandi(max, min) is ({}, {}).\n".format(xmaxcandi,xmincandi,ymaxcandi,ymincandi))
    Xmax = max(Xmaxcandi)
    Xmin = min(Xmincandi)
    Ymax = max(Ymaxcandi)
    Ymin = min(Ymincandi)
    
    print("Xmax, Xmin, Ymax, Ymin : {}, {}, {}, {}.".format(Xmax,Xmin,Ymax,Ymin))
    fig = plt.figure(figsize=(8, 6), dpi=100)
    fig.suptitle('hough lines', fontsize=24)
 #   ax1 = fig.add_subplot(1,2,1), plt.imshow(result)
    plt.imshow(result)
#    ax2 = fig.add_subplot(1,2,2), plt.imshow(edges, 'gray')






    xylist_mat_center = [Xmax, Xmin, Ymax, Ymin, Mat_rot, rotx, roty, tan_mean]
    return xylist_mat_center

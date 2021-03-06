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

###### 画像情報
def get_FigureInfo(img):
    height, width, ch = img.shape
    # 画素数 = 幅 * 高さ
    size = width * height
    # 情報表示
    print("幅：", width)
    print("高さ：", height)
    print("チャンネル数:", ch)
    print("画素数:", size)   
    print("データ型：", img.dtype)
    # 1chずつ表示
    #print("Bの画素値：\n", img[:,:,0])
    #print("Gの画素値：\n", img[:,:,1])
    #print("Rの画素値：\n", img[:,:,2])

def set_ResizeFigure(img, scale):
    height = img.shape[0]
    width  = img.shape[1]
    img = cv2.resize(img , (int(width*scale), int(height*scale)))
    return img

###### 閾値処理
def draw_TypicalThresholdProcessing(img,imgG):
    print("#call draw_TypicalThresholdProcessing")
    #fig, ax = plt.subplots(2, 3, figsize=(12, 9), sharex=True, sharey=True) 
    #nrow, ncol = ax.shape # nrow=2, ncol=3
    ret,th1 = cv2.threshold(imgG,127,256,cv2.THRESH_BINARY)
    ret,th2 = cv2.threshold(imgG,127,256,cv2.THRESH_BINARY_INV)
    ret,th3 = cv2.threshold(imgG,127,256,cv2.THRESH_TRUNC)
    ret,th4 = cv2.threshold(imgG,127,256,cv2.THRESH_TOZERO)
    ret,th5 = cv2.threshold(imgG,127,256,cv2.THRESH_TOZERO_INV)
    titles = ['Original', 'BINARY', 'BINARY_INV', 'TRUNC', 'TOZERO', 'TOZERO_INV']
    images = [img, th1, th2, th3, th4, th5]
    plt.figure(figsize=(8, 4), dpi=100)
    for i in range(6):
        plt.subplot(2,3,i+1)
        plt.imshow(images[i],'gray')
        plt.title(titles[i])
        plt.axis('off')
        plt.xticks([])
        plt.yticks([])

#####
def get_ExtractionGrayScaleSimpleThreshould(imgG, lim):
    ret,th1 = cv2.threshold(imgG,lim,256,cv2.THRESH_TRUNC)
    #ret,th1 = cv2.threshold(imgG,lim,256,cv2.THRESH_TRUNC)
    # 情報抽出
    height, width = th1.shape
    # 画素数 = 幅 * 高さ
    size = width * height
    # 情報表示
    print("幅：", width)
    print("高さ：", height)
    xw1 = []  # 結果を入れるリストを用意
    yw1 = []  # 結果を入れるリストを用意
    for i in range(width):
        v1 = th1[int(height/10*5),i] # 画素値 x,y
        xw1.append(i )  # 結果を追加
        yw1.append(v1)  # 結果を追加
        print(i, v1)  # y,x
    fig = plt.figure(figsize=(8, 4), dpi=100)
    fig.suptitle('White Extraction', fontsize=24)
    #plt.title("White Extraction")
    plt.subplot(1,2,1)
    plt.axis('off')
    plt.imshow(th1,'gray') # need 'gray' for drawing w/ gray scale
    plt.subplot(1,2,2)
    plt.plot(xw1, yw1, marker="o", color = "red", linestyle = "--")
    #plt.show()
    #cv2.imshow("Show Image", th1)
    #cv2.waitKey(0)
    #cv2.destroyAllWindows()
    return th1

##### BGRでの白色抽出
def get_ExtractionRGB(img, lim):
    print("#call get_ExtractionRGB")
    bgrLower = np.array([lim, lim, lim])    # 抽出する色の下限(BGR)
    bgrUpper = np.array([256, 256, 256])    # 抽出する色の上限(BGR)
    img_mask = cv2.inRange(img, bgrLower, bgrUpper) # BGRからマスクを作成
    result = cv2.bitwise_and(img, img, mask=img_mask) # 元画像とマスクを合成    
    fig = plt.figure(figsize=(8, 6), dpi=100)
    fig.suptitle('White Extraction', fontsize=24)
    #plt.title("White Extraction")
    plt.axis('off')
    plt.imshow(result)
    #cv2.imshow("Show Image", result)
    #cv2.waitKey(0)
    #cv2.destroyAllWindows()
    return result

##### 画像抜き出し
def get_TrimmedFigure(img,y1,y2,x1,x2):
    print("#call get_TrimmedFigure")
    trimmed = img[y1:y2,x1:x2]
    fig = plt.figure(figsize=(8, 6), dpi=100)
    fig.suptitle('Trimmed Figure', fontsize=24)
    plt.axis('off')
    plt.imshow(trimmed)
    #cv2.imshow("Show Image", img)
    #cv2.waitKey(0)
    #cv2.destroyAllWindows()
    return trimmed

##### ハフ変換による円検出
def detect_HoughCircles(saveName, img,img2 , col):
    print("\n#call detect_HoughCircles")
    if col == 1 : 
        print("figure is colored")
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
    else :
        gray = img
        gray2 = img2
    gray2 = cv2.medianBlur(gray2, 5)
    #ret, th = cv2.threshold(gray2,0,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)
    ret,th = cv2.threshold(gray2,140,255,cv2.THRESH_BINARY)    

    minVal = 100
    maxVal = 200
    edges = cv2.Canny(th, minVal, maxVal)
    
    #cv2.imshow("Show Image", gray)
    #cv2.waitKey(0)
    #cv2.destroyAllWindows()
    #circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1, 20, param1=200, param2=50,minRadius=0,maxRadius=0)
    #circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1, 20, param1=150,param2=40,minRadius=0,maxRadius=0)
    circles = cv2.HoughCircles(edges, cv2.HOUGH_GRADIENT, 1, 20, param1=10,param2=15,minRadius=15,maxRadius=23)
    #circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1, 20, param1=30,param2=15,minRadius=0,maxRadius=0)
    circles = np.squeeze(circles, axis=0)  # (1, N, 3) -> (N, 3)
    # 描画する。
    fig = plt.figure(figsize=(8, 6), dpi=100)
    fig.suptitle('Hough Circles', fontsize=24)
    if circles is not None:
        #for x, y, radius in np.rint(circles).astype(int):
        #    print('center: ({}, {}), radius: {}'.format(x, y, radius))
        #    cv2.circle(img2, (x, y), radius, (10,250, 10), 1)
        #    cv2.circle(img2, (x, y), 2,      (10, 10,250), 1)
        x_ave = 0.
        y_ave = 0.
        r_ave = 0. 
        for i, xyr in enumerate(circles):
            print('center: ({}, {}), radius: {}'.format(xyr[0], xyr[1], xyr[2]))
            cv2.circle(img2, (xyr[0], xyr[1]), xyr[2], (10,250, 10), 1)
            #cv2.circle(img2, (x, y), 22,     (210,250, 10), 1)
            cv2.circle(img2, (xyr[0], xyr[1]), 2,      (10, 10,250), 1)
            x_ave = xyr[0] 
            y_ave = xyr[1]
            r_ave = xyr[2]
    print('(x,y,r) is ({},{},{}).'.format(x_ave, y_ave, r_ave))
    x_ave_int = np.rint(x_ave).astype(int)
    y_ave_int = np.rint(y_ave).astype(int)
    r_ave_int = np.rint(r_ave).astype(int)
    #cv2.circle(img2, (x_ave, y_ave), 20, (210, 210, 10), 1)
    #cv2.imshow("Show Image2", img )
    #cv2.imshow("Show Image2", img )
    #cv2.waitKey(0)
    #cv2.destroyAllWindows()
    plt.axis('off')
#    plt.imshow(cv2.cvtColor(img2, cv2.COLOR_BGR2RGB))
    plt.imshow(img2)

    myfig = plt.figure(figsize = (8, 6))
    myax = myfig.add_subplot(1,3,1)
    plt.imshow(gray, 'gray')
    #cube_circle = patches.Circle((circles[0,0],circles[0,1]), radius = circles[0,2], color = 'w')
    cube_circle = patches.Circle((x_ave_int,y_ave_int), radius = r_ave_int, color = 'w')
    #cube_circle = patches.Circle((circles[0,0],circles[0,1]), radius = 22, color = 'w')

    myax.add_patch(cube_circle)
    mask_circle = np.zeros(img.shape[:2], np.uint8)
    
    cv2.circle(mask_circle, (x_ave_int, y_ave_int), r_ave_int, 255, -1)
    #cv2.circle(mask_circle, (circles[0,0], circles[0,1]), circles[0,2], 255, -1)
    hist_mask = cv2.calcHist([gray],[0],mask_circle, [256], [0,256])
    masked_gray = cv2.bitwise_and(gray, gray, mask = mask_circle)
    myax2 = myfig.add_subplot(1,3,2), plt.imshow(masked_gray, 'gray')
    plt.subplot(1,3,3), plt.plot(hist_mask)
    plt.xlim([0,256])

    np.save('files/file0925/'+saveName+'.npy', hist_mask)
    Info = [x_ave, y_ave, r_ave]
    print(Info)
    return Info
    #print(circles[0,])
    #return circles[0,]

##### BGRでの白色抽出したものに、輪郭抽出
def detect_Outline_wColFigure(img, col, thre):
    print("\n#call detect_Outline_wColFigure")
    if col == 1 :
        print("figure is colored")
        # グレースケールに変換する。
        convGray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        #convGray = cv2.cvtColor(extractWide, cv2.COLOR_BGR2GRAY)
    else :
        convGray = img
    # 輪郭を抽出する。
    # http://pynote.hatenablog.com/entry/opencv-findcontours
    #contours, hierarchy = cv2.findContours(convGray, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    contours, hierarchy = cv2.findContours(convGray, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

    # draw

    fig, ax = plt.subplots(figsize=(8, 6), dpi=100)
    ax.imshow(img)  # 画像を表示する。
    ax.set_axis_off()
    #print(contours)
    max_len = 0
    for i, cnt in enumerate(contours):
    #cv2.circle(mask_circle, (circles[0,0], circles[0,1]), circles[0,2], 255, -1)
        # 形状を変更する。(NumPoints, 1, 2) -> (NumPoints, 2)
        cnt = cnt.squeeze(axis=1)
        
        # 輪郭の周囲の長さ、面積を計算する。


        arclen = cv2.arcLength(cnt, True) # 対象領域が閉曲線の場合、True
        arcare = cv2.contourArea(contours[i])
        print('arc length of contour {}: \n{:.2f}(length), {:.2f}(area)'.format(i, arclen, arcare))

        
        approx_cnt = cv2.approxPolyDP(cnt, epsilon=0.001 * arclen, closed=True)
        print('contour {}: {} -> {}'.format(i, len(cnt), len(approx_cnt)))

        len_approx = cv2.arcLength(approx_cnt, True)
        area_approx = cv2.contourArea(approx_cnt)
        
        print('approximated contour {}: {:.2f}(length), {:.2f}(area)\n'.format(i, len_approx, area_approx))





        if arclen < thre:
            #print('100 < num')
            continue
        # 輪郭の点同士を結ぶ線を描画する。
        #ax.add_patch(Polygon(cnt, color="b", fill=None, lw=2))

        # 輪郭の点を描画する。
        #ax.plot(cnt[:, 0], cnt[:, 1], "ro", mew=0, ms=2)

        approx_cnt = approx_cnt.squeeze(axis=1)
        ax.plot(approx_cnt[:, 0], approx_cnt[:, 1], "ro", mew=0, ms=2)
        # 輪郭の番号を描画する。

        ax.add_patch(Polygon(approx_cnt, color="b", fill=None, lw=2))
        ax.text(cnt[0][0], cnt[0][1], i, color="orange", size="20")
        
        # x,yのmax,minを求める。
        max_x = max(approx_cnt[:,0])
        min_x = min(approx_cnt[:,0])
        max_y = max(approx_cnt[:,1])
        min_y = min(approx_cnt[:,1])
    size_x = max_x - min_x
    size_y = max_y - min_y

    print("x:max, min is {}, {}.".format(max_x, min_x))
    print("y:max, min is {}, {}.".format(max_y, min_y))
    print("the size of qube is ({},{}).".format(size_x, size_y))
    size = [size_x, size_y, max_x, max_y, min_x, min_y]
    return size




def get_PixelValues(saveName, img, col, cube_size):
    print("\n#call get_PixelValues")
    if col == 1 :
        print("figure is colored")
        # グレースケールに変換する。
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        #convGray = cv2.cvtColor(extractWide, cv2.COLOR_BGR2GRAY)
    else :
        gray = img

    '''
    fig, ax = plt.subplots(figsize=(8, 6), dpi=100)
    #### 画像情報
    plt.subplot(1,3,1), 
    plt.axis('off'), 
    plt.imshow(gray,'gray')
    #height, width, ch = extractWide.shape
    '''
    height, width = gray.shape
    size = width * height # 画素数 = 幅 * 高さ
    # 情報表示
    print("幅：", width)
    print("高さ：", height)
    '''
    xw1 = []
    yw1 = []  # 結果を入れるリストを用意
    yw2 = []  # 結果を入れるリストを用意
    yw3 = []  # 結果を入れるリストを用意
    for i in range(width):
        v1 = gray[int(height/10*2),i] # 画素値 x,y
        v2 = gray[int(height/10*5),i] # 画素値 x,y
        v3 = gray[int(height/10*8),i] # 画素値 x,y
        xw1.append(i )  # 結果を追加
        yw1.append(v1)  # 結果を追加
        yw2.append(v2)  # 結果を追加
        yw3.append(v3)  # 結果を追加
        #print(i, v1, v2, v3)  # y,x
    xh1 = []  # 結果を入れるリストを用意
    yh1 = []  # 結果を入れるリストを用意
    yh2 = []  # 結果を入れるリストを用意
    yh3 = []  # 結果を入れるリストを用意
    for i in range(height):
        v1 = gray[i,int(width/10*2)] # 画素値 x,y
        v2 = gray[i,int(width/10*5)] # 画素値 x,y
        v3 = gray[i,int(width/10*8)] # 画素値 x,y
        xh1.append(i )  # 結果を追加
        yh1.append(v1)  # 結果を追加
        yh2.append(v2)  # 結果を追加
        yh3.append(v3)  # 結果を追加
        #print(i, v1, v2, v3)  # y,x

    plt.subplot(1,3,2)
    plt.plot(xw1, yw1, marker="o", markersize=4, color = "red", linestyle = "--")
    plt.plot(xw1, yw2, marker="o", markersize=4, color = "blue", linestyle = "--")
    plt.plot(xw1, yw3, marker="o", markersize=4, color = "green", linestyle = "--")
    plt.subplot(1,3,3)
    plt.plot(xh1, yh1, marker="o", markersize=4, color = "red", linestyle = "--")
    plt.plot(xh1, yh2, marker="o", markersize=4, color = "blue", linestyle = "--")
    plt.plot(xh1, yh3, marker="o", markersize=4, color = "green", linestyle = "--")
    '''

    #真似して書いてみる
    ###################
    gray2 = gray    
    myfig = plt.figure(figsize=(8,6)) 
    myax = myfig.add_subplot(1,3,1)
    plt.axis('off'),
    plt.imshow(gray2,'gray')
    print(cube_size)

    cube_rectangle = patches.Rectangle((cube_size[4],cube_size[5]), cube_size[0], cube_size[1], fill = False, edgecolor='red')
    myax.add_patch(cube_rectangle)
    print(cube_size[0])
    print(cube_size[1])    


    mask_rect = np.zeros(gray.shape[:2], np.uint8)
    mask_rect[cube_size[5]:cube_size[3], cube_size[4]:cube_size[2]] = 255
    masked_gray = cv2.bitwise_and(gray, gray, mask=mask_rect)
    hist_mask = cv2.calcHist([gray], [0], mask_rect, [256], [0,256])
    myax2 = myfig.add_subplot(1,3,2), plt.imshow(masked_gray, 'gray')
    #plt.subplot(1,3,2), plt.imshow(masked_gray, 'gray')
    plt.subplot(1,3,3), plt.plot(hist_mask)
    plt.xlim([0,256])


    np.save('files/file0925/'+saveName+'_whole.npy', hist_mask)
    ###################



def main():
    cam = cv2.VideoCapture(3)
    
    width_cam = int(cam.get(cv2.CAP_PROP_FRAME_WIDTH))
    height_cam = int(cam.get(cv2.CAP_PROP_FRAME_HEIGHT))
    x = width_cam//2
    y = height_cam//2
    while True:
        _, img_cam = cam.read()
        _, img2_cam = cam.read()
        #cv2.line(img_cam, (0, y), (2*x, y), (0,0,255), 1)
        #cv2.line(img_cam, (x, 0), (x, 2*y), (0,0,255), 1)
        #cv2.line(img_cam, (0, 0), (5,0), (0,255,0),1)
        cv2.line(img_cam, (172+160, 405), (406+160,405), (0,255,0),1)
        cv2.line(img_cam, (172+160, 639), (406+160,639), (0,255,0),1)
        cv2.line(img_cam, (172+160, 405), (172+160,639), (0,255,0),1)
        cv2.line(img_cam, (406+160, 405), (406+160,639), (0,255,0),1)
        cv2.line(img_cam, (406+160-117, 405+117-10), (406+160-117,639-117+10), (0,0,255),1)
        cv2.line(img_cam, (172+160+117-10, 639-117), (406+160-117+10,639-117), (0,0,255),1)
        
        cv2.imshow('PUSH ENTER KEY', img_cam)
        key = cv2.waitKey(1)
        if key == ord('s') :
            print('input file name :')
            name_cam = input()
    
            cv2.imwrite("mao_pictures/pic1008/{}.jpg".format(name_cam), img2_cam)
            cv2.imwrite("mao_pictures/grided/{}_grid.jpg".format(name_cam), img_cam)
            print('image is written. Now starting to recognize.')
    
    
    
            start = time.time()
        
        
            saveName  = name_cam 
            ImageName = 'mao_pictures/pic1008/{}.jpg'.format(name_cam) 
            imgG= cv2.imread(ImageName,0)
            imgG= cv2.rotate(imgG, cv2.ROTATE_90_CLOCKWISE)
            img = cv2.imread(ImageName,1)
            img = cv2.rotate(img, cv2.ROTATE_90_CLOCKWISE)
            img = cv2.split(img)
            img = cv2.merge((img[2],img[1],img[0])) # => bgr
            #hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
            print("image is '{}'.".format(ImageName))
            outLineImage = cv2.Canny(imgG, 100,200)
            
            get_FigureInfo(img)
        
            draw_TypicalThresholdProcessing(img,imgG) # input gray scale
            #plt.show()
        
        
            # cube1.jpg :
            img = set_ResizeFigure(img,1)
            img_forHist = set_ResizeFigure(img,1)    
         # BGRでの白色抽出
            result = get_ExtractionRGB(img,100)
            result_forHist = get_ExtractionRGB(img_forHist,100)
            
            #result = get_ExtractionGrayScaleSimpleThreshould(imgG,160) # input gray scaled picture
            # 画像抜き出し
            img = get_TrimmedFigure(img,   160,650,0,500) # 左上0,0: y1,y2,x1,x2
            img_forHist = get_TrimmedFigure(img_forHist,   160,650,0,500) # 左上0,0: y1,y2,x1,x2
            result_forHist = get_TrimmedFigure(result_forHist,   160,650,0,500) # 左上0,0: y1,y2,x1,x2
            #extractWide= get_TrimmedFigure(result,120,393,120,393) # 左上0,0: y1,y2,x1,x2
            #extractLeft= get_TrimmedFigure(result,0,393,0,120) # 左上0,0: y1,y2,x1,x2
            # ハフ変換による円検出
            circleInfo = detect_HoughCircles(saveName, img_forHist, img, 1)
            # 輪郭検出
            #detect_Outline_wColFigure(extractWide, 1, 500)
            cube_size = detect_Outline_wColFigure(result_forHist, 1, 500)
            print(cube_size)


            #detect_Outline_wColFigure(extractLeft, 1, 0)
            #size2 = detect_Outline_wColFigure(result, 1,   0)
        
            get_PixelValues(saveName, img_forHist, 1, cube_size)
        
            elapsed_time = time.time() - start
            print ("elapsed_time:{0}".format(elapsed_time) + "[sec]")    
   
            file = open('files/cube_data1008.txt', 'a')
            Xhole = cube_size[2] - circleInfo[0]
            Yhole = cube_size[3] - circleInfo[1]
            file.write(saveName+' '+str(circleInfo[0])+' '+str(circleInfo[1])+' '+str(circleInfo[2])+' '+str(Xhole)+' '+str(Yhole)+' '+str(cube_size[0])+' '+str(cube_size[1])+'\n')
            file.close()
            
     
            plt.show()


        elif key == 13 : break

    cam.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()


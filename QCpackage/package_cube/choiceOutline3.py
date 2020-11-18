import cv2
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from numba.decorators import jit
import math
#出っ張りを検出する関数
#########################################################################
#@jit
def choice_Outline(img, outxmin, outxmin_y, outymin, outymin_x, outxmax, outxmax_y,  outymax, outymax_x,  xmin, ymin, xmax, ymax, rotx, roty, tan):

###輪郭検出の方から、輪郭の一番外側の4点を持ってくる必要がある。
### outxmin, outxmin_y : 左辺の最外座標
### outxmax, outxmax_y : 右辺の最外座標
### outymin, outymin_x : 上辺の最外座標
### outymax, outymax_x : 下辺の最外座標
### こいつらがあるものだと思って一旦書く。

    print("\n#call choice_Outline")
    #例：outxminが輪郭検出による左の辺、ymaxがハフ直線検出による下の辺

    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    #最終的に出力する変数
    chosenymax = ymax
    chosenymin = ymin
    chosenxmax = xmax
    chosenxmin = xmin
    whiterate = [0]
    #マスク用の画像を用意
    mask_rect = np.zeros(gray.shape[:2], np.uint8)
    #ハフ変換による辺と輪郭検出による辺の差
    gapymin = ymin - outymin
    gapymax = outymax - ymax
    gapxmin = xmin - outxmin
    gapxmax = outxmax - xmax

    delta = 5
    ###出っ張りの高さのピクセル数。　適当に変えつついい感じのところを狙う。
    sigma = 20
    ###白かどうか見る幅のピクセル数。適当に変えつついい感じのところを狙う。

    #画像を角度theta_deg だけ回転する行列を得て、回転を行う。   
    theta_deg =  math.degrees(math.atan(tan))
    center = (rotx,  roty)
    imgsize = (img.shape[1],img.shape[0])
    Mat_aff = cv2.getRotationMatrix2D(center, -theta_deg, scale=1)
    img_rot = cv2.warpAffine(img, Mat_aff, imgsize)
    gray_rot= cv2.cvtColor(img_rot, cv2.COLOR_BGR2GRAY)

 

    #４つの辺に対して以下の同様の操作を行う
    print('gapymin:')
    if gapymin > delta :  ###輪郭の方が直線より外にある時。
        #print('gapymin = {}'.format(gapymin))
        Sgymin = gapymin * 2*sigma #長方形のピクセル数
        Sgy1 = np.zeros((int(gapymin), 2*sigma))
        Sgy1 = gray_rot[int(outymin-1):int(ymin-1), int(outymin_x-sigma):int(outymin_x+sigma)]
        #長方形内部の、threshold(今回は40)より大きい明るさのピクセル数と
        #長方形全体のピクセル数を比較して、適切な範囲であれば出っ張りがあると思い、
        #輪郭検出による辺を出力する。

        whiteymin = round(len(Sgy1[Sgy1 > 40])/Sgymin, 4)  ### 白ピクセルの割合（各辺について求める）
        ### この時点で細かい小数点以下は切っておく
        whiterate.append(whiteymin)
        mask_rect[int(outymin-1):int(ymin-1), int(outymin_x-sigma):int(outymin_x+sigma)] = 255
        print('whiiteymin : ', whiteymin)

         

    print('gapymax:')
    if gapymax > delta :
        Sgymax = gapymax * 2*sigma
        Sgy2 = np.zeros((int(gapymax), 2*sigma))
        Sgy2 = gray_rot[int(ymax+1):int(outymax+1), int(outymax_x-sigma):int(outymax_x+sigma)]

        whiteymax = round(len(Sgy2[Sgy2 > 40])/Sgymax, 4)
        whiterate.append(whiteymax)
        mask_rect[int(ymax+1):int(outymax+1), int(outymax_x-sigma):int(outymax_x+sigma)] = 255
        print('whiteymax : ', whiteymax)


    print('gapxmin:')
    if gapxmin > delta :
        Sgxmin = gapxmin * 2*sigma
        Sgx3 = np.zeros((2*sigma, int(gapxmin)))
        Sgx3 = gray_rot[int(outxmin_y-sigma):int(outxmin_y+sigma), int(outxmin-1):int(xmin-1)]
        
        whitexmin = round(len(Sgx3[Sgx3 > 40])/Sgxmin, 4)
        whiterate.append(whitexmin)
        mask_rect[int(outxmin_y-sigma):int(outxmin_y+sigma), int(outxmin-1):int(xmin-1)] = 255
        print('whitexmin : ', whitexmin)


    print('gapxmax:')
    if gapxmax > delta :
        Sgxmax = gapxmax * 2*sigma
        Sgx4 = np.zeros((2*sigma, int(gapxmax)))
        Sgx4 = gray_rot[int(outxmax_y-sigma):int(outxmax_y+sigma), int(xmax+1):int(outxmax+1)]

        whitexmax = round(len(Sgx4[Sgx4 > 40])/Sgxmax, 4)
        whiterate.append(whitexmax)
        mask_rect[int(outxmax_y-sigma):int(outxmax_y+sigma), int(xmax+1):int(outxmax+1)] = 255
        print('whitexmax : ', whitexmax)
        

    '''
    rectangle = patches.Rectangle((chosenxmin,chosenymin), chosenxmax-chosenxmin, chosenymax-chosenymin, fill=False, edgecolor='red')
    
    fig_rot = plt.figure(figsize=(8,6))
    fig_rot.suptitle('choice_Outline rotation', fontsize=24)
    ax_rot = fig_rot.add_subplot(1,1,1)
    plt.axis('off')
    plt.imshow(gray_rot,'gray')
    ax_rot.add_patch(rectangle)
    masked_gray = cv2.bitwise_and(gray_rot, gray_rot, mask=mask_rect)
    hist_mask = cv2.calcHist([gray_rot], [0], mask_rect, [256], [0,256])
   # print("hist_mask is {}".format(hist_mask)) 
    fig = plt.figure(figsize=(8,6))
    fig.suptitle('choice_Outline', fontsize=24)
    ax = fig.add_subplot(2,2,1), plt.imshow(gray_rot, 'gray')
    plt.subplot(2,2,2), plt.imshow(masked_gray, 'gray')
    plt.subplot(2,2,3), plt.plot(hist_mask)
    plt.xlim([0,256])

    fig2 = plt.figure(figsize=(8,6))
    fig2.suptitle('choice_Outline', fontsize=24)
    plt.imshow(masked_gray,'gray')
    '''
    print('whiterate = {}'.format(whiterate))
    print('whiterate (Max) : {}'.format(max(whiterate)))
    chosenOutline = [chosenxmax, chosenxmin, chosenymax, chosenymin, max(whiterate)]
    print('chosenxmax, chosenxmin, chosenymax, chosenymin, whiterate:{}'.format(chosenOutline))
    return chosenOutline



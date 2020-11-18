import cv2
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from numba.decorators import jit
import math
#出っ張りを検出する関数
#########################################################################
#@jit
def choice_Outline(img, outxmin, outymin, outxmax, outymax, xmin, ymin, xmax, ymax, rotx, roty, tan):
    print("\n#call choice_Outline")
    #例：outxminが輪郭検出による左の辺、ymaxがハフ直線検出による下の辺

    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    #最終的に出力する変数
    chosenymax = ymax
    chosenymin = ymin
    chosenxmax = xmax
    chosenxmin = xmin
    judge = [0]
    #マスク用の画像を用意
    mask_rect = np.zeros(gray.shape[:2], np.uint8)
    #ハフ変換による辺と輪郭検出による辺の差
    gapymin = ymin - outymin
    gapymax = outymax - ymax
    gapxmin = xmin - outxmin
    gapxmax = outxmax - xmax


    #画像を角度theta_deg だけ回転する行列を得て、回転を行う。   
    theta_deg =  math.degrees(math.atan(tan))
    center = (rotx,  roty)
    imgsize = (img.shape[1],img.shape[0])
    Mat_aff = cv2.getRotationMatrix2D(center, -theta_deg, scale=1)
    img_rot = cv2.warpAffine(img, Mat_aff, imgsize)
    gray_rot= cv2.cvtColor(img_rot, cv2.COLOR_BGR2GRAY)

 

    #４つの辺に対して以下の同様の操作を行う
    print('gapymin:')
    if gapymin > 1 :
        #print('gapymin = {}'.format(gapymin))
        Sgymin = gapymin * (outxmax - outxmin) #長方形のピクセル数
        Sgy1 = np.zeros((int(ymin - outymin), int(outxmax - outxmin)))
        Sgy1 = gray_rot[int(outymin-1):int(ymin-1), int(outxmin):int(outxmax)]
        #長方形内部の、threshold(今回は20)より大きい明るさのピクセル数と
        #長方形全体のピクセル数を比較して、適切な範囲であれば出っ張りがあると思い、
        #輪郭検出による辺を出力する。
        if len(Sgy1[Sgy1 > 20]) < 0.4*Sgymin and len(Sgy1[Sgy1 > 20]) > 0.01*Sgymin:
                judge.append(len(Sgy1[Sgy1 > 20])/Sgymin)
                mask_rect[int(outymin-1):int(ymin-1), int(outxmin):int(outxmax)] = 255
                chosenymin = outymin
                print(len(Sgy1[Sgy1 > 20])/Sgymin)
                print('judge.append(2)')

    print('gapymax:')
    if gapymax > 1 :
        Sgymax = gapymax * (outxmax - outxmin)
        Sgy2 = np.zeros((int(outymax - ymax), int(outxmax - outxmin)))
        Sgy2 = gray_rot[int(ymax+1):int(outymax+1), int(outxmin):int(outxmax)]
        if len(Sgy2[Sgy2 > 20]) < 0.4*Sgymax and len(Sgy2[Sgy2 > 20]) > 0.01*Sgymax:
                judge.append(len(Sgy2[Sgy2 > 20])/Sgymax)
                mask_rect[int(ymax+1):int(outymax+1), int(outxmin):int(outxmax)] = 255
                chosenymax = outymax
                print(len(Sgy2[Sgy2 > 20])/Sgymax)
                print('judge.append(2)')

    print('gapxmin:')
    if gapxmin > 1 :
        Sgxmin = gapxmin * (outymax - outymin)
        Sgx3 = np.zeros((int(outymax - outymin), int(xmin - outxmin)))
        Sgx3 = gray_rot[int(outymin):int(outymax), int(outxmin-1):int(xmin-1)]
        if len(Sgx3[Sgx3 > 20]) < 0.4*Sgxmin and len(Sgx3[Sgx3 > 20]) > 0.01*Sgxmin:
                judge.append(len(Sgx3[Sgx3 > 20])/Sgxmin)
                mask_rect[int(outymin):int(outymax), int(outxmin-1):int(xmin-1)] = 255
                chosenxmin = outxmin
                print(len(Sgx3[Sgx3 > 20])/Sgxmin)
                print('judge.append(2)')

    print('gapxmax:')
    if gapxmax > 1 :
        Sgxmax = gapxmax * (outymax - outymin)
        Sgx4 = np.zeros((int(outymax - outymin), int(outxmax - xmax)))
        Sgx4 = gray_rot[int(outymin):int(outymax), int(xmax+1):int(outxmax+1)]
        if len(Sgx4[Sgx4 > 20]) < 0.4*Sgxmax and len(Sgx4[Sgx4 > 20]) > 0.01*Sgxmax:
                judge.append(len(Sgx4[Sgx4 > 20])/Sgxmax)
                mask_rect[int(outymin):int(outymax), int(xmax+1):int(outxmax+1)] = 255
                chosenxmax = outxmax
                print(len(Sgx4[Sgx4 > 20])/Sgxmax)
                print('judge.append(2)')


#    '''
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
#    '''
    print('judge = {}'.format(judge))
    print('bump judgement : {}'.format(max(judge)))
    chosenOutline = [chosenxmax, chosenxmin, chosenymax, chosenymin, max(judge)]
    print('chosenxmax, chosenxmin, chosenymax, chosenymin, judge:{}'.format(chosenOutline))
    return chosenOutline



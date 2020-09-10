import cv2
import numpy as np
import matplotlib.pyplot as plt

#出っ張りを検出する関数
#########################################################################
def choice_Outline(img, outxmin, outymin, outxmax, outymax, xmin, ymin, xmax, ymax):
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


    #４つの辺に対して以下の同様の操作を行う
    print('gapymin:')
    if gapymin > 1 :
        #print('gapymin = {}'.format(gapymin))
        Sgymin = gapymin * (outxmax - outxmin) #長方形のピクセル数
        Sgy1 = np.zeros(ymin - outymin, outxmax - outxmin)
        Sgy1 = gray[outymin-1:ymin-1, outxmin:outxmax]
        #長方形内部の、threshold(今回は20)より大きい明るさのピクセル数と
        #長方形全体のピクセル数を比較して、適切な範囲であれば出っ張りがあると思い、
        #輪郭検出による辺を出力する。
        if len(Sgy1[Sgy1 > 20]) < 0.4*Sgymin and len(Sgy1[Sgy1 > 20]) > 0.01*Sgymin:
            if len(Sgy1[Sgy1 > 20]) < 0.05*Sgymin:
                judge.append(len(Sgy1[Sgy1 > 20])/Sgymin)
                print('judge.append(1)')
            else:
                print(len(Sgy1[Sgy1 > 20])/Sgymin)
                print(Sgymin)
                mask_rect[outymin-1:ymin-1, outxmin:outxmax] = 255
                chosenymin = outymin
                judge.append(len(Sgy1[Sgy1 > 20])/Sgymin)
                print('judge.append(2)')

    print('gapymax:')
    if gapymax > 1 :
        Sgymax = gapymax * (outxmax - outxmin)
        Sgy2 = np.zeros(outymax - ymax, outxmax - outxmin)
        Sgy2 = gray[ymax+1:outymax+1, outxmin:outxmax]
        if len(Sgy2[Sgy2 > 20]) < 0.4*Sgymax and len(Sgy2[Sgy2 > 20]) > 0.01*Sgymax:
            if len(Sgy2[Sgy2 > 20]) < 0.05*Sgymax:
                judge.append(len(Sgy2[Sgy2 > 20])/Sgymax)
                print('judge.append(1)')
            else:
                print(len(Sgy2[Sgy2 > 20])/Sgymax)
                print(Sgymax)
                mask_rect[ymax+1:outymax+1, outxmin:outxmax] = 255
                chosenymax = outymax
                judge.append(len(Sgy2[Sgy2 > 20])/Sgymax)
                print('judge.append(2)')



    print('gapxmin:')
    if gapxmin > 1 :
        Sgxmin = gapxmin * (outymax - outymin)
        Sgx3 = np.zeros(outymax - outymin, xmin - outxmin)
        Sgx3 = gray[outymin:outymax, outxmin-1:xmin-1]
        if len(Sgx3[Sgx3 > 20]) < 0.4*Sgxmin and len(Sgx3[Sgx3 > 20]) > 0.01*Sgxmin:
            if len(Sgx3[Sgx3 > 20]) < 0.05*Sgxmin:
                judge.append(len(Sgx3[Sgx3 > 20])/Sgxmin)
                print('judge.append(1)')
            else:
                print(len(Sgx3[Sgx3 > 20])/Sgxmin)
                print(Sgxmin)
                mask_rect[outymin:outymax, outxmin-1:xmin-1] = 255
                chosenxmin = outxmin
                judge.append(len(Sgx3[Sgx3 > 20])/Sgxmin)
                print('judge.append(2)')

    print('gapxmax:')
    if gapxmax > 1 :
        Sgxmax = gapxmax * (outymax - outymin)
        Sgx4 = np.zeros(outymax - outymin, outxmax - xmax)
        Sgx4 = gray[outymin:outymax, xmax+1:outxmax+1]
        if len(Sgx4[Sgx4 > 20]) < 0.4*Sgxmax and len(Sgx4[Sgx4 > 20]) > 0.01*Sgxmax:
            if len(Sgx4[Sgx4 > 20]) < 0.05*Sgxmax:
                judge.append(len(Sgx4[Sgx4 > 20])/Sgxmax)
                print('judge.append(1)')
            else:
                print(len(Sgx4[Sgx4 > 20])/Sgxmax)
                print(Sgxmax)
                mask_rect[outymin:outymax, xmax+1:outxmax+1] = 255
                chosenxmax = outxmax
                judge.append(len(Sgx4[Sgx4 > 20])/Sgxmax)
                print('judge.append(2)')


    masked_gray = cv2.bitwise_and(gray, gray, mask=mask_rect)
    hist_mask = cv2.calcHist([gray], [0], mask_rect, [256], [0,256])
   # print("hist_mask is {}".format(hist_mask)) 
    fig = plt.figure(figsize=(8,6))
    fig.suptitle('choice_Outline', fontsize=24)
    ax = fig.add_subplot(2,2,1), plt.imshow(gray, 'gray')
    plt.subplot(2,2,2), plt.imshow(masked_gray, 'gray')
    plt.subplot(2,2,3), plt.plot(hist_mask)
    plt.xlim([0,256])

    fig2 = plt.figure(figsize=(8,6))
    fig2.suptitle('choice_Outline', fontsize=24)
    plt.imshow(masked_gray,'gray')
    print('judge = {}'.format(judge))
    print('bump judgement : {}'.format(max(judge)))
    chosenOutline = [chosenxmax, chosenxmin, chosenymax, chosenymin]
    return chosenOutline



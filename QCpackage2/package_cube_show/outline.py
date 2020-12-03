import cv2
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon
import numpy as np
##### BGRでの白色抽出したものに、輪郭抽出
def detect_Outline_wColFigure(img, col, thre, rotx, roty, Mat_rot):
    print("\n#call detect_Outline_wColFigure")
    if col == 1 :
        print("figure is colored")
        # グレースケールに変換する。
        convGray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    else :
        convGray = img
    # 輪郭を抽出する。
    # http://pynote.hatenablog.com/entry/opencv-findcontours
    contours, hierarchy = cv2.findContours(convGray, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

    # draw
#    '''
    fig, ax = plt.subplots(figsize=(8, 6), dpi=100)
    fig.suptitle('Outline', fontsize=24)
    ax.imshow(img)  # 画像を表示する。
    ax.set_axis_off()
    #print(contours)
#    '''
    for i, cnt in enumerate(contours):
        # 形状を変更する。(NumPoints, 1, 2) -> (NumPoints, 2)
        cnt = cnt.squeeze(axis=1)

        
        # 輪郭の周囲の長さ、面積を計算する。

        arclen = cv2.arcLength(cnt, True) # 対象領域が閉曲線の場合、True
        arcare = cv2.contourArea(contours[i])
        
        
        approx_cnt = cv2.approxPolyDP(cnt, epsilon=0.0005 * arclen, closed=True)
        

        len_approx = cv2.arcLength(approx_cnt, True)
        area_approx = cv2.contourArea(approx_cnt)







        if arclen < thre:
            #print('100 < num')
            continue
        print('arc length of contour {}: \n{:.2f}(length), {:.2f}(area)'.format(i, arclen, arcare))
        print('contour {}: {} -> {}'.format(i, len(cnt), len(approx_cnt)))
        print('approximated contour {}: {:.2f}(length), {:.2f}(area)'.format(i, len_approx, area_approx))


        approx_cnt = approx_cnt.squeeze(axis=1)
        print('approx_cnt = {}'.format(approx_cnt))
        Approx_cnt = np.zeros((2,2)) ###初めに[0,0]配列を生成
       # print('Mat = {}'.format(Mat_rot))
        for i, xy in enumerate(approx_cnt):
           # print('xy = {}'.format(xy))
            x = xy[0]-rotx
            y = xy[1]-roty  ###回転中心からの座標に変換
            xy0 = np.array([x, y])
            XY0 = np.dot(Mat_rot, xy0) ###このXY0 は回転中心からの座標。
                                       ###絶対座標に直す？必要ない気がするなぁ。
                                            
            XY0 = XY0 + [rotx, roty]   ###一応絶対座標に戻してみる。
           # print('i={}, XY0={}'.format(i, XY0))
            Approx_cnt = np.insert(Approx_cnt, i, XY0, axis=0 ) ###配列を追加   
        Approx_cnt = np.delete(Approx_cnt, -1 , axis=0) ###初めのゼロ成分の行を削除する
        Approx_cnt = np.delete(Approx_cnt, -1 , axis=0) 
       # print(Approx_cnt)
#        '''
        ax.plot(Approx_cnt[:, 0], Approx_cnt[:, 1], "ro", mew=0, ms=2)
        # 輪郭の番号を描画する。

        ax.add_patch(Polygon(approx_cnt, color="b", fill=None, lw=2))
        ax.text(cnt[0][0], cnt[0][1], i, color="orange", size="20")
#        '''
        # x,yのmax,minを求める。
        max_x = max(Approx_cnt[:,0])
        min_x = min(Approx_cnt[:,0])
        max_y = max(Approx_cnt[:,1])
        min_y = min(Approx_cnt[:,1])
    
        ### 対応する座標を求め、出っ張り検出で使う。
        max_x_y = Approx_cnt[:,1][np.argmax(Approx_cnt[:,0])]
        min_x_y = Approx_cnt[:,1][np.argmin(Approx_cnt[:,0])]
        max_y_x = Approx_cnt[:,0][np.argmax(Approx_cnt[:,1])]
        min_y_x = Approx_cnt[:,0][np.argmin(Approx_cnt[:,1])]

        size_x = max_x - min_x
        size_y = max_y - min_y

        print("x:max, min is {}, {}.".format(max_x, min_x))
        print("y:max, min is {}, {}.".format(max_y, min_y))
        print("the size(cnt) of cube is ({},{}).\n".format(size_x, size_y))

        size = [size_x, size_y, max_x, max_y, min_x, min_y, max_x_y, min_x_y, max_y_x, min_y_x]
        
    return size

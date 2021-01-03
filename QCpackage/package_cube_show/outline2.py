import cv2
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon
import numpy as np
##### BGRでの白色抽出したものに、輪郭抽出
def detect_Outline_wColFigure(img, col, thre):
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


#        '''
        ax.add_patch(Polygon(approx_cnt, color="b", fill=None, lw=2))
        ax.text(cnt[0][0], cnt[0][1], i, color="orange", size="20")
#        '''

        

        # x,yのmax,minを求める。
        max_x = max(approx_cnt[:,0])
        min_x = min(approx_cnt[:,0])
        max_y = max(approx_cnt[:,1])
        min_y = min(approx_cnt[:,1])
    

        size_x = max_x - min_x
        size_y = max_y - min_y



        print("x:max, min is {}, {}.".format(max_x, min_x))
        print("y:max, min is {}, {}.".format(max_y, min_y))
        print("the size(cnt) of cube is ({},{}).\n".format(size_x, size_y))

        size = [min_x, min_y, max_x, max_y]
        
    return size

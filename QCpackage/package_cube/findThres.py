import time
import cv2


#明るさのthresholdを決定する関数
#####################################################################
def findThreshold(img, rhole):
    startTh = time.time()
    print("\n#call findThreshold")
    print('image size:{}'.format(img.shape))
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    colsumx = 0
    colsumy = 0
    for dr in range(int(2*rhole)):

        colsumx = colsumx + img[10, 30+dr] ###トリム画像による。
        colsumy = colsumy + img[30+dr, 10] ###トリム画像による。

    colmeanx = colsumx / int(2*rhole)
    colmeany = colsumy / int(2*rhole)
    print('colmeanx = {}'.format(colmeanx))
    print('colmeany = {}'.format(colmeany))

    colmean =  max(colmeanx, colmeany)
    print('findThres time: {} sec'.format(time.time()-startTh))
    return colmean



import cv2
import time
import numpy as np
import matplotlib.pyplot as plt
#############ハフ変換による円検出
def detect_HoughCircles(saveName,img,img2,img3,img4, col):
    circlestart = time.time()
    print("\n#call detect_HoughCircles")
    if col == 1 : 
        print("figure is colored")
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
        gray3 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
    else :
        gray = img
        gray2 = img2
        gray3 = img3
    gray2 = cv2.GaussianBlur(gray2, (5,5), 0)
#    gray3 = cv2.GaussianBlur(gray3, (9,9), 5)
    gray3 = cv2.GaussianBlur(gray3, (5,5), 0)
    ret,th = cv2.threshold(gray2, 100,255,cv2.THRESH_BINARY)
    ret2,th2 = cv2.threshold(gray3, 100,255,cv2.THRESH_BINARY)


    minVal = 100
    maxVal = 200
    edges = cv2.Canny(th, minVal, maxVal)
    edges2 = cv2.Canny(th2, minVal, maxVal)
    vote = 20
    while(True):
        print("challenge at vote = {}:".format(vote)) 

        circles = cv2.HoughCircles(edges, cv2.HOUGH_GRADIENT, 1, 1000, 
                  param1=15,param2=vote,minRadius=47,maxRadius=52)
        circles = np.squeeze(circles, axis=0)  # (1, N, 3) -> (N, 3)
        if circles.any() !=  None:
            print("circle is detected!")
            break 
        vote -= 1
        if vote == 0 : 
                
            print('cannot detect any circles!!')
            Info = [0,0,0,0,0,0,0]
            hist_mask = np.zeros(256)
            x_hole = 0.
            y_hole = 0.
            r_hole = 0.
   #         np.save('files/1114bad1/th150/'+saveName+'.npy', hist_mask)
            return Info
        
    print(circles) 
    x_hole = 0.
    y_hole = 0.
    r_hole = 0.
    
    for i, xyr in enumerate(circles):
        print('center: ({}, {}), radius: {}'.format(xyr[0], xyr[1], xyr[2]))
        cv2.circle(img2, (xyr[0], xyr[1]), xyr[2], (10,250, 10), 1)
        cv2.circle(img2, (xyr[0], xyr[1]), 2,      (10, 10,250), 1)
        cv2.circle(edges, (xyr[0], xyr[1]), xyr[2], (210,50, 210), 1)
        cv2.circle(edges, (xyr[0], xyr[1]), 2,      (210, 210,50), 1)
        x_hole = xyr[0]
        y_hole = xyr[1]
        r_hole = xyr[2]
################################################################################   
#エッジと円周の距離最小化
    

################################################################################               
    cv2.circle(th2, (int(x_hole), int(y_hole)), int(r_hole), (210,50, 210), 1)
    cv2.circle(th2, (int(x_hole), int(y_hole)), 2, (210,50, 210), 1)

    cv2.circle(th2, (int(x_hole), int(y_hole)), 2, (100,50, 210), 1)
    

    cv2.circle(edges2, (int(x_hole), int(y_hole)), 2, (100,50, 210), 1)
    
    
    cv2.circle(img4, (int(x_hole), int(y_hole)), int(r_hole), (210,50, 210), 1)
    cv2.circle(img4, (int(x_hole), int(y_hole)), 2, (210,50, 210), 1)
    cv2.circle(img4, (int(x_hole), int(y_hole)), 2, (100,50, 210), 1)

    # 描画する。
    '''
    fig = plt.figure(figsize=(8, 6), dpi=100)
    fig.suptitle('Hough Circles', fontsize=24)
    '''

    
    print('average (x,y,r) is ({},{},{}).'.format(x_hole, y_hole, r_hole))
    #circlestart=time.time()
    x_hole_int = np.rint(x_hole).astype(int)
    y_hole_int = np.rint(y_hole).astype(int)
    r_hole_int = np.rint(r_hole).astype(int)
    radius = r_hole_int
#    if r_hole >= 18 :
 #       radius = r_hole_int - 1 




    '''     
    plt.axis('off')
    
    plt.subplot(221)
    plt.imshow(img2)
    plt.subplot(222)
    #plt.imshow(edges)
    plt.imshow(th2)
    plt.subplot(223)
    plt.imshow(edges2)
    plt.subplot(224)
    plt.imshow(img4)
    '''


    Info = [x_hole, y_hole, r_hole, vote, edges2]
    #print(Info)
    print('circle time : {} sec'.format(time.time()-circlestart))
    return Info

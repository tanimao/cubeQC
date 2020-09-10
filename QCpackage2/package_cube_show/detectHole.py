import cv2
import numpy as np
import matplotlib.pyplot as plt


#穴の中心を検出する関数
#####################################################################
def detect_HoleCenter(img, img2, colmean, rate, radius):
    print("\n#call detect_Hole")
    
    th = colmean * rate
    img_forDraw = img2
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    height, width, ch = img.shape
    holeimg = np.zeros(gray.shape[:2], np.uint8)
    print ("height, width : {}, {}".format(height, width))
    gray = cv2.GaussianBlur(gray, (5,5), 0)
    #gray = cv2.GaussianBlur(gray, (9,9), 5)

    ret,binary = cv2.threshold(gray,th,255,cv2.THRESH_BINARY)
    
    median_x = 0
    median_y = 0
    num_y = np.zeros(height)
    num_x = np.zeros(width)
    for yi, pixels in enumerate(binary):
        for xi, pixel in enumerate(pixels):
            if pixel == 0:
                num_y[yi] = num_y[yi] + 1
                num_x[xi] = num_x[xi] + 1
    

    Ny = num_y.sum()
    Sy = 0
    Nx = num_x.sum()
    Sx = 0
    for yi in range(height):
        Sy = Sy + num_y[yi]
        if Sy >= int(Ny/2):
            median_y = yi
            break
    
    for xi in range(width):
        Sx = Sx + num_x[xi]
        if Sx >= int(Nx/2):
            median_x =xi
            break
#    '''
    cv2.circle(img_forDraw, (int(median_x), int(median_y)), 1, (150,10, 100), 1)
    cv2.circle(img_forDraw, (int(median_x), int(median_y)), radius, (150,10, 100), 1)
    cv2.circle(binary, (int(median_x), int(median_y)), 1, (150,10, 100), 1)
    cv2.circle(binary, (int(median_x), int(median_y)), radius, (150,10, 100), 1)
    
    cv2.circle(img_forDraw, (int(width/2), int(height/2)), 1, (10,150, 100), 1)


    fig = plt.figure(figsize=(8,6) ,dpi=100)
    fig.suptitle('extract hole', fontsize=24)
    ax = fig.add_subplot(1,2,1), plt.imshow(img_forDraw, 'gray')
    plt.subplot(122)
    plt.imshow(binary)
#    '''
    print("xholecenter, yholecenter is {}, {}".format(median_x, median_y))
    #print('Estimate = {}'.format(Estimate))
    
    medians = [median_x, median_y]
    return medians

##############################################################################





import cv2
import numpy as np
from matplotlib import pyplot as plt
import matplotlib.patches as patches


minVal = 100
maxVal = 200
img = cv2.imread('mao_pictures/1115test.jpg',0)
img = cv2.GaussianBlur(img, (5,5), 0)
ret,th = cv2.threshold(img,100,255,cv2.THRESH_BINARY)
edges = cv2.Canny(th, minVal, maxVal)

cv2.namedWindow('image desu.')
plt.subplot(131),plt.imshow(img, cmap = 'gray')
plt.title('Original'), plt.xticks([]),plt.yticks([])
plt.subplot(132),plt.imshow(th,cmap = 'gray')
plt.title('thres'), plt.xticks([]), plt.yticks([])
plt.subplot(133),plt.imshow(edges,cmap = 'gray')
plt.title('Edge'), plt.xticks([]), plt.yticks([])


circles = cv2.HoughCircles(edges, cv2.HOUGH_GRADIENT, 1, 500, param1=15,param2=15,minRadius=30,maxRadius=70)

circles = np.squeeze(circles, axis=0)  # (1, N, 3) -> (N, 3)
fig = plt.figure(figsize=(8, 6), dpi=100)
fig.suptitle('Hough Circles', fontsize=24)

print(circles)
if circles.any() == None:
    print('cannot detect circles!!')

else :
   # for x, y, radius in np.rint(circles).astype(int):
   #     print('center: ({}, {}), radius: {}'.format(x, y, radius))
    print(circles)
    print(circles[0])
    x_ave = 0.
    y_ave = 0.
    r_ave = 0.
    for i, xyr in enumerate(circles):
        print('center: ({}, {}), radius: {}'.format(xyr[0], xyr[1], xyr[2]))
        cv2.circle(img, (xyr[0], xyr[1]), xyr[2], (10,250, 10), 1)
        cv2.circle(img, (xyr[0], xyr[1]), 2,      (150, 150,250), 1)
        cv2.circle(th, (xyr[0], xyr[1]), xyr[2], (110,250, 100), 1)
        cv2.circle(th, (xyr[0], xyr[1]), 2,      (150, 150,250), 1)
        cv2.circle(edges, (xyr[0], xyr[1]), xyr[2], (110,250, 100), 1)
        cv2.circle(edges, (xyr[0], xyr[1]), 2,      (150, 150,250), 1)
        x_ave = xyr[0]
        y_ave = xyr[1]
        r_ave = xyr[2]

ax1 = fig.add_subplot(2,2,1)
plt.imshow(th)
ax2 = fig.add_subplot(2,2,2)
plt.imshow(img)
ax3 = fig.add_subplot(2,2,3)
plt.imshow(edges)
#plt.gray()
plt.show() 

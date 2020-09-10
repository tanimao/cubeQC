import cv2
import numpy as np
from matplotlib import pyplot as plt





minVal = 100
maxVal = 550
img = cv2.imread('mao_pictures/pic1008good/good27_4.jpg',0)
img = cv2.GaussianBlur(img, (5,5), 0)

#ret, th = cv2.threshold(img,0,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)
ret,th = cv2.threshold(img,180,255,cv2.THRESH_BINARY)

edges1 = cv2.Canny(img, minVal, maxVal)
edges2 = cv2.Canny(th, minVal, maxVal)
cv2.namedWindow('image desu.')
plt.subplot(141),plt.imshow(img, cmap = 'gray')
plt.title('Original'), plt.xticks([]),plt.yticks([])
plt.subplot(142),plt.imshow(th, cmap = 'gray')
plt.title('binary'), plt.xticks([]), plt.yticks([])
plt.subplot(143),plt.imshow(edges1, cmap = 'gray')
plt.title('Edge1'), plt.xticks([]), plt.yticks([])
plt.subplot(144),plt.imshow(edges2,cmap = 'gray')
plt.title('Edge2'), plt.xticks([]), plt.yticks([])

plt.show() 

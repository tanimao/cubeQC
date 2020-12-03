import numpy as np
import cv2

while True:
    for i in range(10):
        for j in range(6):
            img = cv2.imread('../mao_pictures/pic0925/bad_cube_1'+str(j+1)+'.jpg',1)
    
            cv2.imshow("title", img)
            k = cv2.waitKey(1)
            if k == 13 : break
#        if k == ord('n'):
#            continue
#        elif k == 13 : break
cv2.destroyAllWindows()

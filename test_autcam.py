import cv2
import time

cam = cv2.VideoCapture(3)



i = 0
while True:
    _, img_cam = cam.read()
    _, img2_cam = cam.read()
    cv2.imshow('PUSH ENTER KEY', img_cam)
        
        #key = cv2.waitKey(1)    
        #if key == ord('s') : 
        
    
            
        key = cv2.waitKey(1) & 0xFF
        #if key == ord('s'):
            #time.sleep(7)
            #print("now taking...")
            #time.sleep(3)
        if i == cycle:
            i = 0
            cv2.imwrite("mao_pictures/test0930/test_bad11_15mm{}.jpg".format(i), img_cam)
            
            print("picture {} is captured.".format(i)) 
        i +=1
            '''

            print('input file name :')
            name_cam = input()
        
            cv2.imwrite("mao_pictures/{}.jpg".format(name_cam), img2_cam)
            print('image is written. Now starting to recognize.')
            '''
        if key == 13 : break

cam.release()
cv2.destroyAllWindows()

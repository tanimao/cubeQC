import cv2


cam = cv2.VideoCapture(0)
cam2 = cv2.VideoCapture(2)
cam3 = cv2.VideoCapture(4)
width_cam = int(cam.get(cv2. CAP_PROP_FRAME_WIDTH))
height_cam = int(cam.get(cv2.CAP_PROP_FRAME_HEIGHT))
x = width_cam//2
y = height_cam//2
#for i in range(1000000):
def read_Cam(cam, cam2, cam3, x, y):
    while True:
    
        _, img_cam = cam.read()
        _, img2_cam = cam.read()
        
        cv2.line(img2_cam, (0, y), (2*x, y), (0,0,255), 1)
        cv2.line(img2_cam, (x, 0), (x, 2*y), (0,0,255), 1)
        cv2.line(img2_cam, (0, 0), (5,0), (0,255,0),1)
        cv2.namedWindow('cam 1', cv2.WINDOW_NORMAL)
        cv2.imshow('cam 1', img2_cam)
    
        _, img_cam2 = cam2.read()
        _, img2_cam2 = cam2.read()
        
        cv2.line(img2_cam2, (0, y), (2*x, y), (0,0,255), 1)
        cv2.line(img2_cam2, (x, 0), (x, 2*y), (0,0,255), 1)
        cv2.line(img2_cam2, (0, 0), (5,0), (0,255,0),1)
        cv2.namedWindow('cam 2', cv2.WINDOW_NORMAL)
        cv2.imshow('cam 2', img2_cam2)
        
        _, img_cam3 = cam3.read()
        _, img2_cam3 = cam3.read()
        
        cv2.line(img2_cam3, (0, y), (2*x, y), (0,0,255), 1)
        cv2.line(img2_cam3, (x, 0), (x, 2*y), (0,0,255), 1)
        cv2.line(img2_cam3, (0, 0), (5,0), (0,255,0),1)
        cv2.namedWindow('cam 3', cv2.WINDOW_NORMAL)
        cv2.imshow('cam 3', img2_cam3)
    

def read_Camera():
    read_Cam(cam, cam2, cam3, x, y)


cubeID = 1
def write_pic(img_cam, img_cam2, img_cam3, cubeID):
    #if key == ord('f') : 
        print('first taking:')
       # print('input file name :')
       # name_cam = input()
        
        cv2.imwrite('mao_pictures/pic0207/cube{}1.jpg'.format(cubeID), img_cam)
        cv2.imwrite('mao_pictures/pic0207/cube{}2.jpg'.format(cubeID), img_cam2)
        cv2.imwrite('mao_pictures/pic0207/cube{}3.jpg'.format(cubeID), img_cam3)
        print('image is taken.')

    #if key == ord('s') : 
        print('second taking:')
       # print('input file name :')
       # name_cam = input()
        
        cv2.imwrite('mao_pictures/pic0207/cube{}4.jpg'.format(cubeID), img_cam)
        cv2.imwrite('mao_pictures/pic0207/cube{}5.jpg'.format(cubeID), img_cam2)
        cv2.imwrite('mao_pictures/pic0207/cube{}6.jpg'.format(cubeID), img_cam3)
        print('image is taken.')

    #elif key == 13 : break

    
read_Camera()
cam.release()
cam2.release()
cam3.release()
cv2.destroyAllWindows()

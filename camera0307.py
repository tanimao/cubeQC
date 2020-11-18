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
    cubeID=1
    Num=1
    surfID=1
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
        
        key = cv2.waitKey(1)    
        Num, cubeID, surfID = write_pic(img_cam, img_cam2, img_cam3, cubeID, surfID, Num, key)
    


def write_pic(img_cam, img_cam2, img_cam3, cubeID, surfID, Num, key):
    if key == ord('1') : 
        print('cam1:')
        cv2.imwrite('mao_pictures/pic0323/cube{0}{1}cam1{2}.jpg'.format(cubeID, surfID, Num), img_cam)
        print('mao_pictures/pic0323/cube{0}{1}cam1{2}.jpg'.format(cubeID, surfID, Num))
        if Num < 5:
            Num=Num+1
        if Num == 5:
            Num=1


    if key == ord('2') : 
        print('cam2:')
        cv2.imwrite('mao_pictures/pic0323/cube{0}{1}cam2{2}.jpg'.format(cubeID, surfID, Num), img_cam2)
        print('mao_pictures/pic0323/cube{0}{1}cam2{2}.jpg'.format(cubeID, surfID, Num))
        if Num < 5:
            Num=Num+1
        if Num == 5:
            Num=1


    if key == ord('3') :
        print('cam3:')
        cv2.imwrite('mao_pictures/pic0323/cube{0}{1}cam3{2}.jpg'.format(cubeID, surfID, Num), img_cam3)
        print('mao_pictures/pic0323/cube{0}{1}cam3{2}.jpg'.format(cubeID, surfID, Num))
        if Num < 5:
            Num=Num+1
        if Num == 5:
            Num= 1

    if key == ord('c') :
        cubeID=cubeID+1
        surfID=1
        print('cubeID={}, surfID={}.'.format(cubeID, surfID))
    
    if key == ord('s') :
        
        if surfID < 7:
            surfID=surfID+1
        if surfID == 7 :
            surfID=1
        print('surfID={}.'.format(surfID))
    ID = [Num, cubeID, surfID]
    return ID

    

read_Cam(cam, cam2, cam3, x, y)
cam.release()
cam2.release()
cam3.release()
cv2.destroyAllWindows()

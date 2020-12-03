import cv2


cam = cv2.VideoCapture(1)
cam2 = cv2.VideoCapture(4)
width_cam = int(cam.get(cv2. CAP_PROP_FRAME_WIDTH))
height_cam = int(cam.get(cv2.CAP_PROP_FRAME_HEIGHT))
x = width_cam//2
y = height_cam//2
#for i in range(1000000):
def read_Cam(cam, cam2, x, y):
    cubeID=1
    surfID=1
    surfcamID=0
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
        
        
        
        key = cv2.waitKey(1)    
        cubeID, surfcamID = write_pic(img_cam, img_cam2, cubeID, surfID,  key, surfcamID)
    


def write_pic(img_cam, img_cam2, cubeID, surfID, key, surfcamID):
    '''
    surfcam1 = [11, 12, 13, 14, 21, 22, 23, 24, 31, 32, 33, 34, 
                41, 42, 43, 44, 51, 52, 53, 54, 61, 62, 63, 64]

    surfcam2 = [32, 64, 51, 23, 12, 54, 41, 33, 22, 44, 61, 13,
                62, 34, 21, 53, 42, 24, 11, 63, 52, 14, 31, 43]

    surfcam3 = [24, 33, 61, 52, 34, 13, 51, 42, 14, 23, 41, 62,
                54, 63, 31, 22, 64, 43, 21, 12, 44, 53, 11, 32]

    if key == ord('1') : 
        print('cam1,2,3:')
        cv2.imwrite('mao_pictures/pic0415/cube{0}cam1_{1}.jpg'.format(cubeID, surfcam1[surfcamID]), img_cam)
        print('mao_pictures/pic0415/cube{0}cam1_{1}.jpg'.format(cubeID, surfcam1[surfcamID]))
        cv2.imwrite('mao_pictures/pic0415/cube{0}cam2_{1}.jpg'.format(cubeID, surfcam2[surfcamID]), img_cam2)
        print('mao_pictures/pic0325/cube{0}cam2_{1}.jpg'.format(cubeID, surfcam2[surfcamID]))
        cv2.imwrite('mao_pictures/pic0415/cube{0}cam3_{1}.jpg'.format(cubeID, surfcam3[surfcamID]), img_cam3)
        print('mao_pictures/pic0415/cube{0}cam3_{1}.jpg'.format(cubeID, surfcam3[surfcamID]))
    
        surfcamID = surfcamID + 1
    '''
    surfcam1 = [11, 
                41]

    surfcam2 = [32,
                62]

    surfcam3 = [24,
                54]

    if key == ord('1') : 
        print('cam1,2,3:')
        cv2.imwrite('mao_pictures/pic0415bad/cube{0}cam1_{1}.jpg'.format(cubeID, surfcam1[surfcamID]), img_cam)
        print('mao_pictures/pic0415bad/cube{0}cam1_{1}.jpg'.format(cubeID, surfcam1[surfcamID]))
        cv2.imwrite('mao_pictures/pic0415bad/cube{0}cam2_{1}.jpg'.format(cubeID, surfcam2[surfcamID]), img_cam2)
        print('mao_pictures/pic0325/cube{0}cam2_{1}.jpg'.format(cubeID, surfcam2[surfcamID]))
    
        surfcamID = surfcamID + 1

    if key == ord('c') :
        cubeID=cubeID+1
        surfcamID=0
        print('cubeID={}, surfcamID={}.'.format(cubeID, surfcamID))
    
    if key == ord('s') :
        
        if surfID < 7:
            surfID=surfID+1
        if surfID == 7 :
            surfID=1
        print('surfID={}.'.format(surfID))
    ID = [cubeID, surfcamID]
    return ID

    

read_Cam(cam, cam2, x, y)
cam.release()
cam2.release()
cv2.destroyAllWindows()

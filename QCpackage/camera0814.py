import cv2
import serial
import time
def read_3Cams(cam1, cam2, cam3, x, y, cubeID):
    while True:
        cubeID_saveNames=[]
        
        _, img_cam1 = cam1.read()
        _, img2_cam1 = cam1.read()
        
        cv2.line(img2_cam1, (0, y), (2*x, y), (0,0,255), 1)
        cv2.line(img2_cam1, (x, 0), (x, 2*y), (0,0,255), 1)
        cv2.line(img2_cam1, (0, 0), (5,0), (0,255,0),1)
        #cv2.namedWindow('cam 1', cv2.WINDOW_NORMAL)
        img2_cam1 = cv2.resize(img2_cam1, (2*x//3, 2*y//3 +1))
        cv2.imshow('cam 1', img2_cam1)
        cv2.moveWindow('cam 1', 35, 0)        
    
        _, img_cam2 = cam2.read()
        _, img2_cam2 = cam2.read()
        
        cv2.line(img2_cam2, (0, y), (2*x, y), (0,0,255), 1)
        cv2.line(img2_cam2, (x, 0), (x, 2*y), (0,0,255), 1)
        cv2.line(img2_cam2, (0, 0), (5,0), (0,255,0),1)
        #cv2.namedWindow('cam 2', cv2.WINDOW_NORMAL)
        img2_cam2 = cv2.resize(img2_cam2, (2*x//3, 2*y//3 +1))
        cv2.imshow('cam 2', img2_cam2)
        cv2.moveWindow('cam 2', 35, 2*y//3 +1 +46)        

        _, img_cam3 = cam3.read()
        _, img2_cam3 = cam3.read()
        
        cv2.line(img2_cam3, (0, y), (2*x, y), (0,0,255), 1)
        cv2.line(img2_cam3, (x, 0), (x, 2*y), (0,0,255), 1)
        cv2.line(img2_cam3, (0, 0), (5,0), (0,255,0),1)
        #cv2.namedWindow('cam 3', cv2.WINDOW_NORMAL)
        img2_cam3 = cv2.resize(img2_cam3, (2*x//3, 2*y//3 +1))
        cv2.imshow('cam 3', img2_cam3)
        cv2.moveWindow('cam 3', 35, (2*y//3 +1 +34)*2)        
        
        key = cv2.waitKey(1) &0xff   
        cubeID_saveNames = write_3pic(img_cam1, img_cam2, img_cam3, cubeID,  key)
         
        
        if cubeID_saveNames != None:
            return cubeID_saveNames

        
def write_3pic(img_cam1, img_cam2, img_cam3, cubeID, key):
#    print("PRESS 1 to ROTATE and WRITE PICTURE")

    if key == ord('1') : 
        print( 'WRITING IMAGEs ...')
        #ser1.write(1)
        #time.sleep(2)    
        #print('cam1,2,3:')
        cv2.imwrite('mao_pictures/pic0813test/cube{0}cam1.jpg'.format(cubeID), img_cam1)
        #print('mao_pictures/pic0731est/cube{0}cam1.jpg'.format(cubeID))
        cv2.imwrite('mao_pictures/pic0813test/cube{0}cam2.jpg'.format(cubeID), img_cam2)
        #print('mao_pictures/pic0731test/cube{0}cam2.jpg'.format(cubeID))
        cv2.imwrite('mao_pictures/pic0813test/cube{0}cam3.jpg'.format(cubeID), img_cam3)
        #print('mao_pictures/pic0731test/cube{0}cam3.jpg'.format(cubeID))
   

#        flag=0
        cubeID_saveNames = [cubeID+1, 'cube'+str(cubeID)+'cam1', 'cube'+str(cubeID)+'cam2', 'cube'+str(cubeID)+'cam3']#, flag]
        
        '''
        #イミテーションのやつ
        cubeID_saveNames = [cubeID+1, 'cube'+str(cubeID)+'cam1_11',
                                'cube'+str(cubeID)+'cam3_24',
                                'cube'+str(cubeID)+'cam2_32']
        '''
        
        return cubeID_saveNames



    
def read_6Cams(cam1, cam2, cam3, cam4, cam5, cam6, x, y, cubeID):
    while True:
        cubeID_save6Names=[]
        
        _, img_cam1 = cam1.read()
        _, img2_cam1 = cam1.read()
        
        cv2.line(img2_cam1, (0, y), (2*x, y), (0,0,255), 1)
        cv2.line(img2_cam1, (x, 0), (x, 2*y), (0,0,255), 1)
        cv2.line(img2_cam1, (0, 0), (5,0), (0,255,0),1)
        #cv2.namedWindow('cam 1', cv2.WINDOW_NORMAL)
        img2_cam1 = cv2.resize(img2_cam1, (2*x//3, 2*y//3 +1))
        cv2.imshow('cam 1', img2_cam1)
        cv2.moveWindow('cam 1', 35, 0)        
    
        _, img_cam2 = cam2.read()
        _, img2_cam2 = cam2.read()
        
        cv2.line(img2_cam2, (0, y), (2*x, y), (0,0,255), 1)
        cv2.line(img2_cam2, (x, 0), (x, 2*y), (0,0,255), 1)
        cv2.line(img2_cam2, (0, 0), (5,0), (0,255,0),1)
        #cv2.namedWindow('cam 2', cv2.WINDOW_NORMAL)
        img2_cam2 = cv2.resize(img2_cam2, (2*x//3, 2*y//3 +1))
        cv2.imshow('cam 2', img2_cam2)
        cv2.moveWindow('cam 2', 35, 2*y//3 +1 +46)        
        
        _, img_cam3 = cam3.read()
        _, img2_cam3 = cam3.read()
        
        cv2.line(img2_cam3, (0, y), (2*x, y), (0,0,255), 1)
        cv2.line(img2_cam3, (x, 0), (x, 2*y), (0,0,255), 1)
        cv2.line(img2_cam3, (0, 0), (5,0), (0,255,0),1)
        #cv2.namedWindow('cam 3', cv2.WINDOW_NORMAL)
        img2_cam3 = cv2.resize(img2_cam3, (2*x//3, 2*y//3 +1))
        cv2.imshow('cam 3', img2_cam3)
        cv2.moveWindow('cam 3', 35, (2*y//3 +1 +34)*2)        
        
        #'''
        _, img_cam4 = cam4.read()
        _, img2_cam4 = cam4.read()
        
        cv2.line(img2_cam4, (0, y), (2*x, y), (0,0,255), 1)
        cv2.line(img2_cam4, (x, 0), (x, 2*y), (0,0,255), 1)
        cv2.line(img2_cam4, (0, 0), (5,0), (0,255,0),1)
        #cv2.namedWindow('cam 4', cv2.WINDOW_NORMAL)
        img2_cam4 = cv2.resize(img2_cam4, (2*x//3, 2*y//3 +1))
        cv2.imshow('cam 4', img2_cam4)
        cv2.moveWindow('cam 4', 35+2*x//3, 0)        
        
        _, img_cam5 = cam5.read()
        _, img2_cam5 = cam5.read()
        
        cv2.line(img2_cam5, (0, y), (2*x, y), (0,0,255), 1)
        cv2.line(img2_cam5, (x, 0), (x, 2*y), (0,0,255), 1)
        cv2.line(img2_cam5, (0, 0), (5,0), (0,255,0),1)
        #cv2.namedWindow('cam 5', cv2.WINDOW_NORMAL)
        img2_cam5 = cv2.resize(img2_cam5, (2*x//3, 2*y//3 +1))
        cv2.imshow('cam 5', img2_cam5)
        cv2.moveWindow('cam 5', 35+2*x//3, 2*y//3 +1 +46)        
        
        _, img_cam6 = cam6.read()
        _, img2_cam6 = cam6.read()
        
        cv2.line(img2_cam6, (0, y), (2*x, y), (0,0,255), 1)
        cv2.line(img2_cam6, (x, 0), (x, 2*y), (0,0,255), 1)
        cv2.line(img2_cam6, (0, 0), (5,0), (0,255,0),1)
        #cv2.namedWindow('cam 6', cv2.WINDOW_NORMAL)
        img2_cam6 = cv2.resize(img2_cam6, (2*x//3, 2*y//3 +1))
        cv2.imshow('cam 6', img2_cam6)
        cv2.moveWindow('cam 6', 35+2*x//3, (2*y//3 +1 +34)*2)        
        #'''
        '''
        img_cam4 =1
        img_cam5 =1
        img_cam6 =1
        '''
        key = cv2.waitKey(1) & 0xff    
        cubeID_save6Names = write_6pic(img_cam1, img_cam2, img_cam3, img_cam4, img_cam5, img_cam6, cubeID,  key)

        
        if cubeID_save6Names != None:
            return cubeID_save6Names

        
def write_6pic(img_cam1, img_cam2, img_cam3, img_cam4, img_cam5, img_cam6, cubeID, key):
#    print("PRESS 1 to ROTATE and WRITE PICTURE")

    if key == ord('1') : 
        print( 'WRITING IMAGEs ...')
        #ser1.write(1)
        #time.sleep(2)    
        #print('cam1,2,3:')
        cv2.imwrite('mao_pictures/pic0813test/cube{0}cam1.jpg'.format(cubeID), img_cam1)#####cam1~3については、新しいキューブ
        #print('mao_pictures/pic0731test/cube{0}cam1.jpg'.format(cubeID))
        cv2.imwrite('mao_pictures/pic0813test/cube{0}cam2.jpg'.format(cubeID), img_cam2)
        #print('mao_pictures/pic0731test/cube{0}cam2.jpg'.format(cubeID))
        cv2.imwrite('mao_pictures/pic0813test/cube{0}cam3.jpg'.format(cubeID), img_cam3)
        #print('mao_pictures/pic0731test/cube{0}cam3.jpg'.format(cubeID))
   
        #'''
        cv2.imwrite('mao_pictures/pic0813test/cube{0}cam4.jpg'.format(cubeID-1), img_cam4)#####cam4~6については、さっき1~3を撮影した
        #print('mao_pictures/pic0609test/cube{0}cam1.jpg'.format(cubeID-1))                #####前のキューブだから、cubeIDは1減らして使う
        cv2.imwrite('mao_pictures/pic0813test/cube{0}cam5.jpg'.format(cubeID-1), img_cam5)
        #print('mao_pictures/pic0731test/cube{0}cam2.jpg'.format(cubeID-1))
        cv2.imwrite('mao_pictures/pic0813test/cube{0}cam6.jpg'.format(cubeID-1), img_cam6)
        #print('mao_pictures/pic0731test/cube{0}cam3.jpg'.format(cubeID-1))
        #'''

#        flag=0
        cubeID_save6Names = [cubeID+1, 'cube'+str(cubeID) + 'cam1', 'cube'+str(cubeID) + 'cam2', 'cube'+str(cubeID) + 'cam3',
                                    'cube'+str(cubeID-1)+'cam4', 'cube'+str(cubeID-1)+'cam5', 'cube'+str(cubeID-1)+'cam6']#, flag]

        '''
        cubeID_save6Names = [cubeID+1,
                         'cube'+str(cubeID) + 'cam1_11',
                         'cube'+str(cubeID) + 'cam3_24',
                         'cube'+str(cubeID) + 'cam2_32',
                         'cube'+str(cubeID-1)+'cam1_41',
                         'cube'+str(cubeID-1)+'cam3_54',
                         'cube'+str(cubeID-1)+'cam2_62']
        '''

        return cubeID_save6Names







def TakePicture():    
    cam1 = cv2.VideoCapture(1)
    cam2 = cv2.VideoCapture(2)
    cam3 = cv2.VideoCapture(4)
    width_cam = int(cam.get(cv2. CAP_PROP_FRAME_WIDTH))
    height_cam = int(cam.get(cv2.CAP_PROP_FRAME_HEIGHT))
    x = width_cam//2
    y = height_cam//2
    
    read_Cam(cam1, cam2, cam3, x, y)
    cam1.release()
    cam2.release()
    cam3.release()
    cv2.destroyAllWindows()

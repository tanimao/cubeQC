import cv2


cam = cv2.VideoCapture(0)
cam2 = cv2.VideoCapture(4)
cam3 = cv2.VideoCapture(1)

'''
cam = cv2.VideoCapture(5)
cam2 = cv2.VideoCapture(2)
cam3 = cv2.VideoCapture(6)

'''

cams = [cam, cam2, cam3]
width_cam = int(cam.get(cv2. CAP_PROP_FRAME_WIDTH))
height_cam = int(cam.get(cv2.CAP_PROP_FRAME_HEIGHT))
x = width_cam//2
y = height_cam//2
minisize = (2*x//3, 2*y//3)
while True:

        
    for i, Ncam in enumerate(cams):

        _, img_cam = Ncam.read()
        _, img2_cam = Ncam.read()

       # _, img2_cam = cam.read()
        cv2.line(img_cam, (0, y), (2*x, y), (0,0,255), 1)
        cv2.line(img_cam, (x, 0), (x, 2*y), (0,0,255), 1)
        cv2.line(img_cam, (0, 0), (5,0), (0,255,0),1)
#        cv2.namedWindow('PUSH ENTER KEY frame'+str(i), cv2.WINDOW_NORMAL)
        img_cam = cv2.resize(img_cam, minisize)
        cv2.imshow('PUSH ENTER KEY frame'+str(i), img_cam)
        cv2.moveWindow('PUSH ENTER KEY frame'+str(i), 0, minisize[1])
    key = cv2.waitKey(1)    &0xff

    if key == ord('s') : 
        print('input file name :')
        name_cam = input()
        
        cv2.imwrite("mao_pictures/pic0127/{}.jpg".format(name_cam), img2_cam)
        #cv2.imwrite("mao_pictures/{}_grid.jpg".format(name_cam), img_cam)
        print('image is written. Now starting to recognize.')

    elif key == 13 : break

    

cam.release()
cam2.release()
cam3.release()
cv2.destroyAllWindows()

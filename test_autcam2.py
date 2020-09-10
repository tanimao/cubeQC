import cv2
import datetime
import time
import gc

cap = cv2.VideoCapture(3)

n = 0
cycle = 50
i = 61
j = 0
start = time.time()
#start = time.time()
while True:
    
    ret, frame = cap.read()
    cv2.imshow("window", frame)
    if cv2.waitKey(1) & 0xff == ord('q'):
        break
    if n == cycle:
    #if cv2.waitKey(1) & 0xff == ord('s'):
        n = 0
        #cv2.imwrite('mao_pictures/test0930/test{}.jpg'.format(datetime.datetime.now().strftime('%Y%m%d%H%M%S%f')), frame)
        cv2.imwrite('mao_pictures/pic1113bad/bad{}_{}.jpg'.format(i+1, j+1), frame)
        print("no.{}_{} captured.".format(i+1,j+1))
        print("time : {} sec".format(time.time()-start))
        j += 1
        start = time.time()
        if j == 6 : 
            j = 0
            i += 1
            print('cube changing... ')
            time.sleep(5)
            print('change is done. ')
        time.sleep(8)
        print('now taking...')
        time.sleep(1)
        del frame
        gc.collect()
    n += 1

    cv2.destroyAllWindows()

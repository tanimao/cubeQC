from QCpackage import MainAnalysis0604
import cv2
from QCpackage import camera0609
from QCpackage import cameraImitation
import serial
from QCpackage import checkSign
from QCpackage import ServoRun
import numpy as np



###読み込めてるかの確認
print('__name__ is', __name__)
print('MainAnalysis __name__ is ', MainAnalysis0604.__name__)



###カメラの起動
cam1 = cv2.VideoCapture(0)
cam2 = cv2.VideoCapture(4)
cam3 = cv2.VideoCapture(1)
cam4 = cv2.VideoCapture(5)
cam5 = cv2.VideoCapture(2)
cam6 = cv2.VideoCapture(6)
width_cam  = int(cam1.get(cv2.CAP_PROP_FRAME_WIDTH ))//2
height_cam = int(cam1.get(cv2.CAP_PROP_FRAME_HEIGHT))//2
cubeID = 1

###シリアル通信機器読み込み
ser = serial.Serial('/dev/tty.usbmodem145301',9600)
###六個のデータセットを3組保持するために、ナムパイ配列を使う。
saveName = [0] * 6
ImageName= [0] * 6
cubedata = np.zeros((3,6,7))###directionIDを忘れてた。
'''
こういう配列ができる。
array([[[0., 0., 0., 0., 0., 0., 0.],1 個めの配列。第一面のxhole,yhole,rhole,Emin,xsize,ysize,bump。
        [0., 0., 0., 0., 0., 0., 0.],
        [0., 0., 0., 0., 0., 0., 0.],
        [0., 0., 0., 0., 0., 0., 0.],
        [0., 0., 0., 0., 0., 0., 0.],
        [0., 0., 0., 0., 0., 0., 0.]],

       [[0., 0., 0., 0., 0., 0., 0.],
        [0., 0., 0., 0., 0., 0., 0.],
        [0., 0., 0., 0., 0., 0., 0.],
        [0., 0., 0., 0., 0., 0., 0.],
        [0., 0., 0., 0., 0., 0., 0.],
        [0., 0., 0., 0., 0., 0., 0.]],

       [[0., 0., 0., 0., 0., 0., 0.],
        [0., 0., 0., 0., 0., 0., 0.],
        [0., 0., 0., 0., 0., 0., 0.],
        [0., 0., 0., 0., 0., 0., 0.],
        [0., 0., 0., 0., 0., 0., 0.],
        [0., 0., 0., 0., 0., 0., 0.]]])

'''
############
###まず、キューブを置いて、回転させる。
print('目の前の台座にキューブを置けたらEnterを押してください>>')
firststep = input()
ser.write(b'200\n')



#############################################################################################
###0番目撮影(初期処理)
#############################################################################################
print('0番目撮影：１を押して撮影>>')
cubeID_save3Names = camera0609.read_3Cams(cam1, cam2, cam3, width_cam, height_cam, cubeID)
###############画像の名前
#saveName = 'cube'+str(i+1)+'cam1_11'
#cubeID_saveNames[0] はcubeID

cubeID = cubeID_save3Names[0]

saveName[0] = cubeID_save3Names[1]
ImageName[0]= 'mao_pictures/pic0610good/'+ saveName[0] + '.jpg'

saveName[1] = cubeID_save3Names[2]
ImageName[1]= 'mao_pictures/pic0610good/'+ saveName[1] + '.jpg'

saveName[2] = cubeID_save3Names[3]
ImageName[2]= 'mao_pictures/pic0610good/'+ saveName[2] + '.jpg'


for isurface in range(3):
###cubedata[0]の、第1面、第2面、第3面に代入する。
    cubedata[0][isurface] = MainAnalysis0604.ANALYSIS(saveName[isurface], ImageName[isurface])
    print('cubedata for ', saveName[isurface], ' is ', cubedata[0][isurface])
    print('cubedata, type ',cubedata,  type(cubedata[0][isurface]))

    ###cubedataが取れれば、saveNameは保存しておく必要はない。

###ここまでで、cubedata[0]の1~3のみにデータがある。
###これをcubedata[1]に写す。
cubedata[1] = cubedata[0]
print('cubeID :', cubeID, cubedata)

###ここまでできたら、ジグを回転させる。
ser.write(b'200\n')


sign = ['']*2
sign[0] = 'first'
#############################################################################################
###1番目撮影(初期処理2)
#############################################################################################
while True:

    print('ループ：１を押して撮影>>`')
    cubeID_save6Names = camera0609.read_6Cams(cam1, cam2, cam3, cam4, cam5, cam6, width_cam, height_cam, cubeID)
    
    cubeID = cubeID_save6Names[0]
    
    saveName[0] = cubeID_save6Names[1]                              ###1番目の1~3面
    ImageName[0]= 'mao_pictures/pic0610good/'+ saveName[0] + '.jpg'
    
    saveName[1] = cubeID_save6Names[2]
    ImageName[1]= 'mao_pictures/pic0610good/'+ saveName[1] + '.jpg'
    
    saveName[2] = cubeID_save6Names[3]
    ImageName[2]= 'mao_pictures/pic0610good/'+ saveName[2] + '.jpg'
    
    saveName[3] = cubeID_save6Names[4]                              ###0番目の4~6面
    ImageName[3]= 'mao_pictures/pic0610good/'+ saveName[3] + '.jpg'
    
    saveName[4] = cubeID_save6Names[5]
    ImageName[4]= 'mao_pictures/pic0610good/'+ saveName[4] + '.jpg'
    
    saveName[5] = cubeID_save6Names[6]
    ImageName[5]= 'mao_pictures/pic0610good/'+ saveName[5] + '.jpg'
    
    
    for isurface in range(3):
    ###cubedata[1]の、第4面、第5面、第6面に代入する。
        cubedata[1][isurface+3] = MainAnalysis0604.ANALYSIS(saveName[isurface+3], ImageName[isurface+3])
        
        print('cubedata for ', saveName[isurface], ' is ', cubedata[1][isurface])
        print('cubedata, type ',cubedata,  type(cubedata[1][isurface]))
    
    

    ###sign[1]に前回の情報を保管しておく
    sign[1] = sign[0]
    ###cubedataは、xhole, yhole, rhole, Emin, xsize, ysize, bump, directionID です。
    ###このcubedataをインプットとして、signを吐き出す関数を作ってここに入れる。
    ###一個目の配列を全て突っ込む。
    sign[0] = checkSign.checkSign(cubedata[1])
    file = open ('QCpackage/cubedata.txt','a')
    file.write(str(cubeID)+ '  '+ str(cubedata[2])+ '\n')
    ServoRun.ServoRun(sign[0],sign[1], ser)
    ###cubedata[0]の、第1面、第2面、第3面に代入する。時間短縮のため、モータを回転しながら。
    for isurface in range(3):
        cubedata[0][isurface]   = MainAnalysis0604.ANALYSIS(saveName[isurface],   ImageName[isurface])

    ###念の為、cubedata[1]をcubedata[2]に避難しておく。
    cubedata[2] = cubedata[1]
    ###写したあと、[0]の1~3面を[1]の方に写す。
    cubedata[1] = cubedata[0]
    #print('cubedata is \n', cubedata)
    
    
#############################################################################################
###2番目撮影(初期処理?ここからループ?)
#############################################################################################
'''
while True:


    cubeID_save6Names = camera0609.read_6Cams(cam1, cam2, cam3, cam4, cam5, cam6, width_cam, height_cam, cubeID)

    cubeID = cubeID_save6Names[0]
    
    saveName[0] = cubeID_save6Names[1]                              ###2番目の1~3面
    ImageName[0]= 'mao_pictures/pic0610good/'+ saveName[0] + '.jpg'
    
    saveName[1] = cubeID_save6Names[2]
    ImageName[1]= 'mao_pictures/pic0610good/'+ saveName[1] + '.jpg'
    
    saveName[2] = cubeID_save6Names[3]
    ImageName[2]= 'mao_pictures/pic0610good/'+ saveName[2] + '.jpg'
    
    saveName[3] = cubeID_save6Names[4]                              ###1番目の4~6面
    ImageName[3]= 'mao_pictures/pic0610good/'+ saveName[3] + '.jpg'
    
    saveName[4] = cubeID_save6Names[5]
    ImageName[4]= 'mao_pictures/pic0610good/'+ saveName[4] + '.jpg'
    
    saveName[5] = cubeID_save6Names[6]
    ImageName[5]= 'mao_pictures/pic0610good/'+ saveName[5] + '.jpg'
    
    for isurface in range(3):
    ###cubedata[1]の、第4面、第5面、第6面に代入する。
        cubedata[1][isurface+3] = MainAnalysis0604.ANALYSIS(saveName[isurface+3], ImageName[isurface+3])
    ###cubedata[0]の、第1面、第2面、第3面に代入する。
        cubedata[0][isurface]   = MainAnalysis0604.ANALYSIS(saveName[isurface],   ImageName[isurface])
        
        print('cubedata for ', saveName[isurface], ' is ', cubedata[1][isurface])
        print('cubedata, type ',cubedata,  type(cubedata[1][isurface]))
    
    sign = checkSign.checkSign(cubedata[1])
    
    ###念の為、cubedata[1]をcubedata[2]に避難しておく。
    cubedata[2] = cubedata[1]
    ###写したあと、[0]の1~3面を[1]の方に写す。
    cubedata[1] = cubedata[0]
    print('cubedata is \n', cubedata)
    file = open ('QCpackage/cubedata.txt','a')
    file.write(str(cubeID)+ '  '+ str(cubedata[2])+ '\n')
    #file.close()
    ###サーボモータとジグを動かす
    ServoRun.ServoRun(sign, ser)
'''




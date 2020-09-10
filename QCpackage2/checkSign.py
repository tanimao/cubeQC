import numpy as np

def checkSign(cubedata):
    ###good,badの分布を見て範囲を書いておく。
    xholemax = 202
    xholemin = 176.
    yholemax = 202.
    yholemin = 176.
    xsizemax = 674.0
    xsizemin = 642.0
    ysizemax = 676.0
    ysizemin = 642.0
    Esummax  = 200
    bumpthr1 = 200
    bumpmax  = 300

    rholemin = 47
    rholemax = 53

    ###cubedataの中身を名前つける。
    '''
    cubedataの形：
    array([[0., 0., 0., 0., 0., 0., 0., 0., 0.],第一面のcamID, directionID, xhole,yhole,rhole,Emin,xsize,ysize,bump
           [0., 0., 0., 0., 0., 0., 0., 0., 0.],
           [0., 0., 0., 0., 0., 0., 0., 0., 0.],
           [0., 0., 0., 0., 0., 0., 0., 0., 0.],
           [0., 0., 0., 0., 0., 0., 0., 0., 0.],
           [0., 0., 0., 0., 0., 0., 0., 0., 0.]])

    c[:,0]で第ゼロ番目の縦ベクトルを持ってこれる。
    
    '''
#    camID = cubedata[:,0]
    directionID = cubedata[:,0]
    xhole = cubedata[:,1]
    yhole = cubedata[:,2]
    rhole = cubedata[:,3]
    Esum  = cubedata[:,4]
    xsize = cubedata[:,5]
    ysize = cubedata[:,6]
    bump  = cubedata[:,7]
    print('xhole: ', np.round(xhole,4))
    print('yhole: ', np.round(yhole,4))
    print('xsize: ', np.round(xsize,4))
    print('xsize: ', np.round(ysize,4))
    print('Esum : ', np.round(Esum ,4))
    print('rhole: ', np.round(rhole,4))
    print('bump : ', np.round(bump ,4))
    filecali = open ('QCpackage2/files/data200901_cali.txt', 'a')
    for i in range (6):
        filecali.write( str(directionID[i]) +  ' '+
                   str(np.round(xhole[i], 4))+ ' '+
                   str(np.round(yhole[i], 4))+' '+
                   str(np.round(rhole[i], 4))+' '+
                   str(np.round(Esum[i], 4))+' '+
                   str(np.round(xsize[i], 4))+' '+
                   str(np.round(ysize[i], 4))+' '+
                   str(np.round(bump[i], 4))+' '+
                     '\n')
    filecali.close()

    sign = ''
    for surface in range(6):
        if xhole[surface] > xholemax+1 or xhole[surface] < xholemin-1 :
            sign = 'bad'
            print('xhole is bad.')

        if yhole[surface] > yholemax+1 or yhole[surface] < yholemin-1 :
            sign = 'bad'
            print('yhole is bad.')

    #    if xsize[surface] > xsizemax or xsize[surface] < xsizemin :
    #        sign = 'bad'
    #        print('xsize is bad.')

    #    if ysize[surface] > ysizemax or ysize[surface] < ysizemin :
    #        sign = 'bad'
    #        print('ysize is bad.')

        if Esum[surface]  > Esummax :
            sign = 'bad'
            print('Esum is bad.')

        if rhole[surface] > rholemax or rhole[surface] < rholemin :
            sign = 'bad'
            print('rhole is bad.')

        '''
        if bump[surface]  > bumpthr1    and bump[surface]  < bumpmax  :
            sign = 'middle'
            print('There is some bump.')
        '''    
        if bump[surface]> bumpmax :
            sign = 'bad'
            print('bump is bad.')
            
        
            

    #bad のとき。
    if sign == 'bad' :
        print('This cube is ', sign)
        return sign

    #bad でないとき。
    elif  ( (xhole[0] > xholemin-1 and xhole[0] < xholemin +1) or
            (xhole[0] > xholemax-1 and xhole[0] < xholemax +1) or
            (xhole[1] > xholemin-1 and xhole[1] < xholemin +1) or
            (xhole[1] > xholemax-1 and xhole[1] < xholemax +1) or
            (xhole[2] > xholemin-1 and xhole[2] < xholemin +1) or
            (xhole[2] > xholemax-1 and xhole[2] < xholemax +1) or
            (xhole[3] > xholemin-1 and xhole[3] < xholemin +1) or
            (xhole[3] > xholemax-1 and xhole[3] < xholemax +1) or
            (xhole[4] > xholemin-1 and xhole[4] < xholemin +1) or
            (xhole[4] > xholemax-1 and xhole[4] < xholemax +1) or
            (xhole[5] > xholemin-1 and xhole[5] < xholemin +1) or
            (xhole[5] > xholemax-1 and xhole[5] < xholemax +1) ) :
        
        sign = 'middle'
        print("xhole is around threshold:", sign)
        return sign


    elif  ( (yhole[0] > yholemin-1 and yhole[0] < yholemin +1) or
            (yhole[0] > yholemax-1 and yhole[0] < yholemax +1) or
            (yhole[1] > yholemin-1 and yhole[1] < yholemin +1) or
            (yhole[1] > yholemax-1 and yhole[1] < yholemax +1) or
            (yhole[2] > yholemin-1 and yhole[2] < yholemin +1) or
            (yhole[2] > yholemax-1 and yhole[2] < yholemax +1) or
            (yhole[3] > yholemin-1 and yhole[3] < yholemin +1) or
            (yhole[3] > yholemax-1 and yhole[3] < yholemax +1) or
            (yhole[4] > yholemin-1 and yhole[4] < yholemin +1) or
            (yhole[4] > yholemax-1 and yhole[4] < yholemax +1) or
            (yhole[5] > yholemin-1 and yhole[5] < yholemin +1) or
            (yhole[5] > yholemax-1 and yhole[5] < yholemax +1) ) :
        
        sign = 'middle'
        print("yhole is around threshold:", sign)
        return sign




    elif    bump[0] > bumpthr1 or  bump[1] > bumpthr1 or bump[2] > bumpthr1 or bump[3] > bumpthr1 or bump[4] > bumpthr1 or bump[5] > bumpthr1 :
        
        sign = 'middle'
        print ('There are some bump:',sign)
        return sign
    
    elif    xsize[0] > xsizemax or xsize[0] < xsizemin or xsize[1] > xsizemax or xsize[1] < xsizemin or xsize[2] > xsizemax or xsize[2] < xsizemin or xsize[3] > xsizemax or xsize[3] < xsizemin or xsize[4] > xsizemax or xsize[4] < xsizemin or xsize[5] > xsizemax or xsize[5] < xsizemin :

        sign = 'middle'
        print ('xsize is out of range:',sign)
        return sign
    

    elif    ysize[0] > ysizemax or  ysize[0] < ysizemin or ysize[1] > ysizemax or ysize[1] < ysizemin or ysize[2] > ysizemax or ysize[2] < ysizemin or ysize[3] > ysizemax or ysize[3] < ysizemin or ysize[4] > ysizemax or ysize[4] < ysizemin or ysize[5] > ysizemax or ysize[5] < ysizemin :
        
        sign = 'middle'
        print ('ysize is out of range:',sign)
        return sign
        


    #badでもmiddleでもない時。
    else :
        sign = 'good'
        print('This cube is ', sign)
        return sign 

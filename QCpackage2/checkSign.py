import numpy as np
###12/24追記
###穴が右上にある時の横をxとしている。
###height,width,depthを計算してテキストファイルに書き出すことをする。


def checkSign(cubeID, cubedata):
    ###good,badの分布を見て範囲を書いておく。
    ###9/28のけっかから範囲を更新
    ##xholemax = 202
    ##xholemin = 176.
    ##yholemax = 202.
    ##yholemin = 176.
    ##xsizemax = 674.0
    ##xsizemin = 642.0
    ##ysizemax = 676.0
    ##ysizemin = 642.0
    
    ##rholemin = 47
    ##rholemax = 53
    '''
    xholemax = 198+2
    yholemax = 198+2
    xholemin = 168+4
    yholemin = 168+4

    xsizemax = 664.8-0.5
    ysizemax = 664.8-0.5
    xsizemin = 651.8
    ysizemin = 651.8
    '''

    #10/14変更

    xholemax = 199.5+3
    yholemax = 199.5+3
    xholemin = 162.5+2*3
    yholemin = 162.5+2*3

    xsizemax = 664.3+3
    ysizemax = 664.3+3
    xsizemin = 649.5+0
    ysizemin = 649.5+0

    rholemin = 47.8
    rholemax = 100 ## ありえないはず。実質下限のみ用意する。
    Esummax  = 200
    bumpthr1 = 200
    bumpmax  = 300


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
    #camID = cubedata[:,0]
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
    print('ysize: ', np.round(ysize,4))
    print('Esum : ', np.round(Esum ,4))
    print('rhole: ', np.round(rhole,4))
    print('bump : ', np.round(bump ,4))
    filecali = open ('QCpackage2/files/data210118_cali.txt', 'a')
    for i in range (6):
        filecali.write( str(directionID[i])       + ' ' +
                        str(np.round(xhole[i], 4))+ ' ' +
                        str(np.round(yhole[i], 4))+ ' ' +
                        str(np.round(rhole[i], 4))+ ' ' +
                        str(np.round(Esum[i],  4))+ ' ' +
                        str(np.round(xsize[i], 4))+ ' ' +
                        str(np.round(ysize[i], 4))+ ' ' +
                        str(np.round(bump[i],  4))+ ' ' +
                     '\n')
    filecali.close()

###12/24追記
###height, width, depth を計算する。
###1面が天面に来るような向き

    height = (ysize[2-1] + xsize[3-1]
            + xsize[5-1] + ysize[6-1] ) /4

    width  = (xsize[1-1] + ysize[3-1]
            + ysize[4-1] + xsize[6-1] ) /4

    depth  = (ysize[1-1] + xsize[2-1]
            + xsize[4-1] + ysize[5-1] ) /4
    
    sizeoutput = open ('sizeoutput.txt','a')##aは追記する、というオプション

    sizeoutput.write( str(cubeID) + ' ' +
                      str(np.round(height, 4)) + ' ' +
                      str(np.round(width,  4)) + ' ' +
                      str(np.round(depth,  4)) + ' ' +
                      '\n')
    sizeoutput.close()


    sign = ''
    for surface in range(6):
        if xhole[surface] >= xholemax+0.5 or xhole[surface] <= xholemin-0.5 :
            sign = 'bad'
            print('xhole({}) is bad.'.format(surface))

        if yhole[surface] >= yholemax+0.5 or yhole[surface] <= yholemin-0.5 :
            sign = 'bad'
            print('yhole({}) is bad.'.format(surface))

        ###今回(9/28以降はサイズでしっかり切る)
        if xsize[surface] > xsizemax or xsize[surface] < xsizemin :
            sign = 'bad'
            print('xsize({}) is bad.'.format(surface))

        if ysize[surface] > ysizemax or ysize[surface] < ysizemin :
            sign = 'bad'
            print('ysize({}) is bad.'.format(surface))

        if Esum[surface]  > Esummax :
            sign = 'bad'
            print('Esum({}) is bad.'.format(surface))

        if rhole[surface] > rholemax or rhole[surface] < rholemin :
            sign = 'bad'
            print('rhole({}) is bad.'.format(surface))

        '''
        if bump[surface]  > bumpthr1    and bump[surface]  < bumpmax  :
            sign = 'middle'
            print('There is some bump.')
        '''    


        if bump[surface]> bumpmax :
            sign = 'bad'
            print('bump({}) is bad.'.format(surface))
            
        
            

    #bad のとき。
    if sign == 'bad' :
        print('This cube is ', sign)
        return sign

    #bad でないとき。
    ##ミドル領域は1ずつ取るのではなく、0.5ずつにする
    ##１ずつだと、ミドルが多くなりすぎる。
    elif  ( (xhole[0] > xholemin-0.5 and xhole[0] < xholemin +0.5) or
            (xhole[0] > xholemax-0.5 and xhole[0] < xholemax +0.5) or
            (xhole[1] > xholemin-0.5 and xhole[1] < xholemin +0.5) or
            (xhole[1] > xholemax-0.5 and xhole[1] < xholemax +0.5) or
            (xhole[2] > xholemin-0.5 and xhole[2] < xholemin +0.5) or
            (xhole[2] > xholemax-0.5 and xhole[2] < xholemax +0.5) or
            (xhole[3] > xholemin-0.5 and xhole[3] < xholemin +0.5) or
            (xhole[3] > xholemax-0.5 and xhole[3] < xholemax +0.5) or
            (xhole[4] > xholemin-0.5 and xhole[4] < xholemin +0.5) or
            (xhole[4] > xholemax-0.5 and xhole[4] < xholemax +0.5) or
            (xhole[5] > xholemin-0.5 and xhole[5] < xholemin +0.5) or
            (xhole[5] > xholemax-0.5 and xhole[5] < xholemax +0.5) ) :
        
        sign = 'middle'
        print("xhole is around threshold:", sign)
        return sign


    elif  ( (yhole[0] > yholemin-0.5 and yhole[0] < yholemin +0.5) or
            (yhole[0] > yholemax-0.5 and yhole[0] < yholemax +0.5) or
            (yhole[1] > yholemin-0.5 and yhole[1] < yholemin +0.5) or
            (yhole[1] > yholemax-0.5 and yhole[1] < yholemax +0.5) or
            (yhole[2] > yholemin-0.5 and yhole[2] < yholemin +0.5) or
            (yhole[2] > yholemax-0.5 and yhole[2] < yholemax +0.5) or
            (yhole[3] > yholemin-0.5 and yhole[3] < yholemin +0.5) or
            (yhole[3] > yholemax-0.5 and yhole[3] < yholemax +0.5) or
            (yhole[4] > yholemin-0.5 and yhole[4] < yholemin +0.5) or
            (yhole[4] > yholemax-0.5 and yhole[4] < yholemax +0.5) or
            (yhole[5] > yholemin-0.5 and yhole[5] < yholemin +0.5) or
            (yhole[5] > yholemax-0.5 and yhole[5] < yholemax +0.5) ) :
        
        sign = 'middle'
        print("yhole is around threshold:", sign)
        return sign




    elif    bump[0] > bumpthr1 or  bump[1] > bumpthr1 or bump[2] > bumpthr1 or bump[3] > bumpthr1 or bump[4] > bumpthr1 or bump[5] > bumpthr1 :
        
        sign = 'middle'
        print ('There are some bump:',sign)
        return sign
    
    ##elif    xsize[0] > xsizemax or xsize[0] < xsizemin or xsize[1] > xsizemax or xsize[1] < xsizemin or xsize[2] > xsizemax or xsize[2] < xsizemin or xsize[3] > xsizemax or xsize[3] < xsizemin or xsize[4] > xsizemax or xsize[4] < xsizemin or xsize[5] > xsizemax or xsize[5] < xsizemin :

    ##    sign = 'middle'
    ##    print ('xsize is out of range:',sign)
    ##    return sign
    ##

    ##elif    ysize[0] > ysizemax or  ysize[0] < ysizemin or ysize[1] > ysizemax or ysize[1] < ysizemin or ysize[2] > ysizemax or ysize[2] < ysizemin or ysize[3] > ysizemax or ysize[3] < ysizemin or ysize[4] > ysizemax or ysize[4] < ysizemin or ysize[5] > ysizemax or ysize[5] < ysizemin :
    ##    
    ##    sign = 'middle'
    ##    print ('ysize is out of range:',sign)
    ##    return sign
        


    #badでもmiddleでもない時。
    else :
        sign = 'good'
        print('This cube is ', sign)
        return sign 

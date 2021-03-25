import numpy as np
import math
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
    filecali = open ('QCpackage2/files/data210126_cali.txt', 'a')
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



###2021/1/25追記
###キューブの穴位置での分類を実装する
###向かい合う面での平均を計算
    xhole14 = (xhole[1-1] + yhole[4-1])/2
    yhole14 = (yhole[1-1] + xhole[4-1])/2
    xhole25 = (xhole[2-1] + yhole[5-1])/2
    yhole25 = (yhole[2-1] + xhole[5-1])/2
    xhole36 = (xhole[3-1] + yhole[6-1])/2
    yhole36 = (yhole[3-1] + xhole[6-1])/2

    xholemean = 181.7
    yholemean = 181.9

    dhole14 = math.sqrt((xhole14-xholemean)**2 + (yhole14-yholemean)**2)
    dhole25 = math.sqrt((xhole25-xholemean)**2 + (yhole25-yholemean)**2)
    dhole36 = math.sqrt((xhole36-xholemean)**2 + (yhole36-yholemean)**2)

##ズレが最も小さい面を探す
    dhole = dhole14
    topsurf = 0
    yokosurf= 1
    tatesurf= 2

    if dhole25 < dhole :
        dhole = dhole25
        topsurf = 1
        yokosurf= 2
        tatesurf= 0

    if dhole36 < dhole :
        dhole = dhole36
        topsurf = 2
        yokosurf= 0
        tatesurf= 1

##height,width,depth をあらためて定義。後半の面ではxyが入れ替わっていることに注意
    height_2 = (ysize[yokosurf]   + xsize[tatesurf] 
              + xsize[yokosurf+3] + ysize[tatesurf+3])/4
    width_2  = (xsize[topsurf]    + ysize[tatesurf]
              + ysize[topsurf+3]  + xsize[tatesurf+3])/4
    depth_2  = (ysize[topsurf]    + xsize[yokosurf]
              + xsize[topsurf+3]  + ysize[yokosurf+3])/4

##垂直方向の穴位置を基準に測った穴位置を定義
    yoko2Dx = (depth_2 - (xhole[yokosurf] + yhole[yokosurf+3])/2
                       - (yhole[topsurf]  + xhole[topsurf+3])/2)
    yoko2Dy = (yhole[yokosurf] + xhole[yokosurf+3])/2

    tate2Dx = (width_2 - (yhole[tatesurf] + xhole[tatesurf+3])/2
                       - (xhole[topsurf]  + yhole[topsurf+3])/2)
    tate2Dy = (xhole[tatesurf]+ yhole[tatesurf+3])/2

##座標変換のための2D分布の平均と傾き
    yoko2Dmean = [295.4, 182.2]
    tate2Dmean = [295.5, 181.7]
    yoko2Dp1   = 0.522
    tate2Dp1   = 0.4116
    yokocos = math.sqrt(1/(1+ yoko2Dp1**2))
    tatecos = math.sqrt(1/(1+ tate2Dp1**2))

##２回回転させる
    yoko2Dp1_2   = 0.0957
    tate2Dp1_2   = 0.1091
    yokocos_2 = math.sqrt(1/(1+ yoko2Dp1_2**2))
    tatecos_2 = math.sqrt(1/(1+ tate2Dp1_2**2))

##座標変換
    yoko2DX = yokocos * ((yoko2Dx - yoko2Dmean[0]) - yoko2Dp1*(yoko2Dy - yoko2Dmean[1]))
    yoko2DY = yokocos * (yoko2Dp1*(yoko2Dx - yoko2Dmean[0]) + (yoko2Dy - yoko2Dmean[1]))
    tate2DX = tatecos * ((tate2Dx - tate2Dmean[0]) - tate2Dp1*(tate2Dy - tate2Dmean[1]))
    tate2DY = tatecos * (tate2Dp1*(tate2Dx - tate2Dmean[0]) + (tate2Dy - tate2Dmean[1]))

    yoko2DX2 = yokocos_2 * ((yoko2DX) - yoko2Dp1_2*(yoko2DY))
    yoko2DY2 = yokocos_2 * (yoko2Dp1_2*(yoko2DX) + (yoko2DY))
    tate2DX2 = tatecos_2 * ((tate2DX) - tate2Dp1_2*(tate2DY))
    tate2DY2 = tatecos_2 * (tate2Dp1_2*(tate2DX) + (tate2DY))

##楕円の内部カット
    print("yoko:(", str(yoko2DX2),", ", str(yoko2DY2), ")")
    print("tate:(", str(tate2DX2),", ", str(tate2DY2), ")")
    if ((yoko2DX2**2)/((2.3*8.135)**2) + (yoko2DY2**2)/((3*3.34)**2) < 1 and 
        (tate2DX2**2)/((2.3*7.741)**2) + (tate2DY2**2)/((3*3.804)**2) < 1) :



        print("this cube is inside the ellipse!")

        if yoko2DY2 >=0 :
           if yoko2DX2 < 0 :
               yokoClass = "A"
           else :
                yokoClass = "B"
        else :
            if yoko2DX2 < 0 :
                yokoClass = "C"
            else :
                yokoClass = "D"

        if tate2DY2 >=0 :
           if tate2DX2 < 0 :
               tateClass = "A"
           else :
                tateClass = "B"
        else :
            if tate2DX2 < 0 :
                tateClass = "C"
            else :
                tateClass = "D"

        print("topsurface is ", str(topsurf+1), ", (1, 2, 3).")
    #    print("yoko:(", str(yoko2DX),", ", str(yoko2DY), ")")
    #    print("tate:(", str(tate2DX),", ", str(tate2DY), ")")
        print("yokoClass is ", yokoClass)
        print("tateClass is ", tateClass)

    else : 
        print("this cube is outside the ellipse!")
    


    sign = ''
    for surface in range(6):
        if xhole[surface] >= xholemax+0.5 or xhole[surface] <= xholemin-0.5 :
            sign = 'bad'
#            print('xhole({}) is bad.'.format(surface))

        if yhole[surface] >= yholemax+0.5 or yhole[surface] <= yholemin-0.5 :
            sign = 'bad'
#            print('yhole({}) is bad.'.format(surface))

        ###今回(9/28以降はサイズでしっかり切る)
        if xsize[surface] > xsizemax or xsize[surface] < xsizemin :
            sign = 'bad'
#            print('xsize({}) is bad.'.format(surface))

        if ysize[surface] > ysizemax or ysize[surface] < ysizemin :
            sign = 'bad'
#            print('ysize({}) is bad.'.format(surface))

        if Esum[surface]  > Esummax :
            sign = 'bad'
#            print('Esum({}) is bad.'.format(surface))

        if rhole[surface] > rholemax or rhole[surface] < rholemin :
            sign = 'bad'
#            print('rhole({}) is bad.'.format(surface))

        '''
        if bump[surface]  > bumpthr1    and bump[surface]  < bumpmax  :
            sign = 'middle'
            print('There is some bump.')
        '''    


        if bump[surface]> bumpmax :
            sign = 'bad'
#            print('bump({}) is bad.'.format(surface))
            
        
            

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
#        print("xhole is around threshold:", sign)
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
#        print("yhole is around threshold:", sign)
        return sign




    elif    bump[0] > bumpthr1 or  bump[1] > bumpthr1 or bump[2] > bumpthr1 or bump[3] > bumpthr1 or bump[4] > bumpthr1 or bump[5] > bumpthr1 :
        
        sign = 'middle'
#        print ('There are some bump:',sign)
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

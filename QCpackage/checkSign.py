import numpy as np

def checkSign(cubedata):
    ###適当に範囲を書いておく。
    xholemax = 195
    xholemin = 185
    yholemax = 195
    yholemin = 185
    xsizemax = 670.0
    xsizemin = 658.2
    ysizemax = 668.6
    ysizemin = 658.0
    Esummax  = 40
    bumpthr1 = 0.05
    bumpmax  = 0.2

    ###cubedataの中身を名前つける。
    '''
    cubedataの形：
    array([[0., 0., 0., 0., 0., 0., 0.],第一面のxhole,yhole,rhole,Emin,xsize,ysize,bump
           [0., 0., 0., 0., 0., 0., 0.],
           [0., 0., 0., 0., 0., 0., 0.],
           [0., 0., 0., 0., 0., 0., 0.],
           [0., 0., 0., 0., 0., 0., 0.],
           [0., 0., 0., 0., 0., 0., 0.]])

    c[:,0]で第ゼロ番目の縦ベクトルを持ってこれる。
    
    '''
    xhole = cubedata[:,0]
    yhole = cubedata[:,1]
    rhole = cubedata[:,2]
    Esum  = cubedata[:,3]
    xsize = cubedata[:,4]
    ysize = cubedata[:,5]
    bump  = cubedata[:,6]

    for surface in range(6):
        if xhole[surface] > xholemax or xhole[surface] < xholemin :
            sign = 'bad'
            break

        if yhole[surface] > yholemax or yhole[surface] < yholemin :
            sign = 'bad'
            break

        if xsize[surface] > xsizemax or xsize[surface] < xsizemin :
            sign = 'bad'
            break

        if ysize[surface] > ysizemax or ysize[surface] < ysizemin :
            sign = 'bad'
            break

        if Esum[surface]  > Esummax :
            sign = 'bad'
            break

        if bump[surface]  > bumpthr1    and bump[surface]  < bumpmax  :
            sign = 'middle'
            break
        elif bump[surface]> bumpmax :
            sign = 'bad'
            break

    if sign == 'bad' or sign == 'middle' :
        print('This cube is ', sign)
        return sign
    else :
        sign = 'good'
        print('This cube is ', sign)
        return sign 

import numpy as np


def calibration( cubedata ,i, filename):


    #これらは取っておく。
#    '''
    cubeID      = i//6 + 1
    daizalist   = [8,1,2,3,4,5,6,7]
    daizaID     = daizalist[cubeID%8]
    '''
    #同じカメラ・同じ台座での測定
    cubeID      = i +1
    daizaID     = 7
    '''

    
    camID       = cubedata[0]
    directionID = cubedata[1]
    xhole       = cubedata[2]
    yhole       = cubedata[3]
    rhole       = cubedata[4]
    Emin        = cubedata[5]
    xsize       = cubedata[6]
    ysize       = cubedata[7]
    bump        = cubedata[8]

    stdx    = 655.967
    stdy    = 655.906

    par = np.loadtxt ("QCpackage2/parameters.txt")

    if      camID == 1 or camID == 2 or camID == 3:
        caliID = 12*(daizaID-1) + 4*(camID-1) + (directionID-1)

    elif camID == 4 or camID == 5 or camID == 6:
        caliID = 96 + 12*(daizaID-1) + 4*(camID-4) + (directionID-1)

    elif camID == 0:
        calidata = [0, 0, 0, 0, 0, 0, 0, 0, 0]
        file = open(filename,'a')
        file.write(str(calidata)+'\n')
        file.close()
        return calidata


    caliID = int(caliID)
    print ("calibration ID :" , caliID)
    print ("daiza ID : ", daizaID)
    xmean   = par[caliID][0]
    ymean   = par[caliID][1]
    xp0     = par[caliID][2]
    xp1     = par[caliID][3]
    yp0     = par[caliID][4]
    yp1     = par[caliID][5]
    rp0     = par[caliID][6]
    rp1     = par[caliID][7]

    corxsize = stdx * xsize / xmean
    corysize = stdy * ysize / ymean
    corxhole = stdx * ((xhole/xmean) - xp0) / xp1
    coryhole = stdy * ((yhole/ymean) - yp0) / yp1
    corradius= ((stdx+stdy)/2) * (rhole/((xmean+ymean)/2) - rp0) /rp1


    
    calidata = [int(camID),  int(directionID), round(corxhole,2), round(coryhole,2), round(corradius,2), Emin, round(corxsize,2), round(corysize,2), bump]
    file = open(filename,'a')
    file.write(str(calidata)+'\n')
    file.close()

    return calidata

if __name__ == '__main__':
    f = np.loadtxt('files/data210118.txt')
    for i in range(42):
        calibration(f[i],i, 'files/data210118cor.txt')
    ###f[0]が一行目

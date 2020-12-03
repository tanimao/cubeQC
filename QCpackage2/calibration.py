import numpy as np


def calibration(daizaID, cubedata, icam):

    camID       = icam+1
    directionID = cubedata[0]
    xhole       = cubedata[1]
    yhole       = cubedata[2]
    rhole       = cubedata[3]
    Emin        = cubedata[4]
    xsize       = cubedata[5]
    ysize       = cubedata[6]
    bump        = cubedata[7]

    stdx    = 655.967
    stdy    = 655.906

    par = np.loadtxt ("QCpackage2/parameters.txt")

    if      camID == 1 or camID == 2 or camID == 3:
        caliID = 12*(daizaID-1) + 4*(camID-1) + (directionID-1)
    
    elif camID == 4 or camID == 5 or camID == 6:
        caliID = 96 + 12*(daizaID-1) + 4*(camID-4) + (directionID-1)
    
    elif camID == 0 :
        print("camID is 0; img is broken")
        calidata = [ 0, 0, 0, 0, 0, 0, 0, 0]
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


    ###ここでも camIDは配列に入れない。
    calidata = [ int(directionID), round(corxhole,4), round(coryhole,4), round(corradius,4), round(Emin,4), round(corxsize,4), round(corysize,4), round(bump,4)]


    return calidata

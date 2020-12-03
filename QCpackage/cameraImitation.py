def read_3Cams(cam1, cam2, cam3, x, y, cubeID):
    cubeID_saveNames = [cubeID+1, 'cube'+str(cubeID)+'cam1_11',
                                'cube'+str(cubeID)+'cam3_24',
                                'cube'+str(cubeID)+'cam2_32']
    #cubeID = cubeID +1 こう書いても配列には影響がない。配列のところでプラス１しておく。
    print('撮影の真似をしてください>>')
    a= input()
    return cubeID_saveNames


def read_6Cams(cam1, cam2, cam3, cam4, cam5, cam6, x, y, cubeID):
    cubeID_save6Names = [cubeID+1,
                         'cube'+str(cubeID) + 'cam1_11',
                         'cube'+str(cubeID) + 'cam3_24',
                         'cube'+str(cubeID) + 'cam2_32',
                         'cube'+str(cubeID-1)+'cam1_41',
                         'cube'+str(cubeID-1)+'cam3_54',
                         'cube'+str(cubeID-1)+'cam2_62']

    #cubeID = cubeID +1
    print('撮影の真似をしてください>>')
    a= input()
    return cubeID_save6Names

import serial
from pydub import AudioSegment
from pydub.playback import play

def ServoRun(sign,signBefore,ser):

    if sign == signBefore :
        #ser.write(b'200\n')
        print('sign is ',sign)
        if sign == 'bad':
            #play(AudioSegment.from_mp3('QCpackage2/sword-slash2.mp3'))
            play(AudioSegment.from_mp3('QCpackage2/bad.mp3'))
        if sign == 'middle':
            #play(AudioSegment.from_mp3('QCpackage2/warning1.mp3'))
            play(AudioSegment.from_mp3('QCpackage2/middle.mp3'))
        if sign == 'good':
            #play(AudioSegment.from_mp3('QCpackage2/cat-cry1.mp3'))
            play(AudioSegment.from_mp3('QCpackage2/good.mp3'))
    else :
        if sign == 'bad':
            ser.write(b'140\n')
            #play(AudioSegment.from_mp3('QCpackage2/sword-slash2.mp3'))
            play(AudioSegment.from_mp3('QCpackage2/bad.mp3'))
    
        if sign == 'middle':
            ser.write(b'100\n')
            #play(AudioSegment.from_mp3('QCpackage2/warning1.mp3'))
            play(AudioSegment.from_mp3('QCpackage2/middle.mp3'))

        if sign == 'good':
            ser.write(b'178\n')
            #play(AudioSegment.from_mp3('QCpackage2/cat-cry1.mp3'))
            play(AudioSegment.from_mp3('QCpackage2/good.mp3'))







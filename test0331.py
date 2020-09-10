import math
from package_cube import trimmFig
import cv2
import matplotlib.pyplot as plt
from package_cube import outline2
import numpy as np
from package_cube import extractionRGB
saveName  = 'cube18cam1_54'
ImageName = 'mao_pictures/pic0325/'+ saveName + '.jpg'
gray2= cv2.imread(ImageName,0)
img = cv2.imread(ImageName,1)
img = cv2.split(img)
img = cv2.merge((img[2],img[1],img[0])) # => bgr
img2 = cv2.merge((img[2],img[1],img[0])) # => bgr
print("image is '{}'.".format(ImageName))
result =         extractionRGB.get_ExtractionRGB(img,40)

prex0, prey0, prex1, prey1 = outline2.detect_Outline_wColFigure(result, 1, 500)

bx = int((prex0+prex1)/2)
by = int((prey0+prey1)/2)

edges0_ = trimmFig.get_TrimmedFigure(gray2,prey0,by, prex0-50,prex0+50)
edges1_ = trimmFig.get_TrimmedFigure(gray2,prey0,by, prex1-50,prex1+50)
edges2_ = trimmFig.get_TrimmedFigure(gray2,by,prey1, prex0-50,prex0+50)
edges3_ = trimmFig.get_TrimmedFigure(gray2,by,prey1, prex1-50,prex1+50)

edges4_ = trimmFig.get_TrimmedFigure(gray2,0,prey0+50, prex0,bx)
edges5_ = trimmFig.get_TrimmedFigure(gray2,prey1-50,767, prex0,bx)
edges6_ = trimmFig.get_TrimmedFigure(gray2,0,prey0+50, bx,prex1)
edges7_ = trimmFig.get_TrimmedFigure(gray2,prey1-50,767, bx,prex1)

plt.show()

import numpy as np
import cv2
import matplotlib.pyplot as plt


##### BGRでの白色抽出
def get_ExtractionRGB(img, lim):
    print("#call get_ExtractionRGB")
    bgrLower = np.array([lim, lim, lim])    # 抽出する色の下限(BGR)
    bgrUpper = np.array([256, 256, 256])    # 抽出する色の上限(BGR)
    img_mask = cv2.inRange(img, bgrLower, bgrUpper) # BGRからマスクを作成
    result = cv2.bitwise_and(img, img, mask=img_mask) # 元画像とマスクを合成    
    fig = plt.figure(figsize=(8, 6), dpi=100)
    fig.suptitle('White Extraction', fontsize=24)
    plt.title("White Extraction")
    plt.axis('off')
    plt.imshow(result)
    return result

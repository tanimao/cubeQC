
import cv2
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np

def get_PixelValues(saveName, img, col, cube_size):
    print("\n#call get_PixelValues")
    if col == 1 :
        print("figure is colored")
        # グレースケールに変換する。
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        #convGray = cv2.cvtColor(extractWide, cv2.COLOR_BGR2GRAY)
    else :
        gray = img
    #height, width, ch = extractWide.shape
    '''
    height, width = gray.shape
    size = width * height # 画素数 = 幅 * 高さ
    # 情報表示
    print("幅：", width)
    print("高さ：", height)
    ########################################
    gray2 = gray
    myfig = plt.figure(figsize=(8,6))     
    myfig.suptitle('pixel values', fontsize=24)
    myax = myfig.add_subplot(1,1,1)
    plt.axis('off'),
    plt.imshow(gray2,'gray')


    cube_rectangle = patches.Rectangle((cube_size[4],cube_size[5]), cube_size[0], cube_size[1], fill = False, edgecolor='red')
    myax.add_patch(cube_rectangle)
    print(cube_size[0])
    print(cube_size[1])
    
    '''
    '''
    mask_rect = np.zeros(gray.shape[:2], np.uint8)
    mask_rect[cube_size[5]:cube_size[3], cube_size[4]:cube_size[2]] = 255
    masked_gray = cv2.bitwise_and(gray, gray, mask=mask_rect)
    hist_mask = cv2.calcHist([gray], [0], mask_rect, [256], [0,256])
    #myax2 = myfig.add_subplot(3,1,2), plt.imshow(masked_gray, 'gray')
    #plt.subplot(1,3,2), plt.imshow(masked_gray, 'gray')
    #plt.subplot(3,1,3), plt.plot(hist_mask)
    #plt.xlim([0,256])
    '''
    
    #np.save('files/cube_check1011_edge_bad/'+saveName+'_whole.npy', hist_mask)
    ########################################

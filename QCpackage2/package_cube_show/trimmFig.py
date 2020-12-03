import matplotlib.pyplot as plt
##### 画像抜き出し

def get_TrimmedFigure(img,y1,y2,x1,x2):
    print("#call get_TrimmedFigure")
    trimmed = img[y1:y2,x1:x2]
    '''
    fig = plt.figure(figsize=(8, 6), dpi=100)
    fig.suptitle('Trimmed Figure', fontsize=24)
    plt.axis('off')
    plt.imshow(trimmed)
    '''
    return trimmed

import cv2
def set_ResizeFigure(img, scale):
    height = img.shape[0]
    width  = img.shape[1]
    img = cv2.resize(img , (int(width*scale), int(height*scale)))
    return img

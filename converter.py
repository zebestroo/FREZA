from cv2 import cv2
import math

def loading_displaying_saving():
    img = cv2.imread('new_image.jpg', cv2.IMREAD_GRAYSCALE)
    print("DLINA: " + str(img.shape[1]))
    print("VISOTA: " + str(img.shape[0]))
    return img

with open("file.txt", "w") as file:
    image = loading_displaying_saving()
    color = False
    for i in range(image.shape[0]):
        if i % 2 == 0:
            for j in range(image.shape[1]):
                if not color and image[i][j] <= 127:
                    file.write(f"{j} {i}")
                    file.write('\n')
                    color = True
                    #image[i][j] = 0
                    continue 
                if color and image[i][j] > 127:
                    file.write(f"{j} {i}") 
                    file.write('\n')
                    color = False
                    image[i][j] = 255
                    continue 
                
        else:
            for j in reversed(range(image.shape[1])):
                if not color and image[i][j] <= 127:
                    file.write(f"{j} {i}")
                    file.write('\n')
                    color = True
                    image[i][j] = 0
                    continue 
                if color and image[i][j] > 127:
                    file.write(f"{j} {i}") 
                    file.write('\n')
                    color = False
                    image[i][j] = 255
                    continue 
cv2.imwrite('black_white.jpg', image)
cv2.imshow('black_white', image)
cv2.waitKey(0)
file.close()

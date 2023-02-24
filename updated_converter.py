import cv2
from cutting import *


def point(ls, tup):
    for tp in ls:
        if tp[0] <= tup[1] and tp[1] >= tup[0] and tup[2] == (tp[2] - 1):
            ls.remove(tp)
            return tp
    return False


def search(file, ls):
    main_ls = []
    while ls != []:
        st_tup = ls[0]
        ls.remove(st_tup)
        file.write(f"move {st_tup[0]} {st_tup[2]}")
        file.write('\n')
        file.write("down")
        file.write('\n')
        file.write(f"move {st_tup[1]} {st_tup[2]}")
        file.write('\n')
        flag = True
        loc_ls = []
        while (tup := point(ls, st_tup)):
            loc_ls.append(tup)
            if not flag: 
                file.write(f"move {tup[0]} {tup[2]}")
                file.write('\n')
                file.write(f"move {tup[1]} {tup[2]}")
                file.write('\n')
                flag = True
            else: 
                file.write(f"move {tup[1]} {tup[2]}")
                file.write('\n')
                file.write(f"move {tup[0]} {tup[2]}")
                file.write('\n')
                flag = False
            st_tup = tup
        file.write("up")
        file.write('\n')
        main_ls.append(loc_ls)
    return main_ls

def restyle_photo(filename, photoname, processing_level=100):
    with open(filename, "w") as file:
        image = cv2.imread(photoname, cv2.IMREAD_GRAYSCALE)
        ls = []
        for i in range(image.shape[0]):
            color = False
            for j in range(image.shape[1]):
                if image[i][j] <= processing_level:
                    if not color:
                        start_x = j
                        color = True
                    image[i][j] = 0
                    continue 
                if image[i][j] > processing_level:
                    if color:
                        end_x = j-1
                        ls.append((start_x, end_x, i))
                        color = False
                    image[i][j] = 255
                    continue 

        cv2.imwrite('Converted_image.jpg', image)
        # cutting_photos_deffections(image)
        search(file, ls)
    file.close()

level = int(input('Level of processing: '))
photo = input('Image to be processing: ')
restyle_photo('Instructions_file.txt', photo, level)


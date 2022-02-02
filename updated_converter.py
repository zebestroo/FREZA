from cv2 import cv2


def point(ls, tup):
    for tp in ls:
        if tp[0] <= tup[1] and tp[1] >= tup[0] and tup[2] == (tp[2] - 1):
            ls.remove(tp)
            return tp
    return False


def search(file, ls):
    while ls != []:
        st_tup = ls[0]
        ls.remove(st_tup)
        file.write(f"{st_tup[0]} {st_tup[2]}")
        file.write('\n')
        file.write(f"{st_tup[1]} {st_tup[2]}")
        file.write('\n')
        flag = True
        while (tup := point(ls, st_tup)):
            if not flag: 
                file.write(f"{tup[0]} {tup[2]}")
                file.write('\n')
                file.write(f"{tup[1]} {tup[2]}")
                file.write('\n')
                flag = True
            else: 
                file.write(f"{tup[1]} {tup[2]}")
                file.write('\n')
                file.write(f"{tup[0]} {tup[2]}")
                file.write('\n')
                flag = False
            st_tup = tup
    return None

with open("file.txt", "w") as file:
    image = cv2.imread('new_image.jpg', cv2.IMREAD_GRAYSCALE)
    ls = []
    for i in range(image.shape[0]):
        color = False
        for j in range(image.shape[1]):
            if not color and image[i][j] <= 127:
                start_x = j
                color = True
                continue 
            if color and image[i][j] > 127:
                end_x = j-1
                ls.append((start_x, end_x, i))
                color = False
                continue 
    search(file, ls)

file.close()

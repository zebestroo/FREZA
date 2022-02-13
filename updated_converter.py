from cv2 import cv2


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
        file.write("up")
        file.write('\n')
        flag = True
        loc_ls = []
        while (tup := point(ls, st_tup)):
            loc_ls.append(tup)
            if not flag: 
                file.write(f"move {tup[0]} {tup[2]}")
                file.write('\n')
                file.write("down")
                file.write('\n')
                file.write(f"move {tup[1]} {tup[2]}")
                file.write('\n')
                file.write("up")
                file.write('\n')
                flag = True
            else: 
                file.write(f"move {tup[1]} {tup[2]}")
                file.write('\n')
                file.write("down")
                file.write('\n')
                file.write(f"move {tup[0]} {tup[2]}")
                file.write('\n')
                file.write("up")
                file.write('\n')
                flag = False
            st_tup = tup
        main_ls.append(loc_ls)
    return main_ls

def smoothing(file, main_ls, image):
    for ls in main_ls:
        flag = True
        for tup in ls:
            if image[tup[2]-1][tup[0]] <= 127 or image[tup[2]+1][tup[0]] <= 127:
                if flag:
                    file.write(f"movesmth {tup[0]} {tup[2]}")
                    file.write('\n')
                    file.write("down")
                    file.write('\n')
                    flag = False
                else:
                    file.write(f"movesmth {tup[0]} {tup[2]}")
                    file.write('\n')
        for tup in reversed(ls):
            if image[tup[2]-1][tup[1]] <= 127 or image[tup[2]+1][tup[1]] <= 127:
                file.write(f"movesmth {tup[1]} {tup[2]}")
                file.write('\n')
        file.write("up")
        file.write('\n')




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
    smoothing(file, search(file, ls), image)

file.close()

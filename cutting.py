import cv2


def fix_defect(img, i, j, circle_list, central_color, fix_color):
    if img[i][j] == central_color:
        if img[i-1][j-1] == circle_list[0] and \
            img[i-1][j] == circle_list[1] and \
            img[i-1][j+1] == circle_list[2] and \
            img[i][j+1] == circle_list[3] and \
            img[i+1][j+1] == circle_list[4] and \
            img[i+1][j] == circle_list[5] and \
            img[i+1][j-1] == circle_list[6] and \
            img[i][j-1] == circle_list[7]:

            img[i][j] = fix_color 
            return True


def fix_defect_2(img, i, j, central_color, fix_color):
    if img[i][j] == central_color:
        if img[i-1][j] == fix_color and \
            img[i][j+1] == fix_color and \
            img[i+1][j] == fix_color and \
            img[i][j-1] == fix_color:

            img[i][j] = fix_color 
            return True
    

def conditions_block(img, i, j, central_color, fix_color):
    return fix_defect(img, i, j, [fix_color, central_color, central_color, central_color, fix_color, fix_color, fix_color, fix_color], central_color, fix_color) or \
        fix_defect(img, i, j, [fix_color, fix_color, central_color, central_color, central_color, fix_color, fix_color, fix_color], central_color, fix_color) or \
        fix_defect(img, i, j, [fix_color, fix_color, fix_color, central_color, central_color, central_color, fix_color, fix_color], central_color, fix_color) or \
        fix_defect(img, i, j, [fix_color, fix_color, fix_color, fix_color, central_color, central_color, central_color, fix_color], central_color, fix_color) or \
        fix_defect(img, i, j, [fix_color, fix_color, fix_color, fix_color, fix_color, central_color, central_color, central_color], central_color, fix_color) or \
        fix_defect(img, i, j, [central_color, fix_color, fix_color, fix_color, fix_color, fix_color, central_color, central_color], central_color, fix_color) or \
        fix_defect(img, i, j, [central_color, central_color, fix_color, fix_color, fix_color, fix_color, fix_color, central_color], central_color, fix_color) or \
        fix_defect(img, i, j, [central_color, central_color, central_color, fix_color, fix_color, fix_color, fix_color, fix_color], central_color, fix_color) or \
        fix_defect(img, i, j, [fix_color, central_color, fix_color, fix_color, fix_color, fix_color, fix_color, fix_color], central_color, fix_color) or \
        fix_defect(img, i, j, [fix_color, fix_color, fix_color, central_color, fix_color, fix_color, fix_color, fix_color], central_color, fix_color) or \
        fix_defect(img, i, j, [fix_color, fix_color, fix_color, fix_color, fix_color, central_color, fix_color, fix_color], central_color, fix_color) or \
        fix_defect(img, i, j, [fix_color, fix_color, fix_color, fix_color, fix_color, fix_color, fix_color, central_color], central_color, fix_color) or \
        fix_defect_2(img, i, j, central_color, fix_color)


def process_defect(img, i, j):
    if i > 0 and i < img.shape[0]-1 and j > 0 and j < img.shape[1]-1:
        return conditions_block(img, i, j, 255, 0) or conditions_block(img, i, j, 0, 255)



def cutting_photos_deffections(image):
    print("Correcting started")
    persents = 0
    k = 0
    while k <= image.shape[0]:
        flag_deffect = False
        prsnts = int((k*100)/image.shape[0])
        if persents != prsnts:
            persents = prsnts
            print(f'Processing: {persents}% ' + '[' + (persents * '=') + ((100 - persents) * ' ') + ']')
        t = 0
        while t < image.shape[1]:
            if process_defect(image, k, t):
                flag_deffect = True
            t += 1
        if flag_deffect:
            print('Deffect founded, return level -1')
            k -= 1
            print('Now level', k)
        else:
            k += 1

    cv2.imwrite('Corrected_image.jpg', image)

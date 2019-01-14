import cv2
import numpy as np

cam = cv2.VideoCapture(1)

indicate = 0        # 0 FOR LOGO, 1 FOR ARROW, 2 FOR COLOR DETECTION

img_names_logo = ['img1.jpg','img2.jpg','img3.jpg']
tem_names_logo = ['template1.jpg','template2.jpg','template3.jpg','template4.jpg']

img_names_arr = ['signboard.jpg']
tem_names_arr = ['template11.jpg','template12.jpg','template13.jpg','template14.jpg','template15.jpg','template16.jpg','template21.jpg','template22.jpg','template23.jpg','template24.jpg','template25.jpg','template26.jpg' ]


def color_detect():
    raw_input("Ready for image...")
    for _ in range(10):
        frame = cam.read()[1]
    cv2.imwrite(filename='color.jpg',img=frame)
    myimg = cv2.imread('color.jpg')
    avg_color_per_row = np.average(myimg, axis=0)
    avg_color = np.average(avg_color_per_row, axis=0)[::-1]
    c = avg_color.argmax()+1
    if c == 1: print 'Color:         Red'
    else: print 'Color:         Blue'

def img_detect(img_names,tem_names,snaps,threshold,indi):
    flag = 0
    l_tem = len(tem_names)
    img_gray_arr,img_rgb_arr,template_arr,w,h = ([]for i in range(5))
    
    for i in range(snaps):
        raw_input("Ready for image...")
        for _ in range(10):
            frame = cam.read()[1]
        cv2.imwrite(filename=img_names[i],img=frame)
    
    for i in range(snaps):
        img_rgb = cv2.imread(img_names[i])
        img_rgb_arr.append(img_rgb)
        img_gray_arr.append(cv2.cvtColor(img_rgb, cv2.COLOR_BGR2GRAY))
        
    for i in range(l_tem):
        template = cv2.imread(tem_names[i],0)
        template_arr.append(template)
        wi,hi = template.shape[::-1]
        w.append(wi)
        h.append(hi)

    resii,locii,pttii = ( [[0 for i in range(l_tem)] for i in range(3)] for i in  range(3) )

    for c in range(snaps):
        for d in range(l_tem):
            resii[c][d] = cv2.matchTemplate(img_gray_arr[c],template_arr[d],cv2.TM_CCOEFF_NORMED)
            locii[c][d] = np.where(resii[c][d] >= threshold)
            for pt in zip(*locii[c][d][::-1]): pass
            try:
                pt
                del pt
            except:
                pttii[c][d] = 1    
    if indi == 0:
        for i in range(3):
            for j in range(l_tem):
                if pttii[i][j] == 0:
                    flag = 1
                    '''print 'Image at position: ', i+1,' matches with template: ', j+1'''
                    print 'Img position: ', i+1
        if flag != 1: print "No match"
    elif indi == 1:
        for i in range(1):
            for j in range(l_tem):
                if pttii[i][j] == 0:
                    flag = 1
                    if flag is 1 and j>5: print 'Drop Zone:     LEFT'
                    if flag is 1 and j<=5: print 'Drop Zone:     RIGHT'
                    break
        if flag != 1: print("No match")
                

if indicate == 0:
    img_detect(img_names_logo,tem_names_logo,3,0.7,0)
    
indicate = 1

if indicate == 1:
    img_detect(img_names_arr,tem_names_arr,1,0.885,1)

indicate = 2

if indicate == 2:
    color_detect()

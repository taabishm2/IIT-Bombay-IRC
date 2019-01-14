import cv2
import numpy as np

cam = cv2.VideoCapture(1)

img_gray_arr,img_rgb_arr,template_arr,w,h = ([]for i in range(5))
threshold, flag = 0.885 , 0   

img_names = ['signboard.jpg']
tem_names = ['template11.jpg','template12.jpg','template13.jpg','template14.jpg','template15.jpg','template16.jpg','template21.jpg','template22.jpg','template23.jpg','template24.jpg','template25.jpg','template26.jpg' ]
l_tem = len(tem_names)

for i in range(1):
    raw_input("Ready for image...")
    for _ in range(10):
        frame = cam.read()[1]
    cv2.imwrite(filename=img_names[i],img=frame)

for i in range(1):
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

for c in range(1):
    for d in range(l_tem):
        resii[c][d] = cv2.matchTemplate(img_gray_arr[c],template_arr[d],cv2.TM_CCOEFF_NORMED)
        locii[c][d] = np.where(resii[c][d] >= threshold)
        for pt in zip(*locii[c][d][::-1]):
           cv2.rectangle(img_rgb_arr[c], pt, (pt[0] + w[d], pt[1] + h[d]), (0,255,255), 2)
        try:
            pt
            del pt
        except:
            pttii[c][d] = 1
           
for i in range(1):
    for j in range(l_tem):
        if pttii[i][j] == 0:
            flag = 1
            if flag is 1 and j>5: print('template:2'+str(j-5))
            if flag is 1 and j<=5: print('template:1'+str(j+1))
if flag != 1: print("No match")
#if flag is 1 and j>5: print("goto left")
#if flag is 1 and j<=5: print("goto right")



#cv2.imshow('detected', img_rgb_arr[c])
#cv2.rectangle(img_rgb_arr[c], pt, (pt[0] + w[d], pt[1] + h[d]), (0,255,255), 2)


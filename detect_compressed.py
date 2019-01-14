import cv2
import numpy as np

img_gray_arr,img_rgb_arr,template_arr,w,h = ([]for i in range(5))
threshold, flag = 0.7 , 0   

img_names = ['img1.jpg','img2.jpg','img3.jpg']
tem_names = ['template1.jpg','template2.jpg','template3.jpg','template4.jpg']
l_tem = len(tem_names)

for i in range(3):
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

for c in range(3):
    for d in range(l_tem):
        resii[c][d] = cv2.matchTemplate(img_gray_arr[c],template_arr[d],cv2.TM_CCOEFF_NORMED)
        locii[c][d] = np.where(resii[c][d] >= threshold)
        for pt in zip(*locii[c][d][::-1]): pass
        try:
            pt
            del pt
        except:
            pttii[c][d] = 1    
       
for i in range(3):
    for j in range(l_tem):
        if pttii[i][j] == 0:
            flag = 1
            print 'Image at position: ', i+1,' matches with template: ', j+1
if flag != 1: print "No match"





#cv2.rectangle(img_rgb_arr[c], pt, (pt[0] + w[d], pt[1] + h[d]), (0,255,255), 2)

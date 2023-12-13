import cv2
import pyminizip
import os
from pyzbar.pyzbar import decode
for i in range(999,-1,-1):
    #print(f'Image number: {i}.png')
    img = cv2.imread(f"{i}.png")
    data =decode(img)
    paswd=data[0].data.decode('utf-8')
    #print(f"this is paswd{paswd}")
    pyminizip.uncompress(f'{i}.zip',paswd,"C:/task",int(0))
    if i!=0:
        os.rename(f"{i-1}/{i-1}.png",f'{i-1}.png')
        os.rename(f"{i-1}/{i-1}.zip",f'{i-1}.zip')
        os.rmdir(f'{i-1}')
    os.remove(f'{i}.zip')
    os.remove(f'{i}.png')
os.rename('0/flag.png','flag.png')
img = cv2.imread("flag.png")
data =decode(img)
flag=data[0].data.decode('utf-8')
print(flag)
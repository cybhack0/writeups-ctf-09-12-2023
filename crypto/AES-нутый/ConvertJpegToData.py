import numpy as np
from PIL import Image

img = Image.open('Task.jpeg')
arr = np.asarray(img)
file = open("Data", "wb")

print(len(arr))
print(len(arr[0]))
print(len(arr[0][0]))

for i in arr:
    for j in i:
        file.write(j[0])
        file.write(j[1])
        file.write(j[2])
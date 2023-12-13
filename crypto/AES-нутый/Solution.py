import numpy as np
from PIL import Image

def ShowData(fileName):
    file = open(fileName, "rb")
    arr = np.array(Image.open("Task.jpeg"))

    for i in range(257):
        for j in range(997):
            r = int.from_bytes(file.read(1), byteorder="big")
            g = int.from_bytes(file.read(1), byteorder="big")
            b = int.from_bytes(file.read(1), byteorder="big")
            arr[i][j][0] = r
            arr[i][j][1] = g
            arr[i][j][2] = b

    img = Image.fromarray(arr)
    img.show()

ShowData("Data.enc")
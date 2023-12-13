from PIL import Image

with open("flag_enc.bin", "rb") as fp:
    flag_enc = fp.read()
with open("the_penguin_enc.bin", "rb") as fp:
    the_penguin_enc = fp.read()

images_sum = bytes(x^y for x,y in zip(flag_enc, the_penguin_enc))
Image.frombytes('RGB', (500,500), images_sum).save('images_sum.jpg')
from PIL import Image
from Crypto.Cipher import ARC4
from os import urandom

def encryptor(data: bytes, key: bytes) -> bytes:
    rc4_encryptor = ARC4.new(key)
    return rc4_encryptor.encrypt(data)


with open("metadata.txt", 'w') as fp:
    with Image.open("flag.jpg") as image:
        flag = image.tobytes()
        fp.write(str([image.mode, image.size]) + "\n")
    with Image.open("ThePenguin.jpg") as image:
        the_penguin = image.tobytes()
        fp.write(str([image.mode, image.size]) + "\n")

key = urandom(256)
flag_enc = encryptor(flag, key)
the_penguin_enc = encryptor(the_penguin, key)

with open("flag_enc.bin", "wb") as fp:
    fp.write(flag_enc)
with open("the_penguin_enc.bin", "wb") as fp:
    fp.write(the_penguin_enc)
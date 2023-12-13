from Gammator3000 import Gammator3000

with open("leak.msg", "rb") as fp:
    leak = fp.read()
with open("enc_message.bin", "rb") as fp:
    enc_message = fp.read()
IV_leaked_part = bytes(x^y for x,y in zip(leak, enc_message))[::-1]
two_byte_values = [bytes([i,j]) for i in range(256) for j in range(256)]
for probable_part in two_byte_values:
    probable_IV = probable_part + IV_leaked_part
    gamma_gen = Gammator3000(probable_IV, [8,4,3,1,0])
    probable_message = bytes(x^y for x,y in zip(enc_message, gamma_gen.getRandomBytes(len(enc_message))))
    print(probable_part)
    if b'kxctf{' in probable_message:
        print(probable_message.decode())
        
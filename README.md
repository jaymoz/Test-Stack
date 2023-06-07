# Test-Stack
Тестовое задание
С++ разработчик
Описание задания
В рамках задачи необходимо подготовить программу, осуществляющую поиск и
замену данных в шаблонах.
Программа должна делать следующее:
1) Парсить каталог файлов/папок произвольной вложенности
2) В каждом из файлов менять все вхождения шаблона на текст замены.
3) Работать в несколько потоков
4) Сообщать пользователю, что работа выполнена
Также у программы должен быть конфиг файл со следующими данными:
1) Количество потоков на парсинг файлов
2) Адрес корневой директории с файлами и папками
3) Перечисление шаблонов и их замен (неограниченное количество)
Например, "<%COLOR%>" - шаблон, "BLACK" - замена. Во всех файлах шаблон должен
изменится на текст замены после работы программы
Написание unit-тестов будет являться дополнительным плюсом.
Требования к выполнению
- С++11 или выше
- Программа должна работать только с использованием библиотеки STL
- Выполненное задание должно располагаться на Github или Bitbucket.


## Как запустить программу

Откройте проект в редакторе кода. Отредактируйте файл config.txt с нужными вам данными.

1) Откройте терминал и введите make. Подождите, пока программа скомпилируется
2) введите make run

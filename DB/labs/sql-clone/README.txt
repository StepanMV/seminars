Использование (синтаксис строгий, включая пробелы)
(N - кол-во строк, P - кол-во столбцов)

// Создание объекта Database
CREATE TABLE <table_name> (<column name> <type>, <column name> <type>...)
<type> = int, float, bool, str
O(P)

// Чтение (создание из файла .csv) объекта Database
READ TABLE <table_name>
O(P * N) (установка соответствующих типов для каждой строки)

// Добавление строки в таблицу
INSERT INTO <table_name> (<column_name>, <column_name>...) VALUES (<value>, <value>...)
O(P) (установка соответствующих типов)

// Изменение строки таблицы
UPDATE <table_name> ROW <row_id> (<column_name>...) VALUES (<value>...)
O(P) (установка соответствующих типов)

// Удаление строки из таблицы
DELETE FROM <table_name> ROW <row_id>
O(1)

// Сохранение таблицы в .csv файл
SAVE <table_name>
O(N)

// Получение строки из таблицы
GET FROM <table_name> ROW <row_id>
O(1)

// Вывод таблицы
PRINT <table_name>
O(N)

P.S. можно создавать несколько таблиц, они хранятся в словаре

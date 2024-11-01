# Поисковой сервер
## Краткое описание
С написания данной программы происходило знакомство с языком C++.
Проект является прообразом поискового сервера, в связи с чем в нем реализованы лишь его основные функции.

Программа ищет документы содержащие ключевые слова запроса, показывает результаты упорядоченно — начиная с самых полезных, а также может отобразить сколько за последние сутки было запросов, на которые ничего не нашлось. 

Полезность определяется релевантностью документа. Релевантность документа запросу определяется с помощью TF и IDF.
* Полезность слов оценивают понятием inverse document frequency или IDF. Чем в большем количестве документов есть слово, тем ниже IDF (Количество всех документов, имеющихся в базе, делят на количество тех, где встречается слово. Не встречающиеся нигде слова в расчёт не берут, поэтому деления на ноль опасаться не надо. Важно, встречается ли слово в документе. А сколько раз встречается — всё равно). Вычисляется при получении запроса.
* Второй способ улучшить ранжирование — выше располагать документы, где искомое слово встречается более одного раза. Здесь нужно рассчитать term frequency или TF. Для конкретного слова и конкретного документа это доля, которую данное слово занимает среди всех. Вычисляется при добавлении документа в базу.

Расчет релевантности: 
1. IDF каждого слова запроса умножается на TF этого слова в этом документе;
2. Все произведения IDF и TF в документе суммируются.

Порядок работы с программой:
1. Изначально определяются стоп-слова поискового сервера (наличие данных слов не учитывается в результатах поиска).
2. В дальнейшем идет наполнение поискового сервера документами.
Документ содержит id, сам текст. С каждым документом связан набор пользовательских оценок и актуальность.
* Каждая оценка — целое число (положительное, отрицательное или ноль). На основе оценок документа вычисляется его рейтинг. Чтобы найти рейтинг, надо сумму оценок нацело разделить на их количество. Если документ не имеет оценок, его рейтинг равен нулю.
* Каждый документ при добавлении будет помечаться как актуальный (ACTUAL), устаревший (IRRELEVANT), отклонённый (BANNED) или удалённый (REMOVED).
  
3. Поисковой запрос.
Может содержать минус-слова(исключают из результатов поиска документы, содержащие такие слова). В документе минус-слов быть не может.

Для эффективного поиска текста среди большого количества документов применяется инвертированный индекс. Это структура данных, в которой каждому слову соответствует множество документов, в которых это слово встречается.

Программа выдает не все документы, а определённое количество наиболее релевантных страниц. Это количество задается [константной переменной](https://github.com/Eugene-yandex/cpp-search-server/blob/86977d958ab8fd6678682fa092efc255e678a00f/search-server/search_server.h#L13)
Результаты разбиваются на листы, содержащей N страниц. N определяется непосредственно в коде.

Предусмотрена обработка следующих ошибок:
* Указание в поисковом запросе более чем одного минуса перед словами, которых не должно быть в документах, например: кот --пушистый. В середине слов минусы разрешаются, например: иван-чай.
* Отсутствие в поисковом запросе текста после символа «минус», например кот -.
* Наличие спецсимволов в тексте документов и поискового запроса.
* Попытка добавить документ с отрицательным id.
* Попытка добавить документ с id, совпадающим с id документа, который добавился ранее.

## Инструкция по развёртыванию и системные требования 
Версия языка: C++17. Дополнительные требования отстуствуют.

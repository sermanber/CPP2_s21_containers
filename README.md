# s21_containers

Реализация библиотеки s21_containers.h

## Introduction

В данном проекте реализована библиотека контейнерных классов C++: `list`, `map`, `queue`, `set`, `stack`, `vector`. Реализация выполнена в виде шаблонных классов в пространстве имен `s21`. Контейнеры предоставляют стандартные методы и атрибуты для работы с элементами, проверкой заполненности контейнера и итерирования.

## Реализация библиотеки s21_containers.h

- Программа разработана на языке C++ стандарта C++20 с использованием компилятора gcc.
- Код программы находится в папке src.
- При написании кода соблюдается Google Style.
- Обязательно используются итераторы.
- Классы обязательно шаблонные.
- Классы реализованы внутри пространства имен `s21`.
- Подготовлено полное покрытие unit-тестами методов контейнерных классов c помощью библиотеки GTest.
- Запрещено копирование реализации стандартной библиотеки шаблонов (STL).
- Соблюдена логика работы стандартной библиотеки шаблонов (STL) в части проверок, работы с памятью и поведения в нештатных ситуациях.

## Part 1. Реализация библиотеки s21_containers.h

- Реализованы классы библиотеки `s21_containers.h`: `list`, `map`, `queue`, `set`, `stack`, `vector`.
- Решение оформлено в виде заголовочного файла `s21_containers.h`, который включает в себя другие заголовочные файлы с реализациями необходимых контейнеров (`s21_list.h`, `s21_map.h` и т. д.).
- Предусмотрен Makefile для тестов написанной библиотеки с целями `clean`, `test`.
- Список реализован через структуру списка, а не через массив.

## Part 2. Дополнительно. Реализация библиотеки s21_containersplus.h

- Дополнительно реализованы классы библиотеки `s21_containersplus.h`: `array`, `multiset`.
- Решение оформлено в виде заголовочного файла `s21_containersplus.h`, который включает в себя другие заголовочные файлы с реализациями необходимых контейнеров (`s21_array.h`, `s21_multiset.h`).
- Предусмотрен Makefile для тестов написанной библиотеки с целями `clean`, `test`.

## Part 3. Дополнительно. Реализация методов insert_many

Дополнительно реализованы методы `insert_many` согласно таблице:

| Modifiers | Definition | Containers |
|-----------|------------|------------|
| `iterator insert_many(const_iterator pos, Args&&... args)` | Inserts new elements into the container directly before `pos`. | List, Vector. |
| `void insert_many_back(Args&&... args)` | Appends new elements to the end of the container. | List, Vector, Queue, Stack. |
| `void insert_many_front(Args&&... args)` | Appends new elements to the top of the container. | List. |
| `vector<std::pair<iterator,bool>> insert_many(Args&&... args)` | Inserts new elements into the container. | Map, Set, Multiset. |

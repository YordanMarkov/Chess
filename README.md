# Chess
***Опростен Шах***
* *Мина Славова, Йордан Марков, Никола Милков, Румен Ценков*
* *10в клас*

# Кратка информация
* *Опростен Шах е съвсем нормален шах, но с намален брой фигури. Включва: 1 вражески цар (KE); 2 приятелски топа (R1, R2) и 1 приятелски цар (KF). Приема се логиката, че ние сме с белите фигури, защото винаги местим първи. Играта съдържа меню, от което определяме размер, стартираме нова игра, стартираме Replay от последно изиграната игра и избираме дали да се излезе от програмата. По време на играта се разпечатват 2 дъски - една за наш ход и една за ход на противника. В края на играта излиза кратка статистика, показваща всички ходове на фигурите и брой пъти шах на противника.*

# Източници
  * [Помощ за работа с файлове №1](https://www.tutorialspoint.com/the-best-way-to-check-if-a-file-exists-using-standard-c-cplusplus)
  * [Помощ за работа с файлове №2](https://www.programiz.com/c-programming/c-file-input-output)
  * [Помощ за работа с файлове №3](https://www.tutorialspoint.com/the-best-way-to-check-if-a-file-exists-using-standard-c-cplusplus)
  * [Помощ за работа с файлове №4](https://www.delftstack.com/howto/c/c-check-if-file-exists/)
  * [Atoi](https://www.geeksforgeeks.org/converting-strings-numbers-cc/)
  * [Rand](https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm)

# Разпределение на задължения
<br/>*Мина Славова и Йордан Марков*
  * 1. Функция за генериране на поле (Подава се размер - 6, 8 или 10)
  * 2. Функция за генериране на фигурите на дъската (Използва се логиката: Белите фигури могат да бъдат навсякъде из полето, при условие, че няма да образуват шах от самото начало, царете не се допират един в друг и царят на компютъра няма съседи (Топовете могат да стоят диагонално от царя!).
  * 3. Създаване на главното меню на играта.
  * 4. Функция, която взема фигура и я премества (Включва множество проверки за валидност).
  * 5. Функция, която проверява дали има шах или мат.
  * 6. Изкарване на:
  *   - Брой местения на фигурите
  *   - Брой пъти шах
  * 7. Мърдането на царя на компютъра (включва предпазване от шах).

<br/>*Никола Милков и Румен Ценков*
  * 1. Царят на противника трябва да може да взима фигури при нужда. (**ВНИМАНИЕ!** Тази функция **не може** да бъде осъществена, поради наличието на затруднения.)
  * 2. Записването на ходовете в текстов файл. Включва:
  *   - Началните позиции на фигурите
  *   - Размер на дъската
  *   - Записване на избраните фигури
  *   - Записване на движенията на противниковия цар
  * 3. Research как да се взима информация от файл и как да се прилага.
  * 4. Разчитане на информацията (Приложение на research-а). Включва:
  *   - Преработване на функциите при нужда
  *   - Добавяне на нови функции при нужда
  *   - Обработване на main
  * 5. Стартиране на Replay; Графично изобразяване на движенията. 

<br/>*Всички*
  * 1. Research как се играе шах.
  * 2. Помагане на АБСОЛЮТНО всеки. Включва:
  *   - Консултация в Discord
  *   - Помагане с кода
  *   - Споделяне на информация, свързана с логиката на програмата
  * 3. Създаването на README.
  * 4. Козметични промени по цялостния файл.

# Текуща готовност на проекта
  * Последно качен файл (считащ се за "финална версия" до сегашния момент): [Натиснете тук](https://github.com/YordanMarkov/Chess/blob/main/Final_Part_ver3.c)

# SimpleTextAnalyzer
[![Build Status](https://travis-ci.com/timerke/SimpleTextAnalyzer.svg?branch=main)](https://travis-ci.com/timerke/SimpleTextAnalyzer)
Приложение на Си для простого анализа текстового файла
## Задание 
Разработать программу анализа текстового файла. Программа должна считывать файл с текстом и проводить его частотный анализ. Результаты работы программы должны сохраняться в файл. 
## Требования к тексту 
Текст состоит из «слов» (только английские буквы и цифры), разделенных пробельными символами (пробел, знак табуляции и знак переноса на новую строку) и(или) знаками пунктуации (запятая, точка, тире, кавыка и прочее). Слова не переносятся. Апостроф не учитывать (считать как два отдельных слова: don't = don + t).
## Требования к реализации 
### Общие сведения о тексте (обязательная часть)
Программа должна подсчитывать общее число абзацев, количество предложений и количество слов в тексте, среднее количество слов в предложении.
### Подсчет частоты символов
Программа должна подсчитывать частоту каждого символа (включая пробелы и разделители) в тексте.
### Подсчет частоты слов
Программа должна считывать текст и дробить его на «слова» (непрерывная последовательность букв и(или) цифр). Формировать из полученного набора слов словарь, содержащий только уникальные слова (дублирований слов в словаре быть не должно). Словарь должен содержать информацию о частоте встречаемости слова (Частота слова = Количество повторений слова в тексте / Общее число слов).

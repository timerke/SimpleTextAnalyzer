#pragma once
#ifndef TEXT_ANALYZER_H
#define TEXT_ANALYZER_H

// Постоянные
const unsigned int N = 100;
const unsigned int WORD_LENGTH = 30;

/**
 * Структура для хранения символа и количества его появлений.
 */
struct Symbol
{
	char s; // символ
	unsigned int n; // количество
};

/**
 * Структура для хранения слова и количества его появлений. Принято, что
 * в слове не может быть больше WORD_LENGTH символов.
 */
struct Word
{
	char word[WORD_LENGTH]; // слово
	double f = -1.0; // частота
	unsigned int length; // длина слова
	unsigned int n; // количество
};

// Функция добавляет символ в массив символов
void add_symbol(Symbol*, unsigned int&, unsigned int&, char);

// Функция добавляет слово в массив слов
void add_word(Word*, unsigned int&, unsigned int&, char*, unsigned int);

// Функция анализирует текст из файла
void analyze_text(const char*);

// Функция вычисляет частоту по предложений
void calculate_frequencies(Word*, unsigned int);

// Функция проверяет, является ли символ разделителем
bool check_delimiter(char);

// Функция проверяет, является ли символ пробелом, табуляцией или переносом
// строки
bool check_space(char);

// Функция выводит на экран информацию о символах
void show_symbols(Symbol*, unsigned int);

// Функция выводит на экран информацию о словах
void show_words(Word*, unsigned int);

#endif // !TEXT_ANALYZER_H
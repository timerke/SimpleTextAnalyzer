/*
Модуль с объявлениями функций, используемых для анализа текста.
*/

#pragma once
#ifndef TEXT_ANALYZER_H
#define TEXT_ANALYZER_H

#include <stdbool.h>
#include "new_types.h"
#define N 100
#define WORD_LENGTH 30

// Функция добавляет символ в массив символов
void add_symbol(struct Symbol**, unsigned int*, unsigned int*, char);

// Функция добавляет слово в массив слов
void add_word(struct Word**, unsigned int*, unsigned int*, char*, unsigned int);

// Функция анализирует текст из файла
void analyze_text(const char*);

// Функция вычисляет частоту символов
void calculate_symbols_frequencies(struct Symbol*, unsigned int);

// Функция вычисляет частоту слов
void calculate_words_frequencies(struct Word*, unsigned int,
	unsigned int);

// Функция вычисляет количество слов в тексте
unsigned int calculate_words(struct Word*, unsigned int);

// Функция проверяет, является ли символ разделителем
bool check_delimiter(char);

// Функция проверяет, является ли символ пробелом, табуляцией или переносом
// строки
bool check_space(char);

// Функция выводит на экран информацию об анализе текста
void show_info(unsigned int, unsigned int, unsigned int, struct Symbol*,
	unsigned int, struct Word*, unsigned int);

// Функция выводит на экран информацию о символах
void show_symbols(struct Symbol*, unsigned int);

// Функция выводит на экран информацию о словах
void show_words(struct Word*, unsigned int);

#endif // !TEXT_ANALYZER_H
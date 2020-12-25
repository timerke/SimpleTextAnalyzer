/*
Модуль содержит объявления полезных функций.
*/

#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>
#include "new_types.h"


// Функция сравнивает две строки
bool compare_strings(const char*, const char*);

// Функция выбирает элемент в качестве опорного в быстрой сортирове массива
// символов
unsigned int make_symbols_partition(struct Symbol**, unsigned int,
	unsigned int);

// Функция сортирует массив символов по количеству
void sort_symbols(struct Symbol**, unsigned int, unsigned int);

// Функция выбирает элемент в качестве опорного в быстрой сортирове массива
// слов
unsigned int make_words_partition(struct Word**, unsigned int,
	unsigned int);

// Функция сортирует массив слов по количеству
void sort_words(struct Word**, unsigned int, unsigned int);

#endif // !FUNCTIONS_H
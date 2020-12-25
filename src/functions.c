/*
Модуль содержит определения полезных функций.
*/

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"


/**
 * Функция сравнивает две строки.
 * @param s1, s2: сравниваемые строки;
 * @return: true, если строки равны, иначе false.
 */
bool compare_strings(const char* s1, const char* s2)
{
	int i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		else
			return false;
	}
	if ((s1[i] == '\0' && s2[i] != '\0') || (s1[i] != '\0' && s2[i] == '\0'))
		return false;
	return true;
}

/**
 * Функция выбирает элемент в качестве опорного в быстрой сортирове массива
 * символов.
 * @param s: массив символов;
 * @param left, right: наименьший и наибольший индексы, для которых нужно
 * отсортировать массив.
 * @return: индекс опорного элемента.
 */
unsigned int make_symbols_partition(struct Symbol** s, unsigned int left,
	unsigned int right)
{
	// Выбираем средний элемент в качестве опорного
	struct Symbol pivot = (*s)[(left + right) / 2];
	unsigned int i = left - 1;
	unsigned int j = right + 1;
	while (true)
	{
		i++;
		while ((*s)[i].n < pivot.n)
			i++;
		j--;
		while ((*s)[j].n > pivot.n)
			j--;
		if (i >= j)
			return j;
		// Если элемент с индексом i (слева от опорного) больше, чем элемент с
		// индексом j (справа от опорного), меняем их местами
		struct Symbol spam = (*s)[i];
		(*s)[i] = (*s)[j];
		(*s)[j] = spam;
	}
}

/**
 * Функция сортирует массив символов по количеству. Используется быстрая
 * сортировка.
 * @param s: массив символов;
 * @param left, right: наименьший и наибольший индексы, для которых нужно
 * отсортировать массив.
 */
void sort_symbols(struct Symbol** s, unsigned int left,
	unsigned int right)
{
	if (left < right)
	{
		unsigned int index = make_symbols_partition(s, left, right);
		sort_symbols(s, left, index);
		sort_symbols(s, index + 1, right);
	}
}

/**
 * Функция выбирает элемент в качестве опорного в быстрой сортирове массива
 * слов.
 * @param w: массив слов;
 * @param left, right: наименьший и наибольший индексы, для которых нужно
 * отсортировать массив.
 * @return: индекс опорного элемента.
 */
unsigned int make_words_partition(struct Word** w, unsigned int left,
	unsigned int right)
{
	// Выбираем средний элемент в качестве опорного
	struct Word pivot = (*w)[(left + right) / 2];
	unsigned int i = left - 1;
	unsigned int j = right + 1;
	while (true)
	{
		i++;
		while ((*w)[i].n < pivot.n)
			i++;
		j--;
		while ((*w)[j].n > pivot.n)
			j--;
		if (i >= j)
			return j;
		// Если элемент с индексом i (слева от опорного) больше, чем элемент с
		// индексом j (справа от опорного), меняем их местами
		struct Word spam = (*w)[i];
		(*w)[i] = (*w)[j];
		(*w)[j] = spam;
	}
}

/**
 * Функция сортирует массив слов по количеству. Используется быстрая
 * сортировка.
 * @param w: массив слов;
 * @param left, right: наименьший и наибольший индексы, для которых нужно
 * отсортировать массив.
 */
void sort_words(struct Word** w, unsigned int left,
	unsigned int right)
{
	if (left < right)
	{
		unsigned int index = make_words_partition(w, left, right);
		sort_words(w, left, index);
		sort_words(w, index + 1, right);
	}
}
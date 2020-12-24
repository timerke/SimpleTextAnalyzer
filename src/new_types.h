/*
Модуль с определением дополнительных типов-структур.
*/

#pragma once
#ifndef NEW_TYPES_H
#define NEW_TYPES_H

#define WORD_LENGTH 30

/**
 * Структура для хранения символа и количества его появлений.
 */
struct Symbol
{
	char s; // символ
	double f; // частота
	unsigned int n; // количество
};

/**
 * Структура для хранения слова и количества его появлений. Принято, что
 * в слове не может быть больше WORD_LENGTH символов.
 */
struct Word
{
	char word[WORD_LENGTH]; // слово
	double f; // частота
	unsigned int length; // длина слова
	unsigned int n; // количество
};

#endif // !NEW_TYPES_H
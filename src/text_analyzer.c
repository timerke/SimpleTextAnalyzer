/*
Модуль содержит определения функций для анализа текста.
*/

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "text_analyzer.h"


/**
 * Функция добавляет символ в массив символов.
 * @param symbols: массив символов;
 * @param n_max: допустимое количество элементов в массиве;
 * @param n: количество записанных элементов в массиве;
 * @param c: добавляемый символ.
 */
void add_symbol(struct Symbol** symbols, unsigned int* n_max, unsigned int* n,
	char c)
{
	// Проверяем, записан ли символ в массив
	for (unsigned int i = 0; i < (*n); i++)
	{
		if ((*symbols)[i].s == c)
		{
			// Символ уже записан, увеличиваем количество
			(*symbols)[i].n++;
			return;
		}
	}
	// Символ еще не записан
	if ((*n) == (*n_max))
	{
		// В массиве нет свободных мест, нужно добавить места
		(*n_max) += N;
		size_t size = (*n_max) * sizeof(struct Symbol);
		struct Symbol* new_symbols = (struct Symbol*)malloc(size);
		for (unsigned int i = 0; i < (*n); i++)
		{
			new_symbols[i].s = (*symbols)[i].s;
			new_symbols[i].f = (*symbols)[i].f;
			new_symbols[i].n = (*symbols)[i].n;
		}
		// Освобождаем память и получаем указатель на новую
		free(*symbols);
		*symbols = new_symbols;
	}
	(*symbols)[*n].s = c;
	(*symbols)[*n].f = -1.0;
	(*symbols)[*n].n = 1;
	(*n)++;
}

/**
 * Функция добавляет слово в массив слов.
 * @param words: массив слов;
 * @param n_words_max: допустимое количество элементов в массиве;
 * @param n_words: количество записанных элементов в массиве;
 * @param word: добавляемое слово;
 * @param n: количество символов в добавляемом слове.
 */
void add_word(struct Word** words, unsigned int* n_words_max,
	unsigned int* n_words, char* word, unsigned int n)
{
	// Проверяем, записано ли слово в массив
	for (unsigned int i = 0; i < *n_words; i++)
	{
		if ((*words)[i].length != n)
			// Добавляемое слово не совпадает со словом из массива по длине
			continue;
		// Слова по длине совпадают
		bool is_equal = true;
		for (unsigned int j = 0; j < n; j++)
		{
			if ((*words)[i].word[j] != word[j])
			{
				// Слова отличаются
				is_equal = false;
				break;
			}
		}
		if (is_equal)
		{
			// Слово уже добавлено в массив, увеличиваем количество
			(*words)[i].n++;
			return;
		}
	}
	// Слово пока не записано в массив
	if (*n_words == *n_words_max)
	{
		// В массиве нет свободных мест, нужно добавить места
		(*n_words_max) += N;
		size_t size = (*n_words_max) * sizeof(struct Word);
		struct Word* new_words = (struct Word*)malloc(size);
		for (unsigned int i = 0; i < *n_words; i++)
		{
			for (unsigned int j = 0; j < (*words)[i].length; j++)
				new_words[i].word[j] = (*words)[i].word[j];
			if ((*words)[i].length < WORD_LENGTH)
				new_words[i].word[(*words)[i].length] = '\0';
			new_words[i].length = (*words)[i].length;
			new_words[i].n = (*words)[i].n;
		}
		// Освобождаем память и получаем указатель на новую
		free(*words);
		*words = new_words;
	}
	// Добавляем слово. Учитываем, что максимальная длина слова WORD_LENGTH
	unsigned int length = n < WORD_LENGTH ? n : WORD_LENGTH;
	for (unsigned int i = 0; i < length; i++)
		(*words)[*n_words].word[i] = word[i];
	// Если есть свободное место в слове, добавляем символ конца строки
	if (length < WORD_LENGTH)
		(*words)[*n_words].word[length] = '\0';
	(*words)[*n_words].length = length;
	(*words)[*n_words].f = -1.0;
	(*words)[*n_words].n = 1;
	(*n_words)++;
}

/**
 * Функция анализирует текст из файла.
 * @param filename: имя файла.
 */
void analyze_text(const char* filename)
{
	// Открываем файл с текстом
	FILE* file = fopen(filename, "r");
	if (file == NULL)
		// Не удалось открыть файл
		return;
	// Файл открыть удалось
	char c; // переменная для прочтенного символа из текста
	char previous_c; // переменная для предыдущего символа
	// Массив символов из текста
	size_t size = N * sizeof(struct Symbol);
	struct Symbol* symbols = (struct Symbol*)malloc(size);
	unsigned int n_sym_max = N;
	unsigned int n_sym = 0;
	// Массив слов из текста
	size = N * sizeof(struct Word);
	struct Word* words = (struct Word*)malloc(size);
	unsigned int n_words_max = N;
	unsigned int n_words = 0;
	// Переменная для слов из текста
	char word[WORD_LENGTH];
	unsigned int n = 0; // длина слова
	// Переменные для подсчета количества предложений
	unsigned int sentences = 0; // количество предложений
	bool is_new_sentence = true; // новое предложение
	// Переменные для подсчета количества абзацев
	unsigned int paragraphs = 0; // количество абзацев
	bool is_new_paragraph = true; // новый абзац
	while ((c = fgetc(file)) != EOF)
	{
		// Добавляем символ
		add_symbol(&symbols, &n_sym_max, &n_sym, c);
		// Работаем со словами
		if (check_delimiter(c) && !check_delimiter(previous_c))
		{
			// Добавляем слово
			add_word(&words, &n_words_max, &n_words, word, n);
			n = 0;
		}
		else if (!check_delimiter(c))
		{
			word[n] = c;
			n++;
		}
		// Работаем с предложениями
		if (c == '.' || c == '!' || c == '?')
			is_new_sentence = true;
		else if (is_new_sentence && !check_space(c))
		{
			is_new_sentence = false;
			sentences++;
		}
		// Работаем с абзацами
		if (c != '\n')
			is_new_paragraph = true;
		if (c == '\n' && previous_c != '\n')
		{
			is_new_paragraph = false;
			paragraphs++;
		}
		previous_c = c;
	}
	if (is_new_paragraph)
		paragraphs++;
	// Закрываем файл
	fclose(file);
	// Вычисляем частоту появления символов
	calculate_symbols_frequencies(symbols, n_sym);
	// Вычисляем полное количество слов
	unsigned int total_words = calculate_words(words, n_words);
	// Вычисляем частоту появления слов
	calculate_words_frequencies(words, n_words, total_words);
	// Выводим информацию
	show_info(paragraphs, sentences, total_words, symbols, n_sym, words, n_words);
	// Освобождаем память
	free(symbols);
	free(words);
}

/**
 * Функция вычисляет частоту символов.
 * @param symbols: массив символов;
 * @param n: количество записанных элементов в массиве.
 */
void calculate_symbols_frequencies(struct Symbol* symbols, unsigned int n)
{
	// Вычисляем полное количество символов
	unsigned int total = 0;
	for (unsigned int i = 0; i < n; i++)
		total += symbols[i].n;
	// Вычисляем частоту появляения символов в тексте
	for (unsigned int i = 0; i < n; i++)
		symbols[i].f = 1.0 * symbols[i].n / total;
}

/**
 * Функция вычисляет частоту слов.
 * @param words: массив слов;
 * @param n: количество записанных элементов в массиве;
 * @param n_words: полное количество слов в тексте.
 */
void calculate_words_frequencies(struct Word* words, unsigned int n,
	unsigned int n_words)
{
	// Вычисляем частоту появляения слов в тексте
	for (unsigned int i = 0; i < n; i++)
		words[i].f = 1.0 * words[i].n / n_words;
}

/**
 * Функция вычисляет количество слов в тексте.
 * @param words: массив слов;
 * @param n: количество записанных элементов в массиве.
 * @return: количество слов.
 */
unsigned int calculate_words(struct Word* words, unsigned int n)
{
	double total = 0;
	for (unsigned int i = 0; i < n; i++)
		total += words[i].n;
	return total;
}

/**
 * Функция проверяет, является ли символ разделителем.
 * @param c: проверяемый символ.
 * @return: true, если символя является разделителем, иначе fasle.
 */
bool check_delimiter(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == ',' || c == '.' || c == ';' ||
		c == ':' || c == '(' || c == ')' || c == '/' || c == '\'' || c == '"')
		return true;
	return false;
}

/**
 * Функция проверяет, является ли символ пробелом, табуляцией или переносом
 * строки.
 * @param c: проверяемый символ.
 * @return: true, если символ является пробелом, табуляцией или переносом
 * строки, иначе false.
 */
bool check_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return true;
	return false;
}

/**
 * Функция выводит на экран информацию об анализе текста.
 * @param paragraphs: количество абзацев;
 * @param sentences: количество предложений;
 * @param total_words: полное количество слов;
 * @param s: массив символов;
 * @param n_s: количество записанных элементов в массиве символов;
 * @param w: массив слов;
 * @param n_w: количество записанных элементов в массиве слов.
 */
void show_info(unsigned int paragraphs, unsigned int sentences,
	unsigned int total_words, struct Symbol* s, unsigned int n_s,
	struct Word* w, unsigned int n_w)
{
	// Общая информация
	printf("\nОбщая информация:\n");
	printf("\tКоличество абзацев: %d.\n", paragraphs);
	printf("\tКоличество предложений: %d.\n", sentences);
	printf("\tКоличество слов: %d, среднее количество слов в предложении: %.3f.\n",
		total_words, 1.0 * total_words / sentences);
	// Информация о символах
	show_symbols(s, n_s);
	// Информация о словах
	show_words(w, n_w);
}

/**
 * Функция выводит на экран информацию о символах.
 * @param symbols: массив символов;
 * @param n: количество записанных элементов в массиве.
 */
void show_symbols(struct Symbol* symbols, unsigned int n)
{
	printf("\nСимволы из текста:\n");
	printf("\tсимвол\tколичество\tчастота\n");
	for (unsigned int i = 0; i < n; i++)
	{
		if (symbols[i].s == '\n')
			printf("\t\\n");
		else if (symbols[i].s == '\t')
			printf("\t\\t");
		else if (symbols[i].s == ' ')
			printf("\t' '");
		else
			printf("\t%c", symbols[i].s);
		printf("\t%d", symbols[i].n);
		if (symbols[i].f != -1.0)
			printf("\t%.4f", symbols[i].f);
		printf("\n");
	}
}

/**
 * Функция выводит на экран информацию о словах.
 * @param words: массив слов;
 * @param n: количество записанных элементов в массиве.
 */
void show_words(struct Word* words, unsigned int n)
{
	printf("\nСлова из текста:\n");
	printf("\tслово\tколичество\tчастота\n");
	for (unsigned int i = 0; i < n; i++)
	{
		printf("\t%s\t%d", words[i].word, words[i].n);
		if (words[i].f != -1.0)
			printf("\t%.4f", words[i].f);
		printf("\n");
	}
}
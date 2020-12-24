/*
Модуль содержит определения функций для анализа текста.
*/

#include <iostream>
#include <stdio.h>
#include "text_analyzer.h"


/**
 * Функция добавляет символ в массив символов.
 * @param symbols: массив символов;
 * @param n_max: допустимое количество элементов в массиве;
 * @param n: количество записанных элементов в массиве;
 * @param c: добавляемый символ.
 */
void add_symbol(Symbol* symbols, unsigned int& n_max, unsigned int& n, char c)
{
	// Проверяем, записан ли символ в массив
	for (unsigned int i = 0; i < n; i++)
	{
		if (symbols[i].s == c)
		{
			// Символ уже записан, увеличиваем количество
			symbols[i].n++;
			return;
		}
	}
	// Символ еще не записан
	if (n == n_max)
	{
		// В массиве нет свободных мест, нужно добавить места
		n_max += N;
		Symbol* new_symbols = new Symbol[n_max];
		for (unsigned int i = 0; i < n; i++)
		{
			new_symbols[i].s = symbols[i].s;
			new_symbols[i].n = symbols[i].n;
		}
		delete[]symbols;
	}
	symbols[n].s = c;
	symbols[n].n = 1;
	n++;
}

/**
 * Функция добавляет слово в массив слов.
 * @param words: массив слов;
 * @param n_words_max: допустимое количество элементов в массиве;
 * @param n_words: количество записанных элементов в массиве;
 * @param word: добавляемое слово;
 * @param n: количество символов в добавляемом слове.
 */
void add_word(Word* words, unsigned int& n_words_max, unsigned int& n_words,
	char* word, unsigned int n)
{
	// Проверяем, записано ли слово в массив
	for (unsigned int i = 0; i < n_words; i++)
	{
		if (words[i].length != n)
			// Добавляемое слово не совпадает со словом из массива по длине
			continue;
		// Слова по длине совпадают
		bool is_equal = true;
		for (unsigned int j = 0; j < n; j++)
		{
			if (words[i].word[j] != word[j])
			{
				// Слова отличаются
				is_equal = false;
				break;
			}
		}
		if (is_equal)
		{
			// Слово уже добавлено в массив, увеличиваем количество
			words[i].n++;
			return;
		}
	}
	// Слово пока не записано в массив
	if (n_words == n_words_max)
	{
		// В массиве нет свободных мест, нужно добавить места
		n_words_max += N;
		Word* new_words = new Word[n_words_max];
		for (unsigned int i = 0; i < n_words; i++)
		{
			for (unsigned int j = 0; j < words[i].length; j++)
				new_words[i].word[j] = words[i].word[j];
			new_words[i].length = words[i].length;
			new_words[i].n = words[i].n;
		}
		delete[]words;
	}
	// Добавляем слово
	for (unsigned int i = 0; i < n; i++)
		words[n_words].word[i] = word[i];
	words[n_words].word[n] = '\0';
	words[n_words].length = n;
	words[n_words].n = 1;
	n_words++;
}

/**
 * Функция анализирует текст из файла.
 * @param filename: имя файла.
 */
void analyze_text(const char* filename)
{
	setlocale(LC_ALL, "Rus");
	// Открываем файл с текстом
	FILE* file = fopen(filename, "r");
	if (file == NULL)
		// Не удалось открыть файл
		return;
	// Файл открыть удалось
	char c; // переменная для прочтенного символа из текста
	char previous_c; // переменная для предыдущего символа
	// Массив символов из текста
	Symbol* symbols = new Symbol[N];
	unsigned int n_sym_max = N;
	unsigned int n_sym = 0;
	// Массив слов из текста
	Word* words = new Word[N];
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
		add_symbol(symbols, n_sym_max, n_sym, c);
		// Работаем со словами
		if (check_delimiter(c) && !check_delimiter(previous_c))
		{
			// Добавляем слово
			add_word(words, n_words_max, n_words, word, n);
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
	// Вычисляем частоту появления слов
	calculate_frequencies(words, n_words);
	// Выводим на экран результаты анализа
	show_symbols(symbols, n_sym);
	show_words(words, n_words);
	std::cout << "\nКоличество предложений: " << sentences << ".\n";
	std::cout << "Количество абзацев: " << paragraphs << ".\n";
	// Освобождаем память
	delete[]symbols;
	delete[]words;
}

/**
 * Функция вычисляет частоту по предложений.
 * @param words: массив слов;
 * @param n: количество записанных элементов в массиве.
 */
void calculate_frequencies(Word* words, unsigned int n)
{
	// Вычисляем общее количество слов в тексте
	double total = 0;
	for (unsigned int i = 0; i < n; i++)
		total += words[i].n;
	// Вычисляем частоту появляения слов тексте
	for (unsigned int i = 0; i < n; i++)
		words[i].f = words[i].n / total;
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
 * Функция выводит на экран информацию о символах.
 * @param symbols: массив символов;
 * @param n: количество записанных элементов в массиве.
 */
void show_symbols(Symbol* symbols, unsigned int n)
{
	std::cout << "\nСимволы из текста:\n";
	for (unsigned int i = 0; i < n; i++)
	{
		if (symbols[i].s == '\n')
			std::cout << "\\n";
		else if (symbols[i].s == '\t')
			std::cout << "\\t";
		else if (symbols[i].s == ' ')
			std::cout << "' '";
		else
			std::cout << symbols[i].s;
		std::cout << " - " << symbols[i].n << "\n";
	}
}

/**
 * Функция выводит на экран информацию о словах.
 * @param words: массив слов;
 * @param n: количество записанных элементов в массиве.
 */
void show_words(Word* words, unsigned int n)
{
	std::cout << "\nСлова из текста:\n";
	for (unsigned int i = 0; i < n; i++)
	{
		std::cout << words[i].word << " - " << words[i].n;
		if (words[i].f != -1.0)
			std::cout << " - " << words[i].f;
		std::cout << "\n";
	}
}
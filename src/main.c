﻿#include "functions.h"
#include "text_analyzer.h"


int main(int argc, char** argv)
{
	// Из командной строки приложение может получить несколько параметров:
	// 1) после обзначения -i нужно указать путь к файлу, который нужно
	// проанализировать;
	// 2) после обозначения -o можно указать путь к файлу, в который будут
	// сохранены результаты анализа текста. Если путь к файлу не указывать,
	// результаты будут выведены на экран
	const char IN[] = "-i";
	const char OUT[] = "-o";
	char* out_file = nullptr; // имя файла для записи результата
	char* src_file = nullptr; // имя файла с текстом для анализа
	for (int i = 0; i < argc;)
	{
		if (compare_strings(argv[i], IN) && i < argc)
		{
			// Следующий параметр из командной строки должен быть именем файла
			// с текстом
			src_file = argv[i + 1];
			i += 2;
			continue;
		}
		else if (compare_strings(argv[i], OUT) && i < argc)
		{
			// Следующий параметр из командной строки должен быть именем файла,
			// в который нужно сохранить результаты
			out_file = argv[i + 1];
			i += 2;
			continue;
		}
		i++;
	}
	if (src_file == NULL)
		// Если в командной строке не передано имя файла, задаем файл по умолчанию
		src_file = (char*)"text1.txt";
	// Анализируем текст
	analyze_text(src_file, out_file);
}
#include <fstream>
#include <iostream>

int main()
{
	std::ifstream in, in1, in2; // Потоки для чтения из файлов
	std::ofstream out, out1, out2; // Потоки для записи в файлы
	int a, b = 0;
	int size = 0;   // Количество чисел в файле
	int p, t, count = 0;
	bool flag = true; // Флаг для чередования между файлами A и B
	bool A_full, B_full = true; // Флаги, указывающие, есть ли еще данные в файлах A и B
	in.open("input.txt"); // Открываем файл для чтения
	out.open("exit.txt"); // Открываем файл для записи

	// Считываем числа из входного файла и записываем в "exit.txt", подсчитывая их количество
	while (in >> a)
	{
			out << a << "\n";
			size++;
	}

	in.close();
	out.close();

	// Внешняя многофазная сортировка
	for (int i = 1; i < size; i *= 2) // Увеличиваем размер сегмента в 2 раза на каждой итерации
	{
			// Разделяем отсортированные сегменты на два файла, A и B
			in.open("exit.txt");
			out1.open("A.txt");
			out2.open("B.txt");
			count = 0; // Счетчик чисел на сегмент
			while (in >> a)
			{
					count++;
					if (flag) // Чередование записи между файлами A и B
							out1 << a << "\n";
					else
							out2 << a << "\n";

					if (count == i) // Переключаемся на другой файл после записи i чисел
					{
							count = 0;
							flag = !flag;
					}
			}

			in.close();
			out1.close();
			out2.close();

			// Слияние файлов A и B обратно в "exit.txt", упорядочивая элементы
			in1.open("A.txt");
			in2.open("B.txt");
			out.open("exit.txt");

			// Проверяем наличие данных в файлах A и B
			A_full = (in1 >> a) ? true : false;
			B_full = (in2 >> b) ? true : false;

			// Сливаем данные из файлов A и B в "exit.txt", упорядочивая их
			for (int j = 0; j < size; j += 2 * i)
			{
					p = 0; t = 0;
					// Сливаем сегменты до тех пор, пока не закончатся элементы в одном из сегментов
					while (p < i && A_full && t < i && B_full)
					{
							if (a < b)
							{
									out << a << "\n";
									A_full = (in1 >> a) ? true : false;
									p++;
							}
							else
							{
									out << b << "\n";
									B_full = (in2 >> b) ? true : false;
									t++;
							}
					}
					// Дозаписываем оставшиеся элементы из A или B, если сегменты не были один одинакового размера
			
					while (p < i && A_full) // Если остались элементы в файле A
					{
							out << a << "\n"; // Записываем их в выходной файл
							A_full = (in1 >> a) ? true : false; // Читаем следующий элемент, если он есть
							p++;
					}
					while (t < i && B_full) // Если остались элементы в файле B
					{
							out << b << "\n"; // Записываем их в выходной файл
							B_full = (in2 >> b) ? true : false; // Читаем следующий элемент, если он есть
							t++;
					}
			}

			in1.close();
			in2.close();
			out.close();

			// Удаляем временные файлы A и B, так как они больше не нужны
			remove("A.txt");
			remove("B.txt");
	}

	return 0; // Завершаем выполнение программы
}

#ifndef REPORTS_GENERATOR_H_
#define REPORTS_GENERATOR_H_

#include <vector>
#include <string>
#include "class_part.h"		// Класс и функции для работы с деталями.

class reports_generator {	// Класс для связи графического интерфейса с остальной частью программы и непосредственной генерации txt-отчётов.
private:
	QString parts_filename;				// Путь и имя входного XML-файла.
	QString output_directory;			// Путь к каталогу для сохранения отчётов.
	std::string outfilename_begin;		// Первая часть имён txt-файлов - обозначение головного изделия.
	std::vector<part> parts_vector;		// Вектор для хранения и сортировки деталей.
public:
	reports_generator(const QString & xml_file, const QString & rep_dir);	// В первом параметре передаётся путь и имя входного XML-файла,
																			// во втором параметре - путь к каталогу для сохранения отчётов.
};

#endif

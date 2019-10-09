#include "reports_generator.h"

reports_generator::reports_generator(const QString & xml_file, const QString & rep_dir) :
	parts_filename(xml_file), output_directory(rep_dir)
{
	xml_file_read(parts_filename, outfilename_begin, parts_vector);		// Вызов функции для разбора входного XML-файла, извлечения первой части имён txt-файлов
																		// (обозначения головного изделия) и помещения деталей в вектор.
	sort(parts_vector.begin(), parts_vector.end());		// Сортировка деталей.
	txt_reports_output(outfilename_begin, output_directory.toLocal8Bit().toStdString(), parts_vector);	//Генерация txt-отчёта на основе отсортированного вектора.
}
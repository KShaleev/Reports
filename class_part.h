#ifndef CLASS_PART_H_
#define CLASS_PART_H_

#include <QtXml>	// Библиотека для работы с XML-файлами.
#include <vector>
#include <string>
#include <fstream>

using std::string;

class part {			// Класс, содержащий информацию о детали.
private:
	string uid;			// Внутренний уникальный идентификатор изделия.
	string item_id;		// Обозначение.
	string rev_id;		// Ревизия.
	string type;		// Тип изделия.
	string name;		// Наименование.
	string desc;		// Описание.
public:
	part(const string & u, const string & i_id, const string & r_id, const string & tp, const string & nm, const string & dsc);
	bool operator<(const part & p2);		// Перегрузка оператора < для сортировки деталей.
	string get_uid() const { return uid; }
	string get_item_id() const { return item_id; }
	string get_rev_id() const { return rev_id; }
	string get_type() const { return type; }
	string get_name() const { return name; }
	string get_desc() const { return desc; }
};

void xml_file_read(const QString & xml_source_filename, string & filename_begin, std::vector<part> & pv);	// Функция для разбора входного XML-файла.
void txt_reports_output(const string & filename_begin, const string & output_directory, const std::vector<part> & pv);	// Функция для генерации txt-отчётов.

#endif
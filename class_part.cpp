#include "class_part.h"

using std::ofstream;
using std::endl;


part::part(const string & u, const string & i_id, const string & r_id, const string & tp, const string & nm, const string & dsc) :
	uid(u), item_id(i_id), rev_id(r_id), type(tp), name(nm), desc(dsc) { ; }	// В конструктор передаются атрибуты детали.


bool part::operator<(const part & p2)	// Перегрузка оператора < для сортировки деталей.
{
	if (this->item_id < p2.item_id)		// Детали должны быть отсортированы по атрибуту "Обозначение" (item_id).
		return true;
	else
		return false;
}


// Определение функции разбора входного XML-файла; в первом параметре передаётся путь и имя файла, во втором параметре -
// объект string для хранения первой части имени txt-отчётов (обозначения головного изделия), в третьем параметре - 
// вектор для хранения объектов класса part с информацией о деталях:
void xml_file_read(const QString & xml_source_filename, string & filename_begin, std::vector<part> & pv)
{
	QDomDocument parts_list;	// Создание документа для работы со входным XML-файлом.
	QFile parts_file(xml_source_filename);	// Создание входного потока для XML-файла.
	pv.clear();		// Очистка вектора для хранения деталей.

	if (parts_file.open(QIODevice::ReadOnly)) {		// Открытие входного XML-файла.
		if (parts_list.setContent(&parts_file)) {	// Установка входного XML-файла в качестве содержимого для разбираемого документа.
			QDomElement head_product = parts_list.documentElement();	// Открытие элемента головного изделия.
			filename_begin = head_product.attribute("root_uid").toLocal8Bit().toStdString();	// Извлечение обозначения головного изделия.
			QDomNode record_node = head_product.firstChild();			// Переход к первому узлу (детали) внутри головного изделия.

			// Цикл для прохода по всем узлам (деталям):
			while (!record_node.isNull() && record_node.isElement()) {	// Проверка корректности открытия узла (детали).
				QDomElement record_element = record_node.toElement();	// Преобразование узла в элемент.
				if (!record_element.isNull()) {		// Проверка корректности элемента, извлечение из него атрибутов детали и помещение её в вектор.
					pv.push_back(part(record_element.attribute("uid").toLocal8Bit().toStdString(),
						record_element.attribute("item_id").toLocal8Bit().toStdString(),
						record_element.attribute("rev_id").toLocal8Bit().toStdString(),
						record_element.attribute("type").toLocal8Bit().toStdString(),
						record_element.attribute("name").toLocal8Bit().toStdString(),
						record_element.attribute("desc").toLocal8Bit().toStdString()));
				}
				record_node = record_node.nextSibling();	// Переход к следующей детали.
			}
		}
	}

	parts_file.close();		// Закрытие входного потока XML-файла.
}


// Определение функции создания выходных txt-файлов и помещения в них деталей из отсортированного вектора в соответствии
// с их атрибутами. В первом параметре передаётся начало имён файлов (обозначение головного изделия), во втором - путь к
// каталогу для сохранения txt-отчётов, в третьем - вектор с объектами класса part, содержащими информацию о деталях:
void txt_reports_output(const string & filename_begin, const string & output_directory, const std::vector<part> & pv)
{
	ofstream assembly_parts(output_directory + "/" + filename_begin + " - Сборочные единицы.txt");
	ofstream details_parts(output_directory + "/" + filename_begin + " - Детали.txt");
	ofstream buying_parts(output_directory + "/" + filename_begin + " - Покупные изделия.txt");
	ofstream standard_parts(output_directory + "/" + filename_begin + " - Стандартные изделия.txt");
	ofstream other_parts(output_directory + "/" + filename_begin + " - Прочие изделия.txt");

	assembly_parts << "Обозначение\t" << "Наименование\t" << "Ревизия\n";
	details_parts << "Обозначение\t" << "Наименование\t" << "Ревизия\n";
	buying_parts << "Обозначение\t" << "Наименование\n";
	standard_parts << "Наименование\n";
	other_parts << "Обозначение\t" << "Тип\t" << "Наименование\t" << "Ревизия\t" << "Описание\n";
	
	for (part pt : pv) {
		if (pt.get_type() == "I8_Assy" || pt.get_type() == "sdb_AssyItem" || pt.get_type() == "AS2_assembly")
			assembly_parts << pt.get_item_id() << "\t" << pt.get_name() << "\t" << pt.get_rev_id() << endl;
		else if (pt.get_type() == "I8_Part" || pt.get_type() == "sbd_DetailItem" || pt.get_type() == "AS2_Detail")
			details_parts << pt.get_item_id() << "\t" << pt.get_name() << "\t" << pt.get_rev_id() << endl;
		else if (pt.get_type() == "I8_PKI" || pt.get_type() == "I8_PKI_draft" || pt.get_type() == "sdb_PKI" || pt.get_type() == "AS2_PKI")
			buying_parts << pt.get_item_id() << "\t" << pt.get_name() << endl;
		else if (pt.get_type() == "I8_Sti" || pt.get_type() == "sdb_Fast" || pt.get_type() == "sdb_Standard" || pt.get_type() == "AS2_STI")
			standard_parts << pt.get_name() << endl;
		else
			other_parts << pt.get_item_id() << "\t" << pt.get_type() << "\t" << pt.get_name() << "\t" << pt.get_rev_id() << "\t" << pt.get_desc() << endl;
	}

	assembly_parts.close();
	details_parts.close();
	buying_parts.close();
	standard_parts.close();
	other_parts.close();
}
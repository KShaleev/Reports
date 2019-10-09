#include "class_part.h"

using std::ofstream;
using std::endl;


part::part(const string & u, const string & i_id, const string & r_id, const string & tp, const string & nm, const string & dsc) :
	uid(u), item_id(i_id), rev_id(r_id), type(tp), name(nm), desc(dsc) { ; }	// � ����������� ���������� �������� ������.


bool part::operator<(const part & p2)	// ���������� ��������� < ��� ���������� �������.
{
	if (this->item_id < p2.item_id)		// ������ ������ ���� ������������� �� �������� "�����������" (item_id).
		return true;
	else
		return false;
}


// ����������� ������� ������� �������� XML-�����; � ������ ��������� ��������� ���� � ��� �����, �� ������ ��������� -
// ������ string ��� �������� ������ ����� ����� txt-������� (����������� ��������� �������), � ������� ��������� - 
// ������ ��� �������� �������� ������ part � ����������� � �������:
void xml_file_read(const QString & xml_source_filename, string & filename_begin, std::vector<part> & pv)
{
	QDomDocument parts_list;	// �������� ��������� ��� ������ �� ������� XML-������.
	QFile parts_file(xml_source_filename);	// �������� �������� ������ ��� XML-�����.
	pv.clear();		// ������� ������� ��� �������� �������.

	if (parts_file.open(QIODevice::ReadOnly)) {		// �������� �������� XML-�����.
		if (parts_list.setContent(&parts_file)) {	// ��������� �������� XML-����� � �������� ����������� ��� ������������ ���������.
			QDomElement head_product = parts_list.documentElement();	// �������� �������� ��������� �������.
			filename_begin = head_product.attribute("root_uid").toLocal8Bit().toStdString();	// ���������� ����������� ��������� �������.
			QDomNode record_node = head_product.firstChild();			// ������� � ������� ���� (������) ������ ��������� �������.

			// ���� ��� ������� �� ���� ����� (�������):
			while (!record_node.isNull() && record_node.isElement()) {	// �������� ������������ �������� ���� (������).
				QDomElement record_element = record_node.toElement();	// �������������� ���� � �������.
				if (!record_element.isNull()) {		// �������� ������������ ��������, ���������� �� ���� ��������� ������ � ��������� � � ������.
					pv.push_back(part(record_element.attribute("uid").toLocal8Bit().toStdString(),
						record_element.attribute("item_id").toLocal8Bit().toStdString(),
						record_element.attribute("rev_id").toLocal8Bit().toStdString(),
						record_element.attribute("type").toLocal8Bit().toStdString(),
						record_element.attribute("name").toLocal8Bit().toStdString(),
						record_element.attribute("desc").toLocal8Bit().toStdString()));
				}
				record_node = record_node.nextSibling();	// ������� � ��������� ������.
			}
		}
	}

	parts_file.close();		// �������� �������� ������ XML-�����.
}


// ����������� ������� �������� �������� txt-������ � ��������� � ��� ������� �� ���������������� ������� � ������������
// � �� ����������. � ������ ��������� ��������� ������ ��� ������ (����������� ��������� �������), �� ������ - ���� �
// �������� ��� ���������� txt-�������, � ������� - ������ � ��������� ������ part, ����������� ���������� � �������:
void txt_reports_output(const string & filename_begin, const string & output_directory, const std::vector<part> & pv)
{
	ofstream assembly_parts(output_directory + "/" + filename_begin + " - ��������� �������.txt");
	ofstream details_parts(output_directory + "/" + filename_begin + " - ������.txt");
	ofstream buying_parts(output_directory + "/" + filename_begin + " - �������� �������.txt");
	ofstream standard_parts(output_directory + "/" + filename_begin + " - ����������� �������.txt");
	ofstream other_parts(output_directory + "/" + filename_begin + " - ������ �������.txt");

	assembly_parts << "�����������\t" << "������������\t" << "�������\n";
	details_parts << "�����������\t" << "������������\t" << "�������\n";
	buying_parts << "�����������\t" << "������������\n";
	standard_parts << "������������\n";
	other_parts << "�����������\t" << "���\t" << "������������\t" << "�������\t" << "��������\n";
	
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
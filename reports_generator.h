#ifndef REPORTS_GENERATOR_H_
#define REPORTS_GENERATOR_H_

#include <vector>
#include <string>
#include "class_part.h"		// ����� � ������� ��� ������ � ��������.

class reports_generator {	// ����� ��� ����� ������������ ���������� � ��������� ������ ��������� � ���������������� ��������� txt-�������.
private:
	QString parts_filename;				// ���� � ��� �������� XML-�����.
	QString output_directory;			// ���� � �������� ��� ���������� �������.
	std::string outfilename_begin;		// ������ ����� ��� txt-������ - ����������� ��������� �������.
	std::vector<part> parts_vector;		// ������ ��� �������� � ���������� �������.
public:
	reports_generator(const QString & xml_file, const QString & rep_dir);	// � ������ ��������� ��������� ���� � ��� �������� XML-�����,
																			// �� ������ ��������� - ���� � �������� ��� ���������� �������.
};

#endif

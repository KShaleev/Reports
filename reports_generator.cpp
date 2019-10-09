#include "reports_generator.h"

reports_generator::reports_generator(const QString & xml_file, const QString & rep_dir) :
	parts_filename(xml_file), output_directory(rep_dir)
{
	xml_file_read(parts_filename, outfilename_begin, parts_vector);		// ����� ������� ��� ������� �������� XML-�����, ���������� ������ ����� ��� txt-������
																		// (����������� ��������� �������) � ��������� ������� � ������.
	sort(parts_vector.begin(), parts_vector.end());		// ���������� �������.
	txt_reports_output(outfilename_begin, output_directory.toLocal8Bit().toStdString(), parts_vector);	//��������� txt-������ �� ������ ���������������� �������.
}
#ifndef REPORT_GUI_H_
#define REPORT_GUI_H_

#include <QtWidgets>
#include "reports_generator.h"	// ����� ��� ����� ������������ ���������� � ��������� ������ ��������� � ���������������� ��������� txt-�������.

class report_GUI : public QWidget	// ����� ������������ ����������������� ����������.
{
	Q_OBJECT

private:
	QString xml_filename;			// �������� ���� � ��� �������� XML-�����.
	QString reports_directory;		// �������� ���� � �������� ��� ���������� txt-�������.
	reports_generator * rpgen;		// ������ ������ ��� ���������������� ��������� �������.

	QPushButton * browse_xml_file;				// ������ �������� ������� ������ �������� XML-�����.
	QPushButton * browse_reports_directory;		// ������ �������� ������� ������ �������� ��� ���������� txt-�������.
	QPushButton * generate_reports;				// ������ "������������� �����".

	QLineEdit * xml_file_path;				// ������ �������������� ���� � ����� �������� XML-�����.
	QLineEdit * reports_directory_path;		// ������ �������������� ���� � �������� ��� ���������� txt-�������.

	QStatusBar * status;		// Status bar ��� ������ ��������� �� ��������� ��������� ������.

	// ��������� ����������:
	QHBoxLayout * browse_xml_file_layout;			// ��������� ������ � ������ ��� �������� �����.
	QHBoxLayout * browse_reports_directory_layout;	// ��������� ������ � ������ ��� ���� ���������� �������.
	QVBoxLayout * main_layout;						// ����� ������������.

public:
	report_GUI(QWidget * parent = nullptr);
	
signals:
	void xml_filename_changed(const QString &);				// ������� ���� � ��� �������� XML-����� ��� ��� ��������� �� ������.
	void reports_save_directory_changed(const QString &);	// ������� ���� � �������� ��� ���������� txt-������� ��� ��� ��������� �� ������.

private slots:
	void browse_xml_file_clicked();				// ������� �� ������ "���� � �����".
	void browse_reports_directory_clicked();	// ������� �� ������ "������� ��� �������".
	void generate_reports_clicked();			// ������� �� ������ "������������� �����".
	void xml_file_change(const QString &);		// ��������� xml_filename � ���������� ������ "������������� �����" ��� ������� ���� � reports_directory.
	void reports_dir_change(const QString &);	// ��������� reports_directory � ���������� ������ "������������� �����" ��� ������� ���� � xml_filename.
};

#endif
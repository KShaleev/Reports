/*
		��������� ��������� �� ������ �������� ����� ����� "������� ������������".
		����� ������������ �� ���� �������� �������, �������� �� �������:
	- ��������� �������;
	- ������;
	- �������� �������;
	- ����������� �������;
	- ������ �������.
		������� ���� �������� ������ �� ��������, ������������ � ��������� ��������� �������, � ���� ������ ������� � ������� XML � ���������� Windows-1251.
		������ ����������� ������� ����� ������������� ����� ���������.
		��������� �������� �����:
	<parts_list ...>
		<part .../>
		<part .../>
		...
		<part .../>
	</parts_list>
		"parts_list" - ������������ ������� ������� �������. �������� ������������ ������� "root_uid" - ���������� ������������� ��������� ������� � ���������.
		"part" - �������, ����������� �������.
		��������:
	uid - ���������� ���������� ������������� �������;
	item_id - �����������;
	rev_id - �������;
	type - ��� �������;
	name - ������������;
	desc - ��������.
		����� ����������� � ���� ���������� ������ ������� txt, ��������������� ��������. ������ � ����� ������������ �� ���� ��������� ������� �� ������ ���������
	� �������� �����������. ��� ������� �� ������ ��� ������������� �������: <����������� ��������� �������> - <��� �������>.txt. �������� ������� � ������ �������
	������������ �� �������� "�����������", ���� ���� ���� ������� �� ���������.
		������ "��������� �������": ����������� | ������������ | �������. � ������ �������� ������ ������� ����� �I8_Assy�, �sdb_AssyItem�, �AS2_assembly�.
		������ "������": ����������� | ������������ | �������. � ������ �������� ������ ������� ����� �I8_Part�, �sbd_DetailItem�, �AS2_Detail�.
		������ "�������� �������": ����������� | ������������. � ������ �������� ������ ������� ����� �I8_PKI�, �I8_PKI_draft�, �sdb_PKI�, �AS2_PKI�.
		������ "����������� �������": �����������. � ������ �������� ������ ������� ����� �I8_Sti�, �sdb_Fast�, �sdb_Standard�, �AS2_STI�.
		������ "������ �������": ����������� | ��� | ������������ | ������� | ��������. � ������ �������� ������ ���� ������ ����� �������, �� ���������� ����.

		� ������ report_gui.h � report_gui.cpp �������� ����� report_GUI, ���������� ����������� ��������� ���������.
		� ������ class_part.h � class_part.cpp �������� ����� part, ���������� �������� ������, ������ ��� ������ � ���, � ����� ������� ��� ������� �������� XML-�����
	� ������� ��� �������� ������� � ������� txt.
		� ������ reports_generator.h � reports_generator.cpp �������� ����� reports_generator, �������� ��� ����� ������������ ����������������� ���������� � ���������
	������ ��������� � ��������������� ������������ ������ �� ������ �������� �����.
		� ����� resources.qrc ���������� ������� ��������.
*/


#include <QApplication>
#include "report_gui.h"		// ����� ������������ ����������.

int main(int argc, char * argv[])
{
	QApplication report(argc, argv);

	report_GUI * rg = new report_GUI;
	rg->setWindowIcon(QIcon(":/new/prefix1/Irkut_logo"));			// ������� ��������.
	rg->setWindowTitle(QString::fromLocal8Bit("��������� �������"));
	rg->resize(300, 100);
	rg->show();

	return report.exec();
}
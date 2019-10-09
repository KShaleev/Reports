#include "report_gui.h"

report_GUI::report_GUI(QWidget * parent)
	: QWidget(parent)
{
	// �������� �������� ���� ���������� � ���������� ����������:
	browse_xml_file = new QPushButton(QString::fromLocal8Bit("���� � &�����"));
	browse_reports_directory = new QPushButton(QString::fromLocal8Bit("&������� ��� �������"));
	generate_reports = new QPushButton(QString::fromLocal8Bit("�&������������ �����"));
	generate_reports->setEnabled(false);

	xml_file_path = new QLineEdit;
	reports_directory_path = new QLineEdit;

	status = new QStatusBar;
	
	browse_xml_file_layout = new QHBoxLayout;
	browse_reports_directory_layout = new QHBoxLayout;
	main_layout = new QVBoxLayout;

	// ���������� �������� � ������:
	// ������� �� ������:
	connect(browse_xml_file, SIGNAL(clicked()), this, SLOT(browse_xml_file_clicked()));
	connect(browse_reports_directory, SIGNAL(clicked()), this, SLOT(browse_reports_directory_clicked()));
	connect(generate_reports, SIGNAL(clicked()), this, SLOT(generate_reports_clicked()));
	// emit-�������:
	connect(this, SIGNAL(xml_filename_changed(const QString &)), xml_file_path, SLOT(setText(const QString &)));
	connect(this, SIGNAL(xml_filename_changed(const QString &)), this, SLOT(xml_file_change(const QString &)));
	connect(this, SIGNAL(reports_save_directory_changed(const QString &)), reports_directory_path, SLOT(setText(const QString &)));
	connect(this, SIGNAL(reports_save_directory_changed(const QString &)), this, SLOT(reports_dir_change(const QString &)));
	// ������� �� ����� �������������� �����:
	connect(xml_file_path, SIGNAL(textChanged(const QString &)), this, SLOT(xml_file_change(const QString &)));
	connect(reports_directory_path, SIGNAL(textChanged(const QString &)), this, SLOT(reports_dir_change(const QString &)));

	// ���������� �������� ���� ����������:
	browse_xml_file_layout->addWidget(browse_xml_file);
	browse_xml_file_layout->addWidget(xml_file_path);
	browse_reports_directory_layout->addWidget(browse_reports_directory);
	browse_reports_directory_layout->addWidget(reports_directory_path);
	main_layout->addLayout(browse_xml_file_layout);
	main_layout->addLayout(browse_reports_directory_layout);
	main_layout->addWidget(generate_reports);
	main_layout->addWidget(status);

	setLayout(main_layout);
}

void report_GUI::browse_xml_file_clicked()				// ������� �� ������ "���� � �����".
{
	QString xml_file_name = QFileDialog::getOpenFileName(nullptr, "Select XML file with parts", "", "*.xml");
	emit xml_filename_changed(xml_file_name);
}

void report_GUI::browse_reports_directory_clicked()		// ������� �� ������ "������� ��� �������".
{
	QString reports_save_directory = QFileDialog::getExistingDirectory(nullptr, "Select directory to save text reports");
	emit reports_save_directory_changed(reports_save_directory);
}

void report_GUI::generate_reports_clicked()				// ������� �� ������ "������������� �����".
{
	rpgen = new reports_generator(xml_filename,	reports_directory);
	delete rpgen;
	status->showMessage(QString::fromLocal8Bit("����� ������������."));
}

void report_GUI::xml_file_change(const QString & filename)		// ��������� xml_filename.
{
	xml_filename = filename;
	if (!reports_directory.isEmpty()) this->generate_reports->setEnabled(true);		// ��������� ������ "������������� �����".
}

void report_GUI::reports_dir_change(const QString & directory)	// ��������� reports_directory.
{
	reports_directory = directory;
	if (!xml_filename.isEmpty()) this->generate_reports->setEnabled(true);			// ��������� ������ "������������� �����".
}
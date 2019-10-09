#include "report_gui.h"

report_GUI::report_GUI(QWidget * parent)
	: QWidget(parent)
{
	// Создание виджетов окна приложения и менеджеров компоновки:
	browse_xml_file = new QPushButton(QString::fromLocal8Bit("Путь к &файлу"));
	browse_reports_directory = new QPushButton(QString::fromLocal8Bit("&Каталог для отчётов"));
	generate_reports = new QPushButton(QString::fromLocal8Bit("С&генерировать отчёт"));
	generate_reports->setEnabled(false);

	xml_file_path = new QLineEdit;
	reports_directory_path = new QLineEdit;

	status = new QStatusBar;
	
	browse_xml_file_layout = new QHBoxLayout;
	browse_reports_directory_layout = new QHBoxLayout;
	main_layout = new QVBoxLayout;

	// Соединения сигналов и слотов:
	// сигналы от кнопок:
	connect(browse_xml_file, SIGNAL(clicked()), this, SLOT(browse_xml_file_clicked()));
	connect(browse_reports_directory, SIGNAL(clicked()), this, SLOT(browse_reports_directory_clicked()));
	connect(generate_reports, SIGNAL(clicked()), this, SLOT(generate_reports_clicked()));
	// emit-сигналы:
	connect(this, SIGNAL(xml_filename_changed(const QString &)), xml_file_path, SLOT(setText(const QString &)));
	connect(this, SIGNAL(xml_filename_changed(const QString &)), this, SLOT(xml_file_change(const QString &)));
	connect(this, SIGNAL(reports_save_directory_changed(const QString &)), reports_directory_path, SLOT(setText(const QString &)));
	connect(this, SIGNAL(reports_save_directory_changed(const QString &)), this, SLOT(reports_dir_change(const QString &)));
	// сигналы от строк редактирования путей:
	connect(xml_file_path, SIGNAL(textChanged(const QString &)), this, SLOT(xml_file_change(const QString &)));
	connect(reports_directory_path, SIGNAL(textChanged(const QString &)), this, SLOT(reports_dir_change(const QString &)));

	// Компоновка виджетов окна приложения:
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

void report_GUI::browse_xml_file_clicked()				// Нажатие на кнопку "Путь к файлу".
{
	QString xml_file_name = QFileDialog::getOpenFileName(nullptr, "Select XML file with parts", "", "*.xml");
	emit xml_filename_changed(xml_file_name);
}

void report_GUI::browse_reports_directory_clicked()		// Нажатие на кнопку "Каталог для отчётов".
{
	QString reports_save_directory = QFileDialog::getExistingDirectory(nullptr, "Select directory to save text reports");
	emit reports_save_directory_changed(reports_save_directory);
}

void report_GUI::generate_reports_clicked()				// Нажатие на кнопку "Сгенерировать отчёт".
{
	rpgen = new reports_generator(xml_filename,	reports_directory);
	delete rpgen;
	status->showMessage(QString::fromLocal8Bit("Отчёт сгенерирован."));
}

void report_GUI::xml_file_change(const QString & filename)		// Обновляет xml_filename.
{
	xml_filename = filename;
	if (!reports_directory.isEmpty()) this->generate_reports->setEnabled(true);		// Активация кнопки "Сгенерировать отчёт".
}

void report_GUI::reports_dir_change(const QString & directory)	// Обновляет reports_directory.
{
	reports_directory = directory;
	if (!xml_filename.isEmpty()) this->generate_reports->setEnabled(true);			// Активация кнопки "Сгенерировать отчёт".
}
#ifndef REPORT_GUI_H_
#define REPORT_GUI_H_

#include <QtWidgets>
#include "reports_generator.h"	// Класс для связи графического интерфейса с остальной частью программы и непосредственной генерации txt-отчётов.

class report_GUI : public QWidget	// Класс графического пользовательского интерфейса.
{
	Q_OBJECT

private:
	QString xml_filename;			// Содержит путь и имя входного XML-файла.
	QString reports_directory;		// Содержит путь к каталогу для сохранения txt-отчётов.
	reports_generator * rpgen;		// Объект класса для непосредственной генерации отчётов.

	QPushButton * browse_xml_file;				// Кнопка открытия диалога выбора входного XML-файла.
	QPushButton * browse_reports_directory;		// Кнопка открытия диалога выбора каталога для сохранения txt-отчётов.
	QPushButton * generate_reports;				// Кнопка "Сгенерировать отчёт".

	QLineEdit * xml_file_path;				// Строка редактирования пути и имени входного XML-файла.
	QLineEdit * reports_directory_path;		// Строка редактирования пути к каталогу для сохранения txt-отчётов.

	QStatusBar * status;		// Status bar для вывода сообщения об окончании генерации отчёта.

	// Менеджеры компоновки:
	QHBoxLayout * browse_xml_file_layout;			// Связывает кнопку и строку для входного файла.
	QHBoxLayout * browse_reports_directory_layout;	// Связывает кнопку и строку для пути сохранения отчётов.
	QVBoxLayout * main_layout;						// Общее расположение.

public:
	report_GUI(QWidget * parent = nullptr);
	
signals:
	void xml_filename_changed(const QString &);				// Передаёт путь и имя входного XML-файла при его изменении по кнопке.
	void reports_save_directory_changed(const QString &);	// Передаёт путь к каталогу для сохранения txt-отчётов при его изменении по кнопке.

private slots:
	void browse_xml_file_clicked();				// Нажатие на кнопку "Путь к файлу".
	void browse_reports_directory_clicked();	// Нажатие на кнопку "Каталог для отчётов".
	void generate_reports_clicked();			// Нажатие на кнопку "Сгенерировать отчёт".
	void xml_file_change(const QString &);		// Обновляет xml_filename и активирует кнопку "Сгенерировать отчёт" при наличии пути в reports_directory.
	void reports_dir_change(const QString &);	// Обновляет reports_directory и активирует кнопку "Сгенерировать отчёт" при наличии пути в xml_filename.
};

#endif
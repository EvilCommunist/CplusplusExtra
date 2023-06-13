#include "pch.h"
#include "MyForm.h"
#include "Struct.h"
#include <algorithm>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

String^ initDay() // Инициализация сего дня
{
	DateTime^ x2 = DateTime::Now;
    return x2->DayOfWeek.ToString();
}

bool isDayofWeek(String^ data) // Проверка строки на принадлежность к значению дня недели
{
	if (data=="Monday"|| data == "Tuesday" || data == "Wednesday" || data == "Thursday" || data == "Friday" || data == "Выходные")
	{ 
		return 1;
	}
	else
	{
		return 0;
	}
}

FileManager^ getTokens(String^ line) // Разбитие прочитанной строки по токенам (номер пары, неделя пары и т.д.)
{
	FileManager^ fm = gcnew FileManager;
	if (isDayofWeek(line))
	{
		fm->chooseweek = line;
		fm->numlesson = "0";
		fm->typelesson = "0";
		fm->namelesson = "0";
		fm->lessplace = "0";
	}
	else
	{
	int i = 0;
	do
	{
		fm->chooseweek += line[i];
		i ++;
	} while (line[i] != ' ');
	do
	{
		fm->numlesson += line[i];
		i++;
	} while (line[i] != ' ');
	do
	{
		fm->typelesson += line[i];
		i++;
	} while (line[i] != ' ');
	do
	{
		fm->namelesson += line[i];
		i++;
	} while (line[i] != ',');
	i++;
	do
	{
		fm->lessplace += line[i];
		i++;
	} while (i< line->Length);
	}
	return fm;
}

List<FileManager^>^ readdocument() // Считывание данных с документа ("базы данных")
{
	String^ path = "C:\\Users\\AT241\\source\\repos\\TimeTableRSREU_KURSACH\\Raspis.txt";
	System::IO::StreamReader^ reader = gcnew System::IO::StreamReader(path);
	String^ line;

	List<FileManager^>^ oneline = gcnew List<FileManager^>(); // Список ячеек

	while ((line = reader->ReadLine()) != nullptr)
	{
			FileManager^ cell = getTokens(line); // Структурный элемент: ячейка расписания
			oneline->Add(cell);
	}

	reader->Close();
	return oneline;
}

String^ findDay(List<FileManager^>^ fm,int padd) // padd - "смещение" дня, поиск указанного дня в списке
{
	List<String^> Days;
	DateTime^ dt = DateTime::Now;
	if ((dt->DayOfWeek.ToString() == "Saturday" || dt->DayOfWeek.ToString() == "Sunday")&&(padd==0)||((dt->DayOfWeek.ToString() == "Saturday") && (padd == 1)))
	{
		return "Weekend"; // Обработка поведения расписания на выходных
	}
	for (int i=0; i<fm->Count; i++)
	{
		if (isDayofWeek(fm[i]->chooseweek))
		{
			Days.Add(fm[i]->chooseweek);
		}
	}
	String^ day;
	for (int i = 0; i < Days.Count; i++)
	{
		if (dt->DayOfWeek.ToString() == Days[i])
		{
			if (i + padd <= 5) {
				day = Days[i + padd];
			}
			else return "Weekend";
		}
		if (dt->DayOfWeek.ToString() == "Saturday" || dt->DayOfWeek.ToString() == "Sunday")
		{
			if(dt->DayOfWeek.ToString() == "Saturday" && padd>1)
				day = Days[padd-1];
			if (dt->DayOfWeek.ToString() == "Sunday" && padd > 0)
				day = Days[padd-1];
		}
	}
	return day;
}

int countLessons(List<FileManager^>^ fm, int padd) // Подсчёт количества пар
{
	int start;
	for (int i = 0; i < fm->Count-1; i++)
	{
		if (fm[i]->chooseweek == findDay(fm, padd)) 
		{
			i++;
			start = i;
			for (int j = 0; j < fm->Count; j++)
			{
				if (fm[j]->chooseweek == findDay(fm, padd + 1))
				{
					int start1;
					start1 = j - start;
					return start1 - 1;
				}
				i++;
			}
		}
	}
}

int seekDay(List<FileManager^>^ fm, String^ day) // Определение номера нужного дня в списке
{
	int seek = 0;
	for (int i = 0; i < fm->Count; i++)
	{
		if (fm[i]->chooseweek == day)
		{
			seek = i;
			return seek;
		}
	}
}

String^ printDayWeek(String^ day) // Определения дня недели на русском
{
	char d = day[0];
	if (day == "Thursday") {
		d = 'H';
	}
	switch (d)
	{
	case 'M': return "Понедельник";
	case 'T': return "Вторник";
	case 'W': return "Среда";
	case 'H': return "Четверг";
	case 'F': return "Пятница";
	}
}

int countLessonsType(List<FileManager^>^ fm, String^ lesson, String^ week) // Подсчёт количества пар запрошенного типа на указанной неделе
{
	if (!(week == "Числитель" || week == "Знаменатель")) {
		return 0;
	}
	int cntch = 0, cntzn=0;
	for (int i = 0; i < fm->Count; i++)
	{
		if (fm[i]->typelesson == lesson) 
		{
			if((week == "Числитель")&&(fm[i]->chooseweek->ToString() == "(числитель)" || fm[i]->chooseweek->ToString() == "(еженедельно)"))
				cntch++;
			if ((week == "Знаменатель") && (fm[i]->chooseweek->ToString() == "(знаменатель)" || fm[i]->chooseweek->ToString() == "(еженедельно)"))
				cntzn++;
		}
	}
	if ((week == "Числитель"))
		return cntch;
	if ((week == "Знаменатель"))
		return cntzn;
}

[STAThread]
int main()
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	TimeTableRSREUKURSACH::MyForm form;
	Application::Run(% form);
}

System::Void TimeTableRSREUKURSACH::MyForm::TodayTt_Click(System::Object^ sender, System::EventArgs^ e) // Кнопка вывода расписания на сегодня
{
	dailyTimetable->Rows->Clear();
	List<FileManager^>^ fm = readdocument();
	if ((CheckZnam->Checked == true)||(CheckChisl->Checked == true)) {
		for (int i = 0; i < countLessons(fm, 0); i++)
			dailyTimetable->Rows->Add(); // Добавление столбцов
	}
	else
	{
		MessageBox::Show("Выберите неделю: числитель либо знаменатель!", "Внимание!"); // Обработка исключения: не выбрана неделя обучения
	}
	if (findDay(fm, 0) == "Weekend")
	{
		dailyTimetable->Rows[0]->Cells[2]->Value = "Weekend"; // Обработка исключения выходного дня
		return System::Void();
	}
	int startpoint = seekDay(fm, findDay(fm, 0));
	for (int i = startpoint; i<fm->Count; i++)
	{
		if (!((CheckZnam->Checked == true) || (CheckChisl->Checked == true))) {
			
			break; // Обработка исключения: не выбрана неделя обучения
		}
		if (fm[i]->chooseweek == findDay(fm,0))
		{
			dailyTimetable->Rows[0]->Cells[4]->Value = printDayWeek(fm[i]->chooseweek); // Вывод дня недели в таблицу
			i++;
		}
		int j = 0;
		while(!(fm[j]->chooseweek == findDay(fm, 1))) // Считывание в таблицу пар указанного типа недели
		{
			if (CheckChisl->Checked == true)
			{
				if (fm[i]->chooseweek->ToString() == "(числитель)" || fm[i]->chooseweek->ToString() == "(еженедельно)")
				{
					dailyTimetable->Rows[j]->Cells[0]->Value = fm[i]->numlesson;
					dailyTimetable->Rows[j]->Cells[1]->Value = fm[i]->typelesson;
					dailyTimetable->Rows[j]->Cells[2]->Value = fm[i]->namelesson;
					dailyTimetable->Rows[j]->Cells[3]->Value = fm[i]->lessplace;
					j++;
				}
				if (fm[i]->chooseweek == findDay(fm, 1))
				{
					break;
				}
			}
			if (CheckZnam->Checked == true)
			{
				if (fm[i]->chooseweek->ToString() == "(знаменатель)" || fm[i]->chooseweek->ToString() == "(еженедельно)")
				{
					dailyTimetable->Rows[j]->Cells[0]->Value = fm[i]->numlesson;
					dailyTimetable->Rows[j]->Cells[1]->Value = fm[i]->typelesson;
					dailyTimetable->Rows[j]->Cells[2]->Value = fm[i]->namelesson;
					dailyTimetable->Rows[j]->Cells[3]->Value = fm[i]->lessplace;
					j++;
				}
				if (fm[i]->chooseweek == findDay(fm, 1))
				{
					break;
				}
			}
			i++;
		}
		if (fm[i]->chooseweek == findDay(fm, 1))
			break;
	}
	return System::Void();
}

System::Void TimeTableRSREUKURSACH::MyForm::TomorrowTt_Click(System::Object^ sender, System::EventArgs^ e) // Кнопка вывода расписания на завтра
{
	dailyTimetable->Rows->Clear();
	List<FileManager^>^ fm = readdocument();
	if ((CheckZnam->Checked == true) || (CheckChisl->Checked == true)) {
		for (int i = 0; i < countLessons(fm,1); i++)
			dailyTimetable->Rows->Add(); // Добавление столбцов
	}
	else
	{
		MessageBox::Show("Введите неделю: числитель либо знаменатель!", "Внимание!"); // Обработка исключения: не выбрана неделя обучения
	}
	if (findDay(fm, 1) == "Weekend" || findDay(fm, 1) == "Выходные")
	{
		dailyTimetable->Rows[0]->Cells[2]->Value = "Weekend";
		return System::Void();
	}
	int startpoint = seekDay(fm, findDay(fm, 1));
	for (int i = startpoint; i < fm->Count-1; i++)
	{
		if (!((CheckZnam->Checked == true) || (CheckChisl->Checked == true))) {

			break; // Обработка исключения: не выбрана неделя обучения
		}
		if (fm[i]->chooseweek == findDay(fm, 1))
		{
			dailyTimetable->Rows[0]->Cells[4]->Value = printDayWeek(fm[i]->chooseweek);
			i++;
		}
		int j = 0;
		while (!(fm[j]->chooseweek == findDay(fm, 2))) // Вывод в таблицу пар указанной недели
		{
			if (CheckChisl->Checked == true)
			{
				if (fm[i]->chooseweek->ToString() == "(числитель)" || fm[i]->chooseweek->ToString() == "(еженедельно)")
				{
					dailyTimetable->Rows[j]->Cells[0]->Value = fm[i]->numlesson;
					dailyTimetable->Rows[j]->Cells[1]->Value = fm[i]->typelesson;
					dailyTimetable->Rows[j]->Cells[2]->Value = fm[i]->namelesson;
					dailyTimetable->Rows[j]->Cells[3]->Value = fm[i]->lessplace;
					j++;
				}
				if (fm[i]->chooseweek == findDay(fm, 2))
				{
					break;
				}
			}
			if (CheckZnam->Checked == true)
			{
				if (fm[i]->chooseweek->ToString() == "(знаменатель)" || fm[i]->chooseweek->ToString() == "(еженедельно)")
				{
					dailyTimetable->Rows[j]->Cells[0]->Value = fm[i]->numlesson;
					dailyTimetable->Rows[j]->Cells[1]->Value = fm[i]->typelesson;
					dailyTimetable->Rows[j]->Cells[2]->Value = fm[i]->namelesson;
					dailyTimetable->Rows[j]->Cells[3]->Value = fm[i]->lessplace;
					j++;
				}
				if (fm[i]->chooseweek == findDay(fm, 2))
				{
					break;
				}
			}
			i++;
		}
		if (fm[i]->chooseweek == findDay(fm, 2))
			break;
	}
	return System::Void();
}

System::Void TimeTableRSREUKURSACH::MyForm::PostTomorrowTt_Click(System::Object^ sender, System::EventArgs^ e) // Кнопка вывода рсаписания на послезавтра
{
	dailyTimetable->Rows->Clear();
	List<FileManager^>^ fm = readdocument();
	if ((CheckZnam->Checked == true) || (CheckChisl->Checked == true)) {
		for (int i = 0; i < countLessons(fm,2); i++)
			dailyTimetable->Rows->Add(); // Добавление столбцов
	}
	else
	{
		MessageBox::Show("Введите неделю: числитель либо знаменатель!", "Внимание!"); // Обработка исключения: не выбрана неделя
	}
	if (findDay(fm, 2) == "Weekend" || findDay(fm, 2) == "Выходные")
	{
		dailyTimetable->Rows[0]->Cells[2]->Value = "Weekend";
		return System::Void();
	}
	int startpoint = seekDay(fm, findDay(fm, 2));
	for (int i = startpoint; i < fm->Count; i++)
	{
		if (!((CheckZnam->Checked == true) || (CheckChisl->Checked == true))) {
			break; // Обработка исключения: не выбрана неделя
		}
		if (fm[i]->chooseweek == findDay(fm, 2))
		{
			dailyTimetable->Rows[0]->Cells[4]->Value = printDayWeek(fm[i]->chooseweek);
			i++;
		}
		int j = 0;
		while (!(fm[j]->chooseweek == findDay(fm, 3))) // Вывод в таблицу пар указанной недели
		{
			if (CheckChisl->Checked == true)
			{
				if (fm[i]->chooseweek->ToString() == "(числитель)" || fm[i]->chooseweek->ToString() == "(еженедельно)")
				{
					dailyTimetable->Rows[j]->Cells[0]->Value = fm[i]->numlesson;
					dailyTimetable->Rows[j]->Cells[1]->Value = fm[i]->typelesson;
					dailyTimetable->Rows[j]->Cells[2]->Value = fm[i]->namelesson;
					dailyTimetable->Rows[j]->Cells[3]->Value = fm[i]->lessplace;
					j++;
				}
				if (fm[i]->chooseweek == findDay(fm, 3))
				{
					break;
				}
			}
			if (CheckZnam->Checked == true)
			{
				if (fm[i]->chooseweek->ToString() == "(знаменатель)" || fm[i]->chooseweek->ToString() == "(еженедельно)")
				{
					dailyTimetable->Rows[j]->Cells[0]->Value = fm[i]->numlesson;
					dailyTimetable->Rows[j]->Cells[1]->Value = fm[i]->typelesson;
					dailyTimetable->Rows[j]->Cells[2]->Value = fm[i]->namelesson;
					dailyTimetable->Rows[j]->Cells[3]->Value = fm[i]->lessplace;
					j++;
				}
				if (fm[i]->chooseweek == findDay(fm, 3))
				{
					break;
				}
			}
			i++;
		}
		if (fm[i]->chooseweek == findDay(fm, 3))
			break;
	}
	return System::Void();
}

System::Void TimeTableRSREUKURSACH::MyForm::ThisWeekTt_Click(System::Object^ sender, System::EventArgs^ e) // Вывод расписания не эту неделю
{
	dailyTimetable->Rows->Clear();
	List<FileManager^>^ fm = readdocument();

	for (int i = 0; i < 18; i++)
		dailyTimetable->Rows->Add();
	int j = 0;
	for (int i = 0; i < fm->Count-1; i++)
	{
		if (!((CheckZnam->Checked == true) || (CheckChisl->Checked == true))) {
			MessageBox::Show("Введите неделю: числитель либо знаменатель!", "Внимание!"); // Обработка исключения: не выбрана неделя
			break;
		}
		if (isDayofWeek(fm[i]->chooseweek))
		{
			dailyTimetable->Rows[j]->Cells[4]->Value = printDayWeek(fm[i]->chooseweek); // Вывод дня недели
			i++;
		}
		if (CheckZnam->Checked == true)
		{
			if (fm[i]->chooseweek->ToString() == "(знаменатель)" || fm[i]->chooseweek->ToString() == "(еженедельно)")
			{
				dailyTimetable->Rows[j]->Cells[0]->Value = fm[i]->numlesson;
				dailyTimetable->Rows[j]->Cells[1]->Value = fm[i]->typelesson;
				dailyTimetable->Rows[j]->Cells[2]->Value = fm[i]->namelesson;
				dailyTimetable->Rows[j]->Cells[3]->Value = fm[i]->lessplace;
				j++;
			}
		}
		if (CheckChisl->Checked == true)
		{
			if (fm[i]->chooseweek->ToString() == "(числитель)" || fm[i]->chooseweek->ToString() == "(еженедельно)")
			{
				dailyTimetable->Rows[j]->Cells[0]->Value = fm[i]->numlesson;
				dailyTimetable->Rows[j]->Cells[1]->Value = fm[i]->typelesson;
				dailyTimetable->Rows[j]->Cells[2]->Value = fm[i]->namelesson;
				dailyTimetable->Rows[j]->Cells[3]->Value = fm[i]->lessplace;
				j++;
			}
		}
	}
	return System::Void();
}

System::Void TimeTableRSREUKURSACH::MyForm::NextWeekTt_Click(System::Object^ sender, System::EventArgs^ e) // Вывод расписания следующей недели (аналогично предыдущей кнопке, другие коэффициенты)
{
	dailyTimetable->Rows->Clear();
	List<FileManager^>^ fm = readdocument();

	for (int i = 0; i < 18; i++)
		dailyTimetable->Rows->Add();
	int j = 0;
	for (int i = 0; i < fm->Count-1; i++)
	{
		if (!((CheckZnam->Checked == true) || (CheckChisl->Checked == true))) {
			MessageBox::Show("Введите неделю: числитель либо знаменатель!", "Внимание!");
			break;
		}
		if (isDayofWeek(fm[i]->chooseweek))
		{
			dailyTimetable->Rows[j]->Cells[4]->Value = printDayWeek(fm[i]->chooseweek);
			i++;
		}
		if (CheckZnam->Checked == true)
		{
			if (fm[i]->chooseweek->ToString() == "(числитель)" || fm[i]->chooseweek->ToString() == "(еженедельно)")
			{
				dailyTimetable->Rows[j]->Cells[0]->Value = fm[i]->numlesson;
				dailyTimetable->Rows[j]->Cells[1]->Value = fm[i]->typelesson;
				dailyTimetable->Rows[j]->Cells[2]->Value = fm[i]->namelesson;
				dailyTimetable->Rows[j]->Cells[3]->Value = fm[i]->lessplace;
				j++;
			}
		}
		if (CheckChisl->Checked == true)
		{
			if (fm[i]->chooseweek->ToString() == "(знаменатель)" || fm[i]->chooseweek->ToString() == "(еженедельно)")
			{
				dailyTimetable->Rows[j]->Cells[0]->Value = fm[i]->numlesson;
				dailyTimetable->Rows[j]->Cells[1]->Value = fm[i]->typelesson;
				dailyTimetable->Rows[j]->Cells[2]->Value = fm[i]->namelesson;
				dailyTimetable->Rows[j]->Cells[3]->Value = fm[i]->lessplace;
				j++;
			}
		}
	}
	return System::Void();
}

System::Void TimeTableRSREUKURSACH::MyForm::EVMTt_Click(System::Object^ sender, System::EventArgs^ e) // Вывод пар в ауд. каф. ЭВМ на этой неделе
{
	dailyTimetable->Rows->Clear();
	List<FileManager^>^ fm = readdocument();

	for (int i = 0; i < 6; i++)
		dailyTimetable->Rows->Add();
	int j = 0; String^ day;
	for (int i = 0; i < fm->Count-1; i++)
	{
		if (!((CheckZnam->Checked == true) || (CheckChisl->Checked == true))) {
			MessageBox::Show("Введите неделю: числитель либо знаменатель!", "Внимание!");
			break;
		}
		if (isDayofWeek(fm[i]->chooseweek))
		{
			day = fm[i]->chooseweek;
			i++;
		}
		if(fm[i]->lessplace==" а. 209" || fm[i]->lessplace == " а. 210" || fm[i]->lessplace == " а. 122" || fm[i]->lessplace == "   а. 02/1" || fm[i]->lessplace == "   а. 02/2" || fm[i]->lessplace == "   а. 32")
		{	
			if (CheckZnam->Checked == true)
		{
			if (fm[i]->chooseweek->ToString() == "(числитель)" || fm[i]->chooseweek->ToString() == "(еженедельно)")
			{
				dailyTimetable->Rows[j]->Cells[4]->Value = printDayWeek(day);
				dailyTimetable->Rows[j]->Cells[0]->Value = fm[i]->numlesson;
				dailyTimetable->Rows[j]->Cells[1]->Value = fm[i]->typelesson;
				dailyTimetable->Rows[j]->Cells[2]->Value = fm[i]->namelesson;
				dailyTimetable->Rows[j]->Cells[3]->Value = fm[i]->lessplace;
				j++;
			}
		}
		if (CheckChisl->Checked == true)
		{
			if (fm[i]->chooseweek->ToString() == "(знаменатель)" || fm[i]->chooseweek->ToString() == "(еженедельно)")
			{
				dailyTimetable->Rows[j]->Cells[4]->Value = printDayWeek(day);
				dailyTimetable->Rows[j]->Cells[0]->Value = fm[i]->numlesson;
				dailyTimetable->Rows[j]->Cells[1]->Value = fm[i]->typelesson;
				dailyTimetable->Rows[j]->Cells[2]->Value = fm[i]->namelesson;
				dailyTimetable->Rows[j]->Cells[3]->Value = fm[i]->lessplace;
				j++;
			}
		}
		}
	}
	return System::Void();
}

System::Void TimeTableRSREUKURSACH::MyForm::Diagramma_Click(System::Object^ sender, System::EventArgs^ e) // Диаграмма соотношения типа пар на выбранную неделю
{
	if (!((CheckZnam->Checked == true) || (CheckChisl->Checked == true))) {
		MessageBox::Show("Введите неделю: числитель либо знаменатель!", "Внимание!");
		return System::Void();
	}
	List<FileManager^>^ fm = readdocument();
	String^ week;
	if (CheckChisl->Checked == true)
		week = CheckChisl->Text;
	if (CheckZnam->Checked == true)
		week = CheckZnam->Text;
	Diagram->Visible = true;
	Diagram->Series[0]->Points->Clear();
	Diagram->Series[0]->Points->AddXY("упр.", countLessonsType(fm, " упр.", week));
	Diagram->Series[0]->Points->AddXY("лек.", countLessonsType(fm, " лек.", week));
	Diagram->Series[0]->Points->AddXY("лаб.",countLessonsType(fm, " лаб.", week));
	return System::Void();
}

System::Void TimeTableRSREUKURSACH::MyForm::dailyTimetable_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) // Объект таблицы
{
	return System::Void();
}

System::Void TimeTableRSREUKURSACH::MyForm::radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) // Кнопка выбора недели: числитель
{
	if (CheckZnam->Checked == true)
		CheckChisl->Checked = false;
	return System::Void();
}

System::Void TimeTableRSREUKURSACH::MyForm::CheckZnam_CheckedChanged(System::Object^ sender, System::EventArgs^ e) // Кнопка выбора недели: числитель
{
	if (CheckChisl->Checked == true)
		CheckZnam->Checked = false;
	return System::Void();
}

System::Void TimeTableRSREUKURSACH::MyForm::Tutor_CheckedChanged(System::Object^ sender, System::EventArgs^ e) // Галочка доступа: преподаватель
{
	if (Tutor->Checked==true) // Если активна: убирает ряд элементов интерфейа и добавляет возможность редактировать таблицу и сохранять её в файл
	{
		Diagram->Visible = false;
		EVMTt->Visible = false;
		Diagramma->Visible = false;
		dailyTimetable->ReadOnly = false;
		ThisWeekTt->Visible = false;
		NextWeekTt->Visible = false;
		SaveCh->Visible = true;
	}
	else
	{
		ThisWeekTt->Visible = true;
		NextWeekTt->Visible = true;
		SaveCh->Visible = false;
		Diagramma->Visible = true;
		EVMTt->Visible = true;
		dailyTimetable->ReadOnly = true;
	}
	return System::Void();
}

System::Void TimeTableRSREUKURSACH::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e) // Кнопка сохранения изменённого расписания в файл (доступна только преподавателю)
{
	String^ path = "C:\\Users\\AT241\\source\\repos\\TimeTableRSREU_KURSACH\\RaspisChanged.txt";
	System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter(path);

	// Создаёт в файле объявление на редактируемый день недели об изменении расписания
	
	writer->WriteLine("ВНИМАНИЕ! Уважаемые студенты, расписание на день недели "+dailyTimetable->Rows[0]->Cells[4]->Value + " было изменено!\n");

	for (int i=0; i<dailyTimetable->Rows->Count-1; i++)
	{
		writer->Write(dailyTimetable->Rows[i]->Cells[0]->Value+"  ");
		writer->Write(dailyTimetable->Rows[i]->Cells[1]->Value + "  ");
		writer->Write(dailyTimetable->Rows[i]->Cells[2]->Value + "  ");
		writer->Write(dailyTimetable->Rows[i]->Cells[3]->Value + "\n");
	}

	writer->Close();
	return System::Void();
}
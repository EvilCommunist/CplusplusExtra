#include "pch.h"
#include "MyForm.h"
#include <algorithm>


using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

String^ initDay()
{
	DateTime^ x2 = DateTime::Now;
    return x2->DayOfWeek.ToString();
}

ref struct FileManager {
public:
	String^ chooseweek = "  ";
	String^ numlesson = "  ";
	String^ typelesson = "  ";
	String^ namelesson = "  ";
	String^ lessplace = "  ";
};

bool isDayofWeek(String^ data) // Проверка строки на принадлежность к значению дня недели
{
	if (data=="Monday"|| data == "Tuesday" || data == "Wednesday" || data == "Thursday" || data == "Friday")
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
	} 
	while (line[i] != ' ');
	do
	{
		fm->numlesson += line[i];
		i++;
	} 
	while (line[i] != ' ');
	do
	{
		fm->typelesson += line[i];
		i++;
	} 
	while (line[i] != ' ');
	do
	{
		fm->namelesson += line[i];
		i++;
	} 
	while (line[i] != ',');
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

String^ findDay(List<FileManager^>^ fm,int padd) // padd - "смещение" дня
{
	List<String^> Days;
	DateTime^ dt = DateTime::Now;
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
			if (i + padd <= 4)
				day = Days[i + padd];
			else return "Weekend";
		}
	}
	return day;
}

int countLessons(List<FileManager^>^ fm, int padd)
{
	int start;
	for (int i = 0; i < fm->Count; i++)
	{
		if (fm[i]->chooseweek == findDay(fm, padd)) // Don't forget exceptions
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

int seekDay(List<FileManager^>^ fm, String^ day)
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

String^ printDayWeek(String^ day)
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

int countLessons(List<FileManager^>^ fm, String^ lesson, String^ week)
{
	if (!(week == "числитель" || week == "Числитель" || week == "знаменатель" || week == "Знаменатель")) {
		//DevRequest->Text="ВВЕДИТЕ УЧ. НЕДЕЛЮ!";
		return 0;
	}
	int cntch = 0, cntzn=0;
	for (int i = 0; i < fm->Count; i++)
	{
		if (fm[i]->typelesson == lesson) 
		{
			if((week == "числитель" || week == "Числитель")&&(fm[i]->chooseweek->ToString() == "  (числитель)" || fm[i]->chooseweek->ToString() == "  (еженедельно)"))
				cntch++;
			if ((week == "знаменатель" || week == "Знаменатель") && (fm[i]->chooseweek->ToString() == "  (знаменатель)" || fm[i]->chooseweek->ToString() == "  (еженедельно)"))
				cntzn++;
		}
	}
	if ((week == "числитель" || week == "Числитель"))
		return cntch;
	if ((week == "знаменатель" || week == "Знаменатель"))
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

System::Void TimeTableRSREUKURSACH::MyForm::closing_bt_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::Windows::Forms::DialogResult sureclose = MessageBox::Show("Вы точно хотите выйти?", "Внимание!", MessageBoxButtons::YesNo,
		MessageBoxIcon::Question);
	if (sureclose == System::Windows::Forms::DialogResult::Yes)
		this->Close();
	return System::Void();
}

System::Void TimeTableRSREUKURSACH::MyForm::TodayTt_Click(System::Object^ sender, System::EventArgs^ e) // Докрутить начало отсчёта!!!!
{
	dailyTimetable->Rows->Clear();
	List<FileManager^>^ fm = readdocument();
	if ((Week->Text == "числитель" || Week->Text == "Числитель" || Week->Text == "знаменатель" || Week->Text == "Знаменатель")) {
		for (int i = 0; i < countLessons(fm, 0); i++)
			dailyTimetable->Rows->Add();
	}
	if (findDay(fm, 0) == "Weekend")
	{
		dailyTimetable->Rows[0]->Cells[2]->Value = "Weekend";
		return System::Void();
	}
	int startpoint = seekDay(fm, findDay(fm, 0));
	for (int i = startpoint; i<fm->Count; i++)
	{
		if (!(Week->Text == "числитель" || Week->Text == "Числитель" || Week->Text == "знаменатель" || Week->Text == "Знаменатель")) {
			
			break;
		}
		if (fm[i]->chooseweek == findDay(fm,0))
		{
			dailyTimetable->Rows[0]->Cells[4]->Value = printDayWeek(fm[i]->chooseweek);
			i++;
		}
		int j = 0;
		while(!(fm[j]->chooseweek == findDay(fm, 1)))
		{
			if (Week->Text == "числитель" || Week->Text == "Числитель")
			{
				if (fm[i]->chooseweek->ToString() == "  (числитель)" || fm[i]->chooseweek->ToString() == "  (еженедельно)")
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
			if (Week->Text == "знаменатель" || Week->Text == "Знаменатель")
			{
				if (fm[i]->chooseweek->ToString() == "  (знаменатель)" || fm[i]->chooseweek->ToString() == "  (еженедельно)")
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

System::Void TimeTableRSREUKURSACH::MyForm::TomorrowTt_Click(System::Object^ sender, System::EventArgs^ e)
{
	dailyTimetable->Rows->Clear();
	List<FileManager^>^ fm = readdocument();
	if ((Week->Text == "числитель" || Week->Text == "Числитель" || Week->Text == "знаменатель" || Week->Text == "Знаменатель")) {
		for (int i = 0; i < countLessons(fm,1); i++)
			dailyTimetable->Rows->Add();
	}
	if (findDay(fm, 1) == "Weekend")
	{
		dailyTimetable->Rows[0]->Cells[2]->Value = "Weekend";
		return System::Void();
	}
	int startpoint = seekDay(fm, findDay(fm, 1));
	for (int i = startpoint; i < fm->Count; i++)
	{
		if (!(Week->Text == "числитель" || Week->Text == "Числитель" || Week->Text == "знаменатель" || Week->Text == "Знаменатель")) {

			break;
		}
		if (fm[i]->chooseweek == findDay(fm, 1))
		{
			dailyTimetable->Rows[0]->Cells[4]->Value = printDayWeek(fm[i]->chooseweek);
			i++;
		}
		int j = 0;
		while (!(fm[j]->chooseweek == findDay(fm, 2)))
		{
			if (Week->Text == "числитель" || Week->Text == "Числитель")
			{
				if (fm[i]->chooseweek->ToString() == "  (числитель)" || fm[i]->chooseweek->ToString() == "  (еженедельно)")
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
			if (Week->Text == "знаменатель" || Week->Text == "Знаменатель")
			{
				if (fm[i]->chooseweek->ToString() == "  (знаменатель)" || fm[i]->chooseweek->ToString() == "  (еженедельно)")
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

System::Void TimeTableRSREUKURSACH::MyForm::PostTomorrowTt_Click(System::Object^ sender, System::EventArgs^ e)
{
	dailyTimetable->Rows->Clear();
	List<FileManager^>^ fm = readdocument();
	if ((Week->Text == "числитель" || Week->Text == "Числитель" || Week->Text == "знаменатель" || Week->Text == "Знаменатель")) {
		for (int i = 0; i < countLessons(fm,2); i++)
			dailyTimetable->Rows->Add();
	}
	if (findDay(fm, 2) == "Weekend")
	{
		dailyTimetable->Rows[0]->Cells[2]->Value = "Weekend";
		return System::Void();
	}
	int startpoint = seekDay(fm, findDay(fm, 2));
	for (int i = startpoint; i < fm->Count; i++)
	{
		if (!(Week->Text == "числитель" || Week->Text == "Числитель" || Week->Text == "знаменатель" || Week->Text == "Знаменатель")) {
			break;
		}
		if (fm[i]->chooseweek == findDay(fm, 2))
		{
			dailyTimetable->Rows[0]->Cells[4]->Value = printDayWeek(fm[i]->chooseweek);
			i++;
		}
		int j = 0;
		while (!(fm[j]->chooseweek == findDay(fm, 3)))
		{
			if (Week->Text == "числитель" || Week->Text == "Числитель")
			{
				if (fm[i]->chooseweek->ToString() == "  (числитель)" || fm[i]->chooseweek->ToString() == "  (еженедельно)")
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
			if (Week->Text == "знаменатель" || Week->Text == "Знаменатель")
			{
				if (fm[i]->chooseweek->ToString() == "  (знаменатель)" || fm[i]->chooseweek->ToString() == "  (еженедельно)")
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

System::Void TimeTableRSREUKURSACH::MyForm::ThisWeekTt_Click(System::Object^ sender, System::EventArgs^ e)
{
	dailyTimetable->Rows->Clear();
	List<FileManager^>^ fm = readdocument();

	for (int i = 0; i < 18; i++)
		dailyTimetable->Rows->Add();
	int j = 0;
	for (int i = 0; i < fm->Count; i++)
	{
		if (!(Week->Text == "числитель" || Week->Text == "Числитель" || Week->Text == "знаменатель" || Week->Text == "Знаменатель")) {
			//DevRequest->Text="ВВЕДИТЕ УЧ. НЕДЕЛЮ!";
			break;
		}
		if (isDayofWeek(fm[i]->chooseweek))
		{
			dailyTimetable->Rows[j]->Cells[4]->Value = printDayWeek(fm[i]->chooseweek);
			i++;
		}
		if (Week->Text == "знаменатель" || Week->Text == "Знаменатель")
		{
			if (fm[i]->chooseweek->ToString() == "  (знаменатель)" || fm[i]->chooseweek->ToString() == "  (еженедельно)")
			{
				dailyTimetable->Rows[j]->Cells[0]->Value = fm[i]->numlesson;
				dailyTimetable->Rows[j]->Cells[1]->Value = fm[i]->typelesson;
				dailyTimetable->Rows[j]->Cells[2]->Value = fm[i]->namelesson;
				dailyTimetable->Rows[j]->Cells[3]->Value = fm[i]->lessplace;
				j++;
			}
		}
		if (Week->Text == "числитель" || Week->Text == "Числитель")
		{
			if (fm[i]->chooseweek->ToString() == "  (числитель)" || fm[i]->chooseweek->ToString() == "  (еженедельно)")
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

System::Void TimeTableRSREUKURSACH::MyForm::NextWeekTt_Click(System::Object^ sender, System::EventArgs^ e)
{
	dailyTimetable->Rows->Clear();
	List<FileManager^>^ fm = readdocument();

	for (int i = 0; i < 18; i++)
		dailyTimetable->Rows->Add();
	int j = 0;
	for (int i = 0; i < fm->Count; i++)
	{
		if (!(Week->Text == "числитель" || Week->Text == "Числитель" || Week->Text == "знаменатель" || Week->Text == "Знаменатель")) {
			//DevRequest->Text="ВВЕДИТЕ УЧ. НЕДЕЛЮ!";
			break;
		}
		if (isDayofWeek(fm[i]->chooseweek))
		{
			dailyTimetable->Rows[j]->Cells[4]->Value = printDayWeek(fm[i]->chooseweek);
			i++;
		}
		if (Week->Text == "знаменатель" || Week->Text == "Знаменатель")
		{
			if (fm[i]->chooseweek->ToString() == "  (числитель)" || fm[i]->chooseweek->ToString() == "  (еженедельно)")
			{
				dailyTimetable->Rows[j]->Cells[0]->Value = fm[i]->numlesson;
				dailyTimetable->Rows[j]->Cells[1]->Value = fm[i]->typelesson;
				dailyTimetable->Rows[j]->Cells[2]->Value = fm[i]->namelesson;
				dailyTimetable->Rows[j]->Cells[3]->Value = fm[i]->lessplace;
				j++;
			}
		}
		if (Week->Text == "числитель" || Week->Text == "Числитель")
		{
			if (fm[i]->chooseweek->ToString() == "  (знаменатель)" || fm[i]->chooseweek->ToString() == "  (еженедельно)")
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

System::Void TimeTableRSREUKURSACH::MyForm::EVMTt_Click(System::Object^ sender, System::EventArgs^ e)
{
	dailyTimetable->Rows->Clear();
	List<FileManager^>^ fm = readdocument();

	for (int i = 0; i < 6; i++)
		dailyTimetable->Rows->Add();
	int j = 0; String^ day;
	for (int i = 0; i < fm->Count; i++)
	{
		if (!(Week->Text == "числитель" || Week->Text == "Числитель" || Week->Text == "знаменатель" || Week->Text == "Знаменатель")) {
			//DevRequest->Text="ВВЕДИТЕ УЧ. НЕДЕЛЮ!";
			break;
		}
		if (isDayofWeek(fm[i]->chooseweek))
		{
			day = fm[i]->chooseweek;
			i++;
		}
		if(fm[i]->lessplace=="   а. 209" || fm[i]->lessplace == "   а. 210" || fm[i]->lessplace == "   а. 122" || fm[i]->lessplace == "   а. 02/1" || fm[i]->lessplace == "   а. 02/2" || fm[i]->lessplace == "   а. 32")
		{	
		if (Week->Text == "знаменатель" || Week->Text == "Знаменатель")
		{
			if (fm[i]->chooseweek->ToString() == "  (числитель)" || fm[i]->chooseweek->ToString() == "  (еженедельно)")
			{
				dailyTimetable->Rows[j]->Cells[4]->Value = printDayWeek(day);
				dailyTimetable->Rows[j]->Cells[0]->Value = fm[i]->numlesson;
				dailyTimetable->Rows[j]->Cells[1]->Value = fm[i]->typelesson;
				dailyTimetable->Rows[j]->Cells[2]->Value = fm[i]->namelesson;
				dailyTimetable->Rows[j]->Cells[3]->Value = fm[i]->lessplace;
				j++;
			}
		}
		if (Week->Text == "числитель" || Week->Text == "Числитель")
		{
			if (fm[i]->chooseweek->ToString() == "  (знаменатель)" || fm[i]->chooseweek->ToString() == "  (еженедельно)")
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

System::Void TimeTableRSREUKURSACH::MyForm::Diagramma_Click(System::Object^ sender, System::EventArgs^ e)
{
	List<FileManager^>^ fm = readdocument();
	Diagram->Visible = true;
	Diagram->Series->Clear();
	Diagram->Series->Add("упр.");
	Diagram->Series["упр."]->Points->Add(countLessons(fm, "   упр.", Week->Text));
	Diagram->Series->Add("лек.");
	Diagram->Series["лек."]->Points->Add(countLessons(fm, "   лек.", Week->Text));
	Diagram->Series->Add("лаб.");
	Diagram->Series["лаб."]->Points->Add(countLessons(fm, "   лаб.", Week->Text));
	return System::Void();
}

System::Void TimeTableRSREUKURSACH::MyForm::Week_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

System::Void TimeTableRSREUKURSACH::MyForm::dailyTimetable_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
	return System::Void();
}

#pragma once

namespace TimeTableRSREUKURSACH {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ closing_bt;
	private: System::Windows::Forms::Button^ TodayTt;
	private: System::Windows::Forms::Button^ TomorrowTt;
	private: System::Windows::Forms::Button^ PostTomorrowTt;
	private: System::Windows::Forms::Button^ ThisWeekTt;
	private: System::Windows::Forms::Button^ NextWeekTt;
	private: System::Windows::Forms::Button^ EVMTt;
	private: System::Windows::Forms::Button^ Diagramma;
	private: System::Windows::Forms::DataGridView^ dailyTimetable;



	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Name1;



	private: System::Windows::Forms::Label^ DevRequest;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Numb;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ type;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Name;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ audit;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ WeekDay;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ Diagram;
	private: System::Windows::Forms::RadioButton^ CheckZnam;

	private: System::Windows::Forms::RadioButton^ CheckChisl;















	protected:

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->closing_bt = (gcnew System::Windows::Forms::Button());
			this->TodayTt = (gcnew System::Windows::Forms::Button());
			this->TomorrowTt = (gcnew System::Windows::Forms::Button());
			this->PostTomorrowTt = (gcnew System::Windows::Forms::Button());
			this->ThisWeekTt = (gcnew System::Windows::Forms::Button());
			this->NextWeekTt = (gcnew System::Windows::Forms::Button());
			this->EVMTt = (gcnew System::Windows::Forms::Button());
			this->Diagramma = (gcnew System::Windows::Forms::Button());
			this->dailyTimetable = (gcnew System::Windows::Forms::DataGridView());
			this->Numb = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->type = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Name = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->audit = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->WeekDay = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DevRequest = (gcnew System::Windows::Forms::Label());
			this->Diagram = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->CheckZnam = (gcnew System::Windows::Forms::RadioButton());
			this->CheckChisl = (gcnew System::Windows::Forms::RadioButton());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dailyTimetable))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Diagram))->BeginInit();
			this->SuspendLayout();
			// 
			// closing_bt
			// 
			this->closing_bt->BackColor = System::Drawing::Color::DarkOrange;
			this->closing_bt->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->closing_bt->Cursor = System::Windows::Forms::Cursors::Hand;
			this->closing_bt->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->closing_bt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->closing_bt->Location = System::Drawing::Point(934, 12);
			this->closing_bt->Name = L"closing_bt";
			this->closing_bt->Size = System::Drawing::Size(37, 34);
			this->closing_bt->TabIndex = 0;
			this->closing_bt->Text = L"Х";
			this->closing_bt->UseVisualStyleBackColor = false;
			this->closing_bt->Click += gcnew System::EventHandler(this, &MyForm::closing_bt_Click);
			// 
			// TodayTt
			// 
			this->TodayTt->BackColor = System::Drawing::Color::WhiteSmoke;
			this->TodayTt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TodayTt->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->TodayTt->ForeColor = System::Drawing::SystemColors::WindowText;
			this->TodayTt->Location = System::Drawing::Point(790, 65);
			this->TodayTt->Name = L"TodayTt";
			this->TodayTt->Size = System::Drawing::Size(181, 55);
			this->TodayTt->TabIndex = 1;
			this->TodayTt->Text = L"Узнать расписание на сегодня";
			this->TodayTt->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->TodayTt->UseVisualStyleBackColor = false;
			this->TodayTt->Click += gcnew System::EventHandler(this, &MyForm::TodayTt_Click);
			// 
			// TomorrowTt
			// 
			this->TomorrowTt->BackColor = System::Drawing::Color::WhiteSmoke;
			this->TomorrowTt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TomorrowTt->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->TomorrowTt->ForeColor = System::Drawing::SystemColors::WindowText;
			this->TomorrowTt->Location = System::Drawing::Point(790, 140);
			this->TomorrowTt->Name = L"TomorrowTt";
			this->TomorrowTt->Size = System::Drawing::Size(181, 55);
			this->TomorrowTt->TabIndex = 2;
			this->TomorrowTt->Text = L"Узнать расписание на завтра";
			this->TomorrowTt->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->TomorrowTt->UseVisualStyleBackColor = false;
			this->TomorrowTt->Click += gcnew System::EventHandler(this, &MyForm::TomorrowTt_Click);
			// 
			// PostTomorrowTt
			// 
			this->PostTomorrowTt->BackColor = System::Drawing::Color::WhiteSmoke;
			this->PostTomorrowTt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->PostTomorrowTt->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->PostTomorrowTt->ForeColor = System::Drawing::SystemColors::WindowText;
			this->PostTomorrowTt->Location = System::Drawing::Point(790, 217);
			this->PostTomorrowTt->Name = L"PostTomorrowTt";
			this->PostTomorrowTt->Size = System::Drawing::Size(181, 55);
			this->PostTomorrowTt->TabIndex = 3;
			this->PostTomorrowTt->Text = L"Узнать расписание на послезавтра";
			this->PostTomorrowTt->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->PostTomorrowTt->UseVisualStyleBackColor = false;
			this->PostTomorrowTt->Click += gcnew System::EventHandler(this, &MyForm::PostTomorrowTt_Click);
			// 
			// ThisWeekTt
			// 
			this->ThisWeekTt->BackColor = System::Drawing::Color::WhiteSmoke;
			this->ThisWeekTt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ThisWeekTt->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ThisWeekTt->ForeColor = System::Drawing::SystemColors::WindowText;
			this->ThisWeekTt->Location = System::Drawing::Point(790, 309);
			this->ThisWeekTt->Name = L"ThisWeekTt";
			this->ThisWeekTt->Size = System::Drawing::Size(181, 70);
			this->ThisWeekTt->TabIndex = 4;
			this->ThisWeekTt->Text = L"Узнать расписание на эту неделю\r\n";
			this->ThisWeekTt->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->ThisWeekTt->UseVisualStyleBackColor = false;
			this->ThisWeekTt->Click += gcnew System::EventHandler(this, &MyForm::ThisWeekTt_Click);
			// 
			// NextWeekTt
			// 
			this->NextWeekTt->BackColor = System::Drawing::Color::WhiteSmoke;
			this->NextWeekTt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->NextWeekTt->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->NextWeekTt->ForeColor = System::Drawing::SystemColors::WindowText;
			this->NextWeekTt->Location = System::Drawing::Point(790, 409);
			this->NextWeekTt->Name = L"NextWeekTt";
			this->NextWeekTt->Size = System::Drawing::Size(181, 70);
			this->NextWeekTt->TabIndex = 5;
			this->NextWeekTt->Text = L"Узнать расписание на грядущую неделю\r\n";
			this->NextWeekTt->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->NextWeekTt->UseVisualStyleBackColor = false;
			this->NextWeekTt->Click += gcnew System::EventHandler(this, &MyForm::NextWeekTt_Click);
			// 
			// EVMTt
			// 
			this->EVMTt->BackColor = System::Drawing::Color::WhiteSmoke;
			this->EVMTt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->EVMTt->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->EVMTt->ForeColor = System::Drawing::SystemColors::WindowText;
			this->EVMTt->Location = System::Drawing::Point(582, 409);
			this->EVMTt->Name = L"EVMTt";
			this->EVMTt->Size = System::Drawing::Size(192, 70);
			this->EVMTt->TabIndex = 6;
			this->EVMTt->Text = L"Узнать расписание пар в ауд. каф. ЭВМ";
			this->EVMTt->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->EVMTt->UseVisualStyleBackColor = false;
			this->EVMTt->Click += gcnew System::EventHandler(this, &MyForm::EVMTt_Click);
			// 
			// Diagramma
			// 
			this->Diagramma->BackColor = System::Drawing::Color::WhiteSmoke;
			this->Diagramma->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Diagramma->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Diagramma->ForeColor = System::Drawing::SystemColors::WindowText;
			this->Diagramma->Location = System::Drawing::Point(582, 309);
			this->Diagramma->Name = L"Diagramma";
			this->Diagramma->Size = System::Drawing::Size(192, 70);
			this->Diagramma->TabIndex = 7;
			this->Diagramma->Text = L"Узнать соотношение пар\r\n";
			this->Diagramma->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->Diagramma->UseVisualStyleBackColor = false;
			this->Diagramma->Click += gcnew System::EventHandler(this, &MyForm::Diagramma_Click);
			// 
			// dailyTimetable
			// 
			this->dailyTimetable->BackgroundColor = System::Drawing::SystemColors::ActiveBorder;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dailyTimetable->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->dailyTimetable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dailyTimetable->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
				this->Numb,
					this->type, this->Name, this->audit, this->WeekDay
			});
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dailyTimetable->DefaultCellStyle = dataGridViewCellStyle2;
			this->dailyTimetable->GridColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->dailyTimetable->Location = System::Drawing::Point(12, 12);
			this->dailyTimetable->Name = L"dailyTimetable";
			this->dailyTimetable->RowHeadersWidth = 51;
			this->dailyTimetable->RowTemplate->Height = 24;
			this->dailyTimetable->Size = System::Drawing::Size(558, 467);
			this->dailyTimetable->TabIndex = 8;
			this->dailyTimetable->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::dailyTimetable_CellContentClick);
			// 
			// Numb
			// 
			this->Numb->Frozen = true;
			this->Numb->HeaderText = L"N";
			this->Numb->MinimumWidth = 6;
			this->Numb->Name = L"Numb";
			this->Numb->ReadOnly = true;
			this->Numb->Width = 45;
			// 
			// type
			// 
			this->type->Frozen = true;
			this->type->HeaderText = L"Тип занятия";
			this->type->MinimumWidth = 6;
			this->type->Name = L"type";
			this->type->ReadOnly = true;
			this->type->Width = 70;
			// 
			// Name
			// 
			this->Name->Frozen = true;
			this->Name->HeaderText = L"Название предмета";
			this->Name->MinimumWidth = 6;
			this->Name->Name = L"Name";
			this->Name->ReadOnly = true;
			this->Name->Width = 210;
			// 
			// audit
			// 
			this->audit->Frozen = true;
			this->audit->HeaderText = L"Аудитория";
			this->audit->MinimumWidth = 6;
			this->audit->Name = L"audit";
			this->audit->ReadOnly = true;
			this->audit->Width = 90;
			// 
			// WeekDay
			// 
			this->WeekDay->HeaderText = L"День недели";
			this->WeekDay->MinimumWidth = 6;
			this->WeekDay->Name = L"WeekDay";
			this->WeekDay->ReadOnly = true;
			this->WeekDay->Width = 90;
			// 
			// DevRequest
			// 
			this->DevRequest->AutoSize = true;
			this->DevRequest->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->DevRequest->ForeColor = System::Drawing::Color::White;
			this->DevRequest->Location = System::Drawing::Point(579, 210);
			this->DevRequest->Name = L"DevRequest";
			this->DevRequest->Size = System::Drawing::Size(126, 36);
			this->DevRequest->TabIndex = 11;
			this->DevRequest->Text = L"Какая сейчас\r\nучебная неделя\?";
			// 
			// Diagram
			// 
			this->Diagram->BackColor = System::Drawing::Color::DarkGray;
			this->Diagram->BackSecondaryColor = System::Drawing::Color::DarkGray;
			this->Diagram->BorderlineColor = System::Drawing::Color::DarkGray;
			chartArea1->Name = L"ChartArea1";
			this->Diagram->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->Diagram->Legends->Add(legend1);
			this->Diagram->Location = System::Drawing::Point(582, 12);
			this->Diagram->Name = L"Diagram";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Pie;
			series1->Color = System::Drawing::Color::DarkGray;
			series1->IsXValueIndexed = true;
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			series1->XValueMember = L"MyForm.cpp";
			this->Diagram->Series->Add(series1);
			this->Diagram->Size = System::Drawing::Size(192, 183);
			this->Diagram->TabIndex = 12;
			this->Diagram->Text = L"Диаграмма";
			this->Diagram->Visible = false;
			this->Diagram->Click += gcnew System::EventHandler(this, &MyForm::Diagram_Click);
			// 
			// CheckZnam
			// 
			this->CheckZnam->AutoSize = true;
			this->CheckZnam->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->CheckZnam->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->CheckZnam->Location = System::Drawing::Point(582, 278);
			this->CheckZnam->Name = L"CheckZnam";
			this->CheckZnam->Size = System::Drawing::Size(133, 22);
			this->CheckZnam->TabIndex = 13;
			this->CheckZnam->TabStop = true;
			this->CheckZnam->Text = L"Знаменатель";
			this->CheckZnam->UseVisualStyleBackColor = true;
			this->CheckZnam->CheckedChanged += gcnew System::EventHandler(this, &MyForm::CheckZnam_CheckedChanged);
			// 
			// CheckChisl
			// 
			this->CheckChisl->AutoSize = true;
			this->CheckChisl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->CheckChisl->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->CheckChisl->Location = System::Drawing::Point(582, 252);
			this->CheckChisl->Name = L"CheckChisl";
			this->CheckChisl->Size = System::Drawing::Size(113, 22);
			this->CheckChisl->TabIndex = 14;
			this->CheckChisl->TabStop = true;
			this->CheckChisl->Text = L"Числитель";
			this->CheckChisl->UseVisualStyleBackColor = true;
			this->CheckChisl->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton2_CheckedChanged);
			// 
			// MyForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(69)), static_cast<System::Int32>(static_cast<System::Byte>(69)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->ClientSize = System::Drawing::Size(992, 495);
			this->Controls->Add(this->CheckChisl);
			this->Controls->Add(this->CheckZnam);
			this->Controls->Add(this->Diagram);
			this->Controls->Add(this->DevRequest);
			this->Controls->Add(this->dailyTimetable);
			this->Controls->Add(this->Diagramma);
			this->Controls->Add(this->EVMTt);
			this->Controls->Add(this->NextWeekTt);
			this->Controls->Add(this->ThisWeekTt);
			this->Controls->Add(this->PostTomorrowTt);
			this->Controls->Add(this->TomorrowTt);
			this->Controls->Add(this->TodayTt);
			this->Controls->Add(this->closing_bt);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ForeColor = System::Drawing::Color::Black;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			//this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"RSREU Timetable";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dailyTimetable))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Diagram))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	
	private: System::Void closing_bt_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void TodayTt_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void TomorrowTt_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void PostTomorrowTt_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void ThisWeekTt_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void NextWeekTt_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void EVMTt_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void Diagramma_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void Week_TextChanged(System::Object^ sender, System::EventArgs^ e);
private: System::Void dailyTimetable_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
private: System::Void Diagram_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
private: System::Void CheckZnam_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
};
}

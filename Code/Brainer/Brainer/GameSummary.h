#pragma once

#include "CommonHeader.h"
#include "MiscUtils.h"
#include "CommonHeader.h"
#include <stdio.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Brainer {

  struct TGameQuestion
  {
    char* mpch_QueString;
    char* mpch_ActualAnsString;
    char* mpch_GivenAnsString;
    char* mpch_TimeString;
    bool mb_correct;
    TGameQuestion()
    : mpch_QueString(new char[iMaxQALen]),
      mpch_ActualAnsString(new char[iMaxQALen]),
      mpch_GivenAnsString(new char[iMaxQALen]),
      mpch_TimeString(new char[iMaxQALen]),
      mb_correct(false){}
    ~TGameQuestion() {
      delete[] mpch_QueString; 
      delete[] mpch_ActualAnsString; 
      delete[] mpch_GivenAnsString; 
      delete[] mpch_TimeString; 
    }
  };
  class TGameQuestions
  {
  private:
    int mi_NumberQuestions;
  public:
    TGameQuestion* mp_GameQuestion; 
	int GetNumberOfRounds(){
		return mi_NumberQuestions;
	}
    TGameQuestions(int _i_NumberQuestions) {
        mi_NumberQuestions = _i_NumberQuestions;
		mp_GameQuestion = new TGameQuestion[_i_NumberQuestions];
    }
    ~TGameQuestions() {
      delete[] mp_GameQuestion;
    }
  };


	/// <summary>
	/// Summary for GameSummary
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class GameSummary : public System::Windows::Forms::Form
	{
  private:
    void addRow(int _i_queNo, const char* _pc_question, const char* _pc_givenAnswer, const char* _pc_actualAnswer, const char* _pc_time, bool _b_correct) 
    {
      char NumberString[4];
      sprintf(NumberString, "%d", _i_queNo);
      String^ questionNumber = gcnew String(NumberString);
      String^ question = gcnew String(_pc_question);
      String^ givenAnswer = gcnew String(_pc_givenAnswer);
      String^ actualAnswer = gcnew String(_pc_actualAnswer);
      String^ time = gcnew String(_pc_time);

      System::Drawing::Color givenAnswerColor;
      if(_b_correct) {
        givenAnswerColor = System::Drawing::Color::FromArgb(255,255,255);
      }
      else {
        givenAnswerColor = System::Drawing::Color::FromArgb(255,51,51);
      }

      System::Windows::Forms::ListViewItem^  listViewItem1 = 
        (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::Windows::Forms::ListViewItem::ListViewSubItem^  >(5) {
          (gcnew System::Windows::Forms::ListViewItem::ListViewSubItem(nullptr, questionNumber)), 
          (gcnew System::Windows::Forms::ListViewItem::ListViewSubItem(nullptr, question)),
          (gcnew System::Windows::Forms::ListViewItem::ListViewSubItem(nullptr, actualAnswer)), 
          (gcnew System::Windows::Forms::ListViewItem::ListViewSubItem(nullptr, givenAnswer, System::Drawing::Color::FromArgb(0,0,0), givenAnswerColor, (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0))))),
          (gcnew System::Windows::Forms::ListViewItem::ListViewSubItem(nullptr, time, System::Drawing::Color::FromArgb(0,0,0), givenAnswerColor, (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0))))) }, -1));
      listViewItem1->UseItemStyleForSubItems = false; 
      this->listView1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(1) {listViewItem1});
    }
    void sizeDialogue(int _i_NumRounds)
    {
      this->col_no->Width = 26;
      this->col_Que->Width = 600;
      if (!mb_answersOnly) {
        this->col_theAns->Width = 150;
		this->col_yourAns->Width = 100;
		this->col_time->Width = 45;
	  }
	  else {
        this->col_theAns->Width = 300;
	  }
      this->Width = this->col_no->Width + this->col_Que->Width + this->col_theAns->Width + this->col_yourAns->Width + this->col_time->Width + 20;
      this->Height = 34 + (this->listView1->Font->Size+16) + ((this->listView1->Font->Size+10) * _i_NumRounds);
    }

	public:
		GameSummary(TGameQuestions* _p_gameQuestions, bool _b_answersOnly)
		{
		  mb_answersOnly = _b_answersOnly;
          InitializeComponent();
		  if (mb_answersOnly) {
		    this->col_yourAns->Width = 0;
		    this->col_time->Width = 0;
		  }
		  for(int i=0; i<_p_gameQuestions->GetNumberOfRounds(); ++i) {
            addRow(i+1, _p_gameQuestions->mp_GameQuestion[i].mpch_QueString, _p_gameQuestions->mp_GameQuestion[i].mpch_GivenAnsString, 
		    _p_gameQuestions->mp_GameQuestion[i].mpch_ActualAnsString, _p_gameQuestions->mp_GameQuestion[i].mpch_TimeString, _p_gameQuestions->mp_GameQuestion[i].mb_correct);
          }

      sizeDialogue(_p_gameQuestions->GetNumberOfRounds());
    }

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GameSummary()
		{
			if (components)
			{
				delete components;
			}
		}
  private: System::Windows::Forms::ListView^  listView1;
  private: System::Windows::Forms::ColumnHeader^  col_no;
  private: System::Windows::Forms::ColumnHeader^  col_Que;
  private: System::Windows::Forms::ColumnHeader^  col_theAns;

  private: System::Windows::Forms::ColumnHeader^  col_yourAns;
	private: System::Windows::Forms::ColumnHeader^  col_time;

	private:
 		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		bool mb_answersOnly;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->col_no = (gcnew System::Windows::Forms::ColumnHeader());
			this->col_Que = (gcnew System::Windows::Forms::ColumnHeader());
			this->col_theAns = (gcnew System::Windows::Forms::ColumnHeader());
			this->col_yourAns = (gcnew System::Windows::Forms::ColumnHeader());
			this->col_time = (gcnew System::Windows::Forms::ColumnHeader());
			this->SuspendLayout();
			// 
			// listView1
			// 
			this->listView1->BackColor = System::Drawing::SystemColors::Window;
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {this->col_no, this->col_Que, 
				this->col_theAns, this->col_yourAns, this->col_time});
			this->listView1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listView1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->listView1->ForeColor = System::Drawing::SystemColors::WindowText;
			this->listView1->Location = System::Drawing::Point(0, 0);
			this->listView1->Name = L"listView1";
			this->listView1->ShowItemToolTips = true;
			this->listView1->Size = System::Drawing::Size(775, 287);
			this->listView1->TabIndex = 0;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			this->listView1->SelectedIndexChanged += gcnew System::EventHandler(this, &GameSummary::listView1_SelectedIndexChanged);
			// 
			// col_no
			// 
			this->col_no->Text = L"Q";
			this->col_no->Width = 26;
			// 
			// col_Que
			// 
			this->col_Que->Text = L"Question";
			this->col_Que->Width = 253;
			// 
			// col_theAns
			// 
			this->col_theAns->Text = L"The Answer";
			this->col_theAns->Width = 197;
			// 
			// col_yourAns
			// 
			this->col_yourAns->Text = L"Your Answer";
			this->col_yourAns->Width = 101;
			// 
			// col_time
			// 
			this->col_time->Text = L"Time";
			// 
			// GameSummary
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(775, 287);
			this->Controls->Add(this->listView1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Name = L"GameSummary";
			this->ShowInTaskbar = false;
			this->Text = L"GameSummary";
			this->ResumeLayout(false);

		}
#pragma endregion

  private: System::Void listView1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
           }
};



}

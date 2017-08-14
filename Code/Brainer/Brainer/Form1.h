#pragma once
#include "stdafx.h"
#include "GameContainer.h"
#include "AppException.h"
#include "ScoreFileHandler.h"
#include "Games.h"
#include "Numeric.h"
#include "IniFile.h"
#include "AppHeader.h"
#include "GameSummary.h"
#include <stdlib.h>
#include <String>
#include "time.h"
#include <windows.h>
#include <process.h>
#include <vector>
#include <algorithm>
#pragma comment(lib, "user32.lib")

namespace Brainer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public
	ref class Form1 : public System::Windows::Forms::Form {
	public:
		Form1(void)
		{
			mi_NoRounds = 10;
			mb_GameUpdate = false;
			mp_ScoreFileHandler = new TScoreFileHandler();
			InitializeComponent();
			this->rbtn_Mix_10->Checked = true;
			this->rbtn_Easy->Checked = true;
			mp_GameQuestions = NULL;
			mp_Rounds = new TRounds();
			mp_GameContainer = new TGameContainer();
			mch_CurrentQueString = new char[iMaxQALen];
			if (mp_GameContainer) {
				try {
					this->mp_GameContainer->Setup();
					int iNoGames = this->mp_GameContainer->GetNumberOfGames();
					mp_Games = new TGames(iNoGames);
					addGameStringsToComboBox(false);
					string GameName;
					for (int i = 0; i < iNoGames; i++) {
						mp_GameContainer->GetGameName(GameName, i);
						String ^ s = gcnew String(GameName.c_str());
						this->mp_Games->SetGame(i, GameName);
					}
					setGameInComboBox(0);

					this->pan_GameScores->BringToFront();
					this->btn_NextQue->Hide();
					this->pgbr_Timer->Hide();
					this->lbl_secsLeft->Hide();
					this->tb_QueNo->Hide();
					this->loadFromIni1();
					this->PopulateHighScores();
					this->SetGameSelectionEnablement();
					this->loadFromIni2();
				}
				catch (TAppException _AppExp) {
					this->pan_Setup->Enabled = false;
					this->btn_NextQue->Hide();
					this->pgbr_Timer->Hide();
					this->lbl_secsLeft->Hide();
					String ^ str = gcnew String(_AppExp.GetMsg());
					MessageBox::Show(str);
				}
			}
			else {
				this->pan_Setup->Enabled = false;
				String ^ str = gcnew String("Unable to allocate memory");
				MessageBox::Show(str);
			}
			mp_SummaryForm = nullptr;
		}

	private:
		System::Windows::Forms::Panel ^ pan_GameText;
		System::Windows::Forms::Panel ^ pan_GameRadio;
		System::Windows::Forms::RichTextBox ^ rtb_GameText_Que;
		System::Windows::Forms::GroupBox ^ grp_Options;
		System::Windows::Forms::RadioButton ^ rbtn_option5;
		System::Windows::Forms::RadioButton ^ rbtn_option4;
		System::Windows::Forms::RadioButton ^ rbtn_option3;
		System::Windows::Forms::RadioButton ^ rbtn_option2;
		System::Windows::Forms::RadioButton ^ rbtn_option1;
		System::Windows::Forms::Button ^ btn_NextQue;
		System::Windows::Forms::RichTextBox ^ rtb_GameText_Ans;
		System::Windows::Forms::TextBox ^ tb_QueNo;
		System::Windows::Forms::Panel ^ pan_GameScores;
		System::Windows::Forms::ProgressBar ^ pgbr_Timer;
		System::Windows::Forms::Timer ^ timer1;
		System::Windows::Forms::RadioButton ^ rbtn_Med;
		System::Windows::Forms::Label ^ lbl_secsLeft;
		System::Windows::Forms::TextBox ^ rtxt_option4;
		System::Windows::Forms::TextBox ^ rtxt_option3;
		System::Windows::Forms::TextBox ^ rtxt_option2;
		System::Windows::Forms::TextBox ^ rtxt_option1;
		System::Windows::Forms::TextBox ^ rtxt_option5;
		System::Windows::Forms::GroupBox ^ grpB_HighScores;
		System::Windows::Forms::TextBox ^ tb_HSDiff;
		System::Windows::Forms::Label ^ label14;
		System::Windows::Forms::TextBox ^ tb_HSGame;
		System::Windows::Forms::Label ^ label9;
		System::Windows::Forms::Label ^ label10;
		System::Windows::Forms::Label ^ label11;
		System::Windows::Forms::Label ^ label12;
		System::Windows::Forms::Label ^ label13;
		System::Windows::Forms::Label ^ label8;
		System::Windows::Forms::Label ^ label7;
		System::Windows::Forms::Label ^ label6;
		System::Windows::Forms::Label ^ label5;
		System::Windows::Forms::Label ^ label4;
		System::Windows::Forms::TextBox ^ tb_HS10;
		System::Windows::Forms::TextBox ^ tb_HS9;
		System::Windows::Forms::TextBox ^ tb_HS8;
		System::Windows::Forms::TextBox ^ tb_HS7;
		System::Windows::Forms::TextBox ^ tb_HS6;
		System::Windows::Forms::TextBox ^ tb_HS5;
		System::Windows::Forms::TextBox ^ tb_HS4;
		System::Windows::Forms::TextBox ^ tb_HS3;
		System::Windows::Forms::TextBox ^ tb_HS2;
		System::Windows::Forms::TextBox ^ tb_HS1;
		System::Windows::Forms::Label ^ label3;
		System::Windows::Forms::GroupBox ^ grpB_LastScores;
		System::Windows::Forms::TextBox ^ tb_FinScore;
		System::Windows::Forms::Label ^ label2;
		System::Windows::Forms::TextBox ^ tb_FinQueNo;
		System::Windows::Forms::Label ^ label1;
		System::Windows::Forms::RadioButton ^ rbtn_Mix_10;
		System::Windows::Forms::RadioButton ^ rbtn_Single_10;
		System::Windows::Forms::Label ^ label15;
		Microsoft::VisualBasic::PowerPacks::ShapeContainer ^ shapeContainer1;
		Microsoft::VisualBasic::PowerPacks::RectangleShape ^ rectangleShape2;
		Microsoft::VisualBasic::PowerPacks::RectangleShape ^ rectangleShape1;
		System::Windows::Forms::Label ^ label16;
		System::Windows::Forms::RadioButton ^ rbtn_Mix_All;
		System::Windows::Forms::RadioButton ^ rbtn_Single_All;
		System::Windows::Forms::Button ^ btn_show;
		System::Windows::Forms::RichTextBox ^ rtb_GameRadio_Que;

		void resetGames();
		void InitGame();
		void InitSingle10Game();
		void InitMix10Game();
		void InitSingleAllGame();
		void InitMixAllGame();
		unsigned int getSelectedGameIndex();
		void InitQue();
		void SetupQue(int _i_GameType);
		void FinaliseGame(bool _b_RunOK);
		void QueEnd();
		void ValidateTextAns(int _i_PercentToAns, bool _b_NumConvert);
		void ValidateRadioAns(int _i_PercentToAns);
		void setTime();
		void GetSelectedRadioBtn(int* _pi_SelRadioBtn);
		void UpdateScoreBox(bool _b_Fin);
		void RoundResults(int* _pi_NoCorrect, int* _pi_Score);
		void SetRadioText(int _i_btn, String ^ _s);
		void PopulateHighScores();
		void SetGameSelectionEnablement();
		string GetHighScoreString();
		void setGameInComboBox(int _i_gameindex);
		void addGameStringsToComboBox(bool _b_triviaOnly);
		void populateTimeRemainingLabel(unsigned int _ui_TotalTime, unsigned int _ui_TimeElapsed);
		void saveToIni();
		void loadFromIni1();
		void loadFromIni2();
		void ThrowError(unsigned int _ui_ErrorCode);
		//This contains all the details of the found and loaded dlls
		TGameContainer* mp_GameContainer;
		//This is populated with the indexes of games to be played on a round
		TRounds* mp_Rounds;
		//This is to associate the game string names with the TGameContainer indexes
		TGames* mp_Games;
		//Handles the high score tables
		TScoreFileHandler* mp_ScoreFileHandler;
		//Keeps track of questions, answers and answers given for display at end of game
		TGameQuestions* mp_GameQuestions;
		int mi_NoRounds;
		int mi_CurrentQue;
		char* mch_CurrentQueString;
		bool mb_GameUpdate;
		unsigned int mui_TimerTicks;
		bool mb_GameFinialised;
		void StartGame();
		int copyQuestionString(char* _pch_QueStringSource, char* _pch_QueStringDest);
		int copyRadioQuestionsAndAnswerStrings(char* _pch_QueStringSource, char* _pch_QueStringDest, char* _pch_ActualAnswerDest, std::vector<std::vector<char> >& AnswerStrings);
		GameSummary ^ mp_SummaryForm;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (mp_GameContainer) {
				delete mp_GameContainer;
			}
			if (mp_Rounds) {
				delete mp_Rounds;
			}
			if (components) {
				delete components;
			}
			if (mp_Games) {
				delete mp_Games;
			}
			if (mch_CurrentQueString) {
				delete[] mch_CurrentQueString;
			}
			if (mp_ScoreFileHandler) {
				delete mp_ScoreFileHandler;
			}
			if (mp_GameQuestions) {
				delete mp_GameQuestions;
			}
		}

	private:
		System::Windows::Forms::ComboBox ^ combo_Game;
		System::Windows::Forms::GroupBox ^ grp_Diff;

	protected:
		virtual void WndProc(Message % m) override
		{
			if (m.Msg == WM_HOTKEY && m.WParam.ToInt32() == 1) {
				this->WindowState = FormWindowState::Normal;
				if (mp_SummaryForm == nullptr) {
					if (mb_GameUpdate == true) {
						this->QueEnd();
					}
					else {
						this->StartGame();
					}
				}
				else {
					mp_SummaryForm->Close();
				}
			}
			__super ::WndProc(m);
		}

	private:
		System::Windows::Forms::RadioButton ^ rbtn_Hard;
		System::Windows::Forms::RadioButton ^ rbtn_Easy;
		System::Windows::Forms::Button ^ btn_Go;
		System::Windows::Forms::Panel ^ pan_Setup;
		System::Windows::Forms::GroupBox ^ grp_Theme;
		System::ComponentModel::IContainer ^ components;

		/// <summary>
		/// Required designer variable.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->combo_Game = (gcnew System::Windows::Forms::ComboBox());
			this->grp_Diff = (gcnew System::Windows::Forms::GroupBox());
			this->rbtn_Med = (gcnew System::Windows::Forms::RadioButton());
			this->rbtn_Hard = (gcnew System::Windows::Forms::RadioButton());
			this->rbtn_Easy = (gcnew System::Windows::Forms::RadioButton());
			this->btn_Go = (gcnew System::Windows::Forms::Button());
			this->pan_Setup = (gcnew System::Windows::Forms::Panel());
			this->btn_show = (gcnew System::Windows::Forms::Button());
			this->grp_Theme = (gcnew System::Windows::Forms::GroupBox());
			this->rbtn_Mix_All = (gcnew System::Windows::Forms::RadioButton());
			this->rbtn_Single_All = (gcnew System::Windows::Forms::RadioButton());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->rbtn_Single_10 = (gcnew System::Windows::Forms::RadioButton());
			this->rbtn_Mix_10 = (gcnew System::Windows::Forms::RadioButton());
			this->shapeContainer1 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->rectangleShape2 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape1 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->pan_GameText = (gcnew System::Windows::Forms::Panel());
			this->pan_GameScores = (gcnew System::Windows::Forms::Panel());
			this->grpB_LastScores = (gcnew System::Windows::Forms::GroupBox());
			this->tb_FinScore = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tb_FinQueNo = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->grpB_HighScores = (gcnew System::Windows::Forms::GroupBox());
			this->tb_HSDiff = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->tb_HSGame = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tb_HS10 = (gcnew System::Windows::Forms::TextBox());
			this->tb_HS9 = (gcnew System::Windows::Forms::TextBox());
			this->tb_HS8 = (gcnew System::Windows::Forms::TextBox());
			this->tb_HS7 = (gcnew System::Windows::Forms::TextBox());
			this->tb_HS6 = (gcnew System::Windows::Forms::TextBox());
			this->tb_HS5 = (gcnew System::Windows::Forms::TextBox());
			this->tb_HS4 = (gcnew System::Windows::Forms::TextBox());
			this->tb_HS3 = (gcnew System::Windows::Forms::TextBox());
			this->tb_HS2 = (gcnew System::Windows::Forms::TextBox());
			this->tb_HS1 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->rtb_GameText_Que = (gcnew System::Windows::Forms::RichTextBox());
			this->rtb_GameText_Ans = (gcnew System::Windows::Forms::RichTextBox());
			this->pan_GameRadio = (gcnew System::Windows::Forms::Panel());
			this->rtb_GameRadio_Que = (gcnew System::Windows::Forms::RichTextBox());
			this->grp_Options = (gcnew System::Windows::Forms::GroupBox());
			this->rtxt_option5 = (gcnew System::Windows::Forms::TextBox());
			this->rtxt_option4 = (gcnew System::Windows::Forms::TextBox());
			this->rtxt_option3 = (gcnew System::Windows::Forms::TextBox());
			this->rtxt_option2 = (gcnew System::Windows::Forms::TextBox());
			this->rtxt_option1 = (gcnew System::Windows::Forms::TextBox());
			this->rbtn_option5 = (gcnew System::Windows::Forms::RadioButton());
			this->rbtn_option4 = (gcnew System::Windows::Forms::RadioButton());
			this->rbtn_option3 = (gcnew System::Windows::Forms::RadioButton());
			this->rbtn_option2 = (gcnew System::Windows::Forms::RadioButton());
			this->rbtn_option1 = (gcnew System::Windows::Forms::RadioButton());
			this->btn_NextQue = (gcnew System::Windows::Forms::Button());
			this->tb_QueNo = (gcnew System::Windows::Forms::TextBox());
			this->pgbr_Timer = (gcnew System::Windows::Forms::ProgressBar());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->lbl_secsLeft = (gcnew System::Windows::Forms::Label());
			this->grp_Diff->SuspendLayout();
			this->pan_Setup->SuspendLayout();
			this->grp_Theme->SuspendLayout();
			this->pan_GameText->SuspendLayout();
			this->pan_GameScores->SuspendLayout();
			this->grpB_LastScores->SuspendLayout();
			this->grpB_HighScores->SuspendLayout();
			this->pan_GameRadio->SuspendLayout();
			this->grp_Options->SuspendLayout();
			this->SuspendLayout();
			//
			// combo_Game
			//
			this->combo_Game->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->combo_Game->FormattingEnabled = true;
			this->combo_Game->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->combo_Game->Location = System::Drawing::Point(13, 115);
			this->combo_Game->MaxDropDownItems = 15;
			this->combo_Game->Name = L"combo_Game";
			this->combo_Game->Size = System::Drawing::Size(253, 21);
			this->combo_Game->TabIndex = 1;
			this->combo_Game->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::combo_Game_SelectedIndexChanged);
			//
			// grp_Diff
			//
			this->grp_Diff->Controls->Add(this->rbtn_Med);
			this->grp_Diff->Controls->Add(this->rbtn_Hard);
			this->grp_Diff->Controls->Add(this->rbtn_Easy);
			this->grp_Diff->Location = System::Drawing::Point(13, 145);
			this->grp_Diff->Name = L"grp_Diff";
			this->grp_Diff->Size = System::Drawing::Size(88, 125);
			this->grp_Diff->TabIndex = 2;
			this->grp_Diff->TabStop = false;
			this->grp_Diff->Text = L"Difficulty";
			//
			// rbtn_Med
			//
			this->rbtn_Med->AutoSize = true;
			this->rbtn_Med->Location = System::Drawing::Point(14, 56);
			this->rbtn_Med->Name = L"rbtn_Med";
			this->rbtn_Med->Size = System::Drawing::Size(52, 17);
			this->rbtn_Med->TabIndex = 2;
			this->rbtn_Med->TabStop = true;
			this->rbtn_Med->Text = L"Freak";
			this->rbtn_Med->UseVisualStyleBackColor = true;
			//
			// rbtn_Hard
			//
			this->rbtn_Hard->AutoSize = true;
			this->rbtn_Hard->Location = System::Drawing::Point(14, 91);
			this->rbtn_Hard->Name = L"rbtn_Hard";
			this->rbtn_Hard->Size = System::Drawing::Size(68, 17);
			this->rbtn_Hard->TabIndex = 1;
			this->rbtn_Hard->TabStop = true;
			this->rbtn_Hard->Text = L"RainMan";
			this->rbtn_Hard->UseVisualStyleBackColor = true;
			this->rbtn_Hard->CheckedChanged += gcnew System::EventHandler(this, &Form1::grp_Diff_CheckedChanged);
			//
			// rbtn_Easy
			//
			this->rbtn_Easy->AutoSize = true;
			this->rbtn_Easy->Location = System::Drawing::Point(14, 19);
			this->rbtn_Easy->Name = L"rbtn_Easy";
			this->rbtn_Easy->Size = System::Drawing::Size(58, 17);
			this->rbtn_Easy->TabIndex = 0;
			this->rbtn_Easy->TabStop = true;
			this->rbtn_Easy->Text = L"Normal";
			this->rbtn_Easy->UseVisualStyleBackColor = true;
			this->rbtn_Easy->CheckedChanged += gcnew System::EventHandler(this, &Form1::grp_Diff_CheckedChanged);
			//
			// btn_Go
			//
			this->btn_Go->Location = System::Drawing::Point(124, 188);
			this->btn_Go->Name = L"btn_Go";
			this->btn_Go->Size = System::Drawing::Size(139, 82);
			this->btn_Go->TabIndex = 1;
			this->btn_Go->Text = L"Go!";
			this->btn_Go->UseVisualStyleBackColor = true;
			this->btn_Go->Click += gcnew System::EventHandler(this, &Form1::btn_Go_Click);
			//
			// pan_Setup
			//
			this->pan_Setup->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pan_Setup->Controls->Add(this->btn_show);
			this->pan_Setup->Controls->Add(this->grp_Theme);
			this->pan_Setup->Controls->Add(this->btn_Go);
			this->pan_Setup->Controls->Add(this->grp_Diff);
			this->pan_Setup->Controls->Add(this->combo_Game);
			this->pan_Setup->Location = System::Drawing::Point(1, 6);
			this->pan_Setup->Name = L"pan_Setup";
			this->pan_Setup->Size = System::Drawing::Size(279, 280);
			this->pan_Setup->TabIndex = 0;
			//
			// btn_show
			//
			this->btn_show->Location = System::Drawing::Point(124, 153);
			this->btn_show->Name = L"btn_show";
			this->btn_show->Size = System::Drawing::Size(139, 29);
			this->btn_show->TabIndex = 5;
			this->btn_show->Text = L"Show Answers";
			this->btn_show->UseVisualStyleBackColor = true;
			this->btn_show->Click += gcnew System::EventHandler(this, &Form1::btn_show_Click);
			//
			// grp_Theme
			//
			this->grp_Theme->Controls->Add(this->rbtn_Mix_All);
			this->grp_Theme->Controls->Add(this->rbtn_Single_All);
			this->grp_Theme->Controls->Add(this->label16);
			this->grp_Theme->Controls->Add(this->label15);
			this->grp_Theme->Controls->Add(this->rbtn_Single_10);
			this->grp_Theme->Controls->Add(this->rbtn_Mix_10);
			this->grp_Theme->Controls->Add(this->shapeContainer1);
			this->grp_Theme->Location = System::Drawing::Point(13, 7);
			this->grp_Theme->Name = L"grp_Theme";
			this->grp_Theme->Size = System::Drawing::Size(253, 99);
			this->grp_Theme->TabIndex = 4;
			this->grp_Theme->TabStop = false;
			this->grp_Theme->Text = L"Theme";
			//
			// rbtn_Mix_All
			//
			this->rbtn_Mix_All->AutoSize = true;
			this->rbtn_Mix_All->Location = System::Drawing::Point(138, 68);
			this->rbtn_Mix_All->Name = L"rbtn_Mix_All";
			this->rbtn_Mix_All->Size = System::Drawing::Size(36, 17);
			this->rbtn_Mix_All->TabIndex = 10;
			this->rbtn_Mix_All->TabStop = true;
			this->rbtn_Mix_All->Text = L"All";
			this->rbtn_Mix_All->UseVisualStyleBackColor = true;
			this->rbtn_Mix_All->CheckedChanged += gcnew System::EventHandler(this, &Form1::grp_Theme_CheckedChanged);
			//
			// rbtn_Single_All
			//
			this->rbtn_Single_All->AutoSize = true;
			this->rbtn_Single_All->Location = System::Drawing::Point(14, 68);
			this->rbtn_Single_All->Name = L"rbtn_Single_All";
			this->rbtn_Single_All->Size = System::Drawing::Size(36, 17);
			this->rbtn_Single_All->TabIndex = 9;
			this->rbtn_Single_All->TabStop = true;
			this->rbtn_Single_All->Text = L"All";
			this->rbtn_Single_All->UseVisualStyleBackColor = true;
			this->rbtn_Single_All->CheckedChanged += gcnew System::EventHandler(this, &Form1::grp_Theme_CheckedChanged);
			//
			// label16
			//
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->Location = System::Drawing::Point(135, 21);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(76, 13);
			this->label16->TabIndex = 8;
			this->label16->Text = L"Mixed Game";
			//
			// label15
			//
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(11, 21);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(78, 13);
			this->label15->TabIndex = 7;
			this->label15->Text = L"Single Game";
			//
			// rbtn_Single_10
			//
			this->rbtn_Single_10->AutoSize = true;
			this->rbtn_Single_10->Location = System::Drawing::Point(14, 45);
			this->rbtn_Single_10->Name = L"rbtn_Single_10";
			this->rbtn_Single_10->Size = System::Drawing::Size(77, 17);
			this->rbtn_Single_10->TabIndex = 5;
			this->rbtn_Single_10->TabStop = true;
			this->rbtn_Single_10->Text = L"10 Rounds";
			this->rbtn_Single_10->UseVisualStyleBackColor = true;
			this->rbtn_Single_10->CheckedChanged += gcnew System::EventHandler(this, &Form1::grp_Theme_CheckedChanged);
			//
			// rbtn_Mix_10
			//
			this->rbtn_Mix_10->AutoSize = true;
			this->rbtn_Mix_10->Location = System::Drawing::Point(138, 45);
			this->rbtn_Mix_10->Name = L"rbtn_Mix_10";
			this->rbtn_Mix_10->Size = System::Drawing::Size(77, 17);
			this->rbtn_Mix_10->TabIndex = 5;
			this->rbtn_Mix_10->TabStop = true;
			this->rbtn_Mix_10->Text = L"10 Rounds";
			this->rbtn_Mix_10->UseVisualStyleBackColor = true;
			this->rbtn_Mix_10->CheckedChanged += gcnew System::EventHandler(this, &Form1::grp_Theme_CheckedChanged);
			//
			// shapeContainer1
			//
			this->shapeContainer1->Location = System::Drawing::Point(3, 16);
			this->shapeContainer1->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer1->Name = L"shapeContainer1";
			this->shapeContainer1->Shapes->AddRange(gcnew cli::array<Microsoft::VisualBasic::PowerPacks::Shape ^>(2) {
				this->rectangleShape2,
					this->rectangleShape1
			});
			this->shapeContainer1->Size = System::Drawing::Size(247, 80);
			this->shapeContainer1->TabIndex = 6;
			this->shapeContainer1->TabStop = false;
			//
			// rectangleShape2
			//
			this->rectangleShape2->BorderColor = System::Drawing::Color::LightGray;
			this->rectangleShape2->Location = System::Drawing::Point(125, 1);
			this->rectangleShape2->Name = L"rectangleShape2";
			this->rectangleShape2->Size = System::Drawing::Size(116, 74);
			//
			// rectangleShape1
			//
			this->rectangleShape1->BorderColor = System::Drawing::Color::LightGray;
			this->rectangleShape1->Location = System::Drawing::Point(5, 1);
			this->rectangleShape1->Name = L"rectangleShape1";
			this->rectangleShape1->Size = System::Drawing::Size(116, 74);
			//
			// pan_GameText
			//
			this->pan_GameText->Controls->Add(this->pan_GameScores);
			this->pan_GameText->Controls->Add(this->rtb_GameText_Que);
			this->pan_GameText->Controls->Add(this->rtb_GameText_Ans);
			this->pan_GameText->Location = System::Drawing::Point(0, 0);
			this->pan_GameText->Name = L"pan_GameText";
			this->pan_GameText->Size = System::Drawing::Size(514, 280);
			this->pan_GameText->TabIndex = 5;
			this->pan_GameText->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pan_GameText_Paint);
			//
			// pan_GameScores
			//
			this->pan_GameScores->Controls->Add(this->grpB_LastScores);
			this->pan_GameScores->Controls->Add(this->grpB_HighScores);
			this->pan_GameScores->Location = System::Drawing::Point(0, 0);
			this->pan_GameScores->Name = L"pan_GameScores";
			this->pan_GameScores->Size = System::Drawing::Size(514, 280);
			this->pan_GameScores->TabIndex = 2;
			this->pan_GameScores->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pan_GameScores_Paint);
			//
			// grpB_LastScores
			//
			this->grpB_LastScores->Controls->Add(this->tb_FinScore);
			this->grpB_LastScores->Controls->Add(this->label2);
			this->grpB_LastScores->Controls->Add(this->tb_FinQueNo);
			this->grpB_LastScores->Controls->Add(this->label1);
			this->grpB_LastScores->Location = System::Drawing::Point(6, 5);
			this->grpB_LastScores->Name = L"grpB_LastScores";
			this->grpB_LastScores->Size = System::Drawing::Size(508, 47);
			this->grpB_LastScores->TabIndex = 30;
			this->grpB_LastScores->TabStop = false;
			this->grpB_LastScores->Text = L"Last Game";
			//
			// tb_FinScore
			//
			this->tb_FinScore->Cursor = System::Windows::Forms::Cursors::Default;
			this->tb_FinScore->Location = System::Drawing::Point(158, 18);
			this->tb_FinScore->Name = L"tb_FinScore";
			this->tb_FinScore->ReadOnly = true;
			this->tb_FinScore->Size = System::Drawing::Size(42, 20);
			this->tb_FinScore->TabIndex = 35;
			//
			// label2
			//
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(114, 21);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(38, 13);
			this->label2->TabIndex = 34;
			this->label2->Text = L"Score:";
			//
			// tb_FinQueNo
			//
			this->tb_FinQueNo->Cursor = System::Windows::Forms::Cursors::Default;
			this->tb_FinQueNo->Location = System::Drawing::Point(58, 18);
			this->tb_FinQueNo->Name = L"tb_FinQueNo";
			this->tb_FinQueNo->ReadOnly = true;
			this->tb_FinQueNo->Size = System::Drawing::Size(42, 20);
			this->tb_FinQueNo->TabIndex = 36;
			//
			// label1
			//
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(15, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 13);
			this->label1->TabIndex = 33;
			this->label1->Text = L"Correct:";
			//
			// grpB_HighScores
			//
			this->grpB_HighScores->Controls->Add(this->tb_HSDiff);
			this->grpB_HighScores->Controls->Add(this->label14);
			this->grpB_HighScores->Controls->Add(this->tb_HSGame);
			this->grpB_HighScores->Controls->Add(this->label9);
			this->grpB_HighScores->Controls->Add(this->label10);
			this->grpB_HighScores->Controls->Add(this->label11);
			this->grpB_HighScores->Controls->Add(this->label12);
			this->grpB_HighScores->Controls->Add(this->label13);
			this->grpB_HighScores->Controls->Add(this->label8);
			this->grpB_HighScores->Controls->Add(this->label7);
			this->grpB_HighScores->Controls->Add(this->label6);
			this->grpB_HighScores->Controls->Add(this->label5);
			this->grpB_HighScores->Controls->Add(this->label4);
			this->grpB_HighScores->Controls->Add(this->tb_HS10);
			this->grpB_HighScores->Controls->Add(this->tb_HS9);
			this->grpB_HighScores->Controls->Add(this->tb_HS8);
			this->grpB_HighScores->Controls->Add(this->tb_HS7);
			this->grpB_HighScores->Controls->Add(this->tb_HS6);
			this->grpB_HighScores->Controls->Add(this->tb_HS5);
			this->grpB_HighScores->Controls->Add(this->tb_HS4);
			this->grpB_HighScores->Controls->Add(this->tb_HS3);
			this->grpB_HighScores->Controls->Add(this->tb_HS2);
			this->grpB_HighScores->Controls->Add(this->tb_HS1);
			this->grpB_HighScores->Controls->Add(this->label3);
			this->grpB_HighScores->Location = System::Drawing::Point(6, 58);
			this->grpB_HighScores->Name = L"grpB_HighScores";
			this->grpB_HighScores->Size = System::Drawing::Size(508, 222);
			this->grpB_HighScores->TabIndex = 29;
			this->grpB_HighScores->TabStop = false;
			this->grpB_HighScores->Text = L"High Scores";
			//
			// tb_HSDiff
			//
			this->tb_HSDiff->Cursor = System::Windows::Forms::Cursors::Default;
			this->tb_HSDiff->Location = System::Drawing::Point(91, 72);
			this->tb_HSDiff->Name = L"tb_HSDiff";
			this->tb_HSDiff->ReadOnly = true;
			this->tb_HSDiff->Size = System::Drawing::Size(82, 20);
			this->tb_HSDiff->TabIndex = 56;
			//
			// label14
			//
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(11, 76);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(81, 13);
			this->label14->TabIndex = 55;
			this->label14->Text = L"Game Difficulty:";
			//
			// tb_HSGame
			//
			this->tb_HSGame->Cursor = System::Windows::Forms::Cursors::Default;
			this->tb_HSGame->Location = System::Drawing::Point(91, 13);
			this->tb_HSGame->Name = L"tb_HSGame";
			this->tb_HSGame->ReadOnly = true;
			this->tb_HSGame->Size = System::Drawing::Size(408, 20);
			this->tb_HSGame->TabIndex = 54;
			//
			// label9
			//
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(355, 170);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(19, 13);
			this->label9->TabIndex = 53;
			this->label9->Text = L"10";
			//
			// label10
			//
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(355, 147);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(13, 13);
			this->label10->TabIndex = 52;
			this->label10->Text = L"9";
			//
			// label11
			//
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(355, 124);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(13, 13);
			this->label11->TabIndex = 51;
			this->label11->Text = L"8";
			//
			// label12
			//
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(355, 101);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(13, 13);
			this->label12->TabIndex = 50;
			this->label12->Text = L"7";
			//
			// label13
			//
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(355, 78);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(13, 13);
			this->label13->TabIndex = 49;
			this->label13->Text = L"6";
			//
			// label8
			//
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(278, 170);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(13, 13);
			this->label8->TabIndex = 48;
			this->label8->Text = L"5";
			//
			// label7
			//
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(278, 147);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(13, 13);
			this->label7->TabIndex = 47;
			this->label7->Text = L"4";
			//
			// label6
			//
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(278, 124);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(13, 13);
			this->label6->TabIndex = 46;
			this->label6->Text = L"3";
			//
			// label5
			//
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(278, 101);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(13, 13);
			this->label5->TabIndex = 45;
			this->label5->Text = L"2";
			//
			// label4
			//
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(278, 78);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(13, 13);
			this->label4->TabIndex = 44;
			this->label4->Text = L"1";
			//
			// tb_HS10
			//
			this->tb_HS10->Cursor = System::Windows::Forms::Cursors::Default;
			this->tb_HS10->Location = System::Drawing::Point(374, 168);
			this->tb_HS10->Name = L"tb_HS10";
			this->tb_HS10->ReadOnly = true;
			this->tb_HS10->Size = System::Drawing::Size(42, 20);
			this->tb_HS10->TabIndex = 43;
			//
			// tb_HS9
			//
			this->tb_HS9->Cursor = System::Windows::Forms::Cursors::Default;
			this->tb_HS9->Location = System::Drawing::Point(374, 145);
			this->tb_HS9->Name = L"tb_HS9";
			this->tb_HS9->ReadOnly = true;
			this->tb_HS9->Size = System::Drawing::Size(42, 20);
			this->tb_HS9->TabIndex = 42;
			//
			// tb_HS8
			//
			this->tb_HS8->Cursor = System::Windows::Forms::Cursors::Default;
			this->tb_HS8->Location = System::Drawing::Point(374, 122);
			this->tb_HS8->Name = L"tb_HS8";
			this->tb_HS8->ReadOnly = true;
			this->tb_HS8->Size = System::Drawing::Size(42, 20);
			this->tb_HS8->TabIndex = 41;
			//
			// tb_HS7
			//
			this->tb_HS7->Cursor = System::Windows::Forms::Cursors::Default;
			this->tb_HS7->Location = System::Drawing::Point(374, 99);
			this->tb_HS7->Name = L"tb_HS7";
			this->tb_HS7->ReadOnly = true;
			this->tb_HS7->Size = System::Drawing::Size(42, 20);
			this->tb_HS7->TabIndex = 40;
			//
			// tb_HS6
			//
			this->tb_HS6->Cursor = System::Windows::Forms::Cursors::Default;
			this->tb_HS6->Location = System::Drawing::Point(374, 76);
			this->tb_HS6->Name = L"tb_HS6";
			this->tb_HS6->ReadOnly = true;
			this->tb_HS6->Size = System::Drawing::Size(42, 20);
			this->tb_HS6->TabIndex = 39;
			//
			// tb_HS5
			//
			this->tb_HS5->Cursor = System::Windows::Forms::Cursors::Default;
			this->tb_HS5->Location = System::Drawing::Point(297, 168);
			this->tb_HS5->Name = L"tb_HS5";
			this->tb_HS5->ReadOnly = true;
			this->tb_HS5->Size = System::Drawing::Size(42, 20);
			this->tb_HS5->TabIndex = 38;
			//
			// tb_HS4
			//
			this->tb_HS4->Cursor = System::Windows::Forms::Cursors::Default;
			this->tb_HS4->Location = System::Drawing::Point(297, 145);
			this->tb_HS4->Name = L"tb_HS4";
			this->tb_HS4->ReadOnly = true;
			this->tb_HS4->Size = System::Drawing::Size(42, 20);
			this->tb_HS4->TabIndex = 37;
			//
			// tb_HS3
			//
			this->tb_HS3->Cursor = System::Windows::Forms::Cursors::Default;
			this->tb_HS3->Location = System::Drawing::Point(297, 122);
			this->tb_HS3->Name = L"tb_HS3";
			this->tb_HS3->ReadOnly = true;
			this->tb_HS3->Size = System::Drawing::Size(42, 20);
			this->tb_HS3->TabIndex = 36;
			//
			// tb_HS2
			//
			this->tb_HS2->Cursor = System::Windows::Forms::Cursors::Default;
			this->tb_HS2->Location = System::Drawing::Point(297, 99);
			this->tb_HS2->Name = L"tb_HS2";
			this->tb_HS2->ReadOnly = true;
			this->tb_HS2->Size = System::Drawing::Size(42, 20);
			this->tb_HS2->TabIndex = 35;
			//
			// tb_HS1
			//
			this->tb_HS1->Cursor = System::Windows::Forms::Cursors::Default;
			this->tb_HS1->Location = System::Drawing::Point(297, 76);
			this->tb_HS1->Name = L"tb_HS1";
			this->tb_HS1->ReadOnly = true;
			this->tb_HS1->Size = System::Drawing::Size(42, 20);
			this->tb_HS1->TabIndex = 34;
			//
			// label3
			//
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(11, 16);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(69, 13);
			this->label3->TabIndex = 33;
			this->label3->Text = L"Game Name:";
			//
			// rtb_GameText_Que
			//
			this->rtb_GameText_Que->Location = System::Drawing::Point(9, 6);
			this->rtb_GameText_Que->Name = L"rtb_GameText_Que";
			this->rtb_GameText_Que->ReadOnly = true;
			this->rtb_GameText_Que->Size = System::Drawing::Size(501, 236);
			this->rtb_GameText_Que->TabIndex = 0;
			this->rtb_GameText_Que->TabStop = false;
			this->rtb_GameText_Que->Text = L"";
			this->rtb_GameText_Que->TextChanged += gcnew System::EventHandler(this, &Form1::rtb_GameText_Que_TextChanged);
			//
			// rtb_GameText_Ans
			//
			this->rtb_GameText_Ans->Location = System::Drawing::Point(9, 250);
			this->rtb_GameText_Ans->Name = L"rtb_GameText_Ans";
			this->rtb_GameText_Ans->Size = System::Drawing::Size(502, 22);
			this->rtb_GameText_Ans->TabIndex = 1;
			this->rtb_GameText_Ans->TabStop = false;
			this->rtb_GameText_Ans->Text = L"";
			//
			// pan_GameRadio
			//
			this->pan_GameRadio->Controls->Add(this->pan_GameText);
			this->pan_GameRadio->Controls->Add(this->rtb_GameRadio_Que);
			this->pan_GameRadio->Controls->Add(this->grp_Options);
			this->pan_GameRadio->Location = System::Drawing::Point(286, 6);
			this->pan_GameRadio->Name = L"pan_GameRadio";
			this->pan_GameRadio->Size = System::Drawing::Size(514, 280);
			this->pan_GameRadio->TabIndex = 6;
			//
			// rtb_GameRadio_Que
			//
			this->rtb_GameRadio_Que->Location = System::Drawing::Point(4, 6);
			this->rtb_GameRadio_Que->Name = L"rtb_GameRadio_Que";
			this->rtb_GameRadio_Que->ReadOnly = true;
			this->rtb_GameRadio_Que->Size = System::Drawing::Size(176, 265);
			this->rtb_GameRadio_Que->TabIndex = 1;
			this->rtb_GameRadio_Que->TabStop = false;
			this->rtb_GameRadio_Que->Text = L"";
			//
			// grp_Options
			//
			this->grp_Options->Controls->Add(this->rtxt_option5);
			this->grp_Options->Controls->Add(this->rtxt_option4);
			this->grp_Options->Controls->Add(this->rtxt_option3);
			this->grp_Options->Controls->Add(this->rtxt_option2);
			this->grp_Options->Controls->Add(this->rtxt_option1);
			this->grp_Options->Controls->Add(this->rbtn_option5);
			this->grp_Options->Controls->Add(this->rbtn_option4);
			this->grp_Options->Controls->Add(this->rbtn_option3);
			this->grp_Options->Controls->Add(this->rbtn_option2);
			this->grp_Options->Controls->Add(this->rbtn_option1);
			this->grp_Options->Location = System::Drawing::Point(186, 3);
			this->grp_Options->Name = L"grp_Options";
			this->grp_Options->Size = System::Drawing::Size(320, 274);
			this->grp_Options->TabIndex = 0;
			this->grp_Options->TabStop = false;
			this->grp_Options->Text = L"Options";
			this->grp_Options->Enter += gcnew System::EventHandler(this, &Form1::grp_Options_Enter);
			//
			// rtxt_option5
			//
			this->rtxt_option5->BackColor = System::Drawing::SystemColors::Control;
			this->rtxt_option5->Location = System::Drawing::Point(27, 222);
			this->rtxt_option5->Multiline = true;
			this->rtxt_option5->Name = L"rtxt_option5";
			this->rtxt_option5->ReadOnly = true;
			this->rtxt_option5->Size = System::Drawing::Size(287, 46);
			this->rtxt_option5->TabIndex = 9;
			this->rtxt_option5->Enter += gcnew System::EventHandler(this, &Form1::rtxt_option5_Enter);
			//
			// rtxt_option4
			//
			this->rtxt_option4->BackColor = System::Drawing::SystemColors::Control;
			this->rtxt_option4->Location = System::Drawing::Point(27, 170);
			this->rtxt_option4->Multiline = true;
			this->rtxt_option4->Name = L"rtxt_option4";
			this->rtxt_option4->ReadOnly = true;
			this->rtxt_option4->Size = System::Drawing::Size(287, 46);
			this->rtxt_option4->TabIndex = 8;
			this->rtxt_option4->Enter += gcnew System::EventHandler(this, &Form1::rtxt_option4_Enter);
			//
			// rtxt_option3
			//
			this->rtxt_option3->BackColor = System::Drawing::SystemColors::Control;
			this->rtxt_option3->Location = System::Drawing::Point(27, 118);
			this->rtxt_option3->Multiline = true;
			this->rtxt_option3->Name = L"rtxt_option3";
			this->rtxt_option3->ReadOnly = true;
			this->rtxt_option3->Size = System::Drawing::Size(287, 46);
			this->rtxt_option3->TabIndex = 7;
			this->rtxt_option3->Enter += gcnew System::EventHandler(this, &Form1::rtxt_option3_Enter);
			//
			// rtxt_option2
			//
			this->rtxt_option2->BackColor = System::Drawing::SystemColors::Control;
			this->rtxt_option2->Location = System::Drawing::Point(27, 66);
			this->rtxt_option2->Multiline = true;
			this->rtxt_option2->Name = L"rtxt_option2";
			this->rtxt_option2->ReadOnly = true;
			this->rtxt_option2->Size = System::Drawing::Size(287, 46);
			this->rtxt_option2->TabIndex = 6;
			this->rtxt_option2->Enter += gcnew System::EventHandler(this, &Form1::rtxt_option2_Enter);
			//
			// rtxt_option1
			//
			this->rtxt_option1->BackColor = System::Drawing::SystemColors::Control;
			this->rtxt_option1->Location = System::Drawing::Point(27, 14);
			this->rtxt_option1->Multiline = true;
			this->rtxt_option1->Name = L"rtxt_option1";
			this->rtxt_option1->ReadOnly = true;
			this->rtxt_option1->Size = System::Drawing::Size(287, 46);
			this->rtxt_option1->TabIndex = 5;
			this->rtxt_option1->Enter += gcnew System::EventHandler(this, &Form1::rtxt_option1_Enter);
			//
			// rbtn_option5
			//
			this->rbtn_option5->AutoSize = true;
			this->rbtn_option5->Location = System::Drawing::Point(7, 238);
			this->rbtn_option5->Name = L"rbtn_option5";
			this->rbtn_option5->Size = System::Drawing::Size(14, 13);
			this->rbtn_option5->TabIndex = 4;
			this->rbtn_option5->TabStop = true;
			this->rbtn_option5->UseVisualStyleBackColor = true;
			//
			// rbtn_option4
			//
			this->rbtn_option4->AutoSize = true;
			this->rbtn_option4->Location = System::Drawing::Point(7, 186);
			this->rbtn_option4->Name = L"rbtn_option4";
			this->rbtn_option4->Size = System::Drawing::Size(14, 13);
			this->rbtn_option4->TabIndex = 3;
			this->rbtn_option4->TabStop = true;
			this->rbtn_option4->UseVisualStyleBackColor = true;
			//
			// rbtn_option3
			//
			this->rbtn_option3->AutoSize = true;
			this->rbtn_option3->Location = System::Drawing::Point(7, 134);
			this->rbtn_option3->Name = L"rbtn_option3";
			this->rbtn_option3->Size = System::Drawing::Size(14, 13);
			this->rbtn_option3->TabIndex = 2;
			this->rbtn_option3->TabStop = true;
			this->rbtn_option3->UseVisualStyleBackColor = true;
			//
			// rbtn_option2
			//
			this->rbtn_option2->AutoSize = true;
			this->rbtn_option2->Location = System::Drawing::Point(7, 81);
			this->rbtn_option2->Name = L"rbtn_option2";
			this->rbtn_option2->Size = System::Drawing::Size(14, 13);
			this->rbtn_option2->TabIndex = 1;
			this->rbtn_option2->TabStop = true;
			this->rbtn_option2->UseVisualStyleBackColor = true;
			//
			// rbtn_option1
			//
			this->rbtn_option1->AutoSize = true;
			this->rbtn_option1->Location = System::Drawing::Point(7, 29);
			this->rbtn_option1->Name = L"rbtn_option1";
			this->rbtn_option1->Size = System::Drawing::Size(14, 13);
			this->rbtn_option1->TabIndex = 0;
			this->rbtn_option1->TabStop = true;
			this->rbtn_option1->UseVisualStyleBackColor = true;
			//
			// btn_NextQue
			//
			this->btn_NextQue->Location = System::Drawing::Point(800, 46);
			this->btn_NextQue->Name = L"btn_NextQue";
			this->btn_NextQue->Size = System::Drawing::Size(41, 214);
			this->btn_NextQue->TabIndex = 6;
			this->btn_NextQue->TabStop = false;
			this->btn_NextQue->Text = L"Next";
			this->btn_NextQue->UseVisualStyleBackColor = true;
			this->btn_NextQue->Click += gcnew System::EventHandler(this, &Form1::btn_NextQue_Click);
			//
			// tb_QueNo
			//
			this->tb_QueNo->Cursor = System::Windows::Forms::Cursors::Default;
			this->tb_QueNo->Location = System::Drawing::Point(800, 14);
			this->tb_QueNo->Name = L"tb_QueNo";
			this->tb_QueNo->ReadOnly = true;
			this->tb_QueNo->Size = System::Drawing::Size(41, 20);
			this->tb_QueNo->TabIndex = 8;
			this->tb_QueNo->TabStop = false;
			//
			// pgbr_Timer
			//
			this->pgbr_Timer->Location = System::Drawing::Point(289, 289);
			this->pgbr_Timer->Name = L"pgbr_Timer";
			this->pgbr_Timer->Size = System::Drawing::Size(501, 20);
			this->pgbr_Timer->TabIndex = 10;
			//
			// timer1
			//
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			//
			// lbl_secsLeft
			//
			this->lbl_secsLeft->AutoSize = true;
			this->lbl_secsLeft->Location = System::Drawing::Point(797, 292);
			this->lbl_secsLeft->Name = L"lbl_secsLeft";
			this->lbl_secsLeft->Size = System::Drawing::Size(36, 13);
			this->lbl_secsLeft->TabIndex = 11;
			this->lbl_secsLeft->Text = L"70/70";
			//
			// Form1
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(848, 314);
			this->Controls->Add(this->pan_GameRadio);
			this->Controls->Add(this->lbl_secsLeft);
			this->Controls->Add(this->pan_Setup);
			this->Controls->Add(this->tb_QueNo);
			this->Controls->Add(this->pgbr_Timer);
			this->Controls->Add(this->btn_NextQue);
			this->MaximumSize = System::Drawing::Size(864, 353);
			this->MinimumSize = System::Drawing::Size(864, 353);
			this->Name = L"Form1";
			this->Text = L"Brainer";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->grp_Diff->ResumeLayout(false);
			this->grp_Diff->PerformLayout();
			this->pan_Setup->ResumeLayout(false);
			this->grp_Theme->ResumeLayout(false);
			this->grp_Theme->PerformLayout();
			this->pan_GameText->ResumeLayout(false);
			this->pan_GameScores->ResumeLayout(false);
			this->grpB_LastScores->ResumeLayout(false);
			this->grpB_LastScores->PerformLayout();
			this->grpB_HighScores->ResumeLayout(false);
			this->grpB_HighScores->PerformLayout();
			this->pan_GameRadio->ResumeLayout(false);
			this->grp_Options->ResumeLayout(false);
			this->grp_Options->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	private:
		System::Void label1_Click(System::Object ^ sender, System::EventArgs ^ e)
		{
		}
		System::Void grp_Theme_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
		{
			this->PopulateHighScores();
			this->SetGameSelectionEnablement();
		}
		System::Void btn_Go_Click(System::Object ^ sender, System::EventArgs ^ e)
		{
			this->StartGame();
		}
		System::Void Form1_Load(System::Object ^ sender, System::EventArgs ^ e)
		{
		}
		System::Void btn_NextQue_Click(System::Object ^ sender, System::EventArgs ^ e)
		{
			this->QueEnd();
		}
		System::Void timer1_Tick(System::Object ^ sender, System::EventArgs ^ e)
		{
			if (mi_CurrentQue >= this->mp_Rounds->GetNumberOfRounds()) {
				this->timer1->Enabled = false;
				this->FinaliseGame(true);
			}
			else {
				try {
					++mui_TimerTicks;
					if (this->pgbr_Timer->Value <= 99) {
						int i_Secs;
						int iret = this->mp_GameContainer->GetTimeLimit(&i_Secs, this->mp_Rounds->GetRound(mi_CurrentQue).mi_GameIndex);
						if (iret != RET_OK) {
							ThrowError(iret);
						}
						int diff = (mui_TimerTicks * 100) / i_Secs - this->pgbr_Timer->Value;
						if (diff >= 10) {
							if (this->pgbr_Timer->Value + diff > 100) {
								this->pgbr_Timer->Value = 100;
							}
							else {
								this->pgbr_Timer->Value += diff;
							}
						}
						populateTimeRemainingLabel(i_Secs, i_Secs - mui_TimerTicks);
					}
					if (this->pgbr_Timer->Value >= 100)
						this->QueEnd();
				}
				catch (TAppException _AppExp) {
					this->FinaliseGame(false);
					String ^ str = gcnew String(_AppExp.GetMsg());
					MessageBox::Show(str);
				}
			}
		}
		System::Void grp_Diff_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
		{
			this->PopulateHighScores();
		}
		System::Void combo_Game_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
		{
			this->PopulateHighScores();
		}
		System::Void Form1_FormClosing(System::Object ^ sender, System::Windows::Forms::FormClosingEventArgs ^ e)
		{
			this->saveToIni();
		}
		System::Void grp_Options_Enter(System::Object ^ sender, System::EventArgs ^ e)
		{
		}
		System::Void pan_GameScores_Paint(System::Object ^ sender, System::Windows::Forms::PaintEventArgs ^ e)
		{
		}
		System::Void rtb_GameText_Que_TextChanged(System::Object ^ sender, System::EventArgs ^ e)
		{
		}
		System::Void pan_GameText_Paint(System::Object ^ sender, System::Windows::Forms::PaintEventArgs ^ e)
		{
		}
		System::Void btn_show_Click(System::Object ^ sender, System::EventArgs ^ e)
		{

			char* pch_QueString = new char[iMaxQALen];
			int i_GameIndex = this->getSelectedGameIndex();

			int i_numQuestions = this->mp_GameContainer->GetNumberOfQuestions(i_GameIndex);
			TGameQuestions* p_GameQuestions = new TGameQuestions(i_numQuestions);

			this->mp_GameContainer->Reset(i_GameIndex);
			for (int i = 0; i < i_numQuestions; ++i) {
				int iret = this->mp_GameContainer->GetQA(pch_QueString, i_GameIndex);
				if (iret != RET_OK) {
					ThrowError(iret);
				}
				std::vector<std::vector<char> > AnswerStrings;
				int i_CorrectAns = copyRadioQuestionsAndAnswerStrings(pch_QueString, p_GameQuestions->mp_GameQuestion[i].mpch_QueString, p_GameQuestions->mp_GameQuestion[i].mpch_ActualAnsString, AnswerStrings);
			}

			GameSummary SummaryForm(p_GameQuestions, true);
			SummaryForm.ShowDialog();

			delete[] pch_QueString;
			delete p_GameQuestions;
		}
		System::Void rtxt_option1_Enter(System::Object ^ sender, System::EventArgs ^ e)
		{
			this->rbtn_option1->Checked = true;
		}
		System::Void rtxt_option2_Enter(System::Object ^ sender, System::EventArgs ^ e)
		{
			this->rbtn_option2->Checked = true;
		}
		System::Void rtxt_option3_Enter(System::Object ^ sender, System::EventArgs ^ e)
		{
			this->rbtn_option3->Checked = true;
		}
		System::Void rtxt_option4_Enter(System::Object ^ sender, System::EventArgs ^ e)
		{
			this->rbtn_option4->Checked = true;
		}
		System::Void rtxt_option5_Enter(System::Object ^ sender, System::EventArgs ^ e)
		{
			this->rbtn_option5->Checked = true;
		}
	};

	void Form1::StartGame()
	{
		RegisterHotKey((HWND)this->Handle.ToPointer(), 1, 0, 0x0D);
		try {
			mb_GameUpdate = true;
			mi_CurrentQue = 0;
			this->InitGame();
			this->InitQue();
		}
		catch (TAppException _AppExp) {
			this->FinaliseGame(false);
			String ^ str = gcnew String(_AppExp.GetMsg());
			MessageBox::Show(str);
		}
	}

	int Form1::copyQuestionString(char* _pch_QueStringSource, char* _pch_QueStringDest)
	{
		if (_pch_QueStringSource[0] == '\0' || !strncmp(_pch_QueStringSource, QD, strlen(QD))) {
			throw TAppException(TAppException::APPEXCEPTION_EMPTYQUESTRING, "Empty Question String");
		}
		int i_cnt = 0;
		while (strncmp(&_pch_QueStringSource[i_cnt], QD, strlen(QD)) && strncmp(&_pch_QueStringSource[i_cnt], "\0", 1) && i_cnt < iMaxQALen) {
			_pch_QueStringDest[i_cnt] = _pch_QueStringSource[i_cnt];
			++i_cnt;
		}
		_pch_QueStringDest[i_cnt] = '\0';
		return i_cnt;
	};

	int Form1::copyRadioQuestionsAndAnswerStrings(char* _pch_QueStringSource, char* _pch_QueStringDest, char* _pch_ActualAnswerDest, std::vector<std::vector<char> >& AnswerStrings)
	{
		int i_cnt = 0;
		for (int i = 0; i < 6; i++) {
			if (i > 0) {
				i_cnt += strlen(QD);
				AnswerStrings.push_back(std::vector<char>());
			}
			int i_cnt2 = 0;
			while (strncmp(&_pch_QueStringSource[i_cnt], QD, strlen(QD)) && strncmp(&_pch_QueStringSource[i_cnt], "\0", 1) && i_cnt < iMaxQALen) {
				if (i == 0) {
					_pch_QueStringDest[i_cnt] = _pch_QueStringSource[i_cnt];
				}
				else {
					AnswerStrings[i - 1].push_back(_pch_QueStringSource[i_cnt]);
				}
				++i_cnt;
			}
			if (i == 0) {
				_pch_QueStringDest[i_cnt] = '\0';
			}
			else {
				AnswerStrings[i - 1].push_back('\0');
			}
			if ((i < 6 && !strncmp(&_pch_QueStringSource[i_cnt], "\0", 1)) || i_cnt >= iMaxQALen) {
				throw TAppException(TAppException::APPEXCEPTION_NOANSSTRING, "No Answer");
			}
		}
		i_cnt += strlen(QD);
		int i_CorrectAns = atoi(&_pch_QueStringSource[i_cnt]);
		if (i_CorrectAns < 1 || i_CorrectAns > 5) {
			throw TAppException(TAppException::APPEXCEPTION_ANSRADIOOUTRANGE, "Answer out of range.");
		}
		strcpy(_pch_ActualAnswerDest, &AnswerStrings[i_CorrectAns - 1][0]);
		return i_CorrectAns;
	};

	void Form1::QueEnd()
	{
		try {
			int i_PercentToAns = this->pgbr_Timer->Value;
			int i_GameType;
			int iret = this->mp_GameContainer->GetGameType(&i_GameType, this->mp_Rounds->GetRound(mi_CurrentQue).mi_GameIndex);
			if (iret != RET_OK) {
				ThrowError(iret);
			}
			if (i_GameType == TEXT) {
				this->ValidateTextAns(i_PercentToAns, false);
			}
			else if (i_GameType == TEXTNUM) {
				this->ValidateTextAns(i_PercentToAns, true);
			}
			else if (i_GameType == RADIO) {
				this->ValidateRadioAns(i_PercentToAns);
			}
			else {
				throw TAppException(TAppException::APPEXCEPTION_NOSUCHGAMETYPE, "No such game type");
			}
			++mi_CurrentQue;
			this->UpdateScoreBox(false);
			if (mi_CurrentQue >= this->mp_Rounds->GetNumberOfRounds()) {
				this->FinaliseGame(true);
			}
			else {
				this->InitQue();
			}
		}
		catch (TAppException _AppExp) {
			this->FinaliseGame(false);
			String ^ str = gcnew String(_AppExp.GetMsg());
			MessageBox::Show(str);
		}
	}

	void Form1::resetGames()
	{
		for (int i = 0; i < this->mp_GameContainer->GetNumberOfGames(); ++i) {
			this->mp_GameContainer->Reset(i);
		}
	}

	void Form1::InitGame()
	{
		mb_GameFinialised = false;
		this->pan_Setup->Enabled = false;
		this->btn_NextQue->Show();
		this->pgbr_Timer->Show();
		this->lbl_secsLeft->Show();
		this->tb_QueNo->Show();

		this->rbtn_option1->Checked = false;
		this->rbtn_option2->Checked = false;
		this->rbtn_option3->Checked = false;
		this->rbtn_option4->Checked = false;
		this->rbtn_option5->Checked = false;

		this->rtb_GameText_Ans->Clear();

		if (mp_GameQuestions) {
			delete mp_GameQuestions;
		}

		resetGames();

		if (this->rbtn_Single_10->Checked) {
			this->InitSingle10Game();
		}
		else if (this->rbtn_Mix_10->Checked) {
			this->InitMix10Game();
		}
		else if (this->rbtn_Single_All->Checked) {
			this->InitSingleAllGame();
		}
		else if (this->rbtn_Mix_All->Checked) {
			this->InitMixAllGame();
		}
		mp_GameQuestions = new TGameQuestions(this->mp_Rounds->GetNumberOfRounds());
		this->UpdateScoreBox(false);
	}

	void Form1::InitSingle10Game()
	{
		this->mp_Rounds->InitialiseRounds(mi_NoRounds);
		int i_GameIndex = this->getSelectedGameIndex();

		for (int i = 0; i < mi_NoRounds; i++) {
			this->mp_Rounds->GetRound(i).mi_GameIndex = i_GameIndex;
		}
	}

	void Form1::InitMix10Game()
	{
		this->mp_Rounds->InitialiseRounds(mi_NoRounds);
		int i_NoGames;
		i_NoGames = this->mp_GameContainer->GetNumberOfGames();
		int i_noTrivia = 0;
		for (int i = 0; i < mi_NoRounds; i++) {
			int i_GameIndex;
			while (true) {
				TNumeric::RandomInt(i_NoGames, &i_GameIndex);
				string GameName;
				mp_GameContainer->GetGameName(GameName, i_GameIndex);
				if (GameName.find(TRIVAPRE) != string::npos && i_noTrivia < mi_NoRounds / 2) {
					i_noTrivia++;
					break;
				}
				else if (GameName.find(TRIVAPRE) == string::npos) {
					if (i + 1 - i_noTrivia < mi_NoRounds / 2 || i == mi_NoRounds - 1) {
						break;
					}
				}
			}
			this->mp_Rounds->GetRound(i).mi_GameIndex = i_GameIndex;
		}
	}

	void Form1::InitSingleAllGame()
	{
		int i_GameIndex = this->getSelectedGameIndex();
		int i_NoRounds = this->mp_GameContainer->GetNumberOfQuestions(i_GameIndex);
		this->mp_Rounds->InitialiseRounds(i_NoRounds);
		for (int i = 0; i < i_NoRounds; i++) {
			this->mp_Rounds->GetRound(i).mi_GameIndex = i_GameIndex;
		}
	}

	int myrandom(int i)
	{
		int i_rand;
		TNumeric::RandomInt(RAND_MAX, &i_rand);
		return i_rand % i;
	}

	void Form1::InitMixAllGame()
	{
		int i_NoGames = this->mp_GameContainer->GetNumberOfGames();
		this->mp_Rounds->InitialiseRounds(i_NoGames);
		vector<int> gameIndices = vector<int>();
		for (int i = 0; i < i_NoGames; ++i) {
			gameIndices.push_back(i);
		}
		std::random_shuffle(gameIndices.begin(), gameIndices.end(), myrandom);
		int round = 0;
		for (std::vector<int>::iterator it = gameIndices.begin(); it != gameIndices.end(); ++it) {
			this->mp_Rounds->GetRound(round).mi_GameIndex = *it;
			round++;
		}
	}

	unsigned int Form1::getSelectedGameIndex()
	{
		int i_GameIndex;
		String ^ s = this->combo_Game->Text;
		IntPtr ip = Marshal::StringToHGlobalAnsi(s);
		const char* str = static_cast<const char*>(ip.ToPointer());

		if (strcmp(str, "Select Game") == 0) {
			throw TAppException(TAppException::APPEXCEPTION_NOGAMESELECTED, "Select a Game!");
		}

		int iret = this->mp_Games->GetIndex(&i_GameIndex, string(str));
		if (iret != RET_OK) {
			ThrowError(iret);
		}
		return i_GameIndex;
	}

	void Form1::InitQue()
	{
		int i_Diff;
		if (this->rbtn_Easy->Checked)
			i_Diff = EASY;
		else if (this->rbtn_Med->Checked)
			i_Diff = MEDIUM;
		else
			i_Diff = HARD;
		int iret = this->mp_GameContainer->SetDiff(i_Diff, this->mp_Rounds->GetRound(mi_CurrentQue).mi_GameIndex);
		if (iret != RET_OK) {
			ThrowError(iret);
		}
		int i_GameType;
		iret = this->mp_GameContainer->GetGameType(&i_GameType, this->mp_Rounds->GetRound(mi_CurrentQue).mi_GameIndex);
		if (iret != RET_OK) {
			ThrowError(iret);
		}
		iret = this->mp_GameContainer->GetQA(mch_CurrentQueString, this->mp_Rounds->GetRound(mi_CurrentQue).mi_GameIndex);
		if (iret != RET_OK) {
			ThrowError(iret);
		}
		if (i_GameType == TEXT || i_GameType == TEXTNUM) {
			this->rtb_GameText_Ans->Clear();
			this->pan_GameScores->Hide();
			this->pan_GameText->Show();
			this->pan_GameText->BringToFront();
		}
		else if (i_GameType == RADIO) {
			this->pan_GameScores->Hide();
			this->pan_GameText->Hide();
			this->pan_GameRadio->Show();
			this->pan_GameRadio->BringToFront();
			this->rbtn_option1->Checked = false;
			this->rbtn_option2->Checked = false;
			this->rbtn_option3->Checked = false;
			this->rbtn_option4->Checked = false;
			this->rbtn_option5->Checked = false;
		}
		else {
			throw TAppException(TAppException::APPEXCEPTION_NOSUCHGAMETYPE, "No such game type");
		}
		this->rtb_GameText_Ans->Select();
		this->SetupQue(i_GameType);

		int i_Secs;
		iret = this->mp_GameContainer->GetTimeLimit(&i_Secs, this->mp_Rounds->GetRound(mi_CurrentQue).mi_GameIndex);
		if (iret != RET_OK) {
			ThrowError(iret);
		}
		if (this->rbtn_Med->Checked)
			i_Secs = (int)((float)i_Secs * 1.0);
		else if (this->rbtn_Hard->Checked)
			i_Secs = (int)((float)i_Secs * 1.0);
		mui_TimerTicks = 0;
		populateTimeRemainingLabel(i_Secs, i_Secs);
		this->pgbr_Timer->Value = 0;
		this->timer1->Interval = 1000;
		this->timer1->Enabled = true;
	}

	void Form1::populateTimeRemainingLabel(unsigned int _ui_TotalTime, unsigned int _ui_TimeElapsed)
	{
		char pc_buff[16];
		sprintf_s(pc_buff, 16, "%d/%d", _ui_TimeElapsed, _ui_TotalTime);
		lbl_secsLeft->Text = gcnew String(pc_buff);
	}

	void Form1::saveToIni()
	{
		char pc_IniFilePath[MAX_PATH];
		TFileUtils::CreateCWDPath(pc_IniFilePath, MAX_PATH, INI_FILENAME);
		TIniFile IniFile(pc_IniFilePath, INI_SECTION_GUISETTINGS);
		int i_SetValue = 0;
		if (rbtn_Mix_All->Checked) {
			i_SetValue = 1;
		}
		else if (rbtn_Single_10->Checked) {
			i_SetValue = 2;
		}
		else if (rbtn_Single_All->Checked) {
			i_SetValue = 3;
		}
		IniFile.SetInt(INI_GUISETTINGS_KEY_THEME, i_SetValue);
		IniFile.SetInt(INI_GUISETTINGS_KEY_GAMEINDEX, combo_Game->SelectedIndex);
		i_SetValue = 0;
		if (rbtn_Med->Checked) {
			i_SetValue = 1;
		}
		else if (rbtn_Hard->Checked) {
			i_SetValue = 2;
		}
		IniFile.SetInt(INI_GUISETTINGS_KEY_DIFFICULTY, i_SetValue);
	}

	void Form1::loadFromIni1()
	{
		char pc_IniFilePath[MAX_PATH];
		TFileUtils::CreateCWDPath(pc_IniFilePath, MAX_PATH, INI_FILENAME);
		TIniFile IniFile(pc_IniFilePath, INI_SECTION_GUISETTINGS);
		switch (IniFile.GetInt(INI_GUISETTINGS_KEY_THEME, 0)) {
		case 0:
			rbtn_Mix_10->Checked = true;
			break;
		case 1:
			rbtn_Mix_All->Checked = true;
			break;
		case 2:
			rbtn_Single_10->Checked = true;
			break;
		case 3:
			rbtn_Single_All->Checked = true;
			break;
		}
	}

	void Form1::loadFromIni2()
	{
		char pc_IniFilePath[MAX_PATH];
		TFileUtils::CreateCWDPath(pc_IniFilePath, MAX_PATH, INI_FILENAME);
		TIniFile IniFile(pc_IniFilePath, INI_SECTION_GUISETTINGS);
		int i_selectedIndex = IniFile.GetInt(INI_GUISETTINGS_KEY_GAMEINDEX, 0);
		if (i_selectedIndex < combo_Game->Items->Count) {
			combo_Game->SelectedIndex = i_selectedIndex;
		}
		else {
			combo_Game->SelectedIndex = 0;
		}
		switch (IniFile.GetInt(INI_GUISETTINGS_KEY_DIFFICULTY, 0)) {
		case 0:
			rbtn_Easy->Checked = true;
			break;
		case 1:
			rbtn_Med->Checked = true;
			break;
		case 2:
			rbtn_Hard->Checked = true;
			break;
		}
	}

	void Form1::SetupQue(int _i_GameType)
	{
		char* pc_Que;
		pc_Que = new char[iMaxQALen];
		if (mch_CurrentQueString[0] == '\0' || !strncmp(mch_CurrentQueString, QD, strlen(QD))) {
			delete[] pc_Que;
			throw TAppException(TAppException::APPEXCEPTION_EMPTYQUESTRING, "Empty Question String");
		}
		int i_cnt = 0;
		while (strncmp(&mch_CurrentQueString[i_cnt], QD, strlen(QD)) && strncmp(&mch_CurrentQueString[i_cnt], "\0", 1) && i_cnt < iMaxQALen) {
			pc_Que[i_cnt] = mch_CurrentQueString[i_cnt];
			++i_cnt;
		}
		pc_Que[i_cnt] = '\0';
		if (!strncmp(&mch_CurrentQueString[i_cnt], "\0", 1)) {
			delete[] pc_Que;
			throw TAppException(TAppException::APPEXCEPTION_NOANSSTRING, "No Answer String");
		}
		else if (i_cnt >= iMaxQALen) {
			delete[] pc_Que;
			throw TAppException(TAppException::APPEXCEPTION_NOANSSTRING, "No Answer String");
		}
		else {
			i_cnt += strlen(QD) - 1;
		}
		String ^ s = gcnew String(pc_Que);
		delete[] pc_Que;

		if (_i_GameType == TEXT || _i_GameType == TEXTNUM)
			this->rtb_GameText_Que->Text = s;
		else if (_i_GameType == RADIO) {
			char* pc_Ans;
			pc_Ans = new char[iMaxQALen];
			this->rtb_GameRadio_Que->Text = s;
			for (int i = 0; i < 5; i++) {
				++i_cnt;
				int i_cnt2 = 0;
				while (strncmp(&mch_CurrentQueString[i_cnt], QD, strlen(QD)) && strncmp(&mch_CurrentQueString[i_cnt], "\0", 1) && i_cnt < iMaxQALen) {
					pc_Ans[i_cnt2] = mch_CurrentQueString[i_cnt];
					++i_cnt;
					++i_cnt2;
				}
				pc_Ans[i_cnt2] = '\0';
				if ((i < 4 && !strncmp(&mch_CurrentQueString[i_cnt], "\0", 1)) || i_cnt >= iMaxQALen) {
					delete[] pc_Ans;
					throw TAppException(TAppException::APPEXCEPTION_NOANSSTRING, "No Answer String");
				}
				else {
					i_cnt += strlen(QD) - 1;
				}
				s = gcnew String(pc_Ans);
				SetRadioText(i, s);
			}

			delete[] pc_Ans;
		}
	}

	void Form1::SetRadioText(int _i_btn, String ^ _s)
	{
		switch (_i_btn) {
		case 0:
			this->rtxt_option1->Text = _s;
			break;
		case 1:
			this->rtxt_option2->Text = _s;
			break;
		case 2:
			this->rtxt_option3->Text = _s;
			break;
		case 3:
			this->rtxt_option4->Text = _s;
			break;
		case 4:
			this->rtxt_option5->Text = _s;
			break;
		}
	}

	void Form1::ValidateTextAns(int _i_PercentToAns, bool _b_NumConvert)
	{
		if (mp_GameQuestions == NULL) {
			throw TAppException(TAppException::APPEXCEPTION_GENERALMEMORYFAIL, "Null Pointer");
		}

		int i_cnt = copyQuestionString(mch_CurrentQueString, mp_GameQuestions->mp_GameQuestion[mi_CurrentQue].mpch_QueString);
		if (!strncmp(&mch_CurrentQueString[i_cnt], "\0", 1)) {
			throw TAppException(TAppException::APPEXCEPTION_NOANSSTRING, "No Answer String");
		}
		else {
			i_cnt += strlen(QD);
		}
		int i_cnt2 = 0;
		while (strncmp(&mch_CurrentQueString[i_cnt], "\0", 1) && i_cnt < iMaxQALen) {
			mp_GameQuestions->mp_GameQuestion[mi_CurrentQue].mpch_ActualAnsString[i_cnt2] = mch_CurrentQueString[i_cnt];
			++i_cnt;
			++i_cnt2;
		}
		mp_GameQuestions->mp_GameQuestion[mi_CurrentQue].mpch_ActualAnsString[i_cnt2] = '\0';
		if (i_cnt >= iMaxQALen) {
			throw TAppException(TAppException::APPEXCEPTION_ANSSTRINGTOOLONG, "Answer String too long");
		}

		String ^ s = this->rtb_GameText_Ans->Text;
		IntPtr ip = Marshal::StringToHGlobalAnsi(s);
		const char* str = static_cast<const char*>(ip.ToPointer());

		bool b_Correct = false;

		if (!_b_NumConvert && !TMiscUtils::caseIndepstrcmp(str, mp_GameQuestions->mp_GameQuestion[mi_CurrentQue].mpch_ActualAnsString)) {
			b_Correct = true;
		}
		else if (_b_NumConvert) {
			if (strlen(str) != 0 && atof(str) == atof(mp_GameQuestions->mp_GameQuestion[mi_CurrentQue].mpch_ActualAnsString)) {
				b_Correct = true;
			}
		}
		strcpy(mp_GameQuestions->mp_GameQuestion[mi_CurrentQue].mpch_GivenAnsString, str);

		if (b_Correct) {
			this->mp_Rounds->GetRound(mi_CurrentQue).mi_score = 100 - _i_PercentToAns;
			this->mp_Rounds->GetRound(mi_CurrentQue).mb_Correct = true;
			mp_GameQuestions->mp_GameQuestion[mi_CurrentQue].mb_correct = true;
		}
		else {
			this->mp_Rounds->GetRound(mi_CurrentQue).mi_score = 0;
			this->mp_Rounds->GetRound(mi_CurrentQue).mb_Correct = false;
			mp_GameQuestions->mp_GameQuestion[mi_CurrentQue].mb_correct = false;
		}
		this->setTime();
	}

	void Form1::ValidateRadioAns(int _i_PercentToAns)
	{
		std::vector<std::vector<char> > AnswerStrings;
		int i_CorrectAns = copyRadioQuestionsAndAnswerStrings(mch_CurrentQueString, mp_GameQuestions->mp_GameQuestion[mi_CurrentQue].mpch_QueString, mp_GameQuestions->mp_GameQuestion[mi_CurrentQue].mpch_ActualAnsString, AnswerStrings);
		int i_SelRadioBtn;
		GetSelectedRadioBtn(&i_SelRadioBtn);

		if (i_SelRadioBtn >= 0) {
			strcpy(mp_GameQuestions->mp_GameQuestion[mi_CurrentQue].mpch_GivenAnsString, &AnswerStrings[i_SelRadioBtn - 1][0]);
		}
		else {
			strcpy(mp_GameQuestions->mp_GameQuestion[mi_CurrentQue].mpch_GivenAnsString, "");
		}

		if (i_SelRadioBtn == i_CorrectAns) {
			this->mp_Rounds->GetRound(mi_CurrentQue).mi_score = 100 - _i_PercentToAns;
			this->mp_Rounds->GetRound(mi_CurrentQue).mb_Correct = true;
			mp_GameQuestions->mp_GameQuestion[mi_CurrentQue].mb_correct = true;
		}
		else {
			this->mp_Rounds->GetRound(mi_CurrentQue).mi_score = 0;
			this->mp_Rounds->GetRound(mi_CurrentQue).mb_Correct = false;
			mp_GameQuestions->mp_GameQuestion[mi_CurrentQue].mb_correct = false;
		}
		this->setTime();
	}

	void Form1::setTime()
	{
		String ^ s = this->lbl_secsLeft->Text;
		IntPtr ip = Marshal::StringToHGlobalAnsi(s);
		const char* str = static_cast<const char*>(ip.ToPointer());
		strcpy(mp_GameQuestions->mp_GameQuestion[mi_CurrentQue].mpch_TimeString, str);
	}

	void Form1::GetSelectedRadioBtn(int* _pi_SelRadioBtn)
	{
		*_pi_SelRadioBtn = -1;
		if (this->rbtn_option1->Checked) {
			*_pi_SelRadioBtn = 1;
		}
		else if (this->rbtn_option2->Checked) {
			*_pi_SelRadioBtn = 2;
		}
		else if (this->rbtn_option3->Checked) {
			*_pi_SelRadioBtn = 3;
		}
		else if (this->rbtn_option4->Checked) {
			*_pi_SelRadioBtn = 4;
		}
		else if (this->rbtn_option5->Checked) {
			*_pi_SelRadioBtn = 5;
		}
	}

	void Form1::UpdateScoreBox(bool _b_Fin)
	{
		int i_NoCorrect, i_Score;
		RoundResults(&i_NoCorrect, &i_Score);

		char c_scr[12];
		sprintf_s(c_scr, 12, "%d/%d", i_NoCorrect, mi_CurrentQue);
		char c_scr2[12];
		sprintf_s(c_scr2, 12, "%d", i_Score);

		String ^ s = gcnew String(c_scr);
		if (!_b_Fin)
			this->tb_QueNo->Text = s;
		else {
			this->tb_FinQueNo->Text = s;
			String ^ s2 = gcnew String(c_scr2);
			this->tb_FinScore->Text = s2;
		}
	}

	void Form1::RoundResults(int* _pi_NoCorrect, int* _pi_Score)
	{
		*_pi_NoCorrect = 0;
		*_pi_Score = 0;
		for (int i = 0; i < mi_CurrentQue; i++) {
			if (this->mp_Rounds->GetRound(i).mb_Correct) {
				(*_pi_NoCorrect)++;
				(*_pi_Score) += this->mp_Rounds->GetRound(i).mi_score;
			}
		}
		TNumeric::RoundToNearestInt(float(*_pi_Score) / float(this->mp_Rounds->GetNumberOfRounds()) * float(mi_NoRounds), _pi_Score);
	}

	void Form1::FinaliseGame(bool _b_RunOK)
	{
		if (mb_GameFinialised == false) {
			mb_GameFinialised = true;
			if (mb_GameUpdate) {
				this->pan_Setup->Enabled = true;
				this->pan_GameText->Show();
				this->pan_GameRadio->Show();
				this->pan_GameScores->Show();
				this->pan_GameScores->BringToFront();
				this->btn_NextQue->Hide();
				this->pgbr_Timer->Hide();
				this->lbl_secsLeft->Hide();
				this->tb_QueNo->Hide();
				this->UpdateScoreBox(true);

				string GameName = this->GetHighScoreString();
				int i_NoCorrect, i_Score;
				RoundResults(&i_NoCorrect, &i_Score);
				this->mp_ScoreFileHandler->TakeScore(GameName, i_Score);

				this->PopulateHighScores();
				mb_GameUpdate = false;
			}
			UnregisterHotKey((HWND)this->Handle.ToPointer(), 1);
			mp_SummaryForm = gcnew GameSummary(mp_GameQuestions, false);
			mp_SummaryForm->ShowDialog();
			mp_SummaryForm->Close();
			mp_SummaryForm = nullptr;
		}
	}

	void Form1::SetGameSelectionEnablement()
	{
		if (this->rbtn_Mix_10->Checked || this->rbtn_Mix_All->Checked) {
			this->combo_Game->Enabled = false;
		}
		else {
			this->combo_Game->Enabled = true;
		}
		if (this->rbtn_Single_All->Checked) {
			this->addGameStringsToComboBox(true);
		}
		else {
			this->addGameStringsToComboBox(false);
		}
	}

	void Form1::PopulateHighScores()
	{
		string GameName = this->GetHighScoreString();
		char c_scr[56];
		String ^ s;

		if (this->mp_ScoreFileHandler->Setgame(GameName) != RET_OK)
			throw TAppException(TAppException::APPEXCEPTION_HIGHSCRCORRUPT, "High Score File Corrupt");

		int i_Score;
		for (int i = 0; i < NOHIGHSCORES; i++) {
			i_Score = this->mp_ScoreFileHandler->GetScore(i);
			sprintf_s(c_scr, 12, "%d", i_Score);
			s = gcnew String(c_scr);

			switch (i) {
			case 0:
				this->tb_HS1->Text = s;
				break;
			case 1:
				this->tb_HS2->Text = s;
				break;
			case 2:
				this->tb_HS3->Text = s;
				break;
			case 3:
				this->tb_HS4->Text = s;
				break;
			case 4:
				this->tb_HS5->Text = s;
				break;
			case 5:
				this->tb_HS6->Text = s;
				break;
			case 6:
				this->tb_HS7->Text = s;
				break;
			case 7:
				this->tb_HS8->Text = s;
				break;
			case 8:
				this->tb_HS9->Text = s;
				break;
			case 9:
				this->tb_HS10->Text = s;
				break;
			}
		}
	}

	string Form1::GetHighScoreString()
	{
		string GameName;
		char c_scr[56];
		String ^ s;

		if (this->rbtn_Mix_10->Checked || this->rbtn_Mix_All->Checked) {
			GameName = MIXEDGAMESTRING;
			if (this->rbtn_Mix_10->Checked) {
				GameName += "_" + string(TENROUNDSSTRING);
			}
			else {
				GameName += "_" + string(ALLROUNDSSTRING);
			}
		}
		else {
			GameName = SINGLEGAMESTRING;
			if (this->rbtn_Single_10->Checked) {
				GameName += "_" + string(TENROUNDSSTRING);
			}
			else {
				GameName += "_" + string(ALLROUNDSSTRING);
			}
			String ^ s = this->combo_Game->Text;
			IntPtr ip = Marshal::StringToHGlobalAnsi(s);
			const char* str = static_cast<const char*>(ip.ToPointer());
			GameName += "_" + string(str);
		}
		sprintf_s(c_scr, 56, "%s", GameName.c_str());
		s = gcnew String(c_scr);
		this->tb_HSGame->Text = s;

		string diff;
		if (this->rbtn_Easy->Checked) {
			diff = "Normal";
		}
		if (this->rbtn_Med->Checked) {
			diff = "Freak";
		}
		if (this->rbtn_Hard->Checked) {
			diff = "RainMan";
		}
		sprintf_s(c_scr, 56, "%s", diff.c_str());
		s = gcnew String(c_scr);
		this->tb_HSDiff->Text = s;

		GameName += "_" + diff;

		return GameName;
	}

	void Form1::addGameStringsToComboBox(bool _b_triviaOnly)
	{
		this->combo_Game->Items->Clear();
		string GameName;
		if (this->mp_GameContainer) {
			int iNoGames = this->mp_GameContainer->GetNumberOfGames();
			int isetIndex = -1;
			for (int i = 0; i < iNoGames; i++) {
				mp_GameContainer->GetGameName(GameName, i);
				String ^ s = gcnew String(GameName.c_str());
				if (!_b_triviaOnly || GameName.find(TRIVAPRE) != string::npos) {
					if (isetIndex == -1)
						isetIndex = i;
					this->combo_Game->Items->Add(s);
					this->mp_Games->SetGame(i, GameName);
				}
			}
			setGameInComboBox(isetIndex);
		}
	}

	void Form1::setGameInComboBox(int _i_gameindex)
	{
		string GameName;
		mp_GameContainer->GetGameName(GameName, _i_gameindex);
		char pc_Que[128];
		strcpy_s(pc_Que, 128, GameName.c_str());
		String ^ s = gcnew String(pc_Que);
		this->combo_Game->Text = s;
	}

	void Form1::ThrowError(unsigned int _ui_ErrorCode)
	{
		if (_ui_ErrorCode == RET_RANGEERR)
			throw TAppException(TAppException::APPEXCEPTION_INDEXOUTSIDERANGE, "Index Outside Range");
		if (_ui_ErrorCode == RET_STRINGDOESNOTEXIST)
			throw TAppException(TAppException::APPEXCEPTION_NOSUCHGAMETYPE, "No Such Game Type");
		if (_ui_ErrorCode == RET_DLLFUNCTIONRETURNERROR)
			throw TAppException(TAppException::APPEXCEPTION_DLLFUNCTIONRETURNERROR, "Dll Return Error");
	}
}
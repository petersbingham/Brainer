// Tests.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "SetupClass_NOQUESTIONS.h"
#include "SetupClass_UNIQUE.h"
#include "SetupClass_DUMMY.h"
#include "SetupClass_DUPLICATE.h"
#include "gtest/gtest.h"
#include "CommonHeader.h"

TEST(NOQUESTIONS, _EMPTY) 
{
  TSetupClass_NOQUESTIONS::EmptyFile();
}

TEST(NOQUESTIONS, _1Section) 
{
  TSetupClass_NOQUESTIONS::SingleSectionTests(EASY, EASY);
}

TEST(NOQUESTIONS, _2Section) 
{
  TSetupClass_NOQUESTIONS::DoubleSectionTests(EASY, EASY, EASY);
  TSetupClass_NOQUESTIONS::DoubleSectionTests(EASY, HARD, MEDIUM);
  TSetupClass_NOQUESTIONS::DoubleSectionTests(EASY, MEDIUM, EASY);
  TSetupClass_NOQUESTIONS::DoubleSectionTests(HARD, EASY, HARD);
  TSetupClass_NOQUESTIONS::DoubleSectionTests(HARD, HARD, MEDIUM);
  TSetupClass_NOQUESTIONS::DoubleSectionTests(HARD, MEDIUM, EASY);
  TSetupClass_NOQUESTIONS::DoubleSectionTests(MEDIUM, EASY, EASY);
  TSetupClass_NOQUESTIONS::DoubleSectionTests(MEDIUM, HARD, EASY);
  TSetupClass_NOQUESTIONS::DoubleSectionTests(MEDIUM, MEDIUM, MEDIUM);
}

TEST(UNIQUE, _1SectionFileEASY_SetDiffEASY) 
{
  TSetupClass_UNIQUE::SingleSectionTests(EASY, EASY);
}
TEST(UNIQUE, _1SectionFileEASY_SetDiffMEDIUM) 
{
  TSetupClass_UNIQUE::SingleSectionTests(EASY, MEDIUM);
}
TEST(UNIQUE, _1SectionFileEASY_SetDiffHARD) 
{
  TSetupClass_UNIQUE::SingleSectionTests(EASY, HARD);
}
TEST(UNIQUE, _1SectionFileMEDIUM_SetDiffEASY) 
{
  TSetupClass_UNIQUE::SingleSectionTests(MEDIUM, EASY);
}
TEST(UNIQUE, _1SectionFileMEDIUM_SetDiffMEDIUM) 
{
  TSetupClass_UNIQUE::SingleSectionTests(MEDIUM, MEDIUM);
}
TEST(UNIQUE, _1SectionFileMEDIUM_SetDiffHARD) 
{
  TSetupClass_UNIQUE::SingleSectionTests(MEDIUM, HARD);
}
TEST(UNIQUE, _1SectionFileHARD_SetDiffEASY) 
{
  TSetupClass_UNIQUE::SingleSectionTests(HARD, EASY);
}
TEST(UNIQUE, _1SectionFileHARD_SetDiffMEDIUM) 
{
  TSetupClass_UNIQUE::SingleSectionTests(HARD, MEDIUM);
}
TEST(UNIQUE, _1SectionFileHARD_SetDiffHARD) 
{
  TSetupClass_UNIQUE::SingleSectionTests(HARD, HARD);
}

TEST(UNIQUE, _2SectionFileEASYEASY_SetDiffEASY) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(EASY, EASY, EASY);
}

TEST(UNIQUE, _2SectionFileEASYEASY_SetDiffMEDIUM) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(EASY, EASY, MEDIUM);
}

TEST(UNIQUE, _2SectionFileEASYEASY_SetDiffHARD) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(EASY, EASY, HARD);
}

TEST(UNIQUE, _2SectionFileEASYMEDIUM_SetDiffEASY) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(EASY, MEDIUM, EASY);
}

TEST(UNIQUE, _2SectionFileEASYMEDIUM_SetDiffMEDIUM) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(EASY, MEDIUM, MEDIUM);
}

TEST(UNIQUE, _2SectionFileEASYMEDIUM_SetDiffHARD) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(EASY, MEDIUM, HARD);
}

TEST(UNIQUE, _2SectionFileEASYHARD_SetDiffEASY) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(EASY, HARD, EASY);
}

TEST(UNIQUE, _2SectionFileEASYHARD_SetDiffMEDIUM) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(EASY, HARD, MEDIUM);
}

TEST(UNIQUE, _2SectionFileEASYHARD_SetDiffHARD) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(EASY, HARD, HARD);
}

TEST(UNIQUE, _2SectionFileMEDIUMEASY_SetDiffEASY) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(MEDIUM, EASY, EASY);
}

TEST(UNIQUE, _2SectionFileMEDIUMEASY_SetDiffMEDIUM) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(MEDIUM, EASY, MEDIUM);
}

TEST(UNIQUE, _2SectionFileMEDIUMEASY_SetDiffHARD) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(MEDIUM, EASY, HARD);
}

TEST(UNIQUE, _2SectionFileMEDIUMMEDIUM_SetDiffEASY) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(MEDIUM, MEDIUM, EASY);
}

TEST(UNIQUE, _2SectionFileMEDIUMMEDIUM_SetDiffMEDIUM) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(MEDIUM, MEDIUM, MEDIUM);
}

TEST(UNIQUE, _2SectionFileMEDIUMMEDIUM_SetDiffHARD) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(MEDIUM, MEDIUM, HARD);
}

TEST(UNIQUE, _2SectionFileMEDIUMHARD_SetDiffEASY) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(MEDIUM, HARD, EASY);
}

TEST(UNIQUE, _2SectionFileMEDIUMHARD_SetDiffMEDIUM) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(MEDIUM, HARD, MEDIUM);
}

TEST(UNIQUE, _2SectionFileMEDIUMHARD_SetDiffHARD) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(MEDIUM, HARD, HARD);
}

TEST(UNIQUE, _2SectionFileHARDEASY_SetDiffEASY) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(HARD, EASY, EASY);
}

TEST(UNIQUE, _2SectionFileHARDEASY_SetDiffMEDIUM) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(HARD, EASY, MEDIUM);
}

TEST(UNIQUE, _2SectionFileHARDEASY_SetDiffHARD) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(HARD, EASY, HARD);
}

TEST(UNIQUE, _2SectionFileHARDMEDIUM_SetDiffEASY) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(HARD, MEDIUM, EASY);
}

TEST(UNIQUE, _2SectionFileHARDMEDIUM_SetDiffMEDIUM) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(HARD, MEDIUM, MEDIUM);
}

TEST(UNIQUE, _2SectionFileHARDMEDIUM_SetDiffHARD) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(HARD, MEDIUM, HARD);
}

TEST(UNIQUE, _2SectionFileHARDHARD_SetDiffEASY) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(HARD, HARD, EASY);
}

TEST(UNIQUE, _2SectionFileHARDHARD_SetDiffMEDIUM) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(HARD, HARD, MEDIUM);
}

TEST(UNIQUE, _2SectionFileHARDHARD_SetDiffHARD) 
{
  TSetupClass_UNIQUE::DoubleSectionTests(HARD, HARD, HARD);
}

TEST(UNIQUE, _3SectionFileEASYEASYEASY_SetDiffEASY) 
{
  TSetupClass_UNIQUE::TripleSectionTests(EASY, EASY, EASY, EASY);
}

TEST(UNIQUE, _3SectionFileEASYEASYEASY_SetDiffMEDIUM) 
{
  TSetupClass_UNIQUE::TripleSectionTests(EASY, EASY, EASY, MEDIUM);
}

TEST(UNIQUE, _3SectionFileEASYEASYEASY_SetDiffHARD) 
{
  TSetupClass_UNIQUE::TripleSectionTests(EASY, EASY, EASY, HARD);
}

TEST(UNIQUE, _3SectionFileEASYMEDIUMHARD_SetDiffEASY) 
{
  TSetupClass_UNIQUE::TripleSectionTests(EASY, MEDIUM, HARD, EASY);
}

TEST(UNIQUE, _3SectionFileEASYMEDIUMHARD_SetDiffMEDIUM) 
{
  TSetupClass_UNIQUE::TripleSectionTests(EASY, MEDIUM, HARD, MEDIUM);
}

TEST(UNIQUE, _3SectionFileEASYMEDIUMHARD_SetDiffHARD) 
{
  TSetupClass_UNIQUE::TripleSectionTests(EASY, MEDIUM, HARD, HARD);
}

TEST(UNIQUE, _3SectionFileHARDMEDIUMEASY_SetDiffEASY) 
{
  TSetupClass_UNIQUE::TripleSectionTests(HARD, MEDIUM, EASY, EASY);
}

TEST(UNIQUE, _3SectionFileHARDMEDIUMEASY_SetDiffMEDIUM) 
{
  TSetupClass_UNIQUE::TripleSectionTests(HARD, MEDIUM, EASY, MEDIUM);
}

TEST(UNIQUE, _3SectionFileHARDMEDIUMEASY_SetDiffHARD) 
{
  TSetupClass_UNIQUE::TripleSectionTests(HARD, MEDIUM, EASY, HARD);
}

TEST(DUMMY, _1SectionFileEASY_SetDiffEASY) 
{
  TSetupClass_DUMMY::SingleSectionTests(EASY, EASY);
}

TEST(DUMMY, _1SectionFileEASY_SetDiffMEDIUM) 
{
  TSetupClass_DUMMY::SingleSectionTests(EASY, MEDIUM);
}

TEST(DUMMY, _1SectionFileEASY_SetDiffHARD) 
{
  TSetupClass_DUMMY::SingleSectionTests(EASY, HARD);
}

TEST(DUPLICATE, _1SectionFileEASY_SetDiffEASY) 
{
  TSetupClass_DUPLICATE::SingleSectionTests(EASY, EASY);
}

TEST(DUPLICATE, _1SectionFileEASY_SetDiffMEDIUM) 
{
  TSetupClass_DUPLICATE::SingleSectionTests(EASY, MEDIUM);
}

TEST(DUPLICATE, _1SectionFileEASY_SetDiffHARD) 
{
  TSetupClass_DUPLICATE::SingleSectionTests(EASY, HARD);
}

int _tmain(int argc, _TCHAR* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  system("pause");
	return 0;
}


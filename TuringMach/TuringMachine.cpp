#include "stdafx.h"
#include "TuringMachine.h"

using namespace std;
using namespace Turing;

#define afterRule prog.find(tmpValue)->second[tmpState - 1]

void TuringMachine::postProcessing() // Delet odd * marks on begining and end
{
	if (row[0] == '*')
		row.pop_front();
	if (row[row.size() - 1] == '*')
		row.pop_back();
}

bool TuringMachine::step()
{
	if (currState == 0)
		return 0;       // HALT

	int  tmpState = currState;
	int  tmpPos   = currPos;
	char tmpValue = row[tmpPos];

	if (prog.find(tmpValue) == prog.end())
		return 0;       // HALT

	row[tmpPos] = afterRule.changeTo;
	currPos    += afterRule.moveDirection;
	if (currPos < 0)
	{
		row.push_front('*');
		currPos++;
	}
	if (currPos >= row.size())
	{
		row.push_back('*');
	}
	currState  = afterRule.nextState;

	return 1;
}

TuringMachine::TuringMachine(string ProgAdress)
{
	ifstream fin(ProgAdress);
	char tmp = 'A';

	while (tmp != '#')
	{
		fin >> tmp;
		if (tmp != '#')
			alphabet.push_back(tmp);
	}

	fin >> numOfStates;

	tmp = 'A';

	while (tmp != '#')
	{
		fin >> tmp;
		if (tmp != '#')
		{
			vector<Rule> tmpVec;
			for (int i = 0; i < numOfStates; i++)
			{
				Rule tmpRule;
				char moveTmp;
				fin >> tmpRule.changeTo >> moveTmp >> tmpRule.nextState;

				if (moveTmp == 'L')
					tmpRule.moveDirection = -1;
				else if (moveTmp == 'R')
					tmpRule.moveDirection = 1;
				else
					tmpRule.moveDirection = 0;

				tmpVec.push_back(tmpRule);
			}
			prog.insert(make_pair(tmp, tmpVec));
		}
	}

	tmp = 'A';
	while (tmp != '#')
	{
		fin >> tmp;
		if (tmp != '#')
		{
			row.push_back(tmp);
		}
	}
}

TuringMachine::~TuringMachine()
{
}

void TuringMachine::setRow(Tline repRow)
{
	row = repRow;
}

void TuringMachine::printAlpha()
{
	for (size_t it = 0; it < alphabet.size(); it++)
		cout << alphabet[it] << " ";
}
void TuringMachine::printRow()
{
	for (auto it = row.begin(); it != row.end(); it++)
		cout << (*it) << " ";
}

void TuringMachine::printPos()
{
	for (int i = 0; i < currPos; i++)
	{
		cout << "  ";
	}
	cout << "^";
}

Tline TuringMachine::work(int beginingState, int beginingPos)
{
	currState = beginingState;
	currPos = beginingPos;

	system("cls");
	printPos();
	cout << '\n';
	printRow();
	cout << "\nCurrent State: " << currState;
	Sleep(DELAY);

	while (step())
	{
		system("cls");
		printPos();
		cout << '\n';
		printRow();
		cout << "\nCurrent State: " << currState;
		Sleep(DELAY);
	}
	postProcessing();

	return row;
}

Tline TuringMachine::silentWork(int beginingState, int beginingPos)
{
	currState = beginingState;
	currPos = beginingPos;
	while (step());

	return row;
}
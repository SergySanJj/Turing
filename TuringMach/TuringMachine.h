#pragma once
#pragma warning(disable: 4018) // comparing signed and unsigned values warning off

#include "stdafx.h"

#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <vector>
#include <windows.h>
using namespace std;

namespace Turing
{
	struct Rule
	{
		char         changeTo;
		short        moveDirection; //-1 L; 0 N; +1 R
		unsigned int nextState;     // 0 == Halt
	};


#define DELAY 300

	typedef deque<char> Tline;

	class TuringMachine
	{
	private:
		int currPos     = 1;
		int currState   = 0;
		int numOfStates = 0;

		vector<char>             alphabet;
		map<char, vector<Rule> > prog;
		Tline                    row;

		void postProcessing(); // Delet odd * marks on begining and end
		bool step();

	public:
		/*
		Programm - 3 parts:
			alphabet {s1, s2, .. sn} #
			number of states
			set of rules #
			input data #
		*/
		TuringMachine(string ProgAdress);

		~TuringMachine();

		void setRow(Tline repRow);

		void printAlpha();
		void printRow();
		void printPos();

		Tline work(int beginingState, int beginingPos);

		Tline silentWork(int beginingState, int beginingPos);
	};
}

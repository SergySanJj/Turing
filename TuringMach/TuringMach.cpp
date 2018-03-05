#include "stdafx.h"
#include "TuringMachine.h"

using namespace std;
using namespace Turing;

int main()
{
	
	TuringMachine Sum("Summ.prog");
	Sum.work(6, 0); // put cursor in the position of last elem of first number
	cout << '\n';
	system("pause");
	return 0;
}
﻿#include <iostream>
#include "task.h"
#include <locale>

int main()
{
	setlocale(LC_ALL, "Rus");
	Shop s(4, 20, 100, 5, 4);
	s.Start();
	return 0;
}

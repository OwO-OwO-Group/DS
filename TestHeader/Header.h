#pragma once
#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

extern bool inputSuccess;
void errorHandling(string message);
static string getOnlyDigits(string str);
static int sToi(string str);
int stringToInt(string str);

#endif


// 第10組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
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


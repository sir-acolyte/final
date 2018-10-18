#pragma once

#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>
#include <string>

using namespace std;

void setConsoleColor(string color);
void setConsoleSize(int width, int height);
void setConsoleFontSize(int size);
void setConsoleTitle(string name);

#endif
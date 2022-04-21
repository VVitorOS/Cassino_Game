#include <stdio.h>
#include "func.h"
#include <locale.h>
#include <windows.h>

int main(){

    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    Menu();

    SetConsoleOutputCP(CPAGE_DEFAULT);
}
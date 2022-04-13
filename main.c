#include <stdio.h>
#include "func.h"
#include <locale.h>

int main(){
    setlocale(LC_ALL, "portuguese");

    Menu();
    system("pause");
    return 0;

}

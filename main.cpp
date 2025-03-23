#include <iostream>
#include "lab02.h"
using namespace std;

int main()
{

    Invoice inv(7770003699, 01234567);
    inv.add_item(Item("M3 screw", 0.37, 'A', 100));
    inv.add_item(Item("2 mm drill", 2.54, 'B', 2));
    std::cout << inv;
    return 0;
}

#include <iostream>
#include "IniFile.h"

int main()
{
    IniFile iniFile = IniFile("qwe.ini");
    iniFile.writeBool("MySection", "abobus", true);
    iniFile.writeString("A section", "furries", "wtf?");
    iniFile.writeInt("The section?", "gigachad", 1);
    iniFile.writeDouble("OMG", "gayRatio", 0.04);
    return 0;
}

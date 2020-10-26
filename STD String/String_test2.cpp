// Alexis Lopez
// String_test2.cpp

#include <iostream>

#include "String.h"

using namespace std;

main()
{
    String s1{"abcd"}, s2{"abe"};

    if (s1 == s2)
        std::cout << s1 << " == " << s2;
    else
        if (s1 <= s2)
            std::cout << s1 << " < " << s2 << std::endl;
        else
            std::cout << s1 << " > " << s2 << std::endl;

    s1 = move(s2);
    std::cout << "s1=" << s1 << " s2=" << s2 << std::endl;

    String s3 = move(s1);
    std::cout << "s1=" << s1 << " s3=" << s3 << std::endl;
}

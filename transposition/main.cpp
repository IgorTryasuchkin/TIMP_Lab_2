#include <iostream>
#include <locale>
#include <cwctype>
#include "modTableCipher.h"
using namespace std;

void check(const wstring& Text, int key, const bool destructCipherText=false)
{
    try {
        wstring cipherText;
        wstring decryptedText;
        modTableCipher cipher(key);
        cipherText = cipher.encrypt(Text);
        if (destructCipherText)
            cipherText.front() = towlower(cipherText.front());
        decryptedText = cipher.decrypt(cipherText);
        wcout<<L"key="<<key<<endl;
        wcout<<Text<<endl;
        wcout<<cipherText<<endl;
        wcout<<decryptedText<<endl;
    } catch (const cipher_error & e) {
        cerr<<"Error: "<<e.what()<<endl;
    }
}

int main(int argc, char **argv)
{
    locale::global(locale(""));
    wcout.imbue(locale());
    wcin.imbue(locale());
    check(L"ПРИВЕТМИР", 3);
    check(L"Съешь же ещё этих мягких французских булок", 5);
    check(L"ПРИВЕТ", 0);                 // недопустимый ключ
    check(L"ПРИВЕТ", -2);                // недопустимый ключ
    check(L"ПРИВЕТ", 10);                // ключ длиннее текста
    check(L"123 !?", 3);                 // в тексте нет букв
    check(L"", 3);                       // пустой текст
    check(L"ПРИВЕТМИР", 3, true);        // испорченный шифротекст
    return 0;
}

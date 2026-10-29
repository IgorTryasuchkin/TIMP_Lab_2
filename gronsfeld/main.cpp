#include <iostream>
#include <locale>
#include <cwctype>
#include "modAlphaCipher.h"
using namespace std;

void check(const wstring& Text, const wstring& key, const bool destructCipherText=false)
{
    try {
        wstring cipherText;
        wstring decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text);
        if (destructCipherText) // надо "портить"?
            cipherText.front() = towlower(cipherText.front()); // "портим"
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
    check(L"ПРИВЕТ", L"ЭХО");
    check(L"ПРИВЕТ", L"эхо");              // ключ в нижнем регистре
    check(L"Съешь же ещё этих мягких французских булок, да выпей чаю", L"Ключ");
    check(L"ПРИВЕТ", L"");                 // пустой ключ
    check(L"ПРИВЕТ", L"ЭХО123");           // недопустимые символы в ключе
    check(L"123", L"ЭХО");                 // в тексте нет букв
    check(L"ПРИВЕТ", L"ЭХО", true);        // испорченный шифротекст
    return 0;
}

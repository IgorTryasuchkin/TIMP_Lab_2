#pragma once
#include <string>
#include <stdexcept>

/// Класс-исключение модуля шифрования
class cipher_error: public std::invalid_argument {
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};

/// Шифр табличной маршрутной перестановки (русский язык)
/// Запись: по строкам слева направо, сверху вниз.
/// Считывание: по столбцам справа налево, сверху вниз.
class modTableCipher
{
private:
    int cols; ///< ключ - количество столбцов таблицы
    wchar_t toUpperRu(wchar_t c);
    bool isRuUpper(wchar_t c);
    std::wstring getValidOpenText(const std::wstring & s);
    std::wstring getValidCipherText(const std::wstring & s);
public:
    modTableCipher()=delete;
    modTableCipher(int key);
    std::wstring encrypt(const std::wstring& open_text);
    std::wstring decrypt(const std::wstring& cipher_text);
};

#include "modTableCipher.h"

modTableCipher::modTableCipher(int key)
{
    if (key <= 0)
        throw cipher_error("Invalid key");
    cols = key;
}

std::wstring modTableCipher::encrypt(const std::wstring& open_text)
{
    std::wstring text = getValidOpenText(open_text);
    int n = text.size();
    if (cols > n)
        throw cipher_error("Key is longer than text");
    int rows = (n + cols - 1) / cols;
    std::wstring result;
    for (int c = cols - 1; c >= 0; c--)          // столбцы справа налево
        for (int r = 0; r < rows; r++) {         // сверху вниз
            int idx = r * cols + c;
            if (idx < n)
                result.push_back(text[idx]);
        }
    return result;
}

std::wstring modTableCipher::decrypt(const std::wstring& cipher_text)
{
    std::wstring text = getValidCipherText(cipher_text);
    int n = text.size();
    if (cols > n)
        throw cipher_error("Key is longer than text");
    std::wstring result(n, L' ');
    int pos = 0;
    for (int c = cols - 1; c >= 0; c--) {
        int height = n / cols + (c < n % cols ? 1 : 0); // высота столбца
        for (int r = 0; r < height; r++)
            result[r * cols + c] = text[pos++];
    }
    return result;
}

wchar_t modTableCipher::toUpperRu(wchar_t c)
{
    if (c >= L'а' && c <= L'я')
        return c - (L'а' - L'А');
    if (c == L'ё')
        return L'Ё';
    return c;
}

bool modTableCipher::isRuUpper(wchar_t c)
{
    return (c >= L'А' && c <= L'Я') || c == L'Ё';
}

std::wstring modTableCipher::getValidOpenText(const std::wstring & s)
{
    std::wstring tmp;
    for (auto c:s) {
        c = toUpperRu(c);
        if (isRuUpper(c))
            tmp.push_back(c);
    }
    if (tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}

std::wstring modTableCipher::getValidCipherText(const std::wstring & s)
{
    if (s.empty())
        throw cipher_error("Empty cipher text");
    for (auto c:s) {
        if (!isRuUpper(c))
            throw cipher_error("Invalid cipher text");
    }
    return s;
}

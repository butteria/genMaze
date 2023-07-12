#include <stdio.h>
#include <fcntl.h>
#include <locale.h>

// seperate it into two parts, the up-side and down-side.
static const wchar_t *block_fonts[27][2] = {
   { L"▄▀▄", L"█▀█"  },    // A, a
   { L"█▄▄", L"█▄█" },     // B, b
   { L"█▀▀", L"█▄▄" },     // C, c
   { L"█▀▄", L"█▄▀" },     // D, d
   { L"██▀", L"█▅▅" },     // E, e
   { L"█▀▀", L"█▀▀" },     // F, f
   { L"█▀▀", L"█▄█" },     // G, g
   { L"█▄█", L"█▀█" },     // H, h
   { L"█", L"█" },         // I, i
   { L"▀█▀", L"▄█ " },     // J, j
   { L"█▄▀", L"█▀▄" },     // K, k
   { L"█  ", L"█▄▄" },     // L, l
   { L"█▀▄▀█", L"█ █ █" }, // M, m
   { L"█▀▄ █", L"█ ▀▄█" }, // N, n
   { L"█▀█", L"█▄█" },     // O, o
   { L"█▀█", L"█▀▀" },     // P, p
   { L"█▀█ ", L"█▄▀▄" },   // Q, q
   { L"█▀█", L"█▀▄" },     // R, r
   { L"█▀", L"▄█" },       // S, s
   { L"▀█▀", L" █ " },     // T, t
   { L"█ █", L"█▄█" },     // U, u
   { L"█ █", L"▀▄▀" },     // V, v
   { L"█ █ █", L"▀▄▀▄▀" }, // W, w
   { L"▀▄▀", L"█ █" },     // X, x
   { L"█▄█", L" █ " },     // Y, y
   { L"▀▀█", L"▄█▄" },     // Z, z
   { L" ", L" " },         // Space
};

void
predo(char *str)
{
    int i, j = 0, c;
    for(i = 0; (c = str[i]) != '\0'; i++)
    {
        if(c >= 'A' && c <= 'Z')
            str[j++] = str[i] + 32;
        else if(c >= 'a' && c <= 'z')
            str[j++] = str[i];
        else if(c == ' ')
            str[j++] = 123;
    }
    str[j] = '\0';
}
int
convert2block(char *str)
{
    int i, c;
    _setmode(_fileno(stdout), _O_U8TEXT);
    setlocale(LC_ALL, "");

    predo(str);
    //  up-side part.
    for(i = 0; (c = str[i]) != '\0'; i++)
        wprintf(L"%ls ", block_fonts[c - 'a'][0]);
    wprintf(L"\n");

    // down-side part.
    for(i = 0; (c = str[i]) != '\0'; i++)
        wprintf(L"%ls ", block_fonts[c - 'a'][1]);
    wprintf(L"\n");

    return 1;
}
#include <stdio.h>
#include <fcntl.h>
#include <locale.h>

// seperate it into two parts, the up-side and down-side.
const wchar_t *block_fonts[1][2] = {
    { L"▄▀█" , L"█▀█"  }, // a
};

int
convert2block(char *str)
{
    int i, j, c;
    _setmode(_fileno(stdout), _O_U16TEXT);

    //  up-side part.
    for(i = 0; (c = str[i]) != '\0'; i++)
        wprintf(L"%ls ", block_fonts[c- 'a'][0]);
    wprintf(L"\n");

    // down-side part.
    for(i = 0; (c = str[i]) != '\0'; i++)
        wprintf(L"%ls ", block_fonts[c- 'a'][1]);
    wprintf(L"\n");

    return 1;
}

int
main()
{
    char str[4] = "aaa\0";
    convert2block(str);
}
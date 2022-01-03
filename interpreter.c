#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc != 2) return 1;

    FILE *fp;
    char* bf;
    long size_bf;

    fp = fopen(argv[1],"r");
    
    if (!fp) return 2;

    fseek(fp, 0L, SEEK_END);
    size_bf = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    bf = (char*)calloc(size_bf, sizeof(char));
    
    if (bf == NULL) return 1;
    
    fread(bf, sizeof(char), size_bf, fp);
   
    long i = 0;
    char array[30000] = {0};
    char *ptr = array;
    short skip = 1;
    int brack[size_bf];
    int sz_brack = 0;

    while (i <= size_bf)
    {
        if (skip)
        {
            switch(bf[i])
            {
                case '>' : 
                    ++ptr;
                    ++i;
                    break;
                case '<':
                    --ptr;
                    ++i;
                    break;
                case '+':
                    ++*ptr;
                    ++i;
                    break;
                case '-' :
                    --*ptr;
                    ++i;
                   break;
                case '.' :
                    putchar(*ptr);
                    ++i;
                    break;
                case ',' :
                    *ptr = getchar();
                    ++i;
                    break;
                case '[' :
                    brack[sz_brack] = i;
                    ++sz_brack;
                    if (*ptr == 0) 
                    {
                        skip = 0;
                    }
                    ++i;
                    break;
                case ']' :
                    if (*ptr != 0) 
                    {
                        i=brack[sz_brack - 1];
                    }
                    else 
                    {
                        --sz_brack;
                        brack[sz_brack] = 0;
                    }
                    ++i;
                    break;
                default:
                    ++i;
                    break;
            }   
        }
        else if (bf[i] == '[') 
        {
            brack[sz_brack] = i;
            ++ sz_brack;
            ++i;
        }
        else if (bf[i] == ']')
        {
            if (sz_brack == 0)
            {
                brack[0] = 0;
                skip = 1;
            }
            else
            {
                brack[sz_brack] = 0;
                -- sz_brack;
            }
            ++i;
        }
        else
        {
            ++i;
        }
    }

    fclose(fp);
    return 0;
}

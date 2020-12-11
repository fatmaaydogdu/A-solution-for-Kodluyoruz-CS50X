#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>


void caesarCode(char *, int);

int main(int argc, char *argv[])
{
    
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (isalpha(argv[1][i]) != 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    
    int key = atoi(argv[1]);
    
    
    char *plaintext = get_string("Enter text to encrypt: ");
    
    caesarCode(plaintext, key);
}

void caesarCode(char *t, int k)
{
    printf("ciphertext: ");
    
    for (int i = 0; t[i] != '\0'; i++)
    {
        
        if (isalpha(t[i]) != 0)
        {
            
            if (isupper(t[i]) != 0)
            {
                
                printf("%c", ((t[i] - 'A' + k) % 26) + 'A');
            }
           
            else
            {
                printf("%c", ((t[i] - 'a' + k) % 26) + 'a');
            }
        }
        
        else
        {
            printf("%c", t[i]);
        }
    }
    printf("\n");
}

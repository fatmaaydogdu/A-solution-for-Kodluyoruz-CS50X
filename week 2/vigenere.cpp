#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[]){
    
    int keyLength;
    
    if(argc != 2){

        printf("error");
        return 1;
    
  
    } 
    else {
        
        keyLength = strlen(argv[1]);
        
        for(int h = 0; h < keyLength; h++){
       
            if( !isalpha(argv[1][h]) ){
                printf("error");
                return 1;
            }
        }
    }

   
    char key[keyLength];
    
    for(int g = 0; g < keyLength; g++){
        
        key[g] = argv[1][g];
        
    }
    
 
    printf("plaintext:");
    string plainText = get_string();
    
    char cipherText[strlen(plainText)];
    int plainLength = strlen(plainText);
    
   
    for(int i = 0, j = 0; i < plainLength; i++){

        if(isalpha(plainText[i])){
            
            if(isupper(key[j % keyLength])){
                
                if(isupper(plainText[i])){
                
                    cipherText[i] = ((((plainText[i] - 65) + (key[j % keyLength] - 65)) % 26) + 65);
                
                } else {
                
                    cipherText[i] = ((((plainText[i] - 97) + (key[j % keyLength] - 65)) % 26) + 97);
                    
                }
            } else {
                
                if(isupper(plainText[i])){
                
                    cipherText[i] = ((((plainText[i] - 65) + (key[j % keyLength] - 97)) % 26) + 65);
                
                } else {
                
                    cipherText[i] = ((((plainText[i] - 97) + (key[j % keyLength] - 97)) % 26) + 97);
                }
            }
            
            j++;
        } else {
            cipherText[i] = plainText[i];
        }
        
    }
    

    printf("ciphertext: ");
    
    for(int k = 0; k < plainLength; k++){
        
        printf("%c",cipherText[k]);
    }

    printf("\n");
        
    return 0;

}

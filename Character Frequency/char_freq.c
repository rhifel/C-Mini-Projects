#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[1000];
    int freq[256] = {0};

    printf("Enter a String: ");
    fgets(str, sizeof(str), stdin);

    // printf("%zu", sizeof(str));

    str[strcspn(str, "\n")] = '\0';

    for(int i = 0; str[i] != '\0'; i++){
        // //if(isalpha((unsigned char)str[i])){
        //     char c = tolower((unsigned char)str[i]);
        //     freq[c - 'a']++;
        // //}
        unsigned char c = str[i];
        freq[c]++;
    }

    printf("Character Frequency\n");
    for(int i = 0; i < 256; i++){
        if(freq[i] > 0){
            if( i == ' '){
                printf("Space: %d\n", freq[i]);
            }
            else if(isprint(i)){
                 printf("'%c' : %d\n", i, freq[i]);
            }
            else{
                printf("ASCII %d : %d\n", i, freq[i]);
            }
        }   
    } 
    return 0;  
}

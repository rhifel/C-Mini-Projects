#include <stdio.h>      
#include <stdlib.h>    
#include <string.h>     
#include <ctype.h>      
#include <stdbool.h>   
#include <unistd.h>

// Function Prototype
int is_ip_valid(char *ip), count_dots(char *ip);
void test_cases();

int main(void){
    char ip[100]; // Buffer to store user input
    int choice;

    printf("[1] Enter IP Manually\n[2] Run Test Cases\nEnter Choice: ");
    scanf("%d", &choice);
    if(choice == 1){
        while(1){
        printf("\nEnter Your IP Address: ");
        scanf("%99s", ip); // Read string safely (max 99 chars + null terminator)

        // Validate the IP and print result
        if(is_ip_valid(ip)){
            printf("%s is valid", ip);
            break;
        }
        else{
            printf("%s is not valid", ip);
        }
        sleep(1);
        }
    }
    else if(choice == 2){
        test_cases();
    }
    else{
        printf("Invalid Choice");
    }
    sleep(2);
    return 0;
}

// so I found that 192..168.56.1 is still getting accepted 
// so my solution is just count the number of dots 
// if its not equal to 3 it returns false
int count_dots(char *ip){
    int dots = 0;
    for(int i = 0; ip[i] != '\0'; i++){
        if(ip[i] == '.'){
            dots++;
            // printf("dots: %d\n", dots);
        }
    }
    return dots;
}
// Function to validate if a string is a valid IPv4 address
int is_ip_valid(char *ip){
    int segments = 0, range, len;
    char *token;
    int string_size = 100;

    // Check if input is NULL or empty
    if(ip == NULL || *ip == '\0')
        return false;

    if(count_dots(ip) != 3){
        return false;
    }

    // Make a copy of the input to avoid modifying the original
    char copy_ip[string_size];
    strncpy(copy_ip, ip, string_size);
    copy_ip[string_size - 1] = '\0'; // null-termination just to ensure the copy behave more predictable ->
                                     // and avoid crashing or undefined behavior

    // Start tokenizing the string by "."
    token = strtok(copy_ip, "."); // this one breaks strings into multiple pieces known as tokens ->
                                  // using delimeters in this case "."
    
    while(token != NULL){

        len = strlen(token); // Get length of current segment
        if(len == 0) return false; // Check for empty segment (e.g., "192..1.1" or 10.1..)
        
        // Check if all characters in the segment are digits
        for(int i = 0; i < len; i++){

            // Casting to unsigned char is a good practice with isdigit()
            // This one I acutally got from searching and reading the documentation
            if(!isdigit((unsigned char)token[i])) // originally I have if(!isdigit(token[i]))

                return false;

        }

        // Convert the segment to an integer
        range = atoi(token);
        
        // Validate that it's within 0 to 255
        if(range < 0 || range > 255)

            return false;

        // Move to the next token
        token = strtok(NULL, ".");
        segments++; // Increase the segment counter
        
    }

    // A valid IPv4 address must have exactly 4 segments
    if(segments != 4)

        return false;

    return true; // If all checks pass, the IP is valid
}

// its easier to test with this
void test_cases(){
    char *test_ips[] = {
        "192.168.1.1",
        "255.255.255.255",
        "10.0.0.1",
        "300.0.0.1",       
        "abc.def.ghi.jkl", 
        "192.168..1",      
        "127.0.0.1.5",     
        "172.16.254.1",    
        "",                
        "0.0.0.0"          
    };
    int total = sizeof(test_ips) / sizeof(test_ips[0]);

    printf("Running Test Cases:\n");
    for(int i = 0; i < total; i++){
        if(is_ip_valid(test_ips[i])){
            printf("%s is valid\n", test_ips[i]);
        }
        else{
            printf("%s is not valid\n", test_ips[i]);
        }
    }
}

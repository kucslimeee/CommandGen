#include<stdio.h>
#include <stdint.h>
#include "main.h"
#include "command.h"

/**
 * This function calculates the checksum of the input array and writes it to the output array.
*/
/*uint8_t checksum(int input[]){
    uint8_t checksum_var = 0;
    uint16_t sum = 0;
    for (int i = 0; i < 7; i++) {
        sum += input[i];
    }
    checksum_var = (uint8_t)sum;
    return checksum_var;
} */

uint8_t checksum(int item[]){     // this checksum calculates the number of set bits in an array of bytes
    uint8_t count = 0;                              	// return value
    uint8_t temp;                               // for storing seperately

    for (int i = 0; i < 7; i++) {                  // go through each byte

        temp = item[i];

            while (temp > 0) {
                temp &= (temp - 1); // Clears the least significant set bit
                count++;
            }
    }
    return count;
}



void commandGen(){
    int command[8] = {0};
    gen_command(command);
    command[7] = checksum(command);
    printf("w");
    for (int j = 0; j < 8; j++)
    {
        printf("%02X", command[j]);
    }
    printf("\n\n");
}

int getDecNum(char num){
    switch (num)
    {
        case 'A': return 10;
        case 'B': return 11;
        case 'C': return 12;
        case 'D': return 13;
        case 'E': return 14;
        case 'F': return 15;
        default: return (int)(num)-48;
    }
}

void readData(){
    char incomingData[33] = {0};
    int nums[16] = {0};
    printf("Type in the data coming from the space. The first letter must be r\n");
    scanf("%s", &incomingData);
    for (int i = 1; i < 33; i++)
    {
        if (i % 2 == 0)
        {
            nums[i/2-1] += getDecNum(incomingData[i]);
        }
        else
        {
            nums[i/2] += 16*getDecNum(incomingData[i]);
        }
        
    }
    printf("r ");
    for (int j = 0; j < 16; j++)
    {
        printf("%d ", nums[j]);
    }
    
    
    
}

void genTimesync() {
    int command[4] = {0};
    timesync_command(command);
    printf("l");
    for (int j = 0; j < 4; j++)
    {
        printf("%02X", command[j]);
    }
    printf("\n");
}

/**
 * The entry point of the program.
*/
int main(){
    char command;
    while (1)
    {
        printf("Type g if you want to generate a hexa command\n");
        printf("Type r if you want to read a hexa code, which was sent by the device\n");
        printf("Type t for timesync\n");
        printf("Press Ctrl + C at any point if you want to exit\n");
        scanf("%c", &command);
        if (command == 'g') commandGen();
        else if (command == 'r') readData();
        else if (command == 't') genTimesync();
    }
    return 0;
}
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lab2b.c
 * Author: kingJames
 *
 * Created on October 4, 2017, 1:21 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read(int count, char *file_name); //, char *key);
//void encrypt_file();
void write(int count, char *s, char *file_name);//writes to a file
void encrypt(char *s, char *key_file, char *cipher_file);//encrypt a message from a file
void make_rand_key(int count, char *key);//make random key
void decrypt(char *key, char *cipher_file, char *message);// decode a message from a file

/*
 * 
 */
int main(int argc, char** argv) {
    //char userinput[56];
    char option[2];// get user option
    char *s;//store message
    char *key_file;//the key file name
    char *cipher_file;//cipher file name
    printf("Enter:1 Encrypt file \nEnter:2 Decrypt file\nEnter:3 Exit program\n");
    gets(option);// get user input

    do {// goes until user enter 3
        // theses if statments check the uses input
        if (*option == '1') {
            encrypt(s, key_file, cipher_file);// call in encrypt function

        }
        if (*option == '2') {
           // printf("user selected option two ");
            //write(0, s, "write.txt");
            decrypt(key_file, cipher_file, s); // call decrypt function
        }
        printf("Enter:1 Encrypt file \nEnter:2 Decrypt file\nEnter:3 Exit program\n");

        gets(option);//get user option
    } while (*option != '3');// end if option is 3




    return (EXIT_SUCCESS);
}

/*this function read in the file and gets the size of the file and rewind the file and reads it again and store in input return input which is 
 * everything in the file
 */
char *read(int count, char *file_name)//, char *key) 
{


    //stor file
    char c; //store each character in the file 
    FILE *file = fopen(file_name, "r");//

    int i = 0; //counter
    if (file == NULL) //checks for file but i will later remove that
    {
        printf("file not found good bye");
        // return -1;
        exit(1); //ends program if file is null
    }//check for file

    if (count == 0) {
        while (fgetc(file) != EOF)// gets the size of the file 
        {
            count++; //counter to store the size of the file
        }//get count  
        //key = (char *) malloc(((sizeof (char)) * (count + 1)));
        //printf("this is the count %d\n", count);

        rewind(file);
    }

    char *input = (char *) malloc(((sizeof (char)) * (count + 1)));
//get eveything thats in the file
    while ((c = fgetc(file)) != EOF) { //printf("%c  %d\n",c, i);
        input[i] = c;
        i++;
    }
    input[i] = '\0';

    //printf("This is whats in the file \n%s\n", input);


    return input;
}
//write to a file
void write(int count, char *s, char *file_name) {
    FILE *file = fopen(file_name, "w");//open a new file
    int i = 0;
    //printf("This should be written to the file %s file name %s\n", s, file_name);

    for (i = 0; s[i] != '\0'; i++) {//this writes character by character to a file
        // printf("Character we are writing to the File = %c \n", clearFile[i]);
        // Let us use our fputc
        fputc(s[i], file);
    }

    fclose(file);

}

void encrypt(char *s, char *key, char *cipher_file) {

    char userinput[56];
    printf("Please enter the file name you would like to read in. ex: msg.txt\n");
    gets(userinput);

    int count = 0;
    int i = 0;
    s = userinput;
    s = read(0, s); //, key);
   // printf("this is  s %s", s);
    count = strlen(s);
    key = (char *) malloc(((sizeof (char)) * (count + 1)));
    make_rand_key(count, key); //pass key pointer and size of file to rand_key
    //write(0, s, "write.txt");//
    printf("the file has just been written\n");

    // cipher_file = (char *) malloc(((sizeof (char)) * (count + 1)));

    for (i = 0; i < count; i++) {
        // encrypted[i] = clearFile[i] ^ key[i % count];
        s[i] ^= key[i]; //% 2];
        //if (key[i] == EOF) {
        //   key[i] = 97;

        //}
        // if (key[i] == '\0') {
        //     key[i] = 98;
        //}
        //encrypted[i]= clearFile[i]^key[i%2];
    }
    //key[count-1] = '\0';
    printf("Please enter a name you would like to give your newly encrypted. ex:encryted.txt\n");
    gets(userinput);
    cipher_file = userinput; //"encrypted.txt";
    printf("This is the encrypted file %s\n", s);

    write(0, s, cipher_file);
    free(s);
    free(key);//free when function ends

}

void make_rand_key(int count, char *key) {
    int i = 0;
    char userkeyfilename[56];

    char eachKeyLetter;
    srand(time(NULL));

    //printf("Key count %d  \n", count, strlen(key));

    for (i = 0; i < count; i++) { //printf("i=%d\n", i);
        key[i] = (char) (rand() % 256);
        if (key[i] == -1)//EOF)
        {
            key[i] = -2; //'a';

        }
        if (key[i] == 0)//'\0')
        {
            key[i] = 1;
        }

    }
    //key[count - 1] = '\0';
    key[count] = '\0';
     printf("Please enter a save name for your key file. ex:key.txt\n");
    gets(userkeyfilename);//gets the key file name   
    write(count, key, userkeyfilename);//"key.txt");
    printf("this is the key %s \n", key);


}
//end makerandKey

//this file decrypts a messages it takes a key and  cipher and a message
void decrypt(char *key, char *cipher_file, char *message) {
    int count = 0;
    int i = 0;
    char userinput[56];
    printf("Please enter the name of file you would like to decrypt. ex:ercryted.txt\n");
    gets(userinput);
    cipher_file = userinput;
    cipher_file = read(0, cipher_file); //, key);   
 /* cipher_file = "encrypted.txt";
    key = read(0, "key.txt");
  */
     printf("Please enter the name of the key file. ex:key.txt\n");
    gets(userinput);//gets the key file name
    key = userinput;// save file name in key
    key = read(0, key);//pass the key file to the read file to be read
    count = strlen(cipher_file);// gets the length of the key file
    //printf("%d count\n", count);
  
    message = (char *) (malloc(count)); //exit(0);

    for (i = 0; i < count; i++) {
     
        message[i] = key[i]^cipher_file[i];//decrypts message

      
    }//end for
    // message[i] = '\0';
//    printf("this should be the message decrypted %s\n", message);
     printf("Please enter the name of the new decrypt you would like to save ex:newmasge.txt\n");
    gets(userinput);//i stop here i have to get the user to enter the name they would like to save the msg with
    write(count, message, userinput);//get userinput from user which will get the newly decrypt message a file name
    // free(message); //free when function ends
    //printf("%s\n",message);
    free(key);
    free(cipher_file);
    free(message);
}// end Decrypt

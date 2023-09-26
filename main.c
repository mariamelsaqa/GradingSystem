//
//  main.c
//  OS_Lab1
//
//  Created by Mariam Elsaqa on 07/02/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

//"/Users/mariamelsaqa/Desktop/OS lab/OS_Lab1/OS_Lab1/students.txt"

char filename[30];

typedef struct{
    char* name;
    float GPA;
    int ID;
} student;

 int Number_ofStudents(char *filename)
 {

   FILE *fp = fopen(filename,"r");
   int ch=0;
   int lines=0;

   while(!feof(fp))
 {
   ch = fgetc(fp);
   if(ch == '\n')
   {
     lines++;
   }
 }
   fclose(fp);
   return lines;
 }
 

void get_fileName(void){
    printf("%s\n","Enter the name of the file");
    scanf (" %[^\n]s", filename);
}

//takes a list of student structs and file name, then writes the struct objects to a file with the name given
void write_data(student* s,char* fileName, int size){
    
    FILE *file = fopen(filename, "a");
    if(file == NULL)
       {
          printf("Error!\n");
          exit(1);
       }
    
    for (int i=0; i < size; i++) {
        fprintf(file,"%s,%d,%f\n", s[i].name,s[i].ID,roundf(s[i].GPA * 100) / 100);
    }
    fclose(file);
}

//takes the name of the file, then reads and returns the data as a list of structs.
student* get_data(char* fileName){
    int numOfStudent = Number_ofStudents(filename);
    student* s = (student*) malloc(numOfStudent*4);

    FILE *file = fopen(filename, "r");
    if(file == NULL)
    {
          printf("Error!\n");
          exit(1);
    }
    char line[255];
    int i = 0;
    while (fgets(line, 255, file) != NULL)
    {
        char *buffer;
        buffer = strtok(line, ",");
        s[i].name = (char *)malloc(512);
        strcpy(s[i].name, buffer);
        buffer = strtok(NULL, ",");
        int id = atoi(buffer);
        s[i].ID = id;
        buffer = strtok(NULL, ",");
        float gpa = atof(buffer);
        s[i].GPA = gpa;
        i++;
    }
    
    fclose(file);
    return s;
}

student* take_input(int *i){
    student* s = malloc(512);
    char* name = (char*) malloc(512);
    int id;
    float gpa;
    
    do{
        printf("Enter student name\n");
        scanf("%s",name);
        s[*i].name = (char *)malloc(512);
        strcpy(s[*i].name, name);
        if(strcmp(name,"?") == 0){
            break;
        }
        printf("Enter student id\n");
        scanf("%d",&id);
        s[*i].ID = id;
        
        printf("Enter student gpa\n");
            scanf("%f",&gpa);
        s[*i].GPA = gpa;
        *i = *i + 1;
    }while(strcmp(name,"?") != 0);
//    printf("i: %d\n", *i);
//    for (int j=0; j < *i; j++) {
//        printf("name-> %s, ID-> %d, gpa->%.2f",s[j].name, s[j].ID, s[j].GPA);}
    
    return s;
}

//takes a list of student structs and prints on the screen the average, standard deviation, min and max of the GPAs
void print_stats(student* s){
    int numOfStudent = Number_ofStudents(filename);
    float sum = 0.0, avg, SD = 0.0, variance =0.0, min, max;
    for (int i=0; i<numOfStudent; ++i) {
        sum += roundf(s[i].GPA * 100) / 100;
    }
    avg = sum / numOfStudent;
    
    for (int i=0; i<numOfStudent; ++i) {
        variance += pow((roundf(s[i].GPA * 100) / 100)-avg,2);
    }
    
    SD = sqrt(variance/numOfStudent);
    
        min=max=s[0].GPA;
        for(int i=0; i<numOfStudent;i++)
        {
             if(min>s[i].GPA)
              min=s[i].GPA;
               if(max<s[i].GPA)
                max=s[i].GPA;
        }
    
    printf("The average of GPAs is = %.2f\nStandart Deviation of GPAs is =  %.2f\nMaximum GPA is = %.2f\nMinimum GPA is = %.2f\n", avg , SD, max , min);
    
}

//takes a list of student structs and prints them on the screen in table format
void print_data(student* s){
    int numOfStudent = Number_ofStudents(filename);
    printf("Name\t\t\tID\t\t\tGPA\n");
    for (int i=0; i<numOfStudent; ++i) {
        printf("%-5s\t\t%d\t\t%.2f\n", s[i].name, s[i].ID, (roundf(s[i].GPA * 100) / 100));
    }
}

int main(int argc, const char * argv[]) {
    
    char choice = '\0';
    printf("Do you want to: \n a. Read students' data \n b. Enter students' data \n c. Calculate statistics of students' data \n d. Exit the program \n");
    scanf("%c", &choice);
    while (choice != 'a' && choice != 'b' && choice != 'c' && choice != 'd'){
        printf("%s\n","Invalid answer");
        scanf("\n%c", &choice);
    }
    int i= 0;
    //If a, b or c are chosen, then prompt the user to enter the name of the file.
    switch (choice) {
        case 'a': //If a is chosen, then print the data in the file given.
            get_fileName();
            student* s = get_data(filename);
            print_data(s);
            break;
            
        case 'b': //If b is chosen, then allow the user to keep entering students’ data till a reserved character is entered. Next, write the data to a file with the name given.
            get_fileName();
            student* st = take_input(&i);
            write_data(st,filename,i);
            break;
            
        case 'c': //If c is chosen, then display statistics of the data in the file given.
            get_fileName();
            student* stu = get_data(filename);
            print_stats(stu);
            break;
            
        case 'd': //If d is chosen, then exit the program.
            exit(0);
            break;
            
        default:
            break;
    }
    
    
}
 

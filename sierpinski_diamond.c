#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_Row(int row,int H,int L) /*Function to print rows of respective stars and spaces*/
{
        
        FILE * fp; 
        if( L == 1 ) /*Builds rows for the basic level of the triangle*/
        {       
                int col; 
                for( col = 1 ; col <= (H/2)+1-row ; col++ ) /*Loop for the first set of spaces, written to a file*/
                {       
                        fp = fopen("sierdiamond.txt", "a");
                        fprintf(fp," ");
                        fclose(fp);
                }
                for( col = 1 ; col <= (2*row)-1 ; col++ ) /*Loop for the set of stars, written to a file*/
                {       
                        fp = fopen("sierdiamond.txt", "a");
                        fprintf(fp,"*");
                        fclose(fp);
                }
                for( col = 1 ; col <= (H/2)+1-row ; col++ ) /*Loop for the second set of spaces, written to a file*/
                {       
                        fp = fopen("sierdiamond.txt", "a");
                        fprintf(fp," ");
                        fclose(fp);
                }
        }
        else if( row <= (H+1)/4 ) /*Builds rows for the top triangle*/
        {       
                for(int i=1; i <= (H+1)/4; i++) /*Loop for the first box of spaces, written to a file*/
                {       
                        fp = fopen("sierdiamond.txt", "a");
                        fprintf(fp," ");
                        fclose(fp);
                }
                
                print_Row(row,H/2,L-1); /*Call print_Row again, with L-1*/
                
                for(int i=1; i <= (H+1)/4; i++) /*Loop for the second box of spaces, written to a file*/
                {       
                        fp = fopen("sierdiamond.txt", "a");
                        fprintf(fp," ");
                        fclose(fp);
                }
        }
        else /*Builds rows for bottom triangles*/
        {       
                print_Row(row-((H+1)/4),H/2,L-1); /*Call print_Row again, with row being a quarter of the original triangle's height and L-1*/
                fp = fopen("sierdiamond.txt", "a");
                fprintf(fp," "); /*Print the space between triangles, written to a file*/
                fclose(fp);
                print_Row(row-((H+1)/4), H/2, L-1); /*Call print_Row again, with row being a quarter of the original triangle's height and L-1*/
        }
}

int myPow(int x,int n) /*Function to get a number to the power of another number*/
{               
                int i; 
                int number = 1;
                
                for (i = 0; i < n; ++i) /*Loop to multiply the first argument by itself as many times as the value of the second argument*/
                {
                number *= x; /*Multiplies the number by itself*/
                }
                return(number);
}

int isPowerOfTwo(int n) /*Function to check if the input is a power of 2*/
{
        if ( n & n - 1) /*Checks if the bits of n and n-1 are equal, if not it returns 0, if they are it returns 1*/
        {
                return 0;
        }
        return 1;
}

void main(int argc, char *argv[])
{
        if( argc != 3 ) /*Test to see if 2 arguments are inputed along with the program name*/
        {
                printf("ERROR: Wrong number of arguments. Two required.\n");
                exit(0);
        }

        /*Extract the arguments, assign variables*/
        char *height = argv[1];
        int H = atoi(height);
        float h = atof(height);
        char *level = argv[2];
        int L = atoi(level);
        int row;
        int HT = (H/2)+1;
        FILE * fp;

        if( H % 2 == 0 || H <= 0 || H != h ) /*Test to see if input is an odd positive integer*/
        {
                printf("ERROR: Bad argument. Height must be positive odd integer.\n");
                exit(0);
        }

        if( isPowerOfTwo(HT) == 0 || HT < myPow(2,L-1)) /*Test to see if the triangle height is a power of 2, and that the triangle height is >= 2^(L-1)*/
        {
                printf("ERROR: Height does not allow evenly dividing requested number of levels\n");
                exit(0);
        }

        for( row = 1; row <= H/2+1 ; row++) /*Loop through print_Row for the rows of the upper half of the diamond, writes the newline to the file*/
        {
                fp = fopen("sierdiamond.txt", "a");
                print_Row(row,H,L);
                fprintf(fp,"\n");
                fclose(fp);
        }

        fp = fopen("sierdiamond.txt","r"); /*Finds the size of the file containing the top half of the diamond*/
        size_t sz;
        fseek(fp,0,SEEK_END);
        sz=ftell(fp);
        rewind(fp);

        char arr[sz+1]; /*Creates array of size sz+1 and reads the file into it*/
        fread( arr,1,sz+1,fp);
        int i;
        for(i = 0; i < sz; i++){
                printf("%c",arr[i]);
        }
        
        for( i = sz-H-3 ; i >= 0 ; i--) /*Loops backwards through the array starting at the second to last row of stars (don't want to repeat the middle)*/
        {
                printf("%c",arr[i]); /*Prints the character at the ith location in the array*/

        }
        printf("\n");

        remove("sierdiamond.txt"); /*Delete the diamond text file after output is complete*/
}

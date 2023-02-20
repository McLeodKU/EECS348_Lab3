/*
 * Author: Michael Oliver 
 * Date: 2/9/2023
 * Last Edit: 2/11/2023
 * KU ID: 3016991
 * Purpose: EECS 348 Lab exercise  
 * Key take away: this was horrible -- not proud of this 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MONTHS 12
const char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
char const *six_months[] = {"January\t\t- June\t", "February\t- July\t", "March\t\t- August", "April\t\t- September", "May\t\t- October", "June\t\t- November", "July\t\t- December"}; // I was in caveman brain mode -- so this is hard coded -- really wish I could of used only one list but I don't have the patience or time to 

int sales_reports(float sales[]){ // prints out money along with month -- easy to understand 
	int i;
	printf("Month\t\tSales\n");
	for(i = 0; i < 12; ++i){
		printf("%s", months[i]);
		if (strlen(months[i]) >= 8){
			printf("\t");
		}
		else{
			printf("\t\t");
			}
		printf("$%5.2f \n", sales[i]);
	}
		return 0; // sales report completed correctly
}


int min_max_avg(float sales[MONTHS]){ // where the caveman brain begun 
	int num = 0;
	float max = -1;
	float min = -1;
	int max_month, min_month, i;
	float avg = 0;

	printf("\nSales summary: \n");

	for(i = 0; i < 12; ++i){
		if (max == -1 || min == -1){ // if nothing is max or min then set both
			max = sales[i];
			min = sales[i];
			max_month = num;
			min_month = num;
		}
		else if (max < sales[i]){ // if the new num is bigger than the current -- new max set 
			max_month = num;
			max = sales[i];
		}
		else if (min > sales[i]){ // if the new num is less than the current -- new min set
			min_month = num;
			min = sales[i];
		}
		avg += sales[i]; // each time the for loop iterates average is added to 
		num += 1; // tracker for the max month and min month 
	}
	printf("Maximum Sales: \t $%5.2f \t (%s)\n", max, months[max_month]); // I hated these print statements -- probably took me the most time in the lab -- I originally using SALES[MONTHS] to try and return a string however it would return a symbol instead -- ngl got hurt by this one 
	printf("Minimum Sales: \t $%5.2f \t (%s)\n", min, months[min_month]);
	printf("Average Sales: \t $%5.2f \n\n", avg/12);
	return 0;
}


int six_month_avg(float sales[MONTHS]) { // six_month_avg was easy to understand however I am not proud of the six_month array that I declared
	int i;
	float six_avg;
	printf("Six-Month Moving Average Report\n");

	for (i= 0; i < 7; ++i){
		six_avg = sales[i] + sales[i+1] + sales[i +2] + sales[i + 3] + sales[i + 4] + sales[i + 5]; // I think that there is a better way to do this with a for in loop but decided against it 
		six_avg = six_avg/6;
		printf("%s\t $%5.2f\n", six_months[i], six_avg);
	}
	return 0;
}

int floatcomp(const void* num1, const void* num2) // quick_sort !!! what I used to help me: https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
{
    if(*(const float*)num1 < *(const float*)num2) // uses a lot of pointers to organize data? -- still learning how to use but this work for now  -- only thing I dislike about it is I wish I had the ability to quickly sort the month along with the floating point numbers  
        return 1;
    if(*(const float*)num1 > *(const float*)num2)
        return -1;
    return 0;
}

int print_sales_descending(float sales[MONTHS]) { // spent too much time on this 
        int i;
	int j;
	float orgin[MONTHS];
	printf("\nSales Report (Highest to Lowest)\nMonths\t\t\tSales\n");
	for (i = 0; i < MONTHS; i++) { // in C you can't just make a copy of a list like in python -- learned that the hard way -- make a copy with a for in loop
 	   orgin[i] = sales[i];
	}

        qsort(sales, MONTHS, sizeof(float), floatcomp); // function call for qsort -- it uses floatcomp
        for(i = 0; i < MONTHS; i++){
		for (j = 0; j < MONTHS; j++){		// I had no idea on how to keep track of the months along with the sorted data so I went with the approach of making a copy before altering the list -- then finding matches -- pretty primative -- I saw I could of used a dictionary but I wouldn't of understood the code
			if (orgin[j] == sales[i]){
				printf("%s\t", months[j]);			
				if (strlen(months[j]) >= 8){
                                	printf("\t");
                        	}
                        	else{
                                	printf("\t\t");

				}

			printf("$%5.2f\n", sales[i]);
			}	

	}

}
return 0;
}


int main() { // main or driver 
	float sales[MONTHS];
	FILE *fp;
	int i;
	char filename[100];
	printf("Enter filename: ");
	scanf("%s", filename);

	fp = fopen(filename, "r"); // open the file for reading
				   
	if (fp == NULL) { // check to see if file was opened correctly
		printf("Error opening file\n");
		return 1;
	}
	for (i = 0; i < MONTHS; i++) { // Read sales data from the file
		fscanf(fp, "%f", &sales[i]);
	}
			// close the file
	fclose(fp);	// function calls 
	sales_reports(sales);
	min_max_avg(sales);
	six_month_avg(sales);
	print_sales_descending(sales);
	return 0;	// congrats we've finished
}

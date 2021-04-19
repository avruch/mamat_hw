#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PASS_GRADE 55
#define HUNDRED 100
#define LINE_LENGTH 10

int calc_median(int hist[HUNDRED],int number_of_grades);
float calc_pass_rate(float number_of_grades,float passing_stud);
float calc_avg(float number_of_grades,float sum);
void print_all(int number,float avg,int median,int max,int min,float pass_rate\
	,int hist[]);


int main(int argc, char *argv[]) {
	int temp,median=0,number_of_grades=0,min=HUNDRED,max=0,sum=0,passing_stud=0;
	int hist[HUNDRED]={0};
	float pass_rate=0,avg=0;

	if (argc < 1) {
    	fprintf(stderr, "Error\n");
        return 1;
    }

	FILE *fp;
	char  path_dst[HUNDRED];
	strcpy(path_dst, argv[1]);


	fp = fopen(path_dst,"r");
	if(fp == NULL){
		return 1;
	}

	while((fscanf(fp,"%d",&temp)) != EOF){
		number_of_grades++;
		hist[temp-1]++;
		sum+=temp;
		if(temp>=PASS_GRADE){
			passing_stud++;
		}
		if(temp>max){
			max=temp;
		}
		if(temp<min){
			min=temp;
		}
	}

	pass_rate=calc_pass_rate((float)number_of_grades,(float)passing_stud);
	avg=calc_avg((float)number_of_grades,(float)sum);
	median=calc_median(hist,number_of_grades);
	print_all(number_of_grades,avg,median,max,min,pass_rate,hist);
	fclose(fp);
    return 0;
}
/**
 * @brief calculate passing rate 
 * @param number of grades
 * @param number of passing students
 * @Returns the passing rate in percent
 */
float calc_pass_rate(float number_of_grades,float passing_stud){
		return (passing_stud/number_of_grades)*HUNDRED;
	}
/**
 * @brief calculate the avg
 * @param number of grades
 * @param sum of grades
 * @Returns the avg
 */
float calc_avg(float number_of_grades,float sum){
		return (sum/number_of_grades);
	}
/**
 * @brief calculate the median grade
 * @param number of grades
 * @param histogram of grades
 * @Returns the median grade
 */	
int calc_median(int hist[HUNDRED],int number_of_grades){
	int i=0;
	for (int j=0;j<HUNDRED;j++){
		for(int k=0;k<hist[j];k++){
			if (i<(number_of_grades/2)){
				i++;
			}
			else {
				return j+1;
			}
		}
	}
}
/**
 * @brief print all
 * @param number of grades
 * @param avg of grades
 * @param median of grades
 * @param max of grades
 * @param min of grades
 * @param pass rate of grades
 * @param histogram of grades
 */	
void print_all(int number,float avg,int median,int max,int min,float pass_rate\
	,int hist[HUNDRED]) {
	 printf("num of students = %d\n",number);
	 printf("avg = %0.3f""\n",avg);
	 printf("the median is - %d\n",median);
	 printf("max grade = %d, min grade = %d\n",max,min);
	 printf("pass rate = %0.2f%""\n",pass_rate);
	 
 	for (int i=0;i<LINE_LENGTH;i++) {
		for (int j=0;j<LINE_LENGTH;j++) {
			printf("%d ",hist[i*LINE_LENGTH+j]);
			}
			printf("\n");
		}
		
}

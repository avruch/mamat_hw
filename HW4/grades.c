#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked-list.h"
#include "grades.h"
#define	MIN_GRADE 0
#define	MAX_GRADE 100

/*linked list  user function declarations*/
int course_clone(void *element, void **output);
void course_destroy(void *element);

int student_clone(void *element, void **output);
void student_destroy(void *element);

//the ADT's we create to suuport the requierd functions.
struct course {
	const char* name;
	int grade;
};

struct student {
	const char* name;
	int id;
	struct list *courses_list;
	};

struct grades {
	struct list *students_list;
};

/**
 * @brief creates clone of element given
 * @param element pointer to the element we want to clone
 * @param output pointer to the pointer of the cloned elemnt
 * @Returns 0 on success 
 */
int course_clone(void *element, void **output) {
	struct course *clone = (struct course *)element;
	struct course *new_course = (struct course*)malloc(sizeof(struct course));
			if(!new_course) {
				return 1;
			};
	new_course->name = (const char*)malloc(sizeof(char)*(strlen(clone->name)+1));
		if(!(new_course->name)) {
					return 1;
				};
	strcpy(new_course->name,clone->name);
	new_course->grade = clone->grade;
	*output= new_course;
	return 0;
}
/**
 * @brief free memory alocated for element
 * @param element pointer to the element to free
 * @return -always succeed  NULL if element does not exist
 */
void course_destroy(void *element) {
	if (!element) {
		return NULL;
	}
	struct course *clone = (struct course *)element;
	free(clone->name);
	free(clone);
	return;
}
/**
 * @brief creates clone of element given 
 * in this case a student name,id, and courses list whice are an ADT
 * @param element pointer to the element we want to clone
 * @param output pointer to the pointer of the cloned elemnt
 * @Returns 0 on success 
 */
int student_clone(void *element, void **output) {
	struct student *clone=(struct student*)element;
	struct student *new_student=(struct student*)malloc(sizeof(struct student));
			if(!new_student) {
				return 1;
			}
	new_student->name=(const char*)malloc(sizeof(char)*(strlen(clone->name)+1));
		if(!(new_student->name)) {
					return 1;
				}
	strcpy(new_student->name,clone->name);
	new_student->id = clone->id;
	new_student->courses_list=clone->courses_list;
	*output= new_student;
	return 0;
}
/**
 * @brief free memory alocated for element
 * @param element pointer to the element to free
 * @return -always succeed  NULL if element does not exist
 */
void student_destroy(void *element) {
	if (!element) {
		return NULL;
	}
	struct student *clone = (struct student *)element;
	list_destroy(clone->courses_list);
	free(clone->name);
	free(clone);
	return;
}
/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, of NULL in case of an error
 */
struct grades* grades_init() {
	struct grades *grades=(struct grades *)malloc(sizeof(struct grades));
		if(!grades) {
						return NULL;
					};
	grades->students_list=list_init(student_clone,student_destroy);
	return grades;
}
/**
 * @brief Destroys "grades", de-allocate all memory!
 */
void grades_destroy(struct grades *grades){
	list_destroy(grades->students_list);
	free(grades);
}
/**
 * @brief find a student by his or her id.
 * @returns A pointer to the specific student ,or NULL if doesn't exist.
 */
static struct student* find_student(struct grades *grades,int student_id) {
	struct student *new_student;
	struct node *current=list_begin(grades->students_list);
	while(current){
		new_student = (struct student *)list_get(current);
			if (new_student->id==student_id) {
				return new_student;
			}
		current= list_next(current);
	}
	return NULL;
}
/**
 * @brief find a course by it name.
 * @returns A pointer to the specific course ,or NULL if doesn't exist.
 */
static struct course* find_course(struct list *courses_list,const char *course_name) {
	struct course *new_course;
	struct node *current=list_begin(courses_list);
	while(current){
		new_course = (struct course*)list_get(current);
		if(!(strcmp(new_course->name,course_name))){
				return new_course;
			}
		current= list_next(current);
	}
return NULL;
}
/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Failes if "grades" is invalid, or a student with 
 * the same "id" already exists in "grades"
 */
int grades_add_student(struct grades *grades,const char *student_name,int student_id){
	if (find_student(grades,student_id)){
		return 1;
	}
	struct student *new_student=(struct student*)malloc(sizeof(struct student));
		if(!(new_student)) {
			return 1;
		}
	new_student->id=student_id;
	new_student->name =(const char*)malloc(sizeof(char)*(strlen(student_name)+1));
		if(!(new_student->name)) {
					return 1;
			}
	strcpy(new_student->name,student_name);
	new_student->courses_list = list_init(course_clone,course_destroy); 
	if(!(new_student->courses_list)) {
			
			return 1;
		}
		int val=list_push_back(grades->students_list, new_student);
		free(new_student->name);
		free(new_student);
	return val;
}

/**
 * @brief Adds a course with "name" and "grade" to the student with "id"
 * @return 0 on success
 * @note Failes if "grades" is invalid, if a student with "id" does not exist
 * in "grades", if the student already has a course with "name", or if "grade"
 * is not between 0 to 100.
 */
int grades_add_grade(struct grades *grades, const char *name,
                     int id, int grade)
{ 
	if(!grades){
		return 1;
	}
	if((grade<MIN_GRADE)||(grade>MAX_GRADE)){
		return 1;
	}
	struct student *student;
	if(!find_student(grades,id)){
		return 1;
	}	
	student=find_student(grades,id);
	if(find_course(student->courses_list,name)){
		return 1;
		}
	struct course *new_course = (struct course*)malloc(sizeof(struct course));
	if (!new_course) {
		return 1;
	}
	new_course->name =(const char*)malloc(sizeof(char)*(strlen(name)+1));
		if(!(new_course->name)) {
					return 1;
			}
	strcpy(new_course->name,name);
	new_course->grade = grade;
	int val=list_push_back(student->courses_list, new_course);
	free(new_course->name);
	free(new_course);
	return val;
}
	
/**
 * @brief calculates the average of the grades in given list of courses
 * @returns the calculated average .
 */
static float avg_list(struct list *list) 
{
	int len = list_size(list);
	if (!len) {
		return 0;
	}

	float sum = 0;
	struct node *current = list_begin(list);
	struct course *course;
	for (int i = 0; i < len; i++) {
		course = (struct course *)list_get(current); 
		sum += course->grade;
		current = list_next(current);
	}

	return sum / len;
}
/**
 * @brief Calcs the average of the student with "id" in "grades".
 * @param[out] out This method sets the variable pointed by "out" to the
 * student's name. Needs to allocate memory. The user is responsible for
 * freeing the memory.
 * @returns The average, or -1 on error
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note If the student has no courses, the average is 0.
 * @note On error, sets "out" to NULL.
 */
float grades_calc_avg(struct grades *grades, int id, char **out) {
	
	struct student *student = find_student(grades, id);
	if (!student) {
		*out = NULL;
		return -1;
	}

	float avg = avg_list(student->courses_list);
	*out = malloc(strlen(student->name)*sizeof(char));
	strcpy(*out, student->name);

	return avg;

}

/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_student(struct grades *grades, int id){
	if(!grades){
		return 1;
	}
	struct student *student;
	student = find_student(grades,id);
		if (!student){
			return 1;
		}	
		printf("%s %d: ", (student->name),(student->id));
		struct node *current=list_begin(student->courses_list);
		while(current){
			struct course *new_course = (struct course*)list_get(current);
			printf("%s %d", (new_course->name),(new_course->grade));
			current= list_next(current);
			if (current){
				printf(", ");
			}
		}
		printf("\n");
		return 0;
}


/**
 * @brief Prints all students in "grade", in the following format:
 * STUDENT-1-NAME STUDENT-1-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * STUDENT-2-NAME STUDENT-2-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid
 * @note The students should be printed according to the order 
 * in which they were inserted into "grades"
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_all(struct grades *grades){
	if(!grades){
		return 1;
	}
	struct node *current;
	struct student *student;
	int val;
	current = list_begin(grades->students_list);
	while(current){
		student=(struct student*)list_get(current);
		val=grades_print_student(grades, student->id);
		if (val){
			printf("student %s failed\n", student->name);
		}
		current= list_next(current);
		
	}
	return 0;
}



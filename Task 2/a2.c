// 205978000
//shahaf zohar

//#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structures
typedef struct student {
    char* name;
    int  id;
    struct clist* courses;
} student;

typedef struct course {
    char* title;
    int  number;
    struct slist* students;
} course;

typedef struct slist {
    student* info;
    struct slist* next;
} slist;

typedef struct clist {
    course* info;
    struct clist* next;
} clist;


// prototypes
slist* add_student(slist* students, char* name, int id);
clist* add_course(clist* courses, char* title, int number);
clist* InsertCourses(clist* head, course* newNode);
slist* insertstudent(slist* head, student* newNode);
slist* sortedstudent(slist *head, slist *newNode);
clist* sortedcourses(clist *head, clist *newNode);
student *SearchStudent(slist *head, int key);
course *SearchCourse(clist *head, int key);
void reg_student(slist* students, clist* courses, int id, int number);
void unreg_student(slist* students, int id, int number);
void print_students(slist* students);
void print_courses(clist* courses);
void free_all(slist* sl, clist* cl);
slist *Cleanstudent(slist *liststudents, student *STD);



// while keeping it sorted ascending by key
slist* insertstudent(slist* head, student* newNode) {
    slist* dynamicallystudent;
    slist* currItem = head;
    dynamicallystudent = (slist*)malloc(sizeof(slist));
    if (dynamicallystudent == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    if (!head->info) {
        head->info = newNode;
        head->next = NULL;
        return head;
    }
    //      check if newNode's number is smaller than all number and should be first
    if ((newNode->id) < (head->info->id)) {
        dynamicallystudent->info = newNode;
        dynamicallystudent->next = head;
        return dynamicallystudent;}
    
    while (currItem->next && (newNode->id > currItem->next->info->id)){
        currItem = currItem->next;}
 //          put newNode between currItem and currItem->next
 //          (if currItem is last then currItem->next == NULL)
    dynamicallystudent->info = newNode;
    dynamicallystudent->next = currItem->next;
    currItem->next = dynamicallystudent;
    return head;
    }


clist* InsertCourses(clist* head, course* newNode) {
    clist* currItem = head;
    clist* dynamicallycourse;
    dynamicallycourse = (clist*)malloc(sizeof(clist));
    if (dynamicallycourse == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    if (!head->info) {
        head->info = newNode;
        head->next = NULL;
        return head;
    }
    //check if newNode's number is smaller than all number and should be first
    if ((newNode->number) < (head->info->number)) {
        dynamicallycourse->info = newNode;
        dynamicallycourse->next = head;
        return dynamicallycourse;
    }
    while (currItem->next && newNode->number > currItem->next->info->number) {
        currItem = currItem->next;
    }
    //put newNode between currItem and currItem->next
    //(if currItem is last then currItem->next == NULL)
    dynamicallycourse->info = newNode;
    dynamicallycourse->next = currItem->next;
    currItem->next = dynamicallycourse;
    return head;
}

// while keeping it sorted ascending by key
slist* sortedstudent(slist *head, slist *newNode) {
    if (!head)
        return newNode;
//check if newNode's key is smaller than all id and should be first
    if (newNode->info->id < head->info->id) {
        newNode->next = head;
        return newNode;}
    head->next = sortedstudent(head->next, newNode);
    return head;
}

clist* sortedcourses(clist *head, clist *newNode){
    if (!head){
        return newNode;}
//check if newNode's key is smaller than all keys and should be first
    if (newNode->info->number < head->info->number) {
        newNode->next = head;
        return newNode;}
    head->next = sortedcourses(head->next, newNode);
    return head;
}

slist* add_student(slist* students, char* name, int id)
{
    if (!students){
        student* std;
        std = (student*)malloc(sizeof(student));          /*  Opend spces for info {name, id} */
        students = (slist*)malloc(sizeof(slist));        /*   Allocated dynamically          */
        if (std == NULL && students == NULL) {
            printf("Memory allocation error!\n");
            exit(1);}
        std->id = id;                                   /*    Add information to            */
        std->name = strdup(name);                      /*     Cope string{name} to string  */
        std->courses = NULL;
        students->info = std;                         //Copy information to slist 
        students->next = NULL;
        return students;
    }
    slist* point;
    point = students;
    slist* copy;
    student* std;
    std = (student*)malloc(sizeof(student));   /*   Opend spces for info {name, id}    */
    copy = (slist*)malloc(sizeof(slist));     /*  Allocated dynamically     */
    if (std == NULL || copy == NULL) {
        printf("Memory allocation error!\n");
        exit(1);}
    std->id = id;                                          /*      Add information to   */
    std->name = strdup(name);                             /* Cope string{name} to string   */
    std->courses = NULL;
    copy->info = std;
    copy->next = NULL;
    return sortedstudent(point , copy);         
}

clist* add_course(clist* courses, char* title, int number)
{
    if (!courses) {
            course* cour;
            cour = (course*)malloc(sizeof(course));
            courses = (clist*)malloc(sizeof(clist));       // Allocated dynamica
            cour->number = number;
            cour->title = strdup(title);
            cour->students = NULL;
            courses->info = cour;                 // Copy information to clist 
            courses->next = NULL;
            return courses;}
    clist* point;
    point = courses;
    clist* copy;
    course* cour;
    cour = (course*)malloc(sizeof(course)); /*   Opend spces for info {name, id}   */
    copy = (clist*)malloc(sizeof(clist));  /*     Allocated dynamically        */
    cour->number = number;                /*  Add information to           */
    cour->title = strdup(title);         /*  Cope string{name} to string  */
    cour->students = NULL;
    copy->info = cour;                  //Copy information to clist 
    copy->next = NULL;
    return sortedcourses(point, copy);
}

void reg_student(slist* students, clist* courses, int id, int number){
    slist* ptlist;
    clist* ptr;
    ptlist = students;
    ptr = courses;
    while (ptlist->info->id != id) {
        ptlist = ptlist->next;
    }
    while (ptr->info->number != number) {
        ptr = ptr->next;
    }
    if (!ptlist->info->courses) {
        ptlist->info->courses = (clist*)malloc(sizeof(clist));
        ptlist->info->courses->info = NULL;
    }
    if (!ptr->info->students) {
        ptr->info->students = (slist*)malloc(sizeof(slist));
        ptr->info->students->info = NULL;        
    }
    ptlist->info->courses = InsertCourses(ptlist->info->courses, ptr->info);
    ptr->info->students = insertstudent(ptr->info->students, ptlist->info);
}

student* SearchStudent(slist *head, int key){
    while (head) { //loop through the list
        if (head->info->id == key){
            return head->info;}
        head = head->next;}
//didn't find the item with the requested key
    return NULL;}

course *SearchCourse(clist *head, int key){
    while (head) { //loop through the list
        if (head->info->number == key){
            return head->info;}
        head = head->next;}
//didn't find the item with the requested key
    return NULL;}

slist *Cleanstudent(slist *liststudents, student *STD){
    slist *curr, *prev = NULL;
    if(!liststudents){
        return NULL;}
    if(liststudents->info == STD){
        curr = liststudents;
        liststudents = liststudents->next;
        free(curr);
        return liststudents;}
    curr = liststudents;
    curr = curr->next;
    while(curr){
        if(curr->info == STD){
            prev->next = curr->next;
            free(curr);
            return liststudents;}
        prev = curr;
        curr = curr->next;}
    return NULL;
        }

clist *Cleanscoures(clist *listscourse, course *cour){
    clist *curr, *prev = NULL;
    curr = listscourse;
    if(!listscourse){
        return NULL;}
    if(listscourse->info == cour){
        listscourse = listscourse->next;
        free(curr);
        return listscourse;}
    while(curr){
        if(curr->info == cour){
            prev->next = curr->next;
            free(curr);
            return listscourse;}
        prev = curr;
        curr = curr->next;}
        return NULL;
}
 
   
void unreg_student(slist* students, int id, int number){
    student *STD = SearchStudent(students,id);    //Student search and return of a student-type pointer
    course *COUR = SearchCourse(STD->courses,number);   //course search and return of a course-type pointer
    COUR->students = Cleanstudent(COUR->students, STD);   //remove the student from the list of courses
    STD->courses = Cleanscoures(STD->courses, COUR);  //remove course from the student courses list 
}
    

void print_students(slist* students){
    slist* p;
    p = students;
    printf("STUDENT LIST:");
    if(!students){
            printf("EMPTY");}
    else{
            while (p) {
                printf("\n");
                printf("%d:%s\n", p->info->id,p->info->name);
                if (p->info->courses == NULL) {
                    printf("student is no registered for courses"); }
                else {
                    clist* CoursesList;
                    CoursesList = p->info->courses;
                    while (CoursesList) {
                        printf("%d-%s, ", CoursesList->info->number,CoursesList->info->title);
                        CoursesList = CoursesList->next;
                    }
                }
                p = p->next;
    }}
    printf("\n");
}
void print_courses(clist* courses){
    clist* p;
    p = courses;
    printf("COURSE LIST:");
    if(!courses){
        printf("EMPTY");}
    else{
            while (p) {
                printf("\n");
                printf("%d:%s\n", p->info->number, p->info->title);
                if (p->info->students == NULL) {
                    printf("course has no students");}
                else {
                    slist* StudentsList;
                    StudentsList = p->info->students;
                    while (StudentsList) {
                        printf("%d-%s, ", StudentsList->info->id,StudentsList->info->name);
                        StudentsList = StudentsList->next;
                    }
                }
                p = p->next;
    }}   
    printf("\n");

}

void free_all(slist* sl, clist* cl){
    //deletes and frees all items in list
    slist* temp1, * curr1 = sl;
    clist* temp2, * curr2 = cl;
    while (curr1){
        while(curr1->info->courses){
            clist* tempcour, *currcour = curr1->info->courses;
            tempcour = currcour;
            currcour = currcour->next;
            free(tempcour);}
        free(curr1->info->name);
        temp1 = curr1;
        curr1 = curr1->next;
        free(temp1);}
    while (curr2) {
        while(curr2->info->students){
            slist* tempstd, *currstd = curr2->info->students;
            tempstd = currstd;
            currstd = currstd->next;
            free(tempstd);}
        free(curr2->info->title);
        temp2 = curr2;
        curr2 = curr2->next;
        free(temp2);}
    }



//DO NOT TOUCH THIS FUNCTION
static void getstring(char* buf, int length) {
    int len;
    buf = fgets(buf, length, stdin);
    len = (int)strlen(buf);
    if (buf[len - 1] == '\n'){
        buf[len - 1] = '\0';}
}

//DO NOT TOUCH THIS FUNCTION 
int main() {
    slist* students = 0;
    clist* courses = 0;
    char  c;
    char  buf[100];
    int   id, num;

    do {
        printf("Choose:\n"
            "    add (s)tudent\n"
            "    add (c)ourse\n"
            "    (r)egister student\n"
            "    (u)nregister student\n"
            "    (p)rint lists\n"
            "    (q)uit\n");

        while ((c = (char)getchar()) == '\n');
        getchar();

        switch (c) {
        case 's':
            printf("Adding new student.\n");

            printf("Student name: ");
            getstring(buf, 100);

            printf("Student ID: ");
            scanf("%d", &id);

            students = add_student(students, buf, id);

            break;

        case 'c':
            printf("Adding new course.\n");

            printf("Course name: ");
            getstring(buf, 100);

            printf("Course number: ");
            scanf("%d", &num);

            courses = add_course(courses, buf, num);

            break;

        case 'r':
            printf("Registering a student to a course.\n");

            printf("Student ID: ");
            scanf("%d", &id);

            printf("Course number: ");
            scanf("%d", &num);

            reg_student(students, courses, id, num);

            break;

        case 'u':
            printf("Unregistering a student from a course.\n");

            printf("Student ID: ");
            scanf("%d", &id);

            printf("Course number: ");
            scanf("%d", &num);

            unreg_student(students, id, num);

            break;

        case 'p':
            printf("Printing Information.\n");

            print_students(students);
            print_courses(courses);

            break;

        case 'q':
            printf("Quitting...\n");
            break;
        }

        if (c != 'q')
            printf("\n");
    } while (c != 'q');

    free_all(students, courses);
    return 0;
}

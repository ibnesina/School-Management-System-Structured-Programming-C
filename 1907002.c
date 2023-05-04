#include<stdio.h>
#include<string.h>

typedef struct admin //struct admin is old type
{
	char name[50];
    char password[50];
} admin; //admin is new type

typedef struct teacher //struct teacher is old type
{
	char name[50];
    char password[50];
	char course1[50];
    char course2[50];
	
} teacher; //teacher is new type

typedef struct student //struct student is old type
{
	char name[50];
    char password[50];
    char roll[50];
} student; //student is new type

typedef struct marks //struct marks is old type
{
	char name[50];
	char course1[50];
	char couse1_mark[50];
	char course2[50];
	char couse2_mark[50];
} marks; //marks is new type

void add_teacher() //this function will add teacher by the admin
{
	teacher teac;
	printf("\nEnter Teacher's name: ");
	fflush(stdin);//fflush(stdin) is used to flush the output buffer of the stream
	gets(teac.name);
    printf("Enter Teacher's password: ");
	fflush(stdin);
	scanf("%s", teac.password);
    printf("Enter Teacher's 1st Course name: ");
	fflush(stdin);
	gets(teac.course1);
    printf("Enter Teacher's 2nd Course name: ");
	fflush(stdin);
	gets(teac.course2);
	FILE *fp = fopen("teacher_record.txt", "a");//this function will open teacher_record.txt file to append
	fwrite(&teac, sizeof(teacher), 1, fp); //this function append data at the end of the teacher_record.txt file.
	fclose(fp); //close the fp file
    printf("\n---Teacher's record updated successfully---\n");
	fflush(stdin);
}

void add_student()//this function will add student by the admin
{
	student stu;
	printf("\nEnter Student's name: ");
	fflush(stdin);
	gets(stu.name);
    printf("Enter Student's password: ");
	fflush(stdin);
	scanf("%s", stu.password);
    printf("Enter Student's roll: ");
	fflush(stdin);
	scanf("%s", stu.roll);
	FILE *fp = fopen("student_record.txt", "a");//this function will open student_record.txt file to append
	fwrite(&stu, sizeof(student), 1, fp);//this function append data at the end of the student_record.txt file.
	fclose(fp);
    printf("\n---Student's record updated successfully---\n");
	fflush(stdin);
}

void update_teacher_info() //this function will update teacher's info by the admin
{
    teacher teac;
    char name[50];
    int find = 0;
    printf("\nEnter Teacher's Name: ");
    fflush(stdin);
    gets(name);
    FILE *fp = fopen("teacher_record.txt", "r+");//this function will open teacher_record.txt file to read and write
    while(fread(&teac, sizeof(teacher), 1, fp) == 1) //checking that is there any file named teacher_record.txt present or not
    {
        if(strcmp(name, teac.name)==0)
        {
            printf("Enter Teacher's new name: ");
            fflush(stdin);
            gets(teac.name);
            printf("Enter Teacher's new password: ");
            fflush(stdin);
            scanf("%s", teac.password);
            printf("Enter Teacher's new 1st Course name: ");
            fflush(stdin);
            gets(teac.course1);
            printf("Enter Teacher's new 2nd Course name: ");
            fflush(stdin);
            gets(teac.course2);
            fseek(fp, -sizeof(teacher), 1);//this function is used to move file pointer associated with a given file to a specific position. Here the pointer will point the point where strcmp(name, teac.name) == 0
            fwrite(&teac, sizeof(teacher), 1, fp);//this function will erase the previous info and write the new data to the teacher_record.txt file.
            fclose(fp);
            find = 1;
            break;
        }
    }
    if(find == 0)
    {
        printf("\n---No Teacher found---\n");
    }
    else
    {
        printf("\n---Record updated successfully---\n");
    }
}

void update_student_info() //this function will update student's info by the admin
{
    student stu;
    char name[50];
    int find = 0;
    printf("\nEnter Student's Name: ");
    fflush(stdin);
    gets(name);
    FILE *fp = fopen("student_record.txt", "r+");//this function will open student_record.txt file to read and write
    while(fread(&stu, sizeof(student), 1, fp) == 1)//checking that is there any file named student_record.txt present or not
    {
        if(strcmp(name, stu.name)==0)
        {
            printf("Enter Student's new name: ");
            fflush(stdin);
            gets(stu.name);
            printf("Enter Student's new password: ");
            fflush(stdin);
            scanf("%s", stu.password);
            printf("Enter Student's new roll: ");
            fflush(stdin);
            scanf("%s", stu.roll);
            fseek(fp, -sizeof(student), 1);//this function is used to move file pointer associated with a given file to a specific position. Here the pointer will point the point where strcmp(name, stu.name) == 0
            fwrite(&stu, sizeof(student), 1, fp);//this function will erase the previous info and write the new data to the student_record.txt file.
            fclose(fp);
            find = 1;
            break;
        }
    }
    if(find == 0)
    {
        printf("\n---No Student found---\n");
    }
    else
    {
        printf("\n---Record updated successfully---\n");
    }
}

int admin_record() //admin's record will check in here
{
	admin ad;
	printf("\nPlease Enter Admin's user id: ");
	fflush(stdin);
	gets(ad.name);
    printf("Please Enter Admin's password: ");
	fflush(stdin);
	scanf("%s", ad.password);

	FILE *admin_file;
	admin adm;
	admin_file = fopen("admin_record.txt", "r");
	if(admin_file == NULL)
	{
		fclose(admin_file);
		admin_file = fopen("admin_record.txt", "w"); //if it is for the very first time, firstly create a text "admin_password" file for saving admin's user name, password
		fwrite(&ad, sizeof(admin), 1, admin_file);
		fclose(admin_file);
		admin_file=fopen("admin_record.txt", "r");
	}

	int find = 0;
	//checking user name, password does exist in the admin_record.txt file or not
	while(fread(&adm, sizeof(admin), 1, admin_file))
	{
		if(strcmp(adm.name, ad.name) == 0 && strcmp(adm.password, ad.password) == 0) 
            find = 1;
	}
	fclose(admin_file);
	return find;
}

void admin_panel()
{
	if(admin_record() == 0)
    {
		printf("\n---Invalid user id or password---\n");
		return;
	}

	//Login sucessfull
	printf("\n---Welcome to Admin---\n");
	fflush(stdin);

	while(1)
    {
        printf("\n1. Add teacher\n2. Add student\n3. Update teacher info\n4. Update student info\n0. Back to main menu\n\n");
        fflush(stdin);
		int choose;
        printf("Enter : ");
		scanf("%d", &choose); 
		if(choose == 0)
        {
			printf("\n---Exiting admin panel---\n\n");
			return;
		}
		if(choose == 1)
        {
            add_teacher(); //it will call add_teacher() function
        }
		else if(choose == 2)
        {
            add_student(); //it will call add_student() function
        }
        else if(choose == 3)
        {
            update_teacher_info(); //it will call update_teacher_info() function
        }
        else if(choose == 4)
        {
            update_student_info(); //it will call update_student_info() function
        }
	}
}

int teacher_record() //teacher's record will check in here
{
	teacher teac;
	printf("\nEnter Teacher's name: ");
	fflush(stdin);
	gets(teac.name);
	printf("Enter Teacher's password: ");
	fflush(stdin);
	scanf("%s", teac.password);

	FILE *fp;
	teacher teach;
	fp = fopen("teacher_record.txt", "r"); //this function will open teacher_record.txt file to read

	int cou = 0;
    if(fp == NULL)
    {
        return cou;
    }

    //checking user name, password does exist in the teacher_record.txt file or not
	while(fread(&teach, sizeof(teacher), 1, fp))
    {
		if(strcmp(teach.name, teac.name) == 0 && strcmp(teach.password, teac.password) == 0) 
			cou = 1;
	}
	fclose(fp);
	return cou;
}

void provide_ct_marks() //teacher will provide ct marks
{
	student stu;
    char name[50];
    int find = 0;
    printf("\nEnter Student's Name: ");
    fflush(stdin);
    gets(name);
    FILE *fp = fopen("student_record.txt", "r"); //this function will open student_record.txt file to read

    //checking student's name does exist in the student_record.txt file or not
    while(fread(&stu, sizeof(student), 1, fp) == 1)
    {
        if(strcmp(name, stu.name)==0)
        {
            find = 1; //student found successfully
            break;
        }
    }
    fclose(fp);

    if(find == 0)
    {
        printf("\n---No Student found---\n\n");
    }
    else
    {
        fp = fopen("mark.txt", "a"); //this function will open mark_record.txt file to append
        marks mrk;
        strcpy(mrk.name, name); //copy data of the variable name to mrk.name
        printf("Enter 1st Course name: ");
        fflush(stdin);
        gets(mrk.course1);
        printf("Enter %s Course mark: ", mrk.course1);
        fflush(stdin);
        gets(mrk.couse1_mark);
        printf("Enter 2nd Course name: ");
        fflush(stdin);
        gets(mrk.course2);
        printf("Enter %s Course mark : ", mrk.course2);
        fflush(stdin);
        gets(mrk.couse2_mark);

        fwrite(&mrk, sizeof(marks), 1, fp); //tis function write data at the mark_record.txt file.
        fclose(fp);
        printf("\n---Marks updated successfully---\n\n");
    }
}

void check_marks(char *c); 


void find_student() //teacher will find the student
{
    student stu;
    char name[50];
    int find = 0;
    printf("\nEnter Student's Name: ");
    fflush(stdin);
    gets(name);
    FILE *fp = fopen("student_record.txt", "r");
    //checking students name does exist in the student_record.txt file or not
    while(fread(&stu, sizeof(student), 1, fp) == 1)
    {
        if(strcmp(name, stu.name)==0)
        {
            find = 1; //student's record found
            printf("\n---Student found successfully---\n");
            printf("\nStudent's Name: %s \t Roll: %s\n", stu.name, stu.roll);
            check_marks(name); //show student's marks
            printf("\n");
            break;
        }
    }
    fclose(fp);
    if(find == 0)
    {
        printf("\n---No Student found---\n\n");
    }
}

void count_student() //teacher will count the number of total students
{
    FILE *fp;
	fp = fopen("student_record.txt", "r"); //open student_record.txt file to read
	student stu;
	int cou = 0;

	while(fread(&stu, sizeof(student), 1, fp))
    {
		cou++; //count student
	}

	printf("\n\n---Number of sutdents is : %d---\n\n\n\n", cou);
}

void teacher_panel()
{
	if(teacher_record() == 0)
    {
		printf("\n---Invalid User id or password---\n");
		return;
	}

	//Login Successfull
	printf("\n---Welcome to Teacher panel---\n\n");
    while(1)
    {
        printf("1. Add ct marks\n2. Find student by Fullname\n3. Count students\n0. Back to main menu\n\n");
        fflush(stdin);
        int choose;
        printf("Enter : ");
        scanf("%d", &choose);
        if(choose == 0)
        {
            printf("\n---Exiting teacher panel---\n\n");
            return;
        }
        else if(choose == 1)
        {
            provide_ct_marks(); //it will call provide_ct_marks()
        }
        else if(choose == 2)
        {
            find_student(); //it will call find_student()
        }
        else if(choose == 3)
        {
            count_student(); //it will call count_student()
        }
    }

}


void check_marks(char *c) //student will check ct marks
{
    FILE *fp = fopen("mark.txt", "r"); //open mark.txt file to read
    if(fp == NULL)
    {
        printf("\n---CT marks still not given---\n");
        return;
    }
	marks mrk;
    char name[50];
    strcpy(name, c);
    int a = 0;
    printf("\n");

    //checking students name does exist in the mark.txt file or not
    while(fread(&mrk, sizeof(mrk), 1, fp))
    {
    	if(strcmp(name, mrk.name)==0) //name found
        {
    		printf("Sub : %s\tMarks : %s\n", mrk.course1, mrk.couse1_mark);
            printf("Sub : %s\tMarks : %s\n\n\n", mrk.course2, mrk.couse2_mark);
            a = 1;
    	}
    }
    if(a == 0)
    {
            printf("---CT marks not found---\n");
    }
    fclose(fp);
}

void student_panel()
{
	printf("\nPlease Enter user name: ");
    fflush(stdin);
	student std;
	gets(std.name);
	printf("Please Enter password: ");
    fflush(stdin);
	scanf("%s",std.password);

	FILE *fp;
	student std1;
	fp=fopen("student_record.txt","r"); //open student_record.txt file to read
    
    if(fp == NULL)
    {
        printf("\n---Invalid User id or password---\n");
		return;
    }
	int cou = 0;
	//checking user name, password does exist in the student_record.txt file or not
	while(fread(&std1,sizeof(std),1,fp))
	{
		if(strcmp(std1.name, std.name) == 0 && strcmp(std1.password, std.password) == 0) 
			cou = 1;
	}
    fclose(fp);
    
    if(cou == 0)
	{
		printf("\n---Invalid User id or password---\n");
		return;
	}

	else
    {
        //Login successfull
        printf("\n---Welcome to student panel---\n");

        while (1)
        {
            printf("\n1. See ct marks\n0. Back to main menu\n\n");
            fflush(stdin);
            int choose;
            printf("Enter : ");
            scanf("%d", &choose);
            if(choose == 0)
            {
                printf("\n---Exiting student panel---\n\n");
                return;
            }
            else if(choose == 1)
            {
                check_marks(std.name); //calling check_marks(char *c) function
            }
        }
    }
    
}

void options()
{
    while (1)
    {
        printf("\n1. Admin\n2. Teacher\n3. Student\n0. Exit\n\n");
        int choose;
        printf("Enter : ");
        scanf("%d", &choose);
        if(choose == 0)
        {
            printf("\n---Exit Successfully---\n\n");
            return;
        }
        else if(choose == 1) 
        {
            admin_panel(); //calling admin_panel() function
        }
        else if(choose == 2) 
        {
            teacher_panel(); //calling teacher_panel() function
        }
        else if(choose == 3)
        {
            student_panel(); //calling student_panel() function
        }
    }
}

int main()
{
    printf("\n---Welcome to KUET Admin, Teacher & Student's Management System---\n\n");
	options(); //calling options() function
    
    return 0;
}
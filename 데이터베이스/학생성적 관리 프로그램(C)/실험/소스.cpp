//학생정보 관리 프로그램

//***************************************************************
//                   HEADER FILE USED IN PROJECT
//***************************************************************

#include<conio.h>
#include<stdio.h>
#include<stdlib.h>

#define SIZE 100
//***************************************************************
//                   STURUCTURE USED IN PROJECT
//****************************************************************

struct student
{
	int rollno;
	char name[50];
	int p_marks, c_marks;
	double per;
	char grade;
}st;

student p[SIZE]; //구조체 배열 생성
student temp[SIZE]; // 임시로 옮길 구조체 배열 생성

int rollno2[SIZE];
int i = 0;
int count = 0;

//***************************************************************
//        global declaration
//****************************************************************

FILE* fptr;

//***************************************************************
//        function to write in file
//****************************************************************

void write_student()
{

	int i, num = 0;
	errno_t err;
	err = fopen_s(&fptr, "student.dat", "ab+");  //return 0 if success
	rewind(fptr);
	printf("\nPlease Enter The New Details of student \n");
	printf("\nEnter The roll number of student ");
	scanf_s("%d", &st.rollno);
	num = st.rollno; //입력 받은 학번을 다른 변수에 저장
	int check = num; // 검사할때 필요
	getchar(); // flushing buffer



	if (fptr == NULL)
		return;
	while ((i = fread(&st, sizeof(st), 1, fptr)) > 0)
	{

		if (st.rollno == check) { //저장한 학번과 일치하면 중복된 학생이라고 출력
			printf("error: 중복된 학생입니다.");
			fclose(fptr);
			_getch();
			return;
		}
	}

	st.rollno = num; //처음으로 움직여서 등록되었던 학번을 다시 아까 입력받았던 학번으로 변경

	printf("\n\nEnter The Name of student ");
	gets_s(st.name, sizeof(st.name));
	printf("\nEnter The marks in physics out of 100 : ");
	scanf_s("%d", &st.p_marks);
	printf("\nEnter The marks in chemistry out of 100 : ");
	scanf_s("%d", &st.c_marks);

	st.per = (st.p_marks + st.c_marks) / 2.0;  //학점 계산
	if (st.per >= 60)
		st.grade = 'A';
	else if (st.per >= 50 && st.per < 60)
		st.grade = 'B';
	else if (st.per >= 33 && st.per < 50)
		st.grade = 'C';
	else
		st.grade = 'F';
	fwrite(&st, sizeof(st), 1, fptr);
	fclose(fptr);
	printf("\n\nStudent Record Has Been Created.  Press any key.... ");

	rollno2[i] = st.rollno;
	i++;
	count++;
	_getch();



}


//***************************************************************
//        function to read all records from file
//****************************************************************


void display_all() // 학생 정보를 입력받아 전부 다 출력
{
	errno_t err; int i;
	system("cls"); // 화면을 다 지움
	printf("\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n");
	printf("====================================================\n");
	printf("R.No.  Name       P   C   Ave   Grade\n");
	printf("====================================================\n");

	err = fopen_s(&fptr, "student.dat", "rb"); // 학생 정보 출력 위해 파일을 연다 
	if (fptr == NULL) // error check
		return;

	while ((i = fread(&st, sizeof(st), 1, fptr)) > 0) // 파일 포인터에서 record 하나를 구조체 사이즈만큼 읽어온다 (1byte도 못읽을때까지 계속 돈다)
	{
		
		printf("%-6d %-10s %-3d %-3d %-3.2f  %-1c\n",
			st.rollno, st.name, st.p_marks, st.c_marks, st.per, st.grade);
		i++;
		p[i];
		if (i>50)
			return; 
	}
	fclose(fptr);
	_getch();
}


//***************************************************************
//        function to read specific record from file
//****************************************************************


void display_sp(int n)
{
	int flag = 0;
	errno_t err;
	err = fopen_s(&fptr, "student.dat", "rb");
	if (fptr == NULL)
		return;
	while ((fread(&st, sizeof(st), 1, fptr)) > 0) // fread 한 결과값이 0보다 클때까지(1byte 이상 읽을때까지 돈다)
	{
		if (st.rollno == n) // 만약 맨 앞에 있는 레코드가  n과 일치하면 모든 정보를 화면에 출력
		{
			system("cls");
			printf("\nRoll number of student : %d", st.rollno);
			printf("\nName of student : %s", st.name);
			printf("\nMarks in Physics : %d", st.p_marks);
			printf("\nMarks in Chemistry : %d", st.c_marks);
			printf("\nPercentage of student is  : %.2f", st.per);
			printf("\nGrade of student is : %c", st.grade);
			flag = 1; // 찾았다 못찾았다를 표시하기 위해
		}
	}
	fclose(fptr);
	if (flag == 0) // while루프를 끝까지 돌았을때도 못찾았을시
		printf("\n\nrecord not exist");
	_getch();
}


//***************************************************************
//        function to modify record of file
//****************************************************************


void modify_student()
{
	int no, found = 0, i;
	errno_t err;
	system("cls");
	printf("\n\n\tTo Modify ");
	printf("\n\n\tPlease Enter The roll number of student");
	scanf_s("%d", &no); // 학번 입력받음
	err = fopen_s(&fptr, "student.dat", "rb+"); // 기존 이진파일을 지우지않고 read, write를 하겠다 
	if (fptr == NULL)
		return;
	while ((i = fread(&st, sizeof(st), 1, fptr)) > 0 && found == 0) // 더 이상 찾지 못할때 까지
	{
		if (st.rollno == no)
		{
			printf("\nRoll number of student : %d", st.rollno);
			printf("\nName of student : %s", st.name);
			printf("\nMarks in Physics : %d", st.p_marks);
			printf("\nMarks in Chemistry : %d", st.c_marks);
			printf("\nPercentage of student is  : %.2f", st.per);
			printf("\nGrade of student is : %c", st.grade);
			printf("\nPlease Enter The New Details of student \n");
			printf("\nEnter The roll number of student ");
			scanf_s("%d", &st.rollno);
			getchar();  //flushing buffer (fflsh는 작동안함)
			printf("\n\nEnter The Name of student ");
			gets_s(st.name, sizeof(st.name));
			printf("\nEnter The marks in physics out of 100 : ");
			scanf_s("%d", &st.p_marks);
			printf("\nEnter The marks in chemistry out of 100 : ");
			scanf_s("%d", &st.c_marks);

			st.per = (st.p_marks + st.c_marks) / 2.0;
			if (st.per >= 60)
				st.grade = 'A';
			else if (st.per >= 50 && st.per < 60)
				st.grade = 'B';
			else if (st.per >= 33 && st.per < 50)
				st.grade = 'C';
			else
				st.grade = 'F';


			fseek(fptr, sizeof(st), 1);  // SEEK_CUR
			fwrite(&st, sizeof(st), 1, fptr);


			printf("\n\n\t Record Updated");

			found = 1;
			break;
		}
	}

	fclose(fptr);
	if (found == 0)
		printf("\n\n Record Not Found ");
	_getch();
}


//***************************************************************
//        function to delete record of file
//****************************************************************


void delete_student()
{
	int no,i=0; 
	FILE* fptr2;
	errno_t err;
	int index = 0;
	system("cls");
	printf("\n\n\n\tDelete Record");
	printf("\n\nPlease Enter The roll number of student You Want To Delete ");
	scanf_s("%d", &no);

	err = fopen_s(&fptr, "student.dat", "ab+");
	if (fptr == NULL)
		return;
	while ((fread(&st, sizeof(st), 1, fptr)) > 0)
	{
		if (st.rollno == no) //삭제하려는 학번과 저장되어있던 학번과 일치하면
		{
			temp[i] = p[i]; 
			p[i] = p[100];
			p[100] = temp[i];
			//삭제하려는 해당 인덱스의 구조체배열을 맨 끝에 배열과 교환한다
			
		}
		i++;
	}
	
	fclose(fptr);
	printf("\n\n\tRecord Deleted ..");
	_getch();
}



//***************************************************************
//        THE MAIN FUNCTION OF PROGRAM
//****************************************************************
void main()
{
	char ch;
	int num;
	do
	{
		system("cls");

		printf("\n\n\t1.CREATE STUDENT RECORD");
		printf("\n\n\t2.DISPLAY ALL STUDENTS RECORDS");
		printf("\n\n\t3.SEARCH STUDENT RECORD ");
		printf("\n\n\t4.MODIFY STUDENT RECORD");
		printf("\n\n\t5.DELETE STUDENT RECORD");
		printf("\n\n\t6.EXIT");
		printf("\n\n\tPlease Enter Your Choice (1-6) ");
		ch = _getche();

		switch (ch)
		{
		case '1':	system("cls");
			write_student();
			break;
		case '2':	display_all();
			break;
		case '3':	system("cls");  // 학생 찾으면 정보를 출력 
			printf("\n\n\tPlease Enter The roll number ");
			scanf_s("%d", &num);
			display_sp(num);
			break;
		case '4':	modify_student(); break; // 학생 정보 수정
		case '5':	delete_student(); break;
		case '6':	break;
		default:	printf("\a");
		}
	} while (ch != '6');
}
//***************************************************************
//                END OF PROJECT
//***************************************************************
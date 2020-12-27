//�л����� ���� ���α׷�

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

student p[SIZE]; //����ü �迭 ����
student temp[SIZE]; // �ӽ÷� �ű� ����ü �迭 ����

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
	num = st.rollno; //�Է� ���� �й��� �ٸ� ������ ����
	int check = num; // �˻��Ҷ� �ʿ�
	getchar(); // flushing buffer



	if (fptr == NULL)
		return;
	while ((i = fread(&st, sizeof(st), 1, fptr)) > 0)
	{

		if (st.rollno == check) { //������ �й��� ��ġ�ϸ� �ߺ��� �л��̶�� ���
			printf("error: �ߺ��� �л��Դϴ�.");
			fclose(fptr);
			_getch();
			return;
		}
	}

	st.rollno = num; //ó������ �������� ��ϵǾ��� �й��� �ٽ� �Ʊ� �Է¹޾Ҵ� �й����� ����

	printf("\n\nEnter The Name of student ");
	gets_s(st.name, sizeof(st.name));
	printf("\nEnter The marks in physics out of 100 : ");
	scanf_s("%d", &st.p_marks);
	printf("\nEnter The marks in chemistry out of 100 : ");
	scanf_s("%d", &st.c_marks);

	st.per = (st.p_marks + st.c_marks) / 2.0;  //���� ���
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


void display_all() // �л� ������ �Է¹޾� ���� �� ���
{
	errno_t err; int i;
	system("cls"); // ȭ���� �� ����
	printf("\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n");
	printf("====================================================\n");
	printf("R.No.  Name       P   C   Ave   Grade\n");
	printf("====================================================\n");

	err = fopen_s(&fptr, "student.dat", "rb"); // �л� ���� ��� ���� ������ ���� 
	if (fptr == NULL) // error check
		return;

	while ((i = fread(&st, sizeof(st), 1, fptr)) > 0) // ���� �����Ϳ��� record �ϳ��� ����ü �����ŭ �о�´� (1byte�� ������������ ��� ����)
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
	while ((fread(&st, sizeof(st), 1, fptr)) > 0) // fread �� ������� 0���� Ŭ������(1byte �̻� ���������� ����)
	{
		if (st.rollno == n) // ���� �� �տ� �ִ� ���ڵ尡  n�� ��ġ�ϸ� ��� ������ ȭ�鿡 ���
		{
			system("cls");
			printf("\nRoll number of student : %d", st.rollno);
			printf("\nName of student : %s", st.name);
			printf("\nMarks in Physics : %d", st.p_marks);
			printf("\nMarks in Chemistry : %d", st.c_marks);
			printf("\nPercentage of student is  : %.2f", st.per);
			printf("\nGrade of student is : %c", st.grade);
			flag = 1; // ã�Ҵ� ��ã�Ҵٸ� ǥ���ϱ� ����
		}
	}
	fclose(fptr);
	if (flag == 0) // while������ ������ ���������� ��ã������
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
	scanf_s("%d", &no); // �й� �Է¹���
	err = fopen_s(&fptr, "student.dat", "rb+"); // ���� ���������� �������ʰ� read, write�� �ϰڴ� 
	if (fptr == NULL)
		return;
	while ((i = fread(&st, sizeof(st), 1, fptr)) > 0 && found == 0) // �� �̻� ã�� ���Ҷ� ����
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
			getchar();  //flushing buffer (fflsh�� �۵�����)
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
		if (st.rollno == no) //�����Ϸ��� �й��� ����Ǿ��ִ� �й��� ��ġ�ϸ�
		{
			temp[i] = p[i]; 
			p[i] = p[100];
			p[100] = temp[i];
			//�����Ϸ��� �ش� �ε����� ����ü�迭�� �� ���� �迭�� ��ȯ�Ѵ�
			
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
		case '3':	system("cls");  // �л� ã���� ������ ��� 
			printf("\n\n\tPlease Enter The roll number ");
			scanf_s("%d", &num);
			display_sp(num);
			break;
		case '4':	modify_student(); break; // �л� ���� ����
		case '5':	delete_student(); break;
		case '6':	break;
		default:	printf("\a");
		}
	} while (ch != '6');
}
//***************************************************************
//                END OF PROJECT
//***************************************************************
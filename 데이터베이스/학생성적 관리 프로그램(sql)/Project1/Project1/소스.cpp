//mysql�� �̿��� ����1���� �����ߴ� �л� ���ڵ� ���� ���α׷� �ۼ�

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <mysql.h>
#include <errno.h>
#include <conio.h>

void main() {

	MYSQL* conn; //pointer to connection handler
	MYSQL_RES* res;
	MYSQL_ROW row;
	int fields, cnt;
	char ch;

	char query[200];
	int rollno, p_mark, c_mark;
	char name[20];

	conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, "localhost", "root", "ksb0707", "studentdb", 0, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	
	mysql_set_character_set(conn, "euckr"); // �ѱ� ���� ���� (���ڵ��� ����� �ٲ۰�)

	do {
		printf("\n\n\n");
		printf("\n\n\t1.CREATE STUDENT RECORD");
		printf("\n\n\t2.DISPLAY ALL STUDENTS RECORDS");
		printf("\n\n\t3.SEARCH STUDENT RECORD ");
		printf("\n\n\t4.MODIFY STUDENT RECORD");
		printf("\n\n\t5.DELETE STUDENT RECORD");
		printf("\n\n\t6.EXIT");
		printf("\n\n\tPlease Enter Your Choice (1-6) ");
		printf("\n\n");
		
		ch = _getch();

		switch (ch)
		{
		case '1': // ����
			printf("�л��� �й�,�̸�, ������ �����Ͻÿ� : ");
			scanf("%d %s %d %d", &rollno, &name, &p_mark, &c_mark); //�л������� �ް�
			sprintf(query, "insert into student values (%d, \"%s\", %d, %d, %s ,%s)", rollno, name, p_mark, c_mark, NULL, NULL); //�Է�
			mysql_query(conn, query);
			break;

		case'2': // ���
			if (mysql_query(conn, "SELECT*FROM student")) {
				printf("%s\n", mysql_error(conn));
				exit(1);
			}

			res = mysql_store_result(conn);
			unsigned int num_fields;
			num_fields = mysql_num_fields(res);

			while ((row = mysql_fetch_row(res))) {
				printf("\n");
				for (int i = 0; i < num_fields; i++)
					printf("%s  ", row[i] != NULL ? row[i] : "NULL");
				
			}
			mysql_free_result(res); //result�� �Ҵ�� �޸� ����
			break;

		case'3': // �˻�
			res = mysql_store_result(conn);
			num_fields = mysql_num_fields(res);

			printf("�˻��� �л��� �й��� �Է��Ͻÿ� : ");
			scanf("%d", &rollno);
			while ((row = mysql_fetch_row(res))) {
				printf("\n");
				for (int i = 0; i < num_fields; i++)
					//   if(rollno == ) -> �Է��� �й��� ������
					printf("%s  ", row[i] != NULL ? row[i] : "NULL"); //�ش� �й��� �л� ������ �Է�

			}
			mysql_free_result(res); //result�� �Ҵ�� �޸� ����
			break;
		
		case'4': // ����
			printf("�����ϰ���� �л��� �й��� �Է��Ͻÿ� :");
			scanf("%d", &rollno);
			

		case'5': // ����
			printf("�����ϰ���� �л��� �й��� �Է��Ͻÿ� : ");
			scanf("%d", &rollno);
			sprintf(query, "delete from student where rollno = %d", rollno);
			printf("�����Ǿ����ϴ�");
			mysql_query(conn, query);
			break;

		default: printf("\a");
		}
	} while (ch != '6');
		

	

	
	mysql_close(conn);
}
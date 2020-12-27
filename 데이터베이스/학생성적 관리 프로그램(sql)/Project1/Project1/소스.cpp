//mysql을 이용해 과제1에서 구현했던 학생 레코드 관리 프로그램 작성

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
	
	mysql_set_character_set(conn, "euckr"); // 한글 깨짐 방지 (인코딩한 방법을 바꾼것)

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
		case '1': // 삽입
			printf("학생의 학번,이름, 점수를 삽입하시오 : ");
			scanf("%d %s %d %d", &rollno, &name, &p_mark, &c_mark); //학생정보를 받고
			sprintf(query, "insert into student values (%d, \"%s\", %d, %d, %s ,%s)", rollno, name, p_mark, c_mark, NULL, NULL); //입력
			mysql_query(conn, query);
			break;

		case'2': // 출력
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
			mysql_free_result(res); //result에 할당된 메모리 해제
			break;

		case'3': // 검색
			res = mysql_store_result(conn);
			num_fields = mysql_num_fields(res);

			printf("검색할 학생의 학번을 입력하시오 : ");
			scanf("%d", &rollno);
			while ((row = mysql_fetch_row(res))) {
				printf("\n");
				for (int i = 0; i < num_fields; i++)
					//   if(rollno == ) -> 입력한 학번과 같으면
					printf("%s  ", row[i] != NULL ? row[i] : "NULL"); //해당 학번의 학생 정보를 입력

			}
			mysql_free_result(res); //result에 할당된 메모리 해제
			break;
		
		case'4': // 수정
			printf("수정하고싶은 학생의 학번을 입력하시오 :");
			scanf("%d", &rollno);
			

		case'5': // 삭제
			printf("삭제하고싶은 학생의 학번을 입력하시오 : ");
			scanf("%d", &rollno);
			sprintf(query, "delete from student where rollno = %d", rollno);
			printf("삭제되었습니다");
			mysql_query(conn, query);
			break;

		default: printf("\a");
		}
	} while (ch != '6');
		

	

	
	mysql_close(conn);
}
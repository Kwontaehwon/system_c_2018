#include <stdio.h>

struct card{
	int pips;
	char suit;
};

typedef struct {
	double re;
	double im;
} complex;


struct dept{
	char name[25];
	int no;
};

typedef struct{
	char name[25];
	int employee_id;
	struct dept department;
	double salary;
} employee_data;


int main(){
	struct card cards[4] = {{1,'D'},{2,'S'},{3,'C'},{4,'H'}};

	employee_data a = {
		"john",
		3,
		{"Engineering", 3},
		1000
	};

	printf("Name: %s\nid: %d\nDept: %s\nDept_no: %d\nSalary: %.2f\n",
		a.name,
		a.employee_id,
		a.department.name,
		a.department.no,
		a.salary);


	return 0;
}
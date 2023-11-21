#include "cluster_manager.cpp"
#include <iostream>
#include <locale>

using namespace std;

int main(){
	setlocale(LC_ALL, "rus");
	int Tmax;
	cout << "������� ������� ������ ����� �������� ���������: ";
	cin >> Tmax;
	Cluster_manager cl(Tmax);
	while (!cl.Finish()) {
		cl.Computation();
		cout << cl;
		system("pause");
		system("cls");
	}
	cout << "����������� ������� " << cl.finishedTasks() << endl;
	cout << "������������� ������� " << cl.failedTasks();
	return 0;
}
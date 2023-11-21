#include <cstdlib>
#include <ctime>
#include "TQueue.h"
#include "Task.cpp"
#include <vector>
#include <iostream>

using namespace std;

class Cluster_manager
{
private:
	int N; //���-�� �������������� �����(���������)
	int Nmax; //���-�� �������������� �����(������������)
	double alpha; //����������� ��������� �������
	int tacts; //max ������ �� ����������
	int thistact; //������� ����
	vector<Task> process;
	TQueue<Task> qu;
	int countTasks; //���-�� ����������� �������
	int countfail = 0;
	bool end = false;

	void generateAlpha() {
		alpha = rand() % (int)pow(10, 3);
		alpha = 0.0 + (alpha / pow(10, 3)) * 1.0;
	}
public:
	Cluster_manager(int T) {
		if (T < 0) throw "invalid tacts";
		tacts = T;
		thistact = 0;
		srand(time(NULL));
		generateAlpha();
		countTasks = 0;
		N = 16 + rand() % 49;
		Nmax = N;
	}
	int finishedTasks() { return countTasks; }
	int failedTasks() { return qu.Size() + countfail; }
	void Computation() {
		//TQueue<Task> qu;
		//while (tacts != 0) {
			generateAlpha();
			if (alpha * 100.0 > 50.0) {
				Task tsk(Nmax);
				if (tsk.getNode() <= N) {
					if (qu.IsEmpty()) {
						process.push_back(tsk);
						N -= tsk.getNode();
					}
					if (!(qu.IsEmpty())) {
						if (qu.peek().getNode() <= N) {
							process.push_back(qu.peek());
							N -= qu.peek().getNode();
							qu.dequeue();
							if (tsk.getNode() <= N) {
								process.push_back(tsk);
								N -= tsk.getNode();
							}
							else qu.enqueue(tsk);
						}
					}
				}
				else {
					if (!(qu.IsEmpty())) {
						if (qu.peek().getNode() <= N) {
							process.push_back(qu.peek());
							N -= qu.peek().getNode();
							qu.dequeue();
						}
					}
					qu.enqueue(tsk);
				}
			}
			if (alpha * 100.0 < 50.0) {
				if (!(qu.IsEmpty())) {
					if (qu.peek().getNode() <= N) {
						process.push_back(qu.peek());
						N -= qu.peek().getNode();
						qu.dequeue();
					}
				}
			}
			for (int i = 0; i < process.size(); i ++) {
				if (process[i].getTa�t() == 0) {
					N += process[i].getNode();
					process.erase(process.begin() + i);
					//vector<Task>(process).swap(process);
					countTasks++;
				}
				if(process.size()!=0)
					process[i].eraseTacts();
				if (i = process.size()) break;
			}
			tacts--;
			thistact++;
		//}
			if (tacts == 0)
				end = true;
			countfail = process.size();
	}
	bool Finish() {
		return end;
	}

	friend ostream& operator<<(ostream& os, const Cluster_manager& T);
};

ostream& operator<<(ostream& os, const Cluster_manager& T)
{
	return os << "�������� ������: " << T.tacts << endl << "����� �����: " << T.Nmax << endl
		<< "����������� ��������� �������: " << T.alpha << endl
		<< "����������� �������: " << T.countTasks << endl
		<< "��������� ���-�� �����: " << T.N << endl
		<< "������� �����������: " << T.process.size() << endl
		<< "�������� �������� = " << (((double(T.Nmax) - double(T.N)) / double(T.Nmax))*100.0) << "%" << endl;

}

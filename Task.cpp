#include <cstdlib>
#include <ctime>
class Task
{
private:
	int p; //���-�� ����� ��� ����������
	int tz; //����� ���������� � ������
public:
	Task() {};
	Task(int N) {
		srand(time(NULL));
		p = 1 + rand() % (N - 1);
		tz = 1 + rand() % 25;
	}
	int getNode() { return p; }
	int getTa�t() { return tz; }
	void eraseTacts() { tz--; }
};


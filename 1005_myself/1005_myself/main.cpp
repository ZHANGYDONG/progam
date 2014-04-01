//zoj��֧�� out ���
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>  

using namespace std;

const string action[6] =
{
	"fill A",
	"fill B",
	"empty A",
	"empty B",
	"pour A B",
	"pour B A"
};

//��ǰ��������������Ϊ״̬
class PointCup
{
public:
	PointCup();
	PointCup(int x1, int x2, int x3, string x4)
	{
		a = x1;
		b = x2;
		c = x3;
		act = x4;
	}
	int geta() { return a; }
	int getb() { return b; }
	int getc() { return c; }
	int seta(int _a) { a = _a; return 0; }
	int setb(int _b) { b = _b; return 0; }
	int setc(int _c) { c = _c; return 0; }
	bool match()
	{
		if (b == c)
			return true;
		else
			return false;
	}
	inline bool operator==(const PointCup &rhs)
	{
		return this->a == rhs.a && 
			this->b == rhs.b &&
			this->c == rhs.c;
 	}

	inline bool operator!=(const PointCup &rhs)
	{
		return this->a != rhs.a ||
			this->b != rhs.b ||
			this->c != rhs.c;
	}
	//��¼���ڵ�,��������Ҫ���Ÿ��ڵ��߻�ȥ,��ָ�벻���ö���
	int pid;//OK ��¼��visitedλ��
	//PointCup *parent; //ERROR ������ʼ���󣬵�ַ������
	//��¼��״̬����Ϊ
	string act;
private:
	int a;
	int b;
	int c;
};

bool IsVisited(PointCup keyPoint, vector<PointCup> in)
{
	vector<PointCup>::iterator first = in.begin(),
		                          last = in.end();
	while (first != last)
	{
		//����==
		if (*first == keyPoint) 
		{
			return true;
		}
		first++;
	}
	return false;
}

//�ҳ���visited��λ��
int findpid(PointCup& key, vector<PointCup> list)
{
	for (vector<PointCup>::size_type ix = 0; ix != list.size(); ix++)
	{
		if (key == list[ix])
		{
			return ix;
		}
	}
}

int main()
{
	//��������� ���Զ��½�
	ofstream out("log.txt");
	if (!(out.is_open()))
	{
		cout << "Cannot open log.txt" << endl;
	}
	int A, B, Key;
	while (cin >> A >> B >> Key)
	{   
		//��ǰ״̬�ĵ�,���������һ��״̬��, �ҳ�ʼ��,�����ڵ㣩
		PointCup initPoint(0, 0, Key, ""), currentPoint(0, 0, Key,""), nextPoint(0, 0, Key,"");
		//�����Լ�Ϊ���ڵ�
		initPoint.pid = 0;
		//�������ĵ�
		queue<PointCup> tovisit;
		//�Ѿ����ʵĵ㼯��
		vector<PointCup> visited;
		//������ڵ㵽visited
		tovisit.push(initPoint);
		visited.push_back(initPoint);
		//BFSѭ��
		while (!tovisit.empty())
		{
			out << 1 << endl;
			currentPoint = tovisit.front();
			tovisit.pop();
			//�ҳ�currentPoint��visited��λ��,Ȼ���pid
			int ix = findpid(currentPoint, visited);
			out << 2 << endl;
			//path one:fill A;�ж�����Ҫ��ֹ��ѭ��
			if (currentPoint.geta() < A)
			{
				//��һ��״̬
				nextPoint.seta(A);
				nextPoint.setb(currentPoint.getb());
				nextPoint.act = action[0];
				nextPoint.pid = ix;
				//�Ƿ��Ѿ������������vector
				if (!IsVisited(nextPoint, visited))
				{
					//û�б�����������ӽ����У�������Ѷ�
					tovisit.push(nextPoint);
					visited.push_back(nextPoint);
					out << 3 << endl;
				}
				if (nextPoint.match())
				{
					out << 4 << endl;
					break;
				}
			}
			//path two : fill B
			if (currentPoint.getb() < B)
			{
				out << 22 << endl;
				//��һ��״̬
				nextPoint.seta(currentPoint.geta());
				nextPoint.setb(B);
				nextPoint.act = action[1];
				nextPoint.pid = ix;
				out << &currentPoint << endl;
				out << &nextPoint << endl;
				//�Ƿ��Ѿ������������vector
				if (!IsVisited(nextPoint, visited))
				{
					out << 222 << endl;
					//û�б�����������ӽ����У�������Ѷ�
					tovisit.push(nextPoint);
					visited.push_back(nextPoint);
				}
				if (nextPoint.match())
				{
					break;
					out << 2 << endl;
				}
			}
			//path three : empty A 
			if (currentPoint.geta() != 0)
			{
				out << 232 << endl;
				nextPoint.seta(0);
				nextPoint.setb(currentPoint.getb());
				nextPoint.act = action[2];
				nextPoint.pid = ix;
				if (!IsVisited(nextPoint, visited))
				{
					//û�б�����������ӽ����У�������Ѷ�
					tovisit.push(nextPoint);
					visited.push_back(nextPoint);
				}
				if (nextPoint.match())
				{
					break;
					out << 3 << endl;
				}
			}
			//path four : empty B
			if (currentPoint.getb() != 0)
			{
				out << 2322 << endl;
				nextPoint.seta(currentPoint.geta());
				nextPoint.setb(0);
				nextPoint.act = action[3];
				nextPoint.pid = ix;
				if (!IsVisited(nextPoint, visited))
				{
					//û�б�����������ӽ����У�������Ѷ�
					tovisit.push(nextPoint);
					visited.push_back(nextPoint);
				}
				if (nextPoint.match())
				{
					break;
					out << 4 << endl;
				}
			}
			//path five : pour A B
			//���ﵱʱд�� ==B �� ���źܾã�����Ҫ˼��Ϊʲôfill_a ��ȥ��һ֧û���� �ͻᷢ������
			if (currentPoint.geta() != 0 && currentPoint.getb() != B)
			{
				out << 2324 << endl;
				int diff = B - currentPoint.getb();
				nextPoint.seta(currentPoint.geta() - min(diff, currentPoint.geta()));
				nextPoint.setb(currentPoint.getb() + min(diff, currentPoint.geta()));
				nextPoint.act = action[4];
				nextPoint.pid = ix;
				if (!IsVisited(nextPoint, visited))
				{
					//û�б�����������ӽ����У�������Ѷ�
					tovisit.push(nextPoint);
					visited.push_back(nextPoint);
				}
				if (nextPoint.match())
				{
					break; out << 5 << endl;
				}
			}
			//path six : pour B A
			if (currentPoint.getb() != 0 && currentPoint.geta() != A)
			{
				out << 2327 << endl;
				int diff = A - currentPoint.geta();
				nextPoint.seta(currentPoint.geta() + min(diff, currentPoint.getb()));
				nextPoint.setb(currentPoint.getb() - min(diff, currentPoint.getb()));
				nextPoint.act = action[5];
				nextPoint.pid = ix;
				out << 2328 << endl;
				if (!IsVisited(nextPoint, visited))
				{
					out << 2329 << endl;
					//û�б�����������ӽ����У�������Ѷ�
					tovisit.push(nextPoint);
					visited.push_back(nextPoint);
				}
				if (nextPoint.match())
				{
					break; out << 6 << endl;
				}
			}

		}out << 2388 << endl;
        //������vector,����·��
		vector<string> path;
		//���һ���ɹ��Ľڵ�
		path.push_back(nextPoint.act);
		while (nextPoint.pid != 0)
		{
			out << nextPoint.pid << "  ";
			PointCup Ppoint = visited[nextPoint.pid];
			//�����ڵ�Ĳ�������
			path.push_back(Ppoint.act);
			nextPoint = Ppoint;
		}

		//�������
		for (vector<string>::reverse_iterator first = path.rbegin();
			first != path.rend(); first++)
		{
			cout << *first << endl;
		}
		cout << "success" << endl;
	}
	out.close();
	return 0;
}


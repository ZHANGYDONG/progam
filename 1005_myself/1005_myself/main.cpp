//zoj不支持 out 输出
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

//当前两个杯子容量作为状态
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
	//记录父节点,输出结果需要沿着父节点走回去,用指针不是用对象
	int pid;//OK 记录在visited位置
	//PointCup *parent; //ERROR 变量初始化后，地址不变了
	//记录本状态的行为
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
		//重载==
		if (*first == keyPoint) 
		{
			return true;
		}
		first++;
	}
	return false;
}

//找出在visited的位置
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
	//如果不存在 会自动新建
	ofstream out("log.txt");
	if (!(out.is_open()))
	{
		cout << "Cannot open log.txt" << endl;
	}
	int A, B, Key;
	while (cin >> A >> B >> Key)
	{   
		//当前状态的点,如果，则下一步状态点, 且初始化,（根节点）
		PointCup initPoint(0, 0, Key, ""), currentPoint(0, 0, Key,""), nextPoint(0, 0, Key,"");
		//定义自己为父节点
		initPoint.pid = 0;
		//待搜索的点
		queue<PointCup> tovisit;
		//已经访问的点集合
		vector<PointCup> visited;
		//加入根节点到visited
		tovisit.push(initPoint);
		visited.push_back(initPoint);
		//BFS循环
		while (!tovisit.empty())
		{
			out << 1 << endl;
			currentPoint = tovisit.front();
			tovisit.pop();
			//找出currentPoint在visited的位置,然后给pid
			int ix = findpid(currentPoint, visited);
			out << 2 << endl;
			//path one:fill A;判断条件要防止死循环
			if (currentPoint.geta() < A)
			{
				//下一个状态
				nextPoint.seta(A);
				nextPoint.setb(currentPoint.getb());
				nextPoint.act = action[0];
				nextPoint.pid = ix;
				//是否已经遍历过，检查vector
				if (!IsVisited(nextPoint, visited))
				{
					//没有遍历过，则添加进队列，并标记已读
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
				//下一个状态
				nextPoint.seta(currentPoint.geta());
				nextPoint.setb(B);
				nextPoint.act = action[1];
				nextPoint.pid = ix;
				out << &currentPoint << endl;
				out << &nextPoint << endl;
				//是否已经遍历过，检查vector
				if (!IsVisited(nextPoint, visited))
				{
					out << 222 << endl;
					//没有遍历过，则添加进队列，并标记已读
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
					//没有遍历过，则添加进队列，并标记已读
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
					//没有遍历过，则添加进队列，并标记已读
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
			//这里当时写成 ==B ， 困扰很久，不过要思考为什么fill_a 下去这一支没有了 就会发现问题
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
					//没有遍历过，则添加进队列，并标记已读
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
					//没有遍历过，则添加进队列，并标记已读
					tovisit.push(nextPoint);
					visited.push_back(nextPoint);
				}
				if (nextPoint.match())
				{
					break; out << 6 << endl;
				}
			}

		}out << 2388 << endl;
        //输出结果vector,回溯路径
		vector<string> path;
		//最后一个成功的节点
		path.push_back(nextPoint.act);
		while (nextPoint.pid != 0)
		{
			out << nextPoint.pid << "  ";
			PointCup Ppoint = visited[nextPoint.pid];
			//将父节点的操作输入
			path.push_back(Ppoint.act);
			nextPoint = Ppoint;
		}

		//倒叙输出
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


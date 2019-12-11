#include <iostream>
#include <vector>
#include <string>

using namespace std;


void decomposition(long long n, vector <long long>& nm)
{
	for (long long i = 2; i <= sqrt(n); i++)
		if (n%i == 0) break;
		else
		{
			nm.push_back(n);
			return;
		}

	long long k = 2;
	while (n != 1)
	{
		if (n % k == 0)
		{
			nm.push_back(k);
			n /= k;
		}
		else k++;
	}

	vector <long long> nm1;
	k = nm.at(0);
	long long kk = 1;
	for (long long i = 0; i < nm.size(); i++)
	{
		if (nm.at(i) == k) kk *= k;
		else
		{
			nm1.push_back(kk);	
			k = nm.at(i);
			kk = k;
		}
	}
	nm1.push_back(kk);
	nm.swap(nm1);
}

int gcd(long long x, long long y)
{
	return y ? gcd(y, x%y) : x;
}

void print_reversible_0(long long n,vector <long long>& rev, bool q)
{
	vector <long long> del0;
	int k = 0;
	if (q) cout << "Обратимые элементы:" << endl;
	for (long long i = 0; i < n; i++)
	{
		if (gcd(i, n) == 1)
		{
			k++;
			rev.push_back(i);
			if (q) cout << i << " ";
		}
		else del0.push_back(i);
	}
	if (q) cout << endl <<"Кол-во обратимых элементов = " << k << endl;
	if (q) cout << endl  << "Делители нуля:" << endl;
	for (long long i = 0; i < del0.size(); i++)
	{
		if (q) cout << del0.at(i) << " ";
	}
	if (q) cout << endl << "Кол-во делителей нуля = " << del0.size() << endl;
}

int reversible(long long n, long long k,vector <long long> rev)
{
	if (gcd(n, k) != 1) return 0;
	for (long long i = 0; i < rev.size(); i++)
	{
		if ((k * rev.at(i)) % n == 1) return rev.at(i);
	}
}

void idem(long long n)
{
	cout << "Идемпотенты:" << endl;
	for (long long i = 0; i < n; i++)
	{
		if (i*i % n == i)
		{
			cout << i << " ";
		}
	}
	cout << endl;
}


int main()
{
	vector <long long> nm;
	vector <long long> rev;
	setlocale(LC_ALL, "Russian");
	long long n;
	cout << "Введите модуль кольца n = ";
	cin >> n;
	string str;
	long long st = 0;
	bool q = true;
	while (q) {
		cout << " 0 - выход " << "\n 1 - Все обратимые и делители нуля" << "\n 2 - Все идемпотенты"
			<< "\n 3 - Найти обратный для элемента" << "\n 4 - Разбить кольцо на простые делители"  
			<< "\n 5 - Разложение элемента на прямой изоморфизм" << "\n 6 - Обратный изоморфизм" << endl;
		cin >> str;
		st = atoi(str.c_str());
		switch (st)
		{
		case 0:
		{
			q = false;
			break;
		}
		case 1:
		{
			print_reversible_0(n,rev,1);
			system("pause>>NULL");
			break;
		}
		case 2:
		{
			idem(n);
			system("pause>>NULL");
			break;
		}
		case 3:
		{
			print_reversible_0(n, rev, 0);
			long long k = 0;
			cout << "Введите элемент, для которого ищете обратный ";
			cin >> k;
			if (reversible(n, k, rev) == 0)
			{
				cout << "элемент " << k << " необратим" << endl;
				system("pause>>NULL");
				break;
			}
			if (k > 0) cout << "Обратным для эл-та " << k << " является " << reversible(n, k, rev) << endl;
			system("pause>>NULL");
			break;
		}
		case 4:
		{
			decomposition(n, nm);
			for (long long i = 0; i < nm.size(); i++)
			{
				cout << nm.at(i) << " ";
			}
			cout << endl;
			system("pause>>NULL");
			break;
		}
		case 5:
		{
			nm.clear();
			decomposition(n, nm);
			vector <long long> buf;
			long long a;
			cout << "Введите число а = ";
			cin >> a;
			for (long long i = 0; i < nm.size(); i++)
			{
				buf.push_back(a % nm.at(i));
			}
			cout << "остаток " << a << " соответствует парам: (";
			for (long long i = 0; i < buf.size(); i++)
			{
				cout << buf.at(i);
				if (i != buf.size() - 1) cout << ",";
			}
			cout << ")" << endl;
			system("pause>>NULL");
			break;
		}
		case 6:
		{
			nm.clear();
			decomposition(n, nm);
			long long buff;
			vector <long long> Buf;
			vector <long long> buf;
			cout << "Введите пары остатков: (после каждого остатка нажимайте ENTER)" << endl;
			for (long long i = 0; i < nm.size(); i++)
			{
				cin >> buff;
				buf.push_back(buff);
			}
			long long ii = 0;
			for (long long i = 0; i < n; i++)
			{
				for (long long j = 0; j < nm.size(); j++)
				{
					Buf.push_back(i % nm.at(j));
					if (Buf.at(j) != buf.at(j))
					{
						Buf.clear();
						break;
					}
				}
				if (!Buf.empty())
				{
					ii = i;
					break;
				}
			}
			cout << "Введенная пара соответствует элементу : " << ii << endl;
			system("pause>>NULL");
			break;
		}
		default:
		{
			break;
		}
		}
		system("cls");
	}






	system("pause>>NULL");
	return 0;
}
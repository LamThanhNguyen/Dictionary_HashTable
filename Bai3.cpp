#include<iostream>
#include<stdio.h>
using namespace std;
#include<stdlib.h>
#include<conio.h>
#include<algorithm>
#include<string>
#include<Windows.h>
#include<fstream>
#include<conio.h>
const int n = 26;
struct tagNode
{
	string Ekey;
	string Vkey;
	struct tagNode* next;
};
typedef struct tagNode Node;
Node* A[26];
int h(string EngWord)
{
	 std::transform(EngWord.begin(), EngWord.end(), EngWord.begin(), tolower);
	 int Key1 = int(EngWord[0]) % n;
	 return Key1; 
}
int Tim(string EngWord)
{
	Node* p;
	int thay;
	std::transform(EngWord.begin(), EngWord.end(), EngWord.begin(), tolower);
	p = A[h(EngWord)];
	thay = 0;
	while (p != NULL && !thay)
	{
		if (p->Ekey == EngWord)
		{
			thay = 1;
		}
		else
		{
			p = p->next;
		}
	}
	return thay;
}
void Them(string EngWord, string VietWord)
{
	int i;
	//Node* p = new Node;
	//Node* p = (Node*)malloc(sizeof(Node));
	std::transform(EngWord.begin(), EngWord.end(), EngWord.begin(), tolower);
	if (!Tim(EngWord))
	{
		i=h(EngWord);
		Node* p = new Node;
		//p = (Node*)malloc(sizeof(Node));
		p->Ekey = EngWord;
		p->Vkey = VietWord;
		p->next = A[i];
		A[i] = p;
	}
	else
	{
		cout << EngWord << " da co trong tu dien";
		return;
	}
}
void Xoa(string EngWord)
{
	int i, thay;
	Node *p, *q;
	std::transform(EngWord.begin(), EngWord.end(), EngWord.begin(), tolower);
	i = h(EngWord);
	if (A[i] == NULL)
	{
		cout << EngWord << "khong co trong tu dien";
	}
	else
	{
		if (A[i]->Ekey == EngWord)
		{
			p = A[i];
			A[i] = A[i]->next;
			free(p);
		}
		else
		{
			q = A[i];
			p = q->next;
			thay = 0;
			while (p !=NULL && !thay)
			{
				if(p->Ekey==EngWord)
				{
					thay = 1;
					q->next = p->next;
					free(p);
				}
				else
				{
					q = p;
					p = q->next;
				}
			}
			if (!thay)
			{
				cout << EngWord << " khong co trong tu dien";
			}
		}
	}
}
void WriteFileAgain(const char* File_Name)
{
	fstream data_file;
	data_file.open(File_Name, ios::out | ios::trunc);
	if (!data_file.is_open())
	{
		cout << "File khong ton tai.";
	}
	else
	{
		Node* p;
		for (int i = 0; i < n; i++)
		{
			p = A[i];
			while (p != NULL)
			{
				data_file << p->Ekey << "\t" << p->Vkey << endl;
				p = p->next;
			}
		}
	}
	data_file.close();
}
void InKQ(string EngWord)
{
	std::transform(EngWord.begin(), EngWord.end(), EngWord.begin(), tolower);
	if (Tim(EngWord) == 0)
	{
		cout << EngWord << " Khong co trong tu dien";
	}
	else
	{
		Node* p;
		p = A[h(EngWord)];
		while (p != NULL)
		{
			if (p->Ekey == EngWord)
			{
				cout << EngWord + " co nghia Tieng Viet la: " + p->Vkey << endl;
				return;
			}
			else
			{
				p = p->next;
			}
		}
	}
}
void InAll()
{
	Node* p;
	for (int i = 0; i < n; i++)
	{
		p = A[i];
		cout << "\nLop " << i << ": " << endl;
		if (p == NULL)
		{
			cout << NULL;
		}
		while (p != NULL)
		{
			cout << p->Ekey << "\t-->\t" << p->Vkey << endl;
			p = p->next;
		}
	}
}
void AddFile(const char* FileName, string EngWordd, string VietWordd)
{
	fstream data_file;
	data_file.open(FileName, ios::out | ios::app);
	if (!data_file.is_open())
	{
		cout << "File khong ton tai.";
	}
	else
	{
		data_file << "\n" << EngWordd << "\t" << VietWordd;
	}
	data_file.close();
}
void DATA(const char* FileName)
{
	char input[100];
	fstream fsFile;
	fsFile.open(FileName, ios::in);
	if (!fsFile.is_open())
	{
		cout << "Cannot read file!";
	}
	else
	{
		while (!fsFile.eof())
		{
			fsFile.getline(input, 100, '\t');
			string EW = input;
			fsFile.getline(input, 100, '\n');
			string VW = input;
			Them(EW, VW);
		}
	}
	fsFile.close();
}
int main()
{
	int chon;
	string EngWordd;
	string VietWordd;
	for (int i = 0; i < n; i++)
	{
		A[i] = NULL;
	}
	DATA("DataTuDien.txt");
	do
	{
		cout << "\n1.Add \t2.Find \t3.Tra tu \t4.Delete \t5.InAll \t6.Exit - Chon: ";
		cin >> chon;
		cin.ignore(1000, '\n');
		if (chon == 1)
		{
			cout << "Tu can them vao: "; 
			getline(cin, EngWordd);
			cout << "Nghia Tieng Viet tuong ung cua tu la: "; 
			getline(cin, VietWordd);			
			Them(EngWordd, VietWordd);
			AddFile("DataTuDien.txt", EngWordd, VietWordd);
		}
		if (chon == 2)
		{
			cout << "Tu can tim kiem xem da xuat hien hay chua la: ";
			getline(cin, EngWordd);
			if (Tim(EngWordd))
			{
				cout << EngWordd + " da co trong tu dien. Ban co the tra tu.";
			}
			else
			{
				cout << "Rat tiec, " + EngWordd + " khong co du lieu trong tu dien. Ban co muon cap nhat tu moi " + EngWordd + " nay cho tu dien khong. Neu muon xin moi chon 1 và them du lieu cho tu moi can them vao. Thanks!";
			}
		}
		if (chon == 3)
		{
			cout << "Tu can tra la: ";
			getline(cin, EngWordd);
			InKQ(EngWordd);
		}
		if (chon == 4)
		{
			cout << "Tu ban muon xoa la: ";
			getline(cin, EngWordd);
			Xoa(EngWordd);
			WriteFileAgain("DataTuDien.txt");
			cout << "Ban da xoa thanh cong tu: " << EngWordd;
		}
		if (chon == 5)
		{
			cout << "Du lieu trong Tu Dien cua ban: ";
			InAll();
		}
	} while (chon >= 1 && chon <= 5);
		return 0;
}
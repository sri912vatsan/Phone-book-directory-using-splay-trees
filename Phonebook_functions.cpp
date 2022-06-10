#include <iostream>
#include <iomanip>
#include <stack>
#include <vector>
#include <string>
#include <cstdio>
#include <bits/stdc++.h>
#include "Phonebook.h"


using namespace std;

Phone_Directory ::Phone_Directory()
{
	nullRecord = new node;
	nullRecord->left = nullRecord->right = nullRecord;
	root = nullRecord;
}

Phone_Directory ::~Phone_Directory()
{
	Make_Empty(root);
	delete root;
}

void Phone_Directory ::Insert_Record(string phone_num, string name,string city)
{
	node *newRecord = new node;
	newRecord->left = newRecord->right = nullRecord;
	newRecord->phone_num = phone_num;
	newRecord->name = name;
	newRecord->city = city;


	if (root == nullRecord)
		root = newRecord;

	else
	{
		splay(phone_num, root);
		if (phone_num < root->phone_num)
		{
			newRecord->left = root->left;
			newRecord->right = root;
			root->left = nullRecord;
			root = newRecord;
		}

		else if (phone_num > root->phone_num)
		{
			newRecord->right = root->right;
			newRecord->left = root;
			root->right = nullRecord;
			root = newRecord;
		}

		else
			return;
	}
	cout << "\nEntry has been successfully inserted into the directory!!\n";
}

void Phone_Directory ::splay(string phone_num, node *&t)
{
	node header;
	header.left = header.right = nullRecord;
	node *leftTreeMax, *rightTreeMin;
	leftTreeMax = rightTreeMin = &header;
	nullRecord->phone_num = phone_num;
	while (1)
	{
		if (phone_num < t->phone_num)
		{
			if (phone_num < t->left->phone_num)
				rotate_with_left_child(t);

			if (t->left == nullRecord)
				break;

			rightTreeMin->left = t;
			rightTreeMin = t;
			t = t->left;
		}

		else if (phone_num > t->phone_num)
		{
			if (phone_num > t->right->phone_num)
				rotate_with_right_child(t);

			if (t->right == nullRecord)
				break;

			leftTreeMax->right = t;
			leftTreeMax = t;
			t = t->right;
		}

		else
			break;
	}
	leftTreeMax->right = t->left;
	rightTreeMin->left = t->right;
	t->left = header.right;
	t->right = header.left;
}

void Phone_Directory ::rotate_with_left_child(node *&k2)
{
	node *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2 = k1;
}

void Phone_Directory ::rotate_with_right_child(node *&k2)
{
	node *k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2 = k1;
}

void Phone_Directory ::Delete_Record(string phone_num)
{
	node *newTree = NULL;
	if (!contains(phone_num))
	{
		cout << phone_num << " is not present in the directory!!\n\n";
		return;
	}

	if (root->right == nullRecord)
		newTree = root->left;

	else
	{
		newTree = root->right;
		splay(phone_num, newTree);
		newTree->left = root->left;
	}
	delete root;
	root = newTree;
}

bool Phone_Directory ::contains(string phone_num)
{
	splay(phone_num, root);
	return root->phone_num == phone_num;
}

bool Phone_Directory ::Is_Empty()
{
	return root == nullRecord;
}

void Phone_Directory ::Make_Empty(node *&t)
{
	while (t != nullRecord)
		Delete_Record(t->phone_num);
}

int Phone_Directory::count = 0;

void Phone_Directory ::Display_Records(node *t)
{
	if (t == NULL)
	{
		cout << "\nThe phone directory has zero entries!!\n";
		return;
	}
	cout << "\n------------------------------------------------------------------------------------------------------\n";
	cout << "Name\t\t\t\tPhone number\t\t\tCity" << endl;
	cout << "---------------------------------------------------------------------------------------------------------\n";
	print(t);
	cout << "---------------------------------------------------------------------------------------------------------\n";
}

void Phone_Directory ::print(node *&t) //Preorder traversal
{
	if (t != t->left)
	{
		cout << t->name << "\t\t\t\t" << t->phone_num <<"\t\t\t"<<t->city<<endl;
		//printf("%-24s %s\n", t->name.c_str(), t->phone_num.c_str(),t->city.c_str());
		print(t->left);
		print(t->right);
	}
}

void Phone_Directory ::search_key(string phone_num)
{
	if (!contains(phone_num))
	{
		cout << phone_num << " is not present in the directory!!\n";
		return;
	}
	cout << endl;
	cout << "Name : " << root->name << endl;
	cout << "Phone number : " << root->phone_num << endl;
	cout << "City:"<<root->city<<endl;
	root->count++;
}

void Phone_Directory ::Partial_Matches(string phone_num)
{
	vector<node *> Partial_Matched_phonenum;
	stack<node *> TEMP_Stk;
	if (Is_Empty())
	{
		cout << "\nThe phone directory is empty !!\n";
		return;
	}
	TEMP_Stk.push(root);
	int count_keys = 1;
	while (TEMP_Stk.size() != 0)
	{
		node *temp = TEMP_Stk.top();
		TEMP_Stk.pop();
		int m = temp->phone_num.size(), n = phone_num.size();
		int LCS[m + 1][n + 1];
		int result = 0;
		for (int i = 0; i <= m; i++)
		{
			for (int j = 0; j <= n; j++)
			{
				if (i == 0 || j == 0)
				{
					LCS[i][j] = 0;
					continue;
				}
				char L = temp->phone_num[i - 1], R = phone_num[j - 1];

				if (L == R)
				{
					LCS[i][j] = LCS[i - 1][j - 1] + 1;
					//result = max(result, LCS[i][j]);
				}

				else
					LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
			}
		}
		if (LCS[m][n] == n)
		{
			cout << count_keys << "." << temp->phone_num << endl;
			count_keys++;
			Partial_Matched_phonenum.push_back(temp);
		}

		if (temp->right != nullRecord)
			TEMP_Stk.push(temp->right);

		if (temp->left != nullRecord)
			TEMP_Stk.push(temp->left);
	}
	if (Partial_Matched_phonenum.size() == 0)
	{
		cout << "\nNo partial matches found !!" << endl;
		return;
	}
	int choice;
	cout << endl
		 << "Enter your choice : ";
	cin >> choice;
	if (choice < 1 || choice > Partial_Matched_phonenum.size())
	{
		cout << "\nInvalid choice !!\n";
		return;
	}
	node *Final = Partial_Matched_phonenum[choice - 1];
	cout << endl;
	cout << "Name : " << Final->name << endl;
	cout << "Phone number : " << Final->phone_num << endl;
	cout << "City:" << Final->city <<endl;
	Final->count++;
	splay(Final->phone_num, root);
}

void Phone_Directory ::Partial_Matches_Name(string name)
{
	vector<node *> Partial_Matched_name;
	stack<node *> TEMP_Stk;
	if (Is_Empty())
	{
		cout << "\nThe phone directory is empty !!\n";
		return;
	}
	TEMP_Stk.push(root);
	int count_keys = 1;
	while (TEMP_Stk.size() != 0)
	{
		node *temp = TEMP_Stk.top();
		TEMP_Stk.pop();
		int m = temp->name.size(), n = name.size();
		int LCS[m + 1][n + 1];
		int result = 0;
		for (int i = 0; i <= m; i++)
		{
			for (int j = 0; j <= n; j++)
			{
				if (i == 0 || j == 0)
				{
					LCS[i][j] = 0;
					continue;
				}
				char L = temp->name[i - 1], R = name[j - 1];

				if (L == R)
				{
					LCS[i][j] = LCS[i - 1][j - 1] + 1;
					//result = max(result, LCS[i][j]);
				}

				else
					LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
			}
		}
		if (LCS[m][n] == n)
		{
			cout << count_keys << "." << temp->name << endl;
			count_keys++;
			Partial_Matched_name.push_back(temp);
		}

		if (temp->right != nullRecord)
			TEMP_Stk.push(temp->right);

		if (temp->left != nullRecord)
			TEMP_Stk.push(temp->left);
	}
	if (Partial_Matched_name.size() == 0)
	{
		cout << "\nNo partial matches found !!" << endl;
		return;
	}
	int choice;
	cout << endl
		 << "Enter your choice : ";
	cin >> choice;
	if (choice < 1 || choice > Partial_Matched_name.size())
	{
		cout << "\nInvalid choice !!\n";
		return;
	}
	node *Final = Partial_Matched_name[choice - 1];
	cout << endl;
	cout << "Name : " << Final->name << endl;
	cout << "Phone number : " << Final->phone_num << endl;
	cout << "City :" <<Final->city <<endl;
	Final->count++;
	splay(Final->phone_num, root);
}

void Phone_Directory ::Frequent_keys()
{
	vector<node *> Frequents;
	stack<node *> TEMP_Stk;
	if (Is_Empty())
	{
		cout << "\nThe phone directory has zero records !!\n";
		return;
	}
	TEMP_Stk.push(root);
	while (TEMP_Stk.size() != 0)
	{
		node *temp = TEMP_Stk.top();
		TEMP_Stk.pop();
		if (temp->count > 0)
		{
			Frequents.push_back(temp);
			sort(Frequents);
		}

		if (temp->right != nullRecord)
			TEMP_Stk.push(temp->right);

		if (temp->left != nullRecord)
			TEMP_Stk.push(temp->left);
	}

	if (Frequents.size() == 0)
	{
		cout << "\nNo phone number was searched\n";
		return;
	}
	cout << endl;
	for (int i = 0; i < Frequents.size(); i++)
	{
		cout << "Name : " << Frequents[i]->name << endl;
		cout << "Phone number : " << Frequents[i]->phone_num << endl;
		cout << "City :" <<Frequents[i]->city <<endl;
		cout << "Search frequency : " << Frequents[i]->count << endl
			 << endl;
	}
}

void Phone_Directory ::sort(vector<node *> &Frequents)
{
	int size = Frequents.size();
	node *last = Frequents[size - 1];
	int i = size - 2;
	while (i >= 0 && Frequents[i]->count < last->count)
	{
		Frequents[i + 1] = Frequents[i];
		i--;
	}
	Frequents[i + 1] = last;
}

bool Phone_Directory ::name_found(node *n, const string &str)
{
	if (n == nullRecord)
		return false;

	string t = n->name;
	transform(t.begin(), t.end(), t.begin(), ::tolower);
	if (t.compare(str) == 0)
		return true;

	return name_found(n->left, str) || name_found(n->right, str);
}

bool Phone_Directory ::name_found(string &n)
{
	transform(n.begin(), n.end(), n.begin(), ::tolower);

	if (root == nullRecord)
		return false;

	/*string t = root->name;
    transform(t.begin(),t.end(),t.begin(),::tolower);

    if(t.compare(n)==0)
    return true;
*/
	//return name_found(root->left,n) || name_found(root->right,n);
	return name_found(root, n);
}

void Phone_Directory ::search_by_name(node *n, const string &search_string)
{
	if (n == nullRecord)
		return;

	string s = n->name;
	transform(s.begin(), s.end(), s.begin(), ::tolower);

	if (s.compare(search_string) == 0)
	{
		cout << n->name << "\t\t\t" << n->phone_num << "\t\t\t" <<n->city << endl;
		n->count++;
	}

	search_by_name(n->left, search_string);
	search_by_name(n->right, search_string);
}

void Phone_Directory ::search_by_name(const string &search_name)
{
	/*string t = root->name;
   transform(t.begin(),t.end(),t.begin(),::tolower);
   if(t.compare(search_name) == 0)
   cout << root->name << "\t\t" << root->phone_num << endl;
   */
	//search_by_name(root->left,search_name);
	//search_by_name(root->right,search_name);
	search_by_name(root, search_name);
}
void Phone_Directory::search_update(node *n,const string &search_name)
{
    if(n==nullRecord)
        return;

    string s=n->name;
    transform(s.begin(),s.end(),s.begin(),::tolower);

    if(s.compare(search_name)==0)
    {
        updatenode(n,s);
    }

    search_update(n->left,search_name);
    search_update(n->right,search_name);

}

void Phone_Directory::updatenode(node * n,string name)
{
    string new_phoneno,new_city;
    int len;
    label1:
    cout<<"Enter the new phone number:";
    getline(cin>>ws,new_phoneno);
    len = new_phoneno.size();

    if(len==11||len==10)
    {
        n->phone_num = new_phoneno;

    }
    else
    {
        cout<<"Invalid!!Please enter 10 digits in a Phone number!!";
        goto label1;
    }

    char ch;

    cout<<"Do you want to update city or not?(PRESS Y for Yes|PRESS Any button other than Y for No)";
    cin>>ch;

    if(ch=='Y'||ch=='y')
    {
        cout<<"Enter the new city name:";  getline(cin>>ws,new_city);

        n->city = new_city;
    }

}


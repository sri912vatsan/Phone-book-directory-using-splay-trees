#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Phone_Directory

{
	struct node
	{
		int count ; //For storing the frequency of a node
		string phone_num;
		string name;
		string city;
		node *left;
		node *right;
		node()
		{
			count = 0;
		}
	};

	public:
		static int count;
		Phone_Directory();
		~Phone_Directory();
		node *nullRecord, *root;
		void Insert_Record(string, string,string);
		void Delete_Record(string);
		void splay(string, node *&);
		bool contains(string);
		bool Is_Empty();
		void Make_Empty(node *&);
		void Display_Records(node *);
		void print(node *&);
		void rotate_with_left_child(node *&);
		void rotate_with_right_child(node *&);
		void search_key(string);
		void Partial_Matches(string);
		void Partial_Matches_Name(string);
		void Frequent_keys();
		void sort(vector<node *>&);
        void search_by_name(const string &);
        bool name_found( string &);
        void search_by_name(node * n, const string &);
        bool name_found(node * n, const string &);
        void search_update(node * n,const string &);
        void updatenode(node * n,string);
};

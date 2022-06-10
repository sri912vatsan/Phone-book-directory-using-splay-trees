#include <iostream>
#include<iomanip>
#include <string>
#include "Phonebook_functions.cpp"
using namespace std;

string accept_phone_num();
string accept_name();
string accept_city();

int main()
{
	Phone_Directory directory;
	int ch;

	do
	{
		cout << "\n1. Insert a new record\n";
		cout << "2. Delete an existing record\n";
		cout << "3. Display the phone directory\n";
		cout << "4. Search by phone number\n";
		cout << "5. Search By Name\n";
		cout << "6. Search By Partial Matching\n";
		cout << "7. Frequently searched phone number\n";
		cout << "8. Update the phone number\n";
		cout << "9. Delete the entire phone directory\n ";
		cout << "10. Exit\n\n";
		cout << "Enter your choice : ";
		cin >> ch;
		switch (ch)
		{
		case 1:       //Insertion Case
		{
			string name, phone_num,city;
			name = accept_name();
            phone_num = accept_phone_num();
			city = accept_city();
			directory.Insert_Record(phone_num, name,city);
			break;
		}

		case 2:       //Deletion case
		{
			string phone_num;
			phone_num = accept_phone_num();
			directory.Delete_Record(phone_num);
			cout << "\nThe record has been deleted !\n";
			break;
		}

		case 3:       //Displaying the whole phone directory
		{
			directory.count = 0;
			if (directory.Is_Empty())
			{
				cout << endl
					 << "\nThe phone directory doesn't have any records\n";
				break;
			}
			directory.Display_Records(directory.root);
			cout << endl;
			break;
		}

		case 4:
		{
			string phone_num;
			phone_num = accept_phone_num();
			directory.search_key(phone_num);
			break;
		}

		case 5:
		{
			string search_name;
			search_name = accept_name();

			if (!directory.name_found(search_name))
				cout << "\nThere are no records with name " << search_name << endl;

			else
			{
				cout << "\n----------------------------------------------------------------------\n";
				cout << "Name\t\t\tPhone number\t\t\tCity" << endl;
				cout << "------------------------------------------------------------------------\n";
				directory.search_by_name(search_name);

				cout << "------------------------------------------------------------------------\n";
			}
			break;
		}

		case 6:      //Searching by entering name or phone number partially
		{
			string partial_detail;
			int flag = 0;
			cout << endl
				 << "Enter the phone number/name : ";      //We either enter a name or phone number
			getline(cin >> ws, partial_detail);
			for (int i = 0; i < partial_detail.length(); i++)
			{
				if ((partial_detail[i] >= 65 && partial_detail[i] <= 90) || (partial_detail[i] >= 97 && partial_detail[i] <= 122))   //Checks whether a name or phone number
                                                                                                                                     //has been entered
				{
					flag = 1;          //if its true flag gets updated to 1
					break;
				}
			}
			if (flag == 0)      //checking whether to partially search by name or phone number
				directory.Partial_Matches(partial_detail);
			if (flag == 1)
				directory.Partial_Matches_Name(partial_detail);
			break;
		}

		case 7:    //printing Most frequently searched number details
		{
			directory.Frequent_keys();
			break;
		}
		case 8:    //Updating phone number
            {
                string name;
                cout<<"Enter the name of the person whose phone number to be updated:";   getline(cin>>ws,name);
                directory.search_update(directory.root,name);
                break;
            }
        case 9:              //Deleting entire phonebook
            {
                directory.~Phone_Directory();
                cout<<"Phone book directory deleted successfully!!"<<endl;
            }
		}

	} while (ch != 10);
	cout << "\nExiting....Thank you!\n";
	return 0;
}

string accept_phone_num()   //function to get phone number
{
	string phone_num;
	int len;
	label:
	cout << endl
		 << "Enter the phone number : ";
	getline(cin >> ws, phone_num);
	len= phone_num.size();
	if(len==11||len==10)
    {
        return phone_num;
    }
    else
    {
	    cout<<len;
        cout<<"Invalid phone number!!Please,enter a valid number"<<endl;
        goto label;


    }
}

string accept_name()
{
	string name;
	cout << endl
		 << "Enter the person's name : ";
	getline(cin >> ws, name);
	return name;
}
string accept_city()
{
    string city;
    cout<<endl
        <<"Enter the city:";
    getline(cin>>ws,city);
    return city;
}

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>
using namespace std;


int translation_third_hexadecimal_number_to_decimal(string& mac_adress)
{
	int tmp = 0;
	int deg = 1;
	char mass[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	for (int i = 6; i <= 7; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (mac_adress[i] == mass[j] || mac_adress[i] == tolower(mass[j]))
			{
				tmp += pow(16, deg) * j;
				deg--;
				break;
			}		
		}
	}
	return tmp;
}
int main()
{

	int decimal_numb, hexadecimal_numb;
	vector <string> mac_adress_mass;
	string mac_adress, file_name,str;
	smatch result;
	regex pattern("(\\s|^)([0-9a-fA-F]{2}:){5}[0-9a-fA-F]{2}(\\s|$)");
	ifstream file_in;
	ofstream file_out;

	cout << "Enter input file name:";
	getline(cin, file_name);
	file_in.open(file_name);
	if (!file_in.is_open())
	{
		cout << "This file doesn't exist!\n";
		return 0;
	}

	cout << "Enter third MAC-adress nubmer:";
	cin >> decimal_numb;
	cin.ignore(1, '\n');
	if (decimal_numb > 255 || decimal_numb < 0)
	{
		cout << "Error! Number must be from 0 to 255!\n";
		return 0;
	}

	// dd - 221
	// a7 - 167
	// ca - 202
	// 4D - 77
	// 3F - 63
	// a1 - 161
	// c7 - 199
	// c3 - 195
	//4e - 78
	//88 - 136
	while (getline(file_in, str))
	{
		while (regex_search(str, result, pattern))
		{
			mac_adress = result[0];
			if (mac_adress[0] == ' ')
				mac_adress.erase(0, 1);
			hexadecimal_numb = translation_third_hexadecimal_number_to_decimal(mac_adress);
			if (hexadecimal_numb == decimal_numb)
			{
				mac_adress_mass.push_back(mac_adress);
			}
			str = result.suffix().str();
		}
	}

	if (mac_adress_mass.size() == 0)
	{
		cout << "MAC-adress not found!" << endl;
		return 0;
	}

	cout << "Enter output file name:";
	getline(cin, file_name);
	file_out.open(file_name);

	for (int i = 0; i < mac_adress_mass.size(); i++)
		file_out << mac_adress_mass[i] << endl;

	file_in.close();
	file_out.close();
	return 0;
}

#include<iostream>
#include<fstream>
#include<string>
#include<typeinfo>
#include<vector>

using namespace std;

struct Passanger
{
	int id;
	int survival;
	int pclass;
	string name;
	string sex;
	int age;
	int sibsp;
	int parch;
	string ticket;
	float fare;
	string cabin;
	string embarked;
};


Passanger allPassangers[891];
fstream file("D:/Downloads/titanic-master/titanic-master/data/train.csv");
fstream result("D:/practicalWorks/programming/labs/lab5/Result.txt");
int main() {

	if (!file.is_open()) cout << "lose";
	
	string temp;
	
	for (int i = 0; i < 891; i++) {
		if (i == 0)
		{
			getline(file, temp, '\r');
			getline(file, temp, '\r');
		}
		else
		{
			getline(file, temp, '\r');
		}
		//id
		allPassangers[i].id = stoi(temp.substr(0, temp.find(',')));
		temp.erase(0, temp.find(',')+1);

		//survival
		allPassangers[i].survival = stoi(temp.substr(0, temp.find(',')));
		temp.erase(0, temp.find(',') + 1);

		//pclass
		allPassangers[i].pclass = stoi(temp.substr(0, temp.find(',')));
		temp.erase(0, temp.find(',') + 1);

		//name
		int prevLength=0;
		temp.erase(0, temp.find('\"') + 1);
		while (temp.find(' ') < temp.find('\"')) {
			allPassangers[i].name += temp.substr(0, temp.find(' '));
			allPassangers[i].name += " ";
			temp.erase(0, temp.find(' ')+1);
		}
		allPassangers[i].name += temp.substr(0, temp.find('\"'));
		temp.erase(0, temp.find(',') + 1);

		//sex
		allPassangers[i].sex = temp.substr(0, temp.find(','));
		temp.erase(0, temp.find(',') + 1);

		//age
		if (temp.substr(0, temp.find(',')) != "" ){
			allPassangers[i].age = stoi(temp.substr(0, temp.find(',')));
		}
		else
		{
			allPassangers[i].age = -1;
		}
		temp.erase(0, temp.find(',') + 1);

		//sibsp
		allPassangers[i].sibsp = stoi(temp.substr(0, temp.find(',')));
		temp.erase(0, temp.find(',') + 1);

		//parch
		allPassangers[i].parch = stoi(temp.substr(0, temp.find(',')));
		temp.erase(0, temp.find(',') + 1);

		//ticket
		allPassangers[i].ticket = temp.substr(0, temp.find(','));
		temp.erase(0, temp.find(',')+1);
		
		//fare
		allPassangers[i].fare = stof(temp.substr(0, temp.find(',')));
		temp.erase(0, temp.find(',') + 1);

		//cabin
		if (temp.substr(0, temp.find(',')) != "") {
			allPassangers[i].cabin = temp.substr(0, temp.find(','));
		}
		else
		{
			allPassangers[i].cabin = -1;
		}
		temp.erase(0, temp.find(',') + 1);

		//embarked
		allPassangers[i].embarked = temp.substr(0, temp.find('\0'));

		
	}
	
	int surv=0;
	int maleCount = 0;
	int femaleCount = 0;
	int fClassSurv = 0;
	int sClassSurv = 0;
	int tClassSurv = 0;
	int maleSurv = 0;
	int femaleSurv = 0;
	float averFemAge = 0;
	float averMalAge = 0;
	int counterC = 0;
	int counterQ = 0;
	int counterS = 0;
	vector<int> children;

	for (int i = 0; i < 891; i++) {
		if (allPassangers[i].survival == 1)surv++;
		if (allPassangers[i].survival == 1 && allPassangers[i].pclass == 1)fClassSurv++;
		if (allPassangers[i].survival == 1 && allPassangers[i].pclass == 2)sClassSurv++;
		if (allPassangers[i].survival == 1 && allPassangers[i].pclass == 3)tClassSurv++;
		if (allPassangers[i].survival == 1 && allPassangers[i].sex == "male")maleSurv++;
		if (allPassangers[i].survival == 1 && allPassangers[i].sex == "female")femaleSurv++;
		if (allPassangers[i].sex == "male") {
			maleCount++;
			averMalAge += allPassangers[i].age;
		}
		if (allPassangers[i].sex == "female") {
			femaleCount++;
			averFemAge += allPassangers[i].age;
		}
		if (allPassangers[i].embarked == "C")counterC++;
		if (allPassangers[i].embarked == "Q")counterQ++;
		if (allPassangers[i].embarked == "S")counterS++;
		if (allPassangers[i].age < 18)children.push_back(allPassangers[i].id);
	}


	result << "Общее число выживших: " << surv << endl;
	result << "Число выживших из 1 класса: " << fClassSurv << endl;
	result << "Число выживших из 2 класса: " << sClassSurv << endl;
	result << "Число выживших из 3 класса: " << tClassSurv << endl;
	result << "Количество выживших женщин: " << femaleSurv<< endl;
	result << "Количество выживших мужчин: " << maleSurv<< endl;
	result << "Средний возраст пассажира: " << (averFemAge+averMalAge)/(femaleCount+maleCount)<< endl;
	result << "Средний возраст женщин: " << averFemAge/femaleCount << endl;
	result << "Средний возраст мужчин: " << averMalAge/maleCount << endl;
	result << "Штат, в котором село больше всего пассажиров: ";
	if (counterC > counterQ) {
		if (counterC > counterS) {
			result << "Cherbourg" << endl;
		}
		else
		{
			result << "Southampton" << endl;
		}
	}
	else
	{
		if (counterQ > counterS) {
			result << "Queenstown" << endl;
		}
		else
		{
			result << "Southampton" << endl;
		}
	}
	result << "Список идентификаторов несовершеннолетних: ";
	for (int i = 0; i < children.size() ; i++)
	{
		result << children[i] << ',';
	}
	result << endl;


	int c = 0;
	cout << allPassangers[c].id << endl;
	cout << allPassangers[c].survival << endl;
	cout << allPassangers[c].pclass << endl;
	cout << allPassangers[c].name << endl;
	cout << allPassangers[c].sex << endl;
	cout << allPassangers[c].age << endl;
	cout << allPassangers[c].sibsp << endl;
	cout << allPassangers[c].parch << endl;
	cout << allPassangers[c].ticket << endl;
	cout << allPassangers[c].fare << endl;
	cout << allPassangers[c].cabin << endl;
	cout << allPassangers[c].embarked << endl;

	
	system("PAUSE");
}
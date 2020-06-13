МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  

Федеральное государственное автономное образовательное учреждение высшего образования  

"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  

ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  

Кафедра компьютерной инженерии и моделирования

<br/><br/>

### Отчёт по лабораторной работе № 5<br/> по дисциплине "Программирование"

<br/>

студента 1 курса группы ПИ-б-о-191(2)  

Кравченко Дмитрия Сергеевича  

направления подготовки 09.03.04 "Программная инженерия"  

<br/>


<table>

<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>

<td>(оценка)</td>

<td>Чабанов В.В.</td>

</tr>

</table>

<br/><br/>

Симферополь, 2019





**Лабораторная работа №5
Работа с текстовыми файлами**

**Цель:**

1. Научиться работать с текстовыми файлами;
2. Закрепить навыки работы со структурами.

Ход работы

Исходный код:

```c++
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
}
```

Ссылка на файл с выходными данными: https://github.com/DDiometr/worksProgramming/blob/master/labs/lab5/Result.txt

<table>
    <tr><td>Характеристика</td>	<td>Результат</td></tr>
     <tr><td>Общее число выживших: <td>342</td></tr>
 <tr><td>Число выживших из 1 класса:</td> <td>136</td></tr>
 <tr><td>Число выживших из 2 класса:</td> <td>87</td></tr>
 <tr><td>Число выживших из 3 класса:</td> <td>119</td></tr>
 <tr><td>Количество выживших женщин:</td> <td>233</td></tr>
 <tr><td>Количество выживших мужчин:</td> <td>109</td></tr>
 <tr><td>Средний возраст пассажира:</td> <td>23.5847</td></tr>
 <tr><td>Средний возраст женщин:</td> <td>23.0255</td></tr>
 <tr><td>Средний возраст мужчин:</td> <td>23.8891</td></tr>
 <tr><td>Штат, в котором село больше всего пассажиров:</td> <td>Southampton</td></tr></tr>
 <tr><td>Список идентификаторов несовершеннолетних:</td> <td>6,8,10,11,15,17,18,20,23,25,27,29,30,32,33,37,40,43,44,46,47,48,49,51,56,59,60,64,65,<br>66,69,72,77,78,79,83,85,87,88,96,102,108,110,112,115,120,122,126,127,129,139,141,148,<br>155,157,159,160,164,165,166,167,169,172,173,177,181,182,183,184,185,186,187,194,197,1<br>99,202,206,209,215,221,224,230,234,236,238,241,242,251,257,261,262,265,267,271,275,27<br>8,279,283,285,296,298,299,301,302,304,305,306,307,308,325,330,331,334,335,336,341,348<br>,349,352,353,355,359,360,365,368,369,375,376,382,385,387,389,390,408,410,411,412,414,<br>416,420,421,426,429,432,434,436,445,446,447,449,452,455,458,460,465,467,469,470,471,4<br>76,480,481,482,486,490,491,496,498,501,503,505,508,512,518,523,525,528,531,532,533,53<br>4,536,539,542,543,548,550,551,553,558,561,564,565,569,574,575,579,585,590,594,597,599<br>,602,603,612,613,614,619,630,634,635,640,643,644,645,649,651,654,657,668,670,675,681,<br>684,687,690,692,693,698,710,712,719,721,722,728,732,733,739,740,741,747,751,752,756,7<br>61,765,767,769,774,777,778,779,781,782,784,788,789,791,792,793,794,803,804,814,816,82<br>0,825,826,827,828,829,831,832,833,838,840,842,845,847,850,851,853,854,860,864,869,870<br>,876,879,889,</td></tr>

</table>

</table>
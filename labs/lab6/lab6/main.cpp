#include <httplib.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include<string>
 
using namespace std;

void replaceSubstr(string* strChanged, string target, string replaceWith) {

	int i = strChanged->find(target);
	strChanged->replace(i, target.length(), replaceWith);
}

void gen_response(const httplib::Request& req, httplib::Response& res) {
	fstream file("Weather.html");
	fstream test;
	test.open("test.html");
	string str;
	string allHtml;
	string* allHtmlPtr = &allHtml;
	while (!file.eof())
	{
		getline(file, str);
		allHtml += str;
	}
	
	
	httplib::Client cli("api.openweathermap.org", 80);
	nlohmann::json j;
	auto resp = cli.Get("/data/2.5/forecast?q=London&units=metric&appid=294ff0e55fddbfc5799b394c46413624");
	
	if (resp && resp->status == 200) {
		j = nlohmann::json::parse(resp->body);	
	}
	
	
	string temp = j["city"]["name"].dump();
	cout << temp;
	for (int i = 0; i < temp.length(); i++)
	{
		if (temp[i] == '\"')
		{
			temp[i] = ' ';
		}
	}
	replaceSubstr(allHtmlPtr, "{city.name}", temp);
	string date;
	string prevDate = "";
	string temperature;
	string icon;
	int counter = 0;
	int i = 0;
	int pos;
	while (true) {
		if (counter == 5)break;
		date = j["list"][i]["dt_txt"].dump();
		
		date = date.substr(0, date.find(' '));
		date.erase(0, 1);
		if (date != prevDate)
		{
			pos = allHtml.find("{list.dt}");
			allHtml.replace(pos, 9, date);
			prevDate = date;
			temperature = j["list"][i]["main"]["temp"].dump();
			pos = allHtml.find("{list.main.temp}");
			allHtml.replace(pos, 16, temperature);
			icon = j["list"][i]["weather"][0]["icon"].dump();
			icon.erase(0,1);
			icon.erase(3, 1);
			pos = allHtml.find("{list.weather.icon}");
			allHtml.replace(pos, 19, icon);
			counter++;
		}
		i++;
	}
	
res.set_content(allHtml, "text/html");
}

int main() {
	httplib::Server svr;                    // Создаём сервер (пока-что не запущен)
	svr.Get("/", gen_response);    // Вызвать функцию gen_response если кто-то обратиться к корню "сайта"
	svr.listen("localhost", 1234); // Запускаем сервер на localhost и порту 1234
}





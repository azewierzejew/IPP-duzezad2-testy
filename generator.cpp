//
// Created by piotr on 17.05.19.
//

#include <vector>
#include <cstdio>
#include <map>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

struct road
{
    int year;
    int length;
};

map<pair<int,int>, road> roads;
map<int, string> cities;

vector<int> v;

int size = 1000;
int cityCount = 10;
int spoil = 4;
bool ok;

char command[1000000];

void AddComment()
{
    int n = strlen(command);
    //printf("%d\n",n);
    for(int i = n; i >=1;i--) command[i] = command[i - 1];
    command[0]='#';
    command[n + 1]='\0';
}

void AddFrontWhitespace()
{
    int n = strlen(command);
    for(int i = n; i >=1;i--) command[i] = command[i - 1];
    command[0]=' ';
    command[n + 1]='\0';
}

void AddEndWhitespace()
{
    int n = strlen(command);
    command[n] = ' ';
    command[n + 1] = '\0';
}

void AddSemicolon()
{
    int n = strlen(command);
    int pos = rand()% n;
    for(int i = n; i >= pos; i--) command[i] = command[i - 1];
    command[pos]=';';
    command[n + 1] = '\0';
}

void RandomChanges()
{
	int n = strlen(command);
	int k = rand() % 3 + 1;

	for(int i = 0; i < k; i++)
	{
		char c;
		do
		{
			c = rand() % 200 + 40;
		} while(isspace(c));

		command[rand() % n] = c;
	}
}

void SpoilCommand()
{

    int r = rand()%15 + 1;
    //printf("spoil %d\n",r);
    if(r & 1 ) AddComment();
    if(r & 2) AddFrontWhitespace();
    if(r & 4) AddEndWhitespace();
    if(r & 8) AddSemicolon();
    if(r & 16) RandomChanges();


    ok = false;
    //if((r & 1) != 0 && (r & 2) == 0) ok = true;
}

void addroad()
{
    int c1 = rand() % cityCount;
    int c2 = rand() % cityCount;

    int year = rand() % 20 - 10;
    int length  = rand() % 10;

    if(year == 0 || length == 0) ok = false;

    if(c1 == c2) ok = false;

    sprintf(command, "addRoad;%s;%s;%d;%d",cities[c1].c_str(),cities[c2].c_str(),length, year);

    if(rand() % spoil == 0) SpoilCommand(), ok = false;

    if(roads.find(make_pair(min(c1,c2), max(c1,c2)))!=roads.end()) ok = false;

    if(ok)
    {
        road r;
        r.length = length;
        r.year = year;
        roads.emplace(make_pair(min(c1,c2), max(c1,c2)), r);
    }
}

void repairroad()
{
    int c1 = rand() % cityCount;
    int c2 = rand() % cityCount;

    if(rand() % 2 == 0)
    {
		auto I = roads.lower_bound(make_pair(min(c1,c2), max(c1,c2)));
		if(I != roads.end())
		{
			c1 = I->first.first;
			c2 = I->first.second;
		}
	}

    int year = rand() % 20 - 10;

    if(year == 0) ok = false;

    if(c1 == c2) ok = false;

    sprintf(command, "repairRoad;%s;%s;%d",cities[c1].c_str(),cities[c2].c_str(), year);

    if(rand() % 4 == 0) SpoilCommand(), ok = false;

    if(roads.find(make_pair(min(c1,c2), max(c1,c2)))!=roads.end())
    {
        road r = roads[make_pair(min(c1,c2), max(c1,c2))];
        if( r.year > year) ok = false;
    }
    else ok = false;

    if(ok)
    {
        roads[make_pair(min(c1,c2), max(c1,c2))].year = year;
    }
}

void getdescription()
{
    int routeId = rand()% 1000;
    if(v.size() > 0 && rand() % 3 > 0) routeId = v[random() % v.size()];

    sprintf(command, "getRouteDescription;%d",routeId);
    if(rand()%4 == 0) SpoilCommand();
}

void addroute()
{
	int len = rand() % 3 + 1;

	if(len == 1) ok = false;

	int routeId = rand() % 1000;

	if(rand() % spoil == 0)
	{
		ok = false;
		if(v.size()==0 || rand()%5 == 0) routeId = 0;
		else routeId = v[rand() % v.size()];
	}

	for(int i = 0; i < (int)v.size(); i++) if(v[i] == routeId) ok = false;

	int m[100];
	int l[100];
	int y[100];

	for(int i = 0;i<len;i++)
	{
		m[i] = rand() % cityCount;

		for(int j = 0; j < i; j++) if(m[j] == m[i]) ok = false;

		if(i > 0)
		{
			l[i - 1] = rand() % 10;
			y[i - 1] = rand() % 20 - 10;
			if(l[i - 1]==0 || y[i - 1]==0)ok = false;
		}
	}

	int buff =  0;
	buff += sprintf(command + buff,"%d;%s",routeId,cities[m[0]].c_str());

	if(ok && rand() % 2==0)
	{
		for(int i = 1; i < len; i++)
		{
			auto I = roads.find(make_pair(min(m[i], m[i  -1]), max(m[i],m[i-1])));
			if(I != roads.end())
			{
				l[i - 1] = I->second.length;
				y[i - 1] = max(y[i - 1],I->second.year);
			}
		}

		v.push_back(routeId);
	}

	if(ok)
    {
        for(int i = 1; i < len; i++)
        {
            auto I = roads.find(make_pair(min(m[i], m[i  -1]), max(m[i],m[i-1])));
            if(I != roads.end())
            {
                if(l[i - 1] != I->second.length) ok = false;
                if(y[i - 1] < I->second.year) ok = false;
            }
        }
    }

	for(int i = 1; i < len; i++)
	{
		buff += sprintf(command + buff,";%d;%d;%s",l[i - 1],y[i - 1],cities[m[i]].c_str());
	}

	if(rand() % spoil == 0) SpoilCommand();

	if(ok)
	{
		for(int i = 1; i < len; i++)
		{
			road r;
			r.year = y[i - 1];
			r.length = l[i - 1];

			roads[make_pair(min(m[i],m[i-1]),max(m[i],m[i-1]))] = r;
		}
	}
}



int main(int argc, char* argv[])
{
	if (argc > 2) {
		srand(atoi(argv[1]));
		size = atoi(argv[2]);
	}
	
    for(int i = 0; i < cityCount; i++)
    {
		string s = "";
		int len = rand() % 5 + 3;

		for(int i = 0; i < len; i++)
		{
			char c;
			do
			{
				c = rand() % 26 + 'A';
				//c = rand() % 256;
			} while(c < 31 && c != ';');

			s+=c;
		}

		cities.emplace(i, s);
    }

    for(int i = 0; i < size; i++)
    {
		ok = true;

        int com = rand() % 4;

        if(com == 0)addroad();
        if(com == 1)repairroad();
        if(com == 2)getdescription();
        if(com == 3)addroute();

        printf("%s\n",command);
        if(!ok && command[0] != '#')fprintf(stderr, "ERROR %d\n",i + 1);
    }
}

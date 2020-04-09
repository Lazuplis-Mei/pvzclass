#pragma once
#include "Enums/PlantType.h"
#include "PVZ.h"
#include <vector>
namespace Utils
{
	typedef PVZ::Memory Memory;
#define Read(x) (Memory::ReadMemory<int>(x))
#define Write(x,y) (Memory::WriteMemory<int>(x,y))
	int GetPlantCost(PlantType::PlantType type)
	{
		int address = 0x69F2C0 + 0x24 * type;
		return Read(address);
	}
	void SetPlantCost(PlantType::PlantType type, int cost)
	{
		int address = 0x69F2C0 + 0x24 * type;
		Write(address, cost);
	}
	int GetPlantCooldown(PlantType::PlantType type)
	{
		int address = 0x69F2C4 + 0x24 * type;
		return Read(address);
	}
	void SetPlantCooldown(PlantType::PlantType type, int cooldown)
	{
		int address = 0x69F2C4 + 0x24 * type;
		Write(address, cooldown);
	}
	int GetPlantSpeed(PlantType::PlantType type)
	{
		int address = 0x69F2CC + 0x24 * type;
		return Read(address);
	}
	void SetPlantSpeed(PlantType::PlantType type, int speed)
	{
		int address = 0x69F2CC + 0x24 * type;
		Write(address, speed);
	}
	void SetSunValue(int sun)
	{
		Write(0x4309F0, sun);
	}
	int readmemory(int t)
	{
		return Read(t);
	}
	bool isvalid(const char* s, int l, int r)
	{
		int top = 0;
		for (int i = l; i < r; i++)
		{
			if (s[i] == '[')
				top++;
			if (s[i] == ']')
			{
				if (top <= 0)
					return 0;
				top--;
			}
		}
		return top == 0;
	}
	bool t(char a)
	{
		return isalnum(a);
	}
	//O(n)
	int GetAddress(const char* s, int l = 0, int r = -1)
	{
		//	cerr<<"l: "<<l<<endl;
		if (r == -1)
		{
			r = strlen(s);
			//		cerr<<"length of "<<s<<" is "<<r<<endl;
			if (!isvalid(s, l, r))
				return -1;
		}
		//	cerr<<l<<" "<<r<<endl;
		int top = 0;
		bool can = 1;
		for (int i = l; i < r; i++)
			if (!t(s[i]))
			{
				can = 0;
				break;
			}
		if (can)
		{
			int rt = 0;
			//cerr << l << " " << r << endl;
			for (int i = l; i < r; i++)
			{
				rt *= 16;
				char c = s[i];
				if (isdigit(c))
				{
					rt += c - '0';
				}
				if (isupper(c))
				{
					rt += c - 'A' + 10;
				}
				if (islower(c))
				{
					rt += c - 'a' + 10;
				}
			}

			return rt;
		}


		std::vector<int> v;
		v.push_back(l - 1);
		for (int i = l; i < r; i++)
		{
			//		if(s[i]=='+')
			//		{
			//			cerr<<"+ "<<i<<" "<<top<<endl;
			//		}
			if (s[i] == '+' && top == 0)
				v.push_back(i);
			if (s[i] == '[')
				top++;
			if (s[i] == ']')
			{
				if (top <= 0)
					return 0;
				top--;
			}
		}
		//	cerr<<"top"<<top<<endl;
		v.push_back(r);
		int rt = 0;
		//cerr << v.size();
		for (int i = 0; i < (int)v.size() - 1; i++)
		{
			int ll = v[i] + 1;
			int rr = v[int((long long)i + 1LL)];
			//		for(int i=ll;i<rr;i++)
			//			cerr<<s[i];
			//		cerr<<endl;
			bool need = 0;
			if (s[ll] == '[' && s[rr - 1] == ']')
			{
				ll++;
				rr--;
				need = 1;
			}
			int t = GetAddress(s, ll, rr);//[...]
			rt += need ? readmemory(t) : t;
		}
		return rt;
	}
#undef Read(x)
#undef Write(x,y)
}
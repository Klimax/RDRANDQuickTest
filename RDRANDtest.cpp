#include <iostream>
#include <intrin.h>
#include <bitset>

int main()
{
	int cpuInfo[4];
	std::bitset<32> EAX;
	std::bitset<32> EBX;
	std::bitset<32> ECX;
	std::bitset<32> EDX;

	__cpuid(cpuInfo, 1);
	EAX = cpuInfo[0];
	EBX = cpuInfo[1];
	ECX = cpuInfo[2];
	EDX = cpuInfo[3];

	bool RDRAND_success(true);

	if (ECX[30])
	{
		unsigned int val1(0);
		_rdrand32_step(&val1);
		std::cout << val1 << std::endl;
		for (int i = 0; i < 666; i++)
		{
			unsigned int val2(0);
			int res = _rdrand32_step(&val2);
			std::cout << val2 << std::endl;
			if (res)
			{
				if (val1 == val2 || val1 == -1 && val2 == -1)
				{
					std::cout << "indentical values generated!" << std::endl;
					RDRAND_success = false;
				}
			}
			else
			{
				std::cout << "RDRAND failed to generate valid number!" << std::endl;
			}
			val1 = val2;
		}
	}
	std::cout << "RDAND is returning random data: " << RDRAND_success << std::endl;
}


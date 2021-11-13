#include <iostream>
#include <vector>
#include <array>
#include <stack>
#define array_size 3
#define all_size 8

using namespace std;

void recursive(const int level, stack<bool>& values, vector<array<bool, array_size>>& result)
{
	if (level != array_size)
	{
		for (int i = 0; i < 2; i++)
		{
			values.emplace(i);
			
			recursive(level + 1, values, result);

			values.pop();
		}
	}

	else
	{
		array<bool, array_size> to_push;

		for (int i = 0; i < array_size; i++)
		{
			to_push[array_size - 1 - i] = values.top();

			values.pop();
		}

		for (int i = 0; i < array_size; i++)
		{
			values.push(to_push[i]);
		}

		result.push_back(to_push);
	}
}

void generate_all(vector<array<bool, array_size>>& result)
{
	stack<bool> values;

	recursive(0, values, result);
}

bool multiply(const array<bool, array_size>& a, const array<bool, array_size>& x)
{
	int sum = 0;

	for (int i = 0; i < array_size; i++)
	{
		sum += a[i] && x[i];
	}

	return sum % 2;
}

void print_c(const vector<array<bool, array_size>>& all_inputs, const array<bool, all_size>& f)
{
	for (int i = 0; i < all_size; i++)
	{
		int c = 0;

		cout << "C(";

		for (int j = 0; j < array_size; j++)
		{
			cout << all_inputs[i][j];
		}

		cout << ") = ";
		
		for (int j = 0; j < all_size; j++)
		{
			int value = f[j] * (multiply(all_inputs[i], all_inputs[j]) ? -1 : 1);

			if (value >= 0)
			{
				cout << '+';
			}

			cout << value;
			
			c += value;
		}

		cout << " = " << float(c) / all_size << endl;
	}
}

void print_h(const vector<array<bool, array_size>>& all_inputs, const array<bool, all_size>& f)
{
	for (int i = 0; i < all_size; i++)
	{
		int h = 0;

		cout << "H(";

		for (int j = 0; j < array_size; j++)
		{
			cout << all_inputs[i][j];
		}

		cout << ") = ";
		
		for (int j = 0; j < all_size; j++)
		{
			int value = f[j] != multiply(all_inputs[i], all_inputs[j]) ? -1 : 1;

			if (value >= 0)
			{
				cout << '+';
			}

			cout << value;
			
			h += value;
		}

		cout << " = " << h << endl;
	}
}

int pow(const int a, const int b)
{
	int result = 1;

	for (int i = 0; i < b; i++)
	{
		result *= a;
	}

	return result;
}

void avalanche(const vector<array<bool, array_size>>& all_inputs, const array<bool, all_size>& f)
{
	for (int i = 0; i < array_size; i++)
	{
		int s = 0;

		cout << "S = ";

		for (int j = 0; j < all_size; j++)
		{
			int value = (f[j] != f[(j + pow(2, i)) % all_size] ? -1 : 1);

			if (value >= 0)
			{
				cout << '+';
			}

			cout << value;

			s += value;
		}

		cout << " = " << s << endl;
	}
}

int main()
{
	vector<array<bool, array_size>> all_inputs;

	generate_all(all_inputs);

	array<bool, all_size> f = { 0, 0, 0, 1, 0, 1, 1, 1 };

	print_c(all_inputs, f);

	print_h(all_inputs, f);

	avalanche(all_inputs, f);

	return 0;
}
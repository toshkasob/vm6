// _______________________
// what need to do?
// try change. what is done?
// it's work. changing is highlighted by green in commits
// _______________________
// translit=vozmozhnie oshibki ili ih ispravlenie
// clear English = real comment to understand how program work
// _______________________
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
// #include <ifstream>
// #include <ofstream>

using namespace std;

int H, T, F;
float h, t, f;					// step by r, t, fi
enum WherePoint
{ inside, outside };
float analit(float x, float f, float y = 1)
{
	WherePoint flag;
	flag = (x < 0 || x > 1 || f < 0 || f > 3.14 / 2 || y < 0 || y > 1) ? outside : inside;
	switch (flag)
	{
	case inside:
		// cout << "belowLC" << endl;
		return (x * cos(f) * sqrt(5 - 4 * y));
		// solution 
		break;
	default:
		cout << "INCORRECT! point x=" << x << "  t=" << y << "fi=" << f << 
			"  is not in [0,1]×[0,1]" << endl;
		throw 0;
		return -10;				// all solution >=-2
		break;
	}
}





int main()
{
	cout.setf(ios::showpos);
	char restart = 'n';
	H = 10;
	T = 10;
	int flagDouble = 0;
  start:
	t = 1. / T;
	h = 1. / H;
	float px, py;
	/* { cout << "enter the point x="; cin >> px; cout << " y="; cin >> py;
	   cout << endl; float mindSolution = analit(px, py); // sled if
	   (mindSolution == -10) { cout << "error. аналитическое
	   решение не может быть найдено... конец
	   программы" << endl; return 1; } else { cout << "mindSolution=" 
	   << mindSolution << endl; }

	   } */
	vector < float >mindSolutionAtT(H + 1);
	for (int i = 0; i <= H; i++)
	{
		try
		{
			mindSolutionAtT[i] = analit(i * h, 1);
		}
		catch(int f)
		{
			cout <<
				"error. your mindsolution cannot calculated. you need change X in your programm";
			return 0;
		}
	}
	cout << endl;

	vector < vector < float >>u(H + 1);
	for (int i = 0; i <= H; i++)
	{
		u[i].resize(T + 1);
		for (int j = 0; j <= T; j++)
		{
			// NB: i*h=xL, j*t=tN
			// assignment U from difference scheme
			if (j == 0)
			{
				u[i][j] = log(1 + (i * h) * (i * h)) + sin(i * h);
			}
			else if (i == 0)
			{
				u[i][j] = log(1 + (j * t) * (j * t));
			}
			else if (i == 1)
			{
				u[i][j] = log(1 + (j * t) * (j * t)) + h * (cos(i * h) - 2 * j * t / (1 + (j * t) * (j * t)));	// u1N 
																												// 
				// 
				// 
				// 
				// 
				// 
				// 
				// 
				// = 
				// u0N+h*(u0N)' 
				// = 
				// u0N+h*(cos(x)-(u0N)°) 
				// = 
				// u0N+h*[ln(1+tN^2)]'
			}
			else
			{
				u[i][j] =
					u[i - 1][j] + (-u[i - 1][j - 2] + 4 * u[i - 1][j - 1] -
								   3 * u[i - 1][j]) * t / 2 / h + (u[i - 1][j - 2] - 2 * u[i -
																						   1][j -
																							  1] +
																   u[i -
																	 1][j]) * t * t / 2 / h / h +
					t * cos(i * h) + t * t / 2 * sin(i * h);
			}					// u》L》N+1


		}
	}

	// cout final table:
	int columnWidth = 20;
	float maxDiff = 0.;
	cout << endl;
	cout << setw(columnWidth / 2) << "x. ";
	cout << setw(columnWidth) << "sled. " /*- analiticheskoe reshenie"*/ ;
	cout << setw(columnWidth) << "chislennoe reshenie. ";
	cout << setw(columnWidth) << "difference module. " << endl;
	for (int i = 0; i <= H; i++)
	{
		if (i % (int)pow(2, flagDouble) == 0)
		{
			// cout.width(columnWidth);
			cout.precision(4);
			cout << setw(columnWidth / 2) << i * h;
			cout << setw(columnWidth) << mindSolutionAtT[i];
			cout << setw(columnWidth) << u[i][T];
			float diff = abs(u[i][T] - mindSolutionAtT[i]);
			cout << setw(columnWidth) << diff;
			if (maxDiff < diff)
			{
				maxDiff = diff;
			}
			cout << endl;
		}
	}
	cout << "maxDiff=" << maxDiff << endl;

	// end:
	// cout << "do you want recalc in another point? ";
	cout << "do you want double step?   ";
	cin >> restart;
	if (restart == 'y')
	{
		T *= 2;
		H *= 2;
		flagDouble++;
		goto start;
	}
	return 0;
}
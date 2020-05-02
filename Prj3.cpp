//       ____   __     __
//        /   /   \  /   \
//       /   /      /
//      /    \___/  \___/
//
// Date: April, 30, 2020
// Name:	Victor Olabiyi
// Project:	Project 3
// Inputs: Heigth, velocity, angle and N value	
// Outputs:	values calculated: time(s), max distance(x), max distance(y) and a table.
// Program Description:

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;
const double PI = acos(-1.0);	// global varaiable
const double g = -9.81;			// global varaible

// Declaring prototypes
double torad(double);
double RealRoot(double, double, double, double&, double&);
string Velconv(string&);

// function for the Angle
double torad(double Angle)
{
	return Angle*PI/180;
}
// function for the roots
double RealRoot(double A, double B, double C, double& Root1, double& Root2)
{
	double D = B*B - 4 * A * C;
    if(D>=0)
    {
        Root1 = (-1 * B + sqrt(D))/(2 * A);
        Root2 = (-1 * B - sqrt(D))/(2 * A);
        if(Root1 > 0) return Root1;
        else if(Root2>0) return Root2;
    }
    return 1;
}
// function for the velocity unit
string Velconv(string& unit)
{
	if(unit == "m/s")			{return "m/s";}
	else if(unit == "mph") 		{return "mph";}
	else if (unit == "ft/s")	{return "ft/s";}
	return unit;
}

int main()
{
	char rerun = 'y';
	ofstream  Output;
	fstream Input;
	int  choose, choice, j=0;
	string vUnit, Fname;
	double A[100][3];
	double heigth, vel, Angle, N, time, Vxo, Vyo, xt, yt,  Root1, Root2;
	do	// do while loop for the whole int-main program
	{
		do	// The loop for the inputs ends
		{
			cout << " Enter cliff height (in m): ";
			cin >> heigth;
			if(heigth > 0)
			{
				cout << " Velocity unit is either one of the following:\n" << endl;
				cout << " m/s, mph or ft/s ";
				cout << endl << endl;
				cout << " Enter initial velocity (w/unit): ";
				cin >> vel >> vUnit;
				vUnit = Velconv(vUnit);		// calling for the velocity unit function
				// using the if-statement to check for the rigth unit for velocity
				if(vUnit == "m/s")  {vel = vel;}
				if(vUnit == "mph")  {vel/= 2.237;} 
				if(vUnit == "ft/s")  {vel /= 3.28;}
				// using while loop for the wrong inputs for the units
					while(vUnit != "m/s" && vUnit != "mph" && vUnit != "ft/s")
			    	{
			    		cout << "units are incorrect, rerun\n";
			    		cout << "would you like to continue? input Y or y: ";
			    		cin >> rerun;
			    		if(rerun!='Y'&& rerun!='y')
						{
							cout << "User ended program." << endl;;
							return 1;	
						}
						else
							cout << " Enter initial velocity (w/unit): ";
							cin >> vel >> vUnit;	
						if(vUnit == "m/s" || vUnit == "mph" || vUnit == "ft/s")
						break;
					}
				if(vel > 0)
				{
					do
					{
						cout << " Enter angle in degree (0 < A < 90): ";
						cin >> Angle;
						if(Angle > 0 && Angle <90 )
						{
							do
							{
								cout << " Enter the number of point: ";
								cin >> N;
								if(!(N > 5 && N <= 100))
								// display this message if the user enters negative 
								// value for N
								{cout << " Invalid Input for N. Try again? y : ";
								cin >> rerun;}
								else
									break;
							}
							while(rerun == 'y' || rerun == 'Y');
							break;
						}	// display this message if the user enters negative Angle
						else
							cout << " Angle invalid. try again? enter y or n: ";
							cin >> rerun;
					}
					while(rerun == 'y' || rerun == 'Y');
					break;
				}	// display this message if the user enters negative velocity
				else
					cout << " Velocity invalid. try again? enter y or n: ";
					if(rerun == 'y' || rerun == 'Y')
					rerun = 'y';
					else{return 0;}
			}	// display this message if the user enters negative heigth
			else
				cout << " Heigth invalid. try again? enter y or n: ";
				cin >> rerun;
		}	// the loop for the inputs ends
		while(rerun == 'y' || rerun == 'Y');
		//if(rerun != 'y' || rerun != 'Y')	return 0;
		Angle = torad(Angle);		// callling for the angle conversion function
		Vxo = vel * cos(Angle);		// calculating Vy
		Vyo = vel * sin(Angle);		// calculating Vx
		time = RealRoot(0.5*g, Vyo, heigth, Root1, Root2); 	// calcutate the time
		cout << " Maximum time to reach the target = " << time << " s" << endl;
		xt = Vxo * time;	// calculate the distance(x)
		cout << " Maximum distance(x) = "  << xt << " m"<< endl;
		yt = heigth - Vyo * Vyo/(2 * g);	// calculate the maximum heigth
		cout << " Maximum heigth reached = " << yt << "  m" << endl;
		cout << endl;
		double div = xt/N;
		// Display the follwoing and ask user how they want to display the table 
		cout << " How do you want to display your values:\n";
		cout << " #1. Display on the screen\n";	cout << " #2. Send to a data file\n";
		cout << " Choice::::";		cin >> choice;
		if(choice == 1 || choice == 2)
		{
			do	// loop for the table display starts
			{
				if( choice == 1)
				// if quser choose 1, do the following
				{
					do	// loop to display the table on the screen starts
					{
						// displaying table 
						cout << " Time(s)" << setw(5) << "||"<< setw(14) << "Distance(m)" <<
						setw(5) << "||"<< setw(14) << "Heigth(m)" << endl;
						cout << "----------------------------------------------" << endl;
						for( double i = 0; i < xt; i+=div)
						{
							j++;
							cout << fixed << right << showpoint ;
							A[j][0] = i/Vxo;
							A[j][1] = i;		
							A[j][2] = Vyo* A[j][0] + 0.5 * g * A[j][0] * A[j][0];
							cout << setw(8) << setprecision(2) << A[j][0] <<setw(18) << setprecision(2) 
							<< A[j][1] << setw(19) << setprecision(2) << A[j][2] << endl;
						}
						break;
					}	// loop to display the table on the screen ends
					while(rerun == 'Y' || rerun == 'y');
					break;
				}
				else if(choice == 2)
				// If the user chooses 2 then do the following
					do	// the loop to send the table into a data file
					{
						cout << " Enter file name(w/extension: vic.txt): ";
						cin >> Fname;
						//Input.open(Fname.c_str());
						Output.open(Fname.c_str());
						
						if(Output.fail())
						{
						cout << " File not found. rerun? enter y or n:  ";
						cin >> rerun;
						}
						else
						{
						
					            for( double i = 0; i < xt; i+=div)
								{
									j++;
									//cout << fixed << right << showpoint ;
									A[j][0] = i/Vxo;
									A[j][1] = i;		
									A[j][2] = Vyo* A[j][0] + 0.5 * g * A[j][0] * A[j][0];
									Output << fixed <<  setw(8)  << A[j][0] << "," <<setw(2) 
									<< A[j][1] << ","<< setw(2) << A[j][2] << setprecision(2) << endl;
								}
							rerun  = 'n';
						}	// Ask user if they want to try again incase they enter an invalid file
						
					}	// The loop to send table to a data file ends
					while(rerun == 'Y' || rerun == 'y');
			}		// The loop for table display choice ends
			while(rerun == 'Y' || rerun == 'y');
				//Ask user if they want to rerun the program
				cout << " End of program. rerun? enter y or n: ";
				cin >> rerun;
				if (rerun == 'y' || rerun == 'Y')
				rerun = 'y';
				// if the user enters no, display this message, then end
				else {cout << " Thank you for playing!"; return 1;}
		}	// Display this message if the user enter the wrong choice
		else
			{cout << " Choice invalid. rerun? enter y or n: ";
			cin >> rerun;}
	}
	while(rerun == 'y' || rerun == 'Y');	//The big loop ends
return 0;		
}

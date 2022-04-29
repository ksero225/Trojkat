#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

class Trojkat{
	protected:
		float x;
		float y;
		float z;
		float h;
	public:
		Trojkat(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->h = h;
		}
		virtual bool zweryfikuj();
		virtual oblicz_bok();
		virtual oblicz_kat();
		virtual oblicz_pole();
		virtual oblicz_obwod();
		
};

class Trojkat_Rownoboczny :public Trojkat{
	protected:
		virtual bool zweryfikuj()
		{
			if( this->x == this->y && this->x == this->z){
			//return Trojkat_Rownoboczny(this->x, this->y, this->z);
			}
			//try new Error("Trojkat Rownoboczny ma wszystkie boki rowne");
		}
		virtual oblicz_pole()
		{
			cout << "Pole trojkata rownobocznego wynosi:" << x * x * sqrt(3) / 4 << endl;	
		}
		virtual oblicz_obwod()
		{
			cout << "Obwod trojkata rownobocznego wynosi:" << 3 * x << endl;
		}
		virtual oblicz_bok()
		{
			
		}
		virtual oblicz_kat()
		{
			
		}
};

class Trojkat_Rownoramienny :public Trojkat{
	protected:
		virtual bool zweryfikuj()
		{
			if( this->x == this->y || this->x == this->z){
			//return Trojkat_Rownoboczny(this->x, this->y, this->z);
			}
			//try new Error("");
		}
		virtual oblicz_pole()
		{
			
		}
		virtual oblicz_obwod()
		{
			cout << "Obwod trojkata rownobocznego wynosi:" << endl;
		}
		virtual oblicz_bok()
		{
			
		}
		virtual oblicz_kat()
		{
			
		}		
};

class Trojkat_Prostokatny :public Trojkat{
	protected:
		virtual bool zweryfikuj()
		{
			//if(){
			//return Trojkat_Rownoboczny();
//			}
			//try new Error("");
		}
		virtual oblicz_pole()
		{
			cout << "Pole trojkata rownobocznego wynosi:" <<   endl;	
		}
		virtual oblicz_obwod()
		{
			cout << "Obwod trojkata rownobocznego wynosi:" <<   endl;
		}
		virtual oblicz_bok()
		{
			
		}
		virtual oblicz_kat()
		{
			
		}
};

int main()
{
	
	
	
	system("PAUSE");
	return 0;
}

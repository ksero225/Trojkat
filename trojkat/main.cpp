#include <iostream>
#include <math.h>
#include <cmath>
#include <string>
#include <iomanip>
#include <limits>

#define PI 3.14159

using namespace std;

struct Wsp { // Wspolrzedne trojkata, podane przez u?ytkownika
	double x;
	double y;
};

class Trojkat {
	public:
		Trojkat(
		    struct Wsp &WspA,
		    struct Wsp &WspB,
		    struct Wsp &WspC
		);// Tutaj podamy wspolrzedne i utworzymy trojkat
		// wyjqtki, zle wspolrzedne, ujemny wynik out,
		~Trojkat(){
		}
		double obliczBok(struct Wsp X, struct Wsp Y) {
			return sqrt(pow(X.x-Y.x,2) + pow(X.y-Y.y,2)); // obliczanie dlugosci boku z podanych wspolrzednych
		}
		int zweryfikuj(struct Wsp WspA, struct Wsp WspB, struct Wsp WspC); // sprawdzimy jaki trojkat wychodzi z podanych przez uzytkowika danych
		//oraz czy wogole jest to trojkat czy odcinek lub punkt
		bool czyPunkt(struct Wsp WspA, struct Wsp WspB, struct Wsp WspC); // sprawdzenie oraz zwrocenie czy z podanych wsporlzednych wychodzi punkt
		bool czyOdcinek(struct Wsp WspA, struct Wsp WspB, struct Wsp WspC);
		double setPrzeciwProstokatna(double bokAB, double bokBC, double bokCA);
		int wynikWeryfikacji() {
			return jakiTrojkat;
		}
		void wyswietlDane(struct Wsp WspA, struct Wsp WspB, struct Wsp WspC);
		double obliczObwod(double bokAB, double bokBC, double bokCA) {
			return bokAB + bokBC + bokCA;
		}
		void obliczKaty(double bokAB, double bokBC, double bokCA);
	protected:
		double bokAB, bokBC, bokCA;
		int jakiTrojkat; // wynik weryfikacji
		double przeciwP; // przeciwprostokatna
		double obwod;
		double pole;
		double h; // wysokosc
		double alfa, beta, gamma; // k?ty
		string nazwaTrojkata;
};

void Trojkat::wyswietlDane(struct Wsp WspA, struct Wsp WspB, struct Wsp WspC) {
	cout << "Wspolrzedne trojkata" << endl;
	cout << "x1: " << WspA.x << " y1: " << WspA.y << endl;
	cout << "x2: " << WspB.x << " y2: " << WspB.y << endl;
	cout << "x3: " << WspC.x << " y3: " << WspC.y << endl;

	cout << "\nOdcinek AB: " << bokAB << endl;
	cout << "Odcinek BC: " << bokBC << endl;
	cout << "Odcinek CA: " << bokCA << endl;

	cout << "\nObwod wynosi: " << obwod << endl;
	cout << "Pole wynosi: " << pole << endl;

	cout << "\nMiary katow" << endl;
	cout << setprecision(5);
	cout << "Alfa: " << alfa << endl;
	cout << "Beta: " << beta << endl;
	cout << "Gamma: " << gamma << endl;
}

Trojkat::Trojkat(struct Wsp &WspA, struct Wsp &WspB, struct Wsp &WspC) {

	bokAB = obliczBok(WspA, WspB);
	bokBC = obliczBok(WspB, WspC);
	bokCA = obliczBok(WspC, WspA);

	jakiTrojkat = zweryfikuj(WspA, WspB, WspC);
	obliczKaty(bokAB, bokBC, bokCA);
}

int Trojkat::zweryfikuj(struct Wsp WspA, struct Wsp WspB, struct Wsp WspC) {

	double AB = pow(bokAB, 2);
	double BC = pow(bokBC, 2);
	double CA = pow(bokCA, 2);

	if(czyPunkt(WspA, WspB, WspC)) {
		return 1; // punkt
	} else if(czyOdcinek(WspA, WspB, WspC)) {
		return 2; // odcinek
	} else if(bokAB == bokBC && bokAB == bokCA)
		return 3; // trojkat rownoboczny
	else if(bokAB == bokBC || bokAB == bokCA  || bokCA == bokBC)
		return 4;	// trojkat rownoramienny
	else if(AB == (BC + CA) || BC == (AB + CA) || CA == (AB + BC)) {
		// trojkat prostokatny
		przeciwP = setPrzeciwProstokatna(AB, BC, CA);
		return 5;
	}
}

bool Trojkat::czyPunkt(struct Wsp WspA, struct Wsp WspB, struct Wsp WspC) {
	if(WspA.x == WspB.x && WspB.x == WspC.x && WspA.y == WspB.y && WspB.y == WspC.y)
		return true;
	else
		return false;
}

bool Trojkat::czyOdcinek(struct Wsp WspA, struct Wsp WspB, struct Wsp WspC) {
	double a = WspA.x * (WspB.y - WspC.y) + WspB.x * (WspC.y - WspA.y) + WspC.x * (WspA.y - WspB.y);
	// pole trojkata z podanych wspolrzednych
	if(a == 0)
		return true;
	else
		return false;
}

double Trojkat::setPrzeciwProstokatna(double AB, double BC, double CA) {
	if((AB + BC) == CA)
		return sqrt(CA);
	else if((AB + CA) == BC)
		return sqrt(BC);
	else if((BC + CA) == AB)
		return sqrt(AB);
}

void Trojkat::obliczKaty(double bokAB, double bokBC, double bokCA) {
	// twierdzenie cosinus?w
	double bokAB2 = pow(bokAB, 2);
	double bokBC2 = pow(bokBC, 2);
	double bokCA2 = pow(bokCA, 2);

 // c^2 = a^2 + b^2 - 2(a)(b)(cos beta) -> beta = acos( ( a^2 + b^2 - c^2 ) / (2ab) )
	alfa = acos((bokBC2 + bokCA2 - bokAB2)/(2*bokBC*bokCA));
	beta = acos((bokAB2 + bokCA2 - bokBC2)/(2*bokAB*bokCA));
	gamma = acos((bokAB2 + bokBC2 - bokCA2)/(2*bokAB*bokBC));

	//zamiana z radianow, na stopnie
	alfa = alfa * 180 / PI;
	beta = beta * 180 / PI;
	gamma = gamma * 180 / PI;
}

class TrojkatRownoboczny:public Trojkat {
	public:
		TrojkatRownoboczny(
		    struct Wsp &WspA,
		    struct Wsp &WspB,
		    struct Wsp &WspC
		):Trojkat(WspA, WspB, WspC) {
			h = obliczH(bokAB);
			obwod = obliczObwod(bokAB, bokBC, bokCA);
			pole = obliczPole(bokAB);
			alfa = 60, beta = 60, gamma = 60;
			Trojkat::wyswietlDane(WspA, WspB, WspC);
			cout << "Wysokosc wynosi: " << h << endl;
		};
		~TrojkatRownoboczny(){
		}
	private:
		// tutaj obliczamy obwod, miary katow, pole,
		// obwod: bokA + bokB + bokC
		// pole a^2 * sqrt(3) / 4
		double obliczH(double bokAB) {
			return (sqrt(3)*bokAB)/2;
		}
		double obliczPole(double bokAB) {
			return (pow(bokAB, 2)*sqrt(3))/4;
		}
};

class TrojkatProstokatny:public Trojkat {
	public:
		TrojkatProstokatny(
		    struct Wsp &WspA,
		    struct Wsp &WspB,
		    struct Wsp &WspC
		):Trojkat(WspA, WspB, WspC) {
			if(przeciwP == bokAB) {
				h1 = bokBC;
				h2 = bokCA;
				pole = obliczPole(bokAB, h1);
			} else if(przeciwP == bokBC) {
				h1 = bokAB;
				h2 = bokCA;
				pole = obliczPole(bokAB, h1);
			} else if(przeciwP == bokCA) {
				h1 = bokAB;
				h2 = bokBC;
				pole = obliczPole(bokAB, h1);
			}
			obwod = obliczObwod(bokAB, bokBC, bokCA);
			Trojkat::wyswietlDane(WspA, WspB, WspC);
			cout << "Wysokosc trojkata wynosi: " << h1 << " lub " << h2 << endl;
			cout << "Przeciwprostokatna wynosi: " << przeciwP << endl;
		};
		~TrojkatProstokatny(){
		}
	private:
		double h1, h2;
		double obliczPole(double a, double h) {
			return (a*h)/2;
		}
};

class TrojkatRownoramienny:public Trojkat {
	public:
		TrojkatRownoramienny(
		    struct Wsp &WspA,
		    struct Wsp &WspB,
		    struct Wsp &WspC
		):Trojkat(WspA, WspB, WspC) {
			if(bokAB == bokBC) {
				h = obliczH(bokCA,bokAB);
				pole = obliczPole(bokCA, h);
			} else if(bokAB == bokCA) {
				h = obliczH(bokBC, bokAB);
				pole = obliczPole(bokBC, h);
			} else if(bokCA == bokBC) {
				h = obliczH(bokAB, bokBC);
				pole = obliczPole(bokAB, h);
			}
			obwod = obliczObwod(bokAB, bokBC, bokCA);
			Trojkat::wyswietlDane(WspA, WspB, WspC);
		};
		~TrojkatRownoramienny(){
		}
	private:
		double obliczH(double a, double b) {
			h = pow(b/2, 2) + pow(a, 2);
			return sqrt(h);
		}
		double obliczPole(double a, double h) {
			return a/2 * h;
		}
};

class DowolnyTrojkat:public Trojkat {
	public:
		DowolnyTrojkat(
		    struct Wsp &WspA,
		    struct Wsp &WspB,
		    struct Wsp &WspC
		):Trojkat(WspA, WspB, WspC) {
			obwod = obliczObwod(bokAB, bokBC, bokCA);
			pole = obliczPole(obwod/2, bokAB, bokBC, bokCA); // wzor herona, p = 1/2 obwodu
			Trojkat::wyswietlDane(WspA, WspB, WspC);
		};
		~DowolnyTrojkat(){
		}
	private:
		double obliczPole(double p, double a, double b, double c) {
			return sqrt(p * (p - a) * (p - b) * (p - c));
		}
};

Wsp WspA;
Wsp WspB;
Wsp WspC;

void pobierzDane() {
		cout << "Podaj wspolrzedne punktu A" << endl;
		cout << "x1: ";
		cin >> WspA.x;
		cout << "y1: ";
		cin >> WspA.y;
	
		cout << "Podaj wspolrzedne punktu B" << endl;
		cout << "x2: ";
		cin >> WspB.x;
		cout << "y2: ";
		cin >> WspB.y;
	
		cout << "Podaj wspolrzedne punktu C" << endl;
		cout << "x3: ";
		cin >> WspC.x;
		cout << "y3: ";
		cin >> WspC.y;
}

int main(int argc, char** argv) {

	pobierzDane();

	Trojkat Trojkat(WspA, WspB, WspC);

	int jakiTrojkat = Trojkat.wynikWeryfikacji();

	system("cls");
	switch(jakiTrojkat) {
		case 1: {
			cout << "Z podanych wspolrzednych wychodzi punkt" << endl;
			cout << "Wspolrzedne punktu " << endl;
			cout << "x: " << WspA.x << endl;
			cout << "y: " << WspA.y << endl;
			break;
		}
		case 2: {
			cout << "Z podanych wspolrzednych wychodzi odcinek" << endl;
			break;
		}
		case 3: {
			cout << "Trojkat Rownoboczny " << endl;
			TrojkatRownoboczny TrojkatRownoboczny(WspA, WspB, WspC);
			break;
		}
		case 4: {
			cout << "Trojkat Rownoramienny " << endl;
			TrojkatRownoramienny TrojkatRownoramienny(WspA, WspB, WspC);
			break;
		}
		case 5: {
			cout << "Trojkat Prostokatny " << endl;
			TrojkatProstokatny TrojkatProstokatny(WspA, WspB, WspC);
			break;
		}
		default: {
			//Trojkat dowolny, nie pasuje do ?adnych powy?szych kryteri?w
			DowolnyTrojkat DowolnyTrojkat(WspA, WspB, WspC);
		}
	}
	cout << endl;

	system("PAUSE");
	return 0;
}

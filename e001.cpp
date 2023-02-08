//Ovo je program koji ispisuje Eulerov broj,
//program koristi Mclaurinov razvoj broja e,
//e=1/0!+1/1!+1/2!+1/3!+...,
//autor je Andrija Koncani, profesor Matematike i Fizike
#include<iostream>
#include<vector>
#include<cmath>
#include<ctime>
#include<fstream>
using namespace std;
void test ( int * );

int main()
{
	// deklaracija varijabli za racunanje
	int n, d;
	int br_clanova=1;
	int dec_mj, dec_mj_plus;
	int l=0, y=0, i;
	double c=0;
	
	// deklaracija varijabli za ispis vremena
	time_t trenutno_vrijeme;
	float sekunde;
	
	// deklaracija vektora za sumiranje
	vector <int> sum00; 	//inicijalni vektor 0.5 tj. 1/2!
	vector <int> sum01; 	//vektor nastao dijeljenjem s n
	vector <int> sum02; 	//suma
	
	cout<<"Unesi broj zeljenih decimalnih mjesta!\n";
	cin>>dec_mj;
	
	// stvaranje i imenovanje datoteke za ispis
	string decmj = to_string(dec_mj);
	time(&trenutno_vrijeme);
	string vremenska_oznaka = to_string( (int)trenutno_vrijeme ); //vrem marker
	ofstream moja_datoteka;
	moja_datoteka.open ("Eulerov_broj_" + decmj + "DP_" +  vremenska_oznaka + ".txt");
	
	// racuna potreban br. clanova
	while ( (dec_mj-c)>0 ){ 
		c=log10(br_clanova)+c;      
		br_clanova++;
	}
	cout<<"Potreban broj clanova razvoja je ";
	cout<<br_clanova<<'\n';
	moja_datoteka<<"Potreban broj clanova razvoja je ";
	moja_datoteka<<br_clanova<<'\n';
	
	// racunamo dodatna decimalna mjesta
	dec_mj_plus=dec_mj+10*log10(br_clanova*9); 
	
	//puni vektor sum00 s 0
	while (l<=dec_mj_plus){ 
		d=0;
		sum00.push_back(d);
		l++;
	}
	
	sum00[1]=5;
	sum02=sum00;
	sum02[0]=2;
	l=0;
	n=3;	
	
	// clan (1/(n-1)!) dijeli s brojem n i puni vektor sum01
	while ( n<=br_clanova ){ 
		y=0;
		d=0;
		for ( int x: sum00 ){
			y=(y-d*n)*10+x;		
			d=y/n;
			sum01.push_back(d);
		}
/* 		// ispis novog clana 1/n!
		cout<<"1/"<<n<<"! = \n"; 
		i=0;
		for ( int x: sum01 ){ 
			if ( i==0 ){
				cout<<x<<".\n";
			}
			else {
				cout<<x;
				if ( (i%5)==0 )
					cout<<" ";
				if ( (i%50)==0 )
					cout<<"\n";
				if ( (i%250)==0 )
					cout<<"\n";
			}
			i++;
		}
		cout<<"\n\n";*/
/* 		// ispis novog clana 1/n! u tekstualnu datoteku
		moja_datoteka<<"1/"<<n<<"! = \n"; 
		i=0;
		for ( int x: sum01 ){ 
			if ( i==0 ){
				moja_datoteka<<x<<".\n";
			}
			else {
				moja_datoteka<<x;
				if ( (i%5)==0 )
					moja_datoteka<<" ";
				if ( (i%50)==0 )
					moja_datoteka<<"\n";
				if ( (i%250)==0 )
					moja_datoteka<<"\n";
			}
			i++;
		}
		moja_datoteka<<"\n\n";*/

		// sumira sum01 i sum02 vektore
		for ( i=dec_mj_plus; i>=0; i--){	
			sum02[i]=sum02[i]+sum01[i];
			test( &sum02[i] );	//testira prijenos jedinice
		}
		sum00.swap(sum01);
		sum01.clear();
		n++;
	}
	
	// ispis sume tj. Eulerovog broja na ekran
	cout<<"Eulerov broj: \n"; 
	i=0;
	for ( int x: sum02 ){
		if ( i<=dec_mj ){ //ispisuje samo trazene decimale bez dodatnih
			if ( i==0 ){
				cout<<x<<".\n";
			}
			else {
				cout<<x;
				if ( (i%5)==0 )
					cout<<" ";
				if ( (i%50)==0 )
					cout<<"\n";
				if ( (i%250)==0 )
					cout<<"\n";
			}
			i++;
		}
	}		
	cout<<"\n\n";
	
	sekunde = difftime(time(NULL),trenutno_vrijeme); //izracunava vrijeme
	cout<<"Izracunato za "<<(float)sekunde<<" sec tj. ";
	cout<<(float)sekunde/60<<"  min.\n";
	
	// ispis sume tj. Eulerovog broja u datoteku
	moja_datoteka<<"Eulerov broj: \n"; 
	i=0;
	for ( int x: sum02 ){
		if ( i<=dec_mj ){ //ispisuje samo trazene decimale bez dodatnih
			if ( i==0 ){
				moja_datoteka<<x<<".\n";
			}
			else {
				moja_datoteka<<x;
				if ( (i%5)==0 )
					moja_datoteka<<" ";
				if ( (i%50)==0 )
					moja_datoteka<<"\n";
				if ( (i%250)==0 )
					moja_datoteka<<"\n";
			}
			i++;
		}
	}		
	moja_datoteka<<"\n\n";
	moja_datoteka<<"Izracunato za "<<(float)sekunde<<" sec tj. ";
	moja_datoteka<<(float)sekunde/60<<"  min.\n";
	moja_datoteka.close (); //zatvara datoteku
	
	cout << "Press any key to continue...";
	cin.get();
	cin.get();
	
	return 0;
}
	
// testira prenosenje jedinice
void test ( int *a ){	
	if ( *a>9 ){
		*a=*a-10;
		*(a-1)=*(a-1)+1;
		test( a-1 );
	}
}

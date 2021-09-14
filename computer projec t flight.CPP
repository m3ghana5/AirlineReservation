//This program displays the details of a flight.
#include<fstream.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>
#include<dos.h>
#include<time.h>


class flights
{
char fl_no[10];
char fl_name[25];
int n_o_bs;
int n_o_es;
float pbs;
float pes;
char dest[25];
char time[10];

public:
void add_flight();
void add_schedule();
void display_menu();
void modify();
void booking();
void cancel();
void display_chart();

char* retflno()
{return fl_no;}
char* retname()
{return fl_name;}
float retpbs()
{return pbs;}
float retpes()
{return pes;}
char* retdest()
{return dest;}
char* rettime()
{return time;}

}f;

struct dates
{
int d,m,y;
};

struct schedule
{
char fl_no[10];
dates d1;
int n_o_ba;
int n_o_ea;
}s;

struct reserve
{
char fl_no[25];
long pnr;
char pass_name[25];
char pass_class[25];
long tel_no;
dates d2;
char status;
}r;

//=============================================================================

void disp();                               //Function Prototypes
void search(char flno[],int &flag);
void del();
void title();

int count=0;                               //Global variable count
void search_sc(char flno[],dates st, int &flag2);
void display1();

//=============================================================================

void border()                      //Function for border design
{
clrscr();
textcolor(14);
gotoxy(20,5);
for (int i=0;i<18;i++)
{cout<<"~";
gotoxy(20,5+i);
}
for (int j=18;j>0;j--)
{cout<<"~";
gotoxy(62,4+j);
}
gotoxy(20,5);
for (int k=0;k<22;k++)
{cout<<"~ ";
}
gotoxy(20,23);
for (int m=22;m>0;m--)
{cout<<"~ ";
}
}

//=============================================================================

void intro()                   //Functions for the 2 introductory screens
{
	   char str1[]="A I R L I N E  R E S E R V A T I O N";
      textcolor(13);
	   gotoxy(23,7);
      for(int f=0;f<strlen(str1);f++)
		{
		cprintf("%c", str1[f]);
		}
      char  str[]="S Y S T E M";
       gotoxy(35,10);
		for( int f=0;f<strlen(str);f++)
		{
		cprintf("%c",str[f]);
     // if(str1[f]==' ')
		//{cout<<"\a";}
		}
      char str2[]="Presented by";
		gotoxy(55,20);
		for( int f=0;f<strlen(str2);f++)
		{
		cprintf("%c",str2[f]);
      }
		char str3[]="Meghana Raj Kanchan";
		gotoxy(53,22);
		for(int f=0;f<strlen(str3);f++)
		{
		cprintf("%c",str3[f]);
      }
		char str4[]="XII B";
		gotoxy(60,24);
		for(int f=0;f<strlen(str4);f++)
		{
		cprintf("%c",str4[f]);
      }textmode(C80);
      getch();
      ;

   }
//=============================================================================

void flights::add_flight()            //Function to add flight details
{
char fno[25];
int flag;
ofstream outfile1,outfile2;
char ch1,ch2;
do
{
clrscr();
title();
flag=0;
cout<<"\nADDING FLIGHTS";
cout<<"\n\nEnter the flight number:";
cin>>fno;
strupr(fno);
search(fno,flag);
if (flag==0)
{
strcpy(fl_no,fno);
cout<<"\nEnter the flight Name:";
gets(f.fl_name);
strupr(fl_name);
cout<<"\nEnter the destination:";
cin>>dest;
strupr(dest);
cout<<"\nEnter the number of buisness class seats:";
cin>>n_o_bs;
cout<<"\nEnter the number of economy class seats:";
cin>>n_o_es;
cout<<"\nEnter the price of buisness class seats:";
cin>>pbs;
cout<<"\nEnter the price of economy class seats:";
cin>>pes;
cout<<"\nEnter the time of departure (hrs:min):";
cin>>time;
outfile1.open("flight.dat",ios::binary|ios::app);
outfile1.write((char*)&f,sizeof(f));
outfile1.close();
do
{
int flag2=0;
strcpy(s.fl_no,fl_no);
s.n_o_ba=n_o_bs;
s.n_o_ea=n_o_es;
cout<<"\nEnter the date (dd mm yyyy):";
cin>>s.d1.d>>s.d1.m>>s.d1.y;
search_sc(fno,s.d1,flag2);
if(flag2==0)
{
outfile2.open("schedule.dat",ios::binary|ios::app);
outfile2.write((char*)&s,sizeof(s));
outfile2.close();
}
else
cout<<"\nYou have already added a schedule for this date";
cout<<"\nDo you want to add another schedule? (y/n)            ";
cin>>ch1;
}
while((ch1=='y')||(ch1=='Y'));
}
else
cout<<"\nThis flight already exists                          ";
cout<<"\n\nDo you want to add another flight detail? (y/n)       ";
cin>>ch2;
}
while((ch2=='y')||(ch2=='Y'));
}

//=============================================================================

void flights::add_schedule()                //Function to add flight schedules
{

char fno[25],ch;
int flag=0;
clrscr();
title();
ofstream outfile;
cout<<"\nADDING SCHEDULE";
cout<<"\n\nEnter the flight number: ";
cin>>fno;
strupr(fno);
search(fno,flag);
if (flag==1)
{
do
{int flag2=0;
strcpy(s.fl_no,fno);
s.n_o_ba=n_o_bs;
s.n_o_ea=n_o_es;
cout<<"\nEnter the date: (dd mm yyyy) ";
cin>>s.d1.d>>s.d1.m>>s.d1.y;
search_sc(fno,s.d1,flag2);
if(flag2==0)
{
outfile.open("schedule.dat",ios::binary|ios::app);
outfile.write((char*)&s,sizeof(s));
outfile.close();
}
else
cout<<"\nYou have already added a schedule for this date";
cout<<"\nDo you want to add another schedule? (y/n) ";
cin>>ch;
}
while((ch=='y')||(ch=='Y'));
}
else
{
cout<<"\nSuch a flight does not exist";
getch();
}
}

//=============================================================================

void search(char flno[],int &flag)             //Function to search for existing flights
{

ifstream infile;
infile.open("flight.dat",ios::binary);
if(!infile)
flag=0;
else
{
infile.read((char*)&f,sizeof(f));
while(!infile.eof())
{if (strcmp(f.retflno(),flno)==0)
{flag=1;
break;}
infile.read((char*)&f,sizeof(f));
}
}
}

//=============================================================================

void search_sc(char flno[],dates st, int &flag2)     //Function to search for flight schedules
{
schedule sc;
ifstream infile;
infile.open("schedule.dat",ios::binary);
if(!infile)
flag2=0;
else
{
infile.read((char*)&sc,sizeof(sc));
while(!infile.eof())
{if ((strcmp(sc.fl_no,flno)==0)&&(sc.d1.d==st.d)&&(sc.d1.m==st.m)&&(sc.d1.y==st.y))
{flag2=1;
break;}
infile.read((char*)&sc,sizeof(sc));
}
}
}

//=============================================================================

void display()                       //Function to Display flight schedule
{
int x;
clrscr(); title();
ifstream infile1,infile2;
infile1.open("flight.dat",ios::binary);
infile1.read((char*)&f,sizeof(
f));
gotoxy(1,6);
cout<<"Flight";
gotoxy(1,7);
cout<<"No";
gotoxy(8,6);
cout<<"Flight";
gotoxy(8,7);
cout<<"Name";
gotoxy(23,6);
cout<<"Time";
gotoxy(30,6);
cout<<"Destination";
gotoxy(45,6);
cout<<"Price of";
gotoxy(45,7);
cout<<"BC";
gotoxy(50,7);
cout<<"EC";
gotoxy(55,6);
cout<<"Scheduled";
gotoxy(55,7);
cout<<"for";
gotoxy(67,6);
cout<<"Availble";
gotoxy(67,7);
cout<<"BC";
gotoxy(71,7);
cout<<"EC";
int row=8;
while(!infile1.eof())
{
gotoxy(1,row);
cout<<f.retflno();
gotoxy(8,row);
cout<<f.retname();
gotoxy(23,row);
cout<<f.rettime();
gotoxy(30,row);
cout<<f.retdest();
gotoxy(45,row);
cout<<f.retpbs();
gotoxy(50,row);
cout<<f.retpes();
infile2.open("schedule.dat",ios::binary);
infile2.read((char*)&s,sizeof(s));
while (!infile2.eof())
{
if (strcmp(s.fl_no,f.retflno())==0)
{
gotoxy(55,row);
cout<<s.d1.d<<"/"<<s.d1.m<<"/"<<s.d1.y;
gotoxy(67,row);
cout<<s.n_o_ba;
gotoxy(71,row);
cout<<s.n_o_ea;
row++;
if (row==23)
{
getch();
clrscr(); title();
gotoxy(1,6);
cout<<"Flight";
gotoxy(1,7);
cout<<"No";
gotoxy(8,6);
cout<<"Flight";
gotoxy(8,7);
cout<<"Name";
gotoxy(23,6);
cout<<"Time";
gotoxy(30,6);
cout<<"Destination";
gotoxy(45,6);
cout<<"Price of";
gotoxy(45,7);
cout<<"BC";
gotoxy(50,7);
cout<<"EC";
gotoxy(55,6);
cout<<"Scheduled";
gotoxy(55,7);
cout<<"for";
gotoxy(72,6);
cout<<"Available";
gotoxy(72,7);
cout<<"BC";
gotoxy(77,7);
cout<<"EC";
row=8;
}
}
infile2.read((char*)&s,sizeof(s));
}
infile2.close();
row+=2;
if(row==23)
{
getch();
clrscr(); title();
gotoxy(1,6);
cout<<"Flight";
gotoxy(1,7);
cout<<"No";
gotoxy(8,6);
cout<<"Flight";
gotoxy(8,7);
cout<<"Name";
gotoxy(23,6);
cout<<"Time";
gotoxy(30,6);
cout<<"Destination";
gotoxy(46,6);
cout<<"Price of";
gotoxy(46,7);
cout<<"BC";
gotoxy(50,7);
cout<<"EC";
gotoxy(55,6);
cout<<"Scheduled";
gotoxy(55,7);
cout<<"for";
gotoxy(72,6);
cout<<"Available";
gotoxy(72,7);
cout<<"BC";
gotoxy(77,7);
cout<<"EC";
 row=8;
}
infile1.read((char*)&f,sizeof(f));
}
getch();
}
int flight_display(char dest[],dates d)
{
int flag=0;
int x;
clrscr(); title();
ifstream infile1,infile2;
infile1.open("flight.dat",ios::binary);
infile1.read((char*)&f,sizeof(f));
gotoxy(1,6);
cout<<"Flight";
gotoxy(1,7);
cout<<"No";
gotoxy(8,6);
cout<<"Flight";
gotoxy(8,7);
cout<<"Name";
gotoxy(23,6);
cout<<"Time";
gotoxy(30,6);
cout<<"Destination";
gotoxy(43,6);
cout<<"Price of";
gotoxy(43,7);
cout<<"BC";
gotoxy(48,7);
cout<<"EC";
gotoxy(55,6);
cout<<"Scheduled";
gotoxy(55,7);
cout<<"for";
gotoxy(67,6);
cout<<"Available";
gotoxy(67,7);
cout<<"BC";
gotoxy(71,7);
cout<<"EC";
int row=8;
while(!infile1.eof())
{
if(strcmp(f.retdest(),dest)==0)
{
infile2.open("schedule.dat",ios::binary);
infile2.read((char*)&s,sizeof(s));
while (!infile2.eof())
{
if (strcmp(s.fl_no,f.retflno())==0)
{
if ((s.d1.d==d.d)&&(s.d1.m==d.m)&&(s.d1.y==d.y))
{
flag=1;
gotoxy(1,row);
cout<<f.retflno();
gotoxy(8,row);
cout<<f.retname();
gotoxy(23,row);
cout<<f.rettime();
gotoxy(30,row);
cout<<f.retdest();
gotoxy(43,row);
cout<<f.retpbs();
gotoxy(48,row);
cout<<f.retpes();
gotoxy(55,row);
cout<<s.d1.d<<"/"<<s.d1.m<<"/"<<s.d1.y;

gotoxy(67,row);
cout<<s.n_o_ba;
gotoxy(71,row);
cout<<s.n_o_ea;
row++;
count++;
}
}
infile2.read((char*)&s,sizeof(s));
}
infile2.close();
row+=2;
}
infile1.read((char*)&f,sizeof(f));
}
return(flag);
}

//=============================================================================

void search_flight(char fno[])        //Function to Search for flight availability
{
int x;
int flag=0;
clrscr(); title();
ifstream infile1,infile2;
infile1.open("flight.dat",ios::binary);
infile1.read((char*)&f,sizeof(f));
gotoxy(2,6);
cout<<"Flight";
gotoxy(2,7);
cout<<"No";
gotoxy(10,6);
cout<<"Flight";
gotoxy(10,7);
cout<<"Name";
gotoxy(24,6);
cout<<"Destination";
gotoxy(39,6);
cout<<"Price of";
gotoxy(39,7);
cout<<"BC";
gotoxy(43,7);
cout<<"EC";
gotoxy(51,6);
cout<<"Scheduled";
gotoxy(51,7);
cout<<"for";
gotoxy(62,6);
cout<<"Available";
gotoxy(62,7);
cout<<"BC";
gotoxy(68,7);
cout<<"EC";
int row=8;
while(!infile1.eof())
{
if(strcmp(f.retflno(),fno)==0)
{
flag=1;
gotoxy(2,row);
cout<<f.retflno();
gotoxy(10,row);
cout<<f.retname();
gotoxy(24,row);
cout<<f.retdest();
gotoxy(39,row);
cout<<f.retpbs();
gotoxy(43,row);
cout<<f.retpes();
infile2.open("schedule.dat",ios::binary);
infile2.read((char*)&s,sizeof(s));
while (!infile2.eof())
{
if (strcmp(s.fl_no,f.retflno())==0)
{
gotoxy(51,row);
cout<<s.d1.d<<"/"<<s.d1.m<<"/"<<s.d1.y;

gotoxy(62,row);
cout<<s.n_o_ba;
gotoxy(68,row);
cout<<s.n_o_ea;
row++;
}
infile2.read((char*)&s,sizeof(s));
}
infile2.close();
row+=2;
}
infile1.read((char*)&f,sizeof(f));
}



if(flag==0)
{clrscr(); title();
cout<<"\nThis flight does not exist";
getch();}
else
getch();
}

//=============================================================================

void check(char fno[],dates d,char cl[],int seats,int &flag) //Function to search for availability of seats
{
int p;
char ch;
fstream infile;
infile.open("schedule.dat",ios::in|ios::out|ios::ate|ios::binary);
if(!infile)
{cout<<"Cannot open file";
getch();
}
//infile.read((char*)&s,sizeof(s));
infile.seekg(0,ios::beg);
//while(!infile.eof())
while(infile.read((char*)&s,sizeof(s)))
{


if((strcmp(s.fl_no,fno)==0)&&(s.d1.d==d.d)&&(s.d1.m==d.m)&&(s.d1.y==d.y))
{
if (strcmp(cl,"BUSINESS")==0)
{
if (s.n_o_ba-seats>=0)
{
p=infile.tellp();
infile.seekg(p-sizeof(s));
s.n_o_ba=s.n_o_ba-seats;
cout<<"\nSeats  available on     ";
cout<<s.fl_no<<" "<<s.d1.d<<" "<<s.d1.m<<" "<<s.d1.y<<endl;
getch();
infile.write((char*)&s,sizeof(s));
flag=1;
}
else
{
cout<<"\nSeats not available";
getch();
flag=0;
}
}
if (strcmp(cl,"ECONOMY")==0)
{
if (s.n_o_ea-seats>=0)
{
p=infile.tellp();
infile.seekg(p-sizeof(s));
s.n_o_ea=s.n_o_ea-seats;
cout<<"\nSeats  available on    ";
cout<<s.fl_no<<" "<<s.d1.d<<" "<<s.d1.m<<" "<<s.d1.y<<endl;
getch();
infile.write((char*)&s,sizeof(s));
flag=1;
}
else
{
cout<<"\nSeats not available";
getch();
flag=0;
}
}
}
//infile.read((char*)&s,sizeof(s));
}
infile.close();
}

//=============================================================================

void flights::booking()                    //Function to book a flight ticket
{
clrscr();
title();
int f1,seats=0,flag=0,d,m,y,fl=0;
char dest[25],fl_no1[25],pass_class[15],ans2,ans3,c;
dates d3;
fstream outfile;
outfile.open("reserve.dat",ios::binary|ios::in|ios::app);
cout<<"\n\t\t\t BOOKING TICKET";
cout<<"\n\nEnter the destination:";
cin>>dest;
strupr(dest);
cout<<"\nEnter date of travel:";
	cin>>d3.d>>d3.m>>d3.y;
	count=0;
	f1=flight_display(dest,d3);

	if (f1==1)
	{
     getch();
	  clrscr(); title();
cout<<"\n\nEnter the flight number:";
		cin>>fl_no1;
		strupr(fl_no1);
		search(fl_no1,fl);
		if(fl==1)
		{
cout<<"\nEnter the class you want to travel(E- Economy,B-Business): ";
		cin>>c;
		if (c=='E'||c=='e')
		strcpy(pass_class,"ECONOMY");
		if (c=='B'||c=='b')
		strcpy(pass_class,"BUSINESS");
		strupr(pass_class);
cout<<"\nEnter the number of seats:";
		cin>>seats;
		check(fl_no1,d3,pass_class,seats,flag);
		if (flag==1)
		{
			for (int i=1;i<=seats;i++)
			{//outfile.seekp(0,ios::end);
			outfile.seekp(outfile.tellp()-(sizeof(r)));
		       outfile.read((char*)&r,sizeof(r));
             outfile.close();
		       r.pnr+=1;
cout<<"\n\n passenger number:" <<r.pnr;
cout<<"\n\nEnter the passenger name: ";
			cin>>r.pass_name;
			strupr(r.pass_name);
cout<<"\nEnter the telephone number:";
			cin>>r.tel_no;
			strcpy(r.fl_no,fl_no1);
			strcpy(r.pass_class,pass_class);
			r.d2.d=d3.d;
			r.d2.m=d3.m;
			r.d2.y=d3.y;
			r.status='C';
			cout<<"\nBooking confirmed for  "<<r.pass_name<<"   on ";
			cout<<r.fl_no<<"      "<<r.d2.d<<" "<<r.d2.m<<" "<<r.d2.y<<endl;
			getch();//outfile.seekp(0,ios::end);
         ofstream outfile1("reserve.dat",ios::binary|ios::app);
			 outfile1.write((char*)&r,sizeof(r));
			}

		}
		}
		else
		{
		cout<<"\nInvalid Flight Number";
		getch();

		}

	}
	else
	{clrscr(); title();
	cout<<"\nThere is no flight for this destintation on this date ";
	getch();	 }
}

//=============================================================================

void modi_seats(char fl_no[],dates d4,char cl[],int count)    //Function to modify flight ticket
{int p;
fstream infile;
infile.open("schedule.dat",ios::in|ios::out|ios::binary);
infile.read((char*)&s,sizeof(s));
while(!infile.eof())
{
if
((strcmp(fl_no,s.fl_no)==0)&&(d4.d==s.d1.d)&&(d4.m==s.d1.m)&&(d4.y==s.d1.y))
{
p=infile.tellg();
infile.seekg(p-sizeof(s));
if (strcmp (cl,"BUSINESS")==0)
{s.n_o_ba +=count;
infile.write((char*)&s,sizeof(s));
}
else
{s.n_o_ea +=count;
infile.write((char*)&s,sizeof(s));
}
}
infile.read((char*)&s,sizeof(s));
}
}

//=============================================================================

void flights::cancel()            //Function to cancel flight ticket
{
clrscr();
title();
int n,count=0,p,flag=0;
char fl_no1[25],name[25],cl[25],ans;
int found=0;
dates d5;
fstream infile;
infile.open("reserve.dat",ios::in|ios::out|ios::ate|ios::binary);
cout<<"\n\t\t\tCANCELLATION OF TICKET";
cout<<"\n\nEnter the flight number:";
cin>>fl_no1;
strupr(fl_no1);
search(fl_no1,flag);
if (flag==1)
{
cout<<"\nEnter the date of travel:";
cin>>d5.d>>d5.m>>d5.y;
cout<<"\nEnter the passenger number:";
cin>>n;
infile.seekg(0);
infile.read((char*)&r,sizeof(r));
while(!infile.eof())
{
if((strcmp(fl_no1,r.fl_no)==0)&&(d5.d==r.d2.d)&&(d5.m==r.d2.m)&&(d5.y==r.d2.y)&&(n==r.pnr))
{
p=infile.tellg();
infile.seekg(p-sizeof(r));
strcpy(cl,r.pass_class);
count++;
found=1;
r.status='X';
infile.write((char*)&r,sizeof(r));
break;
}
infile.read((char*)&r,sizeof(r));
}

infile.close();
if(found==0)
{
cout<<"\nRecord Not Found";
getch();
}
else
{
cout<<"\nSeat Cancelled for   "<<r.pass_name<<" on   ";
			cout<<r.fl_no<<"      "<<r.d2.d<<" "<<r.d2.m<<" "<<r.d2.y<<endl;;
getch();
modi_seats(fl_no1,d5,cl,count);
del();                                     //Function prototype
}
}
else
{
cout<<"\nInvalid Flight Number";
getch();
}
}

//=============================================================================

void del()
{title();
clrscr();
int rmn;

ifstream infile("reserve.dat",ios::binary);
ofstream outfile("temp.dat",ios::binary);
infile.read((char*)&r,sizeof(r));
while(!infile.eof())
{
if(r.status!='X')
outfile.write((char*)&r,sizeof(r));
infile.read((char*)&r,sizeof(r));
}

infile.close();
outfile.close();
infile.open("temp.dat",ios::binary);
outfile.open("reserve.dat",ios::binary);
infile.read((char*)&r,sizeof(r));
while(!infile.eof())
{
outfile.write((char*)&r,sizeof(r));
infile.read((char*)&r,sizeof(r));
}
}

//=============================================================================

void flights::display_chart()             //Function to display reservation chart
{char fl_no1[25];
dates d6;
ifstream infile;
int flag=0;
clrscr();
title();
infile.open("reserve.dat",ios::binary);
cout<<"\n\t\t\tDISPLAYING RESERVATION CHART";
cout<<"\n\nEnter the flight number: ";
cin>>fl_no1;
strupr(fl_no1);
cout<<"\nEnter the date of travel: ";
cin>>d6.d>>d6.m>>d6.y;
gotoxy(2,15);
cout<<"Passenger";
gotoxy(2,16);
cout<<"Number";
gotoxy(16,15);
cout<<"Passenger";
gotoxy(16,16);
cout<<"Name";
gotoxy(30,15);
cout<<"Telephone";
gotoxy(30,16);
cout<<"Number";
gotoxy(44,15);
cout<<"Class";
gotoxy(54,15);
cout<<"Status";
int row=17;
infile.read((char*)&r,sizeof(r));
while(!infile.eof())
{
if((strcmp(fl_no1,r.fl_no)==0)&&(d6.d==r.d2.d)&&(d6.m==r.d2.m)&&(d6.y==r.d2.y))
{
flag=1;
gotoxy(2,row);
cout<<r.pnr;
gotoxy(16,row);
cout<<r.pass_name;
gotoxy(30,row);
cout<<r.tel_no;
gotoxy(44,row);
cout<<r.pass_class;
gotoxy(54,row);
cout<<r.status;
row++;
}
infile.read((char*)&r,sizeof(r));
}
if(flag==0)
{
clrscr();
cout<<"\n\n\t\tNo passengers on this flight.";
}
getch();

}

//=============================================================================

void flights::modify()              //Function to modify flight details
{
clrscr();
title();

int flag=0,choice,p;
char fl_no1[25];
float price;
dates d7,d8;
fstream infile;
infile.open("flight.dat",ios::in|ios::out|ios::ate|ios::binary);
cout<<"\n\t\t\tMODIFYING FLIGHT DETAILS";
cout<<"\n\nEnter the flight number: ";
cin>>fl_no1;
strupr(fl_no1);
infile.seekg(0);
infile.read((char*)&f,sizeof(f));

while(!infile.eof())
{
if (strcmp(fl_no1,fl_no)==0)
{
flag=1;
do
{         clrscr(); title();
	  cout<<"\n\n\n\t\t\t\t Menu";
	  cout<<"\n\t\t\t\t------ ----";
	  cout<<"\n\n\t\t\t1.Price of economy class";
	  cout<<"\n\t\t\t2.Price of buisness class";
	  cout<<"\n\t\t\t3.Reschedule flight";
	  cout<<"\n\t\t\t4.Return to Main Menu";
	  cout<<"\n\n\n\t\t\tEnter your choice ";
	  cin>>choice;
	  switch(choice)
	  {
	  case 1:{cout<<"\n\tEnter the new price ";
				      cin>>price;
				      p=infile.tellg();
				      infile.seekg(p-sizeof(f));
				      f.pes=price;
				      infile.write((char*)&f,sizeof(f));
				      break;
		  }

	    case 2:{cout<<"\n\tEnter the new price ";
				      cin>>price;

				      p=infile.tellg();
				      infile.seekg(p-sizeof(f));
				      f.pbs=price;
				      infile.write((char*)&f,sizeof(f));
				      break;
		  }


	    case 3:{cout<<"\n\tEnter the date to be rescheduled: ";
				      cin>>d7.d>>d7.m>>d7.y;
		    cout<<"\n\tEnter the new date: ";
				      cin>>d8.d>>d8.m>>d8.y;
				      fstream infile1;
				      infile1.open("schedule.dat",ios::in|ios::out|ios::binary);
				      infile1.read((char*)&s,sizeof(s));
				      while (!infile1.eof())
				      {
				      if((strcmp(s.fl_no,fl_no1)==0)&&
				      (d7.d==s.d1.d)&&(d7.m==s.d1.m)&&(d7.y==s.d1.y))
				      {p=infile1.tellg();
				      infile1.seekg(p-sizeof(s));
				      s.d1.d=d8.d;
				      s.d1.m=d8.m;
				      s.d1.y=d8.y;
				      infile1.write((char*)&s,sizeof(s));
				      }
				      infile1.read((char*)&s,sizeof(s));
				      }
				    infile1.close();
				    infile1.open("reserve.dat",ios::in|ios::out|ios::ate|ios::binary);
				      infile1.read((char*)&r,sizeof(r));
				      while (!infile1.eof())
				      {
				      if((strcmp(r.fl_no,fl_no1)==0)&&
				      (d7.d==r.d2.d)&&(d7.m==r.d2.m)&&(d7.y==r.d2.y))
				      {p=infile1.tellg();
				      infile1.seekg(p-sizeof(r));
				      r.d2.d=d8.d;
				      r.d2.m=d8.m;
				      r.d2.y=d8.y;
				      infile1.write((char*)&r,sizeof(r));
				      }
				      infile1.read((char*)&r,sizeof(r));
				      }
				     infile1.close();
				    }
				    break;
		case 4:break;
		default : {cout<<"\n\t\t\tInvalid Choice";
			   getch();
}                         }
}
while(choice!=4);
}
infile.read((char*)&f,sizeof(f));
}
if(flag==0)
{
cout<<"\nSuch a flight number does not exists";
getch();
}
}

//=============================================================================

void title()                 //Function to display the header in each page
{textcolor(12);
cprintf("\n                                EMIRATES TRAVELS");
cout<<"\n";
cprintf("\n         AIRLINE RESERVATION SYSTEM-SALMIYA, P.O BOX No.15269");
gotoxy(1,5);
for(int i=0;i<40;++i)
cout<<"*~";
}


void flights::display_menu()
{int ch=0;
char fno[20];
		   do
		   {clrscr();
		   title();
		   cout<<"\n\n\n\t\t\t\t Menu";
		   cout<<"\n\t\t\t\t------- ----";
		   cout<<"\n\n\t\t\t1.All Flight Details ";
		   cout<<"\n\t\t\t2.Particular Flight Detail";
		   cout<<"\n\t\t\t3.Return to Main Menu";
		   cout<<"\n\n\t\t\tEnter your choice ";
		   cin>>ch;
		   switch(ch)
		   {case 1:{clrscr();
			    display();
			    break;}
		    case 2:{clrscr();title();
			    cout<<"\n\nEnter the flight number ";
			    cin>>fno;
			    strupr(fno);
			    search_flight(fno);
			    break;}
		    case 3:break;

		   default:{cout<<"\n\t\t\tInvalid choice";
			    getch();}
		   }
		   }
		   while (ch!=3);

}

//=============================================================================

void main()                        //main program
{
textcolor(12);
int choice=0;
intro();
do
{         clrscr();
	  border();
	  textcolor(11);
	  gotoxy(35,2);
	  cprintf(" EMIRATES TRAVELS");
	  gotoxy(15,3);
	  cprintf("AIRLINE RESERVATION SYSTEM-SALMIYA, P.O BOX No.15269");
	  gotoxy(39,6);
	  cprintf("Menu");
	  gotoxy(39,7);
	  cprintf("----");
	  gotoxy(30,9);
	  cprintf("1.Add flight details");
	  gotoxy(30,10);
	  cprintf("2.Add flight schedules");
	  gotoxy(30,11);
	  cprintf("3.Display flight details");
	  gotoxy(30,12);
	  cprintf("4.Modify flight details");
	  gotoxy(30,13);
	  cprintf("5.Booking of seats");
	  gotoxy(30,14);
	  cprintf("6.Cancelation of seats");
	  gotoxy(30,15);
	  cprintf("7.Display reservation chart");
	  gotoxy(30,16);
	  cprintf("8.Exit");
	  gotoxy(30,19);
	  cprintf("Enter your choice ");
	  gotoxy(48,19);
	  cin>>choice;
	  switch(choice)
	  {case 1:{ f.add_flight();
		   break;}
	   case 2:{f.add_schedule();
		   break;}
	   case 3:{f.display_menu();
		   break;}
	   case 4:{f.modify();
		   break;}
	   case 5:{f.booking();
		   break;}
	   case 6:{f.cancel();
		   break;}
	   case 7:{f.display_chart();
		   break;}
	   case 8:clrscr();
	 title();
	 gotoxy(20,13);
	 cout<<"Thank you for using this software";
    getch();
    exit(0);  ;

	   default:{ textcolor(11);
		     gotoxy(30,21);
		     cprintf("Invalid choice");
		     getch();
		   }

	   }
}while(choice!=8);
}


#include<iostream>
#include<fstream>
using namespace std;
class players
{
	int playerNo;
	char playerName[50];
	int jersey;
	int matches;
	int runs;
	int four;
	int six;
	int halfCentury;
	int century;
	float strikeRate;
	public:
		void input()
		{
			cout<<"Enter the player no\n";
			cin>>playerNo;
			cout<<"Enter the player name\n";
			cin.ignore();
			cin.getline(playerName,50);
			cout<<"Enter the jersey no\n";
			cin>>jersey;
			cout<<"Enter the total number of matches\n";
			cin>>matches;
			cout<<"Enter the total runs\n";
			cin>>runs;
			cout<<"Enter the number of fours\n";
			cin>>four;
			cout<<"Enter the no of six\n";
			cin>>six;
			cout<<"Enter the number of half century\n";
			cin>>halfCentury;
			cout<<"Enter the number of century\n";
			cin>>century;
			cout<<"Enter the strike rate\n";
			cin>>strikeRate;
		}
		void show()
		{
			cout<<"\t\tPlayer Profile\n";
			cout<<"\nPlayer Number  : "<<playerNo<<endl;
			cout<<"\nPlayer Name  : "<<playerName<<endl;
			cout<<"\nJersey Number  : "<<jersey<<endl;
			cout<<"\nTotal Matches  : "<<matches<<endl;
			cout<<"\nTotal Runs  : "<<runs<<endl;
			cout<<"\nTotal Fours  : "<<four<<endl;
			cout<<"\nTotal Sixes  : "<<six<<endl;
			cout<<"\nHalf Centuries  : "<<playerNo<<endl;
			cout<<"\nCenturies  : "<<playerNo<<endl;
			cout<<"\nStrike Rate  : "<<strikeRate<<endl<<endl;
		}
		int rt_playerNo() { return playerNo;		}	
};
void menu()
{
	system("CLS");
	cout<<"			*****************************\n";
	cout<<"			* Welcome to the IPL	 *\n";
	cout<<"			*****************************\n";
	cout<<"Please enter the followig option to operate:\n";
	cout<<"Press 1: to display all teams\n";
	cout<<"Press 2: to add new player\n";
	cout<<"Press 3: to display all players\n";
	cout<<"Press 4: to search a particular player\n";
	cout<<"Press 5: to modify a particular player\n";
	cout<<"Press 6: to delete a player\n";
	cout<<"Press 7: to display team owner names\n";
	cout<<"Press 8: to display stadium names\n";
	cout<<"Press 9: to print the schedule of matches\n";
	cout<<"Press 0: to EXIT\n";
}
fstream file;

int main()
{
	players obj;
	int choice;
	while(1)
	{
		menu();
		cin>>choice;
			switch(choice)
			{
				case 1: 
					{
						system("CLS");
						ifstream obj;
						obj.open("teamNames.txt");
						char ch[1000];
						while(obj.eof()==0){
							obj.getline(ch,1000);
							cout<<ch<<endl;
						}
						obj.close();
						system("pause");
					break;
					}
				case 2: 
					{
						system("CLS");
						obj.input();
						file.open("player",ios::out | ios::app | ios::binary);
						file.write((char*) &obj, sizeof(obj));
						file.close();
						system("CLS");
						cout<<"The following data saved succesfully\n";
						obj.show();
						system("pause");	
					break;	
					}
				case 3: 
					{
						system("CLS");
						file.open("player",ios::in | ios::binary);
						while (file.read((char*) &obj,sizeof(obj)))
						{
							obj.show();
						}
						file.close();
						system("pause");
					break;						
					}
				case 4:
					{
						int k;
						system("CLS");
						cout<<"Enter the player no you want to search: ";
						cin>>k;
						file.open("player",ios::in | ios::binary);
						int flag=0;
						while (file.read((char*) &obj,sizeof(obj)))
						{
							if(obj.rt_playerNo()==k)
							{
							obj.show();
							break;
							}
							else
							flag=1;
						}
						file.close();						
						if(flag==1) cout<<"Sorry player not found....\n";
						system("pause");
					break;	
					}				
				case 5: 
					{
						int k;
						system("CLS");
						cout<<"Enter the player no you want to modify/Edit: ";
						cin>>k;
						file.open("player",ios::in | ios::out | ios::binary);
						int flag=0; char ch;
						while (file.read((char*) &obj,sizeof(obj)))
						{
							if(obj.rt_playerNo()==k)
							{
							//obj.show();
							flag=0;
							break;
							}
							else
							flag=1;
						}
						if(flag==0)
						{
							cout<<"Player found with following details\n";
							obj.show();
							cout<<"Do you want to still edit y/n :";
							cin>>ch;
							if(ch=='y' || ch=='Y')
							{
							file.seekp(-1*sizeof(obj),ios::cur);
							obj.input();
							file.write((char*) &obj, sizeof(obj));
							}
						}
						else cout<<"Sorry player not found....\n";
						system("pause");
					break;							
					}
				case 6:
					{
						int k;
						system("CLS");
						cout<<"Enter the player no you want to delete: ";
						cin>>k;
						file.open("player",ios::in | ios::binary);
						int flag=0;
						while (file.read((char*) &obj,sizeof(obj)))
						{
							if(obj.rt_playerNo()==k)
							{
							flag=0; 
							break;
							}
							else
							flag=1;  
						}
						ofstream tfile("databkp");						 
						if(flag==0)
							{
								file.seekg(0);
								while (file.read((char*) &obj,sizeof(obj)))
								{
									if(obj.rt_playerNo()!=k)
									{
										tfile.write((char*)&obj,sizeof(obj));
									}
								}							
							} 
						else cout<<"player not found...\n";
					file.close();
					tfile.close();
					remove("player");
					rename("databkp","player");	
					cout<<"Player deleted succesfully...\n";
					system("pause");
					break;
					}
				case 7:
					{
						system("CLS");
						ifstream obj;
						obj.open("teamDetails.txt");
						char ch[1000];
						while(obj.eof()==0){
							obj.getline(ch,1000);
							cout<<ch<<endl;
						}
						obj.close();
						system("pause");	
					break;	
					}
				case 8:
					{
						system("CLS");
						ifstream obj;
						obj.open("StadiumNames.txt");
						char ch[1000];
						while(obj.eof()==0){
							obj.getline(ch,1000);
							cout<<ch<<endl;
						}
						obj.close();
						system("pause");
						break;
					}
				case 9:
					{	system("CLS");
						int a;
						cout<<"Enter the number of teams : ";
						cin>>a;
						int n;
						if(a%2==0){
							n=a;
						}else{
							n=a+1;
						}
						int team[n];
						for(int i=1;i<=n;i++){
							team[i]=i;
						}
						int z=1;
						int d=n;
						int m=1;
						while(d>1){
							/*
							for(int i=1;i<=n;i++){
							cout<<team[i]<<" ";
							}*/
							for(int i=1,j=n;i<=n/2;i++,j--){
								cout<<"Match "<<m<<" "<<"Team No "<<team[i]<<" Vs "<<"Team No "<<team[j]<<endl;
								m++;
							}
							for(int i=1,j=n;i<=n/2;i++,j--){
								cout<<"Match "<<m<<" "<<"Team No "<<team[j]<<" Vs "<<"Team No "<<team[i]<<endl;
								m++;
							}
							
							for(int i=n;i>=3;i--){
								int temp=team[i];
								team[i]=team[i-1];
								team[i-1]=temp;
							}
							d--;
						}
						system("pause");
						break;
										}
				case 0:
					{
						system("CLS");
						exit (0); 
						break;
					}
				default:
				cout<<"Pease enter the valid option\n";			
			}
		
	}
	return 0;
}

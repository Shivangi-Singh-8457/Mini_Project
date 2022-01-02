#include <iostream>
#include<bits/stdc++.h>
#include<limits>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>
using namespace std;

class items;
class cart;
class users;

void display_list(int);
void display_type();
int check(users,int);
void signup();
void signin();
//int check_signin(string,string);
void contactus();
void change_home();
void home();
void signout();
int gst(items);
int discount(items);
float buy_price(items,int,int);

bool login_flag=false;

class users{
 public:
     char name[30];
     char address[50];
     long long int mobile;
     char username[15];
     char email[30];
     char password[15];
}*user;

class items{
    public:
     int id;
     char name[30];
     float price;
}*item;
class cart{
};

int gst(items *item)
{
    if(item->price>500)
        return 18;
    else
        return 0;
}
int discount(items *item)
{
    if(item->price<=500)
        return 10;
    else if(item->price<=1000)
        return 20;
    else
        return 30;
}
float buy_price(items *item,int d,int g)
{
    float buy;
    buy=item->price-(item->price*d/100);
    buy=buy+(buy*g/100);
    return buy;
}

void display_list(int n)
{
    int G,D; float B;
    char ch[2];
    ifstream fp;
    switch(n)
    {
        case 101:fp.open("men_clothing.txt");
                 if(!fp)
                 cout<<"file not found";break;
        case 102:fp.open("men_footwear.txt");
                 if(!fp)
                 cout<<"file not found";break;
        case 103:fp.open("women_clothing.txt");
                 if(!fp)
                 cout<<"file not found";break;
        case 104:fp.open("women_footwear.txt");
                 if(!fp)
                 cout<<"file not found";break;
        case 105:fp.open("women_accessories.txt");
                 if(!fp)
                 cout<<"file not found";break;
    }
    items temp;
    cout<<"--------------------------------------------------------------------------"<<endl;
    cout<<"|"<<"Id\t"<<"Name\t"<<"MRP\t"<<"Discount\t"<<"GST\t"<<"Buy Price"<<" |"<<endl;
    cout<<"--------------------------------------------------------------------------"<<endl;
    while(!fp.eof())
    {
        fp>>temp.id;
        fp.getline(ch,2);
        fp.getline(temp.name,30);
        fp>>temp.price;
        fp.getline(ch,2);
        item=&temp;
        G=gst(item);
        D=discount(item);
        B=buy_price(item,D,G);
        cout<<"|"<<item->id<<"\t"<<item->name<<"\t"<<item->price<<"\t"<<D<<"%\t"<<"\t"<<G<<"%"<<"\t"<<"Rs. "<<fixed<<setprecision(2)<<B<<"|"<<endl;
    }
    cout<<"--------------------------------------------------------------------------"<<endl;

}

void display_type()
{
    int opt;
               cout<<"-------------------"<<endl;
               cout<<"-------------------"<<endl;
               cout<<"||    1.Men      ||"<<endl;
               cout<<"||    2.Women    ||"<<endl;
               cout<<"||    3.Exit     ||"<<endl;
               cout<<"-------------------"<<endl;
               cout<<"-------------------"<<endl;
    cout<<"Enter option:";
    cin>>opt;
    switch(opt)
    {
        case 1:cout<<"-------------------"<<endl;
               cout<<"||      MEN      ||"<<endl;
               cout<<"-------------------"<<endl;
               cout<<"||   1.Clothing  ||"<<endl;
               cout<<"||   2.Footwear  ||"<<endl;
               cout<<"-------------------"<<endl;
               cout<<"-------------------"<<endl;
               cout<<"Enter option:";
               cin>>opt;
               switch(opt)
               {
                   case 1:display_list(101);break;
                   case 2:display_list(102);break;
                   case 3:exit(0);
                   default:cout<<"Please choose one from the above options.";
               }
               break;

       case 2:cout<<"1.Clothing\n"<<"2.Footwear\n"<<"3.Accessories\n"<<"4.Exit\n";
              cout<<"Enter option:";
              cin>>opt;
              switch(opt)
               {
                   case 1:display_list(103);break;
                   case 2:display_list(104);break;
                   case 3:display_list(105);break;
                   case 4:exit(0);
                   default:cout<<"Please choose one from the above options.";
               }
               break;
      case 3:exit(0);
      default:cout<<"Please choose one from the above options.";
    }
}

int check(users *user, int n)
{
   char name[30],add[50],un[15],email[30],pwd[15],ch[2];
   long long int mob;
    ifstream fp("users.txt");
    if(!fp)
   cout<<"file not found\n";
   else
    {
     while(!fp.eof())
      {
         fp.getline(name,30);
         cout<<name<<endl;
         fp.getline(add,50);
         cout<<add<<endl;
         fp>>mob;
         cout<<mob<<endl;
         fp.getline(ch,2);
         fp.getline(un,15);
         cout<<un<<endl;
         fp.getline(email,30);
         cout<<email<<endl;
         fp.getline(pwd,15);
         cout<<pwd<<endl;
         fp.getline(ch,2);
         if(n==1)
    {if(strcmp(user->username,un)==0)
            return 1;
     else
        return 0;
    }
    if(n==2)
    {
        if(strcmp(user->username,un)==0 && strcmp(user->password,pwd)==0)
           return 0;
        else
            {cout<<"Wrong username and password\n";
                 return 1;
            }
    }

     }
    }
      fp.close();
      return 0;
}
void signup()
{

   ofstream fp("users.txt",ios::app);
   if(!fp)
   cout<<"cannot open file\n";
   else
   {
       users temp;
      cout<<"Name:";
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
      cin.getline(temp.name,30);
      cout<<"Address:";
      cin.getline(temp.address,50);
      cout<<"Mobile No.:";
      cin>>temp.mobile;
      cout<<"Username:";
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
      cin.getline(temp.username,15);
      user=&temp;
      while(check(user,1))
      {
          cout<<"\nUsername already exists\nenter another username:";
          cin.getline(temp.username,15);
      }
      cout<<"Email Id:";
      cin.getline(temp.email,30);
      cout<<"Password:";
      cin.getline(temp.password,15);
      fp<<user->name<<"\n"<<user->address<<"\n"<<user->mobile<<"\n"<<user->username<<"\n"<<user->email<<"\n"<<user->password<<"\n\n";
      cout<<"You are registered successfully";
      fp.close();
   }
}

void signin()
{
    users temp;
        cout<<"Enter Username:";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin.getline(temp.username,15);
        cout<<"Enter Password:";
        cin.getline(temp.password,15);
        user=&temp;
    while(check(user,2))
    {
        cout<<"Enter Username:";
        cin.getline(temp.username,15);
        cout<<"Enter Password:";
        cin.getline(temp.password,15);
    }
   login_flag=true;
   cout<<"Logged in successfully";
   change_home();
}

void contactus()
{
    cout<<"----------------------------"<<endl;
    cout<<"||      Contact Us        ||"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"||  Email: xyz@gmail.com  ||"<<endl;
    cout<<"||  Phone No.: 9123458760 ||"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"----------------------------"<<endl;
}
void home()
{
    system("cls");
    int opt;
    char ch;
  do{
    cout<<"----------------------------"<<endl;
    cout<<"||        WELCOME         ||"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"||    1.Display Items     ||"<<endl;
    cout<<"||    2.Sign Up           ||"<<endl;
    cout<<"||    3.Sign In           ||"<<endl;
    cout<<"||    4.Contact Us        ||"<<endl;
    cout<<"||    5.Exit              ||"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"Enter option:";
    cin>>opt;
    switch(opt)
    {
        case 1:display_type();break;
        case 2:signup(); break;
        case 3:signin(); break;
        case 5:exit(0);
        default:cout<<"Please choose one from the above options.";
    }
    cout<<"\nDo you want to choose another option[y/n]:";
    cin>>ch;
    }while(ch=='y'||ch=='Y');
}
void change_home()
{
    system("cls");
    int opt;
    char ch;
    do{
    cout<<"----------------------------"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"||    1.Display Items     ||"<<endl;
    cout<<"||    2.Sign out          ||"<<endl;
    cout<<"||    3.Contact Us        ||"<<endl;
    cout<<"||    4.Exit              ||"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"Enter option:";
    cin>>opt;
    switch(opt)
    {
        case 1:display_type();break;
        case 2:signout(); break;
        case 3:contactus();break;
        case 4:exit(0);
        default:cout<<"Please choose one from the above options.";
    }
    cout<<"\nDo you want to choose another option[y/n]:";
    cin>>ch;
    }while(ch=='y'||ch=='Y');
}

int main()
{
    home();
    return 0;
}
void signout()
{
    login_flag=false;
    main();
}

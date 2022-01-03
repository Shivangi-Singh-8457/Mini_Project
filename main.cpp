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
void add_item(items);
void display_cart();
void remove_item(cart);
void contactus();
void change_home();
void home();
void signout();
int gst(items);
int discount(items);
float buy_price(items,int,int);

bool login_flag=false;
char currentuser[15];
char cartname[20];

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
   public:
       int id;
       char name[30];
       float price;
 }*order;

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
/*--------Add item in Cart--------*/
void add_item(items *item)
{
   fstream fp;
   fp.open(cartname,ios::app);
   if(!fp)
   cout<<"cannot open file\n";
   else
   {
       fp<<item->id<<"\n"<<item->name<<"\n"<<buy_price(item,discount(item),gst(item))<<"\n\n";
       cout<<"Item added in your cart"<<endl;
   }
}
/*--------Remove item from Cart--------*/
void remove_item(cart *order)
{
   cart temp; char ch[2];
   ifstream fp(cartname);
   ofstream fp1("new_cart.txt",ios::app);
   while(1)
   {
       fp>>temp.id;
       fp.getline(ch,2);
       fp.getline(temp.name,30);
       fp>>temp.price;
       fp.getline(ch,2);
       if(fp.eof())
           break;
       if(temp.id != order->id)
       fp1<<temp.id<<"\n"<<temp.name<<"\n"<<temp.price<<"\n\n";
   }
   fp.close();
   fp1.close();
   remove(cartname);
   rename("new_cart.txt",cartname);
}
/*--------Display Cart--------*/
void display_cart()
{
    cart temp;
    float total=0; char ch[2];
    ifstream fp(cartname);
    if(!fp)
        cout<<"Cart is empty";
    else
        {
            cout<<"----------------------"<<endl;
            cout<<"||      Orders      ||"<<endl;
            cout<<"----------------------"<<endl;
            cout<<"|| Id\tName\tPrice ||"<<endl;
            while(1)
            {
                   fp>>temp.id;
                   fp.getline(ch,2);
                   fp.getline(temp.name,30);
                   fp>>temp.price;
                   fp.getline(ch,2);
                   if(fp.eof())
                        break;
                   order=&temp;
                   total+=order->price;
                   cout<<"|| "<<order->id<<"\t"<<order->name<<"\t"<<order->price<<" ||"<<endl;
            }
            char c;
            cout<<"Total Bill: Rs."<<total<<endl;
            fp.close();
            cout<<"\nDo you want to delete any item[y/n]:";
            cin>>c;
            int id;
            if(c=='y'||c=='Y')
              {
              do{
                fp.open(cartname,ios::in);
                cout<<"Enter the id of the item:";
                cin>>id;
                 while(1)
                {
                   fp>>temp.id;
                   fp.getline(ch,2);
                   fp.getline(temp.name,30);
                   fp>>temp.price;
                   fp.getline(ch,2);
                   if(fp.eof())
                        break;
                   order=&temp;
                    if(order->id==id)
                     {
                        fp.close();
                        break;
                     }
                 }
                remove_item(order);
              cout<<"\nDo you want to delete more item[y/n]:";
              cin>>c;
              }while(c=='y'||c=='Y');
            }

        }
}

void select_file(char file[30],int n)
{

  switch(n)
    {
        case 101:strcpy(file,"men_clothing.txt");
                    break;
        case 102:strcpy(file,"men_footwear.txt");break;
        case 103:strcpy(file,"women_clothing.txt");break;
        case 104:strcpy(file,"women_footwear.txt");break;
        case 105:strcpy(file,"women_accessories.txt");break;
    }

}

void display_list(int n)
{
    int G,D; float B;
    char ch[2];
    ifstream fp;
    char file[30];
    select_file(file,n);
    fp.open(file,ios::in);
    items temp;
    char c; int id;
    cout<<"--------------------------------------------------------------------------"<<endl;
    cout<<"|"<<"Id\t"<<"Name\t"<<"MRP\t"<<"Discount\t"<<"GST\t"<<"Buy Price"<<" |"<<endl;
    cout<<"--------------------------------------------------------------------------"<<endl;
    while(1)
    {
        fp>>temp.id;
        fp.getline(ch,2);
        fp.getline(temp.name,30);
        fp>>temp.price;
        fp.getline(ch,2);
        if(fp.eof())
            break;
        item=&temp;
        G=gst(item);
        D=discount(item);
        B=buy_price(item,D,G);
        cout<<"|"<<item->id<<"\t"<<item->name<<"\t"<<item->price<<"\t"<<D<<"%\t"<<"\t"<<G<<"%"<<"\t"<<"Rs. "<<fixed<<setprecision(2)<<B<<"|"<<endl;

    }
    cout<<"--------------------------------------------------------------------------"<<endl;
    cout<<"Do you want to add items in your cart[y/n]:";
    cin>>c;
    fp.close();
    if(c=='y'||c=='Y')
    {
        if(login_flag)
        {

            do{
            cout<<"\nEnter the id of the item:";
            cin>>id;
            fp.open(file,ios::in);
            while(!fp.eof())
             {
                 fp>>temp.id;
                 fp.getline(ch,2);
                 fp.getline(temp.name,30);
                 fp>>temp.price;
                 fp.getline(ch,2);
                 item=&temp;
                  if(item->id==id)
                    {
                        fp.close();
                        add_item(item);
                        break;
                    }
             }

            cout<<"Do you want to add another item[y/n]:";
            cin>>c;
            }while(c=='y'||c=='Y');
       }
        else
          cout<<"Sign in first to add item in your cart";
    }

}
/*--------Display items list--------*/
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

       case 2: cout<<"----------------------"<<endl;
               cout<<"||      WOMEN       ||"<<endl;
               cout<<"----------------------"<<endl;
               cout<<"||   1.Clothing     ||"<<endl;
               cout<<"||   2.Footwear     ||"<<endl;
               cout<<"||   3.Accessories  ||"<<endl;
               cout<<"----------------------"<<endl;
               cout<<"----------------------"<<endl;
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
/*--------To check user already exists or not--------*/
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
/*--------Sign up function--------*/
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
/*--------Sign in function--------*/
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
   strcpy(currentuser,temp.username);
   strcpy(cartname,currentuser);
   strcat(cartname,".txt");
   cout<<"Logged in successfully";
   change_home();
}
/*--------Contact Us--------*/
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
/*--------Home page--------*/
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
/*--------After Sign in--------*/
void change_home()
{
    system("cls");
    cout<<cartname<<endl;
    int opt;
    char ch;
    do{
    cout<<"----------------------------"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"||    1.Display Items     ||"<<endl;
    cout<<"||    2.Cart              ||"<<endl;
    cout<<"||    3.Sign out          ||"<<endl;
    cout<<"||    4.Contact Us        ||"<<endl;
    cout<<"||    5.Exit              ||"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"Enter option:";
    cin>>opt;
    switch(opt)
    {
        case 1:display_type();break;
        case 2:display_cart();break;
        case 3:signout(); break;
        case 4:contactus();break;
        case 5:exit(0);
        default:cout<<"Please choose one from the above options.";
    }
    cout<<"\nDo you want to choose another option[y/n]:";
    cin>>ch;
    }while(ch=='y'||ch=='Y');
}
/*--------Main--------*/
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

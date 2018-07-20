//***************************************************************
//                           HEADER FILE USED IN PROJECT
//****************************************************************
#include<fstream>
#include<iostream>
#include<stdio.h>
#include <cstdlib>
#include<cstring>
#include<iomanip>
using namespace std;
int check_bookno(char[]);
int check_admno(char[]);
//***************************************************************
//                                 CLASS USED IN PROJECT
//****************************************************************
void wait(){
    cin.get();
}
class book
{
    char bno[6];
    char bname[50];
    char aname[20];
    public:
    void create_book()
    {
        int r=1;
        cout<<"\n\tNEW BOOK ENTRY...\n";
        while(r)
        {
            cout<<"\n\tEnter The book no.: ";
            cin>>bno;
            r=check_bookno(bno);
        }
        cout<<"\n\n\tEnter The Name of The Book: ";
        cin.get();
        cin.getline(bname,50);
        cout<<"\n\n\tEnter The Author's Name: ";
        cin.getline(aname,20);;
        cout<<"\n\n\n\tBook Created..";
    }
    void show_book()
    {
        cout<<"\n\tBook no.  :  "<<bno;
        cout<<"\n\tBook Name :  ";
        puts(bname);
        cout<<"\tAuthor Name :  ";
        puts(aname);
    }
    void modify_book()
    {
        cout<<"\n\tBook no. : "<<bno;
        cout<<"\n\tModify Book Name : ";
        cin.getline(bname,50);
        cout<<"\n\tModify Author's Name of Book : ";
        cin.getline(aname,20);
    }
    char* retbno()
    {
        return bno;
    }
    void report()
    {
        cout<<setw(8)<<bno<<setw(34);
        cout<<bname<<setw(26)<<aname<<endl;
    }
};         //class ends here

bool icompare_pred(unsigned char a, unsigned char b)
{
    return std::tolower(a) == std::tolower(b);
}

bool strcmpi(std::string const& a, std::string const& b)
{
    if (a.length()==b.length()) {
        return std::equal(b.begin(), b.end(),
                          a.begin(), icompare_pred);
    }
    else {
        return false;
    }
}
class student
{
    char admno[6];
    char name[20];
    char stbno[6];
    int token;
    public:
    void create_student()
    {
        system("clear");
        int r=1;
        cout<<"\n\tNEW STUDENT ENTRY...\n";
        while(r)
        {
            cout<<"\n\tEnter The admission no.: ";
            cin>>admno;
            r=check_admno(admno);
        }
        
        cout<<"\n\n\tEnter The Name of The Student: ";
        cin.get();
        cin.getline(name,20);
        token=0;
        stbno[0]=0;
        cout<<"\n\n\tStudent Record Created..";
    }
    
    void show_student()
    {
        cout<<"\n\tAdmission no. : "<<admno;
        cout<<"\n\tStudent Name : "<<name;
        cout<<"\n\tNo of Book issued : "<<token;
        if(token==1)
        cout<<"\n\tBook No: "<<stbno;
    }
    void modify_student()
    {
        cout<<"\n\n\tAdmission no. : "<<admno;
        cout<<"\n\tModify Student Name : ";
        cin.get();
        cin.getline(name,20);
    }
    
    char* retadmno()
    {
        return admno;
    }
    char* retstbno()
    {
        return stbno;
    }
    int rettoken()
    {
        return token;
    }
    void addtoken()
    {
        token=1;
    }
    void resettoken()
    {
        token=0;
    }
    void getstbno(char t[])
    {
        strcpy(stbno,t);
    }
    void report()
    {
        cout<<setw(14)<<admno<<setw(19);
        cout<<name<<setw(13)<<token<<endl;
    }
};         //class ends here

//***************************************************************
//                global declaration for stream object, object
//****************************************************************

fstream fp,fp1;
book bk;

student st;
//***************************************************************
//                               function to write in file
//****************************************************************

void write_book()
{
    char ch;
    fp.open("book.dat",ios::out|ios::app);
    do
    {
        system("clear");
        bk.create_book();
        fp.write((char*)&bk,sizeof(book));
        cout<<"\n\n\tDo you want to add more record..(y/n?) ";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}
void write_student()
{
    char ch;
    fp.open("student.dat",ios::out|ios::app);
    do
    {
        st.create_student();
        fp.write((char*)&st,sizeof(student));
        cout<<"\n\n\tdo you want to add more record..(y/n?) ";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}
int check_admno(char admno[6])
{
    student st1;
    fstream file;
    file.open("student.dat",ios::in|ios::out);
    file.seekg(0,ios::beg);
    while(file.read((char*)&st1,sizeof(student)))
    {
        if(strcmpi(st1.retadmno(),admno)==1)
        {
            cout<<"\tAdmno exist, Please enter another Admno  ";
            file.close();
            return 1;
        }
    }
    
    file.close();
    return 0;
}

int check_bookno(char bookno[6])
{
    book bk1;
    fstream file;
    file.open("book.dat",ios::in|ios::out);
    file.seekg(0,ios::beg);
    while(file.read((char*)&bk1,sizeof(book)))
    {
        if(strcmpi(bk1.retbno(),bookno)==1)
        {
            cout<<"\tbookno exist, Please enter another bookno  ";
            file.close();
            return (1);
        }
    }
    
    file.close();
    return 0;
}

//***************************************************************
//                  function to read specific record from file
//****************************************************************

void display_spb(char n[])
{
    cout<<"\n\tBOOK DETAILS\n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n)==1)
        {
            bk.show_book();
            flag=1;
        }
    }
    fp.close();
    if(flag==0)
    cout<<"\n\n\tBook does not exist";
    
    cin.get();
    wait();
}

void display_sps(char n[])
{
    cout<<"\n\tSTUDENT DETAILS\n";
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if((strcmpi(st.retadmno(),n)==1))
        {
            st.show_student();
            flag=1;
        }
    }
    fp.close();
    if(flag==0)
    cout<<"\n\n\tStudent does not exist";
    
    cin.get();
    wait();
}

//***************************************************************
//                         function to modify record of file
//****************************************************************

void modify_book()
{
    char n[6];
    int found=0;
    system("clear");
    cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
    cout<<"\n\n\tEnter The book no. of The book:  ";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&bk,sizeof(book)) && found==0)
    {
        if(strcmpi(bk.retbno(),n)==1)
        {
            bk.show_book();
            cout<<"\n\tEnter The New Details of book: "<<endl;
            bk.modify_book();
            int pos= -1 * int(sizeof(book));
            fp.seekp(pos,ios::cur);
            fp.write((char*)&bk,sizeof(book));
            cout<<"\n\n\tRecord Updated";
            found=1;
        }
    }
    fp.close();
    if(found==0)
        cout<<"\n\n\tRecord Not Found ";
    
    cin.get();
    wait();
}
void modify_student()
{
    char n[6];
    int found=0;
    system("clear");
    cout<<"\n\n\tMODIFY STUDENT RECORD... ";
    cout<<"\n\n\tEnter The admission no. of The student:  ";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out|ios::ate|ios::binary);
    fp.seekg(0);
    fp.read((char*)&st,sizeof(student));
    
    while(!fp.eof() && found==0)
    {
        if(strcmpi(st.retadmno(),n)==1)
        {
            st.show_student();
            cout<<"\n\n\tEnter The New Details of student: "<<endl;
            st.modify_student();
            long pos = fp.tellp();
            fp.seekp(pos-sizeof(student));
            fp.write((char*)&st,sizeof(student));
            cout<<"\n\n\tRecord Updated";
            found=1;
        }
        fp.read((char*)&st,sizeof(student));
    }
    fp.close();
    if(found==0)
        cout<<"\n\n\tRecord Not Found ";
    
    cin.get();
    wait();
}

//***************************************************************
//                           function to delete record of file
//****************************************************************

void delete_student()
{
    char n[6];
    int flag=0;
    system("clear");
    cout<<"\n\n\n\tDELETE STUDENT...";
    cout<<"\n\n\tEnter The admission no. of the Student You Want To Delete ";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if(strcmpi(st.retadmno(),n)!=1)
        fp2.write((char*)&st,sizeof(student));
        else
        flag=1;
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    if(flag==1)
    cout<<"\n\n\tRecord Deleted ..";
    else
    cout<<"\n\n\tRecord not found";
    cin.get();
    wait();
}
void delete_book()
{
    int found = 0;
    char n[6];
    system("clear");
    cout<<"\n\n\n\tDELETE BOOK ...";
    cout<<"\n\n\tEnter The Book no. of the Book You Want To Delete : ";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n)!=1)
        {
            fp2.write((char*)&bk,sizeof(book));
        }else{
            found=1;
        }
    }
    fp2.close();
    fp.close();
    remove("book.dat");
    rename("Temp.dat","book.dat");
    if(found==1)
        cout<<"\n\n\tRecord Deleted ..";
    else{
        cout<<"\n\n\tRecord Not Found !! ..";
    }
    cin.get();
    wait();
}

//***************************************************************
//                      function to display all students list
//****************************************************************
void display_alls()
{
    system("clear");
    fp.open("student.dat",ios::in);
    if(!fp)
    {
        cout<<"\tERROR!!! FILE COULD NOT BE OPEN ";
        cin.get(); wait();
        return;
    }
    cout<<"\n\n\t\tSTUDENT LIST\n\n";
    
    cout<<"============================================================\n";
    cout<<"\tAdmission No."<<setw(11)<<"Name"<<setw(20)<<"Book Issued\n";
    cout<<"============================================================\n";
    
    while(fp.read((char*)&st,sizeof(student)))
    {
        st.report();
    }
    fp.close();
    cin.get();
    wait();
}

//***************************************************************
//                                function to display Books list
//****************************************************************

void display_allb()
{
    system("clear");
    fp.open("book.dat",ios::in);
    if(!fp)
    {
        cout<<"\tERROR!!! FILE COULD NOT BE OPEN ";
        cin.get(); wait();
        return;
    }
    cout<<"\n\n\t\t\t\tBook LIST\n\n";
    cout<<"==================================================================\n";
    cout<<"  "<<"Book Number"<<setw(30)<<"Book Name"<<setw(27)<<"Author\n";
    cout<<"==================================================================\n";
    
    while(fp.read((char*)&bk,sizeof(book)))
    {
        bk.report();
    }
    fp.close();
    cin.get();
    wait();
}

//***************************************************************
//                    function to issue book
//****************************************************************

void book_issue()
{
    char sn[6],bn[6];
    int found=0,flag=0;
    system("clear");
    cout<<"\n\n\t\tBOOK ISSUE ...";
    cout<<"\n\n\t\tEnter The student's admission no.: ";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(strcmpi(st.retadmno(),sn)==1)
        {
            found=1;
            if(st.rettoken()==0)
            {
                cout<<"\n\n\t\tEnter the book no.: ";
                cin>>bn;
                
                while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                {
                    if(strcmpi(bk.retbno(),bn)==1)
                    {
                        bk.show_book();
                        flag=1;
                        st.addtoken();
                        st.getstbno(bk.retbno());
                        int pos=-1*int(sizeof(st));
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&st,sizeof(student));
                        cout<<"\n\n\t\t Book issued successfully!!\n\nPlease Note: Write the current date in";
                        cout<<" backside of your book and submit \n\t\twithin 15 days \n\n\t\t";
                        cout<<"(fine Rs. 1 for each day after 15 days period)";
                    }
                }
                if(flag==0)
                cout<<"\n\t\tBook no. does not exist";
            }
            else
            cout<<"\n\t\tYou have not returned the last book ";
        }
    }
    if(found==0)
    cout<<"\n\n\t\tStudent record not exist !!!!!!";
    cin.get();
    wait();
    fp.close();
    fp1.close();
}
//***************************************************************
//        function to deposit book
//****************************************************************

void book_deposit()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    system("clear");
    cout<<"\n\n\tBOOK DEPOSIT ...";
    cout<<"\n\n\tEnter The student's admission no.: ";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {    if(strcmpi(st.retadmno(),sn)==1)
        {
            found=1;
            if(st.rettoken()==1)
            {
                while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                {
                    if(strcmpi(bk.retbno(),st.retstbno())==1)
                    {
                        bk.show_book();
                        flag=1;
                        cout<<"\n\n\tBook deposited in no. of days: ";
                        cin>>day;
                        if(day>15)
                        {
                            fine=(day-15)*1;
                            cout<<"\n\n\tFine has to deposited Rs.  "<<fine;
                        }
                        st.resettoken();
                        int pos=-1*int(sizeof(st));
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&st,sizeof(student));
                        cout<<"\n\tBook deposited successfully";
                    }
                }
                if(flag==0)
                cout<<"\tBook no does not exist";
            }
            else
            cout<<"\tNo book is issued..please check!!";
        }
    }
    if(found==0)
    cout<<"\tStudent record not exist !!!";
    cin.get(); wait();
    fp.close();
    fp1.close();
}
//***************************************************************
//                         INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
    system("clear");
    cout<<"\n\n\n\n\n\n\n\n\t\t\t       LIBRARY";
    cout<<"\n\n\t\t\t     MANAGEMENT";
    cout<<"\n\n\t\t\t       SYSTEM";
    cout<<"\n\n\n\n\t\t\t   MADE BY : Aditi";
    cout<<"\n\n\t\t    SCHOOL : YUVASHAKTI MODEL SCHOOL";
    wait();
}

//***************************************************************
//                    ADMINISTRATOR MENU FUNCTION
//****************************************************************

void admin_menu()
{
    system("clear");
    int ch2;
    cout<<"\n\n\n\tADMINISTRATOR MENU";
    cout<<"\n\n\t1.CREATE STUDENT RECORD";
    cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
    cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
    cout<<"\n\n\t4.MODIFY STUDENT RECORD";
    cout<<"\n\n\t5.DELETE STUDENT RECORD";
    cout<<"\n\n\t6.CREATE BOOK ";
    cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
    cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK ";
    cout<<"\n\n\t9.MODIFY BOOK ";
    cout<<"\n\n\t10.DELETE BOOK ";
    cout<<"\n\n\t11.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-11)  ";
    cin>>ch2;
    switch(ch2)
    {
        case 1: system("clear");
        write_student();break;
        case 2: display_alls();break;
        case 3:
        char num[6];
        system("clear");
        cout<<"\n\n\tPlease Enter The Admission No.: ";
        cin>>num;
        display_sps(num);
        break;
        case 4: modify_student();break;
        case 5: delete_student();break;
        case 6: system("clear");
        write_book();break;
        case 7: display_allb();break;
        case 8: {
            char num[6];
            system("clear");
            cout<<"\n\n\tPlease Enter The book No.: ";
            cin>>num;
            display_spb(num);
            break;
        }
        case 9: modify_book();break;
        case 10: delete_book();break;
        case 11: return;
        default:cout<<"\a";
    }
    admin_menu();
}

//***************************************************************
//        THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main()
{
    char ch;
    intro();
    do
    {
        system("clear");
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. BOOK ISSUE";
        cout<<"\n\n\t02. BOOK DEPOSIT";
        cout<<"\n\n\t03. ADMINISTRATOR MENU";
        cout<<"\n\n\t04. EXIT";
        cout<<"\n\n\tPlease Select Your Option (1-4) ";
        cin>>ch;
        switch(ch)
        {
            case '1':system("clear");
            book_issue();
            break;
            case '2':book_deposit();
            break;
            case '3':admin_menu();
            break;
            case '4':exit(0);
            default :cout<<"\a";
        }
    }while(ch!='4');
    return 0;
}

//***************************************************************
//                END OF PROJECT
//***************************************************************

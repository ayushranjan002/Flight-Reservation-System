#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int glob = 0;
int global = 10;

class d_booking
{
protected:
    int pnr;
    char f_d[10], toja[7], tojd[7];
    long int doj;
    int choice, src, dest;

public:
    void d_pnr()
    {
        glob++;
        pnr = glob;
    }

    int j_detail()
    {
        cout << "\nSelect your source and destination:\n";
        cout << "1. Delhi to Mumbai\n";
        cout << "2. Mumbai to Delhi\n";
        cin >> src;
        if (src < 1 || src > 2)
        {
            cout << "\nInvalid choice. Please try again.\n";
            return j_detail();
        }
        cout << "Enter date of journey (in DDMMYY format): ";
        cin >> doj;
        cout << "Select your class:\n";
        cout << "1. Economy\n";
        cout << "2. Business\n";
        cin >> choice;
        return 1;
    }

    int select_flight()
    {
        if (src == 1)
        {
            strcpy(f_d, "Delhi to Mumbai");
            if (choice == 1)
            {
                strcpy(tojd, "09:00");
                strcpy(toja, "12:00");
            }
            else
            {
                strcpy(tojd, "06:00");
                strcpy(toja, "10:00");
            }
        }
        else
        {
            strcpy(f_d, "Mumbai to Delhi");
            if (choice == 1)
            {
                strcpy(tojd, "14:00");
                strcpy(toja, "17:00");
            }
            else
            {
                strcpy(tojd, "11:00");
                strcpy(toja, "15:00");
            }
        }
        return 1;
    }
};

class i_booking
{
protected:
    int pnri;
    char f_i[10], tojai[7], tojdi[7];
    long int doji;
    int srci, desti, choicei;

public:
    void i_pnr()
    {
        global++;
        pnri = global;
    }

    int j_detaili()
    {
        cout << "\nSelect your source and destination:\n";
        cout << "1. Delhi to London\n";
        cout << "2. London to Delhi\n";
        cin >> srci;
        if (srci < 1 || srci > 2)
        {
            cout << "\nInvalid choice. Please try again.\n";
            return j_detaili();
        }
        cout << "Enter date of journey (in DDMMYY format): ";
        cin >> doji;
        cout << "Select your class:\n";
        cout << "1. Economy\n";
        cout << "2. Business\n";
        cin >> choicei;
        return 1;
    }

    int select_flighti()
    {
        if (srci == 1)
        {
            strcpy(f_i, "Delhi to London");
            if (choicei == 1)
            {
                strcpy(tojdi, "09:00");
                strcpy(tojai, "14:00");
            }
            else
            {
                strcpy(tojdi, "06:00");
                strcpy(tojai, "11:00");
            }
        }
        else
        {
            strcpy(f_i, "London to Delhi");
            if (choicei == 1)
            {
                strcpy(tojdi, "14:00");
                strcpy(tojai, "19:00");
            }
            else
            {
                strcpy(tojdi, "11:00");
                strcpy(tojai, "16:00");
            }
        }
        return 1;
    }
};

class passenger : public d_booking, public i_booking
{
protected:
    char f_name[20], l_name[20], email[50];
    int age, gender;
    long int c_no;

public:
    void p_detail(int x)
    {
        if (x == 1)
        {
            j_detail();
            select_flight();
        }
        else
        {
            j_detaili();
            select_flighti();
        }
        cout << "\n\n\nEnter passenger details";
        cout << "\nFirst Name:";
        cin >> f_name;
        cout << "Last Name:";
        cin >> l_name;
    }

    int gender_check()
    {
        cout << "\nGender:\nMale-press:1::\nFemale-press:2::";
        cin >> gender;
        if (gender > 2)
        {
            cout << "\n\nWrong input entered.\nTry again\n\n" << endl;
            return gender_check();
        }
        return 1;
    }

    void more_details()
    {
        cout << "Age:";
        cin >> age;
        cout << "Email Id:";
        cin >> email;
        cout << "Contact no.(6 digits):";
        cin >> c_no;
        cout << "\n\nDetails Entered:\n";
        cout << "Name:" << f_name << " " << l_name << endl;
        cout << "Gender:" << gender << endl;
        cout << "Age:" << age << endl;
        cout << "Email id:" << email << endl;
        cout << "Contact No.:" << c_no << endl;
    }

    int getpnr()
    {
        return pnr;
    }

    int getpnri()
    {
        return pnri;
    }

    void disp()
    {
        cout << "PNR:" << pnr << endl;
        cout << "Flight:" << f_d << endl;
        cout << "Name:" << f_name << " " << l_name << endl;
        cout << "DOJ:" << doj << endl;
        cout << "Departure Time:" << tojd << endl;
        cout << "Arrival Time:" << toja;
    }

    void dispi()
    {
        cout << "PNR:" << pnri << endl;
        cout << "Flight:" << f_i << endl;
        cout << "Name:" << f_name << " " << l_name << endl;
        cout << "DOJ:" << doji << endl;
        cout << "Departure Time:" << tojdi << endl;
        cout << "Arrival Time:" << tojai;
    }
};

class payment
{
public:
    void pay_detail()
    {
        cout << "\n\nPayment Successful (Assuming payment is successful).\n";
    }
};

void createfile(passenger p)
{
    ofstream fin("domestic.txt", ios::binary | ios::app);
    fin.write((char *)&p, sizeof(p));
    fin.close();
}

void cancelticket(int x)
{
    passenger p;
    int f = 0;
    ifstream fout("domestic.txt", ios::binary | ios::app);
    ofstream fin("domestic1.txt", ios::binary | ios::app);
    fout.read((char *)&p, sizeof(p));
    while (fout)
    {
        if (p.getpnr() != x)
        {
            fin.write((char *)&p, sizeof(p));
        }
        else
        {
            f = 1;
        }
        fout.read((char *)&p, sizeof(p));
    }
    if (f == 0)
    {
        cout << "Pnr not found" << endl;
    }
    else
    {
        cout << "Ticket cancelled\n";
    }
    fout.close();
    fin.close();
    remove("domestic.txt");
    rename("domestic1.txt", "domestic.txt");
}

void checkticket(int x)
{
    passenger p;
    int f = 0;
    ifstream fout("domestic.txt", ios::binary | ios::app);
    fout.read((char *)&p, sizeof(p));
    while (fout)
    {
        if (p.getpnr() == x)
        {
            p.disp();
            f = 1;
        }
        fout.read((char *)&p, sizeof(p));
    }
    if (f == 0)
    {
        cout << "Pnr not found" << endl;
    }
    fout.close();
}

void createfilei(passenger p)
{
    ofstream fin("international.txt", ios::binary | ios::app);
    fin.write((char *)&p, sizeof(p));
    fin.close();
}

void cancelticketi(int x)
{
    passenger p;
    int f = 0;
    ifstream fout("international.txt", ios::binary | ios::app);
    ofstream fin("international1.txt", ios::binary | ios::app);
    fout.read((char *)&p, sizeof(p));
    while (fout)
    {
        if (p.getpnri() != x)
        {
            fin.write((char *)&p, sizeof(p));
        }
        else
        {
            f = 1;
        }
        fout.read((char *)&p, sizeof(p));
    }
    if (f == 0)
    {
        cout << "Pnr not found" << endl;
    }
    else
    {
        cout << "Ticket cancelled\n";
    }
    fout.close();
    fin.close();
    remove("international.txt");
    rename("international1.txt", "international.txt");
}

void checkticketi(int x)
{
    passenger p;
    int f = 0;
    ifstream fout("international.txt", ios::binary | ios::app);
    fout.read((char *)&p, sizeof(p));
    while (fout)
    {
        if (p.getpnri() == x)
        {
            p.dispi();
            f = 1;
        }
        fout.read((char *)&p, sizeof(p));
    }
    if (f == 0)
    {
        cout << "Pnr not found" << endl;
    }
    fout.close();
}

int main()
{
    int choice, choice2;
    char input = 'Y';
    passenger p1;
    payment p2;

    do
    {
        cout << "\n\nWelcome to XYZ Airlines\n";
        cout << "\nMain Menu\n";
        cout << "1.Book Ticket\n";
        cout << "2.Cancel Ticket\n";
        cout << "3.Check Ticket\n";
        cout << "4.Check Availability\n";
        cout << "5.Exit\n";

        cin >> choice;

        switch (choice)
        {
        case 1:
            system("CLS");
            cout << "\n\n1.Domestic Flights(1) \n2.International Flights(2)" << endl;
            cout << "\nPlease enter your option" << endl;
            cin >> choice2;

            switch (choice2)
            {
            case 1:
                p1.d_pnr();
                p1.p_detail(1);
                p1.gender_check();
                p1.more_details();
                p2.pay_detail(); // Simplified payment process
                p1.disp();
                createfile(p1);
                break;
            case 2:
                p1.p_detail(2);
                p1.i_pnr();
                p1.gender_check();
                p1.more_details();
                p2.pay_detail(); // Simplified payment process
                p1.dispi();
                createfilei(p1);
                break;
            default:
                cout << "Wrong input entered\nTry again\n\n\n" << endl;
                return main();
            }
            break;

        case 2:
            system("CLS");
            cout << "\n1.Domestic Flights(1)\n2.International Flights(2)" << endl;
            cout << "Please enter your option" << endl;
            cin >> choice2;
            int x;
            cout << "Enter the PNR no." << endl;
            cin >> x;

            if (choice2 == 1)
                cancelticket(x);
            else
                cancelticketi(x);

            break;

        case 3:
            system("CLS");
            cout << "\n1.Domestic Flights(1)\n2.International Flights(2)" << endl;
            cout << "Please enter your option" << endl;
            cin >> choice2;
            int y;
            cout << "Enter the PNR no." << endl;
            cin >> y;

            if (choice2 == 1)
                checkticket(y);
            else
                checkticketi(y);

            break;

        case 4:
            system("CLS");
            cout << "No flights available\n\n";
            break;

        case 5:
            exit(0);
            break;

        default:
            cout << "Wrong input entered\nTry again\n\n\n" << endl;
        }

        cout << "Do you want to enter the main menu?\n\nPress Y for yes and N for no.\n";
        cin >> input;
    } while (input == 'Y' || input == 'y');

    return 0;
}

#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include "main.hpp"

using namespace std;

vector<info> books;
vector<logs> adminlist;
int log_num, access, admin;

int Login();
void View();
void Add();
void Del();
void Search();
void Edit();
void Settings();

int main(){
    struct logs log_temp;
    struct info book_temp;
    string name;
    char op;
    log(adminlist);
    book(books);
    while(1){
        cout << "\n=============================\n";
        cout << "Log in as : \n1.| Admin\n2.| Guest\n3.| Exit\n\n- ";
        op = getchar();
        cin.ignore(100000, '\n');
        switch(op){
            case '1':
                if(adminlist.size() != 0){
                    admin = Login();
                    name = adminlist[log_num].user;
                }
                else{
                    admin = 1;
                    name = "Admin";
                }
                break;
            case '2':
                access = 1;
                name = "Guest";
                break;
            case '3':
                cout << "Exiting...\n";
                return 0;
        }
        while(access == 1 || admin == 1){
            cout << "\n=============================\n";
            cout << "LIBRARY MANAGEMENT SYSTEM\nWelcome back "<< name << "! What would you like to do?\n";
            if(admin){
                cout << "1.| View Collections\n2.| Add Book\n3.| Delete Book\n4.| Search Book\n5.| Edit Book\n6.| Settings\n7.| Exit\n\n- ";
                op = getchar();
                cin.ignore(100000, '\n');
                switch(op){
                    case '1':
                        View();
                        break;
                    case '2':
                        Add();
                        break;
                    case '3':
                        Del();
                        break;
                    case '4':
                        Search();
                        break;
                    case '5':
                        Edit();
                        break;
                    case '6':
                        Settings();
                        break;
                    case '7':
                        cout << "\nExiting...";
                        return 0;
                    default:
                        cout << "\nOption is invalid!\n";
                }
            }
            else{
                cout << "1.| View Collections\n2.| Search Book\n3.| Exit\n\n- ";
                op = getchar();
                cin.ignore(100000, '\n');
                switch(op){
                    case '1':
                        View();
                        break;
                    case '2':
                        Search();
                        break;
                    case '3':
                        cout << "\nExiting...";
                        return 0;
                    default:
                        cout << "\nOption is invalid!\n";
                }
            }
        }
    }
    return 0;
}

int Login(){
    struct logs input;
    while(1){
        log_num = 0;
        cout << "=============================\n";
        cout << "[LOGIN]\n|Enter 0 to exit|\nUSERNAME : ";
        getline(cin, input.user);
        cin.sync();
        if(input.user == "0") return 0;
        cout << "PASSWORD : ";
        getline(cin, input.pass);
        cin.sync();
        for(auto& i : adminlist){
            if(input.user == i.user && input.pass == i.pass){
                cout << "\nLogin successful!\n";
                return 1;
            }
            log_num++;
        }
        cout << "\nWrong username/password! Try again!\n\n";
    }
}

void View(){
    int num = 1;
    cout << "=============================\n";
    cout << "||Book Total : " << books.size() << "||\n";
    if(!books.empty()){
        for(auto &n : books){
            cout << endl << "   " << num << ".\t|Title\t\t: \"" << n.title << "\"\n\t|Author\t\t: " << n.author << "\n\t|Release date\t: " << n.date << "\n";
            num++;
        }
    }
    else{
        cout << "\nThe library is empty!\n";
    }
    cout << "\nPress enter to go back!";
    getchar();
    cin.ignore(100000, '\n');
}

void Add(){
        struct info book_temp;
        string title, author, date, day, month, year;
        cout << "=============================\n";
        cout << "Title\t: ";
        getline(cin, title);
        cin.sync();
        cout << "Author\t: ";
        getline(cin, author);
        cin.sync();
        cout << "Publish\t| Day   : ";
        cin >> day;
        cin.sync();
        cout << "\t| Month : ";
        cin >> month;
        cin.ignore(100000, '\n');
        cout << "\t| Year  : ";
        cin >> year;
        cin.ignore(100000, '\n');
        try{
            if(Digit(day) && Digit(month) && Digit(year)){
                if(0 < stoi(day) || stoi(day) <= 31){
                    if(0 < stoi(month) || stoi(month) <= 12){
                        if(0 < stoi(year)){
                            date = day + "/" + month + "/" + year;
                            book_temp = {title, author, date};
                            books.push_back(book_temp);
                            BookTransfer(books);
                            cout << "\nBook successfully added!\n";
                        } else throw 0;
                    } else throw 0;
                } else throw 0;
            } else throw 0;
        }
        catch(...){
            cout << "\nInvalid Date!\n";
        }
}

void Del(){
    int num;
    cout << "=============================\n";
    cout << "Enter the book number you want to erase : ";
    cin >> num;
    cin.ignore(100000, '\n');
    if(0 < num && books.begin() + num <= books.end()){
        books.erase(books.begin() + num - 1);
        BookTransfer(books);
        cout << "\nBook successfully erased!\n";
    }
    else cout << "\nThe book number is invalid!\n";
}

void Search(){
    vector<int> index;
    string key;
    int num;
    char op;
    size_t found;
    while(op != '3'){
        cout << "=============================\n";
        cout << "Search by : \n1.|Book Number\n2.|Keyword\n3.|Back\n\n- ";
        op = getchar();
        cin.ignore(100000, '\n');
        switch(op){
        case '1':
            cout << "\n=============================\n";
            cout << "Enter the book num : ";
            cin >> num;
            cin.ignore(100000, '\n');
            cout << endl << "   " << num << ".\t|Title\t\t: \"" << books[num-1].title << "\"\n\t|Author\t\t: " << books[num-1].author << "\n\t|Release date\t: " << books[num-1].date << "\n\n";
            break;
        case '2':   
            cout << "=============================\n";
            cout << "Enter the title keyword : ";
            getline(cin, key);
            cin.sync();
            for(auto& i : books){
                found = i.title.find(key);
                if(found != string::npos) index.push_back(num);
                num++;
            }
            if(!index.empty()) for(auto& i : index) cout << endl << "   " << i + 1 << ".\t|Title\t\t: \"" << books[i].title << "\"\n\t|Author\t\t: " << books[i].author << "\n\t|Release date\t: " << books[i].date << "\n\n";
            else cout << "\nNo book was found!\n\n";
            num = 0;
            index.clear();
            break;
        case '3':
            break;
        default:
            cout << "\nOption is invalid!\n";
        }    
    }
}

void Edit(){
    string day, month, year;
    char op, booknum;
    cout << "=============================\n";
    cout << "Enter the book number you want to edit : ";
    booknum = getchar();
    cin.ignore(100000, '\n');
    if(isdigit(booknum)){
        int num = int(booknum - '0');
        while(op != '4'){
            cout << "=============================\n";
            cout << "Edit \"" << books[num-1].title << "\" : \n\n1.|Title\n2.|Author\n3.|Date\n4.|Exit\n\n-";
            op = getchar();
            cin.ignore(100000, '\n');
            switch(op){
                case '1':
                    cout << "\nPrevious Title : \"" << books[num-1].title << "\"\n";
                    cout << "New Title : ";
                    getline(cin, books[num-1].title);
                    BookTransfer(books);
                    cout << "\nNew title saved!\n";
                    break;
                case '2':
                    cout << "\nPrevious Author : " << books[num-1].author << endl;
                    cout << "New Author : ";
                    getline(cin, books[num-1].author);
                    BookTransfer(books);
                    cout << "\nNew author saved!\n";
                    break;
                case '3':
                        cout << "Previous date : " << books[num-1].date << endl;
                        cout << "New date : \t1.|Day   : ";
                        getline(cin, day);
                        cout << "\t\t2.|Month : ";
                        getline(cin, month);
                        cout << "\t\t3.|Year  : ";
                        getline(cin, year);
                    try{
                        if(Digit(day) && Digit(month) && Digit(year)){
                            if(0 < stoi(day) || stoi(day) <= 31){
                                if(0 < stoi(month) || stoi(month) <= 12){
                                    if(0 < stoi(year)){
                                        books[num-1].date = day + "/" + month + "/" + year;
                                        BookTransfer(books);
                                        cout << "\nNew date saved!\n";
                                    } else throw 0;
                                } else throw 0;
                            } else throw 0;
                        } else throw 0;
                    }
                    catch(...){
                        cout << "\nInvalid Date!\n";
                    }
                    break;
                case 4:
                    break;
                default:
                    cout << "\nOption is invalid!\n";
            }
        }
    }
    else cout << "\nThe book number is invalid!\n";
}

void Settings(){
    struct logs new_log;
    string newuser, newpass;
    char op, del;
    while(op != '5'){
        cout << "=============================\n[SETTINGS]\n";
        cout << "1.|View Username/Password\n2.|Change Password\n3.|Create New Account\n4.|Delete Account\n5.|Back\n\n-";
        op = getchar();
        cin.ignore(100000, '\n');
        switch(op){
            case '1':
                if(adminlist.size() != 0){
                    cout << "=============================\n";
                    cout << "Username : " << adminlist[log_num].user << endl;
                    cout << "Password : " << adminlist[log_num].pass << endl;
                    cout << "\nPress enter to go back!";
                    getchar();
                    cin.ignore(100000, '\n');
                    break;
                } else cout << "\nYou don't have an account!\n";
            case '2':
                if(adminlist.size() != 0){
                    cout << "=============================\n";
                    cout << "Enter your new password : ";
                    getline(cin, newpass);
                    cin.sync();
                    if(newpass == ""){
                        adminlist[log_num].pass = newpass;
                        LogTransfer(adminlist);
                        cout << "\nChange successful!\n";
                    }
                } else cout << "\nYou don't have an account!\n";
                break;
            case '3':
                cout << "=============================\n";
                cout << "Insert the new username : ";
                getline(cin, newuser);
                cin.sync();
                cout << "Insert the new password : ";
                getline(cin, newpass);
                cin.sync();
                if(newuser != "" && newpass != ""){
                    new_log = {newuser,newpass};
                    adminlist.push_back(new_log);
                    LogTransfer(adminlist);
                    cout << "\nAccount Created!\n";
                }
                else cout << "\nUsername/Password cannot be empty!\n";
                break;
            case '4':
                if(adminlist.size() != 0){
                    cout << "=============================\n";
                    cout << "Are you sure you want to delete this account? y/n\n\n-";
                    del = getchar();
                    cin.ignore(100000, '\n');
                    if(del == 'y'){
                        adminlist.erase(adminlist.begin() + log_num);
                        LogTransfer(adminlist);
                        access = 0;
                        op = '5';
                        cout << "\nAccount successfully deleted!\n";
                    }
                } else cout << "\nYou don't have an account!\n";
                    break;
            case '5':
                break;
            default:
                cout << "\nOption is invalid!\n";
        }
    }
}
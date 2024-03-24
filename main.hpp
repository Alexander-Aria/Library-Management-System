using namespace std;

struct logs{
    string user;
    string pass;
};

struct info{
    string title, author, date;
};

void log(vector<logs>& adminlist){
    struct logs temp;
    string t, t2;
    fstream username, password;
    username.open("LibData/username.txt", ios::in);
    password.open("LibData/password.txt", ios::in);
    while(getline(username, t) && getline(password, t2)){
        temp = {t, t2};
        adminlist.push_back(temp);
    }
    username.close();
    password.close();
}

void book(vector<info>& books){
    struct info temp;
    string btitle, bauthor, bdate;
    fstream title, author, date;
    title.open("LibData/title.txt", ios::in);
    author.open("LibData/author.txt", ios::in);
    date.open("LibData/date.txt", ios::in);
    while(getline(title, btitle) && getline(author, bauthor) && getline(date, bdate)){
        temp = {btitle, bauthor, bdate};
        books.push_back(temp);
    }
    title.close();
    author.close();
    date.close();
}

void BookTransfer(vector<info>& books){
    fstream titletemp, authortemp, datetemp;
    vector<info>::iterator it = books.begin();
    titletemp.open("LibData/titletemp.txt", ios::out);
    authortemp.open("LibData/authortemp.txt", ios::out);
    datetemp.open("LibData/datetemp.txt", ios::out);
    for(auto& i : books){
        if(it != books.begin()){
            titletemp << endl;
            authortemp << endl;
            datetemp << endl;
        }
        titletemp << i.title;
        authortemp << i.author;
        datetemp << i.date;
        it++;
    }
    titletemp.close();
    authortemp.close();
    datetemp.close();
    remove("LibData/title.txt");
    remove("LibData/author.txt");
    remove("LibData/date.txt");
    rename("LibData/titletemp.txt", "LibData/title.txt");
    rename("LibData/authortemp.txt", "LibData/author.txt");
    rename("LibData/datetemp.txt", "LibData/date.txt");
}

void LogTransfer(vector<logs>& adminlist){
    fstream usertemp, passtemp;
    vector<logs>::iterator it = adminlist.begin();
    usertemp.open("LibData/usertemp.txt", ios::out);
    passtemp.open("LibData/passtemp.txt", ios::out);
    for(auto& i : adminlist){
        if(it != adminlist.begin()){
            usertemp << endl;
            passtemp << endl;
        }
        usertemp << i.user;
        passtemp << i.pass;
        it++;
    }
    usertemp.close();
    passtemp.close();
    remove("LibData/username.txt");
    remove("LibData/password.txt");
    rename("LibData/usertemp.txt", "LibData/username.txt");
    rename("LibData/passtemp.txt", "LibData/password.txt");
}

bool Digit(string str){
    for(char i : str){
        if(!isdigit(i)){
            return 0;
        }
    }
    return 1;
}


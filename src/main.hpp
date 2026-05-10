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
    username.open("data/username.txt", ios::in);
    password.open("data/password.txt", ios::in);
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
    title.open("data/title.txt", ios::in);
    author.open("data/author.txt", ios::in);
    date.open("data/date.txt", ios::in);
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
    titletemp.open("temp/titletemp.txt", ios::out);
    authortemp.open("temp/authortemp.txt", ios::out);
    datetemp.open("temp/datetemp.txt", ios::out);
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
    remove("data/title.txt");
    remove("data/author.txt");
    remove("data/date.txt");
    rename("temp/titletemp.txt", "data/title.txt");
    rename("temp/authortemp.txt", "data/author.txt");
    rename("temp/datetemp.txt", "data/date.txt");
}

void LogTransfer(vector<logs>& adminlist){
    fstream usertemp, passtemp;
    vector<logs>::iterator it = adminlist.begin();
    usertemp.open("temp/usertemp.txt", ios::out);
    passtemp.open("temp/passtemp.txt", ios::out);
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
    remove("data/username.txt");
    remove("data/password.txt");
    rename("temp/usertemp.txt", "data/username.txt");
    rename("temp/passtemp.txt", "data/password.txt");
}

bool Digit(string str){
    for(char i : str){
        if(!isdigit(i)){
            return 0;
        }
    }
    return 1;
}


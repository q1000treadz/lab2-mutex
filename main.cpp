#include <iostream>
#include <fstream>
#include<thread>
#include<vector>
#include <mutex>
using namespace std;
class Person {
    string name;
    int age;
    string job;
    public:
    Person() {}
    Person(string name, int age, string job) : name(name), age(age), job(job) {
        
    }
    friend ostream& operator<<(ostream& os, const Person& pers);
    friend istream& operator>>(istream &in,  Person& pers);
};

ostream& operator<<(ostream& os, const Person& pers)
{
    os << pers.name << ' ' << pers.age << ' ' << pers.job<<'\n';
    return os;
}

istream& operator>>(istream &in,  Person &pers)
{
    in >> pers.name >> pers.age >> pers.job;
    return in;
}

mutex file_lock;
 
void writePersonsToFile(vector<Person>persons) {
    file_lock.lock();
    cout<<"write start"<<endl;
    ofstream ofs("database.txt");
    for(auto pp: persons) {
        ofs<<pp;
    }
    ofs.close();
    cout<<"write end"<<endl;
    file_lock.unlock();
}

void readPersonsFromFile() {
    file_lock.lock();
    cout<<"read start"<<endl;
    ifstream ifs("database.txt");
    vector<Person> persons;
    Person p;
    while(ifs >> p) {
        persons.push_back(p);
    }
    for(auto pp: persons) {
        cout<<pp;
    }
    ifs.close();
    cout<<"read end"<<endl;
    file_lock.unlock();
}
int main() {
    vector<Person> persons = { Person("vanya", 21, "programmer"), Person("nastya", 23, "trainer"), Person("anton", 25, "footballer") };
    thread write = thread(writePersonsToFile, persons);
    thread read = thread(readPersonsFromFile);
    write.join();
    read.join();
    return 0;
}
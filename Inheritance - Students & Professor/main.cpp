#include <iostream>
#include <string>
using namespace std;

int professor_id = 0;
int student_id = 0;

class Person {
public:
  string name;
  int age, score, id;
  virtual void putdata() = 0;
  virtual void getdata() = 0;
};
class Professor : public Person {
  void putdata() { cout << name << ' ' << age << ' ' << score << ' ' << ++professor_id << endl; }
  void getdata() { cin >> name >> age >> score; }
};
class Student : public Person {
  void putdata() { cout << name << ' ' << age << ' ' << score << ' ' << ++student_id << endl; }
  void getdata() { cin >> name >> age; score = 0; for (int i = 0, x; i < 6; i++)cin >> x, score += x; }
};

int main() {
  int n, val;
  cin >> n;
  Person *per[n];

  for (int i = 0; i < n; i++) {
    cin >> val;

    if (val == 1) {
      per[i] = new Professor;
    }
    else per[i] = new Student;

    per[i]->getdata();
  }

  for (int i = 0; i < n; i++)
    per[i]->putdata();

  return 0;
}
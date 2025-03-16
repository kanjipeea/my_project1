#include <iostream>
#include<vector>
#include<numeric>
using namespace std;
class Student{
        std::string name;
        std::string surname;
        int album_number;
        std::vector<float> grades;
        float final_grade;
    public:
        void set_name(string n,string s){
            name=n;
            surname=s;
        }
        void set_albumNumber(int num){
            album_number=num;
        }
        void display(){
            cout<<name<<" "<<surname<<": ";
            for(auto i:grades){
                cout<<i<<" ";
            }
            cout<<endl;
            cout<<"Final grade: "<<final_grade<<endl;
        }
        void add_grade(float grade){
            if(grade>=2.0 && grade <=5.0){
                grades.push_back((grade));
            }
        }
        void calculate_grade(){
            float sum=std::accumulate(grades.begin(),grades.end(),0.0f);
            final_grade=sum/grades.size();
        }
        bool passing(){
            int bad_grades=0;
            for(auto i:grades){
                if (i==2.0){
                    bad_grades++;
                }
            }
            if(bad_grades>1){return false;}
            return true;
        }
    };
class Complex{
private:
    double real;
    double imag;
public:
    Complex(double r=0.0, double i=0.0){
        real=r; imag=i;
    }
    void set_r(double r){
        real=r;
    }
    void set_im(double i){
        imag=i;
    }
    void display(){
        cout<<real;
        if(imag>0){
            cout<<"+"<<imag<<"i";
        }
        else if(imag<0){
            cout<<imag<<"i";
        }
        cout<<endl;
    }
    void add(const Complex& num){
        real+=num.real;
        imag+=num.imag;
    }
};
int main(){
    Student student;
    Student student2;
    student.set_name("Anton","Dyrachyo");
    student.add_grade(2); student.add_grade(2); student.add_grade(3);
    student.calculate_grade();
    student.display();
    Complex a(1.0, -2.0);
    Complex b(3.14);
    a.add(b);
    a.display();
    b.display();
    return 0;
}

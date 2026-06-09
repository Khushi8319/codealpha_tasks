#include<iostream>
#include<vector>
#include<string>
using namespace std;

// convert grade letter into grade points
float gradeToPoint(string grade){
    if(grade=="A+") return 10;
    else if(grade=="A") return 9;
    else if(grade=="B+") return 8;
    else if(grade=="B") return 7;
    else if(grade=="C+") return 6;
    else if(grade=="C") return 5;
    else if(grade=="D") return 4;
    else return 0; // F grade
}

int main(){
    int totalSem;
    cout<<"Enter total number of semesters: ";
    cin>>totalSem;

    float overallCredits=0;
    float overallPoints=0;

    for(int s=1;s<=totalSem;s++){
        int courses;
        cout<<"Semester "<<s<<endl;
        cout<<"Enter number of courses: ";
        cin>>courses;

        vector<string> courseNames(courses);
        vector<string> grades(courses);
        vector<float> credits(courses);

        float semCredits=0;
        float semPoints=0;

        // input details for each course
        for(int i=0;i<courses;i++){
            cout<<"\nCourse "<<i+1<<endl;

            cout<<"Enter Course Name: ";
            cin>>ws;                     // clears extra newline
            getline(cin,courseNames[i]); // allows spaces in name

            cout<<"Enter Grade: ";
            cin>>grades[i];

            cout<<"Enter Credits: ";
            cin>>credits[i];

            float points=gradeToPoint(grades[i]);
            semCredits+=credits[i];          // total semester credits
            semPoints+=points*credits[i];    // total grade points
        }

        float semGPA=semPoints/semCredits;

        // print course details of semester
        cout<<"\nCourse Details (Semester "<<s<<"):"<<endl;
        for(int i=0;i<courses;i++){
            cout<<courseNames[i]
                <<" | Grade: "<<grades[i]
                <<" | Credits: "<<credits[i]<<endl;
        }

        cout<<"Semester "<<s<<" GPA: "<<semGPA<<endl;

        overallCredits+=semCredits;
        overallPoints+=semPoints;
    }

    float CGPA=overallPoints/overallCredits;
    cout<<"\nFinal CGPA: "<<CGPA<<endl;

    return 0;
}
/*main.cpp*/

//
// <Beatha Mwombeki>
// U. of Illinois, Chicago
// CS 341, Fall 2019
// Project #03: GradeUtil UI
// This program is C++11 dependent
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype> 
using namespace std;

// includes for gradeutil
#include "gradeutil.h"

College InputGradeData(string filename)
{
    College college;
    ifstream file(filename);
    string line, value;

    if (!file.good())
    {
        cout << "**Error: unable to open input file '" << filename << "'." << endl;
        return college;
    }

    // first line contains semester,year
    getline(file, line);
    stringstream ss(line);

    getline(ss, college.Name, ',');
    getline(ss, college.Semester, ',');
    getline(ss, value);
    college.Year = stoi(value);

    // second line contains column headers --- skip
    getline(file, line);

    //
    // now start inputting and parse course data:
    //

    while (getline(file, line))
    {
        Course c = ParseCourse(line);

        //
        // search for correct dept to ask course to, otherwise create a new dept:
        //
        auto dept_iter = std::find_if(college.Depts.begin(),
                                      college.Depts.end(),
                                      [&](const Dept &d) {
                                          return (d.Name == c.Dept);
                                      });

        if (dept_iter == college.Depts.end())
        {
            //
            // doesn't exist, so we have to create a new dept
            // and insert course:
            //
            Dept d(c.Dept);

            d.Courses.push_back(c);

            college.Depts.push_back(d);
        }
        else
        {
            // dept exists, so insert course into existing dept:
            dept_iter->Courses.push_back(c);
        }

    } //while

    //
    // done:
    //
    return college;
}

// TODO: define your own functions
//
//

// college-level summary function
void CollegeLevelSummary (College college)
{
    //variable declaration
    int  totalStudent = 0;
    int totalCourses = 0;
    double theDFWRate;
    double percentA;
    double percentB;
    double percentC;
    double percentD;
    double percentF;
    int DFW = 0;
    int N = 0;
    cout <<"** College  of " <<   college.Name << ", " <<  college.Semester << " "<< college.Year << " **" << endl;
    for(const Dept& dept: college.Depts)
    {
        totalStudent += dept.NumStudents(); // get number of students in a college
        totalCourses += dept.NumCourses(); // get number of courses in a college
    } // end of for loop
         //get and print grade distribution
        GradeStats d;  //create a  GradeStats object
      
          // call a function to return GradeStats with grade 
        d = GetGradeDistribution(college); // assign returned object from a function to d
      
        //get a total percentage of all the departments
        percentA = d.PercentA;
        percentB = d.PercentB;
        percentC = d.PercentC;
        percentD = d.PercentD;
        percentF = d.PercentF;
        
        //get and print DFW rate
        theDFWRate = GetDFWRate(college, DFW, N);
  
  //cout << "** College of Engineering, Fall 2018 **" << endl;
   //print the summary
  
   cout << "# of courses taught: " << totalCourses << endl;
   cout << "# of students taught: " << totalStudent << endl;
   cout << "grade distribution (A-F): " << percentA << "%, "  << percentB << "%, " << percentC << "%, " ; 
   cout << percentD <<  "%, " <<  percentF << "%"<<  endl;
   cout << "DFW rate: " << theDFWRate << "%"<< endl;

} // end of CollegeLevelSummary



//checking if the department exists
bool checkInstructorPrefix( string instructorPrefix, College college) 
{
  bool check = false;
  size_t len = instructorPrefix.length();
  for(const Dept& h : college.Depts){
      for(const Course& course : h.Courses) {

      if(course.Instructor.substr(0,len) == instructorPrefix) // match
      {
        check = true;
      }
       
     } 
  }
  
  return check;
} // end of checkDepartmentInCollege




//check if department exists in college
bool  checkDepartmentInCollege( string userInput, College college) 
{
  bool check = false;
  for(const Dept& h : college.Depts){
   if(h.Name == userInput){
     check = true;
     }
  }
  
  return check;
} // end of checkDepartmentInCollege


//check if the course number exists 
bool checkCourseNumber( int userInput, College college ) 
{
  bool check = false;
  for(const Dept& h : college.Depts){
        for(const Course& course : h.Courses) {

          if(course.Number == userInput) // match
          {
            check = true;
          }
    }
  }
  
  return check;
} // end of checkCourseNumber


// check a course number in a departments
//check if the course number exists 
bool checkCourseNumberInDepts( int userInput, string userInput2, College college ) 
{
  bool check = false;
  for(const Dept& h : college.Depts){
      if(h.Name == userInput2){
            for(const Course& course : h.Courses) {

              if(course.Number == userInput) // match
              {
                check = true;
              }
        }
      }
  }
  
  return check;
} // end of checkCourseNumber

 


void forAllDepts(College college)
{
  int totalCourses;
  int totalStudent;
  int DFW = 0;
  int N = 0;
  
  //sorting departments in ascending order
  sort(college.Depts.begin(), college.Depts.end(),
	  [](const Dept& d1, const Dept& d2)
	{
	  if (d1.Name < d2.Name)
		return true;
	  else if (d1.Name > d2.Name)
		return false;
		  else
			return false;
	}
	  ); // end of sort function
  
  for(const Dept& dept: college.Depts)
      {
         double theDFWRate;
         
           //print the name of every department
            cout << dept.Name << ":" << endl;
            totalStudent = dept.NumStudents();  // get number of students in a department
            totalCourses = dept.NumCourses();  // get number of courses in a department
            cout << " # courses taught: " << totalCourses << endl;
            cout << " # students taught: " << totalStudent << endl;
           
            //get and print grade distribution
            GradeStats d; // create a GradeStats object
            d = GetGradeDistribution(dept);
            cout << " grade distribution (A-F): " << d.PercentA << "%, "  << d.PercentB << "%, " << d.PercentC << "%, "; 
            cout <<  d.PercentD <<  "%, " << d.PercentF << "%"<<  endl;
           
            //get and print DFW rate
            theDFWRate = GetDFWRate(dept, DFW, N);
            cout << " DFW rate: " << theDFWRate << "%"<< endl;
      } // end of for loop
  
}  // end of  forAllDepts()


// print a college-wide summary, or a departmental summary
void getSummary( College college)
{   int totalCourses;
    int totalStudent;
    int DFW = 0;
    int N = 0;
    string deptName;
    cout << "dept name, or all? ";
    cin >> deptName;
    //check if the input is upper or lower because is case-sensitive
    //if is lower print an error message else proceed
    //if(islower(deptName)){
      // cout << "sorry" << deptName << "should be upper" << endl;
   // }
 
    if(deptName == "all"){
     forAllDepts(college);   // call a function for all which means college summary
   }
     // summary for one department
    else 
    {
      if(checkDepartmentInCollege(deptName,college)) 
      {
        for(const Dept& dept: college.Depts)
        {
           double theDFWRate;
           if(dept.Name == deptName)
           {
             //print the name of every department
              cout << dept.Name << ":" << endl;
              totalStudent = dept.NumStudents();  // get number of students in a department
              totalCourses = dept.NumCourses();  // get number of courses in a department
              cout << " # courses taught: " << totalCourses << endl;
              cout << " # students taught: " << totalStudent << endl;

              //get and print grade distribution
              GradeStats d; // create a GradeStats object
              d = GetGradeDistribution(dept);
              cout << " grade distribution (A-F): " << d.PercentA << "%, "  << d.PercentB << "%, " << d.PercentC << "%, "; 
              cout <<  d.PercentD <<  "%, " << d.PercentF << "%"<<  endl;

              //get and print DFW rate
              theDFWRate = GetDFWRate(dept, DFW, N);
              cout << " DFW rate: " << theDFWRate << "%"<< endl;
          } // end of if
        } // end of for loop
      } // end of if(checkDepartmentInCollege(deptName, college)) 
      
     else {
      cout << "**dept not found" << endl; 
     }
    } // end of else statement
 
} // end of getSummary




// search for a department or college-wide search by course number or instructor prefix
void doSearch( College college)
{
  string deptName, instructorPrefix;
    int DFW = 0;
    int N = 0;
    int courseNum;
    double theDFWRate;
    vector<Course>  courses;
    cout << "dept name, or all? ";
    cin >> deptName;
    // search in a college
    if(deptName == "all") 
    {
      cout << "course # or instructor prefix? ";
      cin >> instructorPrefix;
      stringstream ss(instructorPrefix);  // create stringstream object
      ss >> courseNum;  // try to convert input to a course #:
      
       // conversion failed, input is not numeric
       if ( ss.fail()) 
       {
          if (checkInstructorPrefix( instructorPrefix, college) == true){
               courses = FindCourses(college,instructorPrefix);   // get the vector of courses

              // go through the vector and print each course information
              for(const Course& course : courses)
              {
                  cout << course.Dept << " " << course.Number << " (section " << course.Section << "): " << course.Instructor  << endl;
                  cout << " # students: " << course.getNumStudents() << endl;
                  if(course.getGradingType() == Course::Letter){
                      cout << " course type: " << "letter" << endl;
                    }
                    else if(course.getGradingType() == Course::Satisfactory){
                          cout << " course type: " << "satisfactory" << endl;
                      }
                      else {
                           cout << " course type: " << "unknown" << endl;
                      }
                   //get and print grade distribution
                  GradeStats d; // create a GradeStats object
                  d = GetGradeDistribution(course);
                  cout << " grade distribution (A-F): " << d.PercentA << "%, "  << d.PercentB << "%, " << d.PercentC << "%, "; 
                  cout <<  d.PercentD <<  "%, " << d.PercentF << "%"<<  endl;

                  //get and print DFW rate
                  theDFWRate = GetDFWRate(course, DFW, N);
                  cout << " DFW rate: " << theDFWRate << "%"<< endl;
            }
          }
         
         else {
           cout << "**none found" << endl;
         }
         
       } // end of if ( ss.fail())
      
         // conversion worked, courseNum contains numeric value
      else {
          if ( checkCourseNumber(courseNum,college ) == true){
               courses = FindCourses(college,courseNum);   // get the vector of courses

              // go through the vector and print each course information
              for(const Course& course : courses)
              {
                  cout << course.Dept << " "<< course.Number << " (section " << course.Section << "): " << course.Instructor << endl;
                  cout << " # students: " << course.getNumStudents() << endl;
                  if(course.getGradingType() == Course::Letter){
                        cout << " course type: " << "letter" << endl;
                    }
                  else if(course.getGradingType() == Course::Satisfactory){
                        cout << " course type: " << "satisfactory" << endl;
                    }
                    else {
                         cout << " course type: " << "unknown" << endl;
                    }
                  //get and print grade distribution
                  GradeStats d; // create a GradeStats object
                  d = GetGradeDistribution(course);
                  cout << " grade distribution (A-F): " << d.PercentA << "%, "  << d.PercentB << "%, " << d.PercentC << "%, "; 
                  cout <<  d.PercentD <<  "%, " << d.PercentF << "%" << endl;

                  //get and print DFW rate
                  theDFWRate = GetDFWRate(course , DFW, N);
                  cout << " DFW rate: " << theDFWRate << "%" << endl;
              } // end of for loop
          } // end of if ( checkCourseNumber)
        else {
          cout << "**none found " << endl;
        }
      } // end of else
      
    } //end of if all
  
    else {
      
        cout << "course # or instructor prefix? ";
        cin >> instructorPrefix;
        stringstream ss(instructorPrefix);  // create stringstream object
        ss >> courseNum;  // try to convert input to a course #:
         // conversion failed, input is not numeric
         if(checkDepartmentInCollege(deptName, college) == true) 
      {
        if ( ss.fail() ) 
        {
          if (checkInstructorPrefix( instructorPrefix, college)){
             for(const Dept& dept: college.Depts)
              {
                 double theDFWRate;
                 if(dept.Name == deptName)
                 {
                     courses = FindCourses(dept,instructorPrefix);   // get the vector of courses

                    // go through the vector and print each course information
                    for(const Course& course : courses)
                    {
                        cout << course.Dept << " "<< course.Number << " (section " << course.Section << "): " << course.Instructor << endl;
                        cout << " # students: " << course.getNumStudents() << endl;

                         if(course.getGradingType() == Course::Letter){
                          cout << " course type: " << "letter" << endl;
                         }
                         else if(course.getGradingType() == Course::Satisfactory){
                          cout << " course type: " << "satisfactory" << endl;
                         }
                         else {
                           cout << " course type: " << "unknown" << endl;
                         }
                         //get and print grade distribution
                         GradeStats d; // create a GradeStats object
                         d = GetGradeDistribution(course);
                         cout << " grade distribution (A-F): " << d.PercentA << "%, "  << d.PercentB << "%, " << d.PercentC << "%, "; 
                         cout <<  d.PercentD <<  "%, " << d.PercentF << "%" <<  endl;

                         //get and print DFW rate
                         theDFWRate = GetDFWRate(course, DFW, N);
                         cout << " DFW rate: " << theDFWRate << "%" << endl;
                    }  // end of inner for loop
                 }
               } // end of for loop
           } // end of if (checkDepartmentInCollege( instructorPrefix, college))
          
          else {
           cout << "**none found" << endl;

            }
         } // end of if if ( ss.fail())

           // conversion worked, courseNum contains numeric value
        else 
        {
           if( checkCourseNumberInDepts(courseNum,deptName,college) == true)
           {
               for(const Dept& dept: college.Depts)
                    {
                       double theDFWRate;
                       if(dept.Name == deptName)
                       {
                           courses = FindCourses(dept,courseNum);   // get the vector of courses

                          // go through the vector and print each course information
                          for(const Course& course : courses)
                          {
                              cout << course.Dept << " "<< course.Number << " (section " << course.Section << "): " << course.Instructor  << endl;
                              cout << " # students: " << course.getNumStudents() << endl;
                              if(course.getGradingType() == Course::Letter){
                                 cout << " course type: " << "letter" << endl;
                               }
                             else if(course.getGradingType() == Course::Satisfactory){
                                    cout << " course type: " << "satisfactory" << endl;
                                }
                              else {
                                   cout << " course type: " << "unknown" << endl;
                                }

                               //get and print grade distribution
                              GradeStats d; // create a GradeStats object
                              d = GetGradeDistribution(course);
                              cout << " grade distribution (A-F): " << d.PercentA << "%, "  << d.PercentB << "%, " << d.PercentC << "%, "; 
                              cout <<  d.PercentD <<  "%, " << d.PercentF << "%"<<  endl;

                              //get and print DFW rate
                              theDFWRate = GetDFWRate(course, DFW, N);
                              cout << " DFW rate: " << theDFWRate << "%"<< endl;
                          }  // end of inner for loop
                       }
                     } // end of for loop
               }// end of if( checkCourseNumber(courseNum,college ))
            else {
            cout << "**none found" << endl;
          }
        } // end of else
      } // end of (checkDepartmentInCollege(deptName, college))
      
      else {
      cout << "**dept not found" << endl; 
     }
    }
     
 } // end of search 


//performs a department or college-wide search for all courses whose Grading type is Course::Satisfactory
void satisfactory (College college)
{
   string deptName;
   vector<Course>  theCourses; 
   cout << "dept name, or all? ";
   cin >> deptName;
   // check if the user enters all
   if(deptName == "all")
    {
      for(const Dept& dept : college.Depts)
      {
        
        for(const Course& course : dept.Courses)
        {
         theCourses.push_back(course); // put all the courses in theCourses vector
        }
      }
     
       //sort courses vector
      sort(theCourses.begin(), theCourses.end(), 
      [](const Course& d1, const Course& d2)
      {
        if (d1.Dept < d2.Dept)
          return true;
        else if (d1.Dept > d2.Dept)
          return false;
        else // same dept, look at course #:
          if (d1.Number < d2.Number)
            return true;
          else if (d1.Number > d2.Number)
            return false;
          else // same course #, look at section #:
            if (d1.Section < d2.Section)
              return true;
            else  
              return false;
      }
    );
     
       //loop through the department and course vectors
      
        for(const Course& course : theCourses)
        {
          
           if(course.getGradingType() == Course::Satisfactory)
           {
             
              cout << course.Dept << " "<< course.Number << " (section " << course.Section << "): " << course.Instructor  << endl;
              cout << " # students: " << course.getNumStudents() << endl;
             
              if(course.getGradingType() == Course::Satisfactory){
                 cout << " course type: " << "satisfactory" << endl;
                }//end of inner loop
           } // end of outer if 
        } // end of  for loop
     }// end of if (deptName == "all")
  
  else 
  {   bool check = false;
      if(checkDepartmentInCollege(deptName, college)) 
        { 
            for(const Dept& dept : college.Depts)
          {
            if(dept.Name == deptName ){
                for(const Course& course : dept.Courses)
                {
                 theCourses.push_back(course); // put all the courses in theCourses vector
                }
              }
            }

             //sort courses vector
          sort(theCourses.begin(), theCourses.end(), 
          [](const Course& d1, const Course& d2)
          {
             // same dept, look at course #:
              if (d1.Number < d2.Number)
                return true;
              else if (d1.Number > d2.Number)
                return false;
                // same course #, look at section #:
                else if (d1.Section < d2.Section)
                  return true;
                else  
                  return false;
          }
        );
     
          //loop through the department and course vectors
            for(const Dept& dept : college.Depts)
            {
              if(dept.Name == deptName) 
              {
                for(const Course& course : theCourses)
                {
                  
                   if(course.getGradingType() == Course::Satisfactory)
                   {
                     check = true;
                      // print department name, number, section and instructor name
                      cout << course.Dept << " "<< course.Number << " (section " << course.Section << "): " << course.Instructor  << endl;
                      cout << " # students: " << course.getNumStudents() << endl; // get the number of students

                      if(course.getGradingType() == Course::Satisfactory){
                         cout << " course type: " << "satisfactory" << endl;
                        }//end of inner loop
                    } // end of outer if
                  
                 } // end of inner for loop
                
              } // end of if(dept.Name == deptName)   
           } // end of outer for loop
        if(check == false) {
          cout << "**none found" << endl;
        }
  
       } // end of if(checkDepartmentInCollege(deptName, college))
    
     
    else {
        cout << "**dept not found"; 
       }
   } // end of else statement
    
} // end of satisfactory()


// check if threshold  exists in college
// 
bool checkthreshold(double userInput, College college) {
  bool check = false;
  int DFW = 0;
  int N = 0;
  for(const Dept& h : college.Depts){
            for(const Course& course : h.Courses) {

              if(GetDFWRate( course, DFW, N) > userInput) // match
              {
                check = true;
              }
      }
  }
  
  return check;
}

// checking for course whose letterB exceds the user threshold
// 
// check if shreshold exists in college
// 
bool checkletterBthreshold(double userInput, College college) {
   bool check = false;
  for(const Dept& h : college.Depts){
            
              for(const Course& course : h.Courses) {

                if(GetGradeDistribution(course).PercentB > userInput) // match
                {
                  check = true;
             }
      }
  }
  
  return check;
}


bool checkletterBthresholdforDepts(double userInput, College college, string userInput2) {
   bool check = false;
  for(const Dept& h : college.Depts){
            if(h.Name == userInput2){
              for(const Course& course : h.Courses) {

                if(GetGradeDistribution(course).PercentB > userInput) // match
                {
                  check = true;
             }
        }
      }
  }
  
  return check;
}




//Fuction to check  the DFW for a college
void forCollegeDFW( College college)
{
   double  theDFWRate;
   double threshold;
   cout << "dfw threshold? " ;
   cin  >> threshold;
  
 if(checkthreshold(threshold, college) == false)
      {
        cout << "**none found" << endl;
      }
  
  else {
   vector<Course> theCourses; 
   for(const Dept& dept : college.Depts)
      {
        
        for(const Course& course : dept.Courses)
        {
         theCourses.push_back(course); // put all the courses in theCourses vector
        }
      }
     
       //sort courses vector
      sort(theCourses.begin(), theCourses.end(), 
      [](const Course& d1, const Course& d2)
      { 
        //variable to be passed as argument to GetDFWRate
        int DFW = 0;
        int N = 0;
        if (GetDFWRate(d1,DFW,N) > GetDFWRate(d2,DFW,N))
          return true;
        else if (GetDFWRate(d1,DFW,N) < GetDFWRate(d2,DFW,N))
          return false;
         // same DFW, look at Deptments:
          else if (d1.Dept < d2.Dept)
            return true;
          else if (d1.Dept > d2.Dept)
            return false;
        else // same dept, look at course #:
          if (d1.Number < d2.Number)
            return true;
          else if (d1.Number > d2.Number)
            return false;
          else // same course #, look at section #:
            if (d1.Section < d2.Section)
              return true;
            else  
              return false;
      }
    ); 
    
    
    // go through the theCourses vector and  print the information of each course
    for( const Course& course : theCourses)
    {   int DFW = 0;
        int N = 0;
        theDFWRate = GetDFWRate(course, DFW, N);
        // check if the DFW of each course is greater than threshold
        // and if it is print out the course summary 
       if(theDFWRate > threshold)
       {
          cout << course.Dept << " "<< course.Number << " (section " << course.Section << "): " << course.Instructor << endl;
          cout << " # students: " << course.getNumStudents() << endl;

          if(course.getGradingType() == Course::Letter){
             cout << " course type: " << "letter" << endl;
            }
         
          else if(course.getGradingType() == Course::Satisfactory){
                     cout << " course type: " << "satisfactory" << endl;
                }
         
            else {
                  cout << " course type: " << "unknown" << endl;
                 }
            //get and print grade distribution
            GradeStats d; // create a GradeStats object
            d = GetGradeDistribution(course);
            cout << " grade distribution (A-F): " << d.PercentA << "%, "  << d.PercentB << "%, " << d.PercentC << "%, "; 
            cout <<  d.PercentD <<  "%, " << d.PercentF << "%" <<  endl;
            cout << " DFW rate: " << theDFWRate << "%" << endl;
          } // end of (theDFWRate > threshold)
       } // end of for loop
  }
    
} // forCollegeDFW( College college)



void theDFW( College college){
  
   double threshold;
   double  theDFWRate;
   string deptName;
   vector<Course> theCourses; 
   cout << "dept name, or all? ";
   cin >> deptName;
  if(deptName == "all")
    {
      forCollegeDFW(college);
  } // end of if(deptName == "all")
  
  else
  {
     bool check = false;
    cout << "dfw threshold? " ;
    cin  >> threshold;
      
    if(checkDepartmentInCollege(deptName, college)) 
      {
      
     for(const Dept& dept : college.Depts)
      {
        if(dept.Name == deptName){
          for(const Course& course : dept.Courses)
             {
             theCourses.push_back(course); // put all the courses in theCourses vector
            }
          }
      }

         //sort courses vector
    sort(theCourses.begin(), theCourses.end(), 
        [](const Course& d1, const Course& d2)
        { 
          //variable to be passed as argument to GetDFWRate
          int DFW = 0;
          int N = 0;
          if (GetDFWRate(d1,DFW,N) > GetDFWRate(d2,DFW,N))
            return true;
          else if (GetDFWRate(d1,DFW,N) < GetDFWRate(d2,DFW,N))
            return false;
           // same DFW, look at Deptments:
            else if (d1.Dept < d2.Dept)
              return true;
            else if (d1.Dept > d2.Dept)
              return false;
          else // same dept, look at course #:
            if (d1.Number < d2.Number)
              return true;
            else if (d1.Number > d2.Number)
              return false;
            else // same course #, look at section #:
              if (d1.Section < d2.Section)
                return true;
              else  
                return false;
        }
      ); 


          // go through the theCourses vector and  print the information of each course
          for( const Course& course : theCourses)
          {   int DFW = 0;
              int N = 0;
             
              theDFWRate = GetDFWRate(course, DFW, N);
              // check if the DFW of each course is greater than threshold
              // and if it is print out the course summary 
             if(theDFWRate > threshold)
             {
               check = true;
                cout << course.Dept << " "<< course.Number << " (section " << course.Section << "): " << course.Instructor << endl;
                cout << " # students: " << course.getNumStudents() << endl;

                if(course.getGradingType() == Course::Letter){
                   cout << " course type: " << "letter" << endl;
                  }

                else if(course.getGradingType() == Course::Satisfactory){
                           cout << " course type: " << "satisfactory" << endl;
                      }

                  else {
                        cout << " course type: " << "unknown" << endl;
                       }
                  //get and print grade distribution
                  GradeStats d; // create a GradeStats object
                  d = GetGradeDistribution(course);
                  cout << " grade distribution (A-F): " << d.PercentA << "%, "  << d.PercentB << "%, " << d.PercentC << "%, "; 
                  cout <<  d.PercentD <<  "%, " << d.PercentF << "%" <<  endl;
                  cout << " DFW rate: " << theDFWRate << "%" << endl;
                } // end of (theDFWRate > threshold)
             } // end of  for loop
      
            if(check == false) {
                cout << "**none found" << endl;
              }

       } // end of if(checkDepartmentInCollege(deptName, college)) 
    
    else {
          cout << "**dept not found" <<  endl; 
      
          }
    
  } // end of else statement
  
} // end theDFW()


//Fuction to check a letterB for a college
 void collegeLetterB( College college)
 {
   double  theDFWRate;
   double threshold;
   cout << "letter B threshold? " ;
   cin  >> threshold;
   
   if(checkletterBthreshold(threshold, college) == false)
      {
        cout << "**none found" << endl;
      }
   
  else {
   vector<Course> theCourses; 
   for(const Dept& dept : college.Depts)
      {
        
        for(const Course& course : dept.Courses)
        {
         theCourses.push_back(course); // put all the courses in theCourses vector
        }
      }
     
       //sort courses vector
      sort(theCourses.begin(), theCourses.end(), 
      [](const Course& d1, const Course& d2)
      { 
        if ((GetGradeDistribution(d1).PercentB)  > (GetGradeDistribution(d2).PercentB))
          return true;
        else if ((GetGradeDistribution(d1).PercentB) < (GetGradeDistribution(d2).PercentB))
          return false;
         // same DFW, look at Deptments:
          else if (d1.Dept < d2.Dept)
            return true;
          else if (d1.Dept > d2.Dept)
            return false;
        else // same dept, look at course #:
          if (d1.Number < d2.Number)
            return true;
          else if (d1.Number > d2.Number)
            return false;
          else // same course #, look at section #:
            if (d1.Section < d2.Section)
              return true;
            else  
              return false;
      }
    ); 
    
    
    // go through the theCourses vector and  print the information of each course
    for( const Course& course : theCourses)
    {   int DFW = 0;
        int N = 0;
        GradeStats d = GetGradeDistribution(course);
        theDFWRate = GetDFWRate(course, DFW, N);
        // check if the DFW of each course is greater than threshold
        // and if it is print out the course summary 
       if(d.PercentB > threshold)
       {
          cout << course.Dept << " "<< course.Number << " (section " << course.Section << "): " << course.Instructor << endl;
          cout << " # students: " << course.getNumStudents() << endl;

          if(course.getGradingType() == Course::Letter){
             cout << " course type: " << "letter" << endl;
            }
         
          else if(course.getGradingType() == Course::Satisfactory){
                     cout << " course type: " << "satisfactory" << endl;
                }
         
            else {
                  cout << " course type: " << "unknown" << endl;
                 }
            //get and print grade distribution
            cout << " grade distribution (A-F): " << d.PercentA << "%, "  << d.PercentB << "%, " << d.PercentC << "%, "; 
            cout <<  d.PercentD <<  "%, " << d.PercentF << "%" <<  endl;
            cout << " DFW rate: " << theDFWRate << "%" << endl;
          } // end of (theDFWRate > threshold)
       } // end of for loop
  }
 } // end of collegeLetterB( College college)




//This function performs a department or college-wide search for all courses whose percentage 
//of letter B grades exceeds a threshold input by the user
//
void letterB(College college){
   double threshold;
   double  theDFWRate;
   string deptName;
   vector<Course> theCourses; 
   cout << "dept name, or all? ";
   cin >> deptName;
  if(deptName == "all")
    {
      collegeLetterB(college);
  } // end of if(deptName == "all")
  
 
  else
  {
    cout << "letter B threshold? " ;
    cin  >> threshold;
    
    
    
      if(checkDepartmentInCollege(deptName, college)) 
        {
            if(checkletterBthresholdforDepts(threshold, college, deptName) == false)
          {
            cout << "**none found" << endl;
          }
        
        else { 
         for(const Dept& dept : college.Depts)
          {
            if(dept.Name == deptName){
              for(const Course& course : dept.Courses)
                 {
                 theCourses.push_back(course); // put all the courses in theCourses vector
                }
              }
          }

             //sort courses vector
        sort(theCourses.begin(), theCourses.end(), 
            [](const Course& d1, const Course& d2)
            {  
              if ((GetGradeDistribution(d1).PercentB)> (GetGradeDistribution(d2).PercentB))
                return true;
              else if ((GetGradeDistribution(d1).PercentB )< (GetGradeDistribution(d2).PercentB))
                return false;
               // same DFW, look at Deptments:
                else if (d1.Dept < d2.Dept)
                  return true;
                else if (d1.Dept > d2.Dept)
                  return false;
              else // same dept, look at course #:
                if (d1.Number < d2.Number)
                  return true;
                else if (d1.Number > d2.Number)
                  return false;
                else // same course #, look at section #:
                  if (d1.Section < d2.Section)
                    return true;
                  else  
                    return false;
            }
          ); 


              // go through the theCourses vector and  print the information of each course
              for( const Course& course : theCourses)
              {   int DFW = 0;
                  int N = 0;
                  GradeStats d = GetGradeDistribution(course);
                  theDFWRate = GetDFWRate(course, DFW, N);
                  // check if the DFW of each course is greater than threshold
                  // and if it is print out the course summary 
                 if(d.PercentB > threshold)
                 {
                    cout << course.Dept << " "<< course.Number << " (section " << course.Section << "): " << course.Instructor << endl;
                    cout << " # students: " << course.getNumStudents() << endl;

                    if(course.getGradingType() == Course::Letter){
                       cout << " course type: " << "letter" << endl;
                      }

                    else if(course.getGradingType() == Course::Satisfactory){
                               cout << " course type: " << "satisfactory" << endl;
                          }

                      else {
                            cout << " course type: " << "unknown" << endl;
                           }
                      //get and print grade distribution
                      cout << " grade distribution (A-F): " << d.PercentA << "%, "  << d.PercentB << "%, " << d.PercentC << "%, "; 
                      cout <<  d.PercentD <<  "%, " << d.PercentF << "%" <<  endl;
                      cout << " DFW rate: " << theDFWRate << "%" << endl;
                    } // end of (theDFWRate > threshold)
                 } // end of  for loop
        }
       } // end of (checkDepartmentInCollege(deptName, college))

      else {
            cout << "**dept not found" << endl; 
            }
   }// end of else stacement
 
} // end of  letterB()*/


// function to check if the course has grading type letter

bool checkLetter( Course j) {
  bool check = false;
  if( j.getGradingType() ==  Course::Letter){
   check =  true;
  }
  
  return check;
}

// Function to find GPA of each department
  double calculateDeptGPA(Dept dept){
    // declare and initialize variables  to store number of each course
    int numberA = 0;
    int numberB = 0;
    int numberC = 0;
    int numberD = 0;
    int numberF = 0;
    double theGPA =  0;
    int numStudents = 0;
    int totalNumGrades;
    double the_GPA;
    totalNumGrades = count_if(dept.Courses.begin(), dept.Courses.end(), 
                                     checkLetter);

    //get the total number of each course
    for(const Course& j : dept.Courses) {
      if( j.getGradingType() ==  Course::Letter){
        numberA += j.NumA;
        numberB += j.NumB;
        numberC += j.NumC;
        numberD += j.NumD;
        numberF += j.NumF; 
        numStudents +=j.getNumStudents();
        theGPA += ((4*numberA) + (3*numberB) + (2*numberC) + (1*numberD) + (0*numberF))/(double)numStudents;
      }
    }
    
    the_GPA = theGPA/totalNumGrades;
    
    return the_GPA;
    
  } // end of (Dept dept) function
  

// Function to find GPA of each course in a department
  double calculateCourseGPA(Course j){
    // declare and initialize variables  to store number of each course
    int numberA = 0;
    int numberB = 0;
    int numberC = 0;
    int numberD = 0;
    int numberF = 0;
    double theGPA =  0;
    int numStudents;
  
    //check  if the grading type is letter and calculate the average GPA of each course
    if( j.getGradingType() ==  Course::Letter){
        numberA = j.NumA;
        numberB = j.NumB;
        numberC = j.NumC;
        numberD = j.NumD;
        numberF = j.NumF; 
        numStudents = j.getNumStudents();
        theGPA = ((4*numberA) + (3*numberB) + (2*numberC) + (1*numberD) + (0*numberF))/(double)numStudents;
    }
    return theGPA;
    
  } // end of (Dept dept) function
  


//The average command performs a department or college-wide sort by average GPA. 
//If all departments is chosen, the departments in the college are listed in descending order by average GPA.

void getAverage(College college)
{
  
    double the_GPA;
    string deptName;
    vector<Dept> theDepartments; 
    vector<Course> theCourses;
    cout << "dept name, or all? ";
    cin >> deptName;

    // traverse college.Depts vector and push_back() the departments in theDepartments
    for(const Dept& dept : college.Depts) {
       theDepartments.push_back(dept); // store the departments
    } // end of for loop

    // check if the user enters all
    if(deptName == "all") {

      //Now sort then vector of departments in descending order by GPA
       sort( theDepartments.begin(),  theDepartments.end(), 
          [](const Dept& d1, const Dept& d2)
          {  
            if (calculateDeptGPA(d1) > calculateDeptGPA(d2))
               return true;
            else if (calculateDeptGPA(d1) < calculateDeptGPA(d2))
                return false;
                else  
                  return false;
          }
        ); 

      //Print departments GPAs 

      for(const Dept& j:theDepartments ){
        the_GPA = calculateDeptGPA(j);
        cout << "Overall GPA for " << j.Name << ": " << the_GPA << endl;
      }  
    } // end if (deptName == "all")
  
  
  else {
     if(checkDepartmentInCollege(deptName, college)) 
      {
       //Go through the vector and check for departments that are equal to the user input
        for(const Dept& dept : college.Depts)
        {
          if(dept.Name == deptName){
            for(const Course& course : dept.Courses)
               {
               theCourses.push_back(course); // put all the courses in theCourses vector
              }
            }
        }

      //Now sort then vector of departments in descending order by GPA
          sort(theCourses.begin(), theCourses.end(), 
        [](const Course& d1, const Course& d2)
        {  
          if (calculateCourseGPA(d1) > calculateCourseGPA(d2))
            return true;
          else if (calculateCourseGPA(d1) < calculateCourseGPA(d2))
            return false;
           // same GPA, look at Deptments:
            else if (d1.Dept < d2.Dept)
              return true;
            else if (d1.Dept > d2.Dept)
              return false;
          else // same dept, look at course #:
            if (d1.Number < d2.Number)
              return true;
            else if (d1.Number > d2.Number)
              return false;
            else // same course #, look at section #:
              if (d1.Section < d2.Section)
                return true;
              else  
                return false;
        }
      ); 


        //Print departments GPAs 

        for(const Course& j:theCourses ){
          the_GPA = calculateCourseGPA(j);
          cout << "Overall GPA for " << j.Dept << " " << j.Number << "(" << j.Section << " )" <<": " << the_GPA << endl;
        }  
     } // end of (checkDepartmentInCollege(deptName, college))
    
     else {
          cout << "**dept not found"; 
        }
    
  } // end of else
  
} // end getAverage(College college)




int main()
{
    string filename;

    cout << std::fixed;
    cout << std::setprecision(2);
    string theUserInput;
    //
    // 1. Input the filename and then the grade data:
    //
    cin >> filename;
    // filename = "fall-2018.csv";

    College college = InputGradeData(filename);

    // 2. TODO: print out summary of the college
    CollegeLevelSummary(college);
    cout << endl;
    //
    // 3. TODO: Start executing commands from the user:
    // DEFINE your own functions
    while(1){
      
        cout << "Enter a command> ";
        cin >> theUserInput;
        if( theUserInput == "#" ){
          exit(0);
        }
      
        else {
              if(theUserInput == "summary"){
                getSummary(college);
              }
               
          else if (theUserInput == "search"){
             doSearch(college);
            }
          
          else if (theUserInput == "satisfactory"){
             satisfactory(college);
            }
          
           else if (theUserInput == "dfw"){
             theDFW(college);
            }
          
          else if (theUserInput == "letterB"){
             letterB(college);
            }
          else if (theUserInput == "average"){
             getAverage(college);
            }
             else {
              cout << "**unknown command" << endl;
              
          } // end of switch statement
        }
    } // end of while loop

    //
    // done:
    //
    return 0;
}
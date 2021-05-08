//
//  main.cpp
//  SearchEngine
//
//  Created by Habeeba Sakr on 11/25/20.
//  Copyright © 2020 Habeeba Sakr. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#define V 5
using namespace std;

unordered_map<string,unordered_map<string,int> > webgraph;
unordered_map<string,unordered_map<string,int> >  keyword;
unordered_map<string,int> impressions;
unordered_map<int,string> results;
unordered_map<string,int> clicks;
unordered_map<string,float> pagerank;

vector <string> dest;

void FilesOut()
{
    ofstream f;
    f.open("/Users/habeebasakr/Desktop/SearchEngine/SearchEngine/Impressions.txt");
    for (auto const& i : impressions) {
        f << i.first<<","<<i.second<<clicks[i.first]<<endl;
        
        
    }
    
}

void print_map(std::unordered_map<string,unordered_map<string,int> >  const &m)
{for (auto const& i : m) {
        for (auto const& j : i.second) {
            std::cout << i.first << " -> " << j.first << j.second<< std::endl;
        }
    }
}
void print_map1(std::unordered_map<string,int> const &m)
{for (auto const& i : m) {
            std::cout << i.first << " -> " << i.second << std::endl;
        }
    
}
//bool compWebPages(WebPage One, WebPage Two)
//{
//    return One.CTR > Two.CTR;
//}
void PageRank()
{
    float n= webgraph.size();
    string arr[10];
    pagerank["www.test1.com"]=1/(n+1);
    pagerank["www.test2.com"]=1/(n+1);
    pagerank["www.test3.com"]=1/(n+1);
    pagerank["www.test5.com"]=1/(n+1);
    
                
    unordered_map<string,int> count;

   
        for (auto const& i : webgraph) {
            for (auto const& j : i.second) {
                for (auto const& l : pagerank)
                {
             //   std::cout << i.first << " -> " << j.first << j.second<< std::endl;
                    if(l.first == i.first)
                        count[l.first]++;
                    
                    
                    }
            }
        }
    
    for (int k=0; k<3; k++)
    {
        for (auto const& i : webgraph) {
                for (auto l : pagerank)
                {
                    
                    
                    l.second = l.second /count[l.first];
                    cout<<l.second;
                    
                    }
         
    
        
        
    }
        
    
}
}
void WebGraph()
{
    ifstream inFile;
    inFile.open("/Users/habeebasakr/Desktop/SearchEngine/SearchEngine/WebGraph.txt");
     string read;
    
    if (!inFile) {
        inFile.close();
        cout << "can't open file "<<endl;
        return;
      }
    string temp;
    string temp1;
    int count=0;
    string tempp[4]={" "," "," "," "};
    while (getline (inFile, read)){
            
       //     cout<< read << endl;
            temp=read.substr(0, read.find(","));
            temp1=read.substr(temp.length()+1, read.find("\n"));
          //  webgraph[temp][temp1]++;
         tempp[count]=temp;

        count++;
        for (int i=0; i<4; i++)
        {
            if (temp==tempp[i])
                webgraph[temp][temp1]++;
            
        }
    }
    print_map(webgraph);
    
    
}
void HandleSearch(string query, string orquery[], string andquery[])
{
    cout<<"Search Results: "<<endl;
    int    count=0;
    if (query!="")
    {
        for (auto const& i : keyword) {
            for (auto const& j : i.second) {
                
                if (j.first == query)
                {  cout<<count+1<<". "<< i.first<< endl;
                    results[count+1]=i.first;
                    count++;
                    impressions[i.first]++;
                }//   std::cout << i.first << " -> " << j.first << std::endl;
            }
        }
        
    }
    
    if (orquery[0]!="")
    {
        for (int k=0; k<2; k++)
    {
        for (auto const& i : keyword) {
            for (auto const& j : i.second) {
                
                if (j.first == orquery[k])
                {  cout<<count+1<<". "<< i.first<< endl;
                    results[count+1]=i.first;

                    count++;
                    impressions[i.first]++;

                }//   std::cout << i.first << " -> " << j.first << std::endl;
            }
        }

    }
    }
    bool check = false;
    string temp;
    if (andquery[0]!="")
    {
        for (auto const& i : keyword) {
                   for (auto const& j : i.second) {
                      
                       if ((j.first == andquery[0] || j.first == andquery[1]) && check==true )
                                            {
                                                cout<<count+1 <<". "<< temp<< endl;
                                                results[count+1]=temp;

                                                count++;
                                                check=false;
                                                impressions[i.first]++;

                                                //cout<< count+1<<"."<<temp<< endl;
                                            }
                       
                    else   if (j.first == andquery[0] || j.first == andquery[1])
                    {
                        temp=i.first;
                        check=true;
                        
                       }//   std::cout << i.first << " -> " << j.first << std::endl;
                   }
    }
    
    
}
   // DisplaySecondMenu();

}
void SearchQuery(string sq)
{
    cout <<"Please enter your search query: ";
    cin.ignore();
    getline(cin, sq);
    string query= " ";
     string orquery[2];
    string andquery[2];

        if (sq[0]=='"')
        { query = sq.substr(1, sq.find_last_of(""""));
            cout<<query;}
   
        else if (sq.find("OR")!= std::string::npos)
        {   orquery[0] = sq.substr(0, sq.find(" "));
            cout <<orquery[0]<<endl;
            orquery[1] = sq.substr(orquery[0].length()+4, sq.find("\n"));
            cout<<orquery[1]<<endl;
            
        }
          else if (sq.find("AND")!= std::string::npos)
           {   andquery[0] = sq.substr(0, sq.find(" "));
               cout <<andquery[0]<<endl;
               andquery[1] = sq.substr(andquery[0].length()+5, sq.find("\n"));
               cout<<andquery[1]<<endl;
               
           } else {
             orquery[0] = sq.substr(0, sq.find(" "));
              cout <<orquery[0]<<endl;
              orquery[1] = sq.substr(orquery[0].length()+1, sq.find("\n"));
              cout<<orquery[1]<<endl;
           }
    HandleSearch(query,orquery,andquery);
    
}

void DisplaySecondMenu()
{
    cout<<"Would you like to: " <<endl;
    cout<<"1. Choose a webpage to open  " <<endl;
    cout<<"2. New Search " <<endl;
    cout<<"3. Exit  "<<endl;
    cout <<"Type in your choice: ";
    int m;
    cin>>m;
    int n;
    
    if (m==1)
    {
        
        cout<<"choose which webpage to open"<<endl;
        cin>>n;
        cout<<results[n]<<endl;
        clicks[results[n]]++;
        cout<<"You are now viewing the webpage "<<endl;
            
        
        
    }
        
        else if (m==2)
        {
            string sq;
            SearchQuery(sq);
        }
            else if (m==3)
                return;
}


void Impressions()
{
    ifstream inFile;
    inFile.open("/Users/habeebasakr/Desktop/SearchEngine/SearchEngine/Impressions.txt");
     string read;
    
    if (!inFile) {
        inFile.close();
        cout << "can't open file "<<endl;
        return;
      }
    string temp;
    string temp1;
    int count=0;
    while (getline (inFile, read)){
            
            cout<< read << endl;
            temp=read.substr(0, read.find(","));
            temp1=read.substr(temp.length()+1, read.find("\n"));
            int m= stoi(temp1);
       // cout<<m;
            impressions[temp]=m;
            //count++;
        
         }
    
   print_map1(impressions);
    
    
}

void Keyword()
{
    ifstream inFile;
    inFile.open("/Users/habeebasakr/Desktop/SearchEngine/SearchEngine/Keyword.txt");
    string read;
    
    if (!inFile) {
        inFile.close();
        cout << "can't open file "<<endl;
        return;
      }
    string webpage;
    string temp1;
    int count=0;
    while (getline (inFile, read)){
        

        webpage=read.substr(0, read.find(","));
        read=read.substr(webpage.length()+1);
        
        
            while(read.length()>0)
            {
         //   cout<< read << endl;
                int found = read.find(",");
                
                if (found != std::string::npos)
                    temp1=read.substr(0, read.find(","));

                else
    {                   temp1=read;

           }
                if (temp1!=read)
                {
                read=read.substr(temp1.length()+1);
                } else if ( temp1==read)
                {
                    read="";
                }
                keyword[webpage][temp1]=count;
                
            count++;
            
        
            }
        
         }
    
 //   print_map(keyword);
    
}







int main(int argc, const char * argv[]) {

    cout <<"Welcome! "<<endl;
    cout <<"What would you like to do? "<<endl;
    cout <<"1. New Search "<<endl;
    cout <<"2. Exit "<<endl;
    cout <<"Type in your choice: ";
    
    int menuchoice=0;
    string searchquery;
    cin >> menuchoice;
    if (menuchoice>2 || menuchoice<1)
    {  cout<<"invalid choice"<<endl;
        return 0;
    }

    if (menuchoice==2)
        return 0;

    if (menuchoice==1)
    {
        WebGraph();
        Keyword();
        Impressions();
        SearchQuery(searchquery);
        DisplaySecondMenu();
        PageRank();
        FilesOut();
        
    }

  

    return 0;
}







#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <string>   
#include <utility>
#include <vector>   
#include <sstream>
using namespace std;
string keywordname = "jaguar";


//sorting maps
template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
    return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
std::map<B,A> flip_map(const std::map<A,B> &src)
{
    std::map<B,A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), 
                   flip_pair<A,B>);
    return dst;
}




int main(int argc, const char** argv)
{

    map <string, string> dict;
    map <string, string> googlerank,yahoorank;


    string line;
    ifstream infile1(keywordname+"_google.txt");
    
    int i=1;
    std::size_t found1,found2;

    while(std::getline(infile1, line)) 
    {
        if (line.empty())
            continue;

        std::size_t tempfound=line.find('\t');
        string num=line.substr(0,tempfound);


        found1 = line.find('\t',tempfound+1);
        if (found1!=std::string::npos)
        {
            found2 = line.find('\t',found1+1);
            string temp=line.substr(found1+1,found2-found1-1);
            string temp2=line.substr(found2+1);
            dict[temp]=temp2;
            googlerank[temp]=num;
        }
    }
    infile1.close();



    ifstream infile2(keywordname+"_yahoo.txt");
    while(std::getline(infile2, line)) 
    {
        if (line.empty())
            continue;


        std::size_t tempfound=line.find('\t');
        string num=line.substr(0,tempfound);

        found1 = line.find('\t',tempfound+1);
        if (found1!=std::string::npos)
        {
            found2 = line.find('\t',found1+1);
            string temp=line.substr(found1+1,found2-found1-1);
            string temp2=line.substr(found2+1);
            dict[temp]=temp2;

            
            yahoorank[temp]=num;
        }
    } 
    infile2.close();

    ofstream outfile("UniqueDocuments.txt");
    i=1;

    for (auto& ent : dict)
    {
        outfile<<i++<<"\t"<<ent.first << "\t-->"<<ent.second << "\n";
    }

    outfile.close();


    



    //ranking 1
    map<string, string> globalrank;
    for (auto& ent : dict)
    {
        
        if(yahoorank.find(ent.first)==yahoorank.end()) 
        {
            globalrank[googlerank[ent.first]] = ent.first;
        }
        else if(yahoorank.find(ent.first)!=yahoorank.end() && googlerank.find(ent.first)!=googlerank.end())
        {
            if (stoi(googlerank[ent.first])<=stoi(yahoorank[ent.first])) 
                globalrank[googlerank[ent.first]] = ent.first;
            else
            {
                int tempnum= std::stoi(yahoorank[ent.first]);
                while( (globalrank.find(to_string(tempnum))!= globalrank.end()) )
                {
                    tempnum++;
                }
                globalrank[to_string(tempnum)] = ent.first;
                printf("2: %d\n", tempnum);
            }
        }
    }

    for (auto& ent : dict)
    {
        if(yahoorank.find(ent.first)==yahoorank.end()) 
        {
            continue;
        }
        else if(yahoorank.find(ent.first)!=yahoorank.end() && googlerank.find(ent.first)!=googlerank.end())
        {
            continue;
        }
        else
        {
            int tempnum= std::stoi(yahoorank[ent.first]);
            while( (globalrank.find(to_string(tempnum))!= globalrank.end()) )
            {
                tempnum++;
            }
            globalrank[to_string(tempnum)] = ent.first;   
        }
    }

    map<string, string> tempmap2 = flip_map(globalrank);
    int tempvar2=2000;
    for (auto& ent : dict)
    {
        if(tempmap2.find(ent.first)==tempmap2.end())
            globalrank[to_string(tempvar2++)]=ent.first;
    }


    ofstream outfile2("ResultantRanks_A1.txt");
    i=1;

    for (auto& ent : globalrank)
    {
        outfile2<<i++ << "\t-->\t"<<ent.second << "\n";
    }

    outfile2.close();





    //ranking 2
    map<string, string> globrank;
    for (auto& ent : dict)
    {    
        if(yahoorank.find(ent.first)!=yahoorank.end() && googlerank.find(ent.first)!=googlerank.end())
        {
            if (stoi(googlerank[ent.first])<=stoi(yahoorank[ent.first])) 
            {
                int tempnum= std::stoi(googlerank[ent.first]+ yahoorank[ent.first]);
                while( (globalrank.find(to_string(tempnum))!= globalrank.end()) )
                {
                    tempnum++;
                }
                globrank[to_string(tempnum)] = ent.first;   

            }
        }
    }
    for (auto& ent : dict)
    {    
        if(yahoorank.find(ent.first)!=yahoorank.end() && googlerank.find(ent.first)!=googlerank.end())
        {
            if (stoi(googlerank[ent.first])<=stoi(yahoorank[ent.first])) 
                continue;    

            else
            {
                int tempnum= std::stoi(googlerank[ent.first]+ yahoorank[ent.first]);
                while( (globalrank.find(to_string(tempnum))!= globalrank.end()) )
                {
                    tempnum++;
                }
                globrank[to_string(tempnum)] = ent.first;  
                
            }
        }
    }

    for (auto& ent : dict)
    {    
        if(yahoorank.find(ent.first)==yahoorank.end()) 
        {
            globrank[googlerank[ent.first]+to_string(500)] = ent.first;
        }
        else if(googlerank.find(ent.first)==googlerank.end())
        {
            globrank[yahoorank[ent.first]+to_string(900)] = ent.first;
        }
    }

    map<string, string> tempmap = flip_map(globrank);
    int tempvar=2000;
    for (auto& ent : dict)
    {
        if(tempmap.find(ent.first)==tempmap.end())
            globrank[to_string(tempvar++)]=ent.first;
    }





    ofstream outfile3("ResultantRanks_A2.txt");
    i=1;

    for (auto& ent : globrank)
    {
        outfile3<<i++ << "\t-->\t"<<ent.second << "\n";
    }

    outfile3.close();

    printf("\nApproach1\n");
    float sum=0;
    for(int j=5;j<=30;j=j+5)
    {
        int ans=0;
        
        int i=1,k=1;
        ifstream infile4("Ranked_Documents.txt");
        while(std::getline(infile4, line) && i<j) 
        {
            if (line.empty())
                continue;

            k=1;
            for (auto& ent : globalrank)
            {
                if(k>j)
                    break;
                if(ent.second==line)
                {
                    ans++;
                }
                k++;
            }

            i++;

        }
        sum+=(float)ans/j;
        printf("Precision@%d = %lf\n",j, float(ans)/j);
        infile4.close();
    }
    printf("Map for Approach 1 = %lf\n", sum/6);
    
    printf("\nApproach2\n");
    sum=0;
    for(int j=5;j<=30;j=j+5)
    {
        int ans=0;
        
        int i=1,k=1;
        ifstream infile4("Ranked_Documents.txt");
        while(std::getline(infile4, line) && i<j) 
        {
            if (line.empty())
                continue;

            k=1;
            for (auto& ent : globrank)
            {
                if(k>j)
                    break;
                if(ent.second==line)
                {
                    ans++;
                }
                k++;
            }

            i++;

        }
        sum+=(float)ans/j;
        printf("Precision@%d = %lf\n",j, float(ans)/j);
        
        infile4.close();
    }
    printf("Map for Approach 2 = %lf\n", sum/6);
    





    ifstream infile5("Ranked_Documents.txt");
    int temp1=1;
    int ans=0;
    while(std::getline(infile5, line)) 
    {
        int temp2=1,flag=0;
        if (line.empty())
                continue;

        for (auto& ent : globalrank)
        {
            if(ent.second==line)
            {
                flag=1;
                break;
            }
            temp2++;
        }
        if(flag==1)
        {
            ans+=(temp1-temp2)*(temp1-temp2);
        }
        temp1++;
    }
    float coeff= 1- ((float)(6*ans)/((temp1) * ((temp1*temp1)-1)));
    printf("\nSpearman's Rank Correlation Coefficient for Approach 1 = %lf\n", coeff);
    infile5.close();


    ifstream infile6("Ranked_Documents.txt");
    temp1=1;
    ans=0;
    while(std::getline(infile6, line)) 
    {
        int temp2=1,flag=0;
        if (line.empty())
                continue;

        for (auto& ent : globrank)
        {
            if(ent.second==line)
            {
                flag=1;
                break;
            }
            temp2++;
        }
        if(flag==1)
        {
            ans+=(temp1-temp2)*(temp1-temp2);
        }
        temp1++;
    }
    coeff= 1- ((float)(6*ans)/((temp1) * ((temp1*temp1)-1)));
    printf("\nSpearman's Rank Correlation Coefficient for Approach 2 = %lf\n\n", coeff);
    infile6.close();


    return 0;
}
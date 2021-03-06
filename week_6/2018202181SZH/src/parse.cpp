#include"unit.h"
#include<iostream>
#include<regex>
#include<queue>              
#include<string>
#include<set>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;

extern string sensitive_words[100];
void website::parseUrls(string &src,set<string> &store){
    regex  pattern("(href=|HREF=)((\"(.*?)\")|(\'(.*?)\')|(([^\"\']*?)>))");
    smatch urls;
    while(regex_search(src,urls,pattern)){
        
       string temp = urls[2].str();
       string root1 = "http://";
       string root2 = "https://";

       if(temp.find(root1) != temp.npos){
           int num_te = temp.find(root1);
           temp.erase(num_te,root1.size()); 
       }
        if(temp.find(root2) != temp.npos){
           int num_te = temp.find(root2);
           temp.erase(num_te,root2.size()); 
       }
       if(temp[0] == '\''||temp[0] == '\"')  //删除多余的“ ‘‘ “
       {
           int n = temp.size();
       temp.erase(n-1,1);temp.erase(0,1);
       }
       int flag = 0;
       for(int i = 0; sensitive_words[i] != "words_end"; i++){

           if(temp.find(sensitive_words[i]) != temp.npos){
               flag++;  break;
           }
       }
       if(!flag){
           if(temp[0] != '/' ){
           string ref = current_url;
           int nn = ref.size();
           if(ref.find("\\")!=ref.npos){
               while(ref[nn-1] != '/'){
               ref.erase(nn-1);
               nn --;
           }
           temp = ref + temp;
           }
           
       }
    }
       if (!flag)   store.insert(temp);
        src = urls.suffix();
    }
    
}
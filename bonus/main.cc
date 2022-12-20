#include <iostream>
#include <string>
#include <map>
#include <string.h>
#include <vector>
#include <algorithm>
#include <cctype>
#include <typeinfo>
#include <queue>
#include <memory>
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
using namespace std;

struct Node
{
    string data;
    int i;
    int code=-1;
    Node* left = nullptr, *right = nullptr;
    Node() {};
    Node(string data, int i): data(data),i(i) {};
};
Node* insin(Node* root, vector<string> const &v,bool inbracks);
Node* insmult(Node* root, vector<string> const &v,bool inbracks);
inline bool isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

   char * p;
   strtol(s.c_str(), &p, 10);
   return (*p == 0);
}
Node* CreateNode(char data)
{
	Node* newNode = new Node();
	if (!newNode) {
		cout << "Memory error\n";
		return NULL;
	}
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}
void inorder2(Node* root){
    if (root == nullptr) {
        return;
    }
    inorder2(root->left);
    cout<<root->data<<" r2"<<endl;
    inorder2(root->right);
}
void inorder3(Node* root){
    if (root == nullptr) {
        return;
    }
    inorder3(root->right);
    inorder3(root->left);    
}
tuple<vector<vector<int>>,map<int,bool>,int> bcp(vector<vector<int>> in,map<int,bool> a,int setfalse){
    vector<vector<int>> out;
    bool stillcan=false;
    bool modified=false;
    for (auto & element : in) {
        if(element.size()==1){
            int pq=element[0]; //value of list with size 1
            modified=true;
            int pqneg=element[0]*(-1);
            if(pq>0){ //store the mod value in dict a
                if(!a.count(pq)){
                    a[pq]=true;
                }	
            }
            else{
                if(!a.count(pqneg)){
                    a[pqneg]=false;
                }	
            }
            for(auto elemout: in){
                if (count(elemout.begin(),elemout.end(),pqneg)>0){
                    vector<int> tmpvec;
                    for (auto num:elemout){
                        if((num!=pqneg)&&(elemout.size()>1)){
                            tmpvec.push_back(num);
                        }   
                    }
                    if((elemout[0]==pqneg)&&(elemout.size()==1)){
                            setfalse=-1;
                            break;
                    }   
                    out.push_back(tmpvec);
                }
                else if(count(elemout.begin(),elemout.end(),pq)==0){
                    out.push_back(elemout);
                } 
            }
            break;
        }
    }
  
    for (auto & element2 : out) 
    {
        if (element2.size()==1){
            stillcan=true;
        }
    }
    if ((stillcan==true)&&(setfalse!=-1)&&(setfalse!=1)){
        return bcp(out,a,setfalse);
    }
    else if((out.size()==0)&&(modified==true)&&(setfalse==-1)){
        return make_tuple(out,a,-1);
    }
    else if((out.size()==0)&&(modified==true)){
        return make_tuple(out,a,1);
    }
    else if((out.size()==0)&&(modified==false)){
        return make_tuple(in,a,0);
    }
    else{
        return make_tuple(out,a,setfalse);
    }
}
bool dpll(vector<vector<int>> cnf, map<int,bool> amap){
	vector<vector<int>> checkbcp;
    int setval;
  	tie(checkbcp,amap,setval)=bcp(cnf,amap,setval);
    if (setval==1){
    	return true;
    }
    else if (setval==-1){
    	return false;
    }
    map<int,int>checkvar;
    for(auto xvec:checkbcp){
        for(auto yvec:xvec){
            int mapcheck=0;
            if (yvec>0){
                mapcheck=yvec;
            }
            else if (yvec<0){
                mapcheck=(-1)*yvec;
            }
            if ((mapcheck!=0)&&(!checkvar.count(mapcheck))){
                checkvar[mapcheck]=1; //make map of variables
            }
        }
    }
    int pchoice;
    for (const auto&emap:checkvar){
        pchoice = emap.first;
        int pchoiceneg = (-1)*pchoice;
        amap[pchoice]=true;
        vector<vector<int>> dpout;
        for (auto eachvec:checkbcp){
            if (count(eachvec.begin(),eachvec.end(),pchoiceneg)>0){
                vector<int> tmpvec;
                for (auto num:eachvec){
                    if((num!=pchoiceneg)&&(eachvec.size()>1)){
                        tmpvec.push_back(num);
                    }
                }
                if((eachvec[0]==pchoiceneg)&&(eachvec.size()==1)){
                        return false;
                }
                dpout.push_back(tmpvec);
            }
            else if ((eachvec[0]==pchoice)&&(eachvec.size()==1)&&(checkbcp.size()==1)){
                return true;
            } 
            else if(count(eachvec.begin(),eachvec.end(),pchoice)==0){
                dpout.push_back(eachvec);
            }
        }
        bool dppos = dpll(dpout, amap);
        vector<vector<int>> dpout2;
        amap[pchoice]=false;
        for (auto eachvec:cnf){
    	    if (count(eachvec.begin(),eachvec.end(),pchoice)>0){
                vector<int> tmpvec;
                for (auto num:eachvec){
                    if((num!=pchoice)&&(eachvec.size()>1)){
                        tmpvec.push_back(num);
                    }
                }
                if((eachvec[0]==pchoice)&&(eachvec.size()==1)){
                        return false;
                }
                dpout2.push_back(tmpvec);
            }
            else if ((eachvec[0]==pchoiceneg)&&(eachvec.size()==1)&&(checkbcp.size()==1)){
                return true;
            } 
            else if(count(eachvec.begin(),eachvec.end(),pchoiceneg)==0){
                dpout2.push_back(eachvec);
            }
        }
        if(dppos){
            return true;
        }
        else{
            return dpll(dpout2, amap);
        }
    }
    //return false;
}
vector<vector<int>> namenodes(Node* root){
    map<string, int> namedcodes;
    queue<Node*> q;
    q.push(root);
    int counter=1;
    while (q.size()>0){
        Node* curnode;
        curnode = q.front();
        q.pop();
        if ((isInteger(curnode->data)&&!namedcodes.count(curnode->data)&&(curnode->code==-1))){
            curnode->code=counter;
            namedcodes[curnode->data] = counter;
            counter+=1;
        }
        else if((curnode->data=="+")||(curnode->data=="*")||(curnode->data=="-")){
            curnode->code=counter;
            counter+=1;
        }
        else if(namedcodes.count(curnode->data)){
            curnode->code = namedcodes[curnode->data];
        }
        if (curnode->left!=nullptr){
            q.push(curnode->left);
        }
        if (curnode->right!=nullptr){
            q.push(curnode->right);
        }
    }
    queue<Node*> q2;
    q2.push(root);
    int counter2=1;
    vector<vector<int>> vresfinal;
    while (q2.size()>0){
        Node* curnode2;
        curnode2 = q2.front();
        vector<vector<int>> vres;
        q2.pop();
        if ((curnode2->data=="+")){
            vresfinal.push_back({curnode2->code*(-1), curnode2->left->code,curnode2->right->code});
            vresfinal.push_back({curnode2->left->code*(-1), curnode2->code});
            vresfinal.push_back({curnode2->right->code*(-1), curnode2->code});
        }
        else if ((curnode2->data=="*")){
            vresfinal.push_back({curnode2->code*(-1), curnode2->left->code});
            vresfinal.push_back({curnode2->code*(-1), curnode2->right->code});
            vresfinal.push_back({curnode2->left->code*(-1), curnode2->right->code*(-1),curnode2->code});
        }
        else if ((curnode2->data=="-")){
            vresfinal.push_back({curnode2->code*(-1), curnode2->left->code*(-1)});
            vresfinal.push_back({curnode2->code, curnode2->left->code});   
        }
        if (curnode2->left!=nullptr){
            q2.push(curnode2->left);
        }
        if (curnode2->right!=nullptr){
            q2.push(curnode2->right);
        }
    }
    vresfinal.push_back({1});
    return vresfinal;
}
Node* insmult(Node* root, vector<string> const &v,bool inbracks){
    Node* cent;
    if (v[v.size()-1]==")"){
        int b2count=0;
        int bind=v.size()-1;
        bool found=false;
        while(bind>0){
            if(v[bind]=="("){
                b2count-=1;
            }
            else if(v[bind]==")"){
                b2count+=1;
            }
            if((b2count==0)&&(v[bind]=="*")){
                found=true;
                break;
            }
            bind-=1;//bind points to index of * or index 0
        }
        if (found==false){
            if (v[0]=="-"){
                auto first = v.cbegin() + 2;
                auto last = v.cbegin()+v.size()-1;
                vector<string> v2(first,last);
                cent = new Node(v[0],0);
                cent->left=insin(root,v2,true);
            }
            else{
                auto first = v.cbegin() + 1;
                auto last = v.cbegin()+v.size()-1;
                vector<string> v2(first,last);
                cent = insin(root,v2,true); 
            }
        }
        else{
            if(v[bind+1]=="-"){
                cent = new Node(v[bind],0);
                cent->right =new  Node(v[bind+1],0);
                auto first = v.cbegin() + bind+2;
                auto last = v.cbegin()+v.size();
                vector<string> v2(first,last);
                cent->right->left = insin(root,v2,true);
            }
            else{
                cent =new  Node(v[bind],0);
                auto first = v.cbegin() + bind+2;
                auto last = v.cbegin()+v.size()-1;
                vector<string> v2(first,last);
                cent->right = insin(root,v2,true); 
            }
            
            if(bind>2){
                auto first = v.cbegin();
                auto last = v.cbegin()+bind;
                vector<string> v2(first,last);
                cent->left = insmult(root,v2,inbracks);
            }
            else{
                if (v[0]=="-"){
                    cent->left = new Node(v[0],0);                    
                    cent->left->left = new Node(v[1],0);
                }
                else{
                    cent->left =new  Node(v[0],0);
                }    
            }
        }
    }
    else if (isInteger(v[v.size()-1])){
        int bind;
        if (v[v.size()-2]=="-"){
            bind =-3;
            cent =new  Node(v[v.size()-3],0);
            cent->right =new  Node(v[v.size()-2],0);
            cent->right->left =new  Node(v[v.size()-1],0);
        }
        else{
            bind =-2;
            cent =new  Node(v[v.size()-2],0);
            cent->right =new  Node(v[v.size()-1],0);
        }                
        if((v.size()+bind)>2){
            auto first = v.cbegin();
            auto last = v.cbegin()+v.size()+bind;
            vector<string> v2(first,last);
            cent->left = insmult(root,v2,inbracks);
        }
        else{
            if ((v.size()+bind)==2){
                cent->left = new Node(v[0],0);
                cent->left->left = new Node(v[1],0);                
            }
            else{
                cent->left = new Node(v[0],0);
            }
            
        }
        
    }
    return cent;
}
Node* insin(Node* root, vector<string> const &v,bool inbracks){
    Node* cent;
    if(v.size()>3){
        if (v[0]=="-"){
            if (isInteger(v[1])){
                if (v[2]=="+"){
                    cent  = new Node(v[2],0);
                    cent->left = new Node(v[0],0);
                    cent->left->left = new Node(v[1],0);;
                    auto firstq2 = v.cbegin()+3;
                    auto lastq2 = v.cbegin()+v.size();
                    vector<string> v2q2(firstq2,lastq2);
                    cent->right = insin(root, v2q2,inbracks);
                }
                else if (v[2]=="*"){
                    int negdig=2;
                    int negdigcount=0;
                    while (negdig<v.size()&&!((v[negdig]=="+")&&(negdigcount==0))){
                        if (v[negdig]=="("){
                            negdigcount+=1;
                        }
                        else if (v[negdig]==")"){
                            negdigcount-=1;
                        }
                        negdig+=1;
                    }
                    if (negdig==(v.size())){                
                        cent = insmult(root, v,inbracks);                
                    }
                    else{
                        cent  = new Node(v[negdig],0);
                        auto firstq = v.cbegin();
                        auto lastq = v.cbegin()+negdig;
                        vector<string> v2q(firstq,lastq);
                        cent->left = insmult(root, v2q,inbracks);
                        auto firstq2 = v.cbegin()+negdig+1;
                        auto lastq2 = v.cbegin()+v.size();
                        vector<string> v2q2(firstq2,lastq2);
                        cent->right = insin(root, v2q2,inbracks);
                    }
                }
            }
            else if (v[1]=="("){
                int negind = 2;
                int negcount=1;
                bool negfound=false;
                while ((negcount!=0)&&negind<v.size()){
                    if (v[negind]=="("){
                        negcount+=1;
                    }
                    else if (v[negind]==")"){
                        negcount-=1;
                    }
                    negind+=1;
                }
                if (negind==(v.size())){
                    cent  = new Node(v[0],0);
                    auto firstq = v.cbegin()+1;
                    auto lastq = v.cbegin()+negind;
                    vector<string> v2q(firstq,lastq);
                    cent->left = insin(root, v2q,inbracks);
                }
                else if (v[negind]=="+"){
                    cent  = new Node(v[negind],0);
                    auto firstq = v.cbegin()+1;
                    auto lastq = v.cbegin()+negind;
                    vector<string> v2q(firstq,lastq);
                    cent->left = new Node(v[0],0);
                    cent->left->left = insin(root, v2q,inbracks);
                    auto firstq2 = v.cbegin()+negind+1;
                    auto lastq2 = v.cbegin()+v.size();
                    vector<string> v2q2(firstq2,lastq2);
                    cent->right = insin(root, v2q2,inbracks);
                }
                else if (v[negind]=="*"){
                    negcount=0;
                    bool negfound=false;
                    while ((negind<v.size())&&!((v[negind]=="+")&&(negcount==0))){
                        if (v[negind]=="("){
                            negcount+=1;
                        }
                        else if (v[negind]==")"){
                            negcount-=1;
                        }
                        negind+=1;
                    }
                    if (negind==(v.size()-1)){
                        cent = insmult(root, v,inbracks);
                    }
                    else{
                        cent  = new Node(v[negind],0);
                        auto firstq = v.cbegin()+1;
                        auto lastq = v.cbegin()+negind;
                        vector<string> v2q(firstq,lastq);
                        cent->left = insmult(root, v2q,inbracks);
                        auto firstq2 = v.cbegin()+negind+1;
                        auto lastq2 = v.cbegin()+v.size();
                        vector<string> v2q2(firstq2,lastq2);
                        cent->right = insin(root, v2q2,inbracks);
                    }
                    
                }
            }
            
        }
        else if(v[0]=="("){
            int bind = 1;
            int b2count=1;
            while(bind<v.size()-1){
                if(v[bind]=="("){
                    b2count+=1;
                }
                else if(v[bind]==")"){
                    b2count-=1;
                }
                if(b2count==0){
                    break;
                }
                bind+=1;
            }
            if (bind==(v.size()-1)){
                auto first = v.cbegin() + 1;
                auto last = v.cbegin()+bind;
                vector<string> v2(first,last);
                cent = insin(root,v2,inbracks);
            }
            else if((bind+1)<v.size()&&(v[bind+1]=="+")){
                cent = new Node(v[bind+1],0);
                auto first = v.cbegin() + 1;
                auto last = v.cbegin()+bind;
                vector<string> v2(first,last);
                cent->left = insin(root,v2,true);
                auto first2 = v.cbegin() + bind+2;
                auto last2= v.cbegin()+v.size();
                vector<string> v3(first2,last2);
                cent->right = insin(root,v3,inbracks);
            }
            else if((bind+1)<v.size()&&(v[bind+1]=="*")){
                bool found=false;
                int brcount=0;
                int brind=bind+1;
                while(brind<v.size()){
                    if(v[brind]=="("){
                        brcount+=1;
                    }
                    else if(v[brind]==")"){
                        brcount-=1;
                    }
                    if((brcount==0)&&(v[brind]=="+")){
                        found=true;
                        break;
                    }
                    brind+=1;
                }
                if(found==true){
                    cent = new Node(v[brind],0);
                    auto first = v.cbegin();
                    auto last = v.cbegin()+brind;
                    vector<string> v2(first,last);
                    cent->left = insmult(root,v2,inbracks);
                    auto first2 = v.cbegin() + brind+1;
                    auto last2 = v.cbegin()+v.size();
                    vector<string> v3(first2,last2);
                    cent->right = insin(root,v3,inbracks);
                }
                else{
                    cent = insmult(root,v,inbracks);
                }
            }
            
        }
        else if(isInteger(v[0])){
            int sind=2;
            if(v[1]=="*"){
                bool found=false;
                int brcount=0;
                int brind=1;
                while(brind<v.size()-1){
                    if(v[brind]=="("){
                        brcount+=1;
                    }
                    else if(v[brind]==")"){
                        brcount-=1;
                    }
                    if((brcount==0)&&(v[brind]=="+")){
                        found=true;
                        break;
                    }
                    brind+=1;
                }
                if(found==true){
                    cent = new Node(v[brind],0);
                    auto first = v.cbegin();
                    auto last = v.cbegin()+brind;
                    vector<string> v2(first,last);
                    cent->left = insmult(root,v2,true);
                    auto first2 = v.cbegin() + brind+1;
                    auto last2 = v.cbegin()+v.size();
                    vector<string> v3(first2,last2);
                    cent->right = insin(root,v3,inbracks);
                }
                else{
                    cent = insmult(root,v,inbracks);
                }
            }
            else if(v[1]=="+"){
                cent = new Node(v[1],0);
                cent->left = new Node(v[0],0);
                auto first2 = v.cbegin() + 2;
                auto last2 = v.cbegin()+v.size();
                vector<string> v3(first2,last2);
                cent->right = insin(root,v3,inbracks);
            }
        }
        else if(v[0]=="+"){
            cent = new Node(v[0],0);
            if (root==nullptr){
                root = cent;
            }
            auto first = v.cbegin() + 1;
            auto last = v.cbegin()+v.size();
            vector<string> v3(first,last);
            cent->right = insin(root,v3,inbracks);
        }
    }
    else{
        if (v.size()==1){
            cent = new Node(v[0],0);
        }
        else if((v.size()>1)&&((v[0]=="+")||(v[0]=="*"))&&isInteger(v[1])){
            cent = new Node(v[0],0);
            cent->right = new Node(v[1],1);
        }
        else if ((v.size()>2)&&((v[0]=="+")||(v[0]=="*"))&&(v[1]=="-")){
            cent = new Node(v[0],0);
            cent->right = new Node(v[1],1);
            cent->right->left = new Node(v[2],2);
        }
        else if ((v.size()>2)&&((v[1]=="+")||(v[1]=="*"))){
            cent = new Node(v[1],0);
            cent->right = new Node(v[2],1);
            cent->left = new Node(v[0],2);
        }
        else if (v[0]=="("){
            cent = new Node(v[1],0);
        }
        
        else if ((v.size()==2)&&(v[0]=="-")){
            cent = new Node(v[0],0);
            cent->left = new Node(v[1],1);
        }
        
        if ((root==nullptr)&&(inbracks==false)){
            root = cent;
        } 
    }
    return cent;
}
Node* constructBST(vector<string> const &keys)
{
    Node* root = nullptr;
    root = insin(root,keys,false);
    return root;
}
vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}
vector<vector<int>> bcp(vector<vector<int>> in){
    vector<vector<int>> out;
    for (auto & element : in) 
  {
    if(element.size()==1)
    {
        cout << element[0] << " ";
        int pq=element[0];
        int pqneg=element[0]*(-1);
        
        for(auto elemout: in){
            if (count(elemout.begin(),elemout.end(),pqneg)>0){
                vector<int> tmpvec;
                for (auto num:elemout){
                    if(num!=pqneg){
                        tmpvec.push_back(num);
                    }
                }
                out.push_back(tmpvec);
            }
            else if(count(elemout.begin(),elemout.end(),pq)==0){
                out.push_back(elemout);
            }
        }
        break;
    }
  }
  bool stillcan=false;
  for (auto & element2 : out) 
  {
      if (element2.size()==1){
          stillcan=true;
      }
  }
  if (stillcan==true){
      return bcp(out);
  }
  else{
      return out;
  }
}
int main (int argc, char *argv[])
{  
    std::string input;

    while (getline(std::cin, input) && input != "quit")
    {
        int i=1;
        bool run=true;
        input.erase(std::find_if(input.rbegin(), input.rend(), std::bind1st(std::not_equal_to<char>(), ',')).base(), input.end());

        const char* s3 = input.c_str();
        
        map<std::string, std::string> mymap,formmap;
        if (input=="") {
            std::cout << "Error: invalid input" << '\n';
            run=false;
        }
        else{
            string assignment=s3;
            char *token2;
            map<std::string, std::string> codenames;
            std::string eachname="";
            int countcodes=1;
            codenames[""]=-1;
            for (auto &j:assignment){
                if (isalpha(j)||isdigit(j)){
                    eachname = eachname+j;
                }
                else{
                    if (j!=NULL&&(!codenames.count(eachname))){
                        codenames[eachname] = to_string(countcodes);
                        countcodes+=1;
                    }
                    eachname="";
                }
            }
            if (eachname!=""&&(!codenames.count(eachname))){
                codenames[eachname] = to_string(countcodes);
                countcodes+=1;
            }
            bool mapempty=false;
            bool istextinput=false;
            int index;
            std::string sub_str, find_str;
            bool check2;
            for (int i = 0; i <= sizeof(s3); ++i) {
                check2 = isalpha(s3[i]);
                if (check2){
                    istextinput=true;
                    break;
                }
            }
            for (auto keyval : codenames) {
                find_str=keyval.first;
                sub_str = keyval.second;
                if(find_str!=""){
                    if ((find_str.size()>=10)||((find_str.size()>0)&&isdigit(find_str[0]))){
                        run=false;
                        cout << "Error: invalid input" <<endl;
                        break;
                    }
                    else if ((find_str.size()>0)&&(sub_str.size()>0)&&istextinput){
                        while((index = assignment.find(find_str)) != string::npos){ 
                            assignment.replace(index, find_str.length(), sub_str); 
                        }
                    }
                    else if (((find_str.size()==0)||(sub_str.size()==0))&&istextinput){
                        run=false;
                        cout << "Error: incomplete assignment" <<endl;
                        mapempty=true;
                        break;
                    }
                }        
            }
            std::string find_str2="--";
            while((index = assignment.find(find_str2)) != string::npos){ 
                assignment.replace(index, find_str2.length(), ""); 
            }
            //Assgning to vector
            assignment.erase(std::remove_if(assignment.begin(), assignment.end(), ::isspace),assignment.end());
            vector<string> vfinal;
            int i=0;
            string tmpsub;
            while (i<assignment.size()){
                if (!isdigit(assignment[i])){
                    tmpsub=assignment[i];
                    vfinal.push_back(tmpsub);
                    i+=1;
                }
                else if(isdigit(assignment[i])){
                    tmpsub="";
                    while(isdigit(assignment[i])&&i<assignment.size()){
                        tmpsub+=assignment[i];
                        i+=1;
                    }
                    vfinal.push_back(tmpsub);
                } 
            }
            if (run){
                bool check;
                for (int i = 0; i < assignment.size(); ++i) {
                    if(isalpha(assignment[i])){
                        run = false;
                        cout << "Error: incomplete assignment" <<endl;
                        break;
                        
                    }
                    else if((isdigit(assignment[i]))||(assignment[i]=='*'||assignment[i]=='+'||assignment[i]=='('||assignment[i]=='-'||assignment[i]==')')){
                        continue;
                    }
                    else{
                        run=false;
                        cout << "Error: invalid input" <<endl;
                        break;
                    }
                    
                }
                int brackcounter=0;
                int i=1;
                while ((i<vfinal.size())&&run){
                    if(((vfinal[i]=="+" || vfinal[i]=="*")&&(vfinal[i-1]=="+" || vfinal[i-1]=="*"))||(vfinal[vfinal.size()-1]=="-")||(vfinal[vfinal.size()-1]=="+")||(vfinal[vfinal.size()-1]=="*")){
                        cout << "Error: invalid input" <<endl;
                        run = false;
                    }
                    else if((vfinal[i]=="(")&&isInteger(vfinal[i-1])||(vfinal[i-1]==")")&&isInteger(vfinal[i])){
                        cout << "Error: invalid input" <<endl;
                        run = false;
                    }
                    else if(((vfinal[i-1]=="(")&&((vfinal[i]=="*")||(vfinal[i]=="+"))) || ((vfinal[i]==")")&&((vfinal[i-1]=="+")||(vfinal[i-1]=="*")))){
                        cout << "Error: invalid input" <<endl;
                        run = false;
                    }
                    else if(isInteger(vfinal[i-1])&&isInteger(vfinal[i])){
                        cout << "Error: invalid input" <<endl;
                        run = false;
                    }
                    if(vfinal[i]=="("){
                        brackcounter+=1;
                    }
                    else if(vfinal[i]==")"){
                        brackcounter-=1;
                    }
                    i++;
                }
                if(vfinal[0]=="("){
                    brackcounter+=1;
                }
                if (brackcounter!=0){
                    run = false;
                    cout << "Error: invalid input" <<endl;
                }
            }
            
            if (run)
            {
                Node* root = constructBST(vfinal);
                //inorder2(root);
                inorder3(root);
                vector<vector<int>> outputres = namenodes(root);
                map<int,bool> assmap;
                vector<vector<int>> check=outputres;
                vector<vector<int>> checkbcp;
                int cccount=0;
                bool res = dpll(check,assmap);

                if (res==1){
                    std::cout << "sat" << "\n";
                }
                else{
                    std::cout << "unsat" << "\n";
                }
            }      
        }
    }     
    if (input=="quit"){
        cout << "Exiting Program!" << endl;
    }
    return 0;
}
//latest
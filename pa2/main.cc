//#include "tseitinTransformer.h"
//#include "satSolver.h"
#include <iostream>
#include <string>
#include <map>
//#include "parser.h"
//#include "treeNode.h"
#include <string.h>
#include <vector>
#include <algorithm>
#include <cctype>
#include <typeinfo>
#include <queue>
#include <memory>
// defines Var and Lit
#include "minisat/core/SolverTypes.h"
// defines Solver
#include "minisat/core/Solver.h"

using namespace std;

struct Node
{
    //char data;
    string data;
    int i;
    int code=-1;
    Node* left = nullptr, *right = nullptr;
    Node() {};
    //Node(char data, int i): data(data),i(i) {};
    Node(string data, int i): data(data),i(i) {};
};
//Node* insin(Node* root, vector<char> const &v,bool inbracks);
//Node* insmult(Node* root, vector<char> const &v,bool inbracks);
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
    /*if(root->data=='+'){
        cout<<root->right->data<<" r2 val"<<endl;
    }*/
    inorder2(root->right);
}
void inorder3(Node* root){
    if (root == nullptr) {
        return;
    }
    inorder3(root->right);
    inorder3(root->left);
    //cout<<root->data<<endl;
    
}
/*int inorder(Node* root)
{
    bool result;
    bool val1;
    bool val2;
    
    if (root == nullptr) {
        return 0;
    }
    int lt = inorder(root->right);
    if (lt==48){
            lt = 0;
        }
        else if (lt==49){
            lt = 1;
        }
    int rt = inorder(root->left);
    //sq.push_back(root->data);
    if (rt==48){
            rt = 0;
        }
        else if (rt==49){
            rt = 1;
        }
    
    if (root->data=='*'){
        int r = lt&&rt;
        
        return r;
    }
    else if (root->data=='+'){
        int r= lt||rt;
        
        return r;
    }
    else if (root->data=='-'){
        int r = !lt;
        
        return r;
    }
    //return sq;
    
}*/
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
            //namedcodes[curnode->data] = counter;
            counter+=1;
        }
        else if(namedcodes.count(curnode->data)){
            //cout<<"im the one"<<curnode->data<<namedcodes[curnode->data]<<endl;
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
            //curnode->code=counter;
            vresfinal.push_back({curnode2->code*(-1), curnode2->left->code,curnode2->right->code});
            vresfinal.push_back({curnode2->left->code*(-1), curnode2->code});
            vresfinal.push_back({curnode2->right->code*(-1), curnode2->code});
        }
        else if ((curnode2->data=="*")){
            //curnode->code=counter;
            vresfinal.push_back({curnode2->code*(-1), curnode2->left->code});
            vresfinal.push_back({curnode2->code*(-1), curnode2->right->code});
            vresfinal.push_back({curnode2->left->code*(-1), curnode2->right->code*(-1),curnode2->code});
        }
        else if ((curnode2->data=="-")){
            //curnode->code=counter;
            vresfinal.push_back({curnode2->code*(-1), curnode2->left->code*(-1)});
            vresfinal.push_back({curnode2->code, curnode2->left->code});   
        }
        //vresfinal.push_back(vres);
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
//Node* insmult(Node* root, vector<char> const &v,bool inbracks){
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
                //vector<char> v2(first,last);
                vector<string> v2(first,last);
                cent = new Node(v[0],0);
                cent->left=insin(root,v2,true);
            }
            else{
                auto first = v.cbegin() + 1;
                auto last = v.cbegin()+v.size()-1;
                //vector<char> v2(first,last);
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
                //vector<char> v2(first,last);
                vector<string> v2(first,last);
                cent->right->left = insin(root,v2,true);
            }
            else{
                cent =new  Node(v[bind],0);
                auto first = v.cbegin() + bind+2;
                auto last = v.cbegin()+v.size()-1;
                //vector<char> v2(first,last);
                vector<string> v2(first,last);
                cent->right = insin(root,v2,true); 
            }
            
            if(bind>2){
                auto first = v.cbegin();
                auto last = v.cbegin()+bind;
                //vector<char> v2(first,last);
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
        //cout<<"am i here 13"<<cent->data<<v[1]<<v[0]<<endl;
                
        if((v.size()+bind)>2){
            //cout<<"am i here "<<endl;
            auto first = v.cbegin();
            auto last = v.cbegin()+v.size()+bind;
            //vector<char> v2(first,last);
            vector<string> v2(first,last);
            //cout<<cent->data<<"whai"<<v2.size()<<endl;
            cent->left = insmult(root,v2,inbracks);
        }
        else{
            if ((v.size()+bind)==2){
                //cout<<"am i here 3"<<cent->data<<v[1]<<v[0]<<endl;
                cent->left = new Node(v[0],0);
                cent->left->left = new Node(v[1],0);
                //cout<<"am i here 3"<<cent->data<<v[1]<<v[0]<<endl;
                
            }
            else{
                //cout<<"am i here 5"<<endl;
                cent->left = new Node(v[0],0);
            }
            
        }
        
    }
    //cout<<"whats my prob"<<endl;
    return cent;
}
//Node* insin(Node* root, vector<char> const &v,bool inbracks){
Node* insin(Node* root, vector<string> const &v,bool inbracks){
    //cout<<"am i here?"<<v[0]<<endl;
    Node* cent;
    if(v.size()>3){
        if (v[0]=="-"){
            //cout<<"here?"<<v.size()<<endl;
            if (isInteger(v[1])){
                //cout<<"here?"<<v[1]<<endl;
                if (v[2]=="+"){
                    cent  = new Node(v[2],0);
                    cent->left = new Node(v[0],0);
                    cent->left->left = new Node(v[1],0);;
                    auto firstq2 = v.cbegin()+3;
                    auto lastq2 = v.cbegin()+v.size();
                    //vector<char> v2q2(firstq2,lastq2);
                    vector<string> v2q2(firstq2,lastq2);
                    cent->right = insin(root, v2q2,inbracks);
                }
                else if (v[2]=="*"){
                    int negdig=2;
                    int negdigcount=0;
                    while (negdig<v.size()&&!((v[negdig]=="+")&&(negdigcount==0))){
                        //cout<<"stuckkk"<<endl;
                        if (v[negdig]=="("){
                            negdigcount+=1;
                        }
                        else if (v[negdig]==")"){
                            negdigcount-=1;
                        }
                        negdig+=1;
                    }
                    //cout<<"am i here negdig"<<negdig<<endl;
                    if (negdig==(v.size())){
                        //cout<<"am i here 4r"<<endl;
                
                        cent = insmult(root, v,inbracks);
                        //cout<<"am i here 45"<<cent->data<<v[1]<<v[0]<<endl;
                
                    }
                    else{
                        //cout<<"am i here 45"<<endl;
                        cent  = new Node(v[negdig],0);
                        auto firstq = v.cbegin();
                        auto lastq = v.cbegin()+negdig;
                        //vector<char> v2q(firstq,lastq);
                        vector<string> v2q(firstq,lastq);
                        cent->left = insmult(root, v2q,inbracks);
                        auto firstq2 = v.cbegin()+negdig+1;
                        auto lastq2 = v.cbegin()+v.size();
                        //vector<char> v2q2(firstq2,lastq2);
                        vector<string> v2q2(firstq2,lastq2);
                        cent->right = insin(root, v2q2,inbracks);
                    }
                }
            }
            else if (v[1]=="("){
                //cout<<"here? now"<<v[1]<<endl;
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
                    //cout<<"here now ah"<<endl;
                    cent  = new Node(v[0],0);
                    auto firstq = v.cbegin()+1;
                    auto lastq = v.cbegin()+negind;
                    //vector<char> v2q(firstq,lastq);
                    vector<string> v2q(firstq,lastq);
                    cent->left = insin(root, v2q,inbracks);
                }
                else if (v[negind]=="+"){
                    cent  = new Node(v[negind],0);
                    auto firstq = v.cbegin()+1;
                    auto lastq = v.cbegin()+negind;
                    //vector<char> v2q(firstq,lastq);
                    vector<string> v2q(firstq,lastq);
                    cent->left = new Node(v[0],0);
                    cent->left->left = insin(root, v2q,inbracks);
                    auto firstq2 = v.cbegin()+negind+1;
                    auto lastq2 = v.cbegin()+v.size();
                    //vector<char> v2q2(firstq2,lastq2);
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
                        //vector<char> v2q(firstq,lastq);
                        vector<string> v2q(firstq,lastq);
                        cent->left = insmult(root, v2q,inbracks);
                        auto firstq2 = v.cbegin()+negind+1;
                        auto lastq2 = v.cbegin()+v.size();
                        //vector<char> v2q2(firstq2,lastq2);
                        vector<string> v2q2(firstq2,lastq2);
                        cent->right = insin(root, v2q2,inbracks);
                    }
                    
                }
                //cout<<"im neg ind"<<negind<<endl;
            }
            
        }
        else if(v[0]=="("){
            //cout<<"here? nowwwww"<<endl;
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
                //cout<<"dafrick"<<endl;
                auto first = v.cbegin() + 1;
                auto last = v.cbegin()+bind;
                //vector<char> v2(first,last);
                vector<string> v2(first,last);
                cent = insin(root,v2,inbracks);
            }
            else if((bind+1)<v.size()&&(v[bind+1]=="+")){
                //cout<<"moi"<<endl;
                cent = new Node(v[bind+1],0);
                auto first = v.cbegin() + 1;
                auto last = v.cbegin()+bind;
                //vector<char> v2(first,last);
                vector<string> v2(first,last);
                cent->left = insin(root,v2,true);
                auto first2 = v.cbegin() + bind+2;
                auto last2= v.cbegin()+v.size();
                //vector<char> v3(first2,last2);
                vector<string> v3(first2,last2);
                cent->right = insin(root,v3,inbracks);
            }
            else if((bind+1)<v.size()&&(v[bind+1]=="*")){
                //cout<<"great"<<endl;
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
                //cout << "im brind"<<found<<brind << endl;
                if(found==true){
                    cent = new Node(v[brind],0);
                    auto first = v.cbegin();
                    auto last = v.cbegin()+brind;
                    //vector<char> v2(first,last);
                    vector<string> v2(first,last);
                    //cout<<v2.size()<<endl;
                    cent->left = insmult(root,v2,inbracks);
                    auto first2 = v.cbegin() + brind+1;
                    auto last2 = v.cbegin()+v.size();
                    //vector<char> v3(first2,last2);
                    vector<string> v3(first2,last2);
                    //cout<<v3.size()<<v2.size()<<v2[0]<<v3[0]<<endl;
                    cent->right = insin(root,v3,inbracks);
                }
                else{
                    //cout << "im here"<<brind << endl;
                    cent = insmult(root,v,inbracks);
                }
            }
            
        }
        else if(isInteger(v[0])){
            //cout<<"inge?"<<v[1]<<endl;
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
                        //cout << "im brind 2"<<brind << endl;
                        break;
                    }
                    brind+=1;
                }
                //cout << "im brind"<<brind << endl;
                if(found==true){
                    cent = new Node(v[brind],0);
                    auto first = v.cbegin();
                    auto last = v.cbegin()+brind;
                    //vector<char> v2(first,last);
                    vector<string> v2(first,last);
                    cent->left = insmult(root,v2,true);
                    auto first2 = v.cbegin() + brind+1;
                    auto last2 = v.cbegin()+v.size();
                    //vector<char> v3(first2,last2);
                    vector<string> v3(first2,last2);
                    cent->right = insin(root,v3,inbracks);
                }
                else{
                    //cout << "im here"<<brind << endl;
                    cent = insmult(root,v,inbracks);
                    //cout<<"do i reach"<<endl;
                }
            }
            else if(v[1]=="+"){
                cent = new Node(v[1],0);
                cent->left = new Node(v[0],0);
                /*if ((root==nullptr)&&(inbracks==false)){
                    root = cent;
                }*/
                auto first2 = v.cbegin() + 2;
                auto last2 = v.cbegin()+v.size();
                //vector<char> v3(first2,last2);
                vector<string> v3(first2,last2);
                cent->right = insin(root,v3,inbracks);
            }
        }
        else if(v[0]=="+"){
            //cout<<"here ippo?"<<v[1]<<endl;
            cent = new Node(v[0],0);
            if (root==nullptr){
                root = cent;
            }
            auto first = v.cbegin() + 1;
            auto last = v.cbegin()+v.size();
            //vector<char> v3(first,last);
            vector<string> v3(first,last);
            cent->right = insin(root,v3,inbracks);
        }
    }
    else{
        //cout<<"i get here now gahhhh"<<v[0]<<endl;
        if (v.size()==1){
            //cout<<"i get here"<<endl;
            cent = new Node(v[0],0);
        }
        else if((v.size()>1)&&((v[0]=="+")||(v[0]=="*"))&&isInteger(v[1])){
            //cout<<v[0]<<v[1]<<"am i here atleast"<<endl;
            cent = new Node(v[0],0);
            cent->right = new Node(v[1],1);
        }
        else if ((v.size()>2)&&((v[0]=="+")||(v[0]=="*"))&&(v[1]=="-")){
            //cout<<v[0]<<v[1]<<"am i here kor"<<endl;
            cent = new Node(v[0],0);
            cent->right = new Node(v[1],1);
            cent->right->left = new Node(v[2],2);
        }
        else if ((v.size()>2)&&((v[1]=="+")||(v[1]=="*"))){
            //cout<<v[0]<<v[1]<<"am i here"<<endl;
            cent = new Node(v[1],0);
            cent->right = new Node(v[2],1);
            cent->left = new Node(v[0],2);
        }
        else if (v[0]=="("){
            //cout<<"i get here 2"<<endl;
            cent = new Node(v[1],0);
        }
        
        else if ((v.size()==2)&&(v[0]=="-")){
            //cout<<"i get here"<<endl;
            cent = new Node(v[0],0);
            cent->left = new Node(v[1],1);
        }
        
        if ((root==nullptr)&&(inbracks==false)){
            root = cent;
        } 
    }
    return cent;
}
//Node* constructBST(vector<char> const &keys)
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
        //if (input.find(";") == std::string::npos) {
        if (input=="") {
            //cout<<"here?"<<endl;
            std::cout << "Error: invalid input" << '\n';
            run=false;
        }
        else{
            //vector<string> v = split (s3, ";");
            //vector<string> v = input.c_str();
            //vector<string> form = split (v[1], ",");
            string assignment=s3;
            //Removing white space and mapping
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
                        //cout<<eachname<<codenames[eachname]<<"im each"<<endl;
                        countcodes+=1;
                    }
                    eachname="";
                }
            }
            if (eachname!=""&&(!codenames.count(eachname))){
                        codenames[eachname] = to_string(countcodes);
                        //cout<<eachname<<codenames[eachname]<<"im each"<<endl;
                        countcodes+=1;
                    }
            //cout<<codenames["c"]<<"im c"<<endl;
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
                    //cout << find_str<<"codes"<<sub_str <<endl;
                if ((find_str.size()>=10)||((find_str.size()>0)&&isdigit(find_str[0]))){
                    run=false;
                    
                    cout << "Error: invalid input 2" <<endl;
                    break;
                }
                else if ((find_str.size()>0)&&(sub_str.size()>0)&&istextinput){
                while((index = assignment.find(find_str)) != string::npos){ 
                   assignment.replace(index, find_str.length(), sub_str); 
                }}
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
            assignment.erase(std::remove_if(assignment.begin(), assignment.end(), ::isspace),
                    assignment.end());
            //cout<<assignment<<"im assignment "<<isdigit(assignment[0])<<endl;
            //vector<char> vfinal(assignment.begin(),assignment.end());
            vector<string> vfinal;
            int i=0;
            string tmpsub;
            while (i<assignment.size()){
                if (!isdigit(assignment[i])){
                    tmpsub=assignment[i];
                    vfinal.push_back(tmpsub);
                    i+=1;
                    //cout<<"me str "<<vfinal[vfinal.size()-1]<<endl;
                }
                else if(isdigit(assignment[i])){
                    tmpsub="";
                    while(isdigit(assignment[i])&&i<assignment.size()){
                        //cout<<"me "<<endl;
                        tmpsub+=assignment[i];
                        i+=1;
                    }
                    vfinal.push_back(tmpsub);
                    //cout<<"me str "<<vfinal[vfinal.size()-1]<<endl;
                } 
            }
            //cout<<"me str size"<<vfinal.size()<<endl;
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
                        //cout<<"here 1"<<endl;
                        cout << "Error: invalid input 3" <<endl;
                        break;
                    }
                    
                }
                
                int brackcounter=0;
                int i=1;
                while ((i<vfinal.size())&&run){
                    if(((vfinal[i]=="+" || vfinal[i]=="*")&&(vfinal[i-1]=="+" || vfinal[i-1]=="*"))||(vfinal[vfinal.size()-1]=="-")||(vfinal[vfinal.size()-1]=="+")||(vfinal[vfinal.size()-1]=="*")){
                        //cout<<"here 2"<<vfinal[i]<<vfinal[i-1]<<vfinal[vfinal.size()-1]<<endl;
                        cout << "Error: invalid input 4" <<endl;
                        run = false;
                    }
                    else if((vfinal[i]=="(")&&isInteger(vfinal[i-1])||(vfinal[i-1]==")")&&isInteger(vfinal[i])){
                        //cout<<"here 3"<<endl;
                        cout << "Error: invalid input 5" <<endl;
                        run = false;
                    }
                    else if(((vfinal[i-1]=="(")&&((vfinal[i]=="*")||(vfinal[i]=="+"))) || ((vfinal[i]==")")&&((vfinal[i-1]=="+")||(vfinal[i-1]=="*")))){
                        //std::cout<<"here 5"<<'\n';
                        cout << "Error: invalid input 6" <<endl;
                        run = false;
                    }
                    else if(isInteger(vfinal[i-1])&&isInteger(vfinal[i])){
                        //std::cout<<"here 6"<<'\n';
                        cout << "Error: invalid input 7" <<endl;
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
                    //std::cout<<"here 7"<<'\n';
                    cout << "Error: invalid input 8" <<endl;
                }
            }
            
            if (run)
            {
                
                Node* root = constructBST(vfinal);
                //vector<char> fstr;
                //int valtru = inorder(root);
                
                //inorder2(root);
                inorder3(root);
                vector<vector<int>> outputres = namenodes(root);
                map<int,Minisat::Lit> allvars;
                
                std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
                Minisat::Lit l1, l2, l3, l4;
                // create 3 positive literals over 3 new variables
                for(auto outa:outputres){
                    for (auto outb:outa){
                        int aout;
                        if (outb<0){
                            aout = (-1)*outb;
                        }   
                        else{
                            aout = outb;
                        }
                            
                        if(!allvars.count(aout)){
                            allvars[aout]=Minisat::mkLit(solver->newVar());;
                        }
                        //cout<<"im a "<<outb<<endl;
                    }
                    //cout<<"im b "<<endl;
                }
                Minisat::vec<Minisat::Lit> vecliterals;
                for(vector<int> vr1:outputres){
                    
                    vecliterals.clear();
                    //Minisat::vec<Minisat::Lit> vecliterals;
                    //cout<<vecliterals.size()<<endl;
                    int count=0;
                  for(int vr2:vr1){
                    //cout<<"im num "<<vr2<<endl;
                    count+=1;
                    if (vr2>0){
                        //Minisat::Lit t2 = Minisat::toLit(vr2);
                        
                        vecliterals.push(allvars[vr2]);
                        
                        //cout<<Minisat::toInt(t2)<<"i am int"<<endl;
                    }
                    else{
                        int tmp5 = 0-vr2;
                        //Minisat::Lit t1 = Minisat::toLit(vr2);
                        //vecliterals.push(t1);
                        vecliterals.push(~allvars[tmp5]);
                        //cout<<Minisat::toInt(t1)<<"i am int"<<endl;
                    }
                  }
                  //cout<<count<<"im count "<<endl;
                  solver->addClause(vecliterals);
                }
                

                bool res = solver->solve();
                if (res==1){
                    std::cout << "sat" << "\n";
                }
                else{
                    std::cout << "unsat" << "\n";
                }
                
                solver.reset (new Minisat::Solver());
                
                //cout <<valtru<<endl;
                
                
            }  
            
        }
    }    
      
    if (input=="quit"){
        cout << "Exiting Program!" << endl;
        

    }
    
    return 0;
}
//latest
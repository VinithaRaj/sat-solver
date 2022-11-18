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
using namespace std;

struct Node
{
    char data;
    int i;
    Node* left = nullptr, *right = nullptr;
    Node() {};
    Node(char data, int i): data(data),i(i) {};
};
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
    inorder2(root->right);
    //cout<<root->data<<" r2"<<endl;
    inorder2(root->left);
    
    
}
void inorder3(Node* root){
    if (root == nullptr) {
        return;
    }
    inorder3(root->right);
    inorder3(root->left);
    //cout<<root->data<<endl;
    
}
int inorder(Node* root)
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
    
}
vector<char> invertarray(vector<char> const&v){
    vector<char> newv;
    int i=v.size()-1;
    while(i>=0){
        if (isdigit(v[i])&&v[i-1]=='-'){
            newv.push_back(v[i-1]);
            newv.push_back(v[i]);
            i-=2;
        }
        else if (isdigit(v[i])||(v[i]=='*')){
            newv.push_back(v[i]);
            i-=1;
        }
        else if (v[i]==')'){
            int starti = i;
            int brackcount=1;
            i-=1;
            while (brackcount!=0){
                if (v[i]==')'){
                    brackcount+=1;
                }
                else if (v[i]=='('){
                    brackcount-=1;
                }
                i-=1;
            }
            if (v[i]=='-'){
                for (int leftind=i;leftind<=starti;leftind++){
                    newv.push_back(v[leftind]);
                }
            }
            else{
                for (int leftind=i+1;leftind<=starti;leftind++){
                    newv.push_back(v[leftind]);
                }
            }
            
        }
        else{
            newv.push_back(v[i]);
            i-=1;
        }
    }
    
    
    return newv;
}

Node* insertright(Node* root, int end, int ind,vector<char> const &v, bool inverted )
{
    Node* cent;
    if ((ind+2)<v.size()){
        
        if ((v[end+1]=='*')&&(inverted==false)){
            int timesind = end;
            while ((v[timesind+1]!='+')&&(timesind<v.size()-1)){
                
                if ((isdigit(v[timesind])||v[timesind]==')')&&(v[timesind+1]=='*')){
                    timesind+=2;
                    
                }
                else if (v[timesind]=='('){
                    
                    int mybracind=timesind;
                    int mybrackcount=1;
                    
                    while ((mybrackcount!=0)&&(mybracind<v.size())){
                        if(v[mybracind]=='('){
                            mybrackcount+=1;
                        }
                        else if(v[mybracind]==')'){
                            mybrackcount-=1;
                        }
                        mybracind+=1;
                    }
                    timesind=mybracind-1;
                    
                    
                }
                else if (v[timesind]=='-'){
                    timesind+=1;
                    
                }
            }
            
            if ((timesind+1)<v.size()){
                
                cent = new Node(v[timesind+1],timesind+1);
                auto first = v.cbegin() + ind;
                auto last = v.cbegin() + timesind + 1;
                vector<char> v2(first,last);
                vector<char> v3=invertarray(v2);
                if (isdigit(v3[0])||(v3[0]=='-')||(v3[0]=='(')){
                    
                    cent->left = insertright(cent, 0,0,v3,true);
                }
                else{
                    int meout=v3.size()-1;
                    cent->left = insertright(cent, meout,0,v3,true);
                }
                if(v[timesind+2]!='('  && v[timesind+2]!=')'){
                    cent->right = insertright(cent, timesind+2,timesind+2,v,true);
                }
                else{
                    int j=timesind+2;
                    queue<int> g;
                    if (v[ind+2]=='('){
                        g.push(1);
                    }
                    while (!g.empty()){
                        j+=1;
                        if (v[j]==')'){
                            g.pop();
                        }
                        else if (v[j]=='('){
                            g.push(1);
                        }
                    }
                    cent->right = insertright(cent, j,timesind+2,v,false);
                }
            }
            else{
                auto first = v.cbegin() + ind;
                auto last = v.cbegin() + timesind + 1;
                vector<char> v2(first,last);
                vector<char> v3=invertarray(v2);
                if (isdigit(v3[0])||(v3[0]=='-')||(v3[0]=='(')){
                    
                    cent = insertright(cent, 0,0,v3,true);
                }
                else{
                    
                    int meout=v3.size()-1;
                    cent = insertright(cent, meout,0,v3,true);
                }
            }
            
            
        }
        else if (v[end+1]=='*'  || v[end+1]=='+'){
            //if digit and next to it is an operator
            
            if (ind==end){
                // if its a sigle digit
                cent = new Node(v[ind+1],ind);
                cent->left = new Node(v[ind],ind);
            }
            else{
                // if its a bracket 
                cent = new Node(v[end+1],end);
                auto first = v.cbegin() + ind+1;
                auto last = v.cbegin() + end + 1;
                vector<char> v2(first,last-1);
                
                if (isdigit(v2[0])){
                    cent->left = insertright(cent, 0,0,v2,false);
                }
                else{
                    cent->left = insertright(cent, v2.size()-1,0,v2,false);
                }
            }
            if(v[end+2]!='('  && v[end+2]!=')'){
                
                cent->right = insertright(cent, end+2,end+2,v,inverted);
            }
            else{
                int j=ind+2;
                queue<int> g;
                if (v[ind+2]=='('){
                    g.push(1);
                }
                while (!g.empty()){
                    j+=1;
                    if (v[j]==')'){
                        g.pop();
                    }
                    else if (v[j]=='('){
                        g.push(1);
                    }
                }
                cent->right = insertright(cent, j,ind+2,v,inverted);
            }
        }
        
        else if (v[end]=='-'){
            ind+=1;
            end+=1;
            if (ind==end){
                // this is the number node
               if (isdigit(v[ind])){
                   cent = new Node(v[ind+1],ind);
                    cent->left = new Node(v[ind-1],ind-1);
                    cent->left->right = new Node(v[ind],ind);
                    cent->right = insertright(cent, ind+2,ind+2,v,inverted);
               }
               else if (v[ind]=='('){
                   int brackindneg=ind+1;
                   int brackindcounter=1;
                   while((brackindcounter!=0)&&(brackindneg<v.size())){
                       if(v[brackindneg]=='('){
                           brackindcounter+=1;
                       }
                       else if(v[brackindneg]==')'){
                           brackindcounter-=1;
                       }
                       brackindneg+=1;
                   }
                   cent = new Node(v[ind-1],ind-1);
                    auto first = v.cbegin() + ind;
                    auto last = v.cbegin() + brackindneg + 1;
                    
                    vector<char> v2(first,last-1);
                    
                    /*cent->left = insertright(cent, v2.size()-1,0,v2);*/
                    cent->right = insertright(cent, v2.size()-1,0,v2,false);
               }
               
            }
            else{
                
                cent = new Node(v[end+1],end);
                auto first = v.cbegin() + ind+1;
                auto last = v.cbegin() + end + 1;
                vector<char> v2(first,last-1);
                cent->left = new Node('-',end-1);
                //cent->left->left = insertright(cent, 0,0,v2);
                cent->left->right = insertright(cent, 0,0,v2,false);
            }
            
        }
        else if (v[end]!='('  && v[end]!=')'){
            queue<int> g2;
            int c = end;
            g2.push(1);
            while (!g2.empty()){
                c+=1;
                if(v[c]!=')'){
                    g2.pop();
                }
                else if(v[c]=='('){
                    g2.push(1);
                }
            }
            cent = insertright(cent, c,end,v,false);
        }
        
        else if (v[end]=='('  || v[end]==')'){
            
           if(ind!=end){
               auto first = v.cbegin() + ind+1;
                auto last = v.cbegin() + end + 1;
                vector<char> v2(first,last-1);
                if (isdigit(v2[0])||(v2[0]=='-')){
                    
                    cent = insertright(cent, 0,0,v2,false);
                }
                else{
                    int meout=v2.size()-1;
                    cent = insertright(cent, meout,0,v2,false);
                }
                
            }
            else{
                int brackcounter=1;
                int brackindx=ind+1;
                while ((brackcounter!=0)&&(brackindx<v.size())){
                    if (v[brackindx]==')'){
                        brackcounter-=1;
                    }
                    else if (v[brackindx]=='('){
                        brackcounter+=1;
                    }
                    brackindx+=1;
                }
                
                cent = insertright(cent, brackindx-1,end,v,inverted);
                
            }
            
            
        }
        
    }
    else{
        if (v[end]=='-'){
            ind+=1;
            end+=1;
            if (ind==end){
                
                cent =  new Node(v[ind-1],ind-1);
                //cent->left = new Node(v[ind],ind);
                cent->right = new Node(v[ind],ind);
            }
            else{
                auto first = v.cbegin() + ind+1;
                auto last = v.cbegin() + end + 1;
                vector<char> v2(first,last-1);
                cent = new Node('-',end-1);
                //cent->left = insertright(cent, 0,0,v2);
                cent->right = insertright(cent, 0,0,v2,false);
            }
            
        }
        else{
            if (ind==end){
                
                    cent = new Node(v[ind],ind);
            }
            else{
                auto first = v.cbegin() + ind+1;
                auto last = v.cbegin() + end + 1;
                vector<char> v2(first,last-1);
                cent = insertright(cent, 0,0,v2,false);
            }
        }
        
    }
    return cent;
}

Node* insert(Node* root, char key,int ind,vector<char> const &v)
{
    int counter=0;
    if (root == nullptr) {
        while (counter<v.size()){
            if (v[counter+1]=='+' ){
                counter+=1;
            }
            else if (v[counter+1]=='*'){
                root= insertright(root, counter,counter,v,false);
                return root;
            }
            else if(v[counter]=='('  || v[counter]==')'){
                int j=counter;
                queue<int> g;
                int cbracks=0;
                if (v[counter]=='('){
                    cbracks+=1;
                    g.push(1);
                }
                //while (!g.empty()){
                while (cbracks!=0){
                    if (v[j+1]==')'){
                        cbracks-=1;
                        g.pop();
                    }
                    else if (v[j+1]=='('){
                        cbracks+=1;
                        g.push(1);
                    }
                    j+=1;
                    
                }
                auto first = v.cbegin() + counter+1;
                auto last = v.cbegin() + j + 1;
                vector<char> v2(first,last-1);
                if ((j+1)<v.size()){
                    //to check if there are operators after
                    root  = new Node(v[j+1],j+1);
                    if (isdigit(v2[0])){
                        root->left = insertright(root, 0,0,v2,false);
                    }
                    else{
                        root->left = insertright(root, v2.size()-1,0,v2,false);
                    }
                    root->right = insertright(root, j+2,j+2,v,false);
                }
                else{
                    if (isdigit(v2[0])||(v2[0]=='-')){
                        root = insertright(root, 0,0,v2,false);
                    }
                    else{
                        root = insertright(root, v2.size()-1,0,v2,false);
                    }
                }
                return root;
            }
            else if (v[counter]=='-'){
                if ((isdigit(v[counter+1]))&&(counter+3)<v.size()){
                    //root = new Node(v[counter],counter);
                    root = new Node(v[counter+2],counter+2);
                    root->left = new Node(v[counter],counter);
                    root->left->right = new Node(v[counter+1],counter+1);
                    root->right = insertright(root, counter+3,counter+3,v,false);
                    return root;
                }
                else{
                    int brackinscount=1;
                    int brackinsind=counter+1;
                    while((brackinscount!=0)&&brackinsind<v.size()){
                        if(v[brackinsind]=='('){
                            brackinscount+=1;
                        }
                        else if(v[brackinsind]==')'){
                            brackinscount-=1;
                        }
                        brackinsind+=1;
                    }
                    auto first = v.cbegin() + ind+1;
                    auto last = v.cbegin() + brackinsind + 1;
                    vector<char> v2(first,last-1);
                    root = new Node('-',ind);
                    //root->left = insertright(root, v2.size()-1,0,v2);
                    root->right = insertright(root, v2.size()-1,0,v2,false);
                    //root->right = insertright(root, counter+1,counter+1,v);
                    return root;
                }
                
            }
            else{
                root = new Node(v[counter],counter);
                root->left = new Node(v[counter-1],counter-1);
                root->right = insertright(root, counter+1,counter+1,v,false);
                return root;
            }

        }
    }
    return root;
    
}

Node* constructBST(vector<char> const &keys)
{
    Node* root = nullptr;
    root = insert(root, keys[1], 0,keys);
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
        if (input.find(";") == std::string::npos) {
            
            std::cout << "Error: invalid input" << '\n';
            run=false;
        }
        else{
            
            vector<string> v = split (s3, ";");
            vector<string> form = split (v[1], ",");
            string assignment=v[0];
            
            //Removing white space and mapping
            char *token2;
            for(string i:form){
                i.erase(std::remove_if(i.begin(), i.end(), ::isspace),
                    i.end());
               
                size_t pos2 = i.find(":");
                if (formmap.count(i.substr(0, pos2))){
                    if(formmap[i.substr(0, pos2)] != i.substr(pos2 + 1, string::npos)){
                        cout << "Error: contradicting assignment" <<endl;
                        run = false;
                        break;
                    }
                }
                else{
                    formmap[i.substr(0, pos2)] = i.substr(pos2 + 1, string::npos);
                }
            }
            //Printing formula and assignment
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
            for (auto keyval : formmap) {
                
                find_str=keyval.first;
                sub_str = keyval.second;
                if ((find_str.size()>=10)||((find_str.size()>0)&&isdigit(find_str[0]))){
                    run=false;
                    
                    cout << "Error: invalid input" <<endl;
                    //mapempty=true;
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
            
           
            std::string find_str2="--";
            while((index = assignment.find(find_str2)) != string::npos){ 
                   assignment.replace(index, find_str2.length(), ""); 
                }
            
            //Assgning to vector
            assignment.erase(std::remove_if(assignment.begin(), assignment.end(), ::isspace),
                    assignment.end());
            vector<char> vfinal(assignment.begin(), assignment.end());
            if (run){
                bool check;
                for (int i = 0; i < assignment.size(); ++i) {
                    if(isalpha(assignment[i])){
                        run = false;
                        cout << "Error: incomplete assignment" <<endl;
                        break;
                        
                    }
                    else if((isdigit(assignment[i])&&(assignment[i]=='1'||assignment[i]=='0'))||(assignment[i]=='*'||assignment[i]=='+'||assignment[i]=='('||assignment[i]=='-'||assignment[i]==')')){
                        continue;
                    }
                    else{
                        run=false;
                        cout << "Error: invalid input" <<endl;
                        break;
                    }
                    
                }
                
                int brackcounter=0;
                int i=0;
                while ((i<vfinal.size())&&run){
                    if(((vfinal[i]=='+' || vfinal[i]=='*')&&(vfinal[i-1]=='+' || vfinal[i-1]=='*'))||(vfinal[vfinal.size()-1]=='-')||(vfinal[vfinal.size()-1]=='+')||(vfinal[vfinal.size()-1]=='*')){
                        cout << "Error: invalid input" <<endl;
                        run = false;
                    }
                    else if((vfinal[i]=='(')&&isdigit(vfinal[i-1])||(vfinal[i-1]==')')&&isdigit(vfinal[i])){
                        cout << "Error: invalid input" <<endl;
                        run = false;
                    }
                    else if(((vfinal[i-1]=='(')&&((vfinal[i]=='*')||(vfinal[i]=='+'))) || ((vfinal[i]==')')&&((vfinal[i-1]=='+')||(vfinal[i-1]=='*')))){
                        //std::cout<<"here 5"<<'\n';
                        cout << "Error: invalid input" <<endl;
                        run = false;
                    }
                    else if(isdigit(vfinal[i-1])&&isdigit(vfinal[i])){
                        //std::cout<<"here 6"<<'\n';
                        cout << "Error: invalid input" <<endl;
                        run = false;
                    }
                    if(vfinal[i]=='('){
                        brackcounter+=1;
                    }
                    else if(vfinal[i]==')'){
                        brackcounter-=1;
                    }
                    i++;
                }
                if (brackcounter!=0){
                    run = false;
                    //std::cout<<"here 7"<<'\n';
                    cout << "Error: invalid input" <<endl;
                }
            }
            
            if (run)
            {
                
                Node* root = constructBST(vfinal);
                vector<char> fstr;
                int valtru = inorder(root);
                
                inorder2(root);
                inorder3(root);
                cout << valtru<<endl;
                
                
            }  
            
        }
    }    
      
    if (input=="quit"){
        cout << "Exiting Program!" << endl;
    }
    
    return 0;
}





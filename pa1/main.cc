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
std::string inorder(Node* root,std::string sq)
{
    bool result;
    bool val1;
    bool val2;
    if (root == nullptr) {
        return sq;
    }
    inorder(root->right,sq);
    //cout << root->data << " ";
    if (root->data=='+'){
        if ((root->left->data=='0') && (root->right->data=='0')){
            root->data='0';
        }
        else{
            root->data='1';
        }
    }
    else if((root->data=='*')){
        if ((root->left->data=='1') && (root->right->data=='1')){
            root->data='1';
        }
        else{
            root->data='0';
        }
    }
    else if((root->data=='-')){
        if ((root->left->data=='1')){
            root->data='0';
        }
        else{
            root->data='1';
        }
    }
    inorder(root->left,sq);
    return sq;
    
}


Node* insertright(Node* root, int end, int ind,vector<char> const &v )
{
    Node* cent;
    if ((ind+2)<v.size()){
        if (v[end+1]=='*'  || v[end+1]=='+'){
            if (ind==end){
                cent = new Node(v[ind+1],ind);
                cent->left = new Node(v[ind],ind);
            }
            else{
                cent = new Node(v[end+1],end);
                auto first = v.cbegin() + ind+1;
                auto last = v.cbegin() + end + 1;
                vector<char> v2(first,last-1);
                cent->left = insertright(cent, 0,0,v2);
            }
            if(v[end+2]!='('  && v[end+2]!=')'){
                cent->right = insertright(cent, end+2,end+2,v);
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
                cent->right = insertright(cent, j,ind+2,v);
            }
        }
        
        else if (v[end]=='-'){
            ind+=1;
            end+=1;
            if (ind==end){
                cent = new Node(v[ind+1],ind);
                cent->left = new Node(v[ind-1],ind-1);
                cent->left->left = new Node(v[ind],ind);
            }
            else{
                cent = new Node(v[end+1],end);
                auto first = v.cbegin() + ind+1;
                auto last = v.cbegin() + end + 1;
                vector<char> v2(first,last-1);
                cent->left = new Node('-',end-1);
                cent->left->left = insertright(cent, 0,0,v2);
            }
            if(v[end+2]!='('  && v[end+2]!=')'){
                cent->right = insertright(cent, end+2,end+2,v);
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
                cent->right = insertright(cent, j,ind+2,v);
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
            cent = insertright(cent, c,end,v);
        }
        
        else if (v[end]=='('  || v[end]==')'){
            auto first = v.cbegin() + ind+1;
            auto last = v.cbegin() + end + 1;
            vector<char> v2(first,last-1);
            cent = insertright(cent, 0,0,v2);
            
        }
        
    }
    else{
        if (v[end]=='-'){
            ind+=1;
            end+=1;
            if (ind==end){
                cent =  new Node(v[ind-1],ind-1);
                cent->left = new Node(v[ind],ind);
            }
            else{
                auto first = v.cbegin() + ind+1;
                auto last = v.cbegin() + end + 1;
                vector<char> v2(first,last-1);
                cent = new Node('-',end-1);
                cent->left = insertright(cent, 0,0,v2);
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
                cent = insertright(cent, 0,0,v2);
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
            if (v[counter+1]=='*'  || v[counter+1]=='+' ){
                counter+=1;
            }
            else if(v[counter]=='('  || v[counter]==')'){
                int j=counter;
                queue<int> g;
                if (v[counter]=='('){
                    g.push(1);
                }
                while (!g.empty()){
                    if (v[j+1]==')'){
                        g.pop();
                    }
                    else if (v[j+1]=='('){
                        g.push(1);
                    }
                    j+=1;
                }
                
                auto first = v.cbegin() + counter+1;
                auto last = v.cbegin() + j + 1;
                vector<char> v2(first,last-1);
                if ((j+1)<v.size()){
                    root  = new Node(v[j+1],j+1);
                    root->left = insertright(root, 0,0,v2);
                    root->right = insertright(root, j+2,j+2,v);
                }
                else{
                    root = insertright(root, 0,0,v2);
                }
                return root;
            }
            else{
                root = new Node(v[counter],counter);
                root->left = new Node(v[counter-1],counter-1);
                root->right = insertright(root, counter+1,counter+1,v);
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
        //char s3[] = "A + B * -0 * (1 + -C);A:1, B:1,C:1";
        int i=1;
        bool run=true;
        const char* s3 = input.c_str();
        map<std::string, std::string> mymap,formmap;
        if (input.find(";") == std::string::npos) {
            //std::cout<<"here"<<'\n';
            std::cout << "Error: Invalid input" << '\n';
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
                        cout << "Error: Contradicting Assignment" <<endl;
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
                //cout << keyval.first << "=>" << keyval.second << endl;
                find_str=keyval.first;
                sub_str = keyval.second;
                if ((find_str.size()>0)&&(sub_str.size()>0)&&istextinput){
                while((index = assignment.find(find_str)) != string::npos){ 
                   assignment.replace(index, find_str.length(), sub_str); 
                }}
                else if (((find_str.size()==0)||(sub_str.size()==0))&&istextinput){
                    run=false;
                    cout << "Error: Incomplete Assignment" <<endl;
                    mapempty=true;
                    break;
                }
            }
            
            //cout << "Assignment :" << assignment<<endl;
            
            //Assgning to vector
            assignment.erase(std::remove_if(assignment.begin(), assignment.end(), ::isspace),
                    assignment.end());
            vector<char> vfinal(assignment.begin(), assignment.end());
            if (run){
                bool check;
                for (int i = 0; i < assignment.size(); ++i) {
                    if(isdigit(assignment[i])||(assignment[i]=='*'||assignment[i]=='+'||assignment[i]=='('||assignment[i]=='-'||assignment[i]==')')){
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
                    if((vfinal[i]=='+' || vfinal[i]=='*')&&(vfinal[i-1]=='+' || vfinal[i-1]=='*')){
                        cout << "Error: Invalid Input" <<endl;
                        run = false;
                    }
                    else if((vfinal[i]=='(')&&isdigit(vfinal[i-1])||(vfinal[i-1]==')')&&isdigit(vfinal[i])){
                        cout << "Error: Invalid Input" <<endl;
                        run = false;
                    }
                    else if(((vfinal[i-1]=='(')&&((vfinal[i]=='*')||(vfinal[i]=='+'))) || ((vfinal[i]==')')&&((vfinal[i-1]=='+')||(vfinal[i-1]=='*')))){
                        cout << "Error: Invalid Input" <<endl;
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
                    cout << "Error: Invalid Input" <<endl;
                }
            }
            
            if (run)
            {
                
                Node* root = constructBST(vfinal);
                std::string fstr;
                std::string finalstring = inorder(root,fstr);
                cout << "Output :" << root->data<<endl;
                
            }  
            
        }
    }    
      
    if (input=="quit"){
        cout << "Exiting Program!" << endl;
    }
    
    return 0;
}
// a helper function parsing the input into the formula string and the assignment string
/*void parseLine(const std::string &line, std::string &formulaStr, std::string &assignmentStr) {
  // your code starts here
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  while (true) // continuously asking for new inputs from standard input
  {
    std::string line; // store each input line
    std::string formulaStr; // store the formula string
    std::string assignmentStr; // store the assignment string
    // your code starts here
  }
}*/



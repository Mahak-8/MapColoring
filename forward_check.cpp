#include <bits/stdc++.h>
using namespace std;

class Node{
    public:
    int value;
    vector<int> domain;

    Node(int colors){
        value = 0;
        for(int i=0;i<colors;i++){
            domain.push_back(i+1);
        }
    }
};

void initializeMap(vector<vector<int>> &M,int size){
    for(int i=0;i<size;i++){
        vector<int> v(size);
        M.push_back(v);
    }
}
bool isConsistent(vector<Node> nodes,vector<vector<int>> M,int var,int color){
    for(int i=var+1;i<nodes.size();i++){
        if(M[var][i] == 1 && nodes[i].value == color)
            return false;
    }
    return true;
}
int SELECT_UNASSIGNED_VARIABLE(vector<Node> nodes,vector<vector<int>> M){
    int degree = 0;
    int index = -1;
    for(int i=0;i<nodes.size();i++){

        if(!isConsistent(nodes,M,i,nodes[i].value)){
             //degree
            int temp=0;
            for(int j=0;j<nodes.size();j++){
                if(M[i][j] == 1)
                    temp++;
            }
            if(temp>=degree){
                degree = temp;
                index = i;
            }
        }

    }
    return index;
}

bool forward_check(vector<Node> nodes,vector<vector<int>> M,int var,int color){
    bool isConsist = true;
    bool forcheck =  true;
    int size = nodes.size();
    for(int i=0;i<size;i++){
        if(M[var][i] == 1){
            /**neighbor having same color*/
            if(nodes[i].value == color)
                isConsist = false;
            /**Remove from domain*/
            vector<int>::iterator position = find(nodes[i].domain.begin(), nodes[i].domain.end(), color);
            if (position != nodes[i].domain.end())
                nodes[i].domain.erase(position);

            if(nodes[i].domain.size() == 0)
                forcheck = false;
        }
    }
    return (isConsist && forcheck);
}

bool BT_FORWARD_CHECKING(vector<Node> &nodes,vector<vector<int>> M){
    int var = SELECT_UNASSIGNED_VARIABLE(nodes,M);
    if(var == -1)
        return true;       /**solved*/

     if(nodes[var].domain.size() == 0)
        return false;

    vector<int>::iterator color;

    for (color = nodes[var].domain.begin(); color < nodes[var].domain.end(); color++){
        if (forward_check(nodes,M,var,*color)){
            nodes[var].value = *color;
            if (BT_FORWARD_CHECKING(nodes,M))
                return true;
            nodes[var].value = 0;
        }
    }
    return false;
}


int main(){
    vector<vector<int>> M;
    int size;
    int colors; /**# colors*/
    ifstream infile;
    infile.open("input.txt");
    infile>>size>>colors;
    initializeMap(M,size);
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            infile>>M[i][j];
        }
    }
    infile.close();

    /** Print Map
    cout<<size << " "<<colors<<endl;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            cout<<M[i][j]<<" ";
        }
        cout<<endl;
    }
    **/
    vector<Node> nodes(size,Node(colors));

     /**Using Backtracking with Forward Checking*/
    if(BT_FORWARD_CHECKING(nodes,M)){
        cout<<"Map coloring using Backtracking with forward checking." <<'\n';
        ofstream outfile;
        outfile.open("output.txt");
        for(int i=0;i<size;i++){
            outfile<<i <<" "<< nodes[i].value << endl;
        }
        outfile.close();
    }
    else
        cout<<"Not Solvable!"<<endl;

return 0;
}




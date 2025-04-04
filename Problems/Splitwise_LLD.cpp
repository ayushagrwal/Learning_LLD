//Splitwise

#include<bits/stdc++.h>
using namespace std;

int main(){

    string s;
    cin>>s;

    if(s == "SHOW"){
        string userShow;
        if(cin >> userShow){
            cout<<"Show user balances of "<<userShow<<endl;
        } else {
            cout<<"Show all balances"<<endl;
        }
        
    } else {
        string paidUserId;
        cin>>paidUserId;

        int paidAmount;
        cin>>paidAmount;

        int n;
        cin>>n;

        vector<string> splitUsers(n);
        for(auto &it: splitUsers){
            cin>>it;
        }

        string splitType;
        cin>>splitType;

        if(splitType == "EXACT"){
            vector<int> splitAmounts(n);
            for(auto &it: splitAmounts){
                cin>>it;
            }
        } else if (splitType == "PERCENT"){
            vector<int> splitAmounts(n);
            for(int i=0;i<n;i++){
                int x;
                cin>>x;
                
            }
        }

    }

    return 0;
}
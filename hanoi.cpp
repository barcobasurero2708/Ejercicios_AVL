#include <bits/stdc++.h>

using namespace std;


void hannoi(int n, int src, int pivot, int snk){
    if(n==1){
        cout << n << " " << src << " " << snk << endl;
        return;
    }
    hannoi(n-1, src, snk, pivot);
    cout << n << " " << src << " " << snk << endl;
    hannoi(n-1, pivot, src, snk);
}

int main(){
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    cin >> n;
    hannoi(n,1,2,3);

    return 0;
}
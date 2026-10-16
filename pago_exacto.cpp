#include <bits/stdc++.h>

using namespace std;

int subconjuntos( int i, int s, int n, vector<int> &vec){
    if(s < 0){
        return 0;
    }
    if(i == n){
        return s == 0;
    }
    return subconjuntos(i + 1, s, n, vec) + subconjuntos(i + 1, s - vec[i], n, vec);
}

int main(){
    cin.tie(0) -> sync_with_stdio(false);

    int n, s;
    cin>>n>> s;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin>> a[i];
    }
    cout << subconjuntos(0, s, n, a);

    return 0;
}
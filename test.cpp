#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
class Solution{
public:
    ll getLargestAP(ll k, vector<vector<ll>>& flights){
        
        // main issue is that we cannot create an array of length 10e9 +1...so much contiguous memory is unavailable
        //also note: we only need to create a difference array...not even the actual array
        //hence we create a MAP of difference terms such that only the boundary terms in [l,r] range vary

        map <ll, ll> difference;

        int len = flights.size(); // no. of arrays inside this 2D array

        for(int i =0; i<len; i++)
        {
            
            difference[flights[i][0]] += flights[i][2];     //l,r,x are ll too
            //by default all map values are set to 0

            difference[flights[i][1] + 1] -= flights[i][2];
        }
        // map has been made

        ll longest_len =0;
        ll curr_len = 0;
        ll prev_idx  = INT_MIN;
        for(auto it : difference)  //second is basically the difference
        {
            //key = it.firse
            //value = it.second
            //basics of maps

            if(it.second == k)
            {
                
                if(it.first == prev_idx +1)
                {
                    curr_len++;
                }
                else
                {
                    curr_len = 2;
                    //an AP has minimum two terms, so if even one difference term is found
                    //then an AP of 2 minimum terms us guaranteed
                }

                prev_idx = it.first;
            }
            else
            {
                if(longest_len< curr_len) longest_len = curr_len;

                curr_len =0;
            }
        }

        if(longest_len< curr_len) longest_len = curr_len;
        return longest_len;
    }
};
 
int main(){
    int n; ll k; cin >> n >> k;
    vector<vector<ll>> f;
 
    while(n--){
        ll l,r,x; cin >> l >> r >> x;
        f.push_back({l,r,x}); //an array of arrays
    }
 
    cout << Solution().getLargestAP(k,f);
 
    return 0;
}
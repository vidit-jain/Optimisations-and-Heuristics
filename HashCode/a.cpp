#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int m;
int t[3];

class Pizza{
public:
    int size;
    int id;
    vector<bool> Ingredients;
    Pizza(){
        Ingredients.resize(10000);
    }
    void print(){
        for(int i=0; i<Ingredients.size(); i++){
            cout<<Ingredients[i];
        }
        cout<<endl;
    }
};

class Output{
public:
    int D;
    vector<vector<int>> deliveries;

    Output(int x){
        D = x;
    }

    Output(){
        D = 0;
    }

    void addDelivery(int l, vector<int> &pizzas){
        vector<int> temp;
        temp.push_back(l);
        for(int i=0; i<pizzas.size(); i++){
            temp.push_back(pizzas[i]);
        }
        deliveries.push_back(temp);
        D++;
    }

    void print(){
        cout<<D<<endl;
        for(int i=0; i<D; i++){
            cout<<deliveries[i][0]<<" ";
            for(int j=1; j<=deliveries[i][0]; j++){
                cout<<deliveries[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};

vector<Pizza> pizzas;
unordered_map<string, int> ingredients;

void takeinput(){
    //freopen("c_many_ingredients.in", "r", stdin); 
    cin>>m;
    pizzas.resize(m);
    cin>>t[0]>>t[1]>>t[2];

    int ct = 0;

    for(int i=0; i<m; i++){
        int n;
        cin>>n;
        pizzas[i].size = n;
        pizzas[i].id = i;
        for(int j=0; j<n; j++){
            string x;
            cin>>x;
            if(ingredients.find(x)==ingredients.end()){
                ingredients[x] = ct++;
                pizzas[i].Ingredients[ct] = 1;
            }
            else{
                pizzas[i].Ingredients[ingredients[x]] = 1;
            }
        }
    }
    int sz = ingredients.size();
    for(int i=0; i<m; i++){
        pizzas[i].Ingredients.resize(sz);
    }
}

void analyze(){
    int pizza_ct = m;
    int teams = t[0]+t[1]+t[2];
    int distinctIngredients = ingredients.size();
    cout<<"No of pizzas: "<<pizza_ct<<endl;
    cout<<"Total teams: "<<teams<<endl;
    cout<<"\tTeams of size 2: "<<t[0]<<endl;
    cout<<"\tTeams of size 3: "<<t[1]<<endl;
    cout<<"\tTeams of size 4: "<<t[2]<<endl;
    cout<<"No of distinct ingredients: "<<distinctIngredients<<endl;

    // for(int i=0; i<100; i++){
    //     int p = rand()%m; 
    //     cout<<"Pizza "<<p<<endl;
    //     pizzas[p].print();
    //     cout<<endl;
    // }

}

int main(void){
    takeinput();
    // analyze();
    // cout<<endl;
    sort(pizzas.begin(), pizzas.end(), [](const auto &lhs, const auto &rhs){
        return lhs.size > rhs.size;
    });    

    int teams = t[0]+t[1]+t[2];
    Output op;
    int pizzas_left = m;
    int teams_served[3] = {0, 0, 0};
    for(int i=0; i<m;){
        if(pizzas_left>=4 && teams_served[2] < t[2]){
            vector<int> temp;
            for(int j=i; j<i+4; j++){
                temp.push_back(pizzas[j].id);
            }
            op.addDelivery(4, temp);
            i+=4;
            pizzas_left -= 4;
            teams_served[2]++;
        }
        else if(pizzas_left>=3 && teams_served[1] < t[1]){
            vector<int> temp;
            for(int j=i; j<i+3; j++){
                temp.push_back(pizzas[j].id);
            }
            op.addDelivery(3, temp);
            i+=3;
            pizzas_left -= 3;
            teams_served[1]++;
        }
        else if(pizzas_left>=2 && teams_served[0] < t[0]){
            vector<int> temp;
            for(int j=i; j<i+2; j++){
                temp.push_back(pizzas[j].id);
            }
            op.addDelivery(2, temp);
            i+=2;
            pizzas_left -= 2;
            teams_served[0]++;
        }
        else{
            break;
        }
    }
    //cout<<teams_served<<endl;
    op.print();

}
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int m, imax_sz = 100;
int t[3];

class Pizza{
public:
	int size;
	int id;
	bool taken;
	vector<bool> Ingredients;
	Pizza(){
		Ingredients.resize(imax_sz);
		taken = false;
	}

	void print(){
		for(int i=0; i<Ingredients.size(); i++){
			cout<<Ingredients[i];
		}
		cout<<endl;
	}

	int compare(vector<bool> x){
		int ct = 0;
		for(int i=0; i<Ingredients.size(); i++){
			if(Ingredients[i]==x[i] && Ingredients[i]==1)
				ct++;
		}
		return ct;
	}
};

class Team
{
public:
	int team_sz;
	int sz;
	vector<bool> bitstring;
	vector<int> pizzas_served;

	Team(){
		team_sz = 0;
		sz=0;
		bitstring.resize(imax_sz);
	}

	void addPizza(const Pizza pizza){
		for(int i=0; i<imax_sz; i++){
			if(pizza.Ingredients[i]==1) 
				bitstring[i] = 1;

			if(bitstring[i]==1)	sz++;
		}
		pizzas_served.push_back(pizza.id);
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

	void makeFromTeam(vector<Team> &Teams){
		for(int i=0; i<Teams.size(); i++){
			if(Teams[i].team_sz<=1) continue;
			addDelivery(Teams[i].team_sz, Teams[i].pizzas_served);
		}
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


struct cmp {
    bool operator () (const Pizza &lhs, const Pizza &rhs) const{
		return lhs.size > rhs.size;
	}
};

multiset<Pizza, cmp> pizzas;
unordered_map<string, int> ingredients;

void takeinput(){
	//freopen("c_many_ingredients.in", "r", stdin); 
	cin>>m;
	cin>>t[0]>>t[1]>>t[2];

	int ct = 0;

	for(int i=0; i<m; i++){
		int n;
		cin>>n;
		Pizza toadd;
		toadd.size = n;
		toadd.id = i;
		for(int j=0; j<n; j++){
			string x;
			cin>>x;
			if(ingredients.find(x)==ingredients.end()){
				ingredients[x] = ct++;
				toadd.Ingredients[ct] = 1;
			}
			else{
				toadd.Ingredients[ingredients[x]] = 1;
			}
		}
		pizzas.insert(toadd);
	}
	int sz = ingredients.size();
	imax_sz = sz;
	// for(auto &x:pizzas){
	// 	x.Ingredients.resize(sz);
	// }
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
	cout<<pizzas.size();
	// for(int i=0; i<100; i++){
	// 	int p = rand()%m; 
	// 	cout<<"Pizza "<<p<<endl;
	// 	pizzas[p].print();
	// 	cout<<endl;
	// }

}

int main(void){
	takeinput();
	//analyze();

	int tot_teams = t[0]+t[1]+t[2];
	vector<Team> teams(tot_teams);
	Output op;
	int pizzas_left = m;
	int tot_teams_served = 0;
	int teams_served[3] = {0, 0, 0};
	int singles = 0;
	int team_last_served = 0;

	while(true){
		int max_serveable = 0;
		
		if(teams_served[2] < t[2]) max_serveable = 4;
		else if(teams_served[1] < t[1])	max_serveable = 3;
		else if(teams_served[0] < t[0]) max_serveable = 2;
		else break;

		if(pizzas.empty()) break;

		if(teams[team_last_served].team_sz >= max_serveable) team_last_served++;
		if(teams[team_last_served].team_sz == 0){
			teams[team_last_served].addPizza(*pizzas.begin()); 
			pizzas.erase(pizzas.begin());
			singles++; 
			teams[team_last_served].team_sz++; 
			continue;
		}

		int mi = INT_MAX;
		auto min_it = pizzas.begin();
		int cmp;
		int k=0;
		Pizza min_pizza;	
		
		for(auto it=pizzas.begin(); it!=pizzas.end() && k < 25; it++, k++){
			Pizza pizza = *it;
			cmp = pizza.compare(teams[team_last_served].bitstring);
			if(cmp<mi){
				mi = cmp;
				min_it = it;
				min_pizza = *it;
			}
		}
		
		teams[team_last_served].addPizza(min_pizza);
		
		if(min_it != pizzas.end())
			pizzas.erase(min_it);

		teams[team_last_served].team_sz++;
		teams_served[teams[team_last_served].team_sz-2]++;

		if(teams[team_last_served].team_sz!=2)
			teams_served[teams[team_last_served].team_sz-3]--;
		else{
			tot_teams_served++;
			singles--;
		}

	}
	// analyze();
	// cout<<"Singles: "<<singles<<endl;
	// cout<<"Total teams served: "<<tot_teams_served<<endl;
	// cout<<"Teams served of size 2: "<<teams_served[0]<<endl;
	// cout<<"Teams served of size 3: "<<teams_served[1]<<endl;
	// cout<<"Teams served of size 4: "<<teams_served[2]<<endl;
	// cout<<teams_served<<endl;
	op.makeFromTeam(teams);
	op.print();

}
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include<vector>


using namespace std;

struct A {
    int ar[3];
};

void printGrid(vector<int> grid[9]){
    cout<<"\n";
	for(int j=0;j<9;j++){
		for(int i=0;i<9;i++){
			cout<<grid[j][i]<<" ";
		}
		cout<<"\n";
	}
}


vector<int> check(vector<int> grid[9], vector<int> positions, int a, int b){
	vector<int> x = grid[a];
	sort(x.begin(),x.end());
	vector<int> number;
	int p=1;
	int t=0;
	while(t<9){
		if(x[t]==0){
			t+=1;
		}
		else if(x[t]==p){
			p+=1;
			t+=1;
		}
		else{
			number.push_back(p);
			p+=1;
		}
	}
	for(int i=0;i<9-x[8];i++){
		number.push_back(x[8]+i+1);
	}
	vector<int> y;
	for(int i=0;i<9;i++){
		y.push_back(grid[i][b]);
	}
	sort(y.begin(),y.end());
	t=0;
	p=0;
	while(t<9){
		if(y[t]==0){
			t+=1;
		}
		else if(y[t]==number[p]){
			t+=1;
			number.erase(number.begin() + p);
		}
		else{
			if(y[t]>number[p]){
				p+=1;
			}
			else{
				t+=1;
			}
		}
		if(p == number.size()){
			break;
		}
	}
	int x1 = (a/3)*3;
	int y1 = (b/3)*3;
	vector<int> l1;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			l1.push_back(grid[x1+i][y1+j]);
		}
	}
	sort(l1.begin(),l1.end());
	t = 0;
	p = 0;
	while(t<9){
		if(l1[t]==0){
			t+=1;
		}
		else if(l1[t]==number[p]){
			t+=1;
			number.erase(number.begin()+p);
		}
		else{
			if(l1[t]>number[p]){
				p+=1;
			}
			else{
				t+=1;
			}
		}
		if(p==number.size()){
			break;
		}
	}
	return number;
}


bool solve(vector<int> gride[9]){
	vector<int> positions;
	struct A temp;
	vector<A> test;
	vector<int> number;
	int repeat = 0;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(gride[i][j]==0){
				positions.push_back(i*10+j);
			}
		}
	}
	while(positions.size()){
		int t = positions.size();
		int p = t;
		int l=0;
		int q=0;
		while(l<t){
			int b = positions[l]%10;
			int a = positions[l]/10;
			l+=1;
			number = check(gride, positions,a,b);

			if(repeat==0){
				if(number.size()==0){
					for(int i=0;i<test.size();i++){
                        gride[test[i].ar[0]][test[i].ar[1]] = 0;
                    }
					return false;
				}
				else if(number.size()==1){
					gride[a][b]=number[0];
					temp = {a,b,gride[a][b]};
					test.push_back(temp);
					positions.erase(positions.begin() + (--l));
					delete &temp;
				}
				else{
					q+=1;
				}
			}
			else if(repeat==1){
				if(number.size()==0){
					for(int i=0;i<test.size();i++){
                        gride[test[i].ar[0]][test[i].ar[1]] = 0;
                    }
					return false;
				}
				else if(number.size()==1){
					gride[a][b]=number[0];
					temp = {a,b,gride[a][b]};
					test.push_back(temp);
					positions.erase(positions.begin() + (--l));
					delete &temp;
				}
				else if(number.size()==2){
					gride[a][b]=number[0];
					temp = {a,b,gride[a][b]};
					test.push_back(temp);
					delete &temp;
					positions.erase(positions.begin() + (--l));
					if(solve(gride)){
						return true;
					}
					else{
						gride[a][b] = number[1];
                        temp = {a,b,gride[a][b]};
                        test.push_back(temp);
                        delete &temp;
					}
				}
				else{
					q+=1;
				}
			}
			else if(repeat==2){
				if(number.size()==0){
					for(int i=0;i<test.size();i++){
                        gride[test[i].ar[0]][test[i].ar[1]] = 0;
                    }
					return false;
				}
				else if(number.size()==1){
					gride[a][b]=number[0];
					temp = {a,b,gride[a][b]};
					test.push_back(temp);
					delete &temp;
					positions.erase(positions.begin()+ (--l));
				}
				else if(number.size()==2){
					gride[a][b]=number[0];
					temp = {a,b,gride[a][b]};
					test.push_back(temp);
					delete &temp;
					positions.erase(positions.begin()+(--l));
					if(solve(gride)){
						return true;
					}
					else{
						gride[a][b] = number[1];
                        temp = {a,b,gride[a][b]};
                        test.push_back(temp);
                        delete &temp;
					}
				}
				else if(number.size()==3){
					gride[a][b]=number[0];
					temp = {a,b,gride[a][b]};
					test.push_back(temp);
					delete &temp;
					positions.erase(positions.begin()+ (l-1));
					if(solve(gride)){
						return true;
					}
					else{
						gride[a][b] = number[1];
                        temp = {a,b,gride[a][b]};
                        test.push_back(temp);
                        delete &temp;
						if(solve(gride)){
							return true;
						}
						else{
							gride[a][b] = number[2];
                            temp = {a,b,gride[a][b]};
                            test.push_back(temp);
                            delete &temp;
						}
					}
				}
			}
			else if(repeat==3){
				if(number.size()==0){
					for(int i=0;i<test.size();i++){
                        gride[test[i].ar[0]][test[i].ar[1]] = 0;
                    }
					return false;
				}
				else if(number.size()==1){
					gride[a][b]==number[0];
					temp = {a,b,gride[a][b]};
					test.push_back(temp);
					delete &temp;
					positions.erase(positions.begin() + (--l));
				}
				else if(number.size()==2){
					gride[a][b]=number[0];
					temp = {a,b,gride[a][b]};
					test.push_back(temp);
					delete &temp;
					positions.erase(positions.begin()+ (--l));
					if(solve(gride)){
						return true;
					}
					else{
						gride[a][b] = number[1];
                        temp = {a,b,gride[a][b]};
                        test.push_back(temp);
                        delete &temp;
					}
				}
				else if(number.size()==3){
					gride[a][b]=number[0];
					temp = {a,b,gride[a][b]};
					test.push_back(temp);
					delete &temp;
					positions.erase(positions.begin() + (l-1));
					if(solve(gride)){
						return true;
					}
					else{
						gride[a][b] = number[1];
                        temp = {a,b,gride[a][b]};
                        test.push_back(temp);
                        delete &temp;
						if(solve(gride)){
							return true;
						}
						else{
							gride[a][b] = number[2];
                            temp = {a,b,gride[a][b]};
                            test.push_back(temp);
                            delete &temp;
						}
					}
				}
				else if(number.size()==4){
					gride[a][b]=number[0];
					temp = {a,b,gride[a][b]};
					test.push_back(temp);
					delete &temp;
					positions.erase(positions.begin()+(l-1));
					if(solve(gride)){
						return true;
					}
					else{
						gride[a][b] = number[1];
                        temp = {a,b,gride[a][b]};
                        test.push_back(temp);
                        delete &temp;
						if(solve(gride)){
							return true;
						}
						else{
							gride[a][b] = number[2];
                            temp = {a,b,gride[a][b]};
                            test.push_back(temp);
                            delete &temp;
							if(solve(gride)){
								return true;
							}
							else{
								gride[a][b] = number[3];
                                temp = {a,b,gride[a][b]};
                                test.push_back(temp);
                                delete &temp;
							}
						}
					}
				}
				else{
					q+=1;
				}
			}
			t = positions.size();
		}
		if(q==p){
			repeat+=1;
		}
		if(repeat>3){
			cout<<"Repeating Positions";
			return false;
		}
	}
	printGrid(gride);
	return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int> grid[9];
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            int a;
            cin>>a;
            grid[i].push_back(a);
        }
    }
    solve(grid);
    return 0;
}

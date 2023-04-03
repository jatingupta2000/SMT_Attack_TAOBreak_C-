#include<stdlib.h>
#include<stdio.h>
#include<cvc5/cvc5.h>
#include<iostream>
#include<string>
#include<stdexcept>
#include<bits/stdc++.h>

using namespace std;
using namespace cvc5;

int width=16;
int cycles=1;

// Execution of Oracle
string Cexec(string param){
	char buffer[128];
	string result = "";
	
	FILE* pipe = popen(("./Test.out " + param).c_str(), "r");
	if(!pipe){
		return "popen failed!";
	}
	
	while(!feof(pipe)){
		if(fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);
	return result;
}

// Function
Term findOutput(Solver* slv, Term a, Term b, Term clk, Term working_locking_key, Term* res){
	// Declaring Sorts
	Sort integer = slv->getIntegerSort();
	Sort boolean = slv->getBooleanSort();
	Sort bv32 = slv->mkBitVectorSort(32);

	Term res_old = slv->mkConst(slv->mkArraySort(bv32, bv32), "res_old");	
	int i;
	
	Term temp1 = slv->mkTerm(SELECT, {*res, slv->mkBitVector(32, 0u)});
	res_old = slv->mkTerm(STORE, {res_old, slv->mkBitVector(32, 0u), temp1});
	
	Term Add = slv->mkTerm(BITVECTOR_ADD, {a, b});
	Term Minus = slv->mkTerm(BITVECTOR_SUB, {a, b});
	Term temp2 = slv->mkTerm(ITE, {working_locking_key, Add, Minus});
	*res = slv->mkTerm(STORE, {*res, slv->mkBitVector(32, 0u), temp2});
	
	for(i = 1 & 4294967295; (int)i < cycles; i = (int)i + 1 & 4294967295){
		Term index = slv->mkBitVector(32, i);
		Term temp3 = slv->mkTerm(SELECT, {res_old, slv->mkTerm(BITVECTOR_SUB, {index, slv->mkBitVector(32, 1u)})});
		*res = slv->mkTerm(STORE, {*res, index, temp3});
	}
	return slv->mkTerm(SELECT, {*res, slv->mkTerm(BITVECTOR_SUB, {slv->mkBitVector(32, cycles), slv->mkBitVector(32, 1u)})});
}

// Attacking
int main(){
	Solver slv;
	Solver slv2;
	slv.setOption("produce-models", "true");
	slv.setLogic("QF_BV");
	slv2.setOption("produce-models","true");
	slv2.setLogic("QF_BV");
	
	// Executing Oracle
	string result = Cexec(" 4 5");
	cout << "Oracle Result : " << atoi(result.c_str()) << endl;

	// Declaring Sorts
	Sort integer = slv.getIntegerSort();
	Sort boolean = slv.getBooleanSort();
	Sort bv32 = slv.mkBitVectorSort(32);
	
	// Declaring Variables
	Term a = slv.mkConst(bv32, "a");
	Term b = slv.mkConst(bv32, "b");
	Term clk = slv.mkConst(boolean, "clk");
	Term k1 = slv.mkConst(boolean, "k1");
	Term k2 = slv.mkConst(boolean, "k2");
	Term out1 = slv.mkConst(bv32, "q1");
	Term out2 = slv.mkConst(bv32, "q2");
	std::string ia;
	
	//*******************************************
	//	GLOBAL VARIABLE AREA		   //
	//*******************************************
	Term res = slv.mkConst(slv.mkArraySort(bv32, bv32), "res");
	//*******************************************
	
	Term outCmp1 = slv.mkTerm(EQUAL, {findOutput(&slv, a, b, clk, k1, &res), out1});
	Term outCmp2 = slv.mkTerm(EQUAL, {findOutput(&slv, a, b, clk, k2, &res), out2});
	Term keyEq = slv.mkTerm(EQUAL, {k1, k2});
	Term outEq = slv.mkTerm(EQUAL, {out1, out2});	

	slv.assertFormula(outCmp1);
	slv.assertFormula(outCmp2);
	slv.push();
	
	slv.assertFormula(keyEq.notTerm());
	
	// ===========================================================================================================================================
	cout<<"Loop1 entered..."<<endl;
	int j = 0;
	while(slv.checkSatAssuming(outEq.notTerm()).isSat()){
		vector<Term> temp{a, b, k1, k2};
		vector<Term> m = slv.getValue(temp);
		cout<<"The Variables 1 is "<<endl;
		cout<<"A : "<<slv.getValue(a)<<endl<<"B : "<<slv.getValue(b)<<endl<<"k1 : "<<slv.getValue(k1)<<endl<<"k2 : "<<slv.getValue(k2)<<endl;
		
		ia = (" "+slv.getValue(a).getBitVectorValue(10)+" "+slv.getValue(b).getBitVectorValue(10));
		Term oa = slv.mkBitVector(32, atoi(Cexec(ia).c_str()));
		
		slv.pop();
		slv.assertFormula(slv.mkTerm(EQUAL, {findOutput(&slv, m[0], m[1], k1), oa}));
		slv.assertFormula(slv.mkTerm(EQUAL, {findOutput(&slv, m[0], m[1], k2), oa}));
		slv.push();
		slv.assertFormula(keyEq.notTerm());
		
		j++;
	}
	// ===========================================================================================================================================
/*	slv.pop();
	int p = 0;
	set<vector<Term>> pos_set;
	while(!slv.checkSatAssuming(keyEq).isUnsat()){
		vector<Term> temp{a, b, k1, k2};
		vector<Term> m = slv.getValue(temp);
		pos_set.insert(m);
		slv.assertFormula(slv.mkTerm(EQUAL, {k1, m[2]}).notTerm());
		slv.assertFormula(slv.mkTerm(EQUAL, {k2, m[2]}).notTerm());
		p++;
	}
	cout << "Possible Keys : " << p << endl;*/
	// ===========================================================================================================================================
/*	cout<<"Loop2 entered..."<<endl;
	for(auto m : pos_set){
		cout << m[2]<<endl;
	}*/
	// ===========================================================================================================================================
/*	vector<vector<Term>> pos_v;
	for(std::set<vector<Term>>::iterator it = pos_set.begin(); it != pos_set.end(); ++it){
    		pos_v.push_back(*it);
	}
	
	slv2.assertFormula(slv2.mkTerm(EQUAL, {findOutput(&slv2, a, b, k1), out1}));
	slv2.assertFormula(slv2.mkTerm(EQUAL, {findOutput(&slv2, a, b, k2), out2}));*/
	// ===========================================================================================================================================
	cout<<"Loop3 entered..."<<endl;
	/*while(pos_v.size() > 1){
		vector<Term> m1 = pos_v[0];
		vector<Term> m2 = pos_v[1];
		slv2.push();
		slv2.assertFormula(slv2.mkTerm(EQUAL, {k1, m1[2]}));
		slv2.assertFormula(slv2.mkTerm(EQUAL, {k2, m2[2]}));
		if(slv2.checkSatAssuming(outEq.notTerm()).isSat()){
			vector<Term> temp{a, b, k1, k2};
			vector<Term> m = slv.getValue(temp);
			ia = (" "+slv2.getValue(a).getBitVectorValue(10)+" "+slv2.getValue(b).getBitVectorValue(10));
			Term oa = slv2.mkBitVector(32, atoi(Cexec(ia).c_str()));
			if(slv2.checkSatAssuming(findOutput(&slv2, m1[0], m1[1], m1[2])).isUnsat()){
				pos_v.erase(m1.begin());
			}
			if(slv2.checkSatAssuming(findOutput(&slv2, m2[0], m2[1], m2[2])).isUnsat()){
				pos_v.erase(m1.begin()++);
			}
		}
		else{
			
		}
		slv2.pop();
	}
	
	cout<<"The final key is : ";
	vector<Term> m = pos_v[0];
	cout<<m[2]<<endl;*/
	//===================================================================================================
	/*cout<<"============================================================"<<endl;
	cout<<"============== ALL ASSERTIONS =============="<<endl;
	cout<<"============================================================"<<endl;
	vector<Term> v = slv.getAssertions();
	for(auto item: v){
        	cout << item << endl;
    	}
    	cout<<"============================================================"<<endl;
    	cout<<"============================================================"<<endl;
    	cout<<"============================================================"<<endl;*/

	
	return 0;
}

#ifndef NAME_ANALYSIS_HPP
#define NAME_ANALYSIS_HPP

#include "ast.hpp"
#include "symbol_table.hpp"
#include "types.hpp"
#include <unordered_set>


namespace DTL {



    
class NameAnalysis{
public:
	static NameAnalysis * build(ProgramNode * astIn){
		NameAnalysis * nameAnalysis = new NameAnalysis;
		SymbolTable * symTab = new SymbolTable();
		symTab->na = nameAnalysis;
		bool res = astIn->nameAnalysis(symTab);
		bool res2 = nameAnalysis->CheckDeferred(symTab);
		
		delete symTab;
		if (!res || !res2){ return nullptr; }

		nameAnalysis->ast = astIn;
		return nameAnalysis;
	}
	ProgramNode * ast;

	void AddDeferred(IDNode* node);
	bool CheckDeferred(SymbolTable* symTab);
	std::unordered_set<std::string> m_Declared;
	std::vector<IDNode*> m_Deferred;
private:

	NameAnalysis(){
	}
};





}












#endif
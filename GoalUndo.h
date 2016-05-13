#ifndef _GOALUNDO_H_
#define _GOALUNDO_H_

#include <stack>
#include <queue>
#include <string>

class GoalUndo
{
	public:
		void undoGoal();
		void undoOperation();
		void undoOperation(std::string);
		std::string getOperations();
		std::string getGoal();
		void addOperation(std::string, std::string);
		void addOperation(std::string);
	private:
		struct Goal{
			std::string name;
			std::vector <std::string> operations;
		};
		std::stack <Goal> goals;
};

#endif
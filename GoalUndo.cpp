#include "GoalUndo.h"
#include <string>

void GoalUndo::undoGoal()
{
	if( !goals.empty() )
	{
		goals.pop();
	}
}

void GoalUndo::undoOperation()
{
	if( !goals.empty() )
	{
		goals.top().operations.pop_back();

		if( goals.top().operations.empty() )
		{
			undoGoal();
		}
	}
}

void GoalUndo::undoOperation(std::string undoOp)
{

	if( !goals.empty() )
	{
		std::vector<std::string>::iterator iter;

		for(iter=goals.top().operations.end(); 
			iter > goals.top().operations.begin();
			--iter )
		{
			if( iter->compare(undoOp) == 0 ) //match!
			{
				goals.top().operations.erase(iter);
				break; //only remove first LIFO match
			}
		}
	}
}

std::string GoalUndo::getGoal()
{
	if( goals.empty() )
		return "";
	else
		return goals.top().name;
}

std::string GoalUndo::getOperations()
{
	if( goals.empty() )
		return "";
	else
	{
		std::string allOps = "";
		std::vector <std::string> listOps = goals.top().operations;
		
		std::vector<std::string>::iterator iter;
		//std::vector<std::string>::iterator last=goals.top().operations.end()--;
		for( iter=goals.top().operations.begin(); 
			 iter < goals.top().operations.end();
			 iter++ )
		{
			allOps += *iter;
			//add comma between each operation (but not last)
			if( iter < goals.top().operations.cend()-1 ) 
				allOps += " ";
		}
		return allOps;
	}
}

void GoalUndo::addOperation(std::string newGoal, std::string newOp)
{
	if(!newGoal.empty() && !newOp.empty())
	{
		Goal latest;
		latest.name = newGoal;
		goals.push(latest);
		addOperation( newOp );
	}
}

void GoalUndo::addOperation(std::string newOp)
{
	if(!newOp.empty())
	{
		if( goals.empty() )
		{
			addOperation( newOp, newOp );
		}
		else
		{
			goals.top().operations.push_back(newOp);
		}
	}
}
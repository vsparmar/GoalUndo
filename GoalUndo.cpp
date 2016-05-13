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
		goals.top().operations.pop();

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
		for(int i=goals.top().operations.size()-1; i>=0; i--)
		{
			if( strcmp(goals.top().operations.at(i),undoOp) == 0 ) //match!
			{
				goals.top().operations.remove(i);
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
		for(int i=0; i<listOps.size(); i++)
		{
			allOps += listOps.at(i);
			//add comma between each operation (but not last)
			if( i != listOps.size()-1 ) 
				allOps += " ";
		}
	}
}

void GoalUndo::addOperation(std::string newGoal, std::string newOp)
{
	Goal latest;
	latest.name = newGoal;
	goals.push(latest);
	addOperation( newOp );
}

void GoalUndo::addOperation(std::string newOp)
{
	if( goals.empty() )
	{
		addOperation( newOp, newOp );
	}
	else
	{
		goals.operations.push_back(newOp);
	}
}


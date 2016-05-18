/**
 * Unit Tests for GoalUndo class
**/

/*

Name : Vijay Parmar

*/




#include <gtest/gtest.h>
#include "GoalUndo.h"
 
class GoalUndoTest : public ::testing::Test
{
	protected:
		GoalUndoTest(){}
		virtual ~GoalUndoTest(){}
		virtual void SetUp(){}
		virtual void TearDown(){}
};

TEST(GoalUndoTest, sanityCheck)
{
    ASSERT_TRUE(true);
}

TEST(GoalUndoTest, addOperation_ShouldSkipEmptyOperationArgument)
{
    GoalUndo goalUndo;
    goalUndo.addOperation("");

    EXPECT_TRUE(goalUndo.getOperations().empty());
}

TEST(GoalUndoTest, addOperation_ShouldCreateGoalWithSameNameAsOperation)
{
    GoalUndo goalUndo;
    std::string newOp = "MyTestOperation";
    goalUndo.addOperation(newOp);

    EXPECT_EQ(newOp, goalUndo.getOperations());
    EXPECT_EQ(newOp, goalUndo.getGoal());
}

TEST(GoalUndoTest, addOperation_ShouldAddOperationToRecentGoal)
{
    GoalUndo goalUndo;
    std::string newOp1 = "MyTestOperation";
    std::string newOp2 = "NewOperation";
    goalUndo.addOperation(newOp1);
    goalUndo.addOperation(newOp2);


    EXPECT_EQ(newOp1 + " " + newOp2, goalUndo.getOperations());
    EXPECT_EQ(newOp1, goalUndo.getGoal());
}

TEST(GoalUndoTest, addOperation_ShouldSkipEmptyGoalArgument)
{
    GoalUndo goalUndo;
    std::string newOp = "MyTestOperation";
    std::string newGoal = "";

    goalUndo.addOperation(newGoal, newOp);

    EXPECT_TRUE(goalUndo.getGoal().empty());
    EXPECT_TRUE(goalUndo.getOperations().empty());
}

TEST(GoalUndoTest, addOperation_ShouldSkipEmptyOperationsArgument)
{
    GoalUndo goalUndo;
    std::string newOp = "";
    std::string newGoal = "MyTestGoal";

    goalUndo.addOperation(newGoal, newOp);

    EXPECT_TRUE(goalUndo.getGoal().empty());
    EXPECT_TRUE(goalUndo.getOperations().empty());
}


TEST(GoalUndoTest, addOperation_ShouldAddNewOperationWithinNewGoal)
{
    GoalUndo goalUndo;
    std::string newOp = "MyTestOperation";
    std::string newGoal = "MyTestGoal";

    goalUndo.addOperation("oldGoal", "oldOp");
    goalUndo.addOperation(newGoal, newOp);

    EXPECT_EQ(newGoal, goalUndo.getGoal());
    EXPECT_EQ(newOp, goalUndo.getOperations());
}


TEST(GoalUndoTest, getOperations_ShouldReturnAllOperationsInRecentGoal)
{
    GoalUndo goalUndo;
    goalUndo.addOperation("goal1", "oper1");
    goalUndo.addOperation("oper2");

    EXPECT_EQ(goalUndo.getGoal(), "goal1");
    EXPECT_EQ(goalUndo.getOperations(), "oper1 oper2");
}

TEST(GoalUndoTest, getOperations_ShouldReturnEmptyStringIfGoalsAreEmpty)
{
    GoalUndo goalUndo;
    EXPECT_EQ(goalUndo.getOperations(), "");
}


TEST(GoalUndoTest, getGoal_ShouldReturnEmptyString)
{
    GoalUndo goalUndo;
    EXPECT_TRUE(goalUndo.getGoal().empty());
}

TEST(GoalUndoTest, undoOperationOverloaded_ShouldNotCrashIfGoalsAreEmpty)
{
    GoalUndo goalUndo;
    goalUndo.undoOperation("MyOperation");

    EXPECT_TRUE(true);
}

TEST(GoalUndoTest, undoOperation_ShouldRemoveNothingIfThereAreNoMatches)
{
    GoalUndo goalUndo;
    std::string newOp = "MyOperation";

    goalUndo.addOperation(newOp);
    goalUndo.undoOperation("something");

    EXPECT_EQ(goalUndo.getOperations(), newOp);
}

TEST(GoalUndoTest, undoOperation_ShouldRemoveFirstMatch)
{
    GoalUndo goalUndo;
     std::string newOp = "MyOperation";

    goalUndo.addOperation("newGoal", newOp);
    goalUndo.addOperation(newOp);
    goalUndo.undoOperation(newOp);

    EXPECT_EQ(goalUndo.getOperations(), newOp);
}

TEST(GoalUndoTest, undoOperation_ShouldRemoveOperationFromTheMostRecentGoal)
{
    GoalUndo goalUndo;
    std::string newOp = "MyOperation";

    goalUndo.addOperation("newGoal", newOp);
    goalUndo.addOperation("secondGoal", newOp);
    goalUndo.undoOperation(newOp);

    EXPECT_EQ(goalUndo.getGoal(), "newGoal"); //goal should not exist without operation
    EXPECT_EQ(goalUndo.getOperations(), newOp);
}

TEST(GoalUndoTest, undoOperation_ShouldRemoveTheMostRecentlyAddedOperation)
{
    GoalUndo goalUndo;
    std::string newGoal = "MyGoal";

    goalUndo.addOperation(newGoal, "oper1");
    goalUndo.addOperation("oper2");
    goalUndo.undoOperation();

    EXPECT_EQ(goalUndo.getOperations(), "oper1");
}

TEST(GoalUndoTest, undoOperation_ShouldRemoveOperationAndGoal)
{
    GoalUndo goalUndo;

    goalUndo.addOperation("newGoal", "newOperation");
    goalUndo.undoOperation();

    EXPECT_TRUE(goalUndo.getOperations().empty());
    EXPECT_TRUE(goalUndo.getGoal().empty());
}

TEST(GoalUndoTest, undoOperation_ShouldNotCrashIfGoalsAreEmpty)
{
    GoalUndo goalUndo;
    goalUndo.undoOperation();

    EXPECT_TRUE(true);
}

TEST(GoalUndoTest, undoGoal_ShouldNotCrashIfGoalsAreEmpty)
{
    GoalUndo goalUndo;

    goalUndo.undoGoal();

    EXPECT_TRUE(true);
}

TEST(GoalUndoTest, undoGoal_ShouldRemoveRecentlyAddedGoalWithOperations)
{
    GoalUndo goalUndo;
    std::string firstOp = "firstOperation";

    goalUndo.addOperation(firstOp);
    goalUndo.addOperation("testGoal", "testOperation");
    goalUndo.addOperation("testOperation");
    goalUndo.undoGoal();

    EXPECT_EQ(goalUndo.getOperations(), firstOp);
    EXPECT_EQ(goalUndo.getGoal(), firstOp);
}








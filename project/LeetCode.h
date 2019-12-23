#pragma once
#include <vector>
using namespace std;
#include<iostream>;
#include <unordered_map>

//1、Two Sum
//给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
//你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
//给定 nums = [2, 7, 11, 15], target = 9
//因为 nums[0] + nums[1] = 2 + 7 = 9
//所以返回[0, 1]
class  SolutionTwoSum
{
public:
	vector<int>  GetIndexs(const vector<int>&  Nums,int Target)
	{
		vector<int>  NumsEx;
		if (Nums.size()<2)
		{
			cout << "数组中的元素的个数小于2"<<endl;
		}
		else
		{
			for (int i=0;i < Nums.size();i++)
			{
				for (int j= i + 1; j< Nums.size();j++)
				{
					if (Nums.at(i) + Nums.at(j) == Target) { NumsEx.push_back(i+1); NumsEx.push_back(j+1); }
				}
			}
		}
		return NumsEx;
	}
};

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> m;
		vector<int> res;
		for (int i = 0; i < nums.size(); ++i) {
			m[nums[i]] = i;
		}
		for (int i = 0; i < nums.size(); ++i) {
			int t = target - nums[i];
			if (m.count(t) && m[t] != i) {
				res.push_back(i);
				res.push_back(m[t]);
				break;
			}
		}
		return res;
	}
};






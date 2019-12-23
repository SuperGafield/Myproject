#pragma once
#include <vector>
using namespace std;
#include<iostream>;
#include <unordered_map>

//1��Two Sum
//����һ���������� nums ��һ��Ŀ��ֵ target�������ڸ��������ҳ���ΪĿ��ֵ���� ���� ���������������ǵ������±ꡣ
//����Լ���ÿ������ֻ���Ӧһ���𰸡����ǣ��㲻���ظ��������������ͬ����Ԫ�ء�
//���� nums = [2, 7, 11, 15], target = 9
//��Ϊ nums[0] + nums[1] = 2 + 7 = 9
//���Է���[0, 1]
class  SolutionTwoSum
{
public:
	vector<int>  GetIndexs(const vector<int>&  Nums,int Target)
	{
		vector<int>  NumsEx;
		if (Nums.size()<2)
		{
			cout << "�����е�Ԫ�صĸ���С��2"<<endl;
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






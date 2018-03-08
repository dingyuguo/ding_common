/*************************************************************************
    > File Name: test_dir_op.cpp
    > Author: laoding
    > Mail: dyg1993@foxmail.com 
    > Created Time: 三  2/28 09:39:02 2018
 ************************************************************************/

#include<iostream>
#include"dir_op.hpp"

using namespace std;


int main(int argc,char ** argv)
{
	string dirname(argv[1]);

	vector<string>   file_vec;
	dir_op ss(dirname);
	//ss.print_content();
	//ss.print_catalogue();
	//ss.print_file();
	ss.set_postfix_buff("xml");
	ss.set_postfix_buff("jpg");
	vector<string> img_vec = ss.get_postfix_file_with_path();
	for(int i = 0; i < img_vec.size();i++)
	{
		cout << img_vec[i] << endl;
	}
	return 0;
}

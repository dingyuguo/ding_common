#ifndef __DIR_OP_HEADER__
#define __DIR_OP_HEADER__ 
#include<iostream>

#include<string>
#include<vector>

#include<stdio.h>
#include<dirent.h>
using namespace std;
class dir_op{
	public:
		dir_op(string dir_name);

		~dir_op();
		void read_dir();
		void print_content();
		void print_catalogue();
		void print_file();
		void set_postfix_buff(string postfix);
		void set_postfix_buff(vector<string> postfix_vec);
		vector<string > get_postfix_file();

	vector<string > get_postfix_file_with_path();
	private:
		string  _dir_name;
		DIR *_dp;
		struct dirent *_dirp;
		vector<string> _dir_content;//根目录下的全部文件
		vector<string> _catalogue_vec;//根目录下的目录文件
		vector<string> _file_vec;//根目录下的普通文件
		vector<string> _unknow_file_vec;
		vector<string> _postfix_vec;//需要搜索的后缀
		vector<string> _postfix_file_vec;//符合条件的文件
		vector<string> _postfix_file_with_path_vec;//带有路径的
};

#endif


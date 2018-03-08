/************************************************************************
    > File Name: dir_op.cpp
    > Author: laoding
    > Mail: dyg1993@foxmail.com 
    > Created Time: 二  2/27 15:57:28 2018
 ************************************************************************/

#include<iostream>

#include<string>
#include<vector>

#include<stdio.h>
#include<dirent.h>
#include"dir_op.hpp"

using namespace std;

dir_op::dir_op(string dir_name)
{
	int str_len = dir_name.size();
	if(dir_name[str_len-1] != '/')
	{
		_dir_name = dir_name + '/';
	}else{
		_dir_name = dir_name;
	}
	_dp = opendir(_dir_name.c_str());
	read_dir();
}
dir_op::~dir_op()
{
	closedir(_dp);
}
void  dir_op::read_dir()
{
	if(_dp==NULL)
	{
		_dp = opendir(_dir_name.c_str());
		if(!_dp)
		{
			cout << "Error:Can't Open " << _dir_name << endl;
		}
	}
	while((_dirp = readdir(_dp) )!= NULL)
	{
		_dir_content.push_back(string(_dirp->d_name));
		if(_dirp->d_type == 4)/*目录文件*/ 
			_catalogue_vec.push_back(string(_dirp->d_name));
		else if(_dirp->d_type == 8)
			_file_vec.push_back(string(_dirp->d_name));
		else 
			_unknow_file_vec.push_back(_dirp->d_name);
	}
}
void dir_op::print_content()
{
	cout << _dir_name << "  下的全部文件,不含子目录内的文件" << endl;
	for(int i = 0; i < _dir_content.size();i++)
	{
		cout << _dir_content[i] << endl;
	}
}
void dir_op::print_catalogue()
{
	cout << _dir_name << "  下的目录文件" << endl;
	for(int i = 0; i < _catalogue_vec.size();i++)
	{
		cout << _catalogue_vec[i] << endl;
	}
}
void dir_op::print_file()
{
	cout << _dir_name << "  下的普通文件" << endl;
	for(int i = 0; i < _file_vec.size();i++)
	{
		cout << _file_vec[i] << endl;
	}
}
void dir_op::set_postfix_buff(string postfix)
{
	if(postfix.empty())
	{
		cout << "postfix is empty " << endl;
	}else
	{
		_postfix_vec.push_back(postfix);
	}
}
void dir_op::set_postfix_buff(vector<string> postfix_vec)
{
	if(postfix_vec.size()==0)
	{
		cout << "postfix_vec is empty" << endl;
	}else
	{
		_postfix_vec.insert(_postfix_vec.end(),postfix_vec.begin(),postfix_vec.end());
	}
}

vector<string > dir_op::get_postfix_file()
{
	/*去掉隐藏文件*/
	vector<string> tmp_vec;
	for(int i = 0; i < _file_vec.size();i++)
	{
		if(_file_vec[i].at(0) != '.')
		{
			tmp_vec.push_back(_file_vec[i]);
		}
	}
	/*获取指定后缀文件*/
	int pos = -1;
	for(int i = 0; i < tmp_vec.size();i++)
	{
		pos = tmp_vec[i].find_last_of('.');
		if( pos != string::npos)
		{
			string sub_str = tmp_vec[i].substr(pos+1,tmp_vec.size()-1);
			vector<string>::iterator result = find(_postfix_vec.begin(),_postfix_vec.end(),sub_str);
			if(result != _postfix_vec.end())
			{
				_postfix_file_vec.push_back(tmp_vec[i]);
			}
		}
	}
	std::sort(_postfix_file_vec.begin(),_postfix_file_vec.end());
	return _postfix_file_vec;
}
vector<string > dir_op::get_postfix_file_with_path()
{
	if(_postfix_file_vec.size() == 0)
	{
		get_postfix_file();
	}
	for(int i = 0; i < _postfix_file_vec.size();i++)
	{
		_postfix_file_with_path_vec.push_back(_dir_name + _postfix_file_vec[i]);
	}
	return _postfix_file_with_path_vec;
}

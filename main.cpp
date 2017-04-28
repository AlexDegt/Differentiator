#include <cstdio>
#include <vector>
#include <iostream>
#include <malloc.h>
#include <cstdlib>
#include <new>
#include <stdio.h>
#include <assert.h>
#include <string>
#include <assert.h>
#include <cstring>
#include <conio.h>
#include <math.h>

//using namespace std;

typedef std::string data;

class node
{
    public:
    int length_str(char * str);
    void print();
    void print_file(FILE * out);
    void read_file(FILE * out);
    void create_tree(FILE * f);
    node * left;
	node * right;
	node * parent;
	data data_;

	std::vector<std::string> var_mass;
    void diff_process(node curr_node);
    void diff_const();
    void diff_1degree();
    void diff_plus_minus();
    void diff_multipl();
    void diff_cos();
    void diff_sin();
    void get_var();

    explicit node(data word):
        left(),
        right(),
        parent(),
        data_(word),
        var_mass()
        {}

    explicit node():
        data_(),
        left(),
        right(),
        parent(),
        var_mass()
        {}
};

void node::print()
{
    printf("%s\n", data_.c_str());
    if (left) left->print();
    if (right) right->print();
}

void node::print_file(FILE * out)
{
    fprintf(out, "( %s ", data_.c_str());
    if (left) left->print_file(out);
    else  fprintf(out, "NN");
    if (right) right->print_file(out);
    fprintf(out, " )");
}

void node::create_tree(FILE * f)
{
    char letter[1];
    fscanf(f, "%c", letter);
    while ((letter[0] == ' ') || (letter[0] == ')'))
    {
        char letter1[1];
        fscanf(f, "%c", letter1);
        letter[0] = letter1[0];
    }
    if (letter[0] == '(')
    {
        char space[1];
        fscanf(f, "%c", space);
        node * x1 = new node("");
        node * x2 = new node("");
        left = x1;
        right = x2;
        left->parent = this;
        right->parent = this;

        this->create_tree(f);
        left->create_tree(f);
        if (left->data_ == "")
            left = NULL;
        right->create_tree(f);
        if (right->data_ == "")
            right = NULL;
    }
    if ((letter[0] != ' ') && (letter[0] != ')') && (letter[0] != '(') && (letter[0] != 'N'))
    {
        std::string str;
        while (letter[0] != ' ')
        {
            str += letter[0];
            char letter1[1];
            fscanf(f, "%c", letter1);
            letter[0] = letter1[0];
        }
        data_ = str;
        //printf("%i\n", data_);
    }
}

int node::length_str(char * str)
{
    int i = 0;
    while (str[i]) i++;
    return i;
}

int length_of_str(const char * str)
{
    int i = 0;
    while (str[i]) i++;
    return i;
}

int length_of_num(int num)
{
    int i = 0;
    while (num)
    {
        num = num / 10;
        i++;
    }
    return i;
}

bool is_number(const char * str_num)
{
    int length_str = length_of_str(str_num);
    if ((length_str == 1) && (str_num[0] == '0'))
        return true;
    int number = atoi(str_num);
    if ((length_of_num(number)) == (length_of_str(str_num)))
        return true;
    else
        return false;
}

void node::diff_process(node * curr_node)
{
    //printf("%s\n", curr_node.data_.c_str());
    if ((curr_node->data_ == "+") || (curr_node->data_ == "-"))
        diff_plus_minus(*curr_node);
    if (is_number(curr_node->data_.c_str()))
        diff_const(*curr_node);
}

void node::get_var()
{
    printf("Enter variables\n");
    int eof = -1;
    while (eof)
    {
        char var[100];
        eof = ~scanf("%s", var);
        if (eof)
            var_mass.push_back(var);
    }
}

/*void node::diff_const(node corr_node)
{
    //printf("!");
    curr_node.data_.clear();
    curr_node.data_.push_back('0');
}*/

/*void node::diff_plus_minus(node corr_node)
{
    if ((curr_node.left != NULL) && (curr_node.right != NULL))
    {
        diff_process(*curr_node.left);
        diff_process(*curr_node.right);
    }
    else
        printf("You need numbers to add or sobstrakt\n");
}*/

int main()
{
    FILE * f = fopen("differ.txt","r");
    node q;
    q.create_tree(f);
    q.get_var();
    //q.diff_process();
    //q.print();

    getch();
    return 0;
}

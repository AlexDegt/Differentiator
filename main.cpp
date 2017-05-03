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

    explicit node(data word):
        left(),
        right(),
        parent(),
        data_(word)
        {}

    explicit node():
        data_(),
        left(),
        right(),
        parent()
        {}
};

class diff
{
    public:
    std::string var;
    node * curr_node;
    void diff_process();
    void diff_const();
    void diff_first_degree();
    void diff_plus_minus();
    void diff_multipl();
    void diff_division();
    void diff_cos();
    void diff_sin();
    void get_var();
    diff():
        var()
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

void diff::diff_process()
{
    //printf("%s\n", curr_node->data_.c_str());
    if ((curr_node->data_ == "+") || (curr_node->data_ == "-"))
        diff_plus_minus();
    if (is_number(curr_node->data_.c_str()))
        diff_const();
    if (curr_node->data_ == "*")
        diff_multipl();
    if (curr_node->data_ == "/")
        diff_division();
}

void diff::get_var()
{
    printf("Enter variables\n");
    char var_temp[100];
    scanf("%s", var_temp);
    var = var_temp;
    /*int eof = -1;
    while (eof)
    {
        char var[100];
        eof = ~scanf("%s", var);
        if (eof)
            var_mass.push_back(var);
    }*/
}

void diff::diff_const()
{
    //printf("!");
    curr_node->data_.clear();
    curr_node->data_.push_back('0');
}

void diff::diff_first_degree()
{

}

void diff::diff_plus_minus()
{
    if ((curr_node->left != NULL) && (curr_node->right != NULL))
    {
        curr_node->left->parent = curr_node;
        curr_node = curr_node->left;
        diff_process();
        curr_node = curr_node->parent;
        curr_node->right->parent = curr_node;
        curr_node = curr_node->right;
        diff_process();
        curr_node = curr_node->parent;
    }
    else
        printf("You need numbers to add or sobstrakt\n");
}

void diff::diff_multipl()
{
    node * copy = curr_node;
    node * mult1 = new node();
    node * mult2 = new node();
    node * left_f = new node();
    node * right_f = new node();
    mult1->data_ = "*";
    mult2->data_ = "*";
    curr_node->data_ = "+";
    curr_node->left->parent = mult1;
    curr_node->right->parent = mult2;
    mult1->left = curr_node->left;
    mult1->right = right_f;
    mult2->left = curr_node->right;
    mult2->right = left_f;
    (*mult1->right) = (*curr_node->right);
    (*mult2->right) = (*curr_node->left);
    mult1->parent = curr_node;
    mult2->parent = curr_node;
    curr_node->left = mult1;
    curr_node->right = mult2;
    curr_node = mult1->right;
    diff_process();
    curr_node = mult2->right;
    diff_process();
    curr_node = copy;
}

void diff::diff_division()
{
    node * copy = curr_node;
    node * cap = new node();
    node * cap_left = new node();
    node * cap_right = new node();
    node * mult1_left = new node();
    node * mult2_left = new node();
    cap->left = cap_left;
    cap->right = cap_right;
    (*cap->left) = (*curr_node->right);
    cap->data_ = "^";
    cap->right->data_ = "2";
    node * minus = new node();
    minus->data_ = "-";
    node * mult1 = new node();
    node * mult2 = new node();
    mult1->data_ = "*";
    mult2->data_ = "*";
    minus->left = mult1;
    minus->right = mult2;
    mult1->parent = minus;
    mult2->parent = minus;
    mult1->left = mult1_left;
    mult2->left = mult2_left;
    (*mult1->left) = (*curr_node->right);
    (*mult2->left) = (*curr_node->left);
    mult1->right = curr_node->left;
    mult2->right = curr_node->right;
    curr_node->left = minus;
    minus->parent = curr_node;
    curr_node->right = cap;
    cap->parent = curr_node;
    curr_node = mult1->right;
    diff_process();
    curr_node = mult2->right;
    diff_process();
    curr_node = copy;
}

int main()
{
    FILE * f = fopen("differ.txt","r");
    node q;
    diff w;
    q.create_tree(f);
    w.curr_node = &q;
    w.get_var();
    w.diff_process();
    w.curr_node->print();

    getch();
    return 0;
}

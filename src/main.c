/*
 * Sort(assembler) with parameters
 *
 * Roman Shishkin
 * Last update: 19.10.2020
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define error_print(...) fprintf(stderr, __VA_ARGS__)
#define std_print(...) fprintf(stdout, __VA_ARGS__)

const char *FIRST_PARAMETER = "--from=", *SECOND_PARAMETER = "--to=";
const int FIRST_PARAMETER_LENGTH = 7, SECOND_PARAMETER_LENGTH = 5, MAX_ARRAY_LENGTH = 100;

struct parameters
{
    int from;
    int to;
    bool exist_from;
    bool exist_to;
};

void bubble_sort(int array[], int array_length);

void copy_array(const int copying_array[], int receiving_array[], int array_length)
{
    for(int index = 0; index < array_length; index++)
        receiving_array[index] = copying_array[index];
}

int compare_arrays(const int first_array[], const int second_array[], int array_length)
{
    int count_equal_elements = 0;
    for(int index = 0; index < array_length; index++)
        if(first_array[index] != second_array[index])
            count_equal_elements++;
    return count_equal_elements;
}

bool is_first_parameter(const char argument[])
{
    if(strlen(argument) < ((size_t) FIRST_PARAMETER_LENGTH))
        return 0;
    for(int index = 0; index < FIRST_PARAMETER_LENGTH; index++)
        if(argument[index] != FIRST_PARAMETER[index])
            return 0;
    return 1;
}

bool is_second_parameter(const char argument[])
{
    if(strlen(argument) < ((size_t) SECOND_PARAMETER_LENGTH))
        return 0;
    for(int index = 0; index < SECOND_PARAMETER_LENGTH; index++)
        if(argument[index] != SECOND_PARAMETER[index])
            return 0;
    return 1;
}

int calc_parameter_from(char argument[])
{
    int parameter_from = 0;
    for(size_t index = FIRST_PARAMETER_LENGTH; index < strlen(argument); index++)
    {
        if(argument[index] > '9' || argument[index] < '0')
            break;
        parameter_from = parameter_from * 10 + (argument[index] - '0');
    }
    return parameter_from;
}

int calc_parameter_to(char argument[])
{
    int parameter_to = 0;
    for(size_t index = SECOND_PARAMETER_LENGTH; index < strlen(argument); index++)
    {
        if(argument[index] > '9' || argument[index] < '0')
            break;
        parameter_to = parameter_to * 10 + (argument[index] - '0');
    }
    return parameter_to;
}

int check_input_parameters(int parameter_count, char *parameter[])
{
    if(parameter_count < 1)
        return -1;
    else if(parameter_count > 2)
        return -2;
    if(parameter_count == 1)
        if(!is_first_parameter(parameter[1]) && !is_second_parameter(parameter[1]))
            return -4;
    if(parameter_count == 2)
    {
        if(!is_first_parameter(parameter[1]) && !is_second_parameter(parameter[2]))
            if (!is_first_parameter(parameter[2]) && !is_second_parameter(parameter[1]))
                return -4;
        if(is_first_parameter(parameter[1]) && is_first_parameter(parameter[2]))
            return -3;
        if(is_second_parameter(parameter[1]) && is_second_parameter(parameter[2]))
            return -3;
    }
    return 1;
}

void calc_parameters(int argument_count, char *arguments[], struct parameters *parameter)
{
    parameter->exist_from = 0;
    parameter->exist_to = 0;
    if(is_first_parameter(arguments[1]))
    {
        parameter->from = calc_parameter_from(arguments[1]);
        parameter->exist_from = 1;
    }
    else if(is_second_parameter(arguments[1]))
    {
        parameter->to = calc_parameter_to(arguments[1]);
        parameter->exist_to = 1;
    }
    if(argument_count == 2)
    {
        if(is_first_parameter(arguments[2]))
        {
            parameter->from = calc_parameter_from(arguments[2]);
            parameter->exist_from = 1;
        }
        else if(is_second_parameter(arguments[2]))
        {
            parameter->to = calc_parameter_to(arguments[2]);
            parameter->exist_to = 1;
        }
    }
}

void input_array(int *array, int *array_length, struct parameters parameter)
{
    int input_decimal;
    int index = 0;
    while(scanf("%d", &input_decimal))
    {
        if(parameter.exist_from && parameter.exist_to)
        {
            if(input_decimal < parameter.from)
                std_print("%d ", input_decimal);
            if(input_decimal > parameter.to)
                error_print("%d ", input_decimal);
            if(input_decimal >= parameter.from && input_decimal <= parameter.to)
                array[index++] = input_decimal;
        }
        if(parameter.exist_from && !parameter.exist_to)
        {
            if(input_decimal < parameter.from)
                std_print("%d ", input_decimal);
            else array[index++] = input_decimal;
        }
        if(!parameter.exist_from && parameter.exist_to)
        {
            if(input_decimal > parameter.to)
                error_print("%d ", input_decimal);
            else array[index++] = input_decimal;
        }
    }
    *array_length = index;
}

int main(int argc, char *argv[])
{
    struct parameters parameter;
    int starting_array[MAX_ARRAY_LENGTH], sorted_array[MAX_ARRAY_LENGTH], array_length;
    int exit_code = check_input_parameters(argc - 1, argv);
    if(exit_code < 0) return exit_code;
    calc_parameters(argc - 1, (char **) argv, &parameter);
    input_array((int *) starting_array, &array_length, parameter);
    copy_array(starting_array, sorted_array, array_length);
    bubble_sort((int *) sorted_array, array_length);
    exit_code = compare_arrays(starting_array, sorted_array, array_length);
    return exit_code;
}

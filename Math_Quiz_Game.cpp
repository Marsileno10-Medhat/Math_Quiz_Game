#include <iostream>
#include <cstdlib>

using namespace std;

enum en_operation_type {add = 1, substract = 2, multiplication = 3, divide = 4, mix_op_type = 5};
enum en_game_levels {easy_level = 1, medium_level = 2, hard_level = 3, mix_level = 4};

struct st_questions
{
    short number1;
    short number2;
    en_operation_type op_type;
    en_game_levels question_level;
    int correct_answer;
    int player_answer;
    bool question_answer_status = false;
};

struct st_quizz
{
    st_questions questionsList[100];
    short number_of_questions;
    en_game_levels game_level;
    en_operation_type game_op_type;
    short correct_answers_number = 0;
    short wrong_answers_number = 0;
    bool final_results = false;
};

int random_number(int from, int to)
{
    int ran_num = rand() % (to - from + 1) + from;
    return ran_num;
}

void set_screen_color(bool answer_status)
{
    if (answer_status)
    {
        system("color 2F"); // turn color to green.
        cout << "\a";
    }
    else
    {
        system("color 4F"); // turn color to red.
        cout << "\a";
    }
}

short read_questions_number()
{
    short number = 0;
    do
    {
        cout << "How many questions do you want to answer? [1:100]   ";
        cin >> number;
    } while (number < 1 || number > 100);
    return number;
}

en_game_levels read_game_level()
{
    short number = 0;
    do
    {
        cout << "Enter question level. [1]Easy, [2]Medium, [3]Hard, [4]Mix.   ";
        cin >> number;
    } while (number < 1 || number > 4);
    return (en_game_levels) number;
}

en_operation_type read_game_op_type()
{
    short number = 0;
    do
    {
        cout << "Enter question level. [1]Add, [2]Substract, [3]Multiplication, [4]Divide, [5]Mix.   ";
        cin >> number;
    } while (number < 1 || number > 5);
    return (en_operation_type) number;
}

int read_player_answer()
{
    int answer = 0;
    cin >> answer;
    return answer;
}

string op_type_symbol(en_operation_type operation_type)
{
    switch (operation_type)
    {
        case en_operation_type::add:
        return "+";
        case en_operation_type::divide:
        return "/";
        case en_operation_type::multiplication:
        return "*";
        case en_operation_type::substract:
        return "-";
        default:
        return "Mix";
    }
}

string game_level_text(en_game_levels game_level)
{
    string levels[4] = {"Easy", "Medium", "Hard", "Mix"};
    return levels[game_level - 1];
}

int simple_calculator(int number1 ,int number2 ,en_operation_type operation_type)
{
    switch (operation_type)
    {
        case en_operation_type::add:
        return number1 + number2;
        case en_operation_type::substract:
        return number1 - number2;
        case en_operation_type::divide:
        return number1 / number2;
        default:
        return number1 * number2;
    }
}

en_game_levels mix_game_level()
{
    int level = random_number(1, 3);
    return (en_game_levels)level;
}

en_operation_type mix_operation_type()
{
    int op_type = random_number(1, 4);
    return (en_operation_type)op_type;
} 

st_questions generate_question(en_game_levels game_level, en_operation_type op_type)
{
    st_questions question;
    if (game_level == en_game_levels::mix_level)
    {
        game_level = mix_game_level();
    }
    if (op_type == en_operation_type::mix_op_type)
    {
        op_type = mix_operation_type();
    }
    question.op_type = op_type;

    switch (game_level)
    {
        case en_game_levels::easy_level:
        question.number1 = random_number(1, 10);
        question.number2 = random_number(1, 10);

        question.correct_answer = simple_calculator(question.number1, question.number2, question.op_type);
        question.question_level = game_level;
        return question;

        case en_game_levels::medium_level:
        question.number1 = random_number(10, 50);
        question.number2 = random_number(10, 50);

        question.correct_answer = simple_calculator(question.number1, question.number2, question.op_type);
        question.question_level = game_level;
        return question;

        case en_game_levels::hard_level:
        question.number1 = random_number(50, 100);
        question.number2 = random_number(50, 100);

        question.correct_answer = simple_calculator(question.number1, question.number2, question.op_type);
        question.question_level = game_level;
        return question;
    }
    return question;
}

void correct_the_question_answer(st_quizz& quizz, short question_number)
{
    if (quizz.questionsList[question_number].player_answer != quizz.questionsList[question_number].correct_answer)
    {
        quizz.questionsList[question_number].question_answer_status = false;
        cout << "Wrong answer :-(\n";
        cout << "The right answer is : " << quizz.questionsList[question_number].correct_answer << "\n";
        quizz.wrong_answers_number++;
    }
    else
    {
        quizz.questionsList[question_number].question_answer_status = true;
        cout << "Right answer :-)\n";
        quizz.correct_answers_number++;
    }
    set_screen_color(quizz.questionsList[question_number].question_answer_status);
}

void print_question(st_quizz& quizz, short question_number)
{
    cout << "\nQuestion [" << question_number + 1 << "/" << quizz.number_of_questions << "]\n";
    cout << quizz.questionsList[question_number].number1 << "\n";
    cout << quizz.questionsList[question_number].number2 << " ";
    cout << op_type_symbol(quizz.questionsList[question_number].op_type) << "\n";
    cout << "_______________\n";
}

void generat_all_questions(st_quizz& quizz)
{
    for (short question = 0; question < quizz.number_of_questions; question++)
    {
        quizz.questionsList[question] = generate_question(quizz.game_level, quizz.game_op_type);
    }
}

void correct_questions_list(st_quizz& quizz)
{
    for (short question = 0; question < quizz.number_of_questions; question++)
    {
        print_question(quizz, question);
        quizz.questionsList[question].player_answer = read_player_answer();
        correct_the_question_answer(quizz, question);
    }
    quizz.final_results = (quizz.correct_answers_number >= quizz.wrong_answers_number);
}

string final_results_text(bool results)
{
    if (results)
    {
        return "pass :-)";
    }
    else
    {
        return "fail :-(";
    }
}

void print_final_results(st_quizz quizz)
{
    cout << "________________________________________\n";
    cout << "\n Fianl results is " << final_results_text(quizz.final_results) << "\n";
    cout << "________________________________________\n";
    cout << "Numbers of question     : " << quizz.number_of_questions << "\n";
    cout << "Questions Level         : " << game_level_text(quizz.game_level) << "\n";
    cout << "Operation type          : " << op_type_symbol(quizz.game_op_type) << "\n";
    cout << "Number of right answers : " << quizz.correct_answers_number << "\n";
    cout << "Number of wrong answers : " << quizz.wrong_answers_number << "\n";
    cout << "________________________________________" << endl;
}

void paly_game(st_quizz& quizz)
{
    quizz.number_of_questions = read_questions_number();
    quizz.game_level = read_game_level();
    quizz.game_op_type = read_game_op_type();

    generat_all_questions(quizz);
    correct_questions_list(quizz);
    print_final_results(quizz);
}

void reset_game()
{
    system("cls");
    system("color 0F");
}

void start_game()
{
    st_quizz quizz;
    char play_again = 'y';
    do
    {
        reset_game();
        paly_game(quizz);

        cout << "Do you want to play again?   ";
        cin >> play_again;
    } while (play_again == 'y' || play_again == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));
    start_game();
    return 0;
}
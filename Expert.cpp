// EXPERT.CPP

#include "Expert.h"

#define INCORRECT printf("Введите корректный ответ:\n")
#define EOL printf("\n")
#define DOT printf(".")

#define CHEERS switch(expert_cheer())\
                {\
                    case TRUE:\
                        question = ROOT(Expert);\
                        continue;\
                    \
                    case FALSE:\
                    \
                    case EXIT:\
                        exit = 0;\
                        continue;\
                    \
                    case DEFINE:\
                        def = 1;\
                        EOL;\
                        continue;\
                    \
                    case COMPARE:\
                        comp = 1;\
                        EOL;\
                        continue;\
                    \
                    case DRAW:\
                        tree_draw(dot, EXPERTDUMP, Expert);\
                        EOL;\
                        continue;\
                    default:\
                        return 1;\
                    }

int Akinator(const char dot[], const char* SAVENAME)
{
    const char EXPERTDUMP[10] = "expert";

    Tree* Expert = tree_read(SAVENAME);

    int exit = 1;                                               // variable to exit expert
    int def = 0;
    int comp = 0;

    Node* question = ROOT(Expert);

    while(exit)
    {

        if (def)
        {
            def = 0;

            printf("Введите: \"Выход\"/\"Exit\" для выхода из определения\n");                     // exit condition
            EOL;
            if (expert_get_definition(Expert))
            {
                continue;
            }

            CHEERS;
        }

        if (comp)
        {
            comp = 0;

            printf("Введите: \"Выход\"/\"Exit\" для выхода из сравнения\n");                     // exit condition
            EOL;
            if (expert_get_comparison(Expert))
            {
                continue;
            }

            CHEERS;
        }

        printf("Введите: \"Выход\"/\"Exit\" для выхода из программы\n");                     // exit condition
        printf("         \"Определить\"/\"Define\" для получения определения объкта\n");     // define condition
        printf("         \"Сравнить\"/\"Compare\" для сравнения объектов\n");                  // comparison condition
        printf("         \"Варианты\"/\"Tree\" для просмотра всех объектов\n\n");      // Draw

        int que_flag = 0;                                       // Flag if question

        if (*question->info == '?')                             // Question
        {
            que_flag = 1;
            printf("Ваш персонаж %c%s? Да/Нет\n", tolower(*(question->info + 1)), question->info + 2);
        }
        else
            printf("Это наверняка %s? Да/Нет\n", question->info);

        int ans = expert_get_answer();
        switch(ans)
        {
            case TRUE:
            {
                if (que_flag)
                    question = LEFT(question)? LEFT(question): expert_new_item(Expert, question, L);
                else
                {
                    CHEERS;
                }
                break;
            }

            case FALSE:
            {
                if (que_flag)
                    question = RIGHT(question)? RIGHT(question): expert_new_item(Expert, question, R);
                else
                    question = expert_new_branch(Expert, question);
                break;
            }

            case EXIT:
                exit = 0;
                continue;

            case DEFINE:
                def = 1;
                continue;

            case COMPARE:
                comp = 1;
                continue;

            case DRAW:
                tree_draw(dot, EXPERTDUMP, Expert);
                EOL;
                continue;

            default:
                INCORRECT;
                EOL;
                continue;
        }
        tree_print(Expert, SAVENAME);
    }

    tree_Dtor(Expert);
    free(Expert);
    return 0;
}


#define GETSTR(name)    char* name = (char*) calloc(STRLEN, sizeof(*(name)));\
                        gets(name);\
                        EOL;

Node* expert_new_item(Tree* tr, Node* nd, int POS)
{
    assert(tr && nd);

    printf("А кто это?");
    GETSTR(buff);

    Node* new_nd = NULL;

    if (POS)
    {
        new_nd = tree_insert_left (tr, nd, buff);
    }
    else
    {
        new_nd = tree_insert_right(tr, nd, buff);
    }

    return new_nd;
}

Node* expert_new_branch(Tree* tr, Node* nd)
{
    assert(tr && nd);

    printf("А кто это?\n");
    GETSTR(buffans);

    printf("В чём отличие?\n");

    char* buffquest = (char*) calloc(STRLEN, sizeof(*buffquest));\
    buffquest[0] = '?';
    gets(buffquest + 1);

    EOL;

    Node* new_nd = tree_insert_left(tr, nd, buffans);
    tree_insert_right(tr, nd, nd->info);

    nd->info = buffquest;

    return new_nd;
}
#define NCOMPARE(state,n_letters) (strnicmp(answer, state, n_letters) == 0)
#define RECOGNIZE(state,n_letters,translate,n_tranletters,result) if (NCOMPARE(state, n_letters) || NCOMPARE(translate, n_tranletters))\
                                                                    {\
                                                                        return result;\
                                                                    }\

int expert_get_answer()
{
    char answer[5] = "";

    if (!gets(answer))
    {
        return 0;
    }

    EOL;

    RECOGNIZE("YES", 3, "Да", 2, TRUE);
    RECOGNIZE("NO", 2, "Нет", 3, FALSE);
    RECOGNIZE("EXIT", 4, "Выход", 5, EXIT);
    RECOGNIZE("Определить", 5, "Define", 3, DEFINE);
    RECOGNIZE("Сравнить", 4, "Compare", 4, COMPARE);
    RECOGNIZE("Варианты", 3, "Tree", 4, DRAW)

    return 0;
}

int expert_cheer()
{
    printf("Ура!\nПродолжить? Да/Нет\n");
    int ans = expert_get_answer();

    while(!ans)
    {
        INCORRECT;
        printf("Продолжить? Да/Нет\n");
        ans = expert_get_answer();
    }

    return ans;
}

#define INVITEDEF   printf("Введите определяемый объект:\n");\
                    while (!gets(answer));\
                    EOL;\
                    nd = node_find(ROOT(tr), answer, expert_info_cmp);

#define PRINTOBJ(format,object)    printf(format, toupper(*(object)), (object) + 1)

int expert_get_definition(Tree* tr)
{
    Node* nd = NULL;
    char answer[STRLEN] = "";
    INVITEDEF;
    RECOGNIZE("Выход", 5, "Exit", 4, EXIT);

    while(!nd)
    {
        INCORRECT;
        INVITEDEF;
        RECOGNIZE("Выход", 5, "Exit", 4, EXIT);
    }

    PRINTOBJ("%c%s ", answer);

    expert_print_way(PARENT(nd), ",", node_define(nd));

    DOT;
    EOL;
    EOL;

    return 0;
}

#define INVITECOMP(state,node)  printf("Введите персонажа" state " сравнить:\n");\
                                while (!gets(answer));\
                                EOL;\
                                node = node_find(ROOT(tr), answer, expert_info_cmp);

#define COMPAREIN(state,node)   INVITECOMP(state, node);\
                                RECOGNIZE("Выход", 5, "Exit", 4, EXIT);\
                                \
                                while(!(node))\
                                {\
                                    INCORRECT;\
                                    INVITECOMP(state, node);\
                                    RECOGNIZE("Выход", 5, "Exit", 4, EXIT);\
                                }
#define PRINTINFO(node,mode)     if (!(mode)) \
                                printf("не ");\
                            \
                            printf("%c%s", tolower(*((node)->info + 1)), (node)->info + 2);

int expert_get_comparison(Tree* tr)
{
    Node* nd1 = NULL;
    Node* nd2 = NULL;
    char answer[STRLEN] = "";

    COMPAREIN(", которого нужно", nd1);
    COMPAREIN(", с которым нужно", nd2);

    int nd1_side = 0;                               // side of nd1 related to common
    Node* com = tree_find_common(nd1, nd2, &nd1_side);

    if (com != ROOT(tr))
    {
        PRINTOBJ("%c%s так же, как и ", nd1->info);                 // common
        PRINTOBJ("%c%s, ", nd2->info);

        expert_print_way(PARENT(com), ",", node_define(com));
        DOT;
        EOL;
    }

    if (nd1 != nd2)
    {
        PRINTOBJ("Но %c%s, в отличие от ", nd1->info);
        PRINTOBJ("%c%s, ", nd2->info);

        PRINTINFO(com,nd1_side);

        DOT;
        EOL;
    }

    EOL;

    return 0;
}



int expert_info_cmp(tree_type answer, tree_type info)
{
    if (NCOMPARE(info, strlen(info)))
        return 0;
    else
        return 1;
}



int expert_print_way(Node* nd,const char* separate, int mode)                  // includes input nd info, way is found until end_of_way
{
    if (!nd)
    {
        return 0;
    }

    expert_print_way(PARENT(nd), separate, node_define(nd));

    if (node_define(nd) != NOPARENT)
    {
        printf("%s ", separate);
    }

    PRINTINFO(nd,mode);

    return 0;
}

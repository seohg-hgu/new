#include "vote.h"

T_vote *vote[MAX_VOTE];
int v_count = 0;
int available_vote() //투표를 추가할 공간이 남아 있는가?
{
    int i;
    for (i = 0; i < MAX_VOTE; i++)
    {
        if (vote[i] == NULL)
            return 1;
    }
    return 0;
}

T_vote *v_search_by_name(char *n) //
{
    int i;
    for (i = 0; i < MAX_VOTE; i++)
    {
        if (vote[i] && strcmp(vote[i]->name, n) == 0)
            return vote[i];
    }
    return NULL;
}
T_vote *v_search_by_name_index(char *n) //
{
    int i;
    for (i = 0; i < MAX_VOTE; i++)
    {
        if (vote[i] && strcmp(vote[i]->name, n) == 0)
            return i;
    }
    return NULL;
}

void v_create(char *n, int a) //투표 정보 입력&저장
{
    int index = v_first_available();
    vote[index] = (T_vote *)malloc(sizeof(T_vote));
    T_vote *p = vote[index];
    strcpy(p->name, n);
    p->amount = a;
    printf("choice >\n");
    for (int i = 0; i < a; i++)
    {
        printf("%d. ", i + 1);
        scanf("%s", p->choice[i]);
    }
    v_count++;
}
void v_editer_choice(T_vote *p)
{
    printf("name = %s\n", p->name);
    printf("amount = %d\n", p->amount);

    printf("choice > \n");
    for (int i = 0; i < p->amount; i++)
    {
        printf("%d. ", i + 1);
        scanf("%s", p->choice[i]);
    }
}
void v_editer(T_vote *p, int a)
{

    p->amount = a;
    printf("Change amount :)\n");
}
void v_delete(T_vote *p)
{
    int i, index;
    for (i = 0; i < MAX_VOTE; i++)
    {
        if (vote[i] == p)
        {
            index = i;
            break;
        }
    }
    free(p);
    vote[index] = NULL;
    v_count--;
}
int V_count()
{
    return v_count;
}
int v_first_available() // 추가할 수 있는 가장 빠른 포인터 배열의 인덱스 찾기
{
    int i;
    for (i = 0; i < MAX_VOTE; i++)
    {
        if (vote[i] == NULL)
            return i;
    }
    return -1;
}

char *v_getname(T_vote *p)
{
    return p->name;
}
int *v_getamount(T_vote *p)
{
    return p->amount;
}
char *v_getchoice(T_vote *p, int a)
{
    return p->choice[a];
}
void v_get_all(T_vote *a[])
{
    int i, c = 0;
    for (i = 0; i < MAX_VOTE; i++)
    {
        if (vote[i])
        {
            a[c] = vote[i];
            c++;
        }
    }
}

void v_start(T_vote *p, char name)
{
    int choise;
    printf("%s\n", v_getname(p));
    for (int i = 0; i < v_getamount(p); i++)
    {
        printf("\t(%d) %s\n", i + 1, v_getchoice(p, i));
    }
    printf("Enter number : ");
    scanf("%d", &choise);
    choise--;
    p->vote_box[choise]++;
}
void v_file_save()
{
    char name[50];
    char choice[30];
    int vote_box, amount;
    FILE *fp;
    fp = fopen("txt_file/vote.txt", "r");
    if (fp == NULL)
    {
        printf("파일 열기 오류");
    }
    else
    {
        while (fscanf(fp, "%s %d", name, &amount) == 2)
        {
            int index = v_first_available();
            vote[index] = (T_vote *)malloc(sizeof(T_vote));
            T_vote *p = vote[index];

            strcpy(p->name, name);
            p->amount = amount;
            for (int i = 0; i < amount; i++)
            {
                fscanf(fp, "%s %d", choice, &vote_box);
                strcpy(p->choice[i], choice);
                p->vote_box[i] = vote_box;
            }
            v_count++;
        }
    }
    fclose(fp);
}
void v_add_file()
{
    FILE *fp = fopen("txt_file/vote.txt", "wt");
    int size = V_count();
    T_vote *all_vote[MAX_VOTE];
    v_get_all(all_vote);
    for (int i = 0; i < size; i++)
    {
        T_vote *p = all_vote[i];
        fprintf(fp,"%s %d ",p->name,p->amount);
        for (int i = 0; i < p->amount; i++)
        {
            fprintf(fp,"%s %d ", p->choice[i],p->vote_box[i]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}
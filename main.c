#include <stdio.h>
#include <memory.h>
// 학생의 구조체
typedef struct Student_t{
    int id;
    char name[20];
    double score;
}Student;
//학생 입력
void insertStudent(Student st[]){
    for(int i=0;i<10;i++)
    {
        printf("%d번째 학생이름입력:",i+1);
        scanf("%s",&st[i].name);
        printf("%d번째 학생학번입력:",i+1);
        scanf("%d",&(st[i].id));
        printf("%d번째 학생성적입력:",i+1);
        scanf("%lf",&(st[i].score));
        printf("%s,%d, %0.2lf \n",&st[i].name,st[i].id,st[i].score);
    }
}
//최대값구하는 함수
void MaxScore(Student s[10],double maxscore,char maxname[],int maxid){
    //비교
    for(int i=0;i<10;i++) {
        //비교값보다 더 큰 점수를 갖은 학생 발견시
        if (maxscore < s[i].score) {
            maxscore = s[i].score;
            strcpy(maxname,s[i].name);
            maxid = s[i].id;
        }
    }
    printf("%d학번 %s의 점수가 %0.2lf이므로 제일 높습니다.", maxid,maxname,maxscore);
}
//최소값구하는 함수
void MinScore(Student s[10],double minscore,char minname[],int minid){
    /*
     minname은 name의 주소가 사용된다.
     즉,
     MaxScore(student,score,name,id);코드에서
     MaxScore에서 사용된 maxname이 이미 main에서의 name의 주소를 사용하기때문에 변경된 name에는 maxname이 들어가있다.
     즉,초기화를 위해 strcpy(minname,s[0].name; 를 사용해 준다.
     */
    strcpy(minname,s[0].name);
    //비교
    for(int i=0;i<10;i++) {
        //비교값보다 더 작은 점수를 갖은 학생 발견시
        if (minscore > s[i].score) {
            minscore = s[i].score;
            strcpy(minname,s[i].name);
            minid = s[i].id;
        }
    }
    printf("%d학번 %s의 점수가 %0.2lf이므로 제일 낮습니다.", minid,minname,minscore);
}

int main() {
    Student student[10];
    //학생 입력
    insertStudent(student);
    //비교에 쓰일 초기값 학생 선언
    double score=student[0].score;
    char name[20];
    strcpy(name,student[0].name);
    int id=student[0].id;
    //최대값최소값 구하기
    MaxScore(student,score,name,id);
    MinScore(student,score,name,id);
    return 0;
}


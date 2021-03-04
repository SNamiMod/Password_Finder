//**************************
//Seyed Nami Modarressi
//9733069
//Mid_Term Project
//**************************

#include <stdio.h>

int guess_counter=1;
int pass_data[10][4]={0};
int reaction_data[10][4]={0};
int reaction[4]={0};

// 20736 = 12^4
//pass elements : ( 0 to 9 ) & ( * -> 10 ) & ( # -> 11)
int pass_possible[20736][4];
int pass_counter=0;

int zero_element[100]={0};
int zero_counter=0;
int one_element[2][100]={0};
int one_counter=0;
int two_element[2][100]={0};
int two_counter=0;

int pass_free_position_counter=4;

//final pass : check "2 2 2 2" reaction
int final_pass(){

    int i;
    int counter_2 = 0;

    for(i = 0; i < 4; i++){

        if (reaction[i]==2){

            counter_2=counter_2+1;
        }
    }

    if (counter_2==4){

        return 1;
    }
    return 0;

}
// creat all possible passwords
void pass_all(){

    int i;
    int j;
    int k;
    int h;
    int q=0;

    for (i = 0; i < 12; i++) {
        for (j = 0; j < 12; j++) {
            for (k = 0; k < 12; k++) {
                for (h = 0; h < 12; h++) {

                    pass_possible[q][0]=i;
                    pass_possible[q][1]=j;
                    pass_possible[q][2]=k;
                    pass_possible[q][3]=h;
                    q=q+1;

                }
            }
        }
    }
}
// get reaction
void reaction_get(){

    int i;

    for(i = 0; i < 4; i++) {

        scanf("%d", &reaction[i]);

    }

}
//save the passwords and reactions (save in pass_data & reaction_data)
void data_update(){

    int i;
    int j;

    for(i = 0; i < 4; i++){

        reaction_data[guess_counter-1][i]=reaction[i];
        pass_data[guess_counter-1][i]=pass_possible[pass_counter][i];

    }

    for(i = 0; i < 4; i++){

        if (reaction[i]==0){

            zero_element[zero_counter]=pass_possible[pass_counter][i];
            zero_counter=zero_counter+1;

        }
        if (reaction[i]==1){

            one_element[0][one_counter]=pass_possible[pass_counter][i];
            one_element[1][one_counter]=i;
            one_counter=one_counter+1;

        }
        if (reaction[i]==2){

            two_element[0][two_counter]=pass_possible[pass_counter][i];
            two_element[1][two_counter]=i;
            two_counter=two_counter+1;

        }

    }


    for(i = 0; i < 4; i++){

        if (reaction[i]==2){

            for(j = 0; j < two_counter; j++){

                if (reaction[i]==two_element[1][j] && pass_possible[pass_counter][i]==two_element[0][j]){

                    continue;

                } else{

                    pass_free_position_counter=pass_free_position_counter-1;
                    break;

                }
            }
        }
    }
}
//check zero elements positions in password that we want to print
// x : pass_counter
int is_zero_okay(int x){

    int i;
    int j;

    for(i = 0; i < 4; i++){

        for(j = 0; j < zero_counter; j++){

            if (pass_possible[x][i]== zero_element[j]){

                return 0;

            }
        }
    }

    return 1;
}
//check one elements positions in password that we want to print
// x : pass_counter
int is_one_okay(int x){

    int i;
    int j;

    for(i = 0; i < 4; i++){

        for(j = 0; j < one_counter; j++){

            if (pass_possible[x][i]==one_element[0][j] && i==one_element[1][j]){

                return 0;

            }
        }
    }

    return 1;
}
//check two elements positions in password that we want to print
// x : pass_counter
int is_two_okay(int x){

    int i;
    int j;

    for(i = 0; i < 4; i++){

        for(j = 0; j < two_counter; j++){

            if (i==two_element[1][j] && two_element[0][j]!=pass_possible[x][i]){

                return 0;

            }
        }
    }

    return 1;
}
// print the password that we choose from pass_possible
void pass_print(){

    int j;

    printf("GUESS%d: ",guess_counter);

    for(j = 0; j < 4; j++){

        if (pass_possible[pass_counter][j]==10){
            printf("* ");
        }

        if (pass_possible[pass_counter][j]==11){
            printf("# ");
        }

        if (pass_possible[pass_counter][j]!=10 && pass_possible[pass_counter][j]!=11){
            printf("%d ",pass_possible[pass_counter][j]);
        }
    }

    printf("\n");
}

void pass_counter_calculator(){

    int i;
    int flag=0;

    // Guess1 : 0 1 2 3
    if (guess_counter==1){

        // 171 : (0 1 2 3)
        pass_counter=171;
        pass_print();

    }

    // Guess2 : 4 5 6 7
    if(guess_counter==2){

        // 7711 : (4 5 6 7)
        pass_counter=7711;
        pass_print();

    }

    // Guess3 : 8 9 * #
    if(guess_counter==3){

       //15251 : (8 9 * #)
       pass_counter=15251;
       pass_print();

    }

    if(guess_counter==4) {

        pass_counter = 0;

    }

    if(guess_counter>=4){

        for (i = pass_counter; i < 20736 && flag == 0; i++) {

            if (is_zero_okay(i) == 1 && is_one_okay(i) == 1 && is_two_okay(i) == 1) {

                flag = 1;
                pass_counter = i;

            }
        }

        pass_print();
    }

}
// check reactions with reaction_data
int reaction_check(){

    int i;
    int j;
    int k;

    for(i = 0; i < 4; i++){

        for(j = 0; j < guess_counter; j++){

            if (pass_possible[pass_counter][i]==pass_data[j][i]){

                if (reaction[i]!=reaction_data[j][i]){

                    return 0;

                }
            }

            if (pass_possible[pass_counter][i]!=pass_data[j][i]){

                if (reaction[i]==reaction_data[j][i] && reaction[i]==2){

                    return 0;

                }
            }
        }
    }

    for(i = 0; i < 4; i++){

        for(j = 0; j < guess_counter; j++){

            for(k = 0; k < 4; k++){

                if (pass_possible[pass_counter][i]==pass_data[j][k] && i!=k ){

                    if (reaction[i]*reaction_data[j][k]==0){

                        return 0;

                    }

                    if (reaction[i]==reaction_data[j][k] && reaction[i]==1){

                        if (pass_free_position_counter==2){

                            return 0;

                        }
                    }
                }
            }
        }
    }

    return 1;
}

int main() {

    int i;
    int j;

    for(i = 0; i < 10; i++){
        for(j = 0; j < 4; j++){

            pass_data[i][j]=-1;
            reaction_data[i][j]=-1;

        }
    }

    pass_all();

   while (guess_counter<=10 && final_pass()!=1) {

          pass_counter_calculator();

       do{

            reaction_get();

            if (reaction_check()!=1){

                printf("The guidance was wrong. Be more careful and helpful.\n");

            }

        }while (reaction_check()!=1);

        data_update();
        guess_counter=guess_counter+1;

    }

    if (final_pass()!=1){

        printf("Ruuuuun!!!");

    }else{
        printf("Done :)");
    }

  }

